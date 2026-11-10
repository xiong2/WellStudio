#ifndef XCSSINVERSION_H
#define XCSSINVERSION_H

#include <vector>
#include "xdataplus_global.h"

using std::vector;

class CXParameterCSSInversion;


/**
* @class CXCSSInversion provided in the file "kecssinversion.h"
* @brief The class provides methods to do constrained sparse-spike inversion using Cauchy distribution
* @author Yong Shu
* @date 1/12/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXCSSInversion
{
public:
	CXCSSInversion();
	~CXCSSInversion();

	///@brief Initialize wavelet parameters
	void InitWaveletPara(int nWaveSize, vector<float>& vecWavelet);

	///@brief Initialize inversion parameters
	void InitInversionPara(CXParameterCSSInversion* pPara);
	//void InitInversionPara(double alpha, double beta, double mu, double sigma, double waveletfactor, double tol, int nMaxLoop);

	///@brief Create buffers
	bool CreateBuffers(int nMaxNZ, bool bExportR, bool bExportSeismic);

	///@brief Set data buffer
	void SetDataBuffer(int zMin, int zMax, float* pZP0, float* pSeismic);

	///@brief Calculate
	void Calculate();

	float* GetR() { return m_pR; }
	float* GetSeismic() { return m_pOutSeismic; }
	float* GetImpedance() { return m_pImpedance; }
	float* GetImpedanceBP() { return m_pImpBP; }
	float* GetImpedanceMerged() { return m_pImpMerged; }

	static void CGMethod(int n, double *A, double* pBuffer, double* b, double* x, double tol, int nMaxLoop, double& err, int& iLoop);
	static void CGSolver(int n, double* pBuffer, double*a, double*x, double*b, double tol, int itmax, int& iter, double& err);

private:
	void _InitWavelet();
	void _InitSeismicAndImpedance();
	void _CalcG();
	void _CalcQ();
	void _CalcCComplex();
	void _CalcA();
	void _CalcB();

	void _LowPassFilter();

	double _CalcCostFunction();
	void _CalcImpedance();
	void _CalcSeismic();

	void _MergeLowFreq();

private:
	// wavelet
	int m_nWaveSize;
	double* m_pWavelet;

	// inversion parameters
	double m_dAlpha, m_dBeta, m_dMu, m_dSigma, m_dWavletFactor, m_dTol, m_dSamplingRate, m_dCutFrequency;
	int m_nMaxLoop;

	bool m_bApplyFiltering;
	double m_dLowCut, m_dLowOverlap, m_dHighCut, m_dHighOverlap;

	// max Z num
	int m_nMaxNZ;

	// buffers
	double *m_pZP0, *m_pInSeismic, *m_pX, *m_pB, *m_pQ, *m_pXi, *m_pG, *m_pA, *m_pCCom, *m_pTmp1, *m_pTmp2, *m_pTmp3;

	int m_zmin, m_zmax, m_nZ;

	double m_dMaxSeismicData, m_dZP0, m_dMaxWaveletValue;
	int m_iWaveletPeakPos;

	// output buffer
	float *m_pR, *m_pImpedance, *m_pOutSeismic, *m_pImpBP, *m_pImpMerged;

	// FFT buffer
	double *m_pFFTBuffer, *m_pH1, *m_pH2, *m_pFFTOut1, *m_pFFTOut2;

	double *m_pBuffer;
};

#endif // KECSSINVERSION_H
