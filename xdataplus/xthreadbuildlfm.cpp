#pragma warning (push,0)
#include "xthreadbuildlfm.h"
#include "xparameterbuildlfm.h"
#include "x3dhorizon.h"
#include "xlfmgeometry.h"
#include "xproject.h"
#include "x3dsurvey.h"
#include "x2dpolygon.h"
#include "xsurfaceapi.h"
#include "xgraphicsapi.h"
#include "xglobal.h"
#include "xmathmacro.h"
#include "xregulardatawriter.h"
#include "xutility.h"
#include <cassert>
#include <QCoreApplication>
#include <QMap>
#pragma warning(pop)

CXThreadBuildLFM::CXThreadBuildLFM(CXParameterBuildLFM *pPara)
	:m_pPara(pPara)
{
	assert(m_pPara);

	m_2DRawData = NULL;

	m_p2DData = NULL;
	m_nTotalSlice = 0;

	m_pLFM = NULL;


	// Control polygon
	m_nPolygonDataNum = 0;
	m_pPolygonData = NULL;
	CX2DPolygon* pPolygon = dynamic_cast<CX2DPolygon*>(::GetObjectByID(m_pPara->GetPolygonID()));
	if (pPolygon)
	{
		m_pPara->SetPolygonName(pPolygon->GetObjectName());
		double* pXYData = pPolygon->GetData(m_nPolygonDataNum);
		if (m_nPolygonDataNum > 0 && pXYData)
		{
			m_pPolygonData = new double[m_nPolygonDataNum];
			memcpy(m_pPolygonData, pXYData, sizeof(double)*m_nPolygonDataNum);
		}
	}
}

CXThreadBuildLFM::~CXThreadBuildLFM()
{
	// horizons
	qDeleteAll(m_vecInput3DHorizon);
	m_vecInput3DHorizon.clear();

	// polygon data
	if (m_pPolygonData) { delete[]m_pPolygonData; m_pPolygonData = NULL; }

	// raw data
	if (m_2DRawData)	{ NXUtility::Free2DArray<float>(m_2DRawData, m_nRawNum); m_2DRawData = NULL; }

	// model data
	if (m_p2DData)		{ NXUtility::Free2DArray<float>(m_p2DData, m_nTotalSlice); m_p2DData = NULL; }


	if (IsStopped())
	{
		if (m_pLFM)
		{
			QFile::remove(m_pLFM->GetDataFileName());
			delete m_pLFM;
		}
		m_pLFM = NULL;
	}
}

void CXThreadBuildLFM::RunThread()
{
	if (IsStopped())
		return;

	QString strWindowName = "Build FrameWork of Low Frequency Model ";
	this->EmitSetWindowName(strWindowName);
	QCoreApplication::instance()->processEvents();
	this->EmitStartComputing();


	this->EmitSetTaskName(QString("Prepare data to build low frequency model..."));
	QCoreApplication::instance()->processEvents();

	// Calculate UTM 	 
	if (!_Initialization() || !_CreateUTM())
		return;

	// Calculate the boundary
	if (!_GetValidMap() || !_ApplyPolygon())
		return;

	// Initialize the data
	if (!_GetVecDataMatrix() || !_SetInputSurfaceIndex())
		return;

	this->EmitResetProgressBar();
	this->EmitSetTaskName(QString("Calculate geometry for low frequency model..."));
	QCoreApplication::instance()->processEvents();

	// Calculate strata-grid geometry
	if (!_SetSliceData() || !_CreateStrataGrid())
		return;
}


