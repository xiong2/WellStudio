#include <QMessageBox>
#include <QFile>
#include <qfileinfo.h>

#include "xtraceheaderscanthread.h"
#include "xsegyloadparameters.h"
#include "xseismicutmtool.h"
#include "xprestackgather.h"
#include "xproject.h"
#include "xglobal.h"
#include "xunit.h"

CXTraceHeaderScanThread::CXTraceHeaderScanThread(CXSEGYLoadParameters* pLoadParameters, bool bIrregular, bool bAzimuth)
{
	m_pLoadParameters = pLoadParameters;
	m_iErrorCode = 0;
	m_bIrregularPrestack = bIrregular;
	m_bAzimuth = bAzimuth;
}

void CXTraceHeaderScanThread::RunThread()
{
	emit signalStartComputing();

	if (!m_pLoadParameters)
	{
		m_iErrorCode = 1;
		return;
	}

	int i, j;
	QStringList listFile = m_pLoadParameters->GetAllSEGYFiles();

	//	Before scanning, clean the UTM since it may not the 1st time scanning.
	m_pLoadParameters->ResetUTMTool();

	//	A loop to scan each SEGY File.
	if (m_pLoadParameters->IsPrestackGather())
	{
		//	Prestack gather.
		for (i = 0; i < listFile.count(); i++)
		{
			if (!scanOneGatherFile(listFile.at(i), i))
				break;
		}

		if (i < listFile.count())
		{
			//	Thread failed.
			this->SetStopFlag();
		}
	}
	else if (m_bIrregularPrestack)
	{
		m_iMaxFold = 0;
		m_pLoadParameters->SetStartOffset(99999.);
		m_pLoadParameters->SetEndOffset(-99999.);
		m_pLoadParameters->SetMinAzim(370);
		m_pLoadParameters->SetMaxAzim(-370);

		m_pLoadParameters->FreeTraceInfo();
		QHash<QPair<unsigned short, unsigned short>, SKETraceOffsets *>& hashTraceInfo = m_pLoadParameters->GetTraceInfo();		

		for(i = 0; i < listFile.count(); i++)
		{
			if (!scanOneIrreFile(listFile.at(i), i))
				break;
		}

		m_pLoadParameters->SetMaxFold(m_iMaxFold);

		if (i < listFile.count())
		{
			//	Thread failed.
			this->SetStopFlag();
			m_pLoadParameters->FreeTraceInfo();
		}
	}
	else
	{
		for (i = 0; i < listFile.count(); i++)
		{
			if (!scanOneFile(listFile.at(i), i))
				break;
		}

		if(i < listFile.count())
		{
			//	Thread failed.
			this->SetStopFlag();
		}
	}
}

bool CXTraceHeaderScanThread::scanOneGatherFile(QString strSEGYFile, int iFileNo)
{
	QFile qFile(strSEGYFile);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		m_iErrorCode = 2;
		return false;
	}

	CXPreStackGather *pGather = m_pLoadParameters->GetPrestackGather();
	if (pGather->GetObjectName().isEmpty())
	{
		QFileInfo qFI(strSEGYFile);
		pGather->SetObjectName(qFI.baseName());
	}

	int iFileID = pGather->AddOneSEGYFile(strSEGYFile);
	pGather->PopulateSEGYInfo(m_pLoadParameters->GetStartTime(), m_pLoadParameters->GetSampleInterval(), m_pLoadParameters->GetSampleNumber(), m_pLoadParameters->GetDataType(), m_pLoadParameters->DataNeedFlip());

	unsigned int count = 0, iShotID;
	double x1, y1, x2, y2, dSE, dDE, dFB;
	qint64 numTrace = (qFile.size() - 3600) / (m_pLoadParameters->GetTraceLength() + 240);

	//	Skip the volume header and line header.
	qFile.seek(3600);
	while (count < numTrace)
	{
		qint64 iPos = m_pLoadParameters->ReadAGatherTrace(qFile, iShotID, x1, y1, dSE, x2, y2, dDE, dFB);
		if(iPos == -999)
			break;

		count++;

		//	Now can refresh the progress bar.
		if (IsStopped())
		{
			m_iErrorCode = 0;
			return false;
		}
		else
			emit signalUpdateProgress(count, numTrace);

		QList<qreal>* listPoints = pGather->GetOneShotPoints(iShotID, true);
		if (listPoints->isEmpty())
		{
			listPoints->append((qreal)iFileID);
			listPoints->append((qreal)iPos);
			listPoints->append(x1);
			listPoints->append(y1);
			listPoints->append(dSE);
		}
		else
		{
			listPoints->append(x2);
			listPoints->append(y2);
			listPoints->append(dDE);
			listPoints->append(dFB);
		}			
	}

	qFile.close();
	return true;
}

