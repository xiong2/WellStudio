#include "xavo3terminversion.h"
#include <cmath>
#include <cassert>
#include "xutility.h"
#include "xglobal.h"
#include "xmathmacro.h"
#include "xfunctiontemplate.h"
#include "xblas.h"
#include "mkl.h"

// test
#include <QFile>
#include <qtextstream.h>

CXAVO3TermInversion::CXAVO3TermInversion()
{
	// 1-D
	m_pINIT0 = NULL;
	m_pMeanModel = NULL;
	m_pSeismic = NULL;
	m_pX = NULL;
	m_pB = NULL;
	m_pTmp = NULL;

	m_pZP0 = NULL;
	m_pZS0 = NULL;
	m_pD0 = NULL;

	m_pZP = NULL;
	m_pZS = NULL;
	m_pD = NULL;

	// 2-D 
	m_p2DWD = NULL;
	m_p2DWavelet = NULL;
	m_p2DG = NULL;
	m_p2DGT = NULL;
	m_p2DA = NULL;
	m_p2DC = NULL;
	m_2DTmp = NULL;

	m_p2DCoef = NULL;
	m_p2DWDSquare = NULL;

	// output 
	m_p2DRCoef = NULL;
	m_p2DSSeismic = NULL;


	m_bLapack = false;

	m_pW = NULL; 
	m_pWD = NULL; 
	m_pG = NULL; 
	m_pA = NULL;
	m_pWDSquare = NULL; 
	m_pTmp2 = NULL; 
}

CXAVO3TermInversion::~CXAVO3TermInversion()
{
	if (m_pINIT0)		{ delete[]m_pINIT0; m_pINIT0 = NULL; }
	if (m_pMeanModel)	{ delete[]m_pMeanModel; m_pMeanModel = NULL; }
	if (m_pSeismic)		{ delete[]m_pSeismic; m_pSeismic = NULL; }
	if (m_pX)			{ delete[]m_pX; m_pX = NULL; }
	if (m_pB)			{ delete[]m_pB; m_pB = NULL; }
	if (m_pTmp)			{ delete[]m_pTmp; m_pTmp = NULL; }

	if (m_pZP0)			{ delete[]m_pZP0; m_pZP0 = NULL; }
	if (m_pZS0)			{ delete[]m_pZS0; m_pZS0 = NULL; }
	if (m_pD0)			{ delete[]m_pD0; m_pD0 = NULL; }
	if (m_pZP)			{ delete[]m_pZP; m_pZP = NULL; }
	if (m_pZS)			{ delete[]m_pZS; m_pZS = NULL; }
	if (m_pD)			{ delete[]m_pD; m_pD = NULL; }

	// lapack
	if (m_pW)			{ delete[]m_pW; m_pW = NULL; }
	if (m_pWD)			{ delete[]m_pWD; m_pWD = NULL; }
	if (m_pG)			{ delete[]m_pG; m_pG = NULL; }
	if (m_pA)			{ delete[]m_pA; m_pA = NULL; }
	if (m_pWDSquare)	{ delete[]m_pWDSquare; m_pWDSquare = NULL; }
	if (m_pTmp2)		{ delete[]m_pTmp2; m_pTmp2 = NULL; }

	if (!m_vecWaveletData.empty())
	{
		for (int i = 0; i < m_vecWaveletData.size(); ++i)
			delete[]m_vecWaveletData[i];
	}
	m_vecWaveletData.clear();

	if (m_p2DWD)		{ NXUtility::Free2DMatrix<double>(m_p2DWD); m_p2DWD = NULL; }
	if (m_p2DWavelet)	{ NXUtility::Free2DMatrix<double>(m_p2DWavelet); m_p2DWavelet = NULL; }
	if (m_p2DG)			{ NXUtility::Free2DMatrix<double>(m_p2DG); m_p2DG = NULL; }
	if (m_p2DGT)		{ NXUtility::Free2DMatrix<double>(m_p2DGT); m_p2DGT = NULL; }
	if (m_p2DA)			{ NXUtility::Free2DMatrix<double>(m_p2DA); m_p2DA = NULL; }
	if (m_p2DC)			{ NXUtility::Free2DMatrix<double>(m_p2DC); m_p2DC = NULL; }
	if (m_2DTmp)		{ NXUtility::Free2DMatrix<double>(m_2DTmp); m_2DTmp = NULL; }

	if (m_p2DCoef)		{ NXUtility::Free2DMatrix<double>(m_p2DCoef); m_p2DCoef = NULL; }
	if (m_p2DWDSquare)	{ NXUtility::Free2DMatrix<double>(m_p2DWDSquare); m_p2DWDSquare = NULL; }

	if (m_p2DRCoef)		{ NXUtility::Free2DMatrix<float>(m_p2DRCoef); m_p2DRCoef = NULL; }
	if (m_p2DSSeismic)	{ NXUtility::Free2DMatrix<float>(m_p2DSSeismic); m_p2DSSeismic = NULL; }
}

void CXAVO3TermInversion::InitWaveletPara(vector<float>& vecAngle, int nWaveSize, vector<vector<float> >& vec2DWavelet)
{
	m_nAngleSize = (int)vecAngle.size();
	m_nWaveSize = nWaveSize;

	assert(vecAngle.size() == vec2DWavelet.size());

	// angles
	m_vecAngle.resize(m_nAngleSize);
	for (int i = 0; i < m_nAngleSize; ++i)
		m_vecAngle[i] = vecAngle[i];

	// wavelet
	m_vec2DWavelet.resize(m_nAngleSize);
	for (int i = 0; i < m_nAngleSize; ++i)
	{
		assert(m_nWaveSize == (int)vec2DWavelet[i].size());

		m_vec2DWavelet[i].resize(m_nWaveSize);
		double dMaxValue = 0;
		int iPeakPos = 0;
		for (int j = 0; j < m_nWaveSize; ++j)
		{
			m_vec2DWavelet[i][j] = vec2DWavelet[i][j];
			if (qAbs(m_vec2DWavelet[i][j]) >dMaxValue)
			{
				dMaxValue = qAbs(m_vec2DWavelet[i][j]);
				iPeakPos = j;
			}
		}
		m_vecPeakPos.push_back(iPeakPos);
		m_vecMaxWaveletValue.push_back(dMaxValue);
		//if (dMaxValue > 0)
		//{
		//	for (int j = 0; j < m_nWaveSize; ++j)
		//	{
		//		m_vec2DWavelet[i][j] /= dMaxValue;
		//	}
		//}
	}

	// for lapack
	if (!m_bLapack)
		return;
	
	for (int i = 0; i < m_nAngleSize; ++i)
	{
		double* pWavelet = new double[m_nWaveSize];
		for (int j = 0; j < m_nWaveSize; ++j)
			pWavelet[j] = vec2DWavelet[i][j];

		double dMaxValue = 0;
		int iPeakPos = 0;
		for (int j = 0; j < m_nWaveSize; ++j)
		{			
			if (qAbs(pWavelet[j]) >dMaxValue)
			{
				dMaxValue = qAbs(pWavelet[j]);
				iPeakPos = j;
			}
		}
		m_vecPeakPos.push_back(iPeakPos);
		m_vecMaxWaveletValue.push_back(dMaxValue);

		for (int j = 0; j < m_nWaveSize; ++j)
			pWavelet[j] /= dMaxValue;

		m_vecWaveletData.push_back(pWavelet);
	}
}

