#include "xavossinversion.h"
#include "xparameter3terminversion.h"
#include <cmath>
#include <cassert>
#include "xutility.h"
#include "xglobal.h"
#include "xmathmacro.h"
#include "xfunctiontemplate.h"
#include "xblas.h"
#include "mkl.h"

CXAVOSSInversion::CXAVOSSInversion()
{
	m_nZ = -1;

	m_p2DAkiCoef = NULL;
	m_p2DWaveletData = NULL;

	m_p2DR = NULL;
	m_p2DSeismic = NULL;
	m_p2DPrior = NULL;

	m_pZp = NULL;
	m_pZs = NULL;
	m_pZRho = NULL;

	m_pZ0 = NULL;
	m_pZ1 = NULL;
	m_pZ2 = NULL;
	m_pD0 = NULL;
	m_pXi = NULL;
	m_pTmp = NULL;

	m_pW = NULL;
	m_pA = NULL;
	m_pB = NULL;
	m_pRR = NULL;
	m_pR = NULL;

	// block matrix
	m_p2DGGCoef = NULL;
	m_pSquare = NULL;

	m_pB1 = NULL;
	m_pB2 = NULL;
	m_pA1 = NULL; 
	m_pA2 = NULL;
	m_pWSquareArray = NULL;
	m_pWD = NULL;
	m_pCXi = NULL;
	m_pWArray = NULL;

	m_pTrace = NULL;

	// filtering
	m_pFFTBuffer = NULL;
	m_pH1 = NULL;
	m_pH2 = NULL;
	m_pFFTOut1 = NULL;
	m_pFFTOut2 = NULL;

	m_pTmp2 = NULL;
	m_pTmp3 = NULL;
	m_pZpBP = NULL;
	m_pZsBP = NULL;
	m_pZRhoBP = NULL;
	m_pZpMerged = NULL;
	m_pZsMerged = NULL;
	m_pZRhoMerged = NULL;
}

CXAVOSSInversion::~CXAVOSSInversion()
{
	if (m_p2DAkiCoef)		{ NXUtility::Free2DMatrix<double>(m_p2DAkiCoef);		m_p2DAkiCoef = NULL; }
	if (m_p2DWaveletData)	{ NXUtility::Free2DMatrix<double>(m_p2DWaveletData);		m_p2DWaveletData = NULL; }
	

	if (m_p2DR)				{ NXUtility::Free2DMatrix<float>(m_p2DR);				m_p2DR = NULL; }
	if (m_p2DSeismic)		{ NXUtility::Free2DMatrix<float>(m_p2DSeismic);		m_p2DSeismic = NULL; }
	if (m_p2DPrior)			{ NXUtility::Free2DMatrix<float>(m_p2DPrior);		m_p2DPrior = NULL; }

	if (m_pZp)				{ delete[]m_pZp;				m_pZp = NULL; }
	if (m_pZs)				{ delete[]m_pZs;				m_pZs = NULL; }
	if (m_pZRho)			{ delete[]m_pZRho;				m_pZRho = NULL; }

	if (m_pZ0)				{ delete []m_pZ0;				m_pZ0 = NULL; }
	if (m_pZ1)				{ delete []m_pZ1;				m_pZ1 = NULL; }
	if (m_pZ2)				{ delete []m_pZ2;				m_pZ2 = NULL; }
	if (m_pD0)				{ delete []m_pD0;				m_pD0 = NULL; }
	if (m_pXi)				{ delete []m_pXi;				m_pXi = NULL; }
	if (m_pTmp)				{ delete []m_pTmp;				m_pTmp = NULL; }
		
	if (m_pW)				{ delete[]m_pW;					m_pW = NULL; }
	if (m_pA)				{ delete[]m_pA;					m_pA = NULL; }
	if (m_pB)				{ delete[]m_pB;					m_pB = NULL; }
	if (m_pRR)				{ delete[]m_pRR;				m_pRR = NULL; }
	if (m_pR)				{ delete[]m_pR;					m_pR = NULL; }

	// block matrix
	if (m_p2DGGCoef)		{ NXUtility::Free2DMatrix<double>(m_p2DGGCoef);		m_p2DGGCoef = NULL; }
	if (m_pSquare)			{ delete[]m_pSquare;			m_pSquare = NULL; }

	if (m_pB1)				{ delete[]m_pB1;			m_pB1 = NULL; }
	if (m_pB2)				{ delete[]m_pB2;			m_pB2 = NULL; }
	if (m_pA1)				{ delete[]m_pA1;			m_pA1 = NULL; }
	if (m_pA2)				{ delete[]m_pA2;			m_pA2 = NULL; }
	if (m_pWSquareArray)	{ delete[]m_pWSquareArray;	m_pWSquareArray = NULL; }
	if (m_pWD)				{ delete[]m_pWD;			m_pWD = NULL; }	
	if (m_pCXi)				{ delete[]m_pCXi;			m_pCXi = NULL; }
	if (m_pWArray)			{ delete[]m_pWArray;		m_pWArray = NULL; }

	if (m_pTrace)			{ delete[]m_pTrace;			m_pTrace = NULL; }

	if (m_pFFTBuffer)	{ delete[]m_pFFTBuffer; m_pFFTBuffer = NULL; }
	if (m_pH1)			{ delete[]m_pH1; m_pH1 = NULL; }
	if (m_pH2)			{ delete[]m_pH2; m_pH2 = NULL; }
	if (m_pFFTOut1)		{ delete[]m_pFFTOut1; m_pFFTOut1 = NULL; }
	if (m_pFFTOut2)		{ delete[]m_pFFTOut2; m_pFFTOut2 = NULL; }

	if (m_pTmp2)		{ delete[]m_pTmp2; m_pTmp2 = NULL; }
	if (m_pTmp3)		{ delete[]m_pTmp3; m_pTmp3 = NULL; }
	if (m_pZpBP)		{ delete[]m_pZpBP; m_pZpBP = NULL; }
	if (m_pZsBP)		{ delete[]m_pZsBP; m_pZsBP = NULL; }
	if (m_pZRhoBP)		{ delete[]m_pZRhoBP; m_pZRhoBP = NULL; }
	if (m_pZpMerged)	{ delete[]m_pZpMerged; m_pZpMerged = NULL; }
	if (m_pZsMerged)	{ delete[]m_pZsMerged; m_pZsMerged = NULL; }
	if (m_pZRhoMerged)	{ delete[]m_pZRhoMerged; m_pZRhoMerged = NULL; }
	
}


