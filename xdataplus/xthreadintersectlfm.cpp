#pragma warning(push,0)
#include <QCoreApplication>
#include <cassert>
#include <QMap>
#include "xthreadintersectlfm.h"
#include "xparameterlfmintersecton.h"
#include "xlfmgeometry.h"
#include "xlfmupscalinggeometry.h"
//
#include "xglobal.h"
#include "xwellpath.h"
#include "xwell.h"
#include "xwelltd.h"
#include "xregulardatareader.h"
#include "xproject.h"
#include "xmathmacro.h"
#include "xwellcurve.h"
#include "xutility.h"
#include "xgraphicsapi.h"
#include <cassert>

#pragma warning(pop)


//		 ------- J
//	   /|
//	  /	|
//	 I	|
//		|K
//
//
//  -----0-----1-----
//      /     /
//  --3-----2------
//    |  |  |  |
//    |  |  |  |
//    |  4--|--5
//    |/    | /
//----7-----6----------
class CXLFMCell
{
public:
	CXLFMCell(const double* X, const double* Y, const double* TopZ, const double* BottomZ)
	{
		m_nIntersectionNum = 0;

		for (int i = 0; i < 4; ++i)
		{
			m_Vertice[i].SetValue(X[i], Y[i], TopZ[i]);
			m_Vertice[i + 4].SetValue(X[i], Y[i], BottomZ[i]);
		}
	}

public:
	bool IntersectOneSegment(const CXVector3D& p1, const CXVector3D& p2, int index)
	{
		// Top 013, 213 
		IntersectOneTriangle(m_Vertice[0], m_Vertice[1], m_Vertice[3], p1, p2, index);
		IntersectOneTriangle(m_Vertice[2], m_Vertice[1], m_Vertice[3], p1, p2, index);

		// Bottom 457, 657
		IntersectOneTriangle(m_Vertice[4], m_Vertice[5], m_Vertice[7], p1, p2, index);
		IntersectOneTriangle(m_Vertice[6], m_Vertice[5], m_Vertice[7], p1, p2, index);

		// Left 034, 734
		IntersectOneTriangle(m_Vertice[0], m_Vertice[3], m_Vertice[4], p1, p2, index);
		IntersectOneTriangle(m_Vertice[7], m_Vertice[3], m_Vertice[4], p1, p2, index);

		// Right 125, 625
		IntersectOneTriangle(m_Vertice[1], m_Vertice[2], m_Vertice[5], p1, p2, index);
		IntersectOneTriangle(m_Vertice[6], m_Vertice[2], m_Vertice[5], p1, p2, index);

		// Front 236, 736
		IntersectOneTriangle(m_Vertice[2], m_Vertice[3], m_Vertice[6], p1, p2, index);
		IntersectOneTriangle(m_Vertice[7], m_Vertice[3], m_Vertice[6], p1, p2, index);

		// Back 014, 514
		IntersectOneTriangle(m_Vertice[0], m_Vertice[1], m_Vertice[4], p1, p2, index);
		IntersectOneTriangle(m_Vertice[5], m_Vertice[1], m_Vertice[4], p1, p2, index);

		return (m_nIntersectionNum > 0);
	}

	void GetVertice(double* p)
	{
		for (int i = 0; i < 8; ++i)
		{
			p[i * 3] = m_Vertice[i][0];
			p[i * 3 + 1] = m_Vertice[i][1];
			p[i * 3 + 2] = m_Vertice[i][2];
		}
	}


	int GetIntersectionNum() { return m_nIntersectionNum; }
	CXVector3D& GetFirstIntersection() { return m_Intersection[0]; }
	CXVector3D& GetSecondIntersection() { return m_Intersection[1]; }