void CXAVO3TermInversion::InitInversionPara(double lambda, double gamma, double maxIterationNum, double tol)
{
	m_dLambda = lambda;
	m_dGamma = gamma; 
	m_dMaxLoopNum = maxIterationNum;
	m_dTol = tol;
}

bool CXAVO3TermInversion::CreateBuffers(int nMaxNZ, bool bExportR, bool bExportSeismic)
{
	m_nMaxNZ = nMaxNZ;

	try
	{
		m_pINIT0 = new double[3 * m_nMaxNZ];
		m_pMeanModel = new double[3 * m_nMaxNZ];
		m_pSeismic = new double[m_nAngleSize * m_nMaxNZ];
		m_pX = new double[3 * m_nMaxNZ];
		m_pB = new double[3 * m_nMaxNZ];
		m_pTmp = new double[qMax(3, m_nAngleSize)  * m_nMaxNZ];

		m_pZP0 = new float[ m_nMaxNZ];
		m_pZS0 = new float[m_nMaxNZ];
		m_pD0 = new float[m_nMaxNZ];
		m_pZP = new float[m_nMaxNZ];
		m_pZS = new float[m_nMaxNZ];
		m_pD = new float[m_nMaxNZ];

		if (m_bLapack)
		{
			// for lapack
			m_pW = new double[m_nMaxNZ*m_nMaxNZ];
			m_pWD = new double[m_nMaxNZ*m_nMaxNZ];
			m_pG = new double[m_nMaxNZ*m_nAngleSize*m_nMaxNZ * 3];
			m_pA = new double[m_nMaxNZ * 3 * m_nMaxNZ * 3];
			m_pWDSquare = new double[m_nMaxNZ*m_nAngleSize*m_nMaxNZ];
			m_pTmp2 = new double[m_nMaxNZ * 3 * m_nMaxNZ * 3];
		}
	}
	catch (std::bad_alloc)
	{
		return false;
	}

	m_p2DCoef = NXUtility::New2DMatrix<double>(m_nAngleSize, 3);

	m_p2DA = NXUtility::New2DMatrix<double>(m_nMaxNZ * 3, m_nMaxNZ * 3);


	if (!m_bLapack)
	{
		m_p2DWD = NXUtility::New2DMatrix<double>(m_nMaxNZ, m_nMaxNZ);
		m_p2DWavelet = NXUtility::New2DMatrix<double>(m_nMaxNZ, m_nMaxNZ);

		m_p2DG = NXUtility::New2DMatrix<double>(m_nMaxNZ*m_nAngleSize, m_nMaxNZ * 3);
		//m_p2DGT = NXUtility::New2DMatrix<double>(m_nMaxNZ * 3, m_nMaxNZ*m_nAngleSize);

		//m_p2DA = NXUtility::New2DMatrix<double>(m_nMaxNZ * 3, m_nMaxNZ * 3);
		//m_p2DC = NXUtility::New2DMatrix<double>(m_nMaxNZ * 3, m_nMaxNZ * 3);

		m_2DTmp = NXUtility::New2DMatrix<double>(m_nMaxNZ * 3, m_nMaxNZ * 3);


		m_p2DWDSquare = NXUtility::New2DMatrix<double>(m_nMaxNZ*m_nAngleSize, m_nMaxNZ);
	}

	//if (!m_p2DWD || !m_p2DWavelet || !m_p2DG || !m_p2DA || !m_2DTmp || !m_p2DCoef || !m_p2DWDSquare)
	//	return false;

	// output
	if (bExportR)
	{
		m_p2DRCoef = NXUtility::New2DMatrix<float>(m_nAngleSize, m_nMaxNZ);
	}
	if (bExportSeismic)
	{
		m_p2DSSeismic = NXUtility::New2DMatrix<float>(m_nAngleSize, m_nMaxNZ);
	}


	return true;
}

void CXAVO3TermInversion::SetDataBuffer(int zMin, int zMax, float* pZP0, float* pZS0, float* pD0, float* pSeismic, vector<double>& vecMaxValue)
{
	m_vecSeismicMax = vecMaxValue;

	m_zmin = zMin;
	m_zmax = zMax;

	m_nZ = zMax - zMin + 1;

	// seismic
	for (int i = 0; i < m_nAngleSize; ++i)
	{
		for (int k = 0; k < m_nZ; ++k)
		{
			m_pSeismic[i*m_nZ + k] = pSeismic[i*m_nMaxNZ + k + m_zmin];// / m_vecMaxWaveletValue[i];
		}
	}

	// impedance
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pZP0[i] = pZP0[m_zmin + i];
		m_pZS0[i] = pZS0[m_zmin + i];
		m_pD0[i] = pD0[m_zmin + i];
	}

	// Calc coef
	_CalcCoef();
}

