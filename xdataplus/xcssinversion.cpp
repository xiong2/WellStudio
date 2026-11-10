#include "xcssinversion.h"
#include "xparametercssinversion.h"
#include <cmath>
#include <cassert>
#include "xutility.h"
#include "xglobal.h"
#include "xmathmacro.h"
#include "xfunctiontemplate.h"
#include "mkl.h"

CXCSSInversion::CXCSSInversion()
{
	// 1-D
	m_pWavelet = NULL;

	m_pZP0 = NULL;
	m_pInSeismic = NULL;
	m_pX = NULL;
	m_pB = NULL;
	m_pQ = NULL;
	m_pXi = NULL;
	m_pTmp1 = NULL;

	m_pG = NULL;
	m_pA = NULL;
	m_pCCom = NULL;

	m_pR = NULL;
	m_pImpedance = NULL;
	m_pOutSeismic = NULL;

	

	m_pFFTBuffer = NULL;
	m_pH1 = NULL;
	m_pH2 = NULL;
	m_pFFTOut1 = NULL;
	m_pFFTOut2 = NULL;

	m_pTmp2 = NULL;
	m_pTmp3 = NULL;
	m_pImpBP = NULL;
	m_pImpMerged = NULL;

	m_pBuffer = NULL;
}

CXCSSInversion::~CXCSSInversion()
{
	if (m_pWavelet)		{ delete[]m_pWavelet; m_pWavelet = NULL; }

	if (m_pZP0)			{ delete[]m_pZP0; m_pZP0 = NULL; }
	if (m_pInSeismic)	{ delete[]m_pInSeismic; m_pInSeismic = NULL; }
	if (m_pX)			{ delete[]m_pX; m_pX = NULL; }
	if (m_pB)			{ delete[]m_pB; m_pB = NULL; }
	if (m_pQ)			{ delete[]m_pQ; m_pQ = NULL; }
	if (m_pXi)			{ delete[]m_pXi; m_pXi = NULL; }
	if (m_pTmp1)		{ delete[]m_pTmp1; m_pTmp1 = NULL; }
	if (m_pG)			{ delete[]m_pG; m_pG = NULL; }
	if (m_pA)			{ delete[]m_pA; m_pA = NULL; }
	if (m_pCCom)		{ delete[]m_pCCom; m_pCCom = NULL; }
	if (m_pR)			{ delete[]m_pR; m_pR = NULL; }
	if (m_pImpedance)	{ delete[]m_pImpedance; m_pImpedance = NULL; }
	if (m_pOutSeismic)	{ delete[]m_pOutSeismic; m_pOutSeismic = NULL; }

	//if (m_pDspFilter)	{ delete m_pDspFilter; m_pDspFilter = NULL; }

	if (m_pFFTBuffer)	{ delete[]m_pFFTBuffer; m_pFFTBuffer = NULL; }
	if (m_pH1)			{ delete[]m_pH1; m_pH1 = NULL; }
	if (m_pH2)			{ delete[]m_pH2; m_pH2 = NULL; }
	if (m_pFFTOut1)		{ delete[]m_pFFTOut1; m_pFFTOut1 = NULL; }
	if (m_pFFTOut2)		{ delete[]m_pFFTOut2; m_pFFTOut2 = NULL; }

	if (m_pTmp2)		{ delete[]m_pTmp2; m_pTmp2 = NULL; }
	if (m_pTmp3)		{ delete[]m_pTmp3; m_pTmp3 = NULL; }
	if (m_pImpBP)		{ delete[]m_pImpBP; m_pImpBP = NULL; }
	if (m_pImpMerged)	{ delete[]m_pImpMerged; m_pImpMerged = NULL; }

	if (m_pBuffer)		{ delete[]m_pBuffer; m_pBuffer = NULL; }
	
}

void CXCSSInversion::InitWaveletPara(int nWaveSize, vector<float>& vecWavelet)
{
	if (nWaveSize == 0 || vecWavelet.empty())
		return;

	m_nWaveSize = nWaveSize;
	m_pWavelet = new double[m_nWaveSize];

	for (int i = 0; i < m_nWaveSize; ++i)
		m_pWavelet[i] = vecWavelet[i];

	_InitWavelet();
}

