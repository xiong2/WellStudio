#include "xsegyloadparameters.h"

#include <QFile>
#include <QFileInfo>
#include <cmath>

#include "xdataconvertor.h"
#include "xsegylineheader.h"
#include "xsegytraceheader.h"
#include "xseismicutmtool.h"
#include "xseismicdatavolume.h"
#include "xprestackgather.h"
#include "xglobal.h"

CXSEGYLoadParameters::CXSEGYLoadParameters(QStringList listStrSEGYFiles)
{
	m_bPrestack					= false;
	m_bAzimuth					= false;
	m_bDataLine					= false;
	m_bPrestackGather			= false;
	m_pLineHeader				= new CXSEGYLineHeader;
	m_pTraceHeader				= new CXSEGYTraceHeader;

	m_iDataType					= 0;
	m_bDataFlip					= true;
	m_iSampleNumber				= 0;
	m_fSampleInterval			= 0.;
	m_iTraceNumber				= 0;
	m_iTraceLength				= 0;
	m_bOverwriteSampleNumber	= false;
	m_bOverwriteSampleInterval	= false;
	m_bOverwriteScale			= false;
	m_bCreateSliceFile			= false;
	m_bCreateBrickFile			= false;
	m_dXYScale					= 1.;

	m_iInlinePos				= 5;
	m_iCrosslinePos				= 21;
	m_iOffsetPos				= 37;
	m_iXPos = 73;
	m_iYPos = 77;
	m_iDXPos = 81;
	m_iDYPos = 85;
	m_iAzimuthPos				= 41;

	m_iSEPos = 45;
	m_iDEPos = 41;
	m_iFBPos = 113;

	m_iInlineInd				= 1;
	m_iCrosslineInd				= 5;
	m_iOffsetInd				= 11;
	m_iAzimuthInd				= 12;
	m_iXInd = 21;
	m_iYInd = 22;
	m_iDXInd = 23;
	m_iDYInd = 24;

	m_iSEInd = 13;
	m_iDEInd = 12;
	m_iFBInd = 37;

	m_iMaxFold					= 1;
	m_iNumOffset				= 1;
	m_fStartOffset				= 0.;
	m_fOffsetInc				= 0.;

	m_iMinAzi					= 0;
	m_iMaxAzi					= 0;

	m_fStartTime				= 0.;
	m_fStartImportTime			= 0.;
	m_fTimeShiftTo				= -999.;
	m_iValidStartLine			= 1;
	m_iValidEndLine				= 100000;

	m_eDomainType				= eTimeDomain;
	m_sZUnit					= "ms";	//	default using ms.

	m_pGather = NULL;
	m_pDV = NULL;
	m_strDVName					= "";
	//m_seismicTemplate = IID_TEMPLATE_Poststack_Amplitude_Seismic;

	m_pUTMTool					= new CXSeismicUTMTool();
	m_pParentObject = NULL;

	m_pOriUTMTool = new CXSeismicUTMTool();
	m_pOriUTMTool->Copy(m_pUTMTool);

	memset(m_pVolumeHeader, 0, VOLUMEHEADERLENGTH);

	m_listStrSEGYFile = listStrSEGYFiles;

	//	Automatically parse the parameters.
	AutoParseParameters();
}

CXSEGYLoadParameters::~CXSEGYLoadParameters()
{
	if(m_pLineHeader)
		delete m_pLineHeader;

	if(m_pTraceHeader)
		delete m_pTraceHeader;

	delete m_pUTMTool;
	delete m_pOriUTMTool;
}

void CXSEGYLoadParameters::ResetUTMTool()
{
	m_pUTMTool->Copy(m_pOriUTMTool);
}

//	Get the specified (index start from 1 rather than 0) trace header of the 1st segy file, do not delete the return pointer!
CXSEGYTraceHeader* CXSEGYLoadParameters::GetOneTraceHeader(qint64 iTraceIndex)
{
	if(iTraceIndex < 1 || iTraceIndex > m_iTraceNumber)
		return NULL;

	QFile qFile(m_listStrSEGYFile.at(0));
	if(!qFile.open(QIODevice::ReadOnly))
		return NULL;

	qFile.seek(VOLUMEHEADERLENGTH + LINEHEADERLENGTH + (iTraceIndex - 1) * (m_iTraceLength + TRACEHEADERLENGTH));
	qFile.read(m_pTraceHeader->GetOriginalTraceHeader(), TRACEHEADERLENGTH);
	qFile.close();

	return m_pTraceHeader;
}

void CXSEGYLoadParameters::SetDataType(int iDataType)
{
	if(iDataType >= 0 && iDataType < 5)
	{	
		m_iDataType = iDataType;

		//	Re-caculate the trace length and number.
		int iSampleBytes = 4;
		if(m_iDataType == 3)
			iSampleBytes = 2;
		else if(m_iDataType == 4)
			iSampleBytes = 1;

		m_iTraceLength = iSampleBytes * m_iSampleNumber;

		QFileInfo qFI(m_listStrSEGYFile.at(0));
		m_iTraceNumber = (qFI.size() - VOLUMEHEADERLENGTH - LINEHEADERLENGTH) / (m_iTraceLength + TRACEHEADERLENGTH);
	}
}
void CXSEGYLoadParameters::SetSampleNumber(unsigned short iSampleNumber)
{
	if(m_bOverwriteSampleNumber)
	{		
		m_iSampleNumber = iSampleNumber;
		//	Caculate the trance number.
		int iSampleBytes = 4;
		if(m_iDataType == 3)
			iSampleBytes = 2;
		else if(m_iDataType == 4)
			iSampleBytes = 1;
		m_iTraceLength = iSampleBytes * m_iSampleNumber;

		QFileInfo qFI(m_listStrSEGYFile.at(0));
		m_iTraceNumber = (qFI.size() - VOLUMEHEADERLENGTH - LINEHEADERLENGTH) / (m_iTraceLength + TRACEHEADERLENGTH);
	}
}