void CXAVOSSInversion::_CalcAkiCoef()
{
	if (!m_p2DAkiCoef)
	{
		m_p2DAkiCoef = NXUtility::New2DMatrix<double>(m_nAngleSize, 3);
	}
	if (!m_p2DAkiCoef)
		return;

	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		// theta
		double theta = m_vecAngle[iAngle] * M_RAD;
		double C1 = 1 + SQR(tan(theta));
		double C2 = -8.0*m_dGamma*m_dGamma*SQR(sin(theta));
		double C3 = 4 * m_dGamma*m_dGamma*SQR(sin(theta)) - SQR(tan(theta));

		m_p2DAkiCoef[iAngle][0] = C1;
		m_p2DAkiCoef[iAngle][1] = C2;
		m_p2DAkiCoef[iAngle][2] = C3;
	}
}

void CXAVOSSInversion::InitWaveletPara(vector<float>& vecAngle, int nWaveSize, vector<vector<float> >& vec2DWavelet)
{
	m_nAngleSize = (int)vecAngle.size();
	m_nWaveSize = nWaveSize;

	assert(vecAngle.size() == vec2DWavelet.size());

	// angles
	m_vecAngle.resize(m_nAngleSize);
	for (int i = 0; i < m_nAngleSize; ++i)
		m_vecAngle[i] = vecAngle[i];

	// wavelet buffer
	m_p2DWaveletData = NXUtility::New2DMatrix<double>(m_nAngleSize, m_nWaveSize);
	if (!m_p2DWaveletData)
		return;

	// wavelet data
	for (int i = 0; i < m_nAngleSize; ++i)
	{
		for (int j = 0; j < m_nWaveSize; ++j)
		{
			m_p2DWaveletData[i][j] = vec2DWavelet[i][j] * m_vecWaveletScale[i];
		}
	}

	// calc peak position and max value
	for (int i = 0; i < m_nAngleSize; ++i)
	{
		double dMaxValue = 0;
		int iPeakPos = 0;
		for (int j = 0; j < m_nWaveSize; ++j)
		{
			if (qAbs(m_p2DWaveletData[i][j]) > dMaxValue)
			{
				dMaxValue = qAbs(m_p2DWaveletData[i][j]);
				iPeakPos = j;
			}
		}

		cblas_dscal(m_nWaveSize, 1. / dMaxValue, m_p2DWaveletData[i], 1);

		m_vecPeakPos.push_back(iPeakPos);
		m_vecMaxWaveletValue.push_back(dMaxValue);
	}

	m_bSameWavelet = true;
	for (int i = 1; i < m_nAngleSize; ++i)
	{
		if (0 != memcmp(m_p2DWaveletData[0], m_p2DWaveletData[i], sizeof(double)*m_nWaveSize))
		{
			m_bSameWavelet = false;
			break;
		}
	}

	// Aki coeff
	_CalcAkiCoef();
}

void CXAVOSSInversion::InitInversionPara(CXParameter3TermInversion* pPara)
{
	m_dGamma = pPara->GetGamma();
	m_dMaxLoopNum = pPara->GetMaxLoopNum();
	m_dTol = pPara->GetTolerance();
	m_dAlpha = pPara->GetAlpha();
	m_dBeta = pPara->GetBeta();
	m_dSigma = pPara->GetSigma();
	m_dLamda = pPara->GetLambda();

	m_bOutInversion = pPara->GetOutputInversion();
	m_bOutPrior = pPara->GetOutputPrior();
	m_bAki = pPara->GetAkiRichards();

	m_nOutType = pPara->GetOutputType();

	m_bAVOSSI = (pPara->GetObjectType() == EAVOSSInversion || pPara->GetObjectType() == EAnisotropyInversion);

	m_dSamplingRate = pPara->GetSamplingRate();
	m_bApplyFiltering = true;
	m_dLowCut = pPara->GetLowCut();
	m_dLowOverlap = pPara->GetLowOverlap();
	m_dHighCut = pPara->GetHighCut();
	m_dHighOverlap = pPara->GetHighOverlap();

	m_vecLambda = pPara->GetvecLambda();
	m_vecAlpha = pPara->GetvecAlpha();
	m_vecSigma = pPara->GetvecSigma();
	m_vecWaveletScale = pPara->GetvecWaveletScale();

	if (m_vecLambda.empty())
	{
		int nAngle = pPara->GetVecAngleValue().size();
		if (nAngle == 0)
			nAngle = pPara->GetVecAngleIndex().size();

		for (int i = 0; i < nAngle; ++i)
		{
			m_vecLambda.push_back(m_dLamda);
			m_vecWaveletScale.push_back(1.);
		}

		for (int i = 0; i < 3; ++i)
		{
			m_vecAlpha.push_back(m_dAlpha);
			m_vecSigma.push_back(m_dSigma);
		}

	}
}