bool CXThreadBuildLFM::_Initialization()
{
	//	survey
	CX3DSurvey* p3DSurvey = dynamic_cast<CX3DSurvey*>(::GetObjectByID(m_pPara->GetSurveyID()));
	{
		if (!p3DSurvey)
		{
			QString strErrorMsg = "The the corresponding survey does not exist.!";
			EmitGeneralErrorMsg(strErrorMsg);
			return false;
		}
	}
	CXSeismicUTMTool& surveyUTM = p3DSurvey->GetUTM();

	// Input horizons
	std::vector<QUuid> vecHorizonID = m_pPara->GetVecHorizonID();
	for (int i = 0; i < vecHorizonID.size(); ++i)
	{		
		CX3DHorizon* p3DHorizon = dynamic_cast<CX3DHorizon*>(::GetObjectByID(vecHorizonID[i]));
		if (p3DHorizon)
		{
			CXSeismicUTMTool& horizonUTM = p3DHorizon->GetUTM();
			if (surveyUTM.Equals(&horizonUTM))
			{
				CX3DHorizon* pNewHorizon = new CX3DHorizon(*p3DHorizon);
				m_vecInput3DHorizon.push_back(pNewHorizon);
			}
			else
			{
				m_vecInput3DHorizon.push_back(CXSurfaceAPI::InterpolateWithUTM(p3DHorizon, &surveyUTM));
			}
		}
	}

	if (m_vecInput3DHorizon.size() < vecHorizonID.size())
	{
		QString strErrorMsg = "One of selected horizons was deleted, please re-create a low frequency model!";
		EmitGeneralErrorMsg(strErrorMsg);
		return false;
	}

	// Sort input horizon according to the Z max values
	if (m_vecInput3DHorizon.size() >= 2)
	{
		QMap<double, CX3DHorizon*> mapZToHorizon;
		for (int i = 0; i < m_vecInput3DHorizon.size(); ++i)
		{
			double dBottomZ = m_vecInput3DHorizon[i]->GetZMax();
			if (i == 0)
				dBottomZ += m_pPara->GetTopShift();
			else if (i == m_vecInput3DHorizon.size() - 1)
				dBottomZ += m_pPara->GetBottomShift();

			mapZToHorizon.insert(dBottomZ, m_vecInput3DHorizon[i]);
		}

		// sort
		m_vecInput3DHorizon.clear();
		QMap<double, CX3DHorizon*>::iterator it;
		for (it = mapZToHorizon.begin(); it != mapZToHorizon.end(); ++it)
		{
			m_vecInput3DHorizon.push_back(it.value());
		}
	}

	m_nRawNum = qMax(2, (int)m_vecInput3DHorizon.size());

	return true;
}