//	Get the specified trace data of the 1st segy file, buff should allocated by caller.
bool CXSEGYLoadParameters::GetOneTraceData(qint64 iTraceIndex, float *pData)
{
	if(iTraceIndex < 1 || iTraceIndex > m_iTraceNumber)
		return false;

	QFile qFile(m_listStrSEGYFile.at(0));
	if(!qFile.open(QIODevice::ReadOnly))
		return false;
			
	char* pBuff = new char[m_iTraceLength];

	qFile.seek(VOLUMEHEADERLENGTH + LINEHEADERLENGTH + (iTraceIndex - 1) * (m_iTraceLength + TRACEHEADERLENGTH) + TRACEHEADERLENGTH);
	qFile.read(pBuff, m_iTraceLength);
	qFile.close();

	::ConvertOneTrace(pData, pBuff, m_iDataType, m_iSampleNumber, m_bDataFlip);

	delete []pBuff;

	return true;
}

void CXSEGYLoadParameters::SetInlinePosition(unsigned short iPosition)
{
	m_iInlinePos = iPosition;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();
	for(int i = 0; i < listItem.count(); i++)
	{
		if(listItem.at(i)->GetStartByte() == (iPosition - 1))
		{
			m_iInlineInd = i;
			break;
		}
	}
}

void CXSEGYLoadParameters::SetCrosslinePosition(unsigned short iPosition)
{
	m_iCrosslinePos = iPosition;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();
	for (int i = 0; i < listItem.count(); i++)
	{
		if (listItem.at(i)->GetStartByte() == (iPosition - 1))
		{
			m_iCrosslineInd = i;
			break;
		}
	}
}

void CXSEGYLoadParameters::SetOffsetPosition(unsigned short iPosition)
{
	m_iOffsetPos = iPosition;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();
	for (int i = 0; i < listItem.count(); i++)
	{
		if (listItem.at(i)->GetStartByte() == (iPosition - 1))
		{
			m_iOffsetInd = i;
			break;
		}
	}
}

void CXSEGYLoadParameters::SetAzimuthPosition(unsigned short iPosition)
{
	m_iAzimuthPos = iPosition;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();
	for (int i = 0; i < listItem.count(); i++)
	{
		if (listItem.at(i)->GetStartByte() == (iPosition - 1))
		{
			m_iAzimuthInd = i;
			break;
		}
	}
}

void CXSEGYLoadParameters::SetXPosition(unsigned short iPosition)
{
	m_iXPos = iPosition;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();
	for (int i = 0; i < listItem.count(); i++)
	{
		if (listItem.at(i)->GetStartByte() == iPosition - 1)
		{
			m_iXInd = i;
			break;
		}
	}
}

void CXSEGYLoadParameters::SetYPosition(unsigned short iPosition)
{
	m_iYPos = iPosition;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();
	for (int i = 0; i < listItem.count(); i++)
	{
		if (listItem.at(i)->GetStartByte() == iPosition - 1)
		{
			m_iYInd = i;
			break;
		}
	}
}

void CXSEGYLoadParameters::SetDXPosition(unsigned short iPosition)
{
	m_iDXPos = iPosition;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();
	for (int i = 0; i < listItem.count(); i++)
	{
		if (listItem.at(i)->GetStartByte() == iPosition - 1)
		{
			m_iDXInd = i;
			break;
		}
	}
}

void CXSEGYLoadParameters::SetDYPosition(unsigned short iPosition)
{
	m_iDYPos = iPosition;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();
	for (int i = 0; i < listItem.count(); i++)
	{
		if (listItem.at(i)->GetStartByte() == iPosition - 1)
		{
			m_iDYInd = i;
			break;
		}
	}
}

void CXSEGYLoadParameters::SetSEPosition(unsigned short iPosition)
{
	m_iSEPos = iPosition;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();
	for (int i = 0; i < listItem.count(); i++)
	{
		if (listItem.at(i)->GetStartByte() == iPosition - 1)
		{
			m_iSEInd = i;
			break;
		}
	}
}

void CXSEGYLoadParameters::SetDEPosition(unsigned short iPosition)
{
	m_iDEPos = iPosition;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();
	for (int i = 0; i < listItem.count(); i++)
	{
		if (listItem.at(i)->GetStartByte() == iPosition - 1)
		{
			m_iDEInd = i;
			break;
		}
	}
}

void CXSEGYLoadParameters::SetFBPosition(unsigned short iPosition)
{
	m_iFBPos = iPosition;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();
	for (int i = 0; i < listItem.count(); i++)
	{
		if (listItem.at(i)->GetStartByte() == iPosition - 1)
		{
			m_iFBInd = i;
			break;
		}
	}
}

qint64 CXSEGYLoadParameters::ReadAGatherTrace(QFile& qFile, unsigned int& iShotID, double& dX1, double& dY1, double& dSE, double& dX2, double& dY2, double& dDE, double& dFB)
{
	qint64 iPos = qFile.pos();

	if (qFile.read(m_pTraceHeader->GetOriginalTraceHeader(), TRACEHEADERLENGTH) != TRACEHEADERLENGTH)
		return -999;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();

	iShotID = (int)(listItem.at(m_iInlineInd)->GetValue());
	dX1 = listItem.at(m_iXInd)->GetValue() * m_dXYScale;
	dY1 = listItem.at(m_iYInd)->GetValue() * m_dXYScale;
	dX2 = listItem.at(m_iDXInd)->GetValue() * m_dXYScale;
	dY2 = listItem.at(m_iDYInd)->GetValue() * m_dXYScale;

	dSE = listItem.at(m_iSEInd)->GetValue();
	dDE = listItem.at(m_iDEInd)->GetValue();
	dFB = listItem.at(m_iFBInd)->GetValue();

	if (dFB < 0)
		dFB = -999.25;

	if (!qFile.seek(qFile.pos() + m_iTraceLength))
		return -999;

	return iPos;
}