bool CXAVOSSInversion::CreateBuffers(int nMaxNZ, bool bExportR, bool bExportSeismic)
{
	m_nMaxNZ = nMaxNZ;

	try
	{
		m_pZp = new float[m_nMaxNZ];
		m_pZs = new float[m_nMaxNZ];
		m_pZRho = new float[m_nMaxNZ];

		m_pZpBP = new float[m_nMaxNZ];
		m_pZsBP = new float[m_nMaxNZ];
		m_pZRhoBP = new float[m_nMaxNZ];
		m_pZpMerged = new float[m_nMaxNZ];
		m_pZsMerged = new float[m_nMaxNZ];
		m_pZRhoMerged = new float[m_nMaxNZ];

		m_pZ0 = new double[3 * m_nMaxNZ];
		m_pZ1 = new double[3 * m_nMaxNZ+100];
		m_pZ2 = new double[3 * m_nMaxNZ];
		m_pD0 = new double[m_nAngleSize * m_nMaxNZ];
		m_pXi = new double[3 * m_nMaxNZ];
		m_pTmp = new double[m_nAngleSize * m_nMaxNZ];

		m_pTmp2 = new double[m_nAngleSize * m_nMaxNZ];
		m_pTmp3 = new double[m_nAngleSize * m_nMaxNZ];
				
		m_pW	= new double [m_nMaxNZ * m_nMaxNZ];
		
		if (m_bAVOSSI)
		{
			m_pA = new double[3 * m_nMaxNZ * 3 * m_nMaxNZ];
		}

		m_pB	= new double [3 * m_nMaxNZ];
		m_pRR	= new double[3 * m_nMaxNZ];
		m_pR	= new double [3 * m_nMaxNZ];

		// block matrix
		m_pSquare = new double[m_nMaxNZ * m_nMaxNZ];

		m_pB1 = new double[3 * m_nMaxNZ];
		m_pB2 = new double[3 * m_nMaxNZ];
		m_pA1 = new double[3 * m_nMaxNZ * 3 * m_nMaxNZ];
		m_pA2 = new double[3 * m_nMaxNZ * 3 * m_nMaxNZ];
		m_pWSquareArray = new double[m_nAngleSize * m_nMaxNZ * m_nMaxNZ];
		m_pWD = new double[m_nAngleSize * m_nMaxNZ];
		m_pCXi = new double[3 * m_nMaxNZ];

		m_pWArray = new double[m_nAngleSize * m_nMaxNZ * m_nMaxNZ];

		m_pTrace = new double[m_nMaxNZ];

		// fft buffers
		int nFFTSize = NXUtility::LengthofFFT(2 * m_nMaxNZ);
		m_pFFTBuffer = new double[2 * nFFTSize];
		m_pH1 = new double[nFFTSize];
		m_pH2 = new double[nFFTSize];
		m_pFFTOut1 = new double[m_nMaxNZ];
		m_pFFTOut2 = new double[m_nMaxNZ];
	}
	catch (std::bad_alloc)
	{
		return false;
	}

	m_p2DGGCoef = NXUtility::New2DMatrix<double>(m_nAngleSize, 3);

	// output
	if (m_bOutInversion && bExportR)
	{
		m_p2DR= NXUtility::New2DMatrix<float>(m_nAngleSize, m_nMaxNZ);
	}
	if (m_bOutInversion && bExportSeismic)
	{
		m_p2DSeismic = NXUtility::New2DMatrix<float>(m_nAngleSize, m_nMaxNZ);
	}

	if (m_bOutPrior)
	{
		m_p2DPrior = NXUtility::New2DMatrix<float>(m_nAngleSize, m_nMaxNZ);
	}

	return true;
}

void CXAVOSSInversion::SetDataBuffer(int zMin, int zMax, float* pZP0, float* pZS0, float* pZrho0, float* pSeismic)
{
	m_zmin = zMin;
	m_zmax = zMax;

	// tell if nz is same
	if (zMax - zMin + 1 == m_nZ)
		m_bSameNZ = true;
	else
		m_bSameNZ = false;

	m_nZ = zMax - zMin + 1;

	// invalid
	if (m_nZ < m_nWaveSize)
		return;

	// seismic normalized by wavelet
	for (int i = 0; i < m_nAngleSize; ++i)
	{
		double dFactor = 1.0 / m_vecMaxWaveletValue[i];

		for (int k = 0; k < m_nZ; ++k)
		{
			m_pD0[i*m_nZ + k] = pSeismic[i*m_nMaxNZ + k + m_zmin] * dFactor;
		}
	}

	// impedance (zp, zs zrho)
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pZ0[i] = pZP0[m_zmin + i];
		m_pZ0[m_nZ+i] = pZS0[m_zmin + i];
		m_pZ0[2*m_nZ+i] = pZrho0[m_zmin + i];
	}
}

void CXAVOSSInversion::_LowPassFilter()
{

}

void CXAVOSSInversion::_CalcU1()
{
	// log
	int nSize = 3 * m_nZ;
	vdLn(nSize, m_pZ0, m_pTmp);	

	// r = 0.5*D*log(Z)
	for (int i = 0; i < m_nZ-1; ++i)
	{
		m_pZ1[i] = m_pTmp[i + 1] - m_pTmp[i];
		m_pZ1[m_nZ + i] = m_pTmp[m_nZ + i + 1] - m_pTmp[m_nZ + i];
		m_pZ1[2 * m_nZ + i] = m_pTmp[2 * m_nZ + i + 1] - m_pTmp[2 * m_nZ + i];
	}
	m_pZ1[m_nZ - 1] = m_pZ1[m_nZ - 2];
	m_pZ1[2*m_nZ - 1] = m_pZ1[2*m_nZ - 2];
	m_pZ1[3 * m_nZ - 1] = m_pZ1[3 * m_nZ - 2];

	cblas_dscal(nSize, 0.5, m_pZ1, 1);

	// copy for prior
	if (m_bOutPrior)
	{
		memcpy(m_pZ2, m_pZ1, sizeof(double)*nSize);
	}
	// no inversion
	if (!m_bOutInversion)
		return;

	// mean
	double sum[] = { 0, 0, 0 };
	for (int i = 0; i < m_nZ; ++i)
	{
		sum[0] += m_pZ1[i];
		sum[1] += m_pZ1[m_nZ+i];
		sum[2] += m_pZ1[2*m_nZ+i];
	}
	sum[0] /= m_nZ;
	sum[1] /= m_nZ;
	sum[2] /= m_nZ;

	// normalization
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pZ1[i] -= sum[0];
		m_pZ1[m_nZ+i] -= sum[1];
		m_pZ1[2*m_nZ+i] -= sum[2];
	}


	// calc covariance r'*r
	double cov[9];
	memset(cov, 0, sizeof(double) * 9);
	cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, 3, m_nZ, 1., m_pZ1, m_nZ, 0, cov, 3);

	for (int i = 0; i < 9; ++i)
		cov[i] /= (m_nZ - 1);
	
	// svd, eigenvalue in ascending order
	double w[3];
	LAPACKE_dsyev(CblasColMajor, 'V', 'L', 3, cov, 3, w);

	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < 3; ++i)
		{
			m_u[i][j] = cov[j * 3 + i];
		}
	}

	// descending order
	for (int i = 0; i < 3; ++i)
		qSwap(m_u[i][0], m_u[i][2]);

}