void CXAVO3TermInversion::_CalculateNew()
{
	_CalcInitNew();

	_CalcGAndGTGNew();

	_CalcCovGTGNew(); 
	for (int i = 0; i < 3*m_nZ; ++i)
	{
		m_pA[i*3*m_nZ+i] += m_dLambda;
	}

	// G'*d
	memset(m_pTmp, 0, sizeof(double) * 3 * m_nZ);
	cblas_dgemv(CblasColMajor, CblasTrans, m_nZ*m_nAngleSize, m_nZ * 3, 1.0, m_pG, m_nZ*m_nAngleSize, m_pSeismic, 1, 0, m_pTmp, 1);

	// Cm*G'*d
	_CalcCovGTSNew();

	cblas_daxpy(m_nZ * 3, m_dLambda, m_pMeanModel, 1, m_pB, 1);

	// solve x
//	memcpy(m_pX, m_pB, sizeof(double) * 3 * m_nZ);

	
	//test code
	//{
	//	{
	//		QFile qFile("F:/tmp/A_new.txt");
	//		qFile.open(QIODevice::WriteOnly);
	//		QTextStream out(&qFile);
	//		for (int j = 0; j < m_nZ * 9 * m_nZ; ++j)
	//			out << QString::number(m_pA[j], 'f', 10) << endl;

	//	}
	//	{
	//		QFile qFile("F:/tmp/B_new.txt");
	//		qFile.open(QIODevice::WriteOnly);
	//		QTextStream out(&qFile);
	//		for (int j = 0; j < m_nZ * 3; ++j)
	//			out << QString::number(m_pB[j], 'f', 10) << endl;

	//	}
	//}
	

	//int nLoopNum;
	//double dErr;
	//memcpy(m_pX, m_pINIT0, sizeof(double) * 3 * m_nZ);
	////NXBLAS::SolveLinearEQUWithBICGTwo(m_nZ * 3, m_p2DA, m_pX, m_pB, m_dTol, m_dMaxLoopNum, nLoopNum, dErr);
	//_SolveLinearEQUWithBICG(m_nZ * 3, m_pA, m_pX, m_pB, m_dTol, m_dMaxLoopNum, nLoopNum, dErr);

	//test code
	//{
	//	QFile qFile("F:/tmp/X_new.txt");
	//	qFile.open(QIODevice::WriteOnly);
	//	QTextStream out(&qFile);
	//	for (int j = 0; j < m_nZ * 3; ++j)
	//		out << QString::number(m_pX[j], 'f', 10) << endl;

	//}

	memcpy(m_pX, m_pB, sizeof(double) * 3 * m_nZ);
	LAPACKE_dgels(LAPACK_COL_MAJOR, 'N', m_nZ*3, m_nZ*3, 1, m_pA, m_nZ*3, m_pX, m_nZ*3);

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
}

void CXAVO3TermInversion::Calculate()
{
	//{
	//	//test codes

	//		wavelet
	//	{
	//		QFile qFile("F:/tmp/waveletdata.txt");
	//		qFile.open(QIODevice::WriteOnly);
	//		QTextStream out(&qFile);
	//		for (int j = 0; j < m_nWaveSize; ++j)
	//			out << QString::number(m_vecWaveletData[0][j], 'f', 14) << endl;
	//	}
	//	{
	//		QFile qFile("F:/tmp/impedance.txt");
	//		qFile.open(QIODevice::WriteOnly);
	//		QTextStream out(&qFile);
	//		for (int j = 0; j < m_nZ; ++j)
	//			out << QString::number(m_pZP0[j], 'f', 7) << endl;

	//		for (int j = 0; j < m_nZ; ++j)
	//			out << QString::number(m_pZS0[j], 'f', 7) << endl;

	//		for (int j = 0; j < m_nZ; ++j)
	//			out << QString::number(m_pD0[j], 'f', 7) << endl;
	//	}

	//	{
	//		QFile qFile("F:/tmp/Seismic.txt");
	//		qFile.open(QIODevice::WriteOnly);
	//		QTextStream out(&qFile);
	//		for (int j = 0; j < m_nAngleSize*m_nZ; ++j)
	//			out << QString::number(m_pSeismic[j], 'f', 14) << endl;
	//	}

	//}


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

	if (m_bLapack)
	{
		_CalculateNew2();
		return;
	}

	_CalcInit();

	
	/*

	// G
	_CalcG();

	// covariance matrix
	_CalcCovMatrix();

	// calculate A
	NXBLAS::TransposeMaxtrix(m_nZ*m_nAngleSize, m_nZ * 3, m_p2DG, m_p2DGT);
	NXBLAS::MultiplyMaxtrix(m_nZ * 3, m_nZ*m_nAngleSize, m_nZ * 3, m_p2DGT, m_p2DG, m_2DTmp);
	NXBLAS::MultiplyMaxtrix(m_nZ * 3, m_nZ * 3, m_nZ * 3, m_p2DC, m_2DTmp, m_p2DA);
	for (int i = 0; i < 3 * m_nZ; ++i)
	{
		m_p2DA[i][i] += m_dLambda;
	}

	// calculate B
	NXBLAS::MultiplyRight(m_nZ * 3, m_nZ*m_nAngleSize, m_p2DGT, m_pSeismic, m_pTmp);
	NXBLAS::MultiplyRight(m_nZ * 3, m_p2DC, m_pTmp, m_pB);
	for (int i = 0; i < 3 * m_nZ; ++i)
	{
		m_pB[i] += m_dLambda*m_pMeanModel[i];
	}

	*/
	

	_CalcGAndGTG();

	_CalcCovGTG();
	for (int i = 0; i < 3 * m_nZ; ++i)
	{
		m_p2DA[i][i] += m_dLambda;
	}

	// calculate B
	NXBLAS::MultiplyRight(m_nZ*m_nAngleSize, m_nZ * 3, m_p2DG, m_pSeismic, m_pTmp, true);
	//NXBLAS::TransposeMaxtrix(m_nZ*m_nAngleSize, m_nZ * 3, m_p2DG, m_p2DGT);
	//NXBLAS::MultiplyRight(m_nZ * 3, m_nZ*m_nAngleSize, m_p2DGT, m_pSeismic, m_pTmp);

	_CalcCovGTS();
	for (int i = 0; i < 3 * m_nZ; ++i)
	{
		m_pB[i] += m_dLambda*m_pMeanModel[i];
	}


	// solve x
	int nLoopNum;
	double dErr;
	memcpy(m_pX, m_pINIT0, sizeof(double) * 3 * m_nZ);

	
	//// test code
	//{
	//	{
	//		QFile qFile("F:/tmp/A_old.txt");
	//		qFile.open(QIODevice::WriteOnly);
	//		QTextStream out(&qFile);
	//		for (int j = 0; j < m_nZ*3; ++j)
	//			for (int i = 0; i < m_nZ*3; ++i)
	//				out << QString::number(m_p2DA[i][j], 'f', 10) << endl;

	//	}
	//	{
	//		QFile qFile("F:/tmp/B_old.txt");
	//		qFile.open(QIODevice::WriteOnly);
	//		QTextStream out(&qFile);
	//		for (int j = 0; j < m_nZ * 3; ++j)
	//			out << QString::number(m_pB[j], 'f', 10) << endl;

	//	}
	//}
	

	NXBLAS::SolveLinearEQUWithBICGTwo(m_nZ * 3, m_p2DA, m_pX, m_pB, m_dTol, m_dMaxLoopNum, nLoopNum, dErr);

	////test code
	//{
	//	QFile qFile("F:/tmp/X_old.txt");
	//	qFile.open(QIODevice::WriteOnly);
	//	QTextStream out(&qFile);
	//	for (int j = 0; j < m_nZ * 3; ++j)
	//		out << QString::number(m_pX[j], 'f', 10) << endl;

	//}

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
			m_pD[i] = exp(m_pX[2 * m_nZ + i - m_zmin] );
		}
	}

	////double maxp = *(std::max_element(m_pZP + m_zmin, m_pZP + m_zmax + 1));
	//double dpercentile = 100.0;
	//int index = m_nZ*dpercentile / 100.;
	//double dValue = NXUtility::Select(m_pZP + m_zmin, m_nZ, index);
	//for (int i = m_zmin; i <= m_zmax; ++i)
	//{
	//	m_pZP[i] /= dValue;
	//}

	// calculate Seismic
	_CalcSeismic();

	// calc RCoef
	_CalcRCoef();

}