void CXCSSInversion::InitInversionPara(CXParameterCSSInversion* pPara)
{
	m_dAlpha = pPara->GetAlpha();
	m_dBeta = pPara->GetBeta();
	m_dMu = pPara->GetMu();
	m_dSigma = pPara->GetSigma();
	m_dTol = pPara->GetTolerance();
	m_dWavletFactor = pPara->GetWaveletFactor();
	m_nMaxLoop = pPara->GetMaxLoopNum();

	m_dSamplingRate = pPara->GetSamplingRate();

	m_bApplyFiltering = true;
	m_dLowCut = pPara->GetLowCut();
	m_dLowOverlap = pPara->GetLowOverlap();
	m_dHighCut = pPara->GetHighCut();
	m_dHighOverlap = pPara->GetHighOverlap();

	//Dsp::Params params;
	//params[0] = dSamplingFreq;
	//params[1] = 10;
	//params[2] = m_dCutFrequency;
	//m_pDspFilter->setParams(params);

	//m_pDspFilter->setup(1, dSamplingFreq, m_dCutFrequency);
}

//void CXCSSInversion::InitInversionPara(double alpha, double beta, double mu, double sigma, double waveletfactor, double tol, int nMaxLoop)
//{
//	m_dAlpha = alpha;
//	m_dBeta = beta;
//	m_dMu = mu;
//	m_dSigma = sigma;
//	m_dTol = tol;
//	m_dWavletFactor = waveletfactor;
//	m_nMaxLoop = nMaxLoop;
//}

bool CXCSSInversion::CreateBuffers(int nMaxNZ, bool bExportR, bool bExportSeismic)
{
	m_nMaxNZ = nMaxNZ;

	try
	{
		m_pZP0 = new double[m_nMaxNZ];
		m_pInSeismic = new double[m_nMaxNZ];
		m_pX = new double[m_nMaxNZ+30];
		m_pB = new double[m_nMaxNZ];
		m_pQ = new double[m_nMaxNZ];
		m_pXi = new double[m_nMaxNZ];
		m_pTmp1 = new double[m_nMaxNZ];
		m_pTmp2 = new double[m_nMaxNZ];
		m_pTmp3 = new double[m_nMaxNZ];

		m_pG = new double[m_nMaxNZ*m_nMaxNZ];
		m_pA = new double[m_nMaxNZ*m_nMaxNZ];
		m_pCCom = new double[m_nMaxNZ*m_nMaxNZ];

		// fft buffers
		int nFFTSize = NXUtility::LengthofFFT(2*m_nMaxNZ);
		m_pFFTBuffer = new double[2 * nFFTSize];
		m_pH1 = new double[nFFTSize];
		m_pH2 = new double[nFFTSize];
		m_pFFTOut1 = new double[m_nMaxNZ];
		m_pFFTOut2 = new double[m_nMaxNZ];

		// output
		m_pR = new float[m_nMaxNZ];

		m_pImpedance = new float[m_nMaxNZ];
		m_pImpBP = new float[m_nMaxNZ];
		m_pImpMerged = new float[m_nMaxNZ];

		m_pBuffer = new double[m_nMaxNZ * 6];

		if (bExportSeismic)
		{
			m_pOutSeismic = new float[m_nMaxNZ];
		}
	}
	catch (std::bad_alloc)
	{
		return false;
	}

	return true;
}

void CXCSSInversion::SetDataBuffer(int zMin, int zMax, float* pZP0, float* pSeismic)
{
	m_zmin = zMin;
	m_zmax = zMax;

	m_nZ = zMax - zMin + 1;

	// seismic and impedance
	for (int k = 0; k < m_nZ; ++k)
	{
		m_pInSeismic[k] = pSeismic[k + m_zmin];
		m_pZP0[k] = pZP0[k + m_zmin];
	}
}

