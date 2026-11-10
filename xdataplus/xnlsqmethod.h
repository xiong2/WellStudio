#ifndef XNLSQMETHOD_H
#define XNLSQMETHOD_H

#include "xdataplus_global.h"

/**
* @class CXNLSQMethod provided in the file "kenlsqmethod.h"
* @brief The class provides methods for non-linear least square problem with constraint
* @author Yong Shu
* @date 7/14/2016
*
* @see
* @bug No known bugs so far.
*/
class XDATAPLUS_EXPORT CXNLSQMethod
{
	typedef void (*FunctionFromX2Y)(int* m, int* n, double* x, double* f);
	typedef void(*FunctionFromX2YWithUserData)(int* m, int* n, double* x, double* f, void* userData);
public:
	CXNLSQMethod();
	~CXNLSQMethod();

	///@brief m: length of y; n: length of x
	void Init(int m, int n, int nMaxLoop, FunctionFromX2Y pFunction);
	void InitWithUserData(int m, int n, int nMaxLoop, FunctionFromX2YWithUserData pFunction);

	bool Calculate(double* x,  double* lower, double* upper,int nThread);

	bool Calculate2WithUserData(int m, int n, double* x, void* userData);

	bool Calculate3WithUserData(double* x, double* lower, double* upper, void* userData);

private:
	int m_m, m_n;
	int m_nMaxLoop;
	double *m_pJacbi;
	double *m_pResidual;

	FunctionFromX2Y m_pFunction;
	FunctionFromX2YWithUserData m_pFunctionWithUserData;
	
};

#endif // KENLSQMETHOD_H
