#include "xavoinversion.h"
#include <cmath>
#include <cassert>
#include "xutility.h"
#include "xglobal.h"
#include "xmathmacro.h"
#include "xfunctiontemplate.h"
#include "xblas.h"
#include "mkl.h"

CXAVOInversion::CXAVOInversion()
{
	m_nZ = -1;

	m_pWaveletBuffer = NULL;
	p2DWaveletData = NULL;

	m_pINIT0 = NULL;
	m_pMeanModel = NULL;
	m_pX = NULL;
	m_pB = NULL;

	m_pInSeismic = NULL;
	m_p2DInSeismic = NULL;

	m_pZP0 = NULL;
	m_pD0 = NULL;
	m_pZP = NULL;
	m_pZS = NULL;
	m_pD = NULL;

	m_pTmp = NULL;
	m_pW = NULL;
	m_pWD = NULL;
	m_pG = NULL;
	m_pA = NULL;
	m_pTmp2 = NULL;
	m_pWDSquare = NULL;

	m_p2DTmp = NULL;
	m_p2DW = NULL;
	m_p2DWD = NULL;
	m_p2DG = NULL;
	m_p2DA = NULL;
	m_p2DWDSquare = NULL;

	m_p2DCoef = NULL;
	m_p2DRCoef = NULL;
	m_p2DSSeismic = NULL;

	m_pCGBuffer = NULL;
}

CXAVOInversion::~CXAVOInversion()
{
	if (m_pWaveletBuffer)	{ delete[]m_pWaveletBuffer; m_pWaveletBuffer = NULL; }
	if (p2DWaveletData)		{ delete[]p2DWaveletData; p2DWaveletData = NULL; }

	if (m_pINIT0)			{ delete[]m_pINIT0; m_pINIT0 = NULL; }
	if (m_pMeanModel)		{ delete[]m_pMeanModel; m_pMeanModel = NULL; }
	if (m_pX)				{ delete[]m_pX; m_pX = NULL; }
	if (m_pB)				{ delete[]m_pB; m_pB = NULL; }

	if (m_pInSeismic)		{ delete[]m_pInSeismic; m_pInSeismic = NULL; }
	if (m_p2DInSeismic)		{ delete[]m_p2DInSeismic; m_p2DInSeismic = NULL; }

	if (m_pZP0)				{ delete[]m_pZP0; m_pZP0 = NULL; }
	if (m_pD0)				{ delete[]m_pD0; m_pD0 = NULL; }
	if (m_pZP)				{ delete[]m_pZP; m_pZP = NULL; }
	if (m_pZS)				{ delete[]m_pZS; m_pZS = NULL; }
	if (m_pD)				{ delete[]m_pD; m_pD = NULL; }

	if (m_pTmp)				{ delete[]m_pTmp; m_pTmp = NULL; }
	if (m_pW)				{ delete[]m_pW; m_pW = NULL; }
	if (m_pWD)				{ delete[]m_pWD; m_pWD = NULL; }
	if (m_pG)				{ delete[]m_pG; m_pG = NULL; }
	if (m_pA)				{ delete[]m_pA; m_pA = NULL; }
	if (m_pTmp2)			{ delete[]m_pTmp2; m_pTmp2 = NULL; }
	if (m_pWDSquare)		{ delete[]m_pWDSquare; m_pWDSquare = NULL; }

	if (m_p2DTmp)			{ delete[]m_p2DTmp; m_p2DTmp = NULL; }
	if (m_p2DW)				{ delete[]m_p2DW; m_p2DW = NULL; }
	if (m_p2DWD)			{ delete[]m_p2DWD; m_p2DWD = NULL; }
	if (m_p2DG)				{ delete[]m_p2DG; m_p2DG = NULL; }
	if (m_p2DA)				{ delete[]m_p2DA; m_p2DA = NULL; }
	if (m_p2DWDSquare)		{ delete[]m_p2DWDSquare; m_p2DWDSquare = NULL; }
	
	if (m_p2DRCoef)			{ NXUtility::Free2DMatrix<float>(m_p2DRCoef); m_p2DRCoef = NULL; }
	if (m_p2DSSeismic)		{ NXUtility::Free2DMatrix<float>(m_p2DSSeismic); m_p2DSSeismic = NULL; }

	if (m_p2DCoef)			{ NXUtility::Free2DMatrix<double>(m_p2DCoef); m_p2DCoef = NULL; }

	if (m_pCGBuffer)		{ delete[]m_pCGBuffer; m_pCGBuffer = NULL; }
}

