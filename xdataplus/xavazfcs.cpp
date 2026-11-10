#include "xavazfcs.h"
#include <cmath>
#include <cassert>
#include "xutility.h"
#include "xglobal.h"
#include "xmathmacro.h"
#include "xfunctiontemplate.h"
#include "xblas.h"
#include "mkl.h"
#include "xnlsqmethod.h"

void Function_nls_fcs(int* m, int *n, double* x, double* f, void* userData)
{
	double* pData = (double*)userData; // m azimuth m y's, n = 4

	for (int i = 0; i < *m; ++i)
	{
		f[i] = x[0] + x[1] * cos(2.*M_RAD*(x[3] - pData[i])) + x[2] * cos(4.*M_RAD*(x[3] - pData[i])) - pData[*m + i];
	}
}


CXAVAZFCs::CXAVAZFCs(int nK, int nMaxFold, int nIncidence)
{
	m_nK = nK;
	m_nMaxFold = nMaxFold;

	m_nIncidence = nIncidence;

	m_pMethod = nullptr;
	m_pX = nullptr;
	m_pUserData = nullptr;
}

CXAVAZFCs::~CXAVAZFCs()
{
	delete m_pMethod;
	delete[]m_pX;
	delete[]m_pUserData;
}

void CXAVAZFCs::InitInputData(int kMin, int kMax, float* pGatherData, float* pOffAzi)
{
	m_kMin = kMin;
	m_kMax = kMax;

	m_pGather = pGatherData;
	m_pOffAzi = pOffAzi;

	// for nls
	m_pX = new double[4];
	m_pUserData = new double[m_nMaxFold * 2];
	m_pMethod = new CXNLSQMethod;
	m_pMethod->InitWithUserData(m_nMaxFold, 4, 100, Function_nls_fcs);
}

bool CXAVAZFCs::InitOutputData(float* pBani, float* pAzimuth)
{
	m_pOutBani = pBani;
	m_pOutAzimuth = pAzimuth;
	return true;
}

void CXAVAZFCs::SetFold(int nFold)
{
	m_nFold = nFold;
}

void CXAVAZFCs::Calculate()
{
	// set default
	float fInvalid = ::g_dInvalidData;
	for (int k = m_kMin; k <= m_kMax; ++k)
	{
		m_pOutBani[k] = fInvalid;
		m_pOutAzimuth[k] = fInvalid;
	}

	//  
	vector<sOffAziInd> vecsIncAzi(m_nFold);
	for (int iFold = 0; iFold < m_nFold; ++iFold)
	{
		vecsIncAzi[iFold].incidence = m_pOffAzi[2 * iFold];
		vecsIncAzi[iFold].azimuth = m_pOffAzi[2 * iFold+1];
		vecsIncAzi[iFold].index = iFold;
	}

	// sort by incidence
	std::sort(vecsIncAzi.begin(), vecsIncAzi.end(), [](const sOffAziInd& a, const sOffAziInd& b) {
		return a.incidence < b.incidence;
	});	

	// find proper incidence angle [35, 43]
	float fIncidence = 0;
	int iMin = -1, iMax = -1;
	for (int i = vecsIncAzi.size()-1; i>= 0; --i)
	{
		if (iMin != -1 && iMax != -1)
			break;
		if (iMax  == -1)
		{
			if (vecsIncAzi[i].incidence == (float) m_nIncidence)
			{
				iMax = i;
				fIncidence = vecsIncAzi[i].incidence;
			}
			continue;
		}
		if (iMax != -1)
		{
			if (fIncidence != vecsIncAzi[i].incidence)
				iMin = i + 1;

			if (i == 0)
				iMin = 0;
		}
	}
	if (fIncidence == 0.f || iMin == -1 || iMax == -1)
		return;

	int nAzinum = iMax - iMin + 1;
	// sort by azimuth
	std::sort(&vecsIncAzi[iMin], &vecsIncAzi[iMin] + nAzinum, [](const sOffAziInd& a, const sOffAziInd& b) {
		return a.azimuth < b.azimuth;
	});	

	if (nAzinum < 6)
		return;

	for (int k = m_kMin; k <= m_kMax; ++k)
	{
		double dtheta = (vecsIncAzi[iMin + 1].azimuth - vecsIncAzi[iMin].azimuth);
		double u2(0), v2(0);
		int iGatherIndex;
		float fValue;
		float fAzimuth;
		int iCount = 0;

		for (int i = iMin; i <= iMax; ++i)
		{
			iGatherIndex = vecsIncAzi[i].index;
			fValue = m_pGather[iGatherIndex*m_nK + k];
			fAzimuth = vecsIncAzi[i].azimuth;

			if (fValue != fInvalid && fAzimuth != fInvalid)
			{
				++iCount;
			}
		}
		if (iCount < nAzinum / 2)
			continue;

		for (int i = iMin; i <= iMax; ++i)
		{
			iGatherIndex = vecsIncAzi[i].index;
			fValue = m_pGather[iGatherIndex*m_nK + k];
			fAzimuth = vecsIncAzi[i].azimuth;

			if (fValue == fInvalid || fAzimuth == fInvalid)
			{
				continue;
			}

			u2 += fValue*cos(2 * fAzimuth*M_RAD)*dtheta*M_RAD;
			v2 += fValue*sin(2 * fAzimuth*M_RAD)*dtheta*M_RAD;
		}

		u2 /= M_PI;
		v2 /= M_PI;

		double r2 = sqrt(u2*u2 + v2*v2);
		double dAzisym = 0.5*atan2(v2, u2)*M_DEG;

		// Bani
		m_pOutBani[k] = r2 * 2 / (SQR(sin(fIncidence*M_RAD)));

		// Azi
		m_pOutAzimuth[k] = dAzisym + 90.;

	}
}

