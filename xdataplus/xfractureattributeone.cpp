#include "xfractureattributeone.h"
#include <cmath>
#include <cassert>
#include "xutility.h"
#include "xglobal.h"
#include "xmathmacro.h"
#include "xfunctiontemplate.h"
#include "xblas.h"
#include "mkl.h"
#include "xnlsqmethod.h"
#include <cmath>



void Function_nls(int* m, int *n, double* x, double* f, void* userData)
{
	double* pData = (double*)userData; // m azimuth and m y's

	for (int i = 0; i < *m; ++i)
	{
		f[i] = x[0] + x[1] * cos(2 * (pData[i] - x[2])*M_RAD) + x[3] * cos(4 * (pData[i] - x[2])*M_RAD) - pData[*m + i];
	}
}


CXFractureAttributeOne::CXFractureAttributeOne(int nK)
{
	m_nK = nK;

	m_pMethod = nullptr;
	m_pX = nullptr;
	m_pUserData = nullptr;
	m_pValue = nullptr;
}

CXFractureAttributeOne::~CXFractureAttributeOne()
{
	delete m_pMethod;
	delete[]m_pX;
	delete[]m_pUserData;
	delete[]m_pValue;
}

void CXFractureAttributeOne::InitMethod(int m, int n, int nMaxLoop)
{
	m_m = m;
	m_n = n;

	m_pMethod = new CXNLSQMethod;
	m_pMethod->InitWithUserData(m, n, nMaxLoop, Function_nls);

	m_pX = new double[m_n];
	m_pUserData = new double[2 * m_m];
	m_pValue = new double[m_m];
}

void CXFractureAttributeOne::InitInputData(int kMin, int kMax, float* pGatherData, double* pAzi)
{
	m_kMin = kMin;
	m_kMax = kMax;

	m_pGather = pGatherData;
	memcpy(m_pUserData, pAzi, sizeof(double)*m_m);
}

bool CXFractureAttributeOne::InitOutputData(float* pBani, float* pAzimuth)
{
	m_pOutBani = pBani;
	m_pOutAzimuth = pAzimuth;

	return true;
}

void CXFractureAttributeOne::Calculate()
{
	// set default
	float fInvalid = (float)::g_dInvalidData;
	float fEpsInvalid = ::GetEPSofInvalidData(fInvalid);

	for (int k = m_kMin; k <= m_kMax; ++k)
	{
		m_pOutBani[k] = fInvalid;
		m_pOutAzimuth[k] = fInvalid;
	}
	
	// calculate
	double xlow[4], xhigh[4];
	for (int k = m_kMin; k <= m_kMax; ++k)
	{
		// retrieve data
		bool bContinue = false;
		for (int i = 0; i < m_m; ++i)
		{
			m_pValue[i] = m_pGather[i*m_nK + k];
			if (qAbs(m_pValue[i] - fInvalid) < fEpsInvalid)
			{
				bContinue = true;
				break;
			}
			else
			{
				m_pValue[i] = log(m_pValue[i]);
			}
		}

		if (bContinue)
			continue;

		// set user data
		memcpy(m_pUserData + m_m, m_pValue, sizeof(double)*m_m);

		// low and high
		xlow[0] = -2;
		xlow[1] = -1;
		xlow[2] = -90;
		xlow[3] = -1;

		xhigh[0] = 2;
		xhigh[1] = 1;
		xhigh[2] = 90;
		xhigh[3] = 1;


		// init
		m_pX[0] = 1;
		m_pX[1] = 0.05;
		m_pX[2] = 0;
		m_pX[3] = 0.05;

		//m_pMethod->Calculate2WithUserData(m_m, 4, m_pX, m_pUserData);
		m_pMethod->Calculate3WithUserData(m_pX, xlow, xhigh, m_pUserData);

		// Bani
		m_pOutBani[k] = m_pX[1];		

		// Azi
		m_pOutAzimuth[k] = m_pX[2];
		if (m_pOutAzimuth[k] < 0)
			m_pOutAzimuth[k] = 0;
		//if (m_pOutAzimuth[k] < 0)
		//{
		//	m_pOutAzimuth[k] += 180;
		//}


		//if (m_pOutBani[k] < 0)
		//{
		//	m_pOutBani[k] = -m_pOutBani[k];
		//	m_pOutAzimuth[k] += 90;
		//}
		//if (m_pOutAzimuth[k] < 0)
		//	m_pOutAzimuth[k] += 180;

		//if (m_pOutAzimuth[k] > 180)
		//	m_pOutAzimuth[k] -= 180;

	}
}