bool CXThreadBuildLFM::_CreateUTM()
{
	//	survey
	CX3DSurvey* p3DSurvey = dynamic_cast<CX3DSurvey*>(::GetObjectByID(m_pPara->GetSurveyID()));
	{
		if (!p3DSurvey)
		{
			QString strErrorMsg = "The the corresponding survey does not exist.!";
			EmitGeneralErrorMsg(strErrorMsg);
			return false;
		}
	}

	CXSeismicUTMTool& surveyUTM = p3DSurvey->GetUTM();

	int iOldInlineNumStart, iOldInlineNumEnd, iOldInlineNumInc, iOldXlineNumStart, iOldXlineNumEnd, iOldXlineNumInc;
	int iNewInlineNumStart, iNewInlineNumEnd, iNewInlineNumInc, iNewXlineNumStart, iNewXlineNumEnd, iNewXlineNumInc;
	surveyUTM.GetLineNumRange(iOldInlineNumStart, iOldInlineNumEnd, iOldInlineNumInc, iOldXlineNumStart, iOldXlineNumEnd, iOldXlineNumInc);

	// Get the line range
	if (m_nPolygonDataNum != 0)
	{
		// Get line range of the polygon
		surveyUTM.XYToLine(m_pPolygonData[0], m_pPolygonData[1], iNewInlineNumStart, iNewXlineNumStart);
		iNewInlineNumEnd = iNewInlineNumStart;
		iNewXlineNumEnd = iNewXlineNumStart;

		int iInlineTmp, iXlineTmp;
		for (int i = 2; i < m_nPolygonDataNum; i+=2)
		{
			surveyUTM.XYToLine(m_pPolygonData[i], m_pPolygonData[i+1], iInlineTmp, iXlineTmp);
			iNewInlineNumStart = qMin(iInlineTmp, iNewInlineNumStart);
			iNewInlineNumEnd = qMax(iInlineTmp, iNewInlineNumEnd);
			iNewXlineNumStart = qMin(iXlineTmp, iNewXlineNumStart);
			iNewXlineNumEnd = qMax(iXlineTmp, iNewXlineNumEnd);
		}

		// Get the intersection between the survey and the polygon
		// the line increment might be negative
		iNewInlineNumStart = qMax(iNewInlineNumStart, m_pPara->GetMinInlineNum());
		iNewInlineNumEnd = qMin(iNewInlineNumEnd, m_pPara->GetMaxInlineNum());
		iNewXlineNumStart = qMax(iNewXlineNumStart, m_pPara->GetMinXlineNum());
		iNewXlineNumEnd = qMin(iNewXlineNumEnd, m_pPara->GetMaxXlineNum());

		// Tell if intersection is valid
		if (iNewInlineNumStart > iNewInlineNumEnd || iNewXlineNumStart > iNewXlineNumEnd)
		{
			QString strErrorMsg = "The survey and the selected polygon do not match!";
			EmitGeneralErrorMsg(strErrorMsg);
			return false;
		}
	}
	else
	{
		iNewInlineNumStart = m_pPara->GetMinInlineNum();
		iNewInlineNumEnd = m_pPara->GetMaxInlineNum();
		iNewXlineNumStart = m_pPara->GetMinXlineNum();
		iNewXlineNumEnd = m_pPara->GetMaxXlineNum();
	}

	// Get the line increment
	iNewInlineNumInc = surveyUTM.GetInlineIncrement();
	iNewXlineNumInc = surveyUTM.GetCrosslineIncrement();

	iNewInlineNumStart = ((iNewInlineNumStart - iOldInlineNumStart) / iNewInlineNumInc)*iNewInlineNumInc + iOldInlineNumStart;
	iNewXlineNumStart = ((iNewXlineNumStart - iOldXlineNumStart) / iNewXlineNumInc)*iNewXlineNumInc + iOldXlineNumStart;

	int nNewInLineNumQty = (iNewInlineNumEnd - iNewInlineNumStart) / iNewInlineNumInc + 1;
	int nNewXlineNumQty = (iNewXlineNumEnd - iNewXlineNumStart) / iNewXlineNumInc + 1;

	// Get the new seismic UTM tool
	m_utmLFM = surveyUTM;
	m_utmLFM.Resize(iNewInlineNumStart, iNewXlineNumStart, nNewInLineNumQty, nNewXlineNumQty, iNewInlineNumInc, iNewXlineNumInc);

	return true;
}

// Get valid map
bool CXThreadBuildLFM::_GetValidMap()
{
	EmitUpdateProgress(5, 100);

	// Strata-grid UTM
	int nSize = m_utmLFM.GetNI()*m_utmLFM.GetNJ();

	// init valid map
	m_bitMap.resize(nSize);
	m_bitMap.fill(true);
	

	// Interpolation
	int nHorizonNum = (int)m_vecInput3DHorizon.size();
	for (int i = 0; i < nHorizonNum; ++i)
	{
		CXSurfaceAPI::Interpolate(m_vecInput3DHorizon[i]);

		this->EmitUpdateProgress(5 + (i + 1) * 10 / nHorizonNum, 10);
	}	

	return true;
}

bool CXThreadBuildLFM::_ApplyPolygon()
{
	// No polygon
	if (m_nPolygonDataNum == 0)
	{
		emit this->EmitUpdateProgress(20, 100);
		return true;
	}

	// Strata-grid UTM
	int nI = m_utmLFM.GetNI();
	int nJ = m_utmLFM.GetNJ();

	// Polygon data
	double dX, dY;
	for (int i = 0; i < nI; ++i)
	{
		for (int j = 0; j < nJ; ++j)
		{
			m_utmLFM.IJToXY(i, j, dX, dY);
			if (!CXGraphicsAPI::IsPointInsidePolygon((int)m_nPolygonDataNum/2, dX, dY, m_pPolygonData))
				m_bitMap.clearBit(i*nJ + j);
				
		}
	}

	this->EmitUpdateProgress(20, 100);

	return true;
}