	int GetFirstIntersectionIndex() { return m_index1; }
	int GetSecondIntersectionIndex() { return m_index2; }
private:
	void IntersectOneTriangle(const CXVector3D& v1, const CXVector3D& v2, const CXVector3D& v3,
		const CXVector3D& p1, const CXVector3D& p2, int index)
	{
		CXVector3D intersection;
		if (!CXGraphicsAPI::IntersectLineSegmentAndTriangle(v1, v2, v3, p1, p2, intersection))
			return;
		else
		{
			if (m_nIntersectionNum == 0)
			{
				m_nIntersectionNum++;
				m_Intersection[0] = intersection;
				m_index1 = index;
			}
			else if (m_nIntersectionNum == 1)
			{
				if (m_Intersection[0] != intersection)
				{
					m_nIntersectionNum++;
					m_Intersection[1] = intersection;
					m_index2 = index;
				}
			}
			else if (m_nIntersectionNum == 2)
			{
				if (m_Intersection[0] != intersection && m_Intersection[1] != intersection)
				{
					m_Intersection[1] = intersection;
					m_index2 = index;
				}
			}
		}
	}
private:
	CXVector3D m_Vertice[8];

	int m_nIntersectionNum;

	CXVector3D m_Intersection[2];

	int m_index1, m_index2;
};

CXThreadIntersectLFM::CXThreadIntersectLFM(CXParameterLFMIntersecton* pPara, CXObject* pParent)
	:m_pPara(pPara)
{
	m_pLFM = dynamic_cast<CXLFMGeometry*>(pParent);
	assert(m_pLFM && m_pPara);

	m_nI = 0; m_nJ = 0; m_nK = 0;

	m_pUpscalingGeometry = NULL;

	m_p2DGeoData = NULL;

	if (_Init())
	{
		_LockObj();
		_CreateObj();
	}
}

CXThreadIntersectLFM::~CXThreadIntersectLFM()
{
	// 2D data
	if (m_p2DGeoData)
	{
		NXUtility::Free2DArray<double>(m_p2DGeoData, m_nK);
		m_p2DGeoData = NULL;
	}

	// Cell data
	QMap<qint64, CXLFMCell*>::iterator it;
	for (it = m_mapIndexToCell.begin(); it != m_mapIndexToCell.end(); ++it)
	{
		CXLFMCell* pCell = it.value();
		if (pCell)
			delete pCell;
	}
	m_mapIndexToCell.clear();

	//Unlock
	if (m_pLFM)
		UnlockRead(m_pLFM);
	for (int i = 0; i < m_vecWell.size(); ++i)
	{
		UnlockRead(m_vecWell[i]);
	}

	// delete ?
	if (IsStopped())
	{
		if (m_pUpscalingGeometry)
		{
			delete m_pUpscalingGeometry;
			m_pUpscalingGeometry = NULL;
		}
	}
}

bool CXThreadIntersectLFM::_Init()
{
	std::vector<QUuid> vecWellID = m_pPara->GetVecWellID();
	for (int i = 0; i < vecWellID.size(); ++i)
	{
		CXWell* pWell = dynamic_cast<CXWell*>(::GetObjectByID(vecWellID[i]));

		if (pWell)
		{
			m_vecWell.push_back(pWell);	
		}
	}

	if (m_vecWell.empty())
		return false;
	else
		return true;
}

void CXThreadIntersectLFM::_LockObj()
{
	if (m_pLFM)
		LockRead(m_pLFM);

	for (int i = 0; i < m_vecWell.size(); ++i)
	{
		LockRead(m_vecWell[i]);
	}
}

void CXThreadIntersectLFM::_CreateObj()
{
	m_utm = m_pLFM->GetUTM();
	m_nI = m_utm.GetNI();
	m_nJ = m_utm.GetNJ();
	m_nK = m_pLFM->GetNK();
	
	m_pUpscalingGeometry = new CXLFMUpscalingGeometry(m_pLFM, "Upscaling Geometry");
}

void CXThreadIntersectLFM::RunThread()
{
	if (IsStopped())
		return;

	if (m_vecWell.empty())
	{
		QString strErrorMsg = "Please select wells first.";
		EmitGeneralErrorMsg(strErrorMsg);
		return;
	}

	if (m_pLFM == NULL)
	{
		QString strErrorMsg = "Cannot find the selected low frequency model.";
		EmitGeneralErrorMsg(strErrorMsg);
		return;
	}

	this->EmitSetWindowName("Build Upscaling Geometry");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	// Initialization
	if (!_InitData())
		return;

	_UpscaleAllWells();
}