void CXAVO3TermInversion::_CalcSeismic()
{
	if (!m_p2DSSeismic)
		return;

	NXBLAS::MultiplyRight(m_nAngleSize*m_nZ, 3 * m_nZ, m_p2DG, m_pX, m_pTmp);
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

void CXAVO3TermInversion::_CalcRCoef()
{
	if (!m_p2DRCoef)
		return;

	//calc D
	memset(m_p2DWD[0], 0, sizeof(double)*m_nMaxNZ*m_nMaxNZ);
	for (int j = 0; j < m_nZ; ++j)
	{
		if (j == 0)
		{
			m_p2DWD[0][j] = -0.5;
		}
		else if (j == m_nZ - 2)
		{
			m_p2DWD[m_nZ - 3][j] = 0.5;
			m_p2DWD[m_nZ - 2][j] = -0.5;
			m_p2DWD[m_nZ - 1][j] = -0.5;
		}
		else if (j == m_nZ - 1)
		{
			m_p2DWD[m_nZ - 1][j] = 0.5;
			m_p2DWD[m_nZ - 1][j] = 0.5;
		}
		else
		{
			m_p2DWD[j][j] = -0.5;
			m_p2DWD[j-1][j] = 0.5;
		}
	}
	
	float fInvalid = (float)::g_dInvalidData;
	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		// calc (C1*D C2*D, C3*D)
		for (int i = 0; i < m_nZ; ++i)
		{
			for (int j = 0; j < m_nZ; ++j)
			{
				m_p2DG[i][j] = m_p2DCoef[iAngle][0] * m_p2DWD[i][j];

				m_p2DG[i][j+m_nZ] = m_p2DCoef[iAngle][1] * m_p2DWD[i][j];

				m_p2DG[i][j+2*m_nZ] = m_p2DCoef[iAngle][2] * m_p2DWD[i][j];
			}
		}

		// calc R Coef
		NXBLAS::MultiplyRight(m_nZ, 3*m_nZ, m_p2DG, m_pX, m_pTmp);

		// set data
		for (int i = 0; i < m_nMaxNZ; ++i)
		{
			if (i < m_zmin || i > m_zmax)
			{
				m_p2DRCoef[iAngle][i] = fInvalid;
			}
			else
			{
				m_p2DRCoef[iAngle][i] = m_pTmp[i - m_zmin];
			}
		}
	}
}

void CXAVO3TermInversion::_CalcInitNew()
{
	// Init0
	// Zp0, Zs0, D0
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pINIT0[i] = log(m_pZP0[i]);
		m_pINIT0[m_nZ + i] = log(m_pZS0[i]);
		m_pINIT0[2 * m_nZ + i] = log(m_pD0[i]);
	}

	// mean model
	double dSumZp(0), dSumZs(0), dSumD(0);
	for (int i = 0; i < m_nZ; ++i)
	{
		dSumZp += m_pINIT0[i];
		dSumZs += m_pINIT0[m_nZ + i];
		dSumD += m_pINIT0[2 * m_nZ + i];
	}

	dSumZp /= m_nZ;
	dSumZs /= m_nZ;
	dSumD /= m_nZ;
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pMeanModel[i] = dSumZp;
		m_pMeanModel[m_nZ + i] = dSumZs;
		m_pMeanModel[2 * m_nZ + i] = dSumD;
	}

	// covariance matrix
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pTmp2[i] = m_pINIT0[i] - dSumZp;
		m_pTmp2[m_nZ+i] = m_pINIT0[m_nZ + i] - dSumZs;
		m_pTmp2[2 * m_nZ + i] = m_pINIT0[2 * m_nZ + i] - dSumD;
	}

	// calc covariance D'*D
	memset(m_CovMatrix, 0, sizeof(double) * 9);
	cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, 3, m_nZ, 1., m_pTmp2, m_nZ, 0, m_CovMatrix, 3);
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

void CXAVO3TermInversion::_CalcInit()
{
	// Init0
	// Zp0, Zs0, D0
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pINIT0[i] = log(m_pZP0[i]);
		m_pINIT0[m_nZ + i] = log(m_pZS0[i]);
		m_pINIT0[2 * m_nZ + i] = log(m_pD0[i]);
	}

	// mean model
	double dSumZp(0), dSumZs(0), dSumD(0);
	for (int i = 0; i < m_nZ; ++i)
	{
		dSumZp += m_pINIT0[i];
		dSumZs += m_pINIT0[m_nZ + i];
		dSumD += m_pINIT0[2*m_nZ + i];
	}

	dSumZp /= m_nZ;
	dSumZs /= m_nZ;
	dSumD /= m_nZ;
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pMeanModel[i] = dSumZp;
		m_pMeanModel[m_nZ + i] = dSumZs;
		m_pMeanModel[2 * m_nZ + i] = dSumD;
	}

	// covariance matrix
	for (int i = 0; i < m_nZ; ++i)
	{
		m_p2DG[i][0] = m_pINIT0[i] - dSumZp;
		m_p2DG[i][1] = m_pINIT0[m_nZ + i] - dSumZs;
		m_p2DG[i][2] = m_pINIT0[2 * m_nZ + i] - dSumD;
	}

	NXBLAS::TransposeMaxtrix(m_nZ, 3, m_p2DG, m_2DTmp);
	NXBLAS::MultiplyMaxtrix(3, m_nZ, 3, m_2DTmp, m_p2DG, m_p2DA);

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
			m_covMatrix[i][j] = m_p2DA[i][j] / (m_nZ - 1);
	}
}