bool CXThreadBuildLFM::_GetVecDataMatrix()
{
	if (IsStopped())
		return false;

	// Strata-grid UTM
	int iInlineStart, iInlineEnd, iInlineInc, iXlineStart, iXlineEnd, iXlineInc;
	m_utmLFM.GetLineNumRange(iInlineStart, iInlineEnd, iInlineInc, iXlineStart, iXlineEnd, iXlineInc);
	int nI = m_utmLFM.GetNI();
	int nJ = m_utmLFM.GetNJ();
	int nSize = nI*nJ;

	// Raw horizons   
	int nHorizonNum = (int)m_vecInput3DHorizon.size();

	//Create allocated memory for raw horizons
	m_2DRawData = NXUtility::New2DArray<float>(m_nRawNum, nSize);
	if (!m_2DRawData)
	{
		this->EmitMemoryNotEnough();
		return false;
	}

	// progress
	this->EmitUpdateProgress(25, 100);
		
	// Set the data
	for (int iHor = 0; iHor < nHorizonNum; ++iHor)
	{
		if (IsStopped())
			return false;

		CX3DHorizon* pHorizon = m_vecInput3DHorizon[iHor];
		CXSeismicUTMTool& utmHorizon = pHorizon->GetUTM();

		int nJHorizon = utmHorizon.GetNJ();
		float* pHorizonData = pHorizon->GetData();

		int iInline, iXline, iI, iJ;
		for (int i = 0; i < nI; ++i)
		{
			for (int j = 0; j < nJ; ++j)
			{
				if (m_bitMap.testBit(i*nJ + j))
				{
					m_utmLFM.IJToLine(i, j, iInline, iXline);
					utmHorizon.LineToIJ(iInline, iXline, iI, iJ);
					m_2DRawData[iHor][i*nJ + j] = pHorizonData[iI*nJHorizon + iJ];
				}
				else
				{
					m_2DRawData[iHor][i*nJ + j] = (float)::g_dInvalidData;
				}
			}
		}

		this->EmitUpdateProgress(25 + 10 * (iHor + 1) / nHorizonNum, 100);
	}

	return true;
}

bool CXThreadBuildLFM::_SetInputSurfaceIndex()
{
	if (IsStopped())
		return false;

	int nHorizonNum = m_vecInput3DHorizon.size();
	assert(nHorizonNum != 0);

	int nI = m_utmLFM.GetNI();
	int nJ = m_utmLFM.GetNJ();
	int nSize = nI*nJ;

	// set data
	if (nHorizonNum == 1)
	{
		// Shift top and bottom
		memcpy(m_2DRawData[1], m_2DRawData[0], sizeof(float)*nSize);		
	}
	_ShiftTopAndBottomValues();

	for (int iHor = 1; iHor < m_nRawNum; ++iHor)
	{
		for (int i = 0; i < nSize; ++i)
		{
			if (!m_bitMap.testBit(i))
				continue;

			if (m_2DRawData[iHor][i] < m_2DRawData[iHor - 1][i])
				m_2DRawData[iHor][i] = m_2DRawData[iHor - 1][i];
		}
	}

	// set surface index
	if (nHorizonNum == 1)
	{			
		m_listSurfaceIndex.append(0);
		m_nTotalSlice = m_pPara->GetVecSliceNum().front();
		m_listSurfaceIndex.append((unsigned short)m_nTotalSlice - 1);
	}
	else
	{
		// Shift top and bottom
		m_listSurfaceIndex.push_back(0);
		m_nTotalSlice = 1;

		std::vector<int> vecSliceNum = m_pPara->GetVecSliceNum();
		for (int i = 0; i < nHorizonNum - 1; ++i)
		{
			// determine the slice number by the thickness
			if (m_pPara->GetVecContactType().at(i) != CXParameterBuildLFM::eProportional)
			{
				// Get max height between two adjacent slices
				float* pTopData = m_2DRawData[i];
				float* pBottomData = m_2DRawData[i + 1];
				float fMaxHeight = 0.0f;
				for (int ii = 0; ii < nSize; ++ii)
				{
					fMaxHeight = qMax(fMaxHeight, qAbs(pBottomData[ii] - pTopData[ii]));
				}

				vecSliceNum.at(i) = (int)(fMaxHeight / m_pPara->GetVecThickness().at(i) + 1);
			}

			m_nTotalSlice += vecSliceNum.at(i) - 1;
			m_listSurfaceIndex.append((unsigned short)m_nTotalSlice - 1);
		}
		m_pPara->SetVecSliceNum(vecSliceNum);

		if (m_nTotalSlice == 1)
		{
			QString strErrMsg = "The selected thickness is invalid. It should be less than the \n"
								"maximum thickness between the top and bottom horizons!";
			EmitGeneralErrorMsg(strErrMsg);
			return false;
		}
	}

	this->EmitUpdateProgress(40, 100);
	return true;
}