void CXThreadIntersectLFM::_UpscaleAllWells()
{
	for (int i = 0; i < m_vecWell.size(); ++i)
	{
		if (IsStopped())
			return;

		if (!_PrepareOneWellData(m_vecWell.at(i)))
		{
			this->EmitGeneralErrorMsg("The selected well does not have the T-D curve.");
			return;
		}
	
		this->EmitResetProgressBar();
		this->EmitSetTaskName(QString("Calculating ") + m_vecWell.at(i)->GetObjectName());
		QCoreApplication::instance()->processEvents();

		if (!_UpscalingOneWellLog(i))
			return;
	}

	if (m_pUpscalingGeometry->GetTotalCellNum() == 0)
	{
		this->EmitGeneralErrorMsg("The all selected wells do not intersect the low frequency model.");
		return;
	}
	else
	{
		std::vector<QUuid> vecValidWellID;
		QStringList strListName;

		for (int i = 0; i < m_vecValidWell.size(); ++i)
		{
			vecValidWellID.push_back(m_vecValidWell.at(i)->GetObjectID());
			strListName.append(m_vecValidWell.at(i)->GetObjectName());
		}
		m_pPara->SetVecWellID(vecValidWellID);
		m_pPara->SetListWellName(strListName);
	}
}

CXObject* CXThreadIntersectLFM::GetOutputObj()
{
	return m_pUpscalingGeometry;
}

bool CXThreadIntersectLFM::_InitData()
{	
	this->EmitSetTaskName("Reading data from the low frequency model...");
	QCoreApplication::instance()->processEvents();

	CXRegularDataReader<float> reader(m_pLFM->GetDataFileName(), m_nK, m_nI, m_nJ);
	if (!reader.Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the data of the low frequency model.");
		return false;
	}

	// Allocate memory
	int nIJSize = m_nI*m_nJ;
	// Allocate memory
	m_p2DGeoData = NXUtility::New2DArray<double>(m_nK, nIJSize);
	if (!m_p2DGeoData)
	{
		EmitMemoryNotEnough();
		return false;
	}

	// read data
	std::vector<float> vecSlice(nIJSize);
	for (int k = 0; k < m_nK; ++k)
	{
		if (IsStopped())
			return false;
		else
			this->EmitUpdateProgress(k, m_nK);

		if (!reader.ReadUSection(k, &vecSlice[0]))
		{
			this->EmitGeneralErrorMsg("Cannot read low frequency model data from the disk.");
			return false;
		}		
		
		std::copy(vecSlice.begin(), vecSlice.end(), m_p2DGeoData[k]);
	}

	return true;
}

bool CXThreadIntersectLFM::_PrepareOneWellData(CXWell* pWell)
{
	m_vecX.clear();
	m_vecY.clear();
	m_vecTWT.clear();

	if (!pWell->GetXYAndTWT(m_vecX, m_vecY, m_vecTWT, m_vecMD))
	{
		return false;
	}

	m_nLength = (int)m_vecX.size();

	return true;
}

