#ifndef XAVAZFCS_H
#define XAVAZFCS_H

#include <vector>
#include "xdataplus_global.h"
#include <QMultiMap>

using std::vector;
class CXNLSQMethod;

/**
* @class CXAVAZFCs provided in the file "keavazfcs.h"
* @brief The class provides methods to calculate Fourier Coefficients
* @author Yong Shu
* @date 10/25/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXAVAZFCs
{
public:
	CXAVAZFCs(int nK, int nMaxFold, int nIncidence);
	~CXAVAZFCs();

	///@brief Initialize
	void InitInputData(int kMin, int kMax, float* pGatherData, float* pOffAzi);

	///@brief 
	bool InitOutputData(float* pBani, float* pAzimuth);

	///@brief 
	void SetFold(int nFold);

	///@brief Calculate
	void Calculate();

	///@brief Calculate
	void Calculate2();

private:
	struct sOffAziInd
	{
		sOffAziInd() {}
		sOffAziInd(float inc, float azi, int ind)
		{
			incidence = inc;
			azimuth = azi;
			index = ind;
		}

		float incidence;
		float azimuth;
		int index;
	};


private:
	int m_nK, m_nFold, m_kMin, m_kMax, m_nMaxFold;

	// input
	float *m_pGather, *m_pOffAzi;

	// output
	float *m_pOutBani, *m_pOutAzimuth;

	int m_nIncidence;

private:
	CXNLSQMethod* m_pMethod;
	int m_m, m_n;
	double *m_pX, *m_pUserData;

	vector<double> m_vecAzi, m_vecInc, m_vecData;
};


#endif // KEAVAZFCS_H