// wavelet matrix
void CXAVO3TermInversion::_CalcWNew(int index)
{
	memset(m_pW, 0, sizeof(double)*m_nZ*m_nZ);
	
	double* pWaveletData = m_vecWaveletData[index];
	for (int j = 0, iStart = m_vecPeakPos[index]; j < m_nZ; ++j, --iStart)
	{
		for (int i = qMax(0, iStart); i < m_nWaveSize && i - iStart < m_nZ; ++i)
		{
			m_pW[j*m_nZ + (i - iStart)] = pWaveletData[i];
			//m_p2DWavelet[i - iStart][j] = m_vec2DWavelet[index][i];
		}
	}
}

// wavelet matrix
void CXAVO3TermInversion::_CalcW(int index)
{
	memset(m_p2DWavelet[0], 0, sizeof(double)*m_nMaxNZ*m_nMaxNZ);

	for (int j = 0, iStart = m_vecPeakPos[index]; j < m_nZ; ++j, --iStart)
	{
		for (int i = qMax(0, iStart); i < m_nWaveSize && i - iStart < m_nZ; ++i)
		{
			m_p2DWavelet[i - iStart][j] = m_vec2DWavelet[index][i];
		}
	}
}

// W*D = 1/2*(-W0, W0-W1, W1-W2, ..., Wn-3 - Wn-2 - Wn-1,  Wn-1+Wn-2)
void CXAVO3TermInversion::_CalcWDNew()
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
			cblas_daxpy(m_nZ, -1, m_pW+j*m_nZ, 1, m_pWD + j*m_nZ, 1);
			cblas_daxpy(m_nZ, -1, m_pW+(j+1)*m_nZ, 1, m_pWD + j*m_nZ, 1);
		}
		else if (j == m_nZ - 1)
		{			
			cblas_daxpy(m_nZ, 1, m_pW+j*m_nZ, 1, m_pWD+j*m_nZ, 1);
		}
		else
		{			
			cblas_daxpy(m_nZ, -1, m_pW + j*m_nZ, 1, m_pWD + j*m_nZ, 1);
		}
	}
	cblas_dscal(m_nZ*m_nZ, 0.5, m_pWD, 1);
}

// W*D = 1/2*(-W0, W0-W1, W1-W2, ..., Wn-3 - Wn-2 - Wn-1, Wn-2 + Wn-1)
void CXAVO3TermInversion::_CalcWD()
{
	for (int j = 0; j < m_nZ; ++j)
	{
		if (j == 0)
		{
			for (int i = 0; i < m_nZ; ++i)
			{
				m_p2DWD[i][j] = -0.5*m_p2DWavelet[i][0];
			}
		}
		else if (j == m_nZ - 2)
		{
			for (int i = 0; i < m_nZ; ++i)
			{
				m_p2DWD[i][j] = 0.5*(m_p2DWavelet[i][m_nZ - 3] - m_p2DWavelet[i][m_nZ - 1] - m_p2DWavelet[i][m_nZ - 2]);
			}
		}
		else if (j == m_nZ - 1)
		{
			for (int i = 0; i < m_nZ; ++i)
			{
				m_p2DWD[i][j] = 0.5*(m_p2DWavelet[i][m_nZ - 2] + m_p2DWavelet[i][m_nZ - 1]);
			}
		}
		else
		{
			for (int i = 0; i < m_nZ; ++i)
			{
				m_p2DWD[i][j] = 0.5*(m_p2DWavelet[i][j-1] - m_p2DWavelet[i][j]);
			}
		}

	}
}

void CXAVO3TermInversion::_CalcCoef()
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

void CXAVO3TermInversion::_CalcGAndGTGNew()
{
	memset(m_pWDSquare, 0, sizeof(double)*m_nZ*m_nAngleSize*m_nZ);
	memset(m_pG, 0, sizeof(double)*m_nZ*m_nAngleSize*m_nZ * 3);
	//memset(m_pTmp2, 0, sizeof(double)*m_nZ*3*m_nZ * 3);

	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		// Calculate Wavelet matrix
		_CalcWNew(iAngle);

		// Calculate W*D
		_CalcWDNew();

		// WD'*WD
		double* pOneWDSquare = m_pWDSquare + iAngle*m_nZ*m_nZ;
		cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, m_nZ, m_nZ, 1., m_pWD, m_nZ, 0, pOneWDSquare, m_nZ);
		for (int j = 0; j < m_nZ; ++j)
		{
			for (int i = 0; i < j; ++i)
			{
				pOneWDSquare[j*m_nZ + i] = pOneWDSquare[i*m_nZ + j];
			}
		}

		//copy to G
		for (int jj = 0; jj < 3; ++jj)
		{
			memset(m_pTmp2, 0, sizeof(double)*m_nZ*m_nZ);
			cblas_daxpy(m_nZ*m_nZ, m_p2DCoef[iAngle][jj], m_pWD, 1, m_pTmp2, 1);
			for (int j = 0; j < m_nZ; ++j)
			{
				memcpy(m_pG + (jj*m_nZ + j)*(m_nZ*m_nAngleSize) + iAngle*m_nZ, m_pTmp2 + j*m_nZ, sizeof(double)*m_nZ);
			}
		}
	}

	// G'*G	
	for (int jBlock = 0; jBlock < 3; ++jBlock)
	{
		for (int iBlock = 0; iBlock < 3; ++iBlock)
		{
			//
			double* pX;
			double* pY = m_pWD;
			memset(pY, 0, sizeof(double)*m_nZ*m_nZ);
			for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
			{
				double alpha = m_p2DCoef[iAngle][iBlock] * m_p2DCoef[iAngle][jBlock];
				pX = m_pWDSquare + iAngle*m_nZ*m_nZ;
				cblas_daxpy(m_nZ*m_nZ, alpha, pX, 1, pY, 1);
			}

			memcpy(m_pTmp2 + (jBlock * 3 + iBlock)*m_nZ*m_nZ, m_pWD, sizeof(double)*m_nZ*m_nZ);
		}
	}
}