//	Read a trace header, the file pointer moved to the begining of next trace.
bool CXSEGYLoadParameters::ReadATrace(QFile &qFile, int &iInline, int &iCrossline, float& fOffset, int& iAzimuth, double& dX, double& dY, char* pDataBuff)
{
	if(qFile.read(m_pTraceHeader->GetOriginalTraceHeader(), TRACEHEADERLENGTH) != TRACEHEADERLENGTH)
		return false;

	QList<CXSEGYTraceHeaderItem *> listItem = m_pTraceHeader->GetAllItems();

	iInline = (int)(listItem.at(m_iInlineInd)->GetValue());
	iCrossline = (int)(listItem.at(m_iCrosslineInd)->GetValue());
	fOffset = listItem.at(m_iOffsetInd)->GetValue();
	if (m_bAzimuth)
		iAzimuth = listItem.at(m_iAzimuthInd)->GetValue();
	else
		iAzimuth = 0;
	dX = listItem.at(m_iXInd)->GetValue() * m_dXYScale;
	dY = listItem.at(m_iYInd)->GetValue() * m_dXYScale;

	//	Move the file pointer to the begining of next trace.
	if(pDataBuff)
	{	
		if(qFile.read(pDataBuff, m_iTraceLength) != m_iTraceLength)
			return false;;
	}
	else
	{
		if(!qFile.seek(qFile.pos() + m_iTraceLength))
			return false;;
	}

	//	Bad trace need ignore.
	while(iInline < m_iValidStartLine || iInline > m_iValidEndLine)
	{
		if(qFile.read(m_pTraceHeader->GetOriginalTraceHeader(), TRACEHEADERLENGTH) != TRACEHEADERLENGTH)
			return false;	
		iInline = (int)(listItem.at(m_iInlineInd)->GetValue());
		iCrossline = (int)(listItem.at(m_iCrosslineInd)->GetValue());
		dX = listItem.at(m_iXInd)->GetValue() * m_dXYScale;
		dY = listItem.at(m_iYInd)->GetValue() * m_dXYScale;
		fOffset = listItem.at(m_iOffsetInd)->GetValue();
		if (m_bAzimuth)
			iAzimuth = listItem.at(m_iAzimuthInd)->GetValue();
		else
			iAzimuth = 0;

		//	Move the file pointer to the begining of next trace.
		if(pDataBuff)
		{
			if(qFile.read(pDataBuff, m_iTraceLength) != m_iTraceLength)
				return false;;
		}
		else
		{
			if(!qFile.seek(qFile.pos() + m_iTraceLength))
				return false;
		}
	}

	return true;
}
bool CXSEGYLoadParameters::ScanOffsetInfo(QFile& qFile)
{
	//	Not need for poststack data.
	if (!m_bPrestack)
		return true;

	m_iNumOffset = 0;

	int inline1, xline1, inline2, xline2, iAzim;
	float fPreOffset, fOffset;
	double x2, y2;

	//	Read the first trace.
	if (!ReadATrace(qFile, inline1, xline1, m_fStartOffset, iAzim, x2, y2))
		return false;

	fPreOffset = m_fStartOffset;
	m_iNumOffset++;

	while (ReadATrace(qFile, inline2, xline2, fOffset, iAzim, x2, y2))
	{
		//	Finish reading one CDP.
		if (inline2 != inline1 || xline2 != xline1)
			break;

		if (m_iNumOffset == 1)
			m_fOffsetInc = fOffset - fPreOffset;
		else if (m_fOffsetInc != fOffset - fPreOffset)
		{
			return false;
		}

		m_iNumOffset++;
		fPreOffset = fOffset;
	}
		
	//	Let's check the offset number briefly.
	qint64 numTrace = (qFile.size() - 3600) / (GetTraceLength() + 240);
	if (numTrace % m_iNumOffset != 0)
		return false;

	m_iMaxFold = m_iNumOffset;

	return true;
}

bool CXSEGYLoadParameters::ReadLineTrace(QFile &qFile, int &nTrace, int &iCrosslineInc, int &inline1, int &xline1, double &x1, double &y1, int &inline2, int &xline2, double &x2, double &y2)
{
	int iAzim;
	if(nTrace > 2)
	{
		//	See the file is still contain more than one line?
		while(nTrace > 1 && !skipTraces(qFile, nTrace * (m_iTraceLength + 240)))
			nTrace--;
	}
	
	if(nTrace < 1)
		return false;

	float fOffset;

	//	Read the 2nd trace.  (The 1st one already be read before calling this function.)
	if (!ReadATrace(qFile, inline2, xline2, fOffset, iAzim, x2, y2))
		return false;

	if(inline1 != inline2)
	{
		while(inline1 != inline2)
		{
			//	Backwards 2 traces and read again.
			if(!skipTraces(qFile, (-2) * (m_iTraceLength + 240)))
				return false;

			if (!ReadATrace(qFile, inline2, xline2, fOffset, iAzim, x2, y2))
				return false;

			nTrace--;
			if(nTrace < 0)
				return false;
		}
	
		ReadATrace(qFile, inline1, xline1, fOffset, iAzim, x1, y1);
		nTrace++;
	}
	else
	{
		if(iCrosslineInc > 1)
		{
			int inc = qAbs(xline2 - xline1);
			if(inc > 0 && iCrosslineInc > inc)
				iCrosslineInc = inc;
		}

		while(1)
		{
			//	Try to find out how many traces per line.
			if (!ReadATrace(qFile, inline1, xline1, fOffset, iAzim, x1, y1))
				return false;

			int inc = qAbs(xline2 - xline1);
			if(inc > 0 && iCrosslineInc > inc)
				iCrosslineInc = inc;

			nTrace++;

			if(inline1 == inline2)
			{
				xline2 = xline1;
				x2 = x1;
				y2 = y1;
			}
			else
				break;
		}

		//	nTrace should be the trace number per line minus 1.
		nTrace--;

		//	Right now inline2, xline2, x2, y2 is the last trace of 1st line.
		//	and inline1, xline1, x1, y1 is the 1st trace of the 2nd line.

	}

	return true;
}