void CXAVOInversion::InitWaveletPara(vector<float>& vecAngle, int nWaveSize, vector<vector<float> >& vec2DWavelet)
{
	m_nAngleSize = (int)vecAngle.size();
	m_nWaveSize = nWaveSize;

	assert(vecAngle.size() == vec2DWavelet.size());

	// angles
	m_vecAngle.resize(m_nAngleSize);
	for (int i = 0; i < m_nAngleSize; ++i)
		m_vecAngle[i] = vecAngle[i];

	// wavelet buffer
	m_pWaveletBuffer = new double[m_nAngleSize*m_nWaveSize];
	p2DWaveletData = new double*[m_nWaveSize];
	for (int i = 0; i < m_nAngleSize; ++i)
		p2DWaveletData[i] = m_pWaveletBuffer + i*m_nWaveSize;

	// wavelet
	for (int i = 0; i < m_nAngleSize; ++i)
	{
		for (int j = 0; j < m_nWaveSize; ++j)
			p2DWaveletData[i][j] = vec2DWavelet[i][j];
	}

	// calc peak position and max value
	for (int i = 0; i < m_nAngleSize; ++i)
	{
		double dMaxValue = 0;
		int iPeakPos = 0;
		for (int j = 0; j < m_nWaveSize; ++j)
		{
			if (qAbs(p2DWaveletData[i][j]) > dMaxValue)
			{
				dMaxValue = qAbs(p2DWaveletData[i][j]);
				iPeakPos = j;
			}
		}
		m_vecPeakPos.push_back(iPeakPos);
		m_vecMaxWaveletValue.push_back(dMaxValue);
	}

	m_bSameWavelet = true;
	for (int i = 1; i < m_nAngleSize; ++i)
	{
		if (0 != memcmp(p2DWaveletData[0], p2DWaveletData[i], sizeof(double)*m_nWaveSize))
		{
			m_bSameWavelet = false;
			break;
		}
	}
}

void CXAVOInversion::InitInversionPara(double lambda, double gamma, double maxIterationNum, double tol)
{
	m_dLambda = lambda;
	m_dGamma = gamma;
	m_dMaxLoopNum = maxIterationNum;
	m_dTol = tol;
}

bool CXAVOInversion::CreateBuffers(int nMaxNZ, bool bExportR, bool bExportSeismic)
{
	m_nMaxNZ = nMaxNZ;

	try
	{
		m_pINIT0 = new double[3 * m_nMaxNZ];
		m_pMeanModel = new double[3 * m_nMaxNZ];
		m_pX = new double[3 * m_nMaxNZ];
		m_pB = new double[3 * m_nMaxNZ];

		m_pInSeismic = new double[m_nAngleSize * m_nMaxNZ];	
		m_p2DInSeismic = new double* [m_nAngleSize];		

		m_pZP0 = new float[m_nMaxNZ];
		m_pZS0 = new float[m_nMaxNZ];
		m_pD0 = new float[m_nMaxNZ];
		m_pZP = new float[m_nMaxNZ];
		m_pZS = new float[m_nMaxNZ];
		m_pD = new float[m_nMaxNZ];
		

		m_pTmp = new double[m_nMaxNZ * m_nMaxNZ];
		m_pW = new double[m_nMaxNZ*m_nMaxNZ];
		m_pWD = new double[m_nMaxNZ*m_nMaxNZ];
		m_pG = new double[m_nMaxNZ*m_nAngleSize*m_nMaxNZ * 3];
		m_pA = new double[m_nMaxNZ * 3 * m_nMaxNZ * 3];		
		m_pTmp2 = new double[m_nMaxNZ * 3 * m_nMaxNZ * 3];
		m_pWDSquare = new double[m_nMaxNZ*m_nAngleSize*m_nMaxNZ];

		m_p2DTmp = new double*[m_nMaxNZ];
		m_p2DW = new double*[m_nMaxNZ];
		m_p2DWD = new double*[m_nMaxNZ];
		m_p2DG = new double*[m_nMaxNZ*3];
		m_p2DA = new double*[m_nMaxNZ * 3 ];	
		m_p2DWDSquare = new double*[m_nAngleSize];

		m_pCGBuffer = new double[10 * m_nMaxNZ*3];
	}
	catch (std::bad_alloc)
	{
		return false;
	}

	m_p2DCoef = NXUtility::New2DMatrix<double>(m_nAngleSize, 3);

	// output
	if (bExportR)
	{
		m_p2DRCoef = NXUtility::New2DMatrix<float>(m_nAngleSize, m_nMaxNZ);
	}
	if (bExportSeismic)
	{
		m_p2DSSeismic = NXUtility::New2DMatrix<float>(m_nAngleSize, m_nMaxNZ);
	}

	_CalcAkiCoef();

	return true;
}