void CXAVOSSInversion::_CalcXi()
{
	// xi = 0.5*log(zi/z0)
	int nSize = 3 * m_nZ;
	vdLn(nSize, m_pZ0, m_pTmp);
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pXi[i] = m_pTmp[i] - m_pTmp[0];
		m_pXi[m_nZ + i] = m_pTmp[m_nZ + i] - m_pTmp[m_nZ];
		m_pXi[2 * m_nZ + i] = m_pTmp[2 * m_nZ + i] - m_pTmp[2 * m_nZ];
	}
	cblas_dscal(3 * m_nZ, 0.5, m_pXi, 1);
}


// GG = G*U
void CXAVOSSInversion::_CalcGGCoef()
{
	for (int iBlock = 0; iBlock < m_nAngleSize; ++iBlock)
	{
		for (int jBlock = 0; jBlock < 3; ++jBlock)
		{
			m_p2DGGCoef[iBlock][jBlock] = 0;

			for (int k = 0; k < 3; ++k)
				m_p2DGGCoef[iBlock][jBlock] += m_p2DAkiCoef[iBlock][k] * m_u[k][jBlock];
		}
	}
}


void CXAVOSSInversion::_CalcW(int index)
{
	memset(m_pW, 0, sizeof(double)*m_nZ*m_nZ);
	int iPeakPosition = m_vecPeakPos[index];

	// wavelet matrix, column-major
	for (int j = 0, iStart = iPeakPosition; j < m_nZ; ++j, --iStart)
	{
		for (int i = qMax(0, iStart); i < m_nWaveSize && i - iStart < m_nZ; ++i)
		{
			m_pW[j*m_nZ + i - iStart] = m_p2DWaveletData[index][i];
		}
	}
}

// W'*W and W'*d
void CXAVOSSInversion::_CalcWWandWD()
{
	int nSize = m_nZ*m_nZ;
	memset(m_pWD, 0, sizeof(double)*m_nAngleSize*m_nZ);

	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		double* pWW = m_pWSquareArray + iAngle*nSize;

		if (m_bSameWavelet && iAngle != 0)
		{
			// copy
			//memcpy(pWW, m_pWSquareArray, sizeof(double)*nSize);
		}
		else
		{
			// W
			_CalcW(iAngle);

			//copy
			memcpy(m_pWArray + iAngle*nSize, m_pW, sizeof(double)*nSize);

			// W'*W		
			memset(pWW, 0, sizeof(double)*nSize);
			cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, m_nZ, m_nZ, 1., m_pW, m_nZ, 0, pWW, m_nZ);

			for (int j = 0; j < m_nZ; ++j)
			{
				for (int i = 0; i < j; ++i)
				{	
					pWW[j*m_nZ + i] = pWW[i*m_nZ + j];
				}
			}
		}

		// W'D
		cblas_dgemv(CblasColMajor, CblasTrans, m_nZ, m_nZ, 1., m_pW, m_nZ, m_pD0 + iAngle*m_nZ, 1, 0, m_pWD + iAngle*m_nZ, 1);
	}
}

// GG'*LAMBDA*GG
void CXAVOSSInversion::_CalcA1()
{
	int NZ = 3 * m_nZ;
	int nSize = m_nZ*m_nZ;
	for (int jBlock = 0; jBlock < 3; ++jBlock)
	{
		for (int iBlock = 0; iBlock < 3; ++iBlock)
		{
			if (m_bSameWavelet)
			{
				double dCoef = 0;
				for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
				{
					dCoef += m_p2DGGCoef[iAngle][iBlock] * m_p2DGGCoef[iAngle][jBlock];
				}

				dCoef *= m_vecLambda[0];

				for (int i = 0; i < nSize; ++i)
					m_pSquare[i] = dCoef*m_pWSquareArray[i];
			}
			else
			{
				memset(m_pSquare, 0, sizeof(double)*nSize);
				for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
				{
					double dCoef = m_p2DGGCoef[iAngle][iBlock] * m_p2DGGCoef[iAngle][jBlock];
					dCoef *= m_vecLambda[iAngle];
					double* pWSquare = m_pWSquareArray + iAngle*nSize;

					cblas_daxpy(nSize, dCoef, pWSquare, 1, m_pSquare, 1);
				}
			}

			//copy to A1
			int jMin = jBlock*m_nZ;
			int jMax = (jBlock + 1)*m_nZ;
			int iMin = iBlock*m_nZ;

			for (int j = jMin; j < jMax; ++j)
			{
				memcpy(m_pA1 + j*NZ + iMin, m_pSquare + (j - jMin)*m_nZ, sizeof(double)*m_nZ);
			}
		}
	}
}

