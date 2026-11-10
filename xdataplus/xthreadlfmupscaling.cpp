#pragma warning( push ,0 )
#include "xthreadlfmupscaling.h"
#include "xparameterupscaling.h"
#include "xlfmupscalinggeometry.h"
#include <QCoreApplication>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <numeric>
#include "xglobal.h"
#include "xmathmacro.h"
#include "xproject.h"
#include "xwellcurve.h"
#include "xwell.h"
#include "xwellpath.h"
#include "xutility.h"
#include "xlfmupscalingattribute.h"

#pragma warning( pop )

CXThreadLFMUpscaling::CXThreadLFMUpscaling(CXParameterUpscaling* pPara, CXObject* pObj)
{
	m_pPara = dynamic_cast<CXParameterUpscaling*>(pPara);
	m_pLFMUpscalingGeometry = dynamic_cast<CXLFMUpscalingGeometry*>(pObj);
	assert(m_pPara&&m_pLFMUpscalingGeometry);

	LockRead(m_pLFMUpscalingGeometry);

	_Init();

	for (int i = 0; i < m_listAlias.size(); ++i)
	{
		LockRead(m_listAlias[i]);
	}
}

CXThreadLFMUpscaling::~CXThreadLFMUpscaling()
{
	wait();

	UnlockRead(m_pLFMUpscalingGeometry);

	// unlock alias object
	for (int i = 0; i < m_listAlias.size(); ++i)
	{
		UnlockRead(m_listAlias[i]);
	}

	if (IsStopped())
	{
		qDeleteAll(m_listOutput);
		m_listOutput.clear();
	}
}

void CXThreadLFMUpscaling::_Init()
{
	m_iAverageMethod = m_pPara->GetAverageMethod();

	std::vector<QUuid> vecAlias = m_pPara->GetVecAliasID();
	for (int i = 0; i < vecAlias.size(); ++i)
	{
		CXObject* pAliasObj = ::GetObjectByID(vecAlias[i]);
		if (pAliasObj)
			m_listAlias.append(pAliasObj);
	}
}

void CXThreadLFMUpscaling::RunThread()
{
	if (m_listAlias.isEmpty())
	{
		this->EmitGeneralErrorMsg("Cannot find corresponding curves");
		return;
	}

	this->EmitSetWindowName("Upscale Well Curve");
	this->EmitSetTaskName("Calculating...");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	for (int i = 0; i < m_listAlias.size(); ++i)
	{
		if (!_CalcOneAlis(i))
			return;
	}

	if (IsStopped())
		return;
	
	if (m_listOutput.isEmpty())
	{
		this->EmitGeneralErrorMsg("None of corresponding curves has been found.");
		return;
	}
}

bool CXThreadLFMUpscaling::_CalcOneAlis(int iAliasIndex)
{
	CXObject* pAliasObj = m_listAlias[iAliasIndex];

	// attribute
	CXLFMUpscalingAttribute* pAttribute = new CXLFMUpscalingAttribute(m_pLFMUpscalingGeometry, pAliasObj->GetObjectName());

	QList<QUuid> vecWellID = m_pLFMUpscalingGeometry->GetAllWellID();
	for (int i = 0; i < vecWellID.size(); ++i)
	{
		if (IsStopped())
		{
			delete pAttribute;
			return false;
		}
		else
		{
			this->EmitUpdateProgress(iAliasIndex*vecWellID.size() + i, m_listAlias.size()*vecWellID.size());
		}

		// find well
		CXWell* pWell = dynamic_cast<CXWell*>(::GetObjectByID(vecWellID[i]));
		if (!pWell)
			continue;

		// find the alias curve
		CXWellCurve* pCurve = NULL;
		QList<CXObject*> listChild = pWell->GetChildren(EXWellCurve, false);
		for (int ii = 0; ii < listChild.size(); ++ii)
		{
			CXWellCurve* pCurveTmp = dynamic_cast<CXWellCurve*>(listChild[ii]);
			if (pCurveTmp && pCurveTmp->GetAliasID() == pAliasObj->GetObjectID())
			{
				pCurve = pCurveTmp;
				break;
			}
		}

		// 
		if (!pCurve)
			continue;

		// curve value
		double dMDStart = pCurve->GetStart();
		double dMDEnd = pCurve->GetStop();
		double dMDStep = pCurve->GetStep();
		int nSampleNum = (int) pCurve->GetPointNumber();
		double* pCurveData = pCurve->GetData();

		vector<double> vecMD(nSampleNum);
		for (int iMD = 0; iMD < nSampleNum; ++iMD)
		{
			vecMD[iMD] = dMDStart + iMD*dMDStep;
		}

		double dInvEPS = ::GetEPSofInvalidData(::g_dInvalidData);

		// cell info
		vector<double> vecTopMD, vecBotMD;
		m_pLFMUpscalingGeometry->GetOneWellInfo(vecWellID[i], vecTopMD, vecBotMD);
		int nCellNum = (int)vecTopMD.size();

		// upscaling
		vector<double> vecUpscalingData(nCellNum);
		for (int k = 0; k < nCellNum; ++k)
		{
			double dTopMD = vecTopMD[k];
			double dBotMD = vecBotMD[k];

			if (dTopMD < dMDStart || dBotMD > dMDEnd)
			{
				vecUpscalingData[k] = ::g_dInvalidData;
				continue;
			}

			int iTopIndex = NXUtility::GetBinarySearchIndex<double>(nSampleNum, &vecMD[0], dTopMD);
			int iBotIndex = NXUtility::GetBinarySearchIndex<double>(nSampleNum, &vecMD[0], dBotMD);

			vecUpscalingData[k] = _CalcOneSement(nSampleNum, pCurveData, iTopIndex, iBotIndex);			
		}

		pAttribute->AddOneWell(vecWellID[i], vecUpscalingData);
	}

	if (pAttribute->GetAllWellList().isEmpty())
	{
		delete pAttribute;	
	}
	else
	{
		m_listOutput.append(pAttribute);
	}

	return true;

}

double CXThreadLFMUpscaling::_CalcOneSement(int nSampleNum, double* pCurveData, int iTop, int iBot)
{
	double dValue = ::g_dInvalidData;
	double dInvEPS = ::GetEPSofInvalidData(g_dInvalidData);

	std::vector<double> vecData;
	for (int i = iTop; i <= iBot; ++i)
	{
		if (qAbs(pCurveData[i] - g_dInvalidData) > dInvEPS)
		{
			vecData.push_back(pCurveData[i]);
		}
	}

	int nSize = (int)vecData.size();
	if (0==nSize)
		return dValue;

	if (m_iAverageMethod == CXParameterUpscaling::eArithemtic)
	{
		dValue = std::accumulate(vecData.begin(), vecData.end(), 0.);
		dValue /= vecData.size();
	}
	else if (m_iAverageMethod == CXParameterUpscaling::eGeometric)
	{
		dValue = 1.;
		for (int i = 0; i < vecData.size(); ++i)
			dValue *= qAbs(vecData[i]);

		dValue = pow(dValue, 1. / vecData.size());
	}
	else if (m_iAverageMethod == CXParameterUpscaling::eRMS)
	{
		dValue = std::inner_product(vecData.begin(), vecData.end(), vecData.begin(), 0.) / vecData.size();
		dValue = sqrt(dValue);
	}
	else if (m_iAverageMethod == CXParameterUpscaling::eMedian)
	{
		dValue = NXUtility::Select(&vecData[0], (int)vecData.size(), vecData.size() / 2);
	}

	return dValue;
}