void CXAVOInversion::SetDataBuffer(int zMin, int zMax, float* pZP0, float* pZS0, float* pD0, float* pSeismic, vector<double>& vecMaxValue)
{
	m_zmin = zMin;
	m_zmax = zMax;

	// tell if nz is same
	if (zMax - zMin + 1 == m_nZ)
		m_bSameNZ = true;
	else
		m_bSameNZ = false;

	m_nZ = zMax - zMin + 1;

	// seismic
	for (int i = 0; i < m_nAngleSize; ++i)
	{
		m_p2DInSeismic[i] = m_pInSeismic + i*m_nZ;
	}

	for (int i = 0; i < m_nAngleSize; ++i)
	{
		for (int k = 0; k < m_nZ; ++k)
		{
			m_p2DInSeismic[i][k] = pSeismic[i*m_nMaxNZ + k + m_zmin];// / m_vecMaxWaveletValue[i];
		}
	}

	// impedance
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pZP0[i] = pZP0[m_zmin + i];
		m_pZS0[i] = pZS0[m_zmin + i];
		m_pD0[i] = pD0[m_zmin + i];
	}
}

void CXAVOInversion::_Set2DBuffer()
{
	// 3 terms
	for (int j = 0; j < 3; ++j)
	{
		m_p2DINIT0[j] = m_pINIT0 + j*m_nZ;
		m_p2DMeanModel[j] = m_pMeanModel + j*m_nZ;
		m_p2DX[j] = m_pX + j*m_nZ;
		m_p2DB[j] = m_pB + j*m_nZ;
	}

	// m_nz
	for (int j = 0; j < m_nZ; ++j)
	{
		m_p2DTmp[j] = m_pTmp + j*m_nZ;
		m_p2DW[j] = m_pW + j*m_nZ;
		m_p2DWD[j] = m_pWD + j*m_nZ;
	}

	// 3*m_nZ
	int nSize = 3 * m_nZ;
	for (int j = 0; j < nSize; ++j)
	{
		m_p2DG[j] = m_pG + j*m_nAngleSize*m_nZ;
		m_p2DA[j] = m_pA + j*nSize;
	}

	// m_nAngleSize*m_nZ
	nSize = m_nZ * m_nZ;
	for (int j = 0; j < m_nAngleSize; ++j)
	{		
		m_p2DWDSquare[j] = m_pWDSquare + j*nSize;
	}
}
void CXAVOInversion::Calculate()
{
	if (m_nZ < m_nWaveSize)
	{
		// impedance
		float fInvalid = (float)::g_dInvalidData;
		for (int i = 0; i < m_nMaxNZ; ++i)
		{
			m_pZP0[i] = fInvalid;
			m_pZS0[i] = fInvalid;
			m_pD0[i] = fInvalid;
		}
		return;
	}

	if (!m_bSameNZ)
		_Set2DBuffer();

	_CalcInit();

	_CalcGAndGTG();

	_CalcCovGTG();
	for (int i = 0; i < 3 * m_nZ; ++i)
	{
		m_pA[i * 3 * m_nZ + i] += m_dLambda;
	}

	// G'*d
	memset(m_pTmp, 0, sizeof(double) * 3 * m_nZ);
	cblas_dgemv(CblasColMajor, CblasTrans, m_nZ*m_nAngleSize, m_nZ * 3, 1.0, m_pG, m_nZ*m_nAngleSize, m_pInSeismic, 1, 0, m_pTmp, 1);

	// Cm*G'*d
	_CalcCovGTS();

	cblas_daxpy(m_nZ * 3, m_dLambda, m_pMeanModel, 1, m_pB, 1);

	int nLoopNum;
	double dErr;
	memcpy(m_pX, m_pINIT0, sizeof(double) * 3 * m_nZ);
	_SolveLinearEQUWithBICG(m_nZ * 3, m_pA, m_pX, m_pB, m_dTol, m_dMaxLoopNum, nLoopNum, dErr);

	//memcpy(m_pX, m_pB, sizeof(double) * 3 * m_nZ);
	//LAPACKE_dgels(LAPACK_COL_MAJOR, 'N', m_nZ * 3, m_nZ * 3, 1, m_pA, m_nZ * 3, m_pX, m_nZ * 3);


	// calculate zp, zs and D
	float fInvalid = (float)::g_dInvalidData;
	for (int i = 0; i < m_nMaxNZ; ++i)
	{
		if (i < m_zmin || i > m_zmax)
		{
			m_pZP[i] = fInvalid;
			m_pZS[i] = fInvalid;
			m_pD[i] = fInvalid;
		}
		else
		{
			m_pZP[i] = exp(m_pX[i - m_zmin]);
			m_pZS[i] = exp(m_pX[m_nZ + i - m_zmin]);
			m_pD[i] = exp(m_pX[2 * m_nZ + i - m_zmin]);
		}
	}

	// calculate Seismic
	_CalcSeismic();

	// calc RCoef
	_CalcRCoef();

}