void CXCSSInversion::_InitWavelet()
{
	if (m_nWaveSize <= 0)
		return;

	// find max data and its position
	m_dMaxWaveletValue = m_pWavelet[0];
	m_iWaveletPeakPos = 0;
	for (int i = 1; i < m_nWaveSize; ++i)
	{
		if (qAbs(m_pWavelet[i]) > m_dMaxWaveletValue)
		{
			m_dMaxWaveletValue = qAbs(m_pWavelet[i]);
			m_iWaveletPeakPos = i;
		}
	}

	// normalize
	if (m_dMaxWaveletValue == 0)
		return;

	for (int i = 0; i < m_nWaveSize; ++i)
	{
		m_pWavelet[i] = m_pWavelet[i]/m_dMaxWaveletValue*m_dWavletFactor;
	}
}

void CXCSSInversion::_InitSeismicAndImpedance()
{
	// normalize seismic data with max wavelet data
	if (m_dMaxWaveletValue != 0)
	{
		for (int i = 0; i < m_nZ; ++i)
		{
			m_pInSeismic[i] = m_pInSeismic[i]/m_dMaxWaveletValue;
		}
	}

	// low pass filter
	//_LowPassFilter();

	// calc xi vector
	m_dZP0 = m_pZP0[0];
	m_pXi[0] = 0;
	for (int i = 1; i < m_nZ; ++i)
	{
		m_pXi[i] = 0.5*log(m_pZP0[i] / m_dZP0);
	}
}

void CXCSSInversion::_LowPassFilter()
{
	
}

void CXCSSInversion::_CalcG()
{
	memset(m_pG, 0, sizeof(double)*m_nZ*m_nZ);

	// wavelet matrix, column-major
	for (int j = 0, iStart = m_iWaveletPeakPos; j < m_nZ; ++j, --iStart)
	{
		for (int i = qMax(0, iStart); i < m_nWaveSize && i - iStart < m_nZ; ++i)
		{
			m_pG[j*m_nZ + i - iStart] = m_pWavelet[i];
		}
	}
}

void CXCSSInversion::_CalcQ()
{	
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pQ[i] = 1. / (1 + SQR(m_pX[i] / m_dSigma));
	}
}

void CXCSSInversion::_CalcCComplex()
{
	// CCom = C'*C
	for (int i = 0; i < m_nZ; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			m_pCCom[i*m_nZ + j] = m_nZ - i;
			m_pCCom[j*m_nZ + i] = m_nZ - i;
		}
	}

	_CalcG();

	//test code
	//for (int i = 0; i < m_nZ; ++i)
	//{
	//	for (int j = 0; j <= i; ++j)
	//	{
	//		m_pCCom[i*m_nZ + j] = m_pCCom[i*m_nZ + j] * m_dAlpha + NXUtility::DotProduct<double>(m_pG + i*m_nZ, m_pG + j*m_nZ, m_nZ);
	//		m_pCCom[j*m_nZ + i] = m_pCCom[i*m_nZ + j];
	//	}
	//}


	// CCom = G'*G + alpha*CCom
	cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, m_nZ, m_nZ, m_dBeta, m_pG, m_nZ, m_dAlpha, m_pCCom, m_nZ);
	//for (int i = 0; i < m_nZ; ++i)
	//{
	//	for (int j = i + 1; j < m_nZ; ++j)
	//	{
	//		m_pCCom[j*m_nZ + i] = m_pCCom[i*m_nZ + j];
	//	}
	//}
}

void CXCSSInversion::_CalcA()
{
	_CalcQ();

	// A = CCom + mu*Q
	memcpy(m_pA, m_pCCom, sizeof(double)*m_nZ*m_nZ);
	double dCoef = m_dMu / (m_dSigma*m_dSigma);

	for (int i = 0; i < m_nZ; ++i)
		m_pA[i*m_nZ + i] += dCoef*m_pQ[i];
}

void CXCSSInversion::_CalcB()
{
	// C'*xi
	m_pB[m_nZ - 1] = m_pXi[m_nZ - 1];
	for (int i = m_nZ - 2; i >= 0; --i)
	{
		m_pB[i] = m_pB[i + 1] + m_pXi[i];
	}

	// B = G'*d + alpha*C'*Xi
	cblas_dgemv(CblasColMajor, CblasTrans, m_nZ, m_nZ, m_dBeta, m_pG, m_nZ, m_pInSeismic, 1, m_dAlpha, m_pB, 1);
}