// calc WD1^2, WD2^2, ..., WDm^2
void CXAVO3TermInversion::_CalcGAndGTG()
{
	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		// Calculate Wavelet matrix
		_CalcW(iAngle);

		// Calculate W*D
		_CalcWD();

		// transpose
		NXBLAS::TransposeMaxtrix(m_nZ, m_nZ, m_p2DWD, m_p2DA);

		// WD'*WD
		NXBLAS::MultiplyMaxtrix(m_nZ, m_nZ, m_nZ, m_p2DA, m_p2DWD, m_p2DWDSquare + iAngle*m_nZ);

		// G
		int iStart = iAngle*m_nZ;

		int j1Start = 0;
		int j2Start = m_nZ;
		int j3Start = 2 * m_nZ;
		for (int i = 0; i < m_nZ; ++i)
		{
			for (int j = 0; j < m_nZ; ++j)
			{
				m_p2DG[iStart + i][j1Start + j] = m_p2DCoef[iAngle][0] * m_p2DWD[i][j];
				m_p2DG[iStart + i][j2Start + j] = m_p2DCoef[iAngle][1] * m_p2DWD[i][j];
				m_p2DG[iStart + i][j3Start + j] = m_p2DCoef[iAngle][2] * m_p2DWD[i][j];
			}
		}
	}

	//G'*G
	int iStart;
	for (int iBlock = 0; iBlock < 3; ++iBlock)
	{
		for (int jBlock = 0; jBlock < 3; ++jBlock)
		{
			// one block
			memset(m_p2DWD[0], 0, sizeof(double)*m_nMaxNZ*m_nMaxNZ);

			for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
			{
				iStart = iAngle*m_nZ;
				for (int i = 0; i < m_nZ; ++i)
				{
					for (int j = 0; j < m_nZ; ++j)
					{
						m_p2DWD[i][j] += m_p2DCoef[iAngle][iBlock] * m_p2DCoef[iAngle][jBlock] * m_p2DWDSquare[iStart + i][j];

					}
				}
			}

			// set one block
			for (int i = 0; i < m_nZ; ++i)
			{
				for (int j = 0; j < m_nZ; ++j)
				{
					m_2DTmp[iBlock*m_nZ + i][jBlock*m_nZ+j] = m_p2DWD[i][j];
				}
			}
			
		}
	}
}

void CXAVO3TermInversion::_CalcCovGTGNew()
{
	//Cm*G'*G
	//memset(m_pA, 0, sizeof(double)*m_nZ * 3 * m_nZ * 3);
	double *pX, *pY;
	int index;
	for (int jBlock = 0; jBlock < 3; ++jBlock)
	{
		for (int iBlock = 0; iBlock < 3; ++iBlock)
		{
			// calc
			memset(m_pWD, 0, sizeof(double)*m_nZ*m_nZ);

			double* pX = m_pTmp2 + (jBlock * 3)*m_nZ*m_nZ;
			cblas_daxpy(m_nZ*m_nZ, m_CovMatrix[iBlock * 3], pX, 1, m_pWD, 1);

			cblas_daxpy(m_nZ*m_nZ, m_CovMatrix[iBlock * 3+1], pX+m_nZ*m_nZ, 1, m_pWD, 1);

			cblas_daxpy(m_nZ*m_nZ, m_CovMatrix[iBlock * 3 + 2], pX + 2*m_nZ*m_nZ, 1, m_pWD, 1);

			// set data
			for (int j = 0; j < m_nZ; ++j)
			{
				memcpy(m_pA + (jBlock*m_nZ + j) * 3 * m_nZ + iBlock*m_nZ, m_pWD + j*m_nZ, sizeof(double)*m_nZ);
			}
		}
	}
}

void CXAVO3TermInversion::_CalcCovGTG()
{
	int istart, jstart;
	for (int iBlock = 0; iBlock < 3; ++iBlock)
	{
		for (int jBlock = 0; jBlock < 3; ++jBlock)
		{
			jstart = jBlock*m_nZ;

			// one block
			memset(m_p2DWD[0], 0, sizeof(double)*m_nMaxNZ*m_nMaxNZ);

			for (int k = 0; k < 3; ++k)
			{	
				istart = k*m_nZ;
				for (int i = 0; i < m_nZ; ++i)
				{
					for (int j = 0; j < m_nZ; ++j)
					{
						m_p2DWD[i][j] += m_covMatrix[iBlock][k] * m_2DTmp[istart + i][jstart + j];

					}
				}
			}

			// set one block
			for (int i = 0; i < m_nZ; ++i)
			{
				for (int j = 0; j < m_nZ; ++j)
				{
					m_p2DA[iBlock*m_nZ + i][jBlock*m_nZ + j] = m_p2DWD[i][j];
				}
			}
		}
	}


}


void CXAVO3TermInversion::_CalcG()
{
	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		// theta
		double theta = m_vecAngle[iAngle] * M_RAD;
		double C1 = 1 + SQR(tan(theta));
		double C2 = -8.0*m_dGamma*m_dGamma*SQR(sin(theta));
		double C3 = 4 * m_dGamma*m_dGamma*SQR(sin(theta)) - SQR(tan(theta));

		// Calculate Wavelet matrix
		_CalcW(iAngle);

		// Calculate W*D
		_CalcWD();
		
		int iStart = iAngle*m_nZ;

		// ZP
		int j1Start = 0;
		int j2Start = m_nZ;
		int j3Start = 2 * m_nZ;
		for (int i = 0; i < m_nZ; ++i)
		{
			for (int j = 0; j < m_nZ; ++j)
			{
				m_p2DG[iStart + i][j1Start + j] = C1*m_p2DWD[i][j];
				m_p2DG[iStart + i][j2Start + j] = C2*m_p2DWD[i][j];
				m_p2DG[iStart + i][j3Start + j] = C3*m_p2DWD[i][j];
			}
		}
	}
}

void CXAVO3TermInversion::_CalcCovGTSNew()
{
	for (int k = 0; k < m_nZ; ++k)
	{
		m_pB[k] = m_CovMatrix[0] * m_pTmp[k] + m_CovMatrix[1] * m_pTmp[k + m_nZ] + m_CovMatrix[2] * m_pTmp[k + 2 * m_nZ];

		m_pB[k + m_nZ] = m_CovMatrix[3] * m_pTmp[k] + m_CovMatrix[4] * m_pTmp[k + m_nZ] + m_CovMatrix[5] * m_pTmp[k + 2 * m_nZ];

		m_pB[k + 2 * m_nZ] = m_CovMatrix[6] * m_pTmp[k] + m_CovMatrix[7] * m_pTmp[k + m_nZ] + m_CovMatrix[8] * m_pTmp[k + 2 * m_nZ];
	}
}