// A2 = CC'*CC
void CXAVOSSInversion::_CalcA2()
{
	// m_pSquare = C1'*C1
	for (int i = 0; i < m_nZ; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			m_pWSquareArray[i*m_nZ + j] = m_nZ - i;
			m_pWSquareArray[j*m_nZ + i] = m_nZ - i;
		}
	}

	int NZ = 3 * m_nZ;
	int nSize = m_nZ*m_nZ;
	for (int jBlock = 0; jBlock < 3; ++jBlock)
	{
		for (int iBlock = 0; iBlock < 3; ++iBlock)
		{
			double dCoef = 0;
			for (int k = 0; k < 3; ++k)
			{
				dCoef += m_u[k][iBlock] * m_u[k][jBlock];
			}

			memset(m_pSquare, 0, sizeof(double)*nSize);
			cblas_daxpy(nSize, dCoef, m_pWSquareArray, 1, m_pSquare, 1);

			//copy to A2
			int jMin = jBlock*m_nZ;
			int jMax = (jBlock + 1)*m_nZ;
			int iMin = iBlock*m_nZ;

			for (int j = jMin; j < jMax; ++j)
			{
				memcpy(m_pA2 + j*NZ + iMin, m_pSquare + (j - jMin)*m_nZ, sizeof(double)*m_nZ);
			}
		}
	}
}

// B1 = GG'*LAMDA*d
void CXAVOSSInversion::_CalcB1()
{
	memset(m_pB1, 0, sizeof(double) * 3 * m_nZ);

	for (int iBlock = 0; iBlock < 3; ++iBlock)
	{
		double* pData = m_pB1 + iBlock*m_nZ;
		for (int i = 0; i < m_nZ; ++i)
		{			
			for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
			{
				pData[i] += m_p2DGGCoef[iAngle][iBlock] * m_pWD[iAngle*m_nZ + i] * m_vecLambda[iAngle];
			}
		}
	}
}

// B2 = CC'*Xi
void CXAVOSSInversion::_CalcB2()
{
	// C'*Xi
	for (int iBlock = 0; iBlock < 3; ++iBlock)
	{
		double* pCurrentData = m_pCXi + iBlock*m_nZ;
		double* pCurrentXi = m_pXi + iBlock*m_nZ;

		double dSum = 0;
		for (int i = m_nZ - 1; i >= 0; --i)
		{
			dSum += pCurrentXi[i];
			pCurrentData[i] = dSum;
		}
	}

	// B2
	memset(m_pB2, 0, sizeof(double) * 3 * m_nZ);
	for (int iBlock = 0; iBlock < 3; ++iBlock)
	{
		double* pData = m_pB2 + iBlock*m_nZ;

		for (int i = 0; i < m_nZ; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				pData[i] += m_u[j][iBlock] * m_pCXi[j*m_nZ + i];
			}
		}
	}
}


void CXAVOSSInversion::_CalcA()
{
	int nSize = 3 * m_nZ;
	memcpy(m_pA, m_pA1, sizeof(double)*nSize*nSize);

	double dCoef = m_vecAlpha[0] / (m_vecSigma[0] * m_vecSigma[0]);
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pA[i*nSize + i] += dCoef / (1. + SQR(m_pRR[i] / m_vecSigma[0]));
	}

	int n2XnZ = 2 * m_nZ;
	dCoef = m_vecAlpha[1] / (m_vecSigma[1] * m_vecSigma[1]);
	for (int i = m_nZ; i < n2XnZ; ++i)
	{
		m_pA[i*nSize + i] += dCoef / (1. + SQR(m_pRR[i] / m_vecSigma[1]));
	}

	dCoef = m_vecAlpha[2] / (m_vecSigma[2] * m_vecSigma[2]);
	for (int i = n2XnZ; i < nSize; ++i)
	{
		m_pA[i*nSize + i] += dCoef / (1. + SQR(m_pRR[i] / m_vecSigma[2]));
	}
}

void CXAVOSSInversion::_CalcPartAandB()
{
	_CalcGGCoef();
	_CalcWWandWD();
	_CalcA1();
	
	if (m_dBeta != 0)
		_CalcA2();

	// A
	int nSize = m_nZ*m_nZ * 9;
	if (m_dBeta != 0)
	{
		cblas_daxpy(nSize, m_dBeta, m_pA2, 1, m_pA1, 1);
	}

	// B
	nSize = 3 * m_nZ;
	_CalcB1();

	if (m_dBeta != 0)
		_CalcB2();

	if (m_dBeta != 0)
	{
		cblas_dcopy(nSize, m_pB2, 1, m_pB, 1);
		cblas_daxpby(nSize, m_dLamda, m_pB1, 1, m_dBeta, m_pB, 1);
	}
	else
	{
		memset(m_pB, 0, sizeof(double)*nSize);
		cblas_daxpy(nSize, m_dLamda, m_pB1, 1, m_pB, 1);
	}
}