bool CXSEGYLoadParameters::skipTraces(QFile &qFile, qint64 pos)
{
	//	Beyond the end of the file.
	if(qFile.pos() + pos >= qFile.size())
		return false;

	return qFile.seek(qFile.pos() + pos);
}

unsigned int CXSEGYLoadParameters::GetImportSampleNumber()
{
	return static_cast<int>(qAbs(m_fEndImportTime - m_fStartImportTime) / m_fImportSampleInterval + 0.01) + 1;
}

qint64 CXSEGYLoadParameters::GetRequiredSpaceValue()
{
	//	Calculate ZXY file size.
	qint64 numLine = m_pUTMTool->GetNI();
	qint64 numCDP = m_pUTMTool->GetNJ();
	qint64 numSample = qAbs(m_fEndImportTime - m_fStartImportTime) / m_fImportSampleInterval + 1;

	qint64 iSampleBytes = 4;
	if(m_iDataType == 3)
		iSampleBytes = 2;
	else if(m_iDataType == 4)
		iSampleBytes = 1;

	//	DV size as byte.
	qint64 nDVSize = numLine * numCDP * numSample * iSampleBytes;

	//	Slice file?
	if(m_bCreateSliceFile)
		nDVSize *= 2;

	//	Brick file
	if(m_bCreateBrickFile)
	{
		//qint64 nLDMSize = CXSystemInfo::GetLDMFileSize(numLine, numCDP, numSample, iSampleBytes);
		//nDVSize += nLDMSize;
	}
	return nDVSize;
}

//	How much space required (unit is GB).
QString CXSEGYLoadParameters::GetRequiredSpaceString()
{
	return QString("");

	//	Calculate ZXY file size.
	//qint64 numLine = m_pUTMTool->GetNI();
	//qint64 numCDP = m_pUTMTool->GetNJ();
	//qint64 numSample = qAbs(m_fEndImportTime - m_fStartImportTime) / m_fImportSampleInterval + 1;

	//qint64 iSampleBytes = 4;
	//if(m_iDataType == 3)
	//	iSampleBytes = 2;
	//else if(m_iDataType == 4)
	//	iSampleBytes = 1;

	////	DV size as byte.
	//qint64 nDVSize = numLine * numCDP * numSample * iSampleBytes;

	////	Slice file?
	//if(m_bCreateSliceFile)
	//	nDVSize *= 2;

	////	Brick file
	//if(m_bCreateBrickFile)
	//{
	//	qint64 nLDMSize = CXSystemInfo::GetLDMFileSize(numLine, numCDP, numSample, iSampleBytes);
	//	nDVSize += nLDMSize;
	//}

	//return CXSystemInfo::GetSpaceSizeString(nDVSize);
}

CXSeismicDataVolume* CXSEGYLoadParameters::GetDataVolume()
{
	if(!m_pDV)
	{
		float fZRatio = 1.;
		//if(m_eDomainType == DEPTH)
		//{
		//	fZRatio = ::GetUnitConvertRatio(m_iZUnit, ::GetUnit(::GetProjectUnitNameZ())) * (-1);

		//	//	feet against meet may cause the sample interval changed.
		//	if(m_iZUnit == eFoot && ::GetUnit(::GetProjectUnitNameZ()) != eFoot)
		//	{
		//		m_fImportSampleInterval *= ::GetUnitConvertRatio(eFoot, eMeter);
		//		m_fSampleInterval *= ::GetUnitConvertRatio(eFoot, eMeter);
		//	}
		//	else if(::GetUnit(::GetProjectUnitNameZ()) == eFoot && m_iZUnit != eFoot)
		//	{
		//		m_fImportSampleInterval *= ::GetUnitConvertRatio(eMeter, eFoot);
		//		m_fSampleInterval *= ::GetUnitConvertRatio(eMeter, eFoot);
		//	}
		//}
		//else
		//{
		//	fZRatio = ::GetUnitConvertRatio(m_iZUnit, ::GetUnit(::GetProjectUnitNameSeisTime()));
		//	m_fImportSampleInterval *= qAbs(fZRatio);
		//	m_fSampleInterval *= qAbs(fZRatio);
		//}

		m_fStartImportTime *= fZRatio;
		m_fEndImportTime *= fZRatio;
		m_fStartTime *= fZRatio;

		m_pDV = new CXSeismicDataVolume(*m_pUTMTool, m_fStartImportTime, m_fEndImportTime, m_fImportSampleInterval, m_strDVName, m_iMaxFold, m_fStartOffset, m_fOffsetInc, m_bAzimuth);  
		//m_pDV->SetTemplateID(m_seismicTemplate); 
		//m_pDV->SetDomainType(m_eDomainType);
		//m_pDV->SetOriFileName(m_listStrSEGYFile.at(0));

		//m_pDV->SetObjectFlag(true, GM_ObjectDataModified);
	}

	return m_pDV;
}

