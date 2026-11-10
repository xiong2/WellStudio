#include <qfileinfo.h>
#include "xloadsegytozxythread.h"
#include "xsegyloadparameters.h"
#include "xseismicutmtool.h"
#include "xseismicdatavolume.h"
#include "xregulardatawriter.h"
#include "xseismicirregularreader.h"
#include "xglobal.h"

CXLoadSEGYToZXYThread::CXLoadSEGYToZXYThread(CXSEGYLoadParameters* pLoadParameters)
{
	m_pLoadParameters = pLoadParameters;
	m_pDataWriter = NULL;
}

CXLoadSEGYToZXYThread::~CXLoadSEGYToZXYThread()
{
	this->wait();

	if(m_pDataWriter)
		delete m_pDataWriter;

	//if (IsStopped())
	//{
	//	CXSeismicDataVolume *pDV = m_pLoadParameters->GetDataVolume();
	//	delete pDV;		
	//} 
}

void CXLoadSEGYToZXYThread::RunThread()
{
	if (m_pLoadParameters->IsIrregular())
	{
		_irregularImport();
	}
	else
	{
		_regularImport();
	}
}

void CXLoadSEGYToZXYThread::_irregularImport()
{
	// Data volume
	CXSeismicDataVolume *pDV = m_pLoadParameters->GetDataVolume();
	QString sTInfoFile = pDV->GetTraceInfoFileName();

	// Set the names for progress dialog
	QString strWindowName = "Converting SEG-Y File to Trace File";
	QString strTaskName = "Generating the trace file...(" + pDV->GetObjectName() + ")";
	EmitSetWindowName(strWindowName);
	EmitSetTaskName(strTaskName);
	EmitStartComputing();

	//	Calculate import range.
	CXSeismicUTMTool *pUTM = m_pLoadParameters->GetUTMTool();
	unsigned int nI = pUTM->GetNI();
	unsigned int nJ = pUTM->GetNJ();
	unsigned int nZ = m_pLoadParameters->GetImportSampleNumber();
	qint64 i, j, iPos = 0;
	int iLine, iCDP, iMaxFold = m_pLoadParameters->GetMaxFold();
	bool bAzimuth = m_pLoadParameters->IsAzimuth();
	int iLength = 10 + 2 * (1 + bAzimuth) * iMaxFold;
	int iNum = 2 * (1 + bAzimuth);

	CXSeismicIrregularReader traceReader(iMaxFold, pUTM, sTInfoFile);
	traceReader.SetAzimuth(bAzimuth);
	char *pBuffer = traceReader.GetBuffer();

	QHash<QPair<unsigned short, unsigned short>, SKETraceOffsets *>& hashTraceInfo = m_pLoadParameters->GetTraceInfo();

	for (i = 0; i < nI; i++)
	{
		for (j = 0; j < nJ; j++)
		{
			//	Re-initialize.
			memset(pBuffer, 0, iLength);
			
			qint64 *pITmp = (qint64 *)pBuffer;
			pITmp[0] = iPos;

			pUTM->IJToLine(i, j, iLine, iCDP);
			QPair<unsigned short, unsigned short> theKey((unsigned short)iLine, (unsigned short)iCDP);
			if (hashTraceInfo.contains(theKey))
			{
				SKETraceOffsets *pTInfo = hashTraceInfo.take(theKey);
				short *pSTmp = (short *)pBuffer;
				pSTmp[4] = pTInfo->m_vecIOffsetAzim.size() / (1 + bAzimuth);
				memcpy(pBuffer + 10, pTInfo->m_vecIOffsetAzim.data(), pSTmp[4] * iNum);
			
				//	Start position of next CDP.
				iPos += (nZ * 4 * pSTmp[4]);

				delete pTInfo;
			}

			pBuffer += iLength;
		}
	}

	traceReader.SaveToFile();

	//	Prepare the output trace file.
	if (!QFile::resize(pDV->GetTraceFileName(), iPos))
	{
		EmitGeneralErrorMsg(QString("Unable to open the trace file to write!"));
		return;
	}

	QStringList listFile = m_pLoadParameters->GetAllSEGYFiles();

	//	A loop to scan each SEGY File.
	for (int i = 0; i < listFile.count(); i++)
	{
		QFileInfo qFI(listFile.at(i));
		QString strTaskName = "Importing " + qFI.fileName() + " (" + QString::number(i + 1) + " of " + QString::number(listFile.count()) + " files) ...";
		EmitSetTaskName(strTaskName);
		EmitResetProgressBar();

		if (!_importOneIrreFile(listFile.at(i), traceReader.GetBuffer()))
			return;
	}
}