void CXAVOSSInversion::_HandleInvalidInput()
{
	float fInvalid = (float)::g_dInvalidData;
	if (m_bOutInversion)
	{
		for (int i = 0; i < m_nMaxNZ; ++i)
		{
			// impedance
			m_pZp[i] = fInvalid;
			m_pZs[i] = fInvalid;
			m_pZRho[i] = fInvalid;

			m_pZpBP[i] = fInvalid;
			m_pZsBP[i] = fInvalid;
			m_pZRhoBP[i] = fInvalid;

			m_pZpMerged[i] = fInvalid;
			m_pZsMerged[i] = fInvalid;
			m_pZRhoMerged[i] = fInvalid;
		}
	}

	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		for (int i = 0; i < m_nMaxNZ; ++i)
		{
			if (m_p2DR)
				m_p2DR[iAngle][i] = fInvalid;

			if (m_p2DSeismic)
				m_p2DSeismic[iAngle][i] = fInvalid;

			if (m_p2DPrior)
				m_p2DPrior[iAngle][i] = fInvalid;
		}
	}
}
void CXAVOSSInversion::Calculate()
{
	// invalid data
	if (m_nZ < m_nWaveSize)
	{
		_HandleInvalidInput();
		return;
	}

	_CalcU1();

	if (m_bOutInversion)
	{
		_CalcXi();

		_CalcPartAandB();

		if (m_bAVOSSI)
		{
			// init cost function
			memset(m_pRR, 0, sizeof(double) * 3 * m_nZ);
			double dJ0 = _CalcCostFunction();

			double dJ;
			int iLoop;
			for (iLoop = 0; iLoop < m_dMaxLoopNum; ++iLoop)
			{
				// calc A
				_CalcA();

				// set B
				cblas_dcopy(3 * m_nZ, m_pB, 1, m_pRR, 1);

				// solve R		
				LAPACKE_dposv(LAPACK_COL_MAJOR, 'L', m_nZ * 3, 1, m_pA, m_nZ * 3, m_pRR, m_nZ * 3);

				dJ = _CalcCostFunction();

				if (qAbs(dJ0 - dJ) / (dJ0 + dJ) < m_dTol)
					break;

				dJ0 = dJ;
			}
		}
		else
		{
			// set B
			cblas_dcopy(3 * m_nZ, m_pB, 1, m_pRR, 1);

			// solve R		
			LAPACKE_dposv(LAPACK_COL_MAJOR, 'L', m_nZ * 3, 1, m_pA1, m_nZ * 3, m_pRR, m_nZ * 3);

		}

		_CalcR();

		_CalcImpedance();

		_CalcRCoef();

		_CalcSeismic();
	}

	// for prior 
	if (m_bOutPrior)
		_CalcPrior();

}
void CXAVOSSInversion::_CalcGGRR()
{
	// m_pTmp = GG*RR	
	memset(m_pTmp, 0, sizeof(double)*m_nAngleSize*m_nZ);

	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		double* pW = NULL;
		if (m_bSameWavelet)
			pW = m_pW;
		else
			pW = m_pWArray + iAngle*m_nZ*m_nZ;

		memset(m_pTrace, 0, sizeof(double)*m_nZ);
		cblas_daxpy(m_nZ, m_p2DGGCoef[iAngle][0], m_pRR, 1, m_pTrace, 1);
		cblas_daxpy(m_nZ, m_p2DGGCoef[iAngle][1], m_pRR + m_nZ, 1, m_pTrace, 1);
		cblas_daxpy(m_nZ, m_p2DGGCoef[iAngle][2], m_pRR + 2 * m_nZ, 1, m_pTrace, 1);

		cblas_dgemv(CblasColMajor, CblasNoTrans, m_nZ, m_nZ, 1., pW, m_nZ, m_pTrace, 1, 0, m_pTmp + iAngle*m_nZ, 1);
	}
}
double CXAVOSSInversion::_CalcJs()
{
	_CalcGGRR();

	// GG*RR-d
	int nSize = m_nAngleSize*m_nZ;
	for (int i = 0; i < nSize; ++i)
		m_pTmp[i] -= m_pD0[i];

	double Js = 0.;
	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		int index = iAngle*m_nZ;
		double JsTmp = 0.5*m_vecLambda[iAngle] * cblas_ddot(m_nZ, m_pTmp + index, 1, m_pTmp + index, 1);
		Js += JsTmp;
	}
	return Js;
}

double CXAVOSSInversion::_CalcJi()
{
	int nSize = 3 * m_nZ;

	// m_pTmp = CC*RR	
	memset(m_pTmp, 0, sizeof(double)*nSize);

	for (int i = 0; i < 3; ++i)
	{
		memset(m_pTrace, 0, sizeof(double)*m_nZ);
		cblas_daxpy(m_nZ, m_u[i][0], m_pRR, 1, m_pTrace, 1);
		cblas_daxpy(m_nZ, m_u[i][1], m_pRR + m_nZ, 1, m_pTrace, 1);
		cblas_daxpy(m_nZ, m_u[i][2], m_pRR + 2 * m_nZ, 1, m_pTrace, 1);

		double *pTmp = m_pTmp + i*m_nZ;
		pTmp[0] = m_pTrace[0];
		for (int k = 1; k < m_nZ; ++k)
		{
			pTmp[k] = pTmp[k - 1] + m_pTrace[k];
		}
	}

	// CC*RR-Xi
	for (int i = 0; i < nSize; ++i)
		m_pTmp[i] -= m_pXi[i];

	double Ji = 0.5*m_dBeta*cblas_ddot(nSize, m_pTmp, 1, m_pTmp, 1);

	return Ji;
}

double CXAVOSSInversion::_CalcJr()
{
	// 0.5*alphg*sum(ln(1+(ri/sigma)^2));
	double Jr = 0.;
	for (int i = 0; i < m_nZ; ++i)
		Jr += m_vecAlpha[0] * log(1 + SQR(m_pRR[i] / m_vecSigma[0]));

	int n2X = 2 * m_nZ;
	for (int i = m_nZ; i < n2X; ++i)
		Jr += m_vecAlpha[1] * log(1 + SQR(m_pRR[i] / m_vecSigma[1]));

	int n3X = 3 * m_nZ;
	for (int i = n2X; i < n3X; ++i)
		Jr += m_vecAlpha[2] * log(1 + SQR(m_pRR[i] / m_vecSigma[2]));

	Jr = 0.5*Jr;

	return Jr;
}
double CXAVOSSInversion::_CalcCostFunction()
{
	double Js = _CalcJs();
	double Jr = _CalcJr();

	double Ji = 0;
	if (m_dBeta != 0)
		Ji = _CalcJi();

	return Js + Jr + Ji;
}

void CXAVOSSInversion::_CalcR()
{
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pR[i]				= m_u[0][0] * m_pRR[i] + m_u[0][1] * m_pRR[m_nZ + i] + m_u[0][2] * m_pRR[2 * m_nZ + i];
		m_pR[m_nZ + i]		= m_u[1][0] * m_pRR[i] + m_u[1][1] * m_pRR[m_nZ + i] + m_u[1][2] * m_pRR[2 * m_nZ + i];
		m_pR[2 * m_nZ + i]	= m_u[2][0] * m_pRR[i] + m_u[2][1] * m_pRR[m_nZ + i] + m_u[2][2] * m_pRR[2 * m_nZ + i];
	}
}