//	Correct the DV time range after importing.
void CXSEGYLoadParameters::CorrectTimeRange()
{
	//if(!m_pDV)
	//	return;

	////	Process datum.
	//m_pDV->SetDatum(m_fImportDatum);

	//// get datum replacment TWT
	////float fTimeShift = CRLTDCommand::GetSeismicDataShift_SCD( GetProject()->GetDatum(),m_fImportDatum );
	//	
	////	If user specified a start time?
	if(m_fTimeShiftTo != -999.)
	{
		//	User specified the start time.  Ignore datum difference then.
		m_pDV->ShiftStartSamplingTo(m_fTimeShiftTo);
	}
}

//	Convert one trace data from original SEGY format to float*
void CXSEGYLoadParameters::ConvertTraceData(char *pOriData, float *pDstData)
{
	char c;
	int i, count = 0;
	unsigned int iSOffset = (m_fStartImportTime - m_fStartTime) / m_fSampleInterval;
	unsigned int iStep = m_fImportSampleInterval/m_fSampleInterval;
	unsigned int iImportSampleNumber = GetImportSampleNumber();

	if(m_iDataType == 0)
	{
		//	Original data is IEEE float.
		for(i = iSOffset; i < m_iSampleNumber && count < iImportSampleNumber; i += iStep, count++)
		{
			if(m_bDataFlip)
			{
				c = pOriData[4*i];
				pOriData[4*i] = pOriData[4*i+3];
				pOriData[4*i+3] = c;
				c = pOriData[4*i + 1];
				pOriData[4*i + 1] = pOriData[4*i+2];
				pOriData[4*i+2] = c;
			}
				
			pDstData[count] = *((float *)(pOriData + 4*i));
			if (std::isnan(pDstData[count]))
			{
				pDstData[count] = g_dInvalidData;
			}
		}
	}
	else if (m_iDataType == 1)
	{
		//	Original data is IBM float.
		float *pFBuff = new float[iImportSampleNumber];
		for (i = iSOffset; i < m_iSampleNumber && count < iImportSampleNumber; i += iStep, count++)
		{
			c = pOriData[4 * i];
			pOriData[4 * i] = pOriData[4 * i + 3];
			pOriData[4 * i + 3] = c;
			c = pOriData[4 * i + 1];
			pOriData[4 * i + 1] = pOriData[4 * i + 2];
			pOriData[4 * i + 2] = c;

			pFBuff[count] = *((float *)(pOriData + 4 * i));
		}

		IBMToIEEE((int *)pFBuff, (int *)pDstData, GetImportSampleNumber());
		delete[]pFBuff;

		for (i = 0; i < count; i++)
		{
			if (std::isnan(pDstData[i]))
			{
				pDstData[i] = g_dInvalidData;
			}
		}
	}
	else if(m_iDataType == 2)
	{
		//	Original data is 32-bit integer.
		for(i = iSOffset; i < m_iSampleNumber && count < iImportSampleNumber; i += iStep, count++)
		{
			if(m_bDataFlip)
			{
				c = pOriData[4*i];
				pOriData[4*i] = pOriData[4*i+3];
				pOriData[4*i+3] = c;
				c = pOriData[4*i + 1];
				pOriData[4*i + 1] = pOriData[4*i+2];
				pOriData[4*i+2] = c;
			}
				
			pDstData[count] = (float)(*((int *)(pOriData + 4*i)));
			if (std::isnan(pDstData[count]))
			{
				pDstData[count] = g_dInvalidData;
			}
		}
	}
	else if(m_iDataType == 3)
	{
		//	Original data is 16-bit integer.
		for(i = iSOffset; i < m_iSampleNumber && count < iImportSampleNumber; i += iStep, count++)
		{
			if(m_bDataFlip)
			{
				c = pOriData[2*i];
				pOriData[2*i] = pOriData[2*i+1];
				pOriData[2*i+1] = c;
			}
				
			pDstData[count] = (float)(*((short *)(pOriData + 2*i)));
			if (std::isnan(pDstData[count]))
			{
				pDstData[count] = g_dInvalidData;
			}
		}
	}
	else if(m_iDataType == 4)
	{
		//	Original data is 8-bit integer.
		for(i = iSOffset; i < m_iSampleNumber && count < iImportSampleNumber; i += iStep, count++)
		{				
			pDstData[count] = (float)(*((char *)(pOriData + i)));
			if (std::isnan(pDstData[count]))
			{
				pDstData[count] = g_dInvalidData;
			}
		}
	}
}

