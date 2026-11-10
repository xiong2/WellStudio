#include <qdebug.h>
#include "xgeobody.h"
#include "xgeobodydetectionthread.h"
#include "xparametersgeobodydetection.h"
#include "xseismicdatavolume.h"
#include "x2dpolygon.h"
#include "xglobal.h"
#include "xsurfaceapi.h"
#include "x3dhorizon.h"
#include "xgraphicsapi.h"
#include "xbrickreader.h"
#include <QCoreApplication>
#include <algorithm>

class CXGeobodyCompareByCellNum
{
public:
	CXGeobodyCompareByCellNum(bool bAsc)
	{
		m_bAsc = bAsc;
	}
	bool operator()(CXGeobody* pBody1, CXGeobody* pBody2)
	{
		return m_bAsc ? pBody2->GetSkinCellNumber() > pBody1->GetSkinCellNumber() :
			pBody2->GetSkinCellNumber() < pBody1->GetSkinCellNumber();
	}
private:
	bool m_bAsc;

};

CXGeobodyDetectionThread::CXGeobodyDetectionThread(CXParametersGeobodyDetection* pDetectionParameters)
{
	m_pDetectionParameters = pDetectionParameters;
	m_pBFReader = NULL;
}

CXGeobodyDetectionThread::~CXGeobodyDetectionThread()
{
	if (m_pBFReader)
		delete m_pBFReader;

	if (IsStopped())
	{
		qDeleteAll(m_vecOutput);
		m_vecOutput.clear();
	}
}