bool CXThreadIntersectLFM::_UpscalingOneWellLog(int iWell)
{
	// Clear the map
	CXLFMCell* pCell = NULL;
	QMap<qint64, CXLFMCell*>::iterator it;
	for (it = m_mapIndexToCell.begin(); it != m_mapIndexToCell.end(); ++it)
	{
		pCell = it.value();
		delete pCell;
	}
	m_mapIndexToCell.clear();

	// Calculate intersection
	CXVector3D p1, p2;
	for (int i = 0; i < m_nLength - 1; ++i)
	{
		if (IsStopped())
			return false;
		else
			this->EmitUpdateProgress(i, m_nLength - 1);

		p1.SetValue(m_vecX[i], m_vecY[i], m_vecTWT[i]);
		p2.SetValue(m_vecX[i + 1], m_vecY[i + 1], m_vecTWT[i + 1]);
		_IntersectionOneSegment(p1, p2, i);
	}

	// If empty
	if (m_mapIndexToCell.empty())
	{
		//this->EmitGeneralErrorMsg("The selected well does not intersect the low frequency model.");
		return true;
	}

	// Allocated memory	
	int nCellNum = m_mapIndexToCell.size();

	std::vector<qint64> vecIndex(nCellNum);
	std::vector<double> vecXYZ(24 * nCellNum);
	std::vector<double> vecTopZ(nCellNum);
	std::vector<double> vecBotZ(nCellNum);

	// Calculate interval velocity for each cell
	int nCount = 0;
	double dZTop, dZBottom;
	for (it = m_mapIndexToCell.begin(); it != m_mapIndexToCell.end(); ++it)
	{
		float fCellValue;

		int iIndexTop, iIndexBot;
		if (it.value()->GetIntersectionNum() == 1)
		{
			continue;
		}
		else
		{
			CXVector3D& p1 = it.value()->GetFirstIntersection();
			CXVector3D& p2 = it.value()->GetSecondIntersection();
			int iIndex1 = it.value()->GetFirstIntersectionIndex();
			int iIndex2 = it.value()->GetSecondIntersectionIndex();

			dZTop = qMin(p1[2], p2[2]);
			dZBottom = qMax(p1[2], p2[2]);

			iIndexTop = qMin(iIndex1, iIndex2);
			iIndexBot = qMax(iIndex1, iIndex2);
		}

		vecIndex[nCount] = it.key();

		it.value()->GetVertice(&vecXYZ[0] + nCount * 24);

		dZTop = m_vecMD[iIndexTop] + (m_vecMD[iIndexTop+1] - m_vecMD[iIndexTop]) / (m_vecTWT[iIndexTop+1] - m_vecTWT[iIndexTop])*(dZTop - m_vecTWT[iIndexTop]);
		dZBottom = m_vecMD[iIndexBot] + (m_vecMD[iIndexBot+1] - m_vecMD[iIndexBot]) / (m_vecTWT[iIndexBot+1] - m_vecTWT[iIndexBot])*(dZBottom - m_vecTWT[iIndexBot]);

		vecTopZ[nCount] = dZTop;
		vecBotZ[nCount] = dZBottom;

		++nCount;
	}

	if (nCount < 1)
	{
		this->EmitGeneralErrorMsg("The selected well does not intersect the low frequency model");
		return false;
	}

	m_pUpscalingGeometry->AddOneWell(m_vecWell[iWell]->GetObjectID(), nCount, &vecIndex[0], &vecXYZ[0], &vecTopZ[0], &vecBotZ[0]);

	m_vecValidWell.push_back(m_vecWell[iWell]);

	return true;
}

