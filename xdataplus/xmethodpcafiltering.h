#ifndef XMETHODPCAFILTERING_H
#define XMETHODPCAFILTERING_H

#include <vector>
#include <QStringList>
#include "xdataplus_global.h"

/**
* @class CXMethodPCAFiltering provided in the file "kemethodpcafiltering.h"
* @brief The class provides methods for PCA filtering
* @author Yong Shu
* @date 6/7/2016
*
*/

class XDATAPLUS_EXPORT CXMethodPCAFiltering
{
public:
	CXMethodPCAFiltering(int nJ, int nK, int jMin, int jMax, int nWinNI, int nWinNJ);	
	~CXMethodPCAFiltering();

	bool SetBuffers(float* pInBuffer, float* pOutBuffer);
	void SetTrueWinNI(int nTrueWinNI) { m_nTrueWinNI = nTrueWinNI; }

	void Calculate();

private:
	void _CalcMean(int nAttNum);
	void _CalcSVD(int nAttNum);
	void _CalcPC(int nAttNum);
	float _CalcCorr(double* pData1, double* pData2, int n);


private:
	int m_nJ, m_nK, m_jMin, m_jMax;
	int m_nWinNI, m_nWinNJ, m_nTrueWinNI;
	float *m_pInData, *m_pOutData;

private:
	double *m_pTraceData, *m_pPCAData, *m_pCovMatrix, *m_pTraceMean, *m_pPC;

	
};

#endif // KEMETHODPCAFILTERING_H