void CXAVO3TermInversion::_CalcCovGTS()
{
	//_CalcCovMatrix();
	//NXBLAS::MultiplyRight(m_nZ * 3, m_p2DC, m_pTmp, m_pB);

	for (int k = 0; k < m_nZ; ++k)
	{
		m_pB[k] = m_covMatrix[0][0] * m_pTmp[k] + m_covMatrix[0][1] * m_pTmp[k + m_nZ] + m_covMatrix[0][2] * m_pTmp[k + 2 * m_nZ];

		m_pB[k+m_nZ] = m_covMatrix[1][0] * m_pTmp[k] + m_covMatrix[1][1] * m_pTmp[k + m_nZ] + m_covMatrix[1][2] * m_pTmp[k + 2 * m_nZ];

		m_pB[k+2*m_nZ] = m_covMatrix[2][0] * m_pTmp[k] + m_covMatrix[2][1] * m_pTmp[k + m_nZ] + m_covMatrix[2][2] * m_pTmp[k + 2 * m_nZ];
	}
}

void CXAVO3TermInversion::_CalcCovMatrix()
{
	memset(m_p2DC[0], 0, sizeof(double)*(m_nMaxNZ * 3)*(m_nMaxNZ * 3));

	for (int i = 0; i < m_nZ; ++i)
	{
		m_p2DC[i][i] = m_covMatrix[0][0];
		m_p2DC[m_nZ + i][m_nZ + i] = m_covMatrix[1][1];
		m_p2DC[2*m_nZ + i][2*m_nZ + i] = m_covMatrix[2][2];

		m_p2DC[i][m_nZ + i] = m_covMatrix[0][1];
		m_p2DC[m_nZ + i][i] = m_covMatrix[0][1];

		m_p2DC[i][2*m_nZ + i] = m_covMatrix[0][2];
		m_p2DC[2*m_nZ + i][i] = m_covMatrix[0][2];

		m_p2DC[m_nZ + i][2 * m_nZ + i] = m_covMatrix[1][2];
		m_p2DC[2 * m_nZ + i][m_nZ + i] = m_covMatrix[1][2];
	}
}

void CXAVO3TermInversion::_SolveLinearEQUWithBICG(int n, double*a, double*x, double*b, double tol, int itmax, int& iter, double& err)
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

	double *r = new double[n];
	double *xmin = new double[n];
	double *rt = new double[n];
	double *z = new double[n];
	double *zt = new double[n];
	double *p = new double[n];
	double *pt = new double[n];
	double *q = new double[n];
	double *qt = new double[n];

	double *resvec = new double[itmax + 1];

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
	resvec[0] = normr;

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
		resvec[iter + 1] = normr;

		// convergence
		if (normr <= tolb || stag >= maxstagsteps || moresteps != 0)
		{
			memcpy(r, b, sizeof(double)*n);
			cblas_dgemv(CblasColMajor, CblasNoTrans, n, n, -1, a, n, x, 1, 1, r, 1);

			//MultiplyRight(n, a, x, r, false);
			//for (int i = 0; i < n; i++)
			//	r[i] = b[i] - r[i];

			normr_act = cblas_dnrm2(n, r, 1);
			resvec[iter + 1] = normr_act;

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

	delete[]r;
	delete[]xmin;
	delete[]rt;
	delete[]z;
	delete[]zt;
	delete[]p;
	delete[]pt;
	delete[]q;
	delete[]qt;

	delete[]resvec;
}

void CXAVO3TermInversion::_CalculateNew2()
{
	_CalcInitNew2();

	_CalcGAndA2();

	_CalcB2();

	//int nLoopNum;
	//double dErr;
	//memcpy(m_pX, m_pINIT0, sizeof(double) * 3 * m_nZ);
	//_SolveLinearEQUWithBICG(m_nZ * 3, m_pA, m_pX, m_pB, m_dTol, m_dMaxLoopNum, nLoopNum, dErr);

	memcpy(m_pX, m_pB, sizeof(double) * 3 * m_nZ);
	LAPACKE_dposv(LAPACK_COL_MAJOR, 'L', m_nZ * 3, 1, m_pA, m_nZ * 3, m_pX, m_nZ * 3);
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

}

void CXAVO3TermInversion::_CalcInitNew2()
{
	// Init0
	// Zp0, Zs0, D0
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pINIT0[i] = log(m_pZP0[i]);
		m_pINIT0[m_nZ + i] = log(m_pZS0[i]);
		m_pINIT0[2 * m_nZ + i] = log(m_pD0[i]);
	}

	// mean model
	double dSumZp(0), dSumZs(0), dSumD(0);
	for (int i = 0; i < m_nZ; ++i)
	{
		dSumZp += m_pINIT0[i];
		dSumZs += m_pINIT0[m_nZ + i];
		dSumD += m_pINIT0[2 * m_nZ + i];
	}

	dSumZp /= m_nZ;
	dSumZs /= m_nZ;
	dSumD /= m_nZ;
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pMeanModel[i] = dSumZp;
		m_pMeanModel[m_nZ + i] = dSumZs;
		m_pMeanModel[2 * m_nZ + i] = dSumD;
	}

	// covariance matrix
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pTmp2[i] = m_pINIT0[i] - dSumZp;
		m_pTmp2[m_nZ + i] = m_pINIT0[m_nZ + i] - dSumZs;
		m_pTmp2[2 * m_nZ + i] = m_pINIT0[2 * m_nZ + i] - dSumD;
	}

	// calc covariance D'*D
	memset(m_CovMatrix, 0, sizeof(double) * 9);
	cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, 3, m_nZ, 1., m_pTmp2, m_nZ, 0, m_CovMatrix, 3);
	cblas_dscal(9, 1. / (m_nZ - 1), m_CovMatrix, 1);

	// inverse Cm-1
	LAPACKE_dpotrf(LAPACK_COL_MAJOR, 'L', 3, m_CovMatrix, 3);
	LAPACKE_dpotri(LAPACK_COL_MAJOR, 'L', 3, m_CovMatrix, 3);

	for (int j = 0; j < 3; ++j)
	{
		for (int i = 0; i < j; ++i)
		{
			m_CovMatrix[j * 3 + i] = m_CovMatrix[i * 3 + j];
		}
	}

	// calc Cm-1
	memset(m_pA, 0, sizeof(double) * 3*m_nZ*3*m_nZ);
	int j;
	for (int i = 0; i < m_nZ; ++i)
	{
		m_pA[i * 3 * m_nZ + i] = m_CovMatrix[0];

		j = m_nZ + i;
		m_pA[i * 3 * m_nZ + j] = m_CovMatrix[1];
		m_pA[j * 3 * m_nZ + i] = m_CovMatrix[1];

		j = m_nZ * 2 + i;
		m_pA[i * 3 * m_nZ + j] = m_CovMatrix[2];
		m_pA[j * 3 * m_nZ + i] = m_CovMatrix[2];
	}

	for (int i = m_nZ; i < 2 * m_nZ; ++i)
	{
		m_pA[i * 3 * m_nZ + i] = m_CovMatrix[4];

		j = m_nZ + i;
		m_pA[i * 3 * m_nZ + j] = m_CovMatrix[5];
		m_pA[j * 3 * m_nZ + i] = m_CovMatrix[5];
	}

	for (int i = 2*m_nZ; i < 3*m_nZ; ++i)
		m_pA[i * 3 * m_nZ + i] = m_CovMatrix[8];



	// divide by (m_nZ-1) to normalize
	//cblas_dscal(9, 1. / (m_nZ - 1), m_CovMatrix, 1);
}