void CXAVOInversion::_CalcSeismic()
{
	if (!m_p2DSSeismic)
		return;

	// Seismic = G*X
	memset(m_pTmp, 0, sizeof(double)*m_nAngleSize*m_nZ);
	cblas_dgemv(CblasColMajor, CblasNoTrans, m_nAngleSize*m_nZ, 3 * m_nZ, 1.0, m_pG, m_nAngleSize*m_nZ, m_pX, 1, 0, m_pTmp, 1);
	float fInvalid = (float)::g_dInvalidData;
	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		for (int i = 0; i < m_nMaxNZ; ++i)
		{
			if (i < m_zmin || i > m_zmax)
			{
				m_p2DSSeismic[iAngle][i] = fInvalid;
			}
			else
			{
				m_p2DSSeismic[iAngle][i] = m_pTmp[iAngle*m_nZ + i - m_zmin];
			}
		}
	}
}

void CXAVOInversion::_CalcRCoef()
{
	if (!m_p2DRCoef)
		return;

	//calc D
	memset(m_pTmp, 0, sizeof(double)*m_nZ*m_nZ);
	for (int j = 0; j < m_nZ; ++j)
	{
		if (j == 0)
		{
			m_p2DTmp[j][0] = -0.5;
		}
		else if (j == m_nZ - 2)
		{
			m_p2DTmp[j][j-1] = 0.5;
			m_p2DTmp[j][j] = -0.5;
			m_p2DTmp[j][j+1] = -0.5;
		}
		else if (j == m_nZ - 1)
		{
			m_p2DTmp[j][j] = 0.5;
			m_p2DTmp[j][j-1] = 0.5;
		}
		else
		{
			m_p2DTmp[j][j] = -0.5;
			m_p2DTmp[j][j-1] = 0.5;
		}
	}

	float fInvalid = (float)::g_dInvalidData;
	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		// calc (C1*D C2*D, C3*D)
		memset(m_pWDSquare, 0, sizeof(double) * 3 * m_nZ*m_nZ);

		cblas_daxpy(m_nZ*m_nZ, m_p2DCoef[iAngle][0], m_pTmp, 1, m_pWDSquare, 1);
		cblas_daxpy(m_nZ*m_nZ, m_p2DCoef[iAngle][1], m_pTmp, 1, m_pWDSquare + m_nZ*m_nZ, 1);
		cblas_daxpy(m_nZ*m_nZ, m_p2DCoef[iAngle][2], m_pTmp, 1, m_pWDSquare + 2 * m_nZ*m_nZ, 1);

		// calc R Coef

		memset(m_pB, 0, sizeof(double)*m_nZ);
		cblas_dgemv(CblasColMajor, CblasNoTrans, m_nZ, 3 * m_nZ, 1.0, m_pWDSquare, m_nZ, m_pX, 1, 0, m_pB, 1);

		// set data
		for (int i = 0; i < m_nMaxNZ; ++i)
		{
			if (i < m_zmin || i > m_zmax)
			{
				m_p2DRCoef[iAngle][i] = fInvalid;
			}
			else
			{
				m_p2DRCoef[iAngle][i] = m_pB[i - m_zmin];
			}
		}
	}
}