bool CXTraceHeaderScanThread::scanOneFile(QString strSEGYFile, int iFileNo)
{
	QFile qFile(strSEGYFile);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		m_iErrorCode = 2;
		return false;
	}
	
	unsigned int count = 0;
	int inline1, xline1, inline2, xline2, nTrace, iAzim;
	int iInlineInc = 999, iCrosslineInc = 999;
	int inlineMin, crosslineMin, inlineMax = 0, crosslineMax = 0;
	float fOffset;
	double x1, y1, x2, y2;

	int iLine[3], iCDP[3];
	double dX[3], dY[3];

	//	Skip the volume header and line header.
	qFile.seek(3600);

	if (!m_pLoadParameters->ScanOffsetInfo(qFile))
	{
		m_iErrorCode = 3;
		return false;
	}
	qFile.seek(3600);

	//	Read the 1st trace.
	m_pLoadParameters->ReadATrace(qFile, inline1, xline1, fOffset, iAzim, x1, y1);
	count++;

	inlineMin = inlineMax = inline1;
	crosslineMin = crosslineMax = xline1;
	iLine[0] = inline1;
	iCDP[0] = xline1;
	dX[0] = x1;
	dY[0] = y1;

	nTrace = 1;
	qint64 numTrace = (qFile.size() - 3600) / (m_pLoadParameters->GetTraceLength() + 240);

	while(count < numTrace)
	{
		if(!m_pLoadParameters->ReadLineTrace(qFile, nTrace, iCrosslineInc, inline1, xline1, x1, y1, inline2, xline2, x2, y2))
			break;

		count += nTrace;

		//	Now can refresh the progress bar.
		if (IsStopped())
		{
			m_iErrorCode = 0;
			return false;
		}
		else
			emit signalUpdateProgress(count,numTrace);

		if(inline1 < inlineMin)
			inlineMin = inline1;
		if(inline1 > inlineMax)
			inlineMax = inline1;
		if(inline2 < inlineMin)
			inlineMin = inline2;
		if(inline2 > inlineMax)
			inlineMax = inline2;

		if(xline1 < crosslineMin)
			crosslineMin = xline1;
		if(xline1 > crosslineMax)
			crosslineMax = xline1;
		if (xline2 < crosslineMin)
		{
			crosslineMin = xline2;
			iLine[1] = inline2;
			iCDP[1] = xline2;
			dX[1] = x2;
			dY[1] = y2;
		}
		if (xline2 > crosslineMax)
		{
			crosslineMax = xline2;
			iLine[1]= inline2;
			iCDP[1]	= xline2;
			dX[1]	= x2;
			dY[1]	= y2;
		}

		if(qAbs(inline2 - inline1) > 0 && qAbs(inline2 -inline1) < iInlineInc)
			iInlineInc = qAbs(inline2 - inline1);
	}

	if(inline2 != 0)
	{
		iLine[2]	 = inline2;
		iCDP[2]		= xline2;
		dX[2]		= x2;
		dY[2]		= y2;
	}
	else
	{
		iLine[2]	 = inline1;
		iCDP[2]		= xline1;
		dX[2]		= x1;
		dY[2]		= y1;
	}

	qFile.close();

	if (iLine[1] == 0)
	{
		//	This means only one line.
		iLine[1] = iLine[2];
		iCDP[1] = iCDP[2];
		dX[1] = dX[2];
		dY[1] = dY[2];
		crosslineMax = iCDP[2];
		iInlineInc = 1;
	}

	//	Here let's consider the unit of X,Y.
	unsigned short iUnit = m_pLoadParameters->GetUnit();
	double scale = 1.;
	if(::GetProject()->UsingMetricUnit() && iUnit == 2)
	{
		//	Convert from ft to m.
		scale = CXUnit::GetConvertRatio("ft", "m");
	}
	else if(!::GetProject()->UsingMetricUnit() && iUnit == 1)
	{
		//	Convert from m to ft.
		scale = CXUnit::GetConvertRatio("m", "ft");
	}

	//	Populate the UTM right now.
	int numInline = (inlineMax - inlineMin) / iInlineInc + 1;
	int numCrossline = (crosslineMax - crosslineMin) / iCrosslineInc + 1;
	CXSeismicUTMTool *pUTM = m_pLoadParameters->GetUTMTool();
	if(pUTM->GetNI() == 0)
	{
		//	The 1st file, initialize the UTM.
		pUTM->InitSize(inlineMin, numInline, iInlineInc, crosslineMin, numCrossline, iCrosslineInc);
		pUTM->InitCoordinates(iLine[0], iCDP[0], dX[0] * scale, dY[0] * scale,
			iLine[1], iCDP[1], dX[1] * scale, dY[1] * scale, 
			iLine[2], iCDP[2], dX[2] * scale, dY[2] * scale);
	}
	else
	{
		//	Not the 1st file, create a new UTM first.
		CXSeismicUTMTool *pNewUTM = new CXSeismicUTMTool;
		pNewUTM->InitSize(inlineMin, numInline, iInlineInc, crosslineMin, numCrossline, iCrosslineInc);
		pNewUTM->InitCoordinates(iLine[0], iCDP[0], dX[0] * scale, dY[0] * scale,
			iLine[1], iCDP[1], dX[1] * scale, dY[1] * scale, 
			iLine[2], iCDP[2], dX[2] * scale, dY[2] * scale);

		//	Compatible with the exist one?
		if(!pUTM->IsCompatible(pNewUTM))
		{
			delete pNewUTM;
			m_iErrorCode = 4;
			return false;
		}

		//	Merge them.
		pUTM->MergeUTM(*pNewUTM);
	}

	return true;
}