//	Read 4 traces to guess which byte is inline/crossline/X/Y.
void CXSEGYLoadParameters::guessTraceHeaderPosition()
{
	//	variables to store the possible value of inline/crossline/X/Y for 4 traces.
	int i,x1[3],x5[3],x9[3],x13[3],x17[3],x21[3],x25[3],x73[3],x77[3],x81[3],x85[3],x181[3],x185[3];
	int x1Last,x5Last,x9Last,x13Last,x17Last,x21Last,x25Last,x181Last,x185Last;

	//	Read first 3 traces.
	for(i = 0; i < 3; i++)
	{
		GetOneTraceHeader(i+1);
		x1[i]	= (int)(m_pTraceHeader->GetValueAt(0));		//	byte 1.
		x5[i]	= (int)(m_pTraceHeader->GetValueAt(1));		//	byte 5.
		x9[i]	= (int)(m_pTraceHeader->GetValueAt(2));		//	byte 9.
		x13[i]	= (int)(m_pTraceHeader->GetValueAt(3));		//	byte 13.
		x17[i]	= (int)(m_pTraceHeader->GetValueAt(4));		//	byte 17.
		x21[i]	= (int)(m_pTraceHeader->GetValueAt(5));		//	byte 21.
		x25[i]	= (int)(m_pTraceHeader->GetValueAt(6));		//	byte 25.
		x73[i]	= (int)(m_pTraceHeader->GetValueAt(21));	//	byte 73.
		x77[i]	= (int)(m_pTraceHeader->GetValueAt(22));	//	byte 77.
		x81[i]	= (int)(m_pTraceHeader->GetValueAt(23));	//	byte 81.
		x85[i]	= (int)(m_pTraceHeader->GetValueAt(24));	//	byte 85.
		x181[i]	= (int)(m_pTraceHeader->GetValueAt(71));	//	byte 181.
		x185[i]	= (int)(m_pTraceHeader->GetValueAt(72));	//	byte 185.
	}

	//	Read the last trace.
	GetOneTraceHeader(m_iTraceNumber);
	x1Last	= (int)(m_pTraceHeader->GetValueAt(0));		//	byte 1.
	x5Last	= (int)(m_pTraceHeader->GetValueAt(1));		//	byte 5.
	x9Last	= (int)(m_pTraceHeader->GetValueAt(2));		//	byte 9.
	x13Last	= (int)(m_pTraceHeader->GetValueAt(3));		//	byte 13.
	x17Last	= (int)(m_pTraceHeader->GetValueAt(4));		//	byte 17.
	x21Last	= (int)(m_pTraceHeader->GetValueAt(5));		//	byte 21.
	x25Last	= (int)(m_pTraceHeader->GetValueAt(6));		//	byte 25.
	x181Last	= (int)(m_pTraceHeader->GetValueAt(71));	//	byte 181.
	x185Last	= (int)(m_pTraceHeader->GetValueAt(72));	//	byte 185.

	//	Guess x, y now.
	if(x73[0]>=0 && x77[0]>=0 && (x73[0] != x73[1] || x77[0] != x77[1]))
	{
		m_iXPos = 73;
		m_iYPos = 77;
		m_iXInd = 21;
		m_iYInd = 22;

		if(x73[0] > 1.1e10)
		{
			m_pTraceHeader->GetItemAt(m_iXInd)->SetToFloat(true);
			m_pTraceHeader->GetItemAt(m_iYInd)->SetToFloat(true);

			if(x73[0] < 1.2e10)
			{
				m_pTraceHeader->SetIEEEFloat(false);
			}
		}
	}
	else if(x81[0]>=0 && x85[0]>=0 && (x81[0] != x81[1] || x85[0] != x85[1]))
	{
		m_iXPos = 81;
		m_iYPos = 85;
		m_iXInd = 23;
		m_iYInd = 24;

		if(x81[0] > 1.1e9)
		{
			m_pTraceHeader->GetItemAt(m_iXInd)->SetToFloat(true);
			m_pTraceHeader->GetItemAt(m_iYInd)->SetToFloat(true);

			if(x81[0] < 1.2e9)
			{
				m_pTraceHeader->SetIEEEFloat(false);
			}
		}
	}

	// Guess inline/xline.
	if(x13[0]>0 && (x13[2]-x13[1])>0 && (x13[2]-x13[1]) == (x13[1]-x13[0]))
	{
		m_iCrosslinePos = 13;
		m_iCrosslineInd = 3;

		if(x9[0]>0 && x9[0] == x9[1] && x9[0] != x9Last)
		{
			m_iInlinePos = 9;
			m_iInlineInd = 2;
			return;
		}
		if(x17[0]>0 && x17[0] == x17[1] && x17[1] != x17Last)
		{
			m_iInlinePos = 17;
			m_iInlineInd = 4;
			return;
		}
		if(x21[0]>0 && x21[0] == x21[1] && x21[1] != x21Last)
		{
			m_iInlinePos = 21;
			m_iInlineInd = 5;
			return;
		}
		if(x1[0]>0 && x1[0] == x1[1] && x1[1] != x1Last)
		{
			m_iInlinePos = 1;
			m_iInlineInd = 0;
			return;
		}
		if(x5[0]>0 && x5[0] == x5[1] && x5[1] != x5Last)
		{
			m_iInlinePos = 5;
			m_iInlineInd = 1;
			return;
		}
		if(x25[0]>0 && x25[0] == x25[1] && x25[1] != x25Last)
		{
			m_iInlinePos = 25;
			m_iInlineInd = 6;
			return;
		}
	}

	if(x21[0]>0 && (x21[2]-x21[1])>0 && (x21[2]-x21[1]) == (x21[1]-x21[0]))
	{
		m_iCrosslinePos = 21;
		m_iCrosslineInd = 5;
		if(x17[0]>0 && x17[0] == x17[1] && x17[1] != x17Last)
		{
			m_iInlinePos = 17;
			m_iInlineInd = 4;
			return;
		}
		if(x9[0]>0 && x9[0] == x9[1] && x9[0] != x9Last)
		{
			m_iInlinePos = 9;
			m_iInlineInd = 2;
			return;
		}
		if(x13[0]>0 && x13[0] == x13[1] && x13[1] != x13Last)
		{
			m_iInlinePos = 13;
			m_iInlineInd = 3;
			return;
		}
		if(x1[0]>0 && x1[0] == x1[1] && x1[1] != x1Last)
		{
			m_iInlinePos = 1;
			m_iInlineInd = 0;
			return;
		}
		if(x5[0]>0 && x5[0] == x5[1] && x5[1] != x5Last)
		{
			m_iInlinePos = 5;
			m_iInlineInd = 1;
			return;
		}
		if(x25[0]>0 && x25[0] == x25[1] && x25[1] != x25Last)
		{
			m_iInlinePos = 25;
			m_iInlineInd = 6;
			return;
		}
	}

	if(x17[0]>0 && (x17[2]-x17[1])>0 && (x17[2]-x17[1]) == (x17[1]-x17[0]))
	{
		m_iCrosslinePos = 17;
		m_iCrosslineInd = 4;
		if(x21[0]>0 && x21[0] == x21[1] && x21[1] != x21Last)
		{
			m_iInlinePos = 21;
			m_iInlineInd = 5;
			return;
		}
		if(x9[0]>0 && x9[0] == x9[1] && x9[0] != x9Last)
		{
			m_iInlinePos = 9;
			m_iInlineInd = 2;
			return;
		}
		if(x13[0]>0 && x13[0] == x13[1] && x13[1] != x13Last)
		{
			m_iInlinePos = 13;
			m_iInlineInd = 3;
			return;
		}
		if(x1[0]>0 && x1[0] == x1[1] && x1[1] != x1Last)
		{
			m_iInlinePos = 1;
			m_iInlineInd = 0;
			return;
		}
		if(x5[0]>0 && x5[0] == x5[1] && x5[1] != x5Last)
		{
			m_iInlinePos = 5;
			m_iInlineInd = 1;
			return;
		}
		if(x25[0]>0 && x25[0] == x25[1] && x25[1] != x25Last)
		{
			m_iInlinePos = 25;
			m_iInlineInd = 6;
			return;
		}
	}

	if(x9[0]>0 && (x9[2]-x9[1])>0 && (x9[2]-x9[1]) == (x9[1]-x9[0]))
	{
		m_iCrosslinePos = 9;
		m_iCrosslineInd = 2;
		if(x13[0]>0 && x13[0] == x13[1] && x13[1] != x13Last)
		{
			m_iInlinePos = 13;
			m_iInlineInd = 3;
			return;
		}
		if(x17[0]>0 && x17[0] == x17[1] && x17[1] != x17Last)
		{
			m_iInlinePos = 17;
			m_iInlineInd = 4;
			return;
		}
		if(x21[0]>0 && x21[0] == x21[1] && x21[1] != x21Last)
		{
			m_iInlinePos = 21;
			m_iInlineInd = 5;
			return;
		}
		if(x1[0]>0 && x1[0] == x1[1] && x1[1] != x1Last)
		{
			m_iInlinePos = 1;
			m_iInlineInd = 0;
			return;
		}
		if(x5[0]>0 && x5[0] == x5[1] && x5[1] != x5Last)
		{
			m_iInlinePos = 5;
			m_iInlineInd = 1;
			return;
		}
		if(x25[0]>0 && x25[0] == x25[1] && x25[1] != x25Last)
		{
			m_iInlinePos = 25;
			m_iInlineInd = 6;
			return;
		}
	}

	if(x5[0]>0 && (x5[2]-x5[1])>0 && (x5[2]-x5[1]) == (x5[1]-x5[0]))
	{
		m_iCrosslinePos = 5;
		m_iCrosslineInd = 1;
		if(x1[0]>0 && x1[0] == x1[1] && x1[1] != x1Last)
		{
			m_iInlinePos = 1;
			m_iInlineInd = 0;
			return;
		}
		if(x9[0]>0 && x9[0] == x9[1] && x9[0] != x9Last)
		{
			m_iInlinePos = 9;
			m_iInlineInd = 2;
			return;
		}
		if(x17[0]>0 && x17[0] == x17[1] && x17[1] != x17Last)
		{
			m_iInlinePos = 17;
			m_iInlineInd = 4;
			return;
		}
		if(x21[0]>0 && x21[0] == x21[1] && x21[1] != x21Last)
		{
			m_iInlinePos = 21;
			m_iInlineInd = 5;
			return;
		}
		if(x13[0]>0 && x13[0] == x13[1] && x13[1] != x13Last)
		{
			m_iInlinePos = 13;
			m_iInlineInd = 3;
			return;
		}
		if(x25[0]>0 && x25[0] == x25[1] && x25[1] != x25Last)
		{
			m_iInlinePos = 25;
			m_iInlineInd = 6;
			return;
		}
	}

	if(x1[0]>0 && (x1[2]-x1[1])>0 && (x1[2]-x1[1]) == (x1[1]-x1[0]))
	{
		m_iCrosslinePos = 1;
		m_iCrosslineInd = 0;
		if(x5[0]>0 && x5[0] == x5[1] && x5[1] != x5Last)
		{
			m_iInlinePos = 5;
			m_iInlineInd = 1;
			return;
		}
		if(x9[0]>0 && x9[0] == x9[1] && x9[0] != x9Last)
		{
			m_iInlinePos = 9;
			m_iInlineInd = 2;
			return;
		}
		if(x17[0]>0 && x17[0] == x17[1] && x17[1] != x17Last)
		{
			m_iInlinePos = 17;
			m_iInlineInd = 4;
			return;
		}
		if(x21[0]>0 && x21[0] == x21[1] && x21[1] != x21Last)
		{
			m_iInlinePos = 21;
			m_iInlineInd = 5;
			return;
		}
		if(x13[0]>0 && x13[0] == x13[1] && x13[1] != x13Last)
		{
			m_iInlinePos = 13;
			m_iInlineInd = 3;
			return;
		}
		if(x25[0]>0 && x25[0] == x25[1] && x25[1] != x25Last)
		{
			m_iInlinePos = 25;
			m_iInlineInd = 6;
			return;
		}
	}

	if(x25[0]>0 && (x25[2]-x25[1])>0 && (x25[2]-x25[1]) == (x25[1]-x25[0]))
	{
		m_iCrosslinePos = 25;
		m_iCrosslineInd = 6;
		if(x21[0]>0 && x21[0] == x21[1] && x21[1] != x21Last)
		{
			m_iInlinePos = 21;
			m_iInlineInd = 5;
			return;
		}
		if(x5[0]>0 && x5[0] == x5[1] && x5[1] != x5Last)
		{
			m_iInlinePos = 5;
			m_iInlineInd = 1;
			return;
		}
		if(x9[0]>0 && x9[0] == x9[1] && x9[0] != x9Last)
		{
			m_iInlinePos = 9;
			m_iInlineInd = 2;
			return;
		}
		if(x17[0]>0 && x17[0] == x17[1] && x17[1] != x17Last)
		{
			m_iInlinePos = 17;
			m_iInlineInd = 4;
			return;
		}
		if(x13[0]>0 && x13[0] == x13[1] && x13[1] != x13Last)
		{
			m_iInlinePos = 13;
			m_iInlineInd = 3;
			return;
		}
		if(x1[0]>0 && x1[0] == x1[1] && x1[1] != x1Last)
		{
			m_iInlinePos = 1;
			m_iInlineInd = 0;
			return;
		}
	}

	if(x181[0]>0 && (x181[2]-x181[1])>0 && (x181[2]-x181[1]) == (x181[1]-x181[0]))
	{
		m_iCrosslinePos = 181;
		m_iCrosslineInd = 71;
		if(x185[0]>0 && x185[0] == x185[1] && x185[0] != x185Last)
		{
			m_iInlinePos = 185;
			m_iInlineInd = 72;
			return;
		}
	}

	if(x185[0]>0 && (x185[2]-x185[1])>0 && (x185[2]-x185[1]) == (x185[1]-x185[0]))
	{
		m_iCrosslinePos = 185;
		m_iCrosslineInd = 72;
		if(x181[0]>0 && x181[0] == x181[1] && x181[0] != x181Last)
		{
			m_iInlinePos = 181;
			m_iInlineInd = 71;
			return;
		}
	}
}