void CXAVOInversion::_CalcInit()
{
	// Init0
	// Zp0, Zs0, D0
	for (int i = 0; i < m_nZ; ++i)
	{
		m_p2DINIT0[0][i] = log(m_pZP0[i]);
		m_p2DINIT0[1][i] = log(m_pZS0[i]);
		m_p2DINIT0[2][i] = log(m_pD0[i]);
	}

	// mean model
	double dSumZp(0), dSumZs(0), dSumD(0);
	for (int i = 0; i < m_nZ; ++i)
	{
		dSumZp += m_p2DINIT0[0][i];
		dSumZs += m_p2DINIT0[1][i];
		dSumD  += m_p2DINIT0[2][i];
	}

	dSumZp /= m_nZ;
	dSumZs /= m_nZ;
	dSumD /= m_nZ;
	for (int i = 0; i < m_nZ; ++i)
	{
		m_p2DMeanModel[0][i] = dSumZp;
		m_p2DMeanModel[1][i] = dSumZs;
		m_p2DMeanModel[2][i] = dSumD;
	}

	// covariance matrix
	for (int i = 0; i < m_nZ; ++i)
	{
		m_p2DTmp[0][i] = m_p2DINIT0[0][i] - dSumZp;
		m_p2DTmp[1][i] = m_p2DINIT0[1][i] - dSumZs;
		m_p2DTmp[2][i] = m_p2DINIT0[2][i] - dSumD;
	}

	// calc covariance D'*D
	memset(m_CovMatrix, 0, sizeof(double) * 9);
	cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, 3, m_nZ, 1., m_pTmp, m_nZ, 0, m_CovMatrix, 3);
	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < j; ++i)
		{
			m_CovMatrix[j * 3 + i] = m_CovMatrix[i * 3 + j];
		}
	}

	// divide by (m_nZ-1) to normalize
	cblas_dscal(9, 1. / (m_nZ - 1), m_CovMatrix, 1);
}



// wavelet matrix
void CXAVOInversion::_CalcW(int index)
{
	memset(m_pW, 0, sizeof(double)*m_nZ*m_nZ);
	for (int j = 0, iStart = m_vecPeakPos[index]; j < m_nZ; ++j, --iStart)
	{
		for (int i = qMax(0, iStart); i < m_nWaveSize && i - iStart < m_nZ; ++i)
		{
			m_p2DW[j][i - iStart] = p2DWaveletData[index][i];
		}
	}
}