double CXCSSInversion::_CalcCostFunction()
{	
	// Gr-d
	memcpy(m_pTmp1, m_pInSeismic, sizeof(double)*m_nZ);
	cblas_dgemv(CblasColMajor, CblasNoTrans, m_nZ, m_nZ, 1.0, m_pG, m_nZ, m_pX, 1, -1., m_pTmp1, 1);

	// 0.5*(Gr-d)'*(Gr-d)
	//double Js = 0.5* NXUtility::DotProduct<double>(m_pTmp1, m_pTmp1, m_nZ)
	double Js = 0.5*m_dBeta*cblas_ddot(m_nZ, m_pTmp1, 1, m_pTmp1, 1);

	// 0.5*mu*sum(ln(1+(ri/sigma)^2));
	double Jr = 0.;
	for (int i = 0; i < m_nZ; ++i)
		Jr += log(1+SQR(m_pX[i]/m_dSigma));

	Jr = 0.5*m_dMu*Jr;

	// 0.5*alpha*(Cr-Xi)'(Cr-Xi)
	// C*r
	m_pTmp1[0] = m_pX[0];
	for (int i = 1; i < m_nZ; ++i)
		m_pTmp1[i] = m_pTmp1[i - 1] + m_pX[i];

	// C*r-xi
	for (int i = 0; i < m_nZ; ++i)
		m_pTmp1[i] -= m_pXi[i];

	//double Ji = 0.5*m_dAlpha*NXUtility::DotProduct<double>(m_pTmp1, m_pTmp1, m_nZ);
	double Ji = 0.5*m_dAlpha*cblas_ddot(m_nZ, m_pTmp1, 1, m_pTmp1, 1);

	return Js + Jr + Ji;
}

void CXCSSInversion::Calculate()
{	
	_InitSeismicAndImpedance();

	_CalcCComplex();

	_CalcB();

	// init cost function
	memset(m_pX, 0, sizeof(double)*m_nZ);
	double dJ0 = _CalcCostFunction();

	double dJ;
	int iLoop;
	double err;
	int nLoop;
	for (iLoop = 0; iLoop < m_nMaxLoop; ++iLoop)
	{
		// calc A
		_CalcA();

		// set B
		memcpy(m_pX, m_pB, sizeof(double)*m_nZ);

		// solve x
		//LAPACKE_dgels(LAPACK_COL_MAJOR, 'N', m_nZ, m_nZ, 1, m_pA, m_nZ, m_pX, m_nZ);
		//memset(m_pX, 0, sizeof(double)*m_nZ);
		//CGMethod(m_nZ, m_pA, m_pBuffer, m_pB, m_pX, m_dTol, m_nZ, err, nLoop);
		//CGSolver(m_nZ, m_pBuffer, m_pA, m_pX, m_pB, m_dTol, m_nZ, nLoop, err);
		LAPACKE_dposv(LAPACK_COL_MAJOR, 'L', m_nZ, 1, m_pA, m_nZ, m_pX, m_nZ);

		dJ = _CalcCostFunction();

		if (qAbs(dJ0 - dJ) / (dJ0 + dJ) < m_dTol)
			break;

		dJ0 = dJ;
	}

	// calc impedance
	_CalcImpedance();
	
	// seismic
	_CalcSeismic();

}

