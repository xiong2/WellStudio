#include "xavazruger.h"
#include <cmath>
#include <cassert>
#include "xutility.h"
#include "xglobal.h"
#include "xmathmacro.h"
#include "xfunctiontemplate.h"
#include "xblas.h"
#include "mkl.h"
#include "xnlsqmethod.h"


void Function_nls_ruger(int* m, int *n, double* x, double* f, void* userData)
{
	double* pData = (double*)userData; // m azimuth and m incidence, m y's, n = 4

	for (int i = 0; i < *m; ++i)
	{
		f[i] = x[0] + sin(pData[*m + i] * M_RAD)*(x[1] + x[2] * SQR(cos((x[3] - pData[i])*M_RAD))) - pData[2 * (*m) + i];
	}
}


CXAVAZRuger::CXAVAZRuger(int nK, int nMaxFold)
{
	m_nK = nK;
	m_nMaxFold = nMaxFold;

	m_pG = nullptr;
	m_pB = nullptr;
	m_pAngle = nullptr;
	m_pAzimuth = nullptr;
	m_pValue = nullptr;

	m_pMethod = nullptr; 
	m_pX = nullptr;
	m_pUserData = nullptr;

}

CXAVAZRuger::~CXAVAZRuger()
{
	if (m_pG)		{ delete[]m_pG; }
	if (m_pB)		{ delete[]m_pB; }
	if (m_pAngle)	{ delete[]m_pAngle; }
	if (m_pAzimuth) { delete[]m_pAzimuth; }
	if (m_pValue)	{ delete[]m_pValue; }

	delete m_pMethod;
	delete[]m_pX;
	delete[]m_pUserData;
}

void CXAVAZRuger::InitInputData(int kMin, int kMax, float* pGatherData, float* pOffAzi)
{
	m_kMin = kMin;
	m_kMax = kMax;

	m_pGather = pGatherData;
	m_pOffAzi = pOffAzi;
}

bool CXAVAZRuger::InitOutputData(float* pBani, float* pAzimuth)
{
	m_pOutBani = pBani;
	m_pOutAzimuth = pAzimuth;

	// buffs
	try
	{
		m_pG = new double[m_nMaxFold * 3];
		m_pB = new double[m_nMaxFold];
		m_pAngle = new double[m_nMaxFold];
		m_pAzimuth = new double[m_nMaxFold];
		m_pValue = new double[m_nMaxFold];
	}
	catch (std::bad_alloc)
	{
		return false;
	}

	// for nls
	m_pX = new double[4];
	m_pUserData = new double[m_nMaxFold * 3];
	m_pMethod = new CXNLSQMethod;
	m_pMethod->InitWithUserData(m_nMaxFold, 4, 100, Function_nls_ruger);

	m_vecAzi.resize(m_nMaxFold);
	m_vecInc.resize(m_nMaxFold);
	m_vecData.resize(m_nMaxFold);


	return true;
}

void CXAVAZRuger::SetFold(int nFold)
{
	m_nFold = nFold;
}

void CXAVAZRuger::Calculate()
{
	// set default
	float fInvalid = ::g_dInvalidData;
	for (int k = m_kMin; k <= m_kMax; ++k)
	{
		m_pOutBani[k] = fInvalid;
		m_pOutAzimuth[k] = fInvalid;
	}

	// sort by azimuth
	m_mapAzi.clear();
	for (int iFold = 0; iFold < m_nFold; ++iFold)
	{
		m_mapAzi.insert(m_pOffAzi[2 * iFold + 1]* M_RAD, qMakePair(m_pOffAzi[2 * iFold]* M_RAD, iFold));
	}

	QList<float> listAzi = m_mapAzi.uniqueKeys();

	for (int k = m_kMin; k <= m_kMax; ++k)
	{
		int n = 0;
		for (int iAzi = 0; iAzi < listAzi.size(); ++iAzi)
		{
			QList<QPair<float, int> > listAngleIndex = m_mapAzi.values(listAzi.at(iAzi));
			if (listAngleIndex.size() < 3)
				continue;

			int m = 0, index;
			float fValue;
			for (int iAngle = 0; iAngle < listAngleIndex.size(); ++iAngle)
			{
				index = listAngleIndex[iAngle].second;
				fValue = m_pGather[index*m_nK + k];
				if (fValue == fInvalid)
					continue;

				m_pAngle[m] = listAngleIndex[iAngle].first;
				m_pValue[m] = fValue;
				++m;
			}
			if (m < 3)
				continue;

			//G (m*3)
			for (int i = 0; i < m; ++i)
			{
				m_pG[i] = 1.;
				m_pG[i + m] = SQR(sin(m_pAngle[i]));
				m_pG[i + 2*m] = m_pG[i + m]* SQR(tan(m_pAngle[i]));
			}

			//G*X=B
			LAPACKE_dgels(LAPACK_COL_MAJOR, 'N', m, 3, 1, m_pG, m, m_pValue, m);

			// noramlization
			//if (qAbs(m_pValue[0]) > M_FEPS)
			//	m_pB[n] = m_pValue[1] / m_pValue[0];
			//else
			//	m_pB[n] = m_pValue[1];

			m_pB[n] = m_pValue[1];

			m_pAzimuth[n] = listAzi[iAzi];
			++n;			
		}

		if (n < 3)
			continue;
		
		// G (n*3)
		for (int i = 0; i < n; ++i)
		{
			m_pG[i] = 1.;
			m_pG[i + n] = cos(2.*m_pAzimuth[i]);
			m_pG[i + 2 * n] = sin(2.*m_pAzimuth[i]);
		}

		LAPACKE_dgels(LAPACK_COL_MAJOR, 'N', n, 3, 1, m_pG, n, m_pB, n);

		// Bani
		m_pOutBani[k] = sqrt(m_pB[1]*m_pB[1] + m_pB[2] * m_pB[2]);

		// Azi
		m_pOutAzimuth[k] = atan2(m_pB[2], m_pB[1])*M_DEG/2. + 90.;

	}
}


void CXAVAZRuger::Calculate2()
{
	// set default
	float fInvalid = (float)::g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);
	for (int k = m_kMin; k <= m_kMax; ++k)
	{
		m_pOutBani[k] = fInvalid;
		m_pOutAzimuth[k] = fInvalid;
	}

	int m;
	for (int k = m_kMin; k <= m_kMax; ++k)
	{
		m = 0;
		for (int iFold = 0; iFold < m_nFold; ++iFold)
		{
			if (qAbs(m_pGather[iFold*m_nK + k] - fInvalid) > fInvalidEPS)
			{
				m_vecAzi[m] = m_pOffAzi[2 * iFold + 1];
				m_vecInc[m] = m_pOffAzi[2 * iFold ];
				m_vecData[m] = m_pGather[iFold*m_nK + k];
				++m;
			}			
		}

		if (m < 4)
			continue;

		// init
		// init
		m_pX[0] = m_vecData[0];
		m_pX[1] = m_vecData[0];
		m_pX[2] = 0;
		m_pX[3] = 0;

		memcpy(m_pUserData, &m_vecAzi[0], sizeof(double)*m);
		memcpy(m_pUserData+m, &m_vecInc[0], sizeof(double)*m);
		memcpy(m_pUserData+2*m, &m_vecData[0], sizeof(double)*m);


		m_pMethod->Calculate2WithUserData(m, 4, m_pX, m_pUserData);

			// Bani
		m_pOutBani[k] = m_pX[2];

		// Azi
		m_pOutAzimuth[k] = m_pX[3];
		if (m_pOutAzimuth[k] < 0)
			m_pOutAzimuth[k] = 0;
		
	}

}