// W*D = 1/2*(-W0, W0-W1, W1-W2, ..., Wn-3 - Wn-2 - Wn-1,  Wn-1+Wn-2)
void CXAVOInversion::_CalcWD()
{
	memcpy(m_pWD + m_nZ, m_pW, sizeof(double)*m_nZ*(m_nZ - 1));
	for (int j = 0; j < m_nZ; ++j)
	{
		if (j == 0)
		{
			memset(m_pWD, 0, sizeof(double)*m_nZ);
			cblas_daxpy(m_nZ, -1, m_pW, 1, m_pWD, 1);
		}
		else if (j == m_nZ - 2)
		{
			cblas_daxpy(m_nZ, -1, m_p2DW[j],     1, m_p2DWD[j], 1);
			cblas_daxpy(m_nZ, -1, m_p2DW[j + 1], 1, m_p2DWD[j], 1);
		}
		else if (j == m_nZ - 1)
		{
			cblas_daxpy(m_nZ, 1, m_p2DW[j], 1, m_p2DWD[j], 1);
		}
		else
		{
			cblas_daxpy(m_nZ, -1, m_p2DW[j], 1, m_p2DWD[j], 1);
		}
	}
	cblas_dscal(m_nZ*m_nZ, 0.5, m_pWD, 1);
}



void CXAVOInversion::_CalcAkiCoef()
{
	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		// theta
		double theta = m_vecAngle[iAngle] * M_RAD;
		double C1 = 1 + SQR(tan(theta));
		double C2 = -8.0*m_dGamma*m_dGamma*SQR(sin(theta));
		double C3 = 4 * m_dGamma*m_dGamma*SQR(sin(theta)) - SQR(tan(theta));

		m_p2DCoef[iAngle][0] = C1;
		m_p2DCoef[iAngle][1] = C2;
		m_p2DCoef[iAngle][2] = C3;
	}

}

void CXAVOInversion::_CalcGAndGTG()
{
	if (m_bSameWavelet && m_bSameNZ)
		return;

	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		if (m_bSameWavelet && iAngle != 0)
		{
			memcpy(m_p2DWDSquare[iAngle], m_p2DWDSquare[0], sizeof(double)*m_nZ*m_nZ);
		}
		else
		{
			// Calculate Wavelet matrix
			_CalcW(iAngle);

			// Calculate W*D
			_CalcWD();

			// WD'*WD
			memset(m_pTmp, 0, sizeof(double)*m_nZ*m_nZ);
			cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, m_nZ, m_nZ, 1., m_pWD, m_nZ, 0, m_pTmp, m_nZ);
			for (int j = 0; j < m_nZ; ++j)
			{
				for (int i = 0; i < j; ++i)
				{
					m_p2DTmp[j][i] = m_p2DTmp[i][j];
				}
			}
			memcpy(m_p2DWDSquare[iAngle], m_pTmp, sizeof(double)*m_nZ*m_nZ);
		}

		//copy to G
		for (int jj = 0; jj < 3; ++jj)
		{
			memset(m_pTmp, 0, sizeof(double)*m_nZ*m_nZ);
			cblas_daxpy(m_nZ*m_nZ, m_p2DCoef[iAngle][jj], m_pWD, 1, m_pTmp, 1);
			int index = jj*m_nZ;
			for (int j = 0; j < m_nZ; ++j)
			{
				memcpy(m_p2DG[index + j] + iAngle*m_nZ, m_p2DTmp[j], sizeof(double)*m_nZ);
			}
		}
		
	}

	// G'*G	
	for (int jBlock = 0; jBlock < 3; ++jBlock)
	{
		for (int iBlock = 0; iBlock < 3; ++iBlock)
		{
			memset(m_pTmp, 0, sizeof(double)*m_nZ*m_nZ);
			for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
			{
				double alpha = m_p2DCoef[iAngle][iBlock] * m_p2DCoef[iAngle][jBlock];
				cblas_daxpy(m_nZ*m_nZ, alpha, m_p2DWDSquare[iAngle], 1, m_pTmp, 1);
			}

			memcpy(m_pTmp2 + (jBlock * 3 + iBlock)*m_nZ*m_nZ, m_pTmp, sizeof(double)*m_nZ*m_nZ);
		}
	}
}