void CXCSSInversion::_CalcImpedance()
{
	if (!m_pImpedance)
		return;

	double dRSum = 0.;
	for (int i = 0; i < m_nZ; ++i)
	{
		dRSum += m_pX[i];
		m_pTmp1[i] = m_pZP0[0] * exp(2.*dRSum);
	}

	// merge
	if (m_bApplyFiltering)
		_MergeLowFreq();

	//set	
	float fInvalid = (float)::g_dInvalidData;
	for (int i = 0; i < m_nMaxNZ; ++i)
	{
		if (i < m_zmin || i > m_zmax)
		{
			m_pImpedance[i] = fInvalid;
			m_pImpBP[i] = fInvalid;
			m_pImpMerged[i] = fInvalid;
		}
		else
		{
			m_pImpedance[i] = (float)m_pTmp1[i - m_zmin];
			m_pImpBP[i] = (float)m_pTmp2[i - m_zmin];
			m_pImpMerged[i] = (float)m_pTmp3[i - m_zmin];
		}
	}

	// recalculate R
	if (m_bApplyFiltering)
	{
		for (int i = 0; i < m_nZ; ++i)
		{
			m_pTmp1[i] = log(m_pTmp1[i]);
		}

		for (int i = 0; i < m_nZ - 1; ++i)
		{
			m_pX[i] = 0.5*(m_pTmp1[i + 1] - m_pTmp1[i]);
		}
		m_pX[m_nZ - 1] = m_pX[m_nZ - 2];
	}

	// R
	//set 	
	for (int i = 0; i < m_nMaxNZ; ++i)
	{
		if (i < m_zmin || i > m_zmax)
		{
			m_pR[i] = fInvalid;
		}
		else
		{
			m_pR[i] = m_pX[i - m_zmin];
		}
	}
}

void CXCSSInversion::_MergeLowFreq()
{
	// low pass
	NXUtility::DigitalFilter(m_nZ, m_pZP0, m_pFFTOut1, m_dSamplingRate, 0, 0, m_dLowCut, m_dLowOverlap, m_pFFTBuffer, m_pH1, m_pH2);

	// band pass
	NXUtility::DigitalFilter(m_nZ, m_pTmp1, m_pFFTOut2, m_dSamplingRate, m_dLowCut, m_dLowOverlap, m_dHighCut, m_dHighOverlap, m_pFFTBuffer, m_pH1, m_pH2);

	for (int i = 0; i < m_nZ; ++i)
	{
		m_pTmp2[i] = m_pFFTOut2[i];
		m_pTmp3[i] = m_pFFTOut1[i] + m_pFFTOut2[i];
	}
}

void CXCSSInversion::_CalcSeismic()
{
	if (!m_pOutSeismic)
		return;
	
	// Seismic = G*R 
	memset(m_pTmp1, 0, sizeof(double)*m_nZ);
	cblas_dgemv(CblasColMajor, CblasNoTrans, m_nZ, m_nZ, 1.0, m_pG, m_nZ, m_pX, 1, 0, m_pTmp1, 1);

	//set 
	float fInvalid = (float)::g_dInvalidData;
	for (int i = 0; i < m_nMaxNZ; ++i)
	{
		if (i < m_zmin || i > m_zmax)
		{
			m_pOutSeismic[i] = fInvalid;
		}
		else
		{
			m_pOutSeismic[i] = (float)m_pTmp1[i - m_zmin];
		}
	}

}

void CXCSSInversion::CGMethod(int n, double *A, double* pBuffer, double* b, double* x, double tol, int nMaxLoop, double& err, int& iLoop)
{
	iLoop = 0;
	err = 1.e10;
	if (n < 2)
		return;

	if (!A || !x || !b || !pBuffer)
		return;

	double* r = pBuffer;
	double* rnew = pBuffer + n;
	double* p = pBuffer + 2 * n;
	double* ap = pBuffer + 3 * n;

	// r = b-Ax
	memcpy(r, b, sizeof(double)*n);
	cblas_dsymv(CblasColMajor, CblasLower, n, -1.0, A, n, x, 1, 1, r, 1);
	memcpy(p, r, sizeof(double)*n);

	double r2old = cblas_dnrm2(n, r, 1);
	double alpha, beta, r2new, r2middle;

	for (int i = 0; i < nMaxLoop; ++i)
	{
		// Ap
		memset(ap, 0, sizeof(double)*n);
		cblas_dsymv(CblasColMajor, CblasLower, n, 1, A, n, p,  1, 0, ap, 1);
		
		// alpha = (r'*r)/(p'*Ap)
		alpha = r2old / cblas_ddot(n, p, 1, ap, 1);
		
		// x  = x + alpha*p
		cblas_daxpy(n, alpha, p, 1, x, 1);

		// r = r -alpha*Ap
		cblas_daxpy(n, -alpha, ap, 1, r, 1);

		r2new = cblas_dnrm2(n, r, 1);
		
		err = r2new;
		iLoop = i;
		if (r2new < tol)
		{
			return;
		}	

		// beta = rnew'*rnew/r'*r
		beta = r2new / r2old;

		cblas_dscal(n, beta, p, 1);
		cblas_daxpy(n, 1, r, 1, p, 1);

		r2old = r2new;
	}
}