void CXGeobodyDetectionThread::RunThread()
{
	if (IsStopped())
		return;

	this->EmitSetWindowName("Geobody Detection");
	this->EmitSetTaskName("Calculating...");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	int i, j, k;
	CXSeismicDataVolume *pDV = dynamic_cast<CXSeismicDataVolume *>(::GetObjectByID(m_pDetectionParameters->GetDVID()));
	if (!pDV)
		return;
	
	//	Calculate the 8 bits threshold.
	double dDataMin, dDataMax;
	pDV->GetDataRange(dDataMin, dDataMax);
	m_cLowTh = (unsigned char)(254 * (m_pDetectionParameters->GetLowThreshold() - dDataMin) / (dDataMax - dDataMin));
	m_cHighTh = (unsigned char)(254 * (m_pDetectionParameters->GetHighThreshold() - dDataMin) / (dDataMax - dDataMin));

	if (!m_pBFReader)
		m_pBFReader = new CXBrickReader(pDV);

	//	Find out the UTM of the output geobody.
	m_pUTM = new CXSeismicUTMTool(pDV->GetUTM());
	int iSInline = m_pDetectionParameters->GetStartInline();
	int iEInline = m_pDetectionParameters->GetEndInline();
	int iSXline = m_pDetectionParameters->GetStartXline();
	int iEXline = m_pDetectionParameters->GetEndXline();
	int iInlineInc = m_pUTM->GetInlineIncrement();
	int iXlineInc = m_pUTM->GetCrosslineIncrement();

	//	Using boundary polygon?
	unsigned int iNumPolygonPoints = 0;
	float *pPolygonPoints = NULL;
	QUuid polygonID = m_pDetectionParameters->GetBoundaryPolygonID();
	if (!polygonID.isNull())
	{
		CX2DPolygon *pPolygon = dynamic_cast<CX2DPolygon *>(::GetObjectByID(polygonID));
		if (pPolygon)
		{
			double *pData = pPolygon->GetData(iNumPolygonPoints);
			pPolygonPoints = new float[iNumPolygonPoints];
			iNumPolygonPoints /= 2;
			int iMinInline = 99999, iMaxInline = 0, iMinXline = 99999, iMaxXline = 0;

			for (i = 0; i < iNumPolygonPoints; i++)
			{
				m_pUTM->XYToLine(pData[2 * i], pData[2 * i + 1], pPolygonPoints[2 * i], pPolygonPoints[2 * i + 1]);

				iMinInline = iMinInline < pPolygonPoints[2 * i] ? iMinInline : pPolygonPoints[2 * i];
				iMaxInline = iMaxInline > pPolygonPoints[2 * i] ? iMaxInline : pPolygonPoints[2 * i];
				iMinXline = iMinXline < pPolygonPoints[2 * i + 1] ? iMinXline : pPolygonPoints[2 * i + 1];
				iMaxXline = iMaxXline > pPolygonPoints[2 * i + 1] ? iMaxXline : pPolygonPoints[2 * i + 1];
			}

			//	Shrink the line range.
			iSInline = iSInline > iMinInline ? iSInline : iMinInline;
			iEInline = iEInline < iMaxInline ? iEInline : iMaxInline;
			iSXline = iSXline > iMinXline ? iSXline : iMinXline;
			iEXline = iEXline < iMaxXline ? iEXline : iMaxXline;
		}
	}

	//	Shrink the UTM.
	int nI = (iEInline - iSInline) / iInlineInc + 1;
	int nJ = (iEXline - iSXline) / iXlineInc + 1;
	m_pUTM->Resize(iSInline, iSXline, nI, nJ);

	//	Z Range.
	m_fSZ = m_pDetectionParameters->GetStartZ();
	m_fEZ = m_pDetectionParameters->GetEndZ();
	double dDVSZ, dDVEZ;
	pDV->GetSamplingRange(dDVSZ, dDVEZ, m_dZInc);

	//	Using top or bottom surface?
	CX3DHorizon *pTopH = dynamic_cast<CX3DHorizon *>(::GetObjectByID(m_pDetectionParameters->GetTopSurfaceID()));
	CX3DHorizon *pBotH = dynamic_cast<CX3DHorizon *>(::GetObjectByID(m_pDetectionParameters->GetBottomSurfaceID()));
	float *pTHData = NULL;
	float *pBHData = NULL;
	if (pTopH)
	{
		pTopH = CXSurfaceAPI::InterpolateWithUTM(pTopH, m_pUTM);

		double dTmp, dZMin;
		pTopH->GetDimension(dTmp, dTmp, dTmp, dTmp, dZMin, dTmp);
		m_fSZ = dZMin;
		pTHData = pTopH->GetData();

		//	Correct it with the DV z range.
		if (m_fSZ < dDVSZ)
			m_fSZ = dDVSZ;

		m_fSZ = dDVSZ + (int)((m_fSZ - dDVSZ) / m_dZInc + 0.99) * m_dZInc;
	}
	if (pBotH)
	{
		pBotH = CXSurfaceAPI::InterpolateWithUTM(pBotH, m_pUTM);

		double dTmp, dZMax;
		pTopH->GetDimension(dTmp, dTmp, dTmp, dTmp, dTmp, dZMax);
		m_fEZ = dZMax;
		pBHData = pBotH->GetData();

		//	Correct it with the DV z range.
		if (m_fEZ > dDVEZ)
			m_fEZ = dDVEZ;

		m_fEZ = dDVSZ + (int)((m_fEZ - dDVSZ) / m_dZInc) * m_dZInc;
	}

	m_nZ = (int)(m_fEZ - m_fSZ) / m_dZInc + 1;
	qint64 iLineSize = m_nZ * nJ;
	qint64 iVolumeSize = iLineSize * nI;

	if (m_nZ < 1)
	{
		if (pPolygonPoints)
			delete[]pPolygonPoints;
		if (pTopH)
			delete pTopH;
		if (pBotH)
			delete pBotH;

		EmitGeneralErrorMsg("Z range error, too thin!");
		return;
	}
	
	//	A vector of bool for each voxel in the volume, true means that voxel need not be considered anymore.
	m_vecFlags.resize(iVolumeSize, false);

	//	A big loop to wipe out the position need not be involved into the calculation.
	int iInline, iXline;
	for (i = 0; i < nI; i++)
	{
		for (j = 0; j < nJ; j++)
		{
			//	Using boundary polygon?
			if (iNumPolygonPoints > 0)
			{
				m_pUTM->IJToLine(i, j, iInline, iXline);

				//	Outside the polygon means a whole track need not be considered.
				if (!CXGraphicsAPI::IsPointInsidePolygon((float)iInline, (float)iXline, pPolygonPoints, iNumPolygonPoints))
				{					
					std::fill(m_vecFlags.begin() + (i * nJ + j) * m_nZ, m_vecFlags.begin() + (i * nJ + j + 1) * m_nZ, true);

					continue;
				}
			}

			int iSOffset = 0, iEOffset = m_nZ;

			//	Use top surface?
			if (pTHData)
			{
				iSOffset = (pTHData[i * nJ + j] - m_fSZ) / m_dZInc;
			}

			//	Use bottom surface?
			if (pBHData)
			{
				iEOffset = (pBHData[i * nJ + j] - m_fSZ) / m_dZInc;
			}

			qint64 iOffset = m_nZ * (i * nJ + j);
			for (k = 0; k < iSOffset; k++)
				m_vecFlags[iOffset + k] = true;

			for (k = iEOffset; k < m_nZ; k++)
				m_vecFlags[iOffset + k] = true;
		}
	}

	//	Free the no longer needed memory.
	if (pPolygonPoints)
		delete []pPolygonPoints;
	if (pTopH)
		delete pTopH;
	if (pBotH)
		delete pBotH;

	//	A tmp file to store the result cells.
	QString strResFileName = ::GetProjectPath() + "geobody_TmpBuff" + ".dat";
	QFile qResFile(strResFileName);
	if (!qResFile.open(QIODevice::WriteOnly))
	{
		EmitGeneralErrorMsg("Cannot open data file to write!");
		return;
	}

	//	To statistic the range of the geobody during tracking.
	double xx, yy;
	double dMinX = 99999999., dMinY = 99999999., dMinZ = 99999999., dMaxX = 0, dMaxY = 0, dMaxZ = 0;

	qint64 iIDX, iSeed;
	QVector<CXGeobody *> vecGeobodies;
	QVector<qint64> vecTracking, vecBuff;

	//	Now loop each sample to track the geobody.
	int nCurrentPer, nPercent = 0, iCurrentStep = 0;
	for (iIDX = 0; iIDX < iVolumeSize; iIDX++)
	{
		vecTracking.clear();
		vecBuff.clear();

		//Update the progress bar.
		nCurrentPer = static_cast<int>((++iCurrentStep) * 100 / iVolumeSize);
		if (nCurrentPer > nPercent)
		{
			nPercent++;
			if (IsStopped())
				return;
			else
			{
				EmitUpdateProgress(nPercent, 100);
			}
		}

		//	This sample outside the boundary or has been tracked before.
		if (m_vecFlags[iIDX])
			continue;

		//	Not a valid cell, go to next one.
		if (!isOneCell(iIDX))
			continue;

		//	Is a valid cell, then use this as a seed.
		vecTracking << iIDX;

		//	Reset the range.
		dMaxX = dMaxY = dMaxZ = 0;
		dMinX = 999999999.;
		dMinY = 999999999.;
		dMinZ = 999999999.;

		//	Tracking using the seed.
		while (!vecTracking.isEmpty())
		{
			iSeed = vecTracking.last();
			vecTracking.pop_back();
			vecBuff << iSeed;

			//	Reset the range?
			i = iSeed / iLineSize;
			j = (iSeed % iLineSize) / m_nZ;
			k = iSeed % m_nZ;
			m_pUTM->IJToXY(i, j, xx, yy);
			dMinX = dMinX < xx ? dMinX : xx;
			dMinY = dMinY < yy ? dMinY : yy;
			dMinZ = dMinZ < k ? dMinZ : k;
			dMaxX = dMaxX > xx ? dMaxX : xx;
			dMaxY = dMaxY > yy ? dMaxY : yy;
			dMaxZ = dMaxZ > k ? dMaxZ : k;

			//	1.	One line above.
			if (i > 0 &&					//	Not the 1st line.
				!m_vecFlags[iSeed - iLineSize] &&		//	Not tracked before.
				isOneCell(iSeed - iLineSize))			//	Is a cell.
			{
				vecTracking << (iSeed - iLineSize);
			}

			//	2.	One trace above.
			if (j > 0 &&				//	Not the 1st trace.
				!m_vecFlags[iSeed - m_nZ] &&			//	Not tracked before.
				isOneCell(iSeed - m_nZ))				//	Is a cell.
			{
				vecTracking << (iSeed - m_nZ);
			}

			//	3.	One point above.
			if (k > 0 &&						//	Not the 1st point.
				!m_vecFlags[iSeed - 1] &&				//	Not tracked before.
				isOneCell(iSeed - 1))					//	Is a cell.
			{
				vecTracking << (iSeed - 1);
			}

			//	4.	One line below.
			if (i < nI - 1 &&		//	Not the last line.
				!m_vecFlags[iSeed + iLineSize] &&		//	Not tracked before.
				isOneCell(iSeed + iLineSize))			//	Is a cell.
			{
				vecTracking << (iSeed + iLineSize);
			}

			//	5.	One trace below.
			if (j < nJ -1 &&		//	Not the last trace.
				!m_vecFlags[iSeed + m_nZ] &&			//	Not tracked before.
				isOneCell(iSeed + m_nZ))				//	Is a cell.
			{
				vecTracking << (iSeed + m_nZ);
			}

			//	6.	One point below.
			if (k < m_nZ - 1 &&					//	Not the last point.
				!m_vecFlags[iSeed + 1] &&				//	Not tracked before.
				isOneCell(iSeed + 1))					//	Is a cell.
			{
				vecTracking << (iSeed + 1);
			}

			//	Use face connectivity, end tracking for this point.
			if (m_pDetectionParameters->GetFaceConnectivity())
				continue;

			//	7.	One line, trace, point above.
			if (i > 0 && j > 0 && k > 0 &&							//	Not the 1st line, trace and point.
				!m_vecFlags[iSeed - iLineSize - m_nZ - 1] &&		//	Not tracked before.
				isOneCell(iSeed - iLineSize - m_nZ - 1))			//	Is a cell.
			{
				vecTracking << (iSeed - iLineSize - m_nZ - 1);
			}

			//	8.	One line, trace above.
			if (i > 0 && j > 0 &&									//	Not the 1st line, trace.
				!m_vecFlags[iSeed - iLineSize - m_nZ] &&			//	Not tracked before.
				isOneCell(iSeed - iLineSize - m_nZ))				//	Is a cell.
			{
				vecTracking << (iSeed - iLineSize - m_nZ);
			}

			//	9.	One line, trace above, one point below.
			if (i > 0 && j > 0 && k < m_nZ - 1 &&					//	Not the 1st line, trace and last point.
				!m_vecFlags[iSeed - iLineSize - m_nZ + 1] &&		//	Not tracked before.
				isOneCell(iSeed - iLineSize - m_nZ + 1))			//	Is a cell.
			{
				vecTracking << (iSeed - iLineSize - m_nZ + 1);
			}		

			//	10.	One line, point above.
			if (i > 0 && k > 0 &&									//	Not the 1st line, point.
				!m_vecFlags[iSeed - iLineSize - 1] &&				//	Not tracked before.
				isOneCell(iSeed - iLineSize - 1))					//	Is a cell.
			{
				vecTracking << (iSeed - iLineSize - 1);
			}

			//	11.	One line above, one point below.
			if (i > 0 && k < m_nZ - 1 &&							//	Not the 1st line, last point.
				!m_vecFlags[iSeed - iLineSize + 1] &&				//	Not tracked before.
				isOneCell(iSeed - iLineSize + 1))					//	Is a cell.
			{
				vecTracking << (iSeed - iLineSize + 1);
			}

			//	12.	One line , point above, one trace below.
			if (i > 0 && j < nJ - 1 && k > 0 &&						//	Not the 1st line, point and last trace.
				!m_vecFlags[iSeed - iLineSize + m_nZ - 1] &&		//	Not tracked before.
				isOneCell(iSeed - iLineSize + m_nZ - 1))			//	Is a cell.
			{
				vecTracking << (iSeed - iLineSize + m_nZ - 1);
			}

			//	13.	One line above, one trace below.
			if (i > 0 && j < nJ - 1 &&								//	Not the 1st line, last trace.
				!m_vecFlags[iSeed - iLineSize + m_nZ] &&			//	Not tracked before.
				isOneCell(iSeed - iLineSize + m_nZ))				//	Is a cell.
			{
				vecTracking << (iSeed - iLineSize + m_nZ);
			}

			//	14.	One line above, one trace, point below.
			if (i > 0 && j < nJ -1 && k < m_nZ - 1 &&				//	Not the 1st line, last trace, point.
				!m_vecFlags[iSeed - iLineSize + m_nZ + 1] &&		//	Not tracked before.
				isOneCell(iSeed - iLineSize + m_nZ + 1))			//	Is a cell.
			{
				vecTracking << (iSeed - iLineSize + m_nZ + 1);
			}

			//	15.	One trace, point above.
			if (j > 0 && k > 0 &&									//	Not the 1st trace, point.
				!m_vecFlags[iSeed - m_nZ - 1] &&					//	Not tracked before.
				isOneCell(iSeed - m_nZ - 1))						//	Is a cell.
			{
				vecTracking << (iSeed - m_nZ - 1);
			}

			//	16.	One trace above, one point below.
			if (j > 0 && k < m_nZ - 1 &&							//	Not the 1st trace, last point.
				!m_vecFlags[iSeed - m_nZ + 1] &&					//	Not tracked before.
				isOneCell(iSeed - m_nZ + 1))						//	Is a cell.
			{
				vecTracking << (iSeed - m_nZ + 1);
			}

			//	17.	One trace below, one point above.
			if (j < nJ - 1 && k > 0 &&								//	Not the last trace, 1st point.
				!m_vecFlags[iSeed + m_nZ - 1] &&					//	Not tracked before.
				isOneCell(iSeed + m_nZ - 1))						//	Is a cell.
			{
				vecTracking << (iSeed + m_nZ - 1);
			}

			//	18.	One trace, point below.
			if (j < nJ - 1 && k < m_nZ - 1 &&						//	Not the last trace, point.
				!m_vecFlags[iSeed + m_nZ + 1] &&					//	Not tracked before.
				isOneCell(iSeed + m_nZ + 1))						//	Is a cell.
			{
				vecTracking << (iSeed + m_nZ + 1);
			}

			//	19.	One line below, one trace, point above.
			if (i < nI - 1 && j > 0 && k > 0 &&						//	Not the last line, 1st trace, point.
				!m_vecFlags[iSeed + iLineSize - m_nZ - 1] &&		//	Not tracked before.
				isOneCell(iSeed + iLineSize - m_nZ - 1))			//	Is a cell.
			{
				vecTracking << (iSeed + iLineSize - m_nZ - 1);
			}

			//	20.	One line below, trace above.
			if (i < nI - 1 && j > 0 && 								//	Not the last line, 1st trace.
				!m_vecFlags[iSeed + iLineSize - m_nZ] &&			//	Not tracked before.
				isOneCell(iSeed + iLineSize - m_nZ))				//	Is a cell.
			{
				vecTracking << (iSeed + iLineSize - m_nZ);
			}

			//	21.	One line, point below, one trace above.
			if (i < nI - 1 && j > 0 && k < m_nZ - 1 &&				//	Not the last line, point and 1st trace.
				!m_vecFlags[iSeed + iLineSize - m_nZ + 1] &&		//	Not tracked before.
				isOneCell(iSeed + iLineSize - m_nZ + 1))			//	Is a cell.
			{
				vecTracking << (iSeed + iLineSize - m_nZ + 1);
			}

			//	22.	One line below, one point above.
			if (i < nI - 1 && k > 0	&&								//	Not the last line, 1st point.
				!m_vecFlags[iSeed + iLineSize - 1] &&				//	Not tracked before.
				isOneCell(iSeed + iLineSize - 1))					//	Is a cell.
			{
				vecTracking << (iSeed + iLineSize - 1);
			}

			//	23.	One line, point below.
			if (i < nI - 1 && k < m_nZ - 1 && 						//	Not the last line, point.
				!m_vecFlags[iSeed + iLineSize + 1] &&				//	Not tracked before.
				isOneCell(iSeed + iLineSize + 1))					//	Is a cell.
			{
				vecTracking << (iSeed + iLineSize + 1);
			}

			//	24.	One line, trace below, one point above.
			if (i < nI - 1 && j < nJ - 1 && k >  0 &&				//	Not the last line, trace, 1st point.
				!m_vecFlags[iSeed + iLineSize + m_nZ - 1] &&		//	Not tracked before.
				isOneCell(iSeed + iLineSize + m_nZ - 1))			//	Is a cell.
			{
				vecTracking << (iSeed + iLineSize + m_nZ - 1);
			}

			//	25.	One line, trace below.
			if (i < nI - 1 && j < nJ - 1 &&							//	Not the last line, trace.
				!m_vecFlags[iSeed + iLineSize + m_nZ] &&			//	Not tracked before.
				isOneCell(iSeed + iLineSize + m_nZ))				//	Is a cell.
			{
				vecTracking << (iSeed + iLineSize + m_nZ);
			}

			//	26.	One line, trace, point below.
			if (i < nI - 1 && j < nJ - 1 && k < m_nZ - 1 &&			//	Not the last line, trace, point.
				!m_vecFlags[iSeed + iLineSize + m_nZ + 1] &&		//	Not tracked before.
				isOneCell(iSeed + iLineSize + m_nZ + 1))			//	Is a cell.
			{
				vecTracking << (iSeed + iLineSize + m_nZ + 1);
			}
		}

		//	Check the cell number in the buff.
		if (vecBuff.size() < m_pDetectionParameters->GetMiniSize())
			continue;

		//	Since it will bring troubles in the future, no long wipe out them.....
		//	Now wipe out the inside cells.
		//QVector<qint64> vecSkinCell;
		//wipeOutInsideCells(vecSkinCell, vecBuff);

		//	Write the reseult vector to the file.
		if (!qResFile.isOpen())
			qResFile.open(QIODevice::WriteOnly);
		qResFile.write((char *)(vecBuff.data()), sizeof(qint64) * vecBuff.size());
		qResFile.close();

		//	Create the geobody.
		CXGeobody *pGeobody = new CXGeobody(m_pUTM, m_fSZ, m_fEZ, m_dZInc, false);
		pGeobody->PopulateData(strResFileName, vecBuff.size());
		pGeobody->SetDimension(dMinX, dMaxX, dMinY, dMaxY, m_fSZ + dMinZ * m_dZInc, m_fSZ + dMaxZ * m_dZInc);

		vecGeobodies << pGeobody;
	}

	//	Free the tracking flags.
	m_vecFlags.clear();

	//	Need the merge geobody?
	if (m_pDetectionParameters->GetMerge() && !vecGeobodies.isEmpty())
	{
		qint64 iTotalRes = 0;		
		double dWMinX = 99999999., dWMinY = 99999999., dWMinZ = 99999999., dWMaxX = 0, dWMaxY = 0, dWMaxZ = 0;
		QString strWholeFileName = ::GetProjectPath() + "geobody_WholeBuff" + ".dat";
		QFile qWFile(strWholeFileName);
		qWFile.open(QIODevice::WriteOnly);

		for (i = 0; i < vecGeobodies.size(); i++)
		{
			unsigned int iNumCells;
			qint64 *pCells = vecGeobodies[i]->GetAllCells(iNumCells);

			//	Write the cells into the file.
			iTotalRes += iNumCells;
			qWFile.write((char *)pCells, sizeof(qint64) * iNumCells);

			vecGeobodies[i]->GetDimension(dMinX, dMaxX, dMinY, dMaxY, dMinZ, dMaxZ);
			dWMinX = dWMinX < dMinX ? dWMinX : dMinX;
			dWMaxX = dWMaxX > dMaxX ? dWMaxX : dMaxX;
			dWMinY = dWMinY < dMinY ? dWMinY : dMinY;
			dWMaxY = dWMaxY > dMaxY ? dWMaxY : dMaxY;
			dWMinZ = dWMinZ < dMinZ ? dWMinZ : dMinZ;
			dWMaxZ = dWMaxZ > dMaxZ ? dWMaxZ : dMaxZ;
		}

		qWFile.close();

		QString strGeobodyName = m_pDetectionParameters->GetGeobodyName();
		CXGeobody *pGeobody = new CXGeobody(m_pUTM, m_fSZ, m_fEZ, m_dZInc, true);
		pGeobody->SetObjectName(strGeobodyName);
		pGeobody->PopulateData(strWholeFileName, iTotalRes);
		pGeobody->SetDimension(dWMinX, dWMaxX, dWMinY, dWMaxY, dWMinZ, dWMaxZ);

		m_vecOutput.push_back(pGeobody);
	}	

	if (vecGeobodies.size() > 0)
	{
		CXGeobodyCompareByCellNum GeobodyCompare(true);
		std::sort(vecGeobodies.begin(), vecGeobodies.end(), GeobodyCompare);
		m_vecOutput.insert(m_vecOutput.end(), vecGeobodies.begin(), vecGeobodies.end());		
	}

	if (m_vecOutput.size() <= 0)
	{
		EmitGeneralErrorMsg("No geobody generated, too strict criterion?");
		return;
	}
}