void CXAVOSSInversion::_Filtering()
{
	// output types
	if (m_nOutType == 1) // zp, vpvs, rho
	{
		for (int i = 0; i < m_nZ; ++i)
		{
			m_pZ0[m_nZ + i] = m_pZ0[i] / m_pZ0[m_nZ + i];
			m_pTmp[m_nZ + i] = m_pTmp[i] / m_pTmp[m_nZ + i];
		}
	}
	else if (m_nOutType == 2) //vp, vs, rho
	{
		for (int i = 0; i < m_nZ; ++i)
		{
			m_pZ0[i] /= m_pZ0[2 * m_nZ + i];
			m_pZ0[m_nZ + i] /= m_pZ0[2 * m_nZ + i];

			m_pTmp[i] /= m_pTmp[2 * m_nZ + i];
			m_pTmp[m_nZ + i] /= m_pTmp[2 * m_nZ + i];
		}
	}


	// first component 
	// low pass
	NXUtility::DigitalFilter(m_nZ, m_pZ0, m_pFFTOut1, m_dSamplingRate, 0, 0, m_dLowCut, m_dLowOverlap, m_pFFTBuffer, m_pH1, m_pH2);

	// band pass
	NXUtility::DigitalFilter(m_nZ, m_pTmp, m_pFFTOut2, m_dSamplingRate, m_dLowCut, m_dLowOverlap, m_dHighCut, m_dHighOverlap, m_pFFTBuffer, m_pH1, m_pH2);

	for (int i = 0; i < m_nZ; ++i)
	{
		m_pTmp2[i] = m_pFFTOut2[i];
		m_pTmp3[i] = m_pFFTOut1[i] + m_pFFTOut2[i];
	}

	// second component
	// low pass
	NXUtility::DigitalFilter(m_nZ, m_pZ0+m_nZ, m_pFFTOut1, m_dSamplingRate, 0, 0, m_dLowCut, m_dLowOverlap, m_pFFTBuffer, m_pH1, m_pH2);

	// band pass
	NXUtility::DigitalFilter(m_nZ, m_pTmp+m_nZ, m_pFFTOut2, m_dSamplingRate, m_dLowCut, m_dLowOverlap, m_dHighCut, m_dHighOverlap, m_pFFTBuffer, m_pH1, m_pH2);

	for (int i = 0; i < m_nZ; ++i)
	{
		m_pTmp2[i + m_nZ] = m_pFFTOut2[i];
		m_pTmp3[i + m_nZ] = m_pFFTOut1[i] + m_pFFTOut2[i];
	}

	// third component
	// low pass
	NXUtility::DigitalFilter(m_nZ, m_pZ0 + 2*m_nZ, m_pFFTOut1, m_dSamplingRate, 0, 0, m_dLowCut, m_dLowOverlap, m_pFFTBuffer, m_pH1, m_pH2);

	// band pass
	NXUtility::DigitalFilter(m_nZ, m_pTmp + 2*m_nZ, m_pFFTOut2, m_dSamplingRate, m_dLowCut, m_dLowOverlap, m_dHighCut, m_dHighOverlap, m_pFFTBuffer, m_pH1, m_pH2);

	for (int i = 0; i < m_nZ; ++i)
	{
		m_pTmp2[i + 2 * m_nZ] = m_pFFTOut2[i];
		m_pTmp3[i + 2 * m_nZ] = m_pFFTOut1[i] + m_pFFTOut2[i];
	}
}

