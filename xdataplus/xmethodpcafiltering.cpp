#include "xmethodpcafiltering.h"
#include "mkl.h"

CXMethodPCAFiltering::CXMethodPCAFiltering(int nJ, int nK, int jMin, int jMax, int nWinNI, int nWinNJ)
{
	m_nJ = nJ;	m_nK = nK;
	m_jMin = jMin; m_jMax = jMax;
	m_nWinNI = nWinNI; m_nWinNJ = nWinNJ;

	m_pTraceData = NULL;
	m_pPCAData = NULL;
	m_pCovMatrix = NULL;
	m_pTraceMean = NULL;
	m_pPC = NULL;
}

CXMethodPCAFiltering::~CXMethodPCAFiltering()
{
	if (m_pTraceData)	delete[]m_pTraceData;
	if (m_pPCAData)		delete[]m_pPCAData;
	if (m_pCovMatrix)	delete[]m_pCovMatrix;
	if (m_pTraceMean)	delete[]m_pTraceMean;
	if (m_pPC)			delete[]m_pPC;

}

bool CXMethodPCAFiltering::SetBuffers(float* pInBuffer, float* pOutBuffer)
{
	m_pInData = pInBuffer;
	m_pOutData = pOutBuffer;

	try
	{
		m_pTraceData = new double[m_nWinNI*m_nWinNJ*m_nK];
		m_pPCAData = new double[m_nWinNI*m_nWinNJ*m_nK];
		m_pCovMatrix = new double[m_nWinNI*m_nWinNJ*m_nWinNI*m_nWinNJ];
		m_pTraceMean = new double[m_nWinNI*m_nWinNJ];
		m_pPC = new double[m_nK];
	}
	catch (std::bad_alloc)
	{
		return false;
	}
	return true;
}

void CXMethodPCAFiltering::Calculate()
{
	qint64 nJKSize = m_nJ*m_nK;
	int nHalfWinNJ = m_nWinNJ / 2;

	for (int j = m_jMin; j <= m_jMax; ++j)
	{
		int jMin = qMax(0, j - nHalfWinNJ);
		int jMax = qMin(m_nJ - 1, j + nHalfWinNJ);

		int nAttNum = 0;
		for (int iI = 0; iI < m_nTrueWinNI; ++iI)
		{
			for (int iJ = jMin; iJ <= jMax; ++iJ)
			{
				int index1 = nAttNum*m_nK;
				int index2 = iI*nJKSize + iJ*m_nK;
				for (int k = 0; k < m_nK; ++k)
					m_pTraceData[index1 + k] = m_pInData[index2 + k];
				++nAttNum;
			}
		}

		// find mean
		_CalcMean(nAttNum);

		// svd
		_CalcSVD(nAttNum);
		
		// pc
		_CalcPC(nAttNum);
	
		int index = m_nTrueWinNI / 2 * (jMax - jMin + 1) + j - jMin;
		float fValue = _CalcCorr(m_pTraceData+index*m_nK, m_pPC, m_nK);
		float fFactor = 1.;		
		if (fValue < 0)
			fFactor = -1.f;

		// output
		int index3 = j*m_nK;
		for (int k = 0; k < m_nK; ++k)
			m_pOutData[index3 + k] = m_pPC[k] * fFactor;
	}
}

void CXMethodPCAFiltering::_CalcMean(int nAttNum)
{	
	for (int iAtt = 0; iAtt < nAttNum; ++iAtt)
	{
		double dSum = 0.;
		int index = iAtt*m_nK;
		for (int k = 0; k < m_nK; ++k)
		{
			dSum += m_pTraceData[index + k];
		}
		dSum /= m_nK;
		m_pTraceMean[iAtt] = dSum;

		for (int k = 0; k < m_nK; ++k)
		{
			m_pPCAData[index + k] = m_pTraceData[index + k] - dSum;
		}
	}
}

void CXMethodPCAFiltering::_CalcSVD(int nAttNum)
{
	// calc covariance A'*A
	int nSize = nAttNum*nAttNum;
	memset(m_pCovMatrix, 0, sizeof(float)*nSize);
	cblas_dsyrk(CblasColMajor, CblasLower, CblasTrans, nAttNum, m_nK, 1., m_pPCAData, m_nK, 0, m_pCovMatrix, nAttNum);
	for (int i = 0; i < nSize; ++i)
	{
		m_pCovMatrix[i] /= (m_nK - 1);
	}

	// svd, eigenvalue in ascending order
	std::vector<double> w(nAttNum);
	LAPACKE_dsyev(CblasColMajor, 'V', 'L', nAttNum, m_pCovMatrix, nAttNum, &w[0]);
}

void CXMethodPCAFiltering::_CalcPC(int nAttNum)
{
	// principle component = A*U
	memset(m_pPC, 0, sizeof(float)*m_nK);
	cblas_dgemv(CblasColMajor, CblasNoTrans, m_nK, nAttNum, 1, m_pTraceData, m_nK, m_pCovMatrix + (nAttNum - 1)*nAttNum, 1, 0, m_pPC, 1);

}

float CXMethodPCAFiltering::_CalcCorr(double* pData1, double* pData2, int n)
{
	double dValue = 0.;
	for (int i = 0; i < n; ++i)
		dValue += pData1[i] * pData2[i];

	return dValue;
}