void CXSEGYLoadParameters::AutoParseParameters()
{
	//	Try to open the 1st file to read volume header.
	if(m_listStrSEGYFile.count() > 0)
	{
		QFileInfo fi(m_listStrSEGYFile.at(0));
		m_strDVName = fi.baseName();

		QFile qFile(m_listStrSEGYFile.at(0));
		if(qFile.open(QIODevice::ReadOnly))
		{
			//	Read the 3200 bytes volume header and transfer it to ASCII.
			qFile.read(m_pVolumeHeader, VOLUMEHEADERLENGTH);
			EBCDIC_ASCII(m_pVolumeHeader, VOLUMEHEADERLENGTH);

			//	Read the 400 bytes line header.
			qFile.read(m_pLineHeader->GetLineHeaderBuff(), LINEHEADERLENGTH);
			m_pLineHeader->Initialize();

			//	Defaultly whether flip trace header and th edata
			//	is the same of whether flip line header.
			m_pTraceHeader->SetNeedFlip(m_pLineHeader->GetNeedFlip());
			m_bDataFlip = m_pLineHeader->GetNeedFlip();

			m_iDataType = m_pLineHeader->GetDataType();
			m_iSampleNumber = m_pLineHeader->GetSampleNumber();
			m_fSampleInterval = m_pLineHeader->GetSampleInterval();
			m_fImportSampleInterval = m_fSampleInterval;
			m_iUnit = m_pLineHeader->GetUnit();

			qFile.close();

			//	Caculate the trance number.
			int iSampleBytes = 4;
			if(m_iDataType == 3)
				iSampleBytes = 2;
			else if(m_iDataType == 4)
				iSampleBytes = 1;

			m_iTraceLength = iSampleBytes * m_iSampleNumber;
			m_iTraceNumber = (qFile.size() - VOLUMEHEADERLENGTH - LINEHEADERLENGTH) / (m_iTraceLength + TRACEHEADERLENGTH);

			//	Get the scale factor from the 1st trace header.
			GetOneTraceHeader(1);
			m_dXYScale = m_pTraceHeader->GetScaleFactor();
			m_fStartTime = m_pTraceHeader->GetValueAt(35);
			if (m_fStartTime == 0)
				m_fStartTime = m_pTraceHeader->GetValueAt(33);
			m_fStartImportTime = m_fStartTime;
			m_fEndImportTime = m_fStartTime + (m_iSampleNumber - 1) * m_fSampleInterval;

			//	Guess the inline/crossline/x/y position.
			guessTraceHeaderPosition();
		}
	}
}

void CXSEGYLoadParameters::RefreshParameters()
{
	m_iDataType = m_pLineHeader->GetDataType();
	m_iSampleNumber = m_pLineHeader->GetSampleNumber();
	m_fSampleInterval = m_pLineHeader->GetSampleInterval();
	m_iUnit = m_pLineHeader->GetUnit();
}

void CXSEGYLoadParameters::FreeTraceInfo()
{
	QHashIterator<QPair<unsigned short, unsigned short>, SKETraceOffsets *> it(m_hashTraceInfo);
	while (it.hasNext())
	{
		it.next();
		SKETraceOffsets *pTInfo = it.value();
		delete pTInfo;
	}

	m_hashTraceInfo.clear();
}

CXPreStackGather* CXSEGYLoadParameters::GetPrestackGather()
{
	if (!m_pGather)
		m_pGather = new CXPreStackGather;

	return m_pGather;
}