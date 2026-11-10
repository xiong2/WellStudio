#pragma warning( push ,0 )
#include "xthreadextracthorizonatt.h"
#include "xparameterextracthorizonatt.h"
#include "x3dhorizon.h"
#include "xseismicdatavolume.h"
#include <QCoreApplication>
#include <QMultiMap>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <numeric>
#include "xglobal.h"
#include "xmathmacro.h"
#include "xfunctiontemplate.h"
#include "xproject.h"
#include "xutility.h"
#include <QFile>
#include "xregulardatareader.h"
#include "xsysteminfo.h"
#include <qtconcurrentmap.h>

#pragma warning( pop )

CXThreadExtractHorizonAtt::CXThreadExtractHorizonAtt(CXParameterExtractHorizonAtt* pPara)
{
	m_pPara = pPara;
	m_pParent = nullptr;

	_Init();
}

CXThreadExtractHorizonAtt::~CXThreadExtractHorizonAtt()
{
	wait();

	for (int i = 0; i < m_vecInDV.size(); ++i)
	{
		UnlockRead(m_vecInDV[i]);
	}
	if (m_pParent)
	{
		UnlockRead(m_pParent);
	}


	if (IsStopped())
	{
		for (int i = 0; i < m_vecOutputAtt.size(); ++i)
		{
			QFile::remove(m_vecOutputAtt[i]->GetDataFileName());
		}
		qDeleteAll(m_vecOutputAtt);
		m_vecOutputAtt.clear();

	}
}

void CXThreadExtractHorizonAtt::_Init()
{
	// data volumes
	vector<QUuid> vecDVID = m_pPara->GetVecDVID();
	for (int i = 0; i < vecDVID.size(); ++i)
	{
		m_vecInDV.push_back(dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(vecDVID[i])));
	}
	for (int i = 0; i < m_vecInDV.size(); ++i)
	{
		LockRead(m_vecInDV[i]);
	}

	// horizons
	m_pParent = dynamic_cast<CX3DHorizon*>(::GetObjectByID(m_pPara->GetHorizonID()));
	if (m_pParent)
	{
		LockRead(m_pParent);
	}
}


CX3DHorizon* CXThreadExtractHorizonAtt::_CreateAtt(int iDV)
{
	CX3DHorizon* pHorizon = new CX3DHorizon(*m_pParent);
	pHorizon->SetObjectType(EX3DHorizonAtt);
	pHorizon->SetObjectName(m_pPara->GetPrefix() + m_vecInDV[iDV]->GetObjectName());

	return pHorizon;
}

bool CXThreadExtractHorizonAtt::_Calc(int iDV)
{
	CXSeismicDataVolume* pDV = m_vecInDV[iDV];

	CXSeismicUTMTool utmHor = m_pParent->GetUTM();
	CXSeismicUTMTool utmDV = m_vecInDV[iDV]->GetUTM();

	int nIHor = utmHor.GetNI();
	int nJHor = utmHor.GetNJ();

	float fInvalid = ::g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);

	int nKDV = pDV->GetSamplingQty();
	double dSamplingStart, dSamplingEnd, dSamplingRate;
	pDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

	CXRegularDataReader<float> dvReader(pDV->GetTraceFileName(), pDV->GetInlineQty(),
		pDV->GetXlineQty(), nKDV);

	if (!dvReader.Open())
	{
		this->EmitGeneralErrorMsg("Cannot open the seismic data to read.");
		return false;
	}

	int iInline, iXline, ii, jj;
	vector<float> vecData(nIHor*nJHor, fInvalid);
	vector<float> vecTrace(nKDV);
	CXParameterExtractHorizonAtt::EMethodType eType = static_cast<CXParameterExtractHorizonAtt::EMethodType>(m_pPara->GetMethodType());
	double dTopShift = m_pPara->GetTopShift();
	double dBotShift = m_pPara->GetBottomShift();

	float* pGeoData = m_pParent->GetData();

	float fGeometry;
	for (int i = 0; i < nIHor; ++i)
	{
		if (IsStopped())
			return false;
		else
		{
			this->EmitUpdateProgress(iDV*nIHor+i, m_vecInDV.size()*nIHor);
		}


		for (int j = 0; j < nJHor; ++j)
		{
			fGeometry = pGeoData[i*nJHor+j];
			if (qAbs(fGeometry - fInvalid) < fInvalidEPS)
				continue;

			utmHor.IJToLine(i, j, iInline, iXline);
			if (!utmDV.LineToIJ(iInline, iXline, ii, jj))
				continue;

			if (!dvReader.ReadUVTrace(ii, jj, &vecTrace[0]))
			{
				this->EmitGeneralErrorMsg("Cannot read the seismic data from the disk.");
				return false;
			}

			double dOffset = (fGeometry - dSamplingStart) / dSamplingRate;
			int iOffset = static_cast<int>(dOffset);
			if (iOffset < 0 || iOffset >= nKDV)
				continue;

			int kMin, kMax;
			if (eType == CXParameterExtractHorizonAtt::eInstant)
			{
				kMin = iOffset;
				kMax = iOffset + 1;
				if (kMax >= nKDV)
				{
					vecData[i*nJHor + j] = vecTrace[nKDV - 1];
					continue;
				}

				if (qAbs(vecTrace[kMin] - fInvalid) < fInvalidEPS ||
					qAbs(vecTrace[kMax] - fInvalid) < fInvalidEPS)
				{
					if (dOffset - kMin < kMax - dOffset)
					{
						vecData[i*nJHor + j] = vecTrace[kMin];
					}
					else
					{
						vecData[i*nJHor + j] = vecTrace[kMax];
					}
				}
				else
				{
					vecData[i*nJHor + j] = vecTrace[kMin] * (kMax - dOffset) + vecTrace[kMax] * (dOffset - kMin);
				}
			}
			else
			{
				kMin = static_cast<int>((fGeometry+ dTopShift)/ dSamplingRate);
				kMax = static_cast<int>((fGeometry + dBotShift) / dSamplingRate);
				kMin = qBound(0, kMin, nKDV - 1);
				kMax = qBound(0, kMax, nKDV - 1);
				if (kMin > kMax)
					qSwap(kMin, kMax);

				double dSum = 0.;
				int iCount = 0;
				for (int k = kMin; k <= kMax; ++k)
				{
					if (qAbs(vecTrace[k] - fInvalid) > fInvalidEPS)
					{
						dSum += vecTrace[k];
						++iCount;
					}
				}
				if (!iCount)
					vecData[i*nJHor + j] = dSum / iCount;
			}
		}
	}

	// add new horizon
	CX3DHorizon* pHorizon = _CreateAtt(iDV);
	memcpy(pHorizon->GetData(), &vecData[0], sizeof(float)*nIHor*nJHor);
	m_vecOutputAtt.push_back(pHorizon);

	return true;

}

void CXThreadExtractHorizonAtt::RunThread()
{
	if (!m_pParent)
	{
		this->EmitGeneralErrorMsg("The selected horizon has been removed.");
		return;
	}

	if (m_vecInDV.empty())
	{
		this->EmitGeneralErrorMsg("The selected data volumes have been removed.");
		return;
	}

	this->EmitSetWindowName("Extract 3-D Horizon Attributes");
	this->EmitSetTaskName("Calculating");
	this->EmitStartComputing();
	QCoreApplication::instance()->processEvents();

	for (int i = 0; i < m_vecInDV.size(); ++i)
	{
		if (!_Calc(i))
			return;
	}
}