void CXAVOInversion::_CalcCovGTG()
{
	//Cm*G'*G	
	for (int jBlock = 0; jBlock < 3; ++jBlock)
	{
		for (int iBlock = 0; iBlock < 3; ++iBlock)
		{
			// calc
			memset(m_pTmp, 0, sizeof(double)*m_nZ*m_nZ);

			double* pX = m_pTmp2 + (jBlock * 3)*m_nZ*m_nZ;
			cblas_daxpy(m_nZ*m_nZ, m_CovMatrix[iBlock * 3], pX, 1, m_pTmp, 1);

			cblas_daxpy(m_nZ*m_nZ, m_CovMatrix[iBlock * 3 + 1], pX + m_nZ*m_nZ, 1, m_pTmp, 1);

			cblas_daxpy(m_nZ*m_nZ, m_CovMatrix[iBlock * 3 + 2], pX + 2 * m_nZ*m_nZ, 1, m_pTmp, 1);

			// set data
			int index = jBlock*m_nZ;
			for (int j = 0; j < m_nZ; ++j)
			{
				memcpy(m_p2DA[index + j] + iBlock*m_nZ, m_p2DTmp[j], sizeof(double)*m_nZ);
			}
		}
	}
}

void CXAVOInversion::_CalcCovGTS()
{
	for (int k = 0; k < m_nZ; ++k)
	{
		m_p2DB[0][k] = m_CovMatrix[0] * m_p2DTmp[0][k] + m_CovMatrix[1] * m_p2DTmp[1][k] + m_CovMatrix[2] * m_p2DTmp[2][k];

		m_p2DB[1][k] = m_CovMatrix[3] * m_p2DTmp[0][k] + m_CovMatrix[4] * m_p2DTmp[1][k] + m_CovMatrix[5] * m_p2DTmp[2][k];

		m_p2DB[2][k] = m_CovMatrix[6] * m_p2DTmp[0][k] + m_CovMatrix[7] * m_p2DTmp[1][k] + m_CovMatrix[8] * m_p2DTmp[2][k];
	}
}