void CXThreadBuildLFM::_ShiftTopAndBottomValues()
{
	int nSize = m_utmLFM.GetNI()*m_utmLFM.GetNJ();

	// Shift top and bottom
	float fTopShift = m_pPara->GetTopShift();
	float fBottomShift = m_pPara->GetBottomShift();
	if (fTopShift > fBottomShift)
		qSwap(fTopShift, fBottomShift);

	for (int i = 0; i < nSize; ++i)
	{
		if (m_bitMap.testBit(i))
		{
			m_2DRawData[0][i] += fTopShift;
			m_2DRawData[m_nRawNum-1][i] += fBottomShift;
		}
	}
}

bool CXThreadBuildLFM::_SetSliceData()
{
	if (IsStopped())
		return false;

	int nI = m_utmLFM.GetNI();
	int nJ = m_utmLFM.GetNJ();
	int nK = m_nTotalSlice;
	int nSize = nI*nJ;

	m_p2DData = NXUtility::New2DArray<float>(nK, nI*nJ);
	if (NULL == m_p2DData)
	{
		EmitMemoryNotEnough();
		return false;
	}

	// Set data for indexed surface
	for (int i = 0; i < m_listSurfaceIndex.size(); ++i)
	{
		int iHorizonIndex = m_listSurfaceIndex.at(i);
		memcpy(m_p2DData[iHorizonIndex], m_2DRawData[i], sizeof(float)*nSize);
	}

	this->EmitUpdateProgress(45, 100);

	// Set the slice data between two adjacent indexed horizons
	int nZone = m_listSurfaceIndex.size() - 1;
	int nCurrentSliceIndex = 0;
	for (int i = 0; i < nZone; ++i)
	{
		int iTopIndex = m_listSurfaceIndex.at(i);
		int iBottomIndex = m_listSurfaceIndex.at(i + 1);
		float* pTopData = m_p2DData[iTopIndex];
		float* pBottomData = m_p2DData[iBottomIndex];
		int nMiddleSliceInterval = iBottomIndex - iTopIndex;
		int nType = m_pPara->GetVecContactType().at(i);

		if (nType == CXParameterBuildLFM::eProportional)
		{
			// Get interval matrix
			float* pTmpData = new float[nSize];
			for (int ii = 0; ii < nSize; ++ii)
			{
				if (m_bitMap.testBit(ii))
					pTmpData[ii] = (pBottomData[ii] - pTopData[ii]) / nMiddleSliceInterval;
			}

			// Set each slice data
			for (int iSlice = 1; iSlice < nMiddleSliceInterval; ++iSlice)
			{
				nCurrentSliceIndex = iTopIndex + iSlice;
				if (IsStopped())
				{
					delete[]pTmpData;
					return false;
				}
				else
					this->EmitUpdateProgress(45 + nCurrentSliceIndex * 55 / m_nTotalSlice, 100);

				float* pSliceData = m_p2DData[nCurrentSliceIndex];
				for (int ii = 0; ii < nSize; ++ii)
				{
					if (!m_bitMap.testBit(ii))
						pSliceData[ii] = (float)::g_dInvalidData;
					else
					{
						pSliceData[ii] = pTopData[ii] + pTmpData[ii] * iSlice;
					}
				}
			}   // iSlice

			delete[]pTmpData;
		}
		else if (nType == CXParameterBuildLFM::eTopConformable)
		{
			float fSliceThickness = m_pPara->GetVecThickness().at(i);

			// Set each slice data
			float fTmp;
			for (int iSlice = 1; iSlice < nMiddleSliceInterval; ++iSlice)
			{
				nCurrentSliceIndex = iTopIndex + iSlice;
				if (IsStopped())
					return false;
				else
					this->EmitUpdateProgress(45 + nCurrentSliceIndex * 55 / m_nTotalSlice, 100);

				float* pSliceData = m_p2DData[iTopIndex + iSlice];
				float fThickness = iSlice*fSliceThickness;
				for (int ii = 0; ii < nSize; ++ii)
				{
					if (!m_bitMap.testBit(ii))
						pSliceData[ii] = (float)::g_dInvalidData;
					else
					{
						float fTopValue = pTopData[ii];
						float fBottomValue = pBottomData[ii];
						if (fTopValue < fBottomValue)
							qSwap(fTopValue, fBottomValue);

						fTmp = fTopValue - fThickness;
						if (fTmp < fBottomValue)
							fTmp = fBottomValue;

						pSliceData[ii] = fTmp;
					}
				}
			}   //iSlice
		}
		else if (nType == CXParameterBuildLFM::eBottomConformable)
		{
			float fSliceThickness = m_pPara->GetVecThickness().at(i);

			// Set each slice data
			float fTmp;
			for (int iSlice = 1; iSlice < nMiddleSliceInterval; ++iSlice)
			{
				nCurrentSliceIndex = iTopIndex + iSlice;
				if (IsStopped())
					return false;
				else
					this->EmitUpdateProgress(45 + nCurrentSliceIndex * 55 / m_nTotalSlice, 100);

				float* pSliceData = m_p2DData[nCurrentSliceIndex];
				float pThickness = (nMiddleSliceInterval - iSlice)*fSliceThickness;

				for (int ii = 0; ii < nSize; ++ii)
				{
					if (!m_bitMap.testBit(ii))
						pSliceData[ii] = (float)::g_dInvalidData;
					else
					{
						float fTopValue = pTopData[ii];
						float fBottomValue = pBottomData[ii];
						if (fTopValue < fBottomValue)
							qSwap(fTopValue, fBottomValue);

						fTmp = fBottomValue + pThickness;
						if (fTmp > fTopValue)
							fTmp = fTopValue;

						pSliceData[ii] = fTmp;
					}
				}
			}   //iSlice
		}
	}

	return true;
}

bool CXThreadBuildLFM::_CreateStrataGrid()
{
	//Create strata-grid
	m_pLFM = new CXLFMGeometry(m_pPara->GetSurveyID(), m_utmLFM, m_nTotalSlice, m_pPara->GetLFMName());

	// set a few parameters
	vector<int> vecHorizonIndex;
	for (int i = 0; i < m_listSurfaceIndex.size(); ++i)
		vecHorizonIndex.push_back(m_listSurfaceIndex[i]);

	m_pLFM->SetHorizonIndex(vecHorizonIndex);
	m_pLFM->SetZoneNameList(m_pPara->GetZoneNameList());

	QString strDataFile = m_pLFM->GetDataFileName();
	CXRegularDataWriter<float> writer(strDataFile, m_nTotalSlice, m_utmLFM.GetNI(), m_utmLFM.GetNJ());
	if (!writer.Open())
	{
		this->EmitGeneralErrorMsg("Cannot write data to the disk.");
		return false;
	}

	for (int k = 0; k < m_nTotalSlice; ++k)
	{
		writer.WriteUSection(k, m_p2DData[k]);
	}
	writer.Close();

	return true;
}