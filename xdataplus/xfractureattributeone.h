#ifndef XFRACTUREATTRIBUTEONE_H
#define XFRACTUREATTRIBUTEONE_H

#include <vector>
#include "xdataplus_global.h"
#include <QMultiMap>

using std::vector;

class CXNLSQMethod;

/**
* @class CXFractureAttributeOne provided in the file "kefractureattributeone.h"
* @brief The class provides methods to calculate anisotropic coefficients from VpVs
* @author Yong Shu
* @date 12/29/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXFractureAttributeOne
{
public:
	CXFractureAttributeOne(int nK);
	~CXFractureAttributeOne();

	void InitMethod(int m, int n, int nMaxLoop);

	///@brief Initialize
	void InitInputData(int kMin, int kMax, float* pGatherData, double* pAzi);

	///@brief 
	bool InitOutputData(float* pBani, float* pAzimuth);

	


	///@brief Calculate
	void Calculate();


private:
	int m_nK, m_nFold, m_kMin, m_kMax, m_nMaxFold;

	// input
	float *m_pGather;

	// output (do not need delete)
	float *m_pOutBani, *m_pOutAzimuth;

private:
	// method
	CXNLSQMethod* m_pMethod;
	int m_m, m_n;
	double *m_pX, *m_pUserData;
	double *m_pValue;
};

#endif // KEFRACTUREATTRIBUTEONE_H
