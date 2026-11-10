#ifndef XAVOINVERSION_H
#define XAVOINVERSION_H

#include <vector>
#include "xdataplus_global.h"

using std::vector;

/**
* @class CXAVOInversion provided in the file "keavoinversion.h"
* @brief The class provides methods to do 3-D term AVO inversion
* @author Yong Shu
* @date 2/2/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXAVOInversion
{
public:
	CXAVOInversion();
	~CXAVOInversion();

	///@brief Initialize wavelet parameters
	void InitWaveletPara(vector<float>& vecAngle, int nWaveSize, vector<vector<float> >& vec2DWavelet);

	///@brief Initialize inversion parameters
	void InitInversionPara(double lambda, double gamma, double maxIterationNum, double tol);

	///@brief Create buffers
	bool CreateBuffers(int nMaxNZ, bool bExportR, bool bExportSeismic);

	///@brief Set data buffer
	void SetDataBuffer(int zMin, int zMax, float* pZP0, float* pZS0, float* pD0, float* pSeismic, vector<double>& vecMaxValue);

	///@brief Calculate
	void Calculate();

	float* GetZP() { return m_pZP; }
	float* GetZS() { return m_pZS; }
	float* GetZD() { return m_pD; }

	float** GetSeismic() { return m_p2DSSeismic; }
	float** GetRCoef() { return m_p2DRCoef; }

private:
	void _Set2DBuffer();
	
	void _CalcAkiCoef();

	void _CalcInit();
	void _CalcW(int index);
	void _CalcWD();
	void _CalcGAndGTG();
	void _CalcCovGTG();
	void _CalcCovGTS();

	void _CalcSeismic();
	void _CalcRCoef();

	

	void _SolveLinearEQUWithBICG(int n, double*a, double*x, double*b, double tol, int itmax, int& iter, double& err);

private:
	// wavelet
	vector<double> m_vecAngle;
	int m_nAngleSize, m_nWaveSize;

	// inversion parameters
	double m_dLambda, m_dGamma, m_dMaxLoopNum, m_dTol;

	// max Z num
	int m_nMaxNZ;

	// wavelet
	double *m_pWaveletBuffer, **p2DWaveletData;
	vector<double> m_vecMaxWaveletValue;
	vector<int> m_vecPeakPos;
	bool m_bSameWavelet;

	// aki coeff
	double **m_p2DCoef;

	double *m_pINIT0, *m_pMeanModel, *m_pX, *m_pB;
	double *m_p2DINIT0[3], *m_p2DMeanModel[3], *m_p2DX[3], *m_p2DB[3]; 

	double *m_pInSeismic;
	double **m_p2DInSeismic;

	double *m_pTmp, *m_pW, *m_pWD, *m_pG, *m_pA, *m_pWDSquare, *m_pTmp2;
	double **m_p2DTmp, **m_p2DW, **m_p2DWD, **m_p2DG, **m_p2DA, **m_p2DWDSquare;

	// input buffer 
	float *m_pZP0, *m_pZS0, *m_pD0;
	int m_zmin, m_zmax, m_nZ;

	// output buffer
	float *m_pZP, *m_pZS, *m_pD;
	float **m_p2DRCoef, **m_p2DSSeismic;

	// cov matrix
	double m_CovMatrix[9];

	bool m_bSameNZ;

	double *m_pCGBuffer;
};

#endif // KEAVOINVERSION_H