void CXAVOInversion::_SolveLinearEQUWithBICG(int n, double*a, double*x, double*b, double tol, int itmax, int& iter, double& err)
{
	const double EPS = 1.0e-14;

	double n2b = cblas_dnrm2(n, b, 1);
	//	double n2b = CalcNorm(n, b);
	if (n2b == 0.)
	{
		iter = 0;
		err = 0.;
		memset(x, 0, sizeof(double)*n);
		return;
	}
	double tolb = tol * n2b;

	double *r = m_pCGBuffer;
	double *xmin = m_pCGBuffer + n;
	double *rt = m_pCGBuffer + 2*n;
	double *z = m_pCGBuffer + 3*n;
	double *zt = m_pCGBuffer + 4*n;
	double *p = m_pCGBuffer + 5*n;
	double *pt = m_pCGBuffer + 6*n;
	double *q = m_pCGBuffer + 7*n;
	double *qt = m_pCGBuffer + 8*n;

	//double *resvec = new double[itmax + 1];

	memcpy(xmin, x, sizeof(double)*n);

	// r = b - a*x
	int j;

	memcpy(r, b, sizeof(double)*n);
	cblas_dgemv(CblasColMajor, CblasNoTrans, n, n, -1, a, n, x, 1, 1, r, 1);
	//MultiplyRight(n, a, x, r, false);
	//for (j = 0; j < n; j++)
	//	r[j] = b[j] - r[j];

	double normr = cblas_dnrm2(n, r, 1);
	//double normr =CalcNorm(n, r);
	double normr_act = normr;
	double normrmin = normr;
	if (normr < tolb)
	{
		iter = 0;
		return;
	}

	memcpy(rt, r, sizeof(double)*n);
	//resvec[0] = normr;

	double rho = 1., rho1;
	double beta;
	int flag = 1;
	int stag = 0;                           //stagnation of the method

	int moresteps = 0;
	int	maxmsteps = qMin(qMin(n / 50, 5), n - itmax);
	int	maxstagsteps = 3;

	for (iter = 0; iter < itmax; ++iter)
	{
		memcpy(z, r, sizeof(double)*n);
		memcpy(zt, rt, sizeof(double)*n);

		rho1 = rho;

		rho = 0.;
		for (int i = 0; i < n; ++i)
			rho += rt[i] * z[i];

		if (rho == 0.)
		{
			flag = 4;
			break;
		}

		if (iter == 0)
		{
			memcpy(p, z, sizeof(double)*n);
			memcpy(pt, zt, sizeof(double)*n);
		}
		else
		{
			beta = rho / rho1;
			if (beta == 0.)
			{
				flag = 4;
				break;
			}

			for (int i = 0; i < n; ++i)
			{
				p[i] = z[i] + beta * p[i];
				pt[i] = zt[i] + beta * pt[i];
			}
		}

		//
		memset(q, 0, sizeof(double)*n);
		cblas_dgemv(CblasColMajor, CblasNoTrans, n, n, 1, a, n, p, 1, 0, q, 1);

		//MultiplyRight(n, a, p, q);

		memset(qt, 0, sizeof(double)*n);
		cblas_dgemv(CblasColMajor, CblasTrans, n, n, 1, a, n, pt, 1, 0, qt, 1);
		//MultiplyRight(n, a, pt, qt, true);

		double ptq = cblas_ddot(n, pt, 1, q, 1);
		//double ptq = DotProduct(n, pt, q);

		double alpha;
		if (ptq == 0.)
		{
			flag = 4;
			break;
		}
		else
		{
			alpha = rho / ptq;
		}

		if (qAbs(alpha)*cblas_dnrm2(n, p, 1) < EPS*cblas_dnrm2(n, x, 1))
			++stag;
		else
			stag = 0;

		for (int i = 0; i < n; ++i)
		{
			x[i] += alpha*p[i];
			r[i] -= alpha*q[i];
			rt[i] -= alpha*qt[i];
		}

		normr = cblas_dnrm2(n, r, 1);
		normr_act = normr;
		//resvec[iter + 1] = normr;

		// convergence
		if (normr <= tolb || stag >= maxstagsteps || moresteps != 0)
		{
			memcpy(r, b, sizeof(double)*n);
			cblas_dgemv(CblasColMajor, CblasNoTrans, n, n, -1, a, n, x, 1, 1, r, 1);

			//MultiplyRight(n, a, x, r, false);
			//for (int i = 0; i < n; i++)
			//	r[i] = b[i] - r[i];

			normr_act = cblas_dnrm2(n, r, 1);
			//resvec[iter + 1] = normr_act;

			if (normr_act <= tolb)
			{
				flag = 0;
				break;
			}
			else
			{
				if (stag >= maxstagsteps && moresteps == 0)
				{
					stag = 0;
				}
				++moresteps;

				if (moresteps >= maxmsteps)
				{
					flag = 3;
					break;
				}
			}

		}

		if (normr_act < normrmin)
		{
			normrmin = normr_act;
			memcpy(xmin, x, sizeof(double)*n);
		}

		if (stag >= maxstagsteps)
		{
			flag = 3;
			break;
		}

	} //end loop

	if (flag != 0)
	{
		memcpy(r, b, sizeof(double)*n);
		cblas_dgemv(CblasColMajor, CblasNoTrans, n, n, -1, a, n, xmin, 1, 1, r, 1);

		//MultiplyRight(n, a, xmin, r, false);
		//for (int i = 0; i < n; i++)
		//	r[i] = b[i] - r[i];

		if (flag == 1)
		{
			memcpy(zt, b, sizeof(double)*n);
			cblas_dgemv(CblasColMajor, CblasNoTrans, n, n, -1, a, n, x, 1, 1, zt, 1);

			//MultiplyRight(n, a, x, zt, false);
			//for (int i = 0; i < n; i++)
			//	zt[i] = b[i] - zt[i];

			normr_act = cblas_dnrm2(n, zt, 1);
		}

		if (cblas_dnrm2(n, r, 1) <= normr_act)
		{
			memcpy(x, xmin, sizeof(double)*n);
		}

	}

	//delete[]r;
	//delete[]xmin;
	//delete[]rt;
	//delete[]z;
	//delete[]zt;
	//delete[]p;
	//delete[]pt;
	//delete[]q;
	//delete[]qt;

	//delete[]resvec;
}




