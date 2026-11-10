#ifndef XAVOSSINVERSION_H
#define XAVOSSINVERSION_H

#include <vector>
#include "xdataplus_global.h"

using std::vector;

class CXParameter3TermInversion;

/**
* @class CXAVOSSInversion provided in the file "keavossinversion.h"
* @brief The class provides methods to do 3-D term AVO-SSI
* @author Yong Shu
* @date 3/10/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXAVOSSInversion
{
public:
	CXAVOSSInversion();
	~CXAVOSSInversion();

	///@brief Initialize wavelet parameters
	void InitWaveletPara(vector<float>& vecAngle, int nWaveSize, vector<vector<float> >& vec2DWavelet);

	///@brief Initialize inversion parameters
	void InitInversionPara(CXParameter3TermInversion* pPara);

	///@brief Create buffers
	bool CreateBuffers(int nMaxNZ, bool bExportR, bool bExportSeismic);

	///@brief Set input data buffers
	void SetDataBuffer(int zMin, int zMax, float* pZP0, float* pZS0, float* pD0, float* pSeismic);

	void Calculate();

	///@brief Get three components
	void GetThreeComponents(vector<float*>& vec3Component);
	float** GetSeismic() { return m_p2DSeismic; }
	float** GetRCoef() { return m_p2DR; }
	float** GetPriorSeismic() { return m_p2DPrior; }

private:
	void _CalcAkiCoef();
	void _LowPassFilter();
	void _CalcU1();
	void _CalcXi();	

	void _CalcGGCoef();
	void _CalcW(int index);
	void _CalcWWandWD();
	void _CalcA1();
	void _CalcB1();
	void _CalcA2();
	void _CalcB2();
	void _CalcPartAandB();

	void _CalcA();	
	void _CalcGGRR();
	double _CalcJs();
	double _CalcJi();
	double _CalcJr();
	double _CalcCostFunction();	

	void _CalcR();
	void _CalcImpedance();	
	void _CalcRCoef();
	void _CalcSeismic();

	void _Filtering();

	void _CalcPrior();

	void _HandleInvalidInput();
private:
	// angles
	vector<double> m_vecAngle;
	int m_nAngleSize, m_nWaveSize;

	// aki coeff [m_nAngleSize][3]
	double **m_p2DAkiCoef;

	// wavelet [m_nAngleSize][m_nWaveSize]
	double **m_p2DWaveletData;
	vector<double> m_vecMaxWaveletValue;
	vector<int> m_vecPeakPos;
	bool m_bSameWavelet;

	// inversion parameters
	double m_dGamma, m_dMaxLoopNum, m_dTol, m_dAlpha, m_dBeta, m_dSigma, m_dLamda, m_dSamplingRate;
	int m_nOutType;

	// Z info
	int m_nMaxNZ, m_zmin, m_zmax, m_nZ;
	bool m_bSameNZ;

	// 
	double m_u[3][3];
	double *m_pZ0, *m_pZ1, *m_pZ2, *m_pD0, *m_pXi, *m_pTmp, *m_pTmp2, *m_pTmp3;

	double *m_pW, *m_pA, *m_pB, *m_pRR, *m_pR;

	double *m_pB1, *m_pB2, *m_pA1, *m_pA2, *m_pWSquareArray, *m_pWD, *m_pCXi, *m_pWArray, *m_pTrace;
	double **m_p2DGGCoef, *m_pSquare;
	double m_c[3][3];

	//output 
	bool m_bOutInversion, m_bOutPrior, m_bAki;

	float *m_pZp, *m_pZs, *m_pZRho, *m_pZpBP, *m_pZsBP, *m_pZRhoBP, *m_pZpMerged, *m_pZsMerged, *m_pZRhoMerged;
	float **m_p2DR, **m_p2DSeismic;
	float **m_p2DPrior;

	// avo or avo-ssi
	bool m_bAVOSSI;

	bool m_bApplyFiltering;
	double m_dLowCut, m_dLowOverlap, m_dHighCut, m_dHighOverlap;

	// FFT buffer
	double *m_pFFTBuffer, *m_pH1, *m_pH2, *m_pFFTOut1, *m_pFFTOut2;

	// 
	vector<float> m_vecLambda, m_vecAlpha, m_vecSigma, m_vecWaveletScale;	
};

#endif // KEAVOSSINVERSION_H