bool CXTraceHeaderScanThread::scanOneIrreFile(QString strSEGYFile, int iFileNo)
{
	QFile qFile(strSEGYFile);
	if (!qFile.open(QIODevice::ReadOnly))
	{
		m_iErrorCode = 2;
		return false;
	}
	qFile.seek(3600);

	int iInline, iXline, iAzim;
	int	iInlineMin = 99999, iInlineMax = 0, iXlineMin = 99999, iXlineMax = 0, iInlineInc = 99999, iXlineInc = 99999;
	float fOffset;
	double dX, dY;
	int iXline00 = 99999, iXline01 = 0, iXline11 = 0;		//	3 corner points xline
	float fX00, fY00, fX01, fY01, fX11, fY11;				//	3 corner points x, y.
	QHash<QPair<unsigned short, unsigned short>, SKETraceOffsets *>& hashTraceInfo = m_pLoadParameters->GetTraceInfo();
	qint64 i, iNumTrace = (qFile.size() - 3600) / (m_pLoadParameters->GetTraceLength() + 240);
	bool bEast, bCCW;
	m_pLoadParameters->GetAzimuthInfo(bEast, bCCW);

	for (i = 0; i < iNumTrace; i++)
	{
		m_pLoadParameters->ReadATrace(qFile, iInline, iXline, fOffset, iAzim, dX, dY);
		QPair<unsigned short, unsigned short> theKey((unsigned short)iInline, (unsigned short)iXline);
		SKETraceOffsets *pTInfo = NULL;

		//	Store the offset information.
		if (!hashTraceInfo.contains(theKey))
		{
			pTInfo = new SKETraceOffsets;
			hashTraceInfo.insert(theKey, pTInfo);
		
			pTInfo->m_fX = dX;
			pTInfo->m_fY = dY;
		}
		else
			pTInfo = hashTraceInfo.value(theKey);

		pTInfo->m_vecIOffsetAzim.append((short)fOffset);
		if (m_pLoadParameters->IsAzimuth())
		{
			if (bCCW)
				iAzim *= (-1);
			if (bEast)
				iAzim += 90;
			if (iAzim < 0)
				iAzim += 360;

			pTInfo->m_vecIOffsetAzim.append((short)iAzim);
			if (m_iMaxFold < pTInfo->m_vecIOffsetAzim.size() / 2)
				m_iMaxFold = pTInfo->m_vecIOffsetAzim.size() / 2;
		}
		else
		{
			if (m_iMaxFold < pTInfo->m_vecIOffsetAzim.size())
				m_iMaxFold = pTInfo->m_vecIOffsetAzim.size();
		}

		if (fOffset < m_pLoadParameters->GetStartOffset())
			m_pLoadParameters->SetStartOffset(fOffset);
		if (fOffset > m_pLoadParameters->GetEndOffset())
			m_pLoadParameters->SetEndOffset(fOffset);
		if (iAzim < m_pLoadParameters->GetMinAzim())
			m_pLoadParameters->SetMinAzim(iAzim);
		if (iAzim > m_pLoadParameters->GetMaxAzim())
			m_pLoadParameters->SetMaxAzim(iAzim);

		//	Statistics the dimension information.
		iInlineMin = iInlineMin < iInline ? iInlineMin : iInline;
		iInlineMax = iInlineMax > iInline ? iInlineMax : iInline;
		iXlineMin = iXlineMin < iXline ? iXlineMin : iXline;
		iXlineMax = iXlineMax > iXline ? iXlineMax : iXline;

		if (iInline - iInlineMin > 0 && iInline - iInlineMin < iInlineInc)
			iInlineInc = iInline - iInlineMin;

		if (iXline - iXlineMin > 0 && iXline - iXlineMin < iXlineInc)
			iXlineInc = iXline - iXlineMin;

		if (iInline == iInlineMin)
		{
			if (iXline00 > iXline)
			{
				iXline00 = iXline;
				fX00 = dX;
				fY00 = dY;
			}

			if (iXline01 <= iXline)
			{
				iXline01 = iXline;
				fX01 = dX;
				fY01 = dY;
			}
		}
		else if (iInline == iInlineMax)
		{
			if (iXline11 <= iXline)
			{
				iXline11 = iXline;
				fX11 = dX;
				fY11 = dY;
			}
		}

		//	Refresh the progress bar.
		if (IsStopped())
		{
			m_iErrorCode = 0;
			return false;
		}
		else
			emit signalUpdateProgress(i, iNumTrace);
	}

	qFile.close();

	//	Here let's consider the unit of X,Y.
	unsigned short iUnit = m_pLoadParameters->GetUnit();
	double scale = 1.;
	if (::GetProject()->UsingMetricUnit() && iUnit == 2)
	{
		//	Convert from ft to m.
		scale = CXUnit::GetConvertRatio("ft", "m");
	}
	else if (!::GetProject()->UsingMetricUnit() && iUnit == 1)
	{
		//	Convert from m to ft.
		scale = CXUnit::GetConvertRatio("m", "ft");
	}

	//	Populate the UTM right now.
	int numInline = (iInlineMax - iInlineMin) / iInlineInc + 1;
	int numCrossline = (iXlineMax - iXlineMin) / iXlineInc + 1;
	CXSeismicUTMTool *pUTM = m_pLoadParameters->GetUTMTool();
	if (pUTM->GetNI() == 0)
	{
		//	The 1st file, initialize the UTM.
		pUTM->InitSize(iInlineMin, numInline, iInlineInc, iXlineMin, numCrossline, iXlineInc);
		pUTM->InitCoordinates(iInlineMin, iXline00, fX00 * scale, fY00 * scale,
			iInlineMin, iXline01, fX01 * scale, fY01 * scale,
			iInlineMax, iXline11, fX11 * scale, fY11 * scale);
	}
	else
	{
		//	Not the 1st file, create a new UTM first.
		CXSeismicUTMTool *pNewUTM = new CXSeismicUTMTool;
		pNewUTM->InitSize(iInlineMin, numInline, iInlineInc, iXlineMin, numCrossline, iXlineInc);
		pNewUTM->InitCoordinates(iInlineMin, iXline00, fX00 * scale, fY00 * scale,
			iInlineMin, iXline01, fX01 * scale, fY01 * scale,
			iInlineMax, iXline11, fX11 * scale, fY11 * scale);

		//	Compatible with the exist one?
		if (!pUTM->IsCompatible(pNewUTM))
		{
			delete pNewUTM;
			m_iErrorCode = 4;
			return false;
		}

		//	Merge them.
		int iOldMinInline, iOldMaxInline, iOldInlineInc, iOldMinCrossline, iOldMaxCrossline, iOldCrosslineInc;
		pUTM->GetLineNumRange(iOldMinInline, iOldMaxInline, iOldInlineInc, iOldMinCrossline, iOldMaxCrossline, iOldCrosslineInc);

		iInlineMin = iInlineMin < iOldMinInline ? iInlineMin : iOldMinInline;
		iInlineMax = iInlineMax > iOldMaxInline ? iInlineMax : iOldMaxInline;
		iXlineMin = iXlineMin < iOldMinCrossline ? iXlineMin : iOldMinCrossline;
		iXlineMax = iXlineMax > iOldMaxCrossline ? iXlineMax : iOldMaxCrossline;
		numInline = (iInlineMax - iInlineMin) / iInlineInc + 1;
		numCrossline = (iXlineMax - iXlineMin) / iXlineInc + 1;

		pUTM->Resize(iInlineMin, iXlineMin, numInline, numCrossline);
	}

	return true;
}