void CXThreadIntersectLFM::_IntersectionOneSegment(const CXVector3D& p1, const CXVector3D& p2, int index)
{
	// Get the bounding box with indices
	float fI1, fJ1, fI2, fJ2;
	m_utm.XYToIJ(p1[0], p1[1], fI1, fJ1);
	m_utm.XYToIJ(p2[0], p2[1], fI2, fJ2);

	double dIMin, dJMin, dIMax, dJMax;
	dIMin = qMin(fI1, fI2);
	dIMax = qMax(fI1, fI2);
	dJMin = qMin(fJ1, fJ2);
	dJMax = qMax(fJ1, fJ2);

	int iIMin, iIMax, iJMin, iJMax;
	iIMin = qBound(0, static_cast<int>(dIMin - 0.5), m_nI - 1);
	iIMax = qBound(0, static_cast<int>(dIMax + 0.5), m_nI - 1);
	iJMin = qBound(0, static_cast<int>(dJMin - 0.5), m_nJ - 1);
	iJMax = qBound(0, static_cast<int>(dJMax + 0.5), m_nJ - 1);

	// Loop each cell
	qint64 nIJSize = m_nI*m_nJ;
	double X[4], Y[4], TopZ[4], BottomZ[4];

	CXLFMCell* pCell = NULL;
	qint64 cellIndex;

	float m_fInvalidData = (float)g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(m_fInvalidData);
	for (int k = 0; k < m_nK; ++k)
	{
		if (IsStopped())
			return;

		for (int i = iIMin; i <= iIMax; ++i)
		{
			for (int j = iJMin; j <= iJMax; ++j)
			{
				if (qAbs(m_p2DGeoData[k][i*m_nJ + j] - m_fInvalidData) < fInvalidEPS)
					continue;

				CalculateOneCellXYZ(m_utm, m_p2DGeoData, m_fInvalidData, m_nI, m_nJ, m_nK, i, j, k, X, Y, TopZ, BottomZ);

				// Overlapped ?
				if (!_IsBound(X, Y, TopZ, BottomZ, p1, p2))
					continue;

				cellIndex = k*nIJSize + i*m_nJ + j;
				pCell = m_mapIndexToCell.value(cellIndex, NULL);
				if (!pCell)
				{
					pCell = new CXLFMCell(X, Y, TopZ, BottomZ);
					if (m_nK == 2 || pCell->IntersectOneSegment(p1, p2, index))
						m_mapIndexToCell.insert(cellIndex, pCell);
					else
						delete pCell;
				}
				else
				{
					pCell->IntersectOneSegment(p1, p2, index);
				}
			}
		}
	}
}

void CXThreadIntersectLFM::CalculateOneCellXYZ(CXSeismicUTMTool& utm, double** p2DData, float fInvalid, int nI, int nJ, int nK, int i, int j, int k, double* X, double* Y, double* TopZ, double* BottomZ)
{
	double Z[4][3];
	double dI, dJ;
	int iZTop, iZMiddle, iZBottom, ii, jj;
	int iCount = 0;

	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);

	iZTop = qMax(0, k - 1);
	iZMiddle = k;
	iZBottom = qMin(nK - 1, k + 1);

	// Upper left (0)
	dI = qMax(0., i - 0.5); dJ = qMax(0., j - 0.5);
	utm.IJToXY2(dI, dJ, X[0], Y[0]);

	iCount = 0;
	ii = qMax(0, i - 1); jj = qMax(0, j - 1);
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[0], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = qMax(0, i - 1); jj = j;
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[1], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = i; jj = j;
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[2], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = i; jj = qMax(0, j - 1);
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[3], ii*nJ + jj, fInvalid, fInvalidEPS);

	TopZ[0] = (Z[0][0] + Z[1][0] + Z[2][0] + Z[3][0] + Z[0][1] + Z[1][1] + Z[2][1] + Z[3][1]) / (iCount * 2);
	BottomZ[0] = (Z[0][2] + Z[1][2] + Z[2][2] + Z[3][2] + Z[0][1] + Z[1][1] + Z[2][1] + Z[3][1]) / (iCount * 2);

	// Upper right (1)
	dI = qMax(0., i - 0.5); dJ = qMin(nJ - 1., j + 0.5);
	utm.IJToXY2(dI, dJ, X[1], Y[1]);

	iCount = 0;
	ii = qMax(0, i - 1); jj = j;
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[0], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = qMax(0, i - 1); jj = qMin(nJ - 1, j + 1);
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[1], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = i; jj = qMin(nJ - 1, j + 1);
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[2], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = i; jj = j;
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[3], ii*nJ + jj, fInvalid, fInvalidEPS);

	TopZ[1] = (Z[0][0] + Z[1][0] + Z[2][0] + Z[3][0] + Z[0][1] + Z[1][1] + Z[2][1] + Z[3][1]) / (iCount * 2);
	BottomZ[1] = (Z[0][2] + Z[1][2] + Z[2][2] + Z[3][2] + Z[0][1] + Z[1][1] + Z[2][1] + Z[3][1]) / (iCount * 2);

	// Lower right (2)
	dI = qMin(nI - 1., i + 0.5); dJ = qMin(nJ - 1., j + 0.5);
	utm.IJToXY2(dI, dJ, X[2], Y[2]);

	iCount = 0;
	ii = i; jj = j;
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[0], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = i; jj = qMin(nJ - 1, j + 1);
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[1], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = qMin(nI - 1, i + 1); jj = qMin(nJ - 1, j + 1);
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[2], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = qMin(nI - 1, i + 1); jj = j;
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[3], ii*nJ + jj, fInvalid, fInvalidEPS);

	TopZ[2] = (Z[0][0] + Z[1][0] + Z[2][0] + Z[3][0] + Z[0][1] + Z[1][1] + Z[2][1] + Z[3][1]) / (iCount * 2);
	BottomZ[2] = (Z[0][2] + Z[1][2] + Z[2][2] + Z[3][2] + Z[0][1] + Z[1][1] + Z[2][1] + Z[3][1]) / (iCount * 2);

	// Lower left (3)
	dI = qMin(nI - 1., i + 0.5); dJ = qMax(0., j - 0.5);
	utm.IJToXY2(dI, dJ, X[3], Y[3]);

	iCount = 0;
	ii = i; jj = qMax(0, j - 1);
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[0], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = i; jj = j;
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[1], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = qMin(nI - 1, i + 1); jj = j;
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[2], ii*nJ + jj, fInvalid, fInvalidEPS);

	ii = qMin(nI - 1, i + 1); jj = qMax(0, j - 1);
	iCount += _GetZ(iZTop, iZMiddle, iZBottom, p2DData, Z[3], ii*nJ + jj, fInvalid, fInvalidEPS);

	TopZ[3] = (Z[0][0] + Z[1][0] + Z[2][0] + Z[3][0] + Z[0][1] + Z[1][1] + Z[2][1] + Z[3][1]) / (iCount * 2);
	BottomZ[3] = (Z[0][2] + Z[1][2] + Z[2][2] + Z[3][2] + Z[0][1] + Z[1][1] + Z[2][1] + Z[3][1]) / (iCount * 2);

}