void CXAVAZFCs::Calculate2()
{
	// set default
	float fInvalid = ::g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);
	for (int k = m_kMin; k <= m_kMax; ++k)
	{
		m_pOutBani[k] = fInvalid;
		m_pOutAzimuth[k] = fInvalid;
	}

	//  
	vector<sOffAziInd> vecsIncAzi(m_nFold);
	for (int iFold = 0; iFold < m_nFold; ++iFold)
	{
		vecsIncAzi[iFold].incidence = m_pOffAzi[2 * iFold];
		vecsIncAzi[iFold].azimuth = m_pOffAzi[2 * iFold + 1];
		vecsIncAzi[iFold].index = iFold;
	}

	// sort by incidence
	std::sort(vecsIncAzi.begin(), vecsIncAzi.end(), [](const sOffAziInd& a, const sOffAziInd& b) {
		return a.incidence < b.incidence;
	});

	// find proper incidence angle [35, 43]
	float fIncidence = 0;
	int iMin = -1, iMax = -1;
	for (int i = vecsIncAzi.size() - 1; i >= 0; --i)
	{
		if (iMin != -1 && iMax != -1)
			break;
		if (iMax == -1)
		{
			if (vecsIncAzi[i].incidence == (float)m_nIncidence)
			{
				iMax = i;
				fIncidence = vecsIncAzi[i].incidence;
			}
			continue;
		}
		if (iMax != -1)
		{
			if (fIncidence != vecsIncAzi[i].incidence)
				iMin = i + 1;

			if (i == 0)
				iMin = 0;
		}
	}
	if (fIncidence == 0.f || iMin == -1 || iMax == -1)
		return;

	int nAzinum = iMax - iMin + 1;
	// sort by azimuth
	std::sort(&vecsIncAzi[iMin], &vecsIncAzi[iMin] + nAzinum, [](const sOffAziInd& a, const sOffAziInd& b) {
		return a.azimuth < b.azimuth;
	});

	
	vector<double> vecSeismicData(m_nMaxFold), vecAzimuth(m_nMaxFold);
	for (int k = m_kMin; k <= m_kMax; ++k)
	{
		int iGatherIndex;
		float fValue;
		int m = 0;

		for (int i = iMin; i <= iMax; ++i)
		{
			iGatherIndex = vecsIncAzi[i].index;
			fValue = m_pGather[iGatherIndex*m_nK + k];

			if (qAbs(fValue - fInvalid) > fInvalidEPS)
			{
				vecSeismicData[m] = fValue;
				vecAzimuth[m] = vecsIncAzi[i].azimuth;
				++m;

			}
		}

		if (m < 4)
			continue;

		// init
		m_pX[0] = vecSeismicData[0];
		m_pX[1] = vecSeismicData[0];
		m_pX[2] = 0;
		m_pX[3] = 0;

		memcpy(m_pUserData, &vecAzimuth[0], sizeof(double)*m);
		memcpy(m_pUserData + m, &vecSeismicData[0], sizeof(double)*m);

		m_pMethod->Calculate2WithUserData(m, 4, m_pX, m_pUserData);

	
		// Bani
		m_pOutBani[k] = m_pX[1];

		// Azi
		m_pOutAzimuth[k] = m_pX[3];
		if (m_pOutAzimuth[k] < 0)
			m_pOutAzimuth[k] = 0;

	}
}