void CXAVO3TermInversion::_CalcGAndA2()
{
	memset(m_pWDSquare, 0, sizeof(double)*m_nZ*m_nAngleSize*m_nZ);
	memset(m_pG, 0, sizeof(double)*m_nZ*m_nAngleSize*m_nZ * 3);
	//memset(m_pTmp2, 0, sizeof(double)*m_nZ*3*m_nZ * 3);

	for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
	{
		// Calculate Wavelet matrix
		_CalcWNew(iAngle);

		// Calculate W*D
		_CalcWDNew();

		// WD'*WD
		double* pOneWDSquare = m_pWDSquare + iAngle*m_nZ*m_nZ;
		cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, m_nZ, m_nZ, 1., m_pWD, m_nZ, 0, pOneWDSquare, m_nZ);
		for (int j = 0; j < m_nZ; ++j)
		{
			for (int i = 0; i < j; ++i)
			{
				pOneWDSquare[j*m_nZ + i] = pOneWDSquare[i*m_nZ + j];
			}
		}

		//copy to G
		for (int jj = 0; jj < 3; ++jj)
		{
			memset(m_pTmp2, 0, sizeof(double)*m_nZ*m_nZ);
			cblas_daxpy(m_nZ*m_nZ, m_p2DCoef[iAngle][jj], m_pWD, 1, m_pTmp2, 1);
			for (int j = 0; j < m_nZ; ++j)
			{
				memcpy(m_pG + (jj*m_nZ + j)*(m_nZ*m_nAngleSize) + iAngle*m_nZ, m_pTmp2 + j*m_nZ, sizeof(double)*m_nZ);
			}
		}
	}

	// G'*G
	// CCom = G'*G + alpha*CCom
	memcpy(m_pTmp2, m_pA, sizeof(double) * 3 * m_nZ * 3 * m_nZ);
	cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, 3 * m_nZ, 3 * m_nZ, 1., m_pG, 3 * m_nZ, m_dLambda, m_pA, 3*m_nZ);
	for (int j = 0; j < 3 * m_nZ; ++j)
	{
		for (int i = 0; i < j; ++i)
		{
			m_pA[j*m_nZ * 3 + i] = m_pA[i*m_nZ * 3 + j];
		}
	}

	/*
	for (int jBlock = 0; jBlock < 3; ++jBlock)
	{
		for (int iBlock = 0; iBlock < 3; ++iBlock)
		{
			//
			double* pX;
			double* pY = m_pWD;
			memset(pY, 0, sizeof(double)*m_nZ*m_nZ);
			for (int iAngle = 0; iAngle < m_nAngleSize; ++iAngle)
			{
				double alpha = m_p2DCoef[iAngle][iBlock] * m_p2DCoef[iAngle][jBlock];
				pX = m_pWDSquare + iAngle*m_nZ*m_nZ;
				cblas_daxpy(m_nZ*m_nZ, alpha, pX, 1, pY, 1);
			}

			// add Cm-1*lamda
			double CValue = m_dLambda*m_CovMatrix[jBlock * 3 + iBlock];
			for (int i = 0; i < m_nZ; ++i)
			{
				m_pWD[i*m_nZ + i] = CValue;
			}

			for (int j = 0; j < m_nZ; ++j)
			{
				memcpy(m_pA + (jBlock*m_nZ + j)*(m_nZ * 3) + iBlock*m_nZ, m_pWD + j*m_nZ, sizeof(double)*m_nZ);
			}
		}
	}
	*/
}

void CXAVO3TermInversion::_CalcB2()
{
	/*
	// Cm-1*mu
	memset(m_pB, 0, sizeof(double)*m_nZ * 3);
	cblas_daxpy(m_nZ, m_CovMatrix[0], m_pMeanModel, 1, m_pB, 1);
	cblas_daxpy(m_nZ, m_CovMatrix[1], m_pMeanModel+m_nZ, 1, m_pB, 1);
	cblas_daxpy(m_nZ, m_CovMatrix[2], m_pMeanModel + 2*m_nZ, 1, m_pB, 1);

	cblas_daxpy(m_nZ, m_CovMatrix[3], m_pMeanModel, 1, m_pB+m_nZ, 1);
	cblas_daxpy(m_nZ, m_CovMatrix[4], m_pMeanModel + m_nZ, 1, m_pB + m_nZ, 1);
	cblas_daxpy(m_nZ, m_CovMatrix[5], m_pMeanModel + 2 * m_nZ, 1, m_pB + m_nZ, 1);

	cblas_daxpy(m_nZ, m_CovMatrix[6], m_pMeanModel, 1, m_pB + 2 * m_nZ, 1);
	cblas_daxpy(m_nZ, m_CovMatrix[7], m_pMeanModel + m_nZ, 1, m_pB + 2 * m_nZ, 1);
	cblas_daxpy(m_nZ, m_CovMatrix[8], m_pMeanModel + 2 * m_nZ, 1, m_pB + 2 * m_nZ, 1);

	// G'*d + lamda*Cm-1*mu
	cblas_dgemv(CblasColMajor, CblasTrans, m_nZ*m_nAngleSize, m_nZ * 3, 1.0, m_pG, m_nZ*m_nAngleSize, m_pSeismic, 1, m_dLambda, m_pB, 1);
	*/

	memset(m_pB, 0, sizeof(double) * 3 * m_nZ);
	cblas_dgemv(CblasColMajor, CblasNoTrans, m_nZ * 3, m_nZ * 3, 1.0, m_pTmp2, m_nZ * 3, m_pMeanModel, 1, 0, m_pB, 1);

	cblas_dgemv(CblasColMajor, CblasTrans, m_nZ*m_nAngleSize, m_nZ * 3, 1.0, m_pG, m_nZ*m_nAngleSize, m_pSeismic, 1, m_dLambda, m_pB, 1);

}
