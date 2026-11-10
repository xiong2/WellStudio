#ifndef XAVO3TERMINVERSION_H
#define XAVO3TERMINVERSION_H

#include <vector>
#include "xdataplus_global.h"

using std::vector;

/**
* @class CXAVO3TermInversion provided in the file "keavo3terminversion.h"
* @brief The class provides methods to do 3-D term AVO inversion
* @author Yong Shu
* @date 12/9/2015
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXAVO3TermInversion
{
public:
	CXAVO3TermInversion();
	~CXAVO3TermInversion();

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
	void _CalcInit();
	void _CalcW(int index);
	void _CalcWD();
	void _CalcG();
	void _CalcCovMatrix();

	void _CalcCoef();
	void _CalcGAndGTG();
	void _CalcCovGTG();
	void _CalcCovGTS();

	void _CalcSeismic();
	void _CalcRCoef();

	//lapack
	void _CalcInitNew();
	void _CalcWNew(int index);
	void _CalcWDNew();
	void _CalcGAndGTGNew();
	void _CalcCovGTGNew();
	void _CalcCovGTSNew();

	void _CalculateNew();

	void _SolveLinearEQUWithBICG(int n, double*a, double*x, double*b, double tol, int itmax, int& iter, double& err);

	// inverse Cm
	void _CalculateNew2();
	void _CalcInitNew2();
	void _CalcGAndA2();
	void _CalcB2();

	

private:
	// wavelet
	vector<double> m_vecAngle;
	vector<vector<double> > m_vec2DWavelet;
	int m_nAngleSize, m_nWaveSize;

	// inversion parameters
	double m_dLambda, m_dGamma, m_dMaxLoopNum, m_dTol;

	// max Z num
	int m_nMaxNZ;

	// buffers
	double *m_pINIT0, *m_pMeanModel, *m_pSeismic, *m_pX, *m_pB, *m_pTmp;
	double **m_p2DWD, **m_p2DWavelet, **m_p2DG, **m_p2DGT, **m_p2DA, **m_p2DC, **m_2DTmp, **m_p2DCoef, **m_p2DWDSquare;
	double m_covMatrix[3][3];

	// input buffer (do not need delete)
	float *m_pZP0, *m_pZS0, *m_pD0;
	int m_zmin, m_zmax, m_nZ;

	// output buffer
	float *m_pZP, *m_pZS, *m_pD;
	float **m_p2DRCoef, **m_p2DSSeismic;
	

	// for lapack
	vector<double*> m_vecWaveletData;
	double *m_pW, *m_pWD, *m_pG, *m_pA, *m_pWDSquare, *m_pTmp2;
	double m_CovMatrix[9];

	bool m_bLapack;

	vector<double> m_vecMaxWaveletValue;
	vector<int> m_vecPeakPos;
	vector<double> m_vecSeismicMax;	
};

#endif // KEAVO3TERMINVERSION_H