bool CXGeobodyDetectionThread::isOneCell(qint64 iIDX)
{
	//	This cell be detected!
	m_vecFlags[iIDX] = true;

	//	iIDX to inline, xline and z.
	int iInline, iXline;
	float fZ = m_fSZ + m_dZInc * (iIDX % m_nZ);
	int j = (iIDX % (m_nZ * m_pUTM->GetNJ())) / m_nZ;
	int i = iIDX / (m_nZ * m_pUTM->GetNJ());
	m_pUTM->IJToLine(i, j, iInline, iXline);

	//	Convert to DV's i, j, k;
	CXSeismicDataVolume *pDV = dynamic_cast<CXSeismicDataVolume *>(::GetObjectByID(m_pDetectionParameters->GetDVID()));
	pDV->GetUTM().LineToIJ(iInline, iXline, i, j);

	double dSZ, dEZ, dZInc;
	pDV->GetSamplingRange(dSZ, dEZ, dZInc);
	int k = (int)((fZ - dSZ) / dZInc);

	unsigned char cVal = m_pBFReader->ReadData(k, i, j);

	if (cVal >= m_cLowTh && cVal <= m_cHighTh)
		return true;
	else
		return false;
}

void CXGeobodyDetectionThread::wipeOutInsideCells(QVector<qint64>& vecOutputCells, QVector<qint64>& vecInputCells)
{
	int i, j, nJ = m_pUTM->GetNJ(), iNumCells = vecInputCells.size();
	qint64 iIDX, iOffset[6];

	iOffset[0] = -1;			//	A sample above.
	iOffset[1] = 1;				//	A sample below.
	iOffset[2] = -(nJ * m_nZ);	//	A line prior.
	iOffset[3] = nJ * m_nZ;		//	A line behind.
	iOffset[4] = -m_nZ;			//	A trace prior.
	iOffset[5] = m_nZ;			//	A trace behind.

	for (i = 0; i < vecInputCells.size(); i++)
	{
		for (j = 0; j < 6; j++)
		{
			iIDX = vecInputCells[i] + iOffset[j];
			if (!std::binary_search(vecInputCells.begin(), vecInputCells.end(), iIDX))
			{
				vecOutputCells << vecInputCells[i];
				break;
			}
		}
	}
}