void CXCSSInversion::CGSolver(int n, double* pBuffer, double*a, double*x, double*b, double tol, int itmax, int& iter, double& err)
{
	double ak, akden, bk, bkden = 1.0, bknum, bnrm, dxnrm, xnrm, zm1nrm, znrm;
	const double EPS = 1.0e-14;
	int j;
	double *p = pBuffer;
	double *pp = pBuffer + n;
	double *r = pBuffer + 2*n;
	double *rr = pBuffer + 3*n;
	double *z = pBuffer + 4*n;
	double *zz = pBuffer + 5*n;

	iter = 0;

	// r = b-Ax
	memcpy(r, b, sizeof(double)*n);
	cblas_dsymv(CblasColMajor, CblasLower, n, -1.0, a, n, x, 1, 1, r, 1);
	memcpy(rr, r, sizeof(double)*n);

	for (int i = 0; i < n; ++i)
		z[i] = a[i*n + i] == 0 ? b[i] : b[i] / a[i*n + i];
	bnrm = sqrt(cblas_dnrm2(n, z, 1));

	for (int i = 0; i < n; ++i)
		z[i] = a[i*n + i] == 0 ? r[i] : r[i] / a[i*n + i];
	znrm = sqrt(cblas_dnrm2(n, z, 1));

	while (iter < itmax)
	{
		++iter;

		for (int i = 0; i < n; ++i)
			zz[i] = a[i*n + i] == 0 ? rr[i] : rr[i] / a[i*n + i];

		bknum = cblas_ddot(n, z, 1, rr, 1);

		if (iter == 1)
		{
			memcpy(p, z, sizeof(double)*n);
			memcpy(pp, zz, sizeof(double)*n);
		}
		else
		{
			bk = bknum / bkden;
			for (j = 0; j < n; j++)
			{
				p[j] = bk*p[j] + z[j];
				pp[j] = bk*pp[j] + zz[j];
			}
		}
		bkden = bknum;

		memset(z, 0, sizeof(double)*n);
		cblas_dsymv(CblasColMajor, CblasLower, n, 1.0, a, n, p, 1, 0, r, 1);

		akden = cblas_ddot(n, z, 1, pp, 1);
		ak = bknum / akden;

		memset(zz, 0, sizeof(double)*n);
		cblas_dsymv(CblasColMajor, CblasLower, n, 1.0, a, n, pp, 1, 0, zz, 1);

		for (j = 0; j<n; j++)
		{
			x[j] += ak*p[j];
			r[j] -= ak*z[j];
			rr[j] -= ak*zz[j];
		}

		for (int i = 0; i < n; ++i)
			z[i] = a[i*n + i] == 0 ? r[i] : r[i] / a[i*n + i];

		zm1nrm = znrm;
		znrm = sqrt(cblas_dnrm2(n, z, 1));
		if (qAbs(zm1nrm - znrm) > EPS*znrm)
		{
			dxnrm = qAbs(ak)*sqrt(cblas_dnrm2(n, p, 1));
			err = znrm / qAbs(zm1nrm - znrm)*dxnrm;
		}
		else
		{
			err = znrm / bnrm;
			continue;
		}
		xnrm = sqrt(cblas_dnrm2(n, x, 1));;
		if (err <= 0.5*xnrm)
			err /= xnrm;
		else
		{
			err = znrm / bnrm;
			continue;
		}

		if (err <= tol) break;
	}
}
