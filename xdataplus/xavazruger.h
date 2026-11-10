#ifndef XAVAZRUGER_H
#define XAVAZRUGER_H

#include <vector>
#include "xdataplus_global.h"
#include <QMultiMap>

using std::vector;
class CXNLSQMethod;

/**
* @class CXAVAZRuger provided in the file "keavazruger.h"
* @brief The class provides methods to calculate ruger anisotropic coefficients
* @author Yong Shu
* @date 10/25/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXAVAZRuger
{
public:
	CXAVAZRuger(int nK, int nMaxFold);
	~CXAVAZRuger();

	///@brief Initialize
	void InitInputData(int kMin, int kMax, float* pGatherData, float* pOffAzi);

	///@brief 
	bool InitOutputData(float* pBani, float* pAzimuth);

	///@brief 
	void SetFold(int nFold);
	
	///@brief Calculate
	void Calculate();

	void Calculate2();


private:
	int m_nK, m_nFold, m_kMin, m_kMax, m_nMaxFold;

	// input
	float *m_pGather, *m_pOffAzi;

	// output
	float *m_pOutBani, *m_pOutAzimuth;	

private:
	double *m_pG, *m_pB, *m_pAngle, *m_pAzimuth, *m_pValue;

private:
	QMultiMap<float, QPair<float, int> > m_mapAzi;

private:
	CXNLSQMethod* m_pMethod;
	int m_m, m_n;
	double *m_pX, *m_pUserData;

	vector<double> m_vecAzi, m_vecInc, m_vecData;

};


#endif // KEAVAZRUGER_H