bool CXThreadIntersectLFM::_IsBound(double* X, double* Y, double* TopZ, double* BottomZ, const CXVector3D& p1, const CXVector3D& p2)
{
	double minP[3], maxP[3];

	minP[0] = qMin(qMin(X[0], X[1]), qMin(X[2], X[3]));
	minP[1] = qMin(qMin(Y[0], Y[1]), qMin(Y[2], Y[3]));
	minP[2] = qMin(qMin(qMin(TopZ[0], TopZ[1]), qMin(BottomZ[0], BottomZ[1])), qMin(qMin(TopZ[2], TopZ[3]), qMin(BottomZ[2], BottomZ[3])));

	maxP[0] = qMax(qMax(X[0], X[1]), qMax(X[2], X[3]));
	maxP[1] = qMax(qMax(Y[0], Y[1]), qMax(Y[2], Y[3]));
	maxP[2] = qMax(qMax(qMax(TopZ[0], TopZ[1]), qMax(BottomZ[0], BottomZ[1])), qMax(qMax(TopZ[2], TopZ[3]), qMax(BottomZ[2], BottomZ[3])));

	if (qMax(p1[0], p2[0]) < minP[0] || qMin(p1[0], p2[0]) > maxP[0] ||
		qMax(p1[1], p2[1]) < minP[1] || qMin(p1[1], p2[1]) > maxP[1] ||
		qMax(p1[2], p2[2]) < minP[2] || qMin(p1[2], p2[2]) > maxP[2])
		return false;

	else
		return true;
}

int CXThreadIntersectLFM::_GetZ(int iTop, int iMiddle, int iBottom, double** p2DData, double* Z, int dataIndex, float fInvalid, float fInvalidEPS)
{
	if (qAbs(p2DData[iTop][dataIndex] - fInvalid) < fInvalidEPS)
	{
		Z[0] = Z[1] = Z[2] = 0.;
		return 0;
	}
	else
	{
		Z[0] = p2DData[iTop][dataIndex];
		Z[1] = p2DData[iMiddle][dataIndex];
		Z[2] = p2DData[iBottom][dataIndex];
		return 1;
	}
}