void CXLoadSEGYToZXYThread::_regularImport()
{
	// Data volume
	CXSeismicDataVolume *pDV = m_pLoadParameters->GetDataVolume();

	// Set the names for progress dialog
	QString strWindowName = "Converting SEG-Y File to Trace File";
	EmitSetWindowName(strWindowName);
	EmitStartComputing();
	//qApp->processEvents();    

	//	Calculate import range.
	CXSeismicUTMTool *pUTM = m_pLoadParameters->GetUTMTool();
	unsigned int nI = pUTM->GetNI();
	unsigned int nJ = pUTM->GetNJ() * pDV->GetMaxFold();
	unsigned int nZ = m_pLoadParameters->GetImportSampleNumber();

	//	Prepare the writer to generate ZXY file.
	m_pDataWriter = new CXRegularDataWriter<float>(pDV->GetTraceFileName(), nI, nJ, nZ);

    if (!m_pDataWriter->Open())
    {
		EmitGeneralErrorMsg(QString("Unable to open the trace file to write!"));
		return;
    }
   
	QStringList listFile = m_pLoadParameters->GetAllSEGYFiles();

	//	A loop to scan each SEGY File.
	for(int i = 0; i < listFile.count(); i++)
	{
		QFileInfo qFI(listFile.at(i));
		QString strTaskName = "Importing " + qFI.fileName() + " (" + QString::number(i + 1) + " of " + QString::number(listFile.count()) + " files) ...";
		EmitSetTaskName(strTaskName);
		EmitResetProgressBar();

		if (!_importOneFile(listFile.at(i)))
			return;
	}
	
	delete m_pDataWriter;
	m_pDataWriter = NULL;

	if (!IsStopped())
	{
		//	Correct time range caused by datum or user specification.
		m_pLoadParameters->CorrectTimeRange();
		EmitUpdateProgress(100, 100); 
	} 
}

bool CXLoadSEGYToZXYThread::_importOneFile(QString strSEGYFile)
{	
	//	Open the segy file and skip the volume header.
	QFile qFile(strSEGYFile);
	if(!qFile.open(QIODevice::ReadOnly))
	{
		EmitGeneralErrorMsg(QString("Unable to read the SEGY file!"));
		return false;
	}
	qFile.seek(3600);

	unsigned int nZ = m_pLoadParameters->GetImportSampleNumber();
	int iInline, iCrossline, iAzim;
	char *pDataBuff = new char[m_pLoadParameters->GetTraceLength()];
	float *pData = new float[nZ];

	//	The number of traces varied for each file.
	//qint64 numTrace = m_pLoadParameters->GetTraceNumber();
	qint64 numTrace = (qFile.size() - 3600) / (m_pLoadParameters->GetTraceLength() + 240);
	qint64 i, iInd;
	CXSeismicUTMTool *pUTM = m_pLoadParameters->GetUTMTool();
	CXSeismicDataVolume *pDV = m_pLoadParameters->GetDataVolume();
	float fStartOffset, fOffsetStep, fOffset;
	int iNumOffset;
	pDV->GetOffsetInfo(fStartOffset, fOffsetStep, iNumOffset);

	//	A big loop to read each trace. 	
    qint64 nCurrentPer, nPercent=0, iCurrentStep=0 ;
	for(i = 0; i < numTrace; i++)
	{
		// Progress bar
		nCurrentPer = static_cast<qint64>((++iCurrentStep)*100/numTrace);
		if (nCurrentPer > nPercent)
		{
			nPercent++;
			if (IsStopped())
				break;
			else
			{
				EmitUpdateProgress(nPercent, 100);
			}
		}

		//	Read one trace.
		double dx, dy;
		if (!m_pLoadParameters->ReadATrace(qFile, iInline, iCrossline, fOffset, iAzim, dx, dy, pDataBuff))
		{
			break;
		}

		iInd = pUTM->GetIndexOfOneNode(iInline, iCrossline);

		//	If the trace not within importing range, just ignore it.
		if(iInd < 0)
			continue;
		else
		{
			if (iNumOffset > 1)
			{
				//	Prestack.
				iInd = iInd * iNumOffset + (fOffset - fStartOffset) / fOffsetStep;
			}

			//	Convert the trace data.
			m_pLoadParameters->ConvertTraceData(pDataBuff, pData);

			//	Write it to file.
			m_pDataWriter->Write(iInd*nZ, nZ, pData);
		}
	}

	delete []pDataBuff;
	delete []pData;

	if (IsStopped())
		return false;
	else
	{
		return true;
	}
}