void CXAVOSSInversion::_CalcImpedance()
{
	//z
	double dRpSum(0), dRSSum(0), dRRhoSum(0);
	for (int i = 0; i < m_nZ; ++i)
	{
		dRpSum += m_pR[i];
		m_pTmp[i] = m_pZ0[0] * exp(2.*dRpSum);

		dRSSum += m_pR[m_nZ + i];
		m_pTmp[m_nZ + i] = m_pZ0[m_nZ] * exp(2.*dRSSum);

		dRRhoSum += m_pR[2 * m_nZ + i];
		m_pTmp[2 * m_nZ + i] = m_pZ0[2 * m_nZ] * exp(2.*dRRhoSum);
	}

	if (m_bApplyFiltering)
		 _Filtering();


	float fInvalid = (float)::g_dInvalidData;
	for (int i = 0; i < m_nMaxNZ; ++i)
	{
		if (i < m_zmin || i > m_zmax)
		{
			m_pZp[i] = fInvalid;
			m_pZs[i] = fInvalid;
			m_pZRho[i] = fInvalid;

			m_pZpBP[i] = fInvalid;
			m_pZsBP[i] = fInvalid;
			m_pZRhoBP[i] = fInvalid;

			m_pZpMerged[i] = fInvalid;
			m_pZsMerged[i] = fInvalid;
			m_pZRhoMerged[i] = fInvalid;
		}
		else
		{
			m_pZp[i]	= (float) m_pTmp[i - m_zmin];
			m_pZs[i]	= (float)m_pTmp[m_nZ + i - m_zmin];
			m_pZRho[i]	= (float)m_pTmp[2 * m_nZ + i - m_zmin];

			m_pZpBP[i]	 = (float)m_pTmp2[i - m_zmin];
			m_pZsBP[i]	 = (float)m_pTmp2[m_nZ + i - m_zmin];
			m_pZRhoBP[i] = (float)m_pTmp2[2 * m_nZ + i - m_zmin];

			m_pZpMerged[i]	 = (float)m_pTmp3[i - m_zmin];
			m_pZsMerged[i]	 = (float)m_pTmp3[m_nZ + i - m_zmin];
			m_pZRhoMerged[i] = (float)m_pTmp3[2 * m_nZ + i - m_zmin];
		}
	}	

	// rerange the data according to output type
	/*if (m_nOutType == 1)
	{
	for (int i = m_zmin; i <= m_zmax; ++i)
	{
	m_pZs[i] = m_pZp[i] / m_pZs[i];

	m_pZsBP[i] = m_pZpBP[i] / m_pZsBP[i];

	m_pZsMerged[i] = m_pZpMerged[i] / m_pZsMerged[i];
	}
	}
	else if (m_nOutType == 2)
	{
	for (int i = m_zmin; i <= m_zmax; ++i)
	{
	m_pZp[i] /= m_pZRho[i];
	m_pZs[i] /= m_pZRho[i];

	m_pZpBP[i] /= m_pZRhoBP[i];
	m_pZsBP[i] /= m_pZRhoBP[i];

	m_pZpMerged[i] /= m_pZRhoMerged[i];
	m_pZsMerged[i] /= m_pZRhoMerged[i];
	}
	}*/

	// recalculate R
	if (m_bApplyFiltering && (m_p2DR || m_p2DSeismic))
	{		
		for (int i = 0; i < m_nZ; ++i)
		{
			m_pTmp[i] = log(m_pTmp[i]);
		}
		
		// R_zp, R_zs, R_rho
		for (int i = 0; i < 3*m_nZ - 1; ++i)
			m_pR[i] = 0.5*(m_pTmp[i + 1] - m_pTmp[i]);

		m_pR[m_nZ - 1] = m_pR[m_nZ - 2];
		m_pR[2*m_nZ - 1] = m_pR[2*m_nZ - 2];
		m_pR[3 * m_nZ - 1] = m_pR[3 * m_nZ - 2];

		//RR
		for (int i = 0; i < m_nZ; ++i)
		{
			m_pRR[i]			= m_u[0][0] * m_pR[i] + m_u[1][0] * m_pR[m_nZ + i] + m_u[2][0] * m_pR[2 * m_nZ + i];
			m_pRR[m_nZ + i]		= m_u[0][1] * m_pR[i] + m_u[1][1] * m_pR[m_nZ + i] + m_u[2][1] * m_pR[2 * m_nZ + i];
			m_pRR[2 * m_nZ + i] = m_u[0][2] * m_pR[i] + m_u[1][2] * m_pR[m_nZ + i] + m_u[2][2] * m_pR[2 * m_nZ + i];
		}
	}

}

void CXAVOSSInversion::_CalcRCoef()
{
	if (!m_p2DR)
		return;

	float fInvalid = (float)::g_dInvalidData;
	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		for (int i = 0; i < m_nZ; ++i)
		{
			m_pTmp[i] = m_p2DAkiCoef[iAngle][0] * m_pR[i] + m_p2DAkiCoef[iAngle][1] * m_pR[m_nZ + i] + m_p2DAkiCoef[iAngle][2] * m_pR[2 * m_nZ + i];
		}

		for (int i = 0; i < m_nMaxNZ; ++i)
		{
			if (i < m_zmin || i > m_zmax)
			{
				m_p2DR[iAngle][i] = fInvalid;
			}
			else
			{
				m_p2DR[iAngle][i] = (float) m_pTmp[i - m_zmin];
			}
		}
	}
}


void CXAVOSSInversion::_CalcSeismic()
{
	if (!m_p2DSeismic)
		return;

	_CalcGGRR();

	float fInvalid = (float)::g_dInvalidData;
	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		for (int i = 0; i < m_nMaxNZ; ++i)
		{
			if (i < m_zmin || i > m_zmax)
			{
				m_p2DSeismic[iAngle][i] = fInvalid;
			}
			else
			{
				m_p2DSeismic[iAngle][i] = (float)m_pTmp[iAngle*m_nZ + i - m_zmin];
			}
		}
	}
}

void CXAVOSSInversion::_CalcPrior()
{
	if (!m_bOutPrior)
		return;

	float fInvalid = (float)::g_dInvalidData;
	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		// Get W matrix
		double* pW = NULL;
		if (m_bOutInversion)
		{
			if (m_bSameWavelet)
				pW = m_pW;
			else
				pW = m_pWArray + iAngle*m_nZ*m_nZ;
		}
		else
		{
			_CalcW(iAngle);
			pW = m_pW;
		}

		// Get R
		for (int k = 0; k < m_nZ; ++k)
		{
			m_pTmp[k] = m_p2DAkiCoef[iAngle][0] * m_pZ2[k] + m_p2DAkiCoef[iAngle][1] * m_pZ2[k+m_nZ] + m_p2DAkiCoef[iAngle][2] * m_pZ2[k+2*m_nZ];
		}

		// W*R
		memset(m_pTmp2, 0, sizeof(double)*m_nZ);
		cblas_dgemv(CblasColMajor, CblasNoTrans, m_nZ, m_nZ, 1., pW, m_nZ, m_pTmp, 1, 0, m_pTmp2, 1);

		// write to prior buffers
		for (int i = 0; i < m_nMaxNZ; ++i)
		{
			if (i < m_zmin || i > m_zmax)
			{
				m_p2DPrior[iAngle][i] = fInvalid;
			}
			else
			{
				m_p2DPrior[iAngle][i] = static_cast<float>(m_pTmp2[i - m_zmin]* m_vecMaxWaveletValue[iAngle]);
			}
		}

	}
}

void CXAVOSSInversion::GetThreeComponents(vector<float*>& vec3Component)
{
	vec3Component.clear();
	vec3Component.push_back(m_pZp);
	vec3Component.push_back(m_pZs);
	vec3Component.push_back(m_pZRho);

	vec3Component.push_back(m_pZpBP);
	vec3Component.push_back(m_pZsBP);
	vec3Component.push_back(m_pZRhoBP);

	vec3Component.push_back(m_pZpMerged);
	vec3Component.push_back(m_pZsMerged);
	vec3Component.push_back(m_pZRhoMerged);
}