bool CXLoadSEGYToZXYThread::_importOneIrreFile(QString strSEGYFile, char *pBuffer)
{
	//	Open the segy file and skip the volume header.
	QFile qFile(strSEGYFile);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		EmitGeneralErrorMsg(QString("Unable to read the SEGY file!"));
		return false;
	}
	qFile.seek(3600);

	unsigned int nZ = m_pLoadParameters->GetImportSampleNumber();
	qint64 i, iInd;
	int iInline, iCrossline, iCount = 0, iLastInline = -1, iLastXline = -1, iAzim;
	float fOffset;
	char *pDataBuff = new char[m_pLoadParameters->GetTraceLength()];
	float *pData = new float[nZ];

	qint64 iPos, numTrace = (qFile.size() - 3600) / (m_pLoadParameters->GetTraceLength() + 240);
	CXSeismicUTMTool *pUTM = m_pLoadParameters->GetUTMTool();
	CXSeismicDataVolume *pDV = m_pLoadParameters->GetDataVolume();

	int iLength = 10 + 2 * (1 + m_pLoadParameters->IsAzimuth()) * m_pLoadParameters->GetMaxFold();

	QFile qTraceFile(pDV->GetTraceFileName());
	if (!qTraceFile.open(QIODevice::ReadWrite))
	{
		EmitGeneralErrorMsg(QString("Unable to write to the trace file!"));
		return false;
	}

	//	A big loop to read each trace. 	
	qint64 nCurrentPer, nPercent = 0, iCurrentStep = 0;
	for (i = 0; i < numTrace; i++)
	{
		// Progress bar
		nCurrentPer = static_cast<qint64>((++iCurrentStep) * 100 / numTrace);
		if (nCurrentPer > nPercent)
		{
			nPercent++;
			if (IsStopped())
				break;
			else
			{
				EmitUpdateProgress(nPercent, 100);
			}
		}

		//	Read one trace.
		double dx, dy;
		if (!m_pLoadParameters->ReadATrace(qFile, iInline, iCrossline, fOffset, iAzim, dx, dy, pDataBuff))
		{
			break;
		}

			iInd = pUTM->GetIndexOfOneNode(iInline, iCrossline);

		//	If the trace not within importing range, just ignore it.
		if (iInd < 0)
			continue;

		if (iLastInline != iInline || iLastXline != iCrossline)
		{
			char *pBuff = pBuffer + iInd * iLength;
			iPos = *((qint64 *)pBuff);
			qTraceFile.seek(iPos);

			iLastInline = iInline;
			iLastXline = iCrossline;
		}

		//	Convert and write the trace data.
		m_pLoadParameters->ConvertTraceData(pDataBuff, pData);
		qTraceFile.write((char *)pData, 4 * nZ);
	}

	qTraceFile.close();
	delete[]pDataBuff;
	delete[]pData;

	if (IsStopped())
		return false;
	else
	{
		return true;
	}
}