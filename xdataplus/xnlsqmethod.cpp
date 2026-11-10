#include <string.h>
#include "xnlsqmethod.h"
#include "mkl.h"

CXNLSQMethod::CXNLSQMethod()
{
	m_pJacbi = NULL;
	m_pResidual = NULL;
}

CXNLSQMethod::~CXNLSQMethod()
{
	if (m_pJacbi)
	{
		delete[]m_pJacbi;
		m_pJacbi = NULL;
	}

	if (m_pResidual)
	{
		delete[]m_pResidual;
		m_pResidual = NULL;
	}
	MKL_Free_Buffers();
}

void CXNLSQMethod::Init(int m, int n, int nMaxLoop, FunctionFromX2Y pFunction)
{
	m_m = m;
	m_n = n;
	m_nMaxLoop = nMaxLoop;
	m_pFunction = pFunction;

	delete m_pJacbi;
	delete m_pResidual;
	m_pJacbi = new double[m_m*m_n];
	m_pResidual = new double[m_m];
}

void CXNLSQMethod::InitWithUserData(int m, int n, int nMaxLoop, FunctionFromX2YWithUserData pFunction)
{
	m_m = m;
	m_n = n;
	m_nMaxLoop = nMaxLoop;
	m_pFunctionWithUserData = pFunction;

	delete m_pJacbi;
	delete m_pResidual;
	m_pJacbi = new double[m_m*m_n];
	m_pResidual = new double[m_m];
}

bool CXNLSQMethod::Calculate(double* x, double* lower, double* upper, int nThread)
{
	if (nThread > 0)
	{
		mkl_set_num_threads(1);
	}
	// eps
	double eps[6];
	for (int i = 0; i < 6; ++i)
		eps[i] = 1.0e-5;

	//eps[0] = 1.0e-14;
	//eps[3] = 1.0e-14;
	//eps[4] = 1.0e-14;

	double jac_eps = 1.0e-8;
	double rs = 0;
	int iter1 = 1000, iter2 = 200, iter;

	// set zeros
	memset(m_pJacbi, 0, sizeof(double)*m_m*m_n);
	memset(m_pResidual, 0, sizeof(double)*m_m);

	// init
	_TRNSPBC_HANDLE_t handle;
	int check0 = dtrnlspbc_init(&handle, &m_n, &m_m, x, lower, upper, eps, &iter1, &iter2, &rs);
	if (check0 != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}

	int info[6];
	if (dtrnlspbc_check(&handle, &m_n, &m_m, m_pJacbi, m_pResidual, lower, upper, eps, info) != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}
	else
	{
		if (info[0] != 0 || // The handle is not valid.
			info[1] != 0 || // The jacobi array is not valid.
			info[2] != 0 || // The y array is not valid.
			info[3] != 0 || // The lower array is not valid.
			info[4] != 0 || // The upper array is not valid.
			info[5] != 0    // The eps array is not valid.
			)
		{
			//MKL_Free_Buffers();
			return false;
		}
	}

//	djacobi_init(&handle, &m_n, &m_m, x, m_pJacbi, &jac_eps);

	int RCI_Request = 0;
	bool successful = false;
	int curLoop = 0;
	while (!successful)
	{
		if (m_nMaxLoop<curLoop)
		{
			break;
		}
		curLoop++;
		if (dtrnlspbc_solve(&handle, m_pResidual, m_pJacbi, &RCI_Request) != TR_SUCCESS)
		{
			//MKL_Free_Buffers();
			return false;
		}

		if (RCI_Request == -1 ||
			RCI_Request == -2 ||
			RCI_Request == -3 ||
			RCI_Request == -4 ||
			RCI_Request == -5 ||
			RCI_Request == -6)

			successful = true;

		if (RCI_Request == 1)
		{
			(*m_pFunction)(&m_m, &m_n, x, m_pResidual);
		}
		else if (RCI_Request == 2)
		{
			if (djacobi(m_pFunction, &m_n, &m_m, m_pJacbi, x, &jac_eps) != TR_SUCCESS)
			{
				//MKL_Free_Buffers();
				return false;
			}
		}
	}

	int st_cr;
	double r1, r2;
	if (dtrnlspbc_get(&handle, &iter, &st_cr, &r1, &r2) != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}

	if (dtrnlspbc_delete(&handle) != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}

	//MKL_Free_Buffers();
	return true;
}


bool CXNLSQMethod::Calculate2WithUserData(int m, int n, double* x, void* userData)
{
	//mkl_set_num_threads(1);
	m_m = m;
	m_n = n;

	// eps
	double eps[6];
	for (int i = 0; i < 6; ++i)
		eps[i] = 1.0e-5;

	//eps[0] = 1.0e-14;
	//eps[3] = 1.0e-14;
	//eps[4] = 1.0e-14;

	double jac_eps = 1.0e-8;
	double rs = 0;
	int iter1 = 1000, iter2 = 200, iter;

	// set zeros
	memset(m_pJacbi, 0, sizeof(double)*m_m*m_n);
	memset(m_pResidual, 0, sizeof(double)*m_m);

	// init
	_TRNSP_HANDLE_t handle;
	int check0 = dtrnlsp_init(&handle, &m_n, &m_m, x, eps, &iter1, &iter2, &rs);
	if (check0 != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}

	int info[6];
	if (dtrnlsp_check(&handle, &m_n, &m_m, m_pJacbi, m_pResidual, eps, info) != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}
	else
	{
		if (info[0] != 0 || // The handle is not valid.
			info[1] != 0 || // The jacobi array is not valid.
			info[2] != 0 || // The y array is not valid.
			info[3] != 0    // The eps array is not valid.
			)
		{
			//MKL_Free_Buffers();
			return false;
		}
	}

	//	djacobi_init(&handle, &m_n, &m_m, x, m_pJacbi, &jac_eps);

	int RCI_Request = 0;
	bool successful = false;
	int curLoop = 0;
	while (!successful)
	{
		if (m_nMaxLoop<curLoop)
		{
			break;
		}
		curLoop++;
		if (dtrnlsp_solve(&handle, m_pResidual, m_pJacbi, &RCI_Request) != TR_SUCCESS)
		{
			//MKL_Free_Buffers();
			return false;
		}

		if (RCI_Request == -1 ||
			RCI_Request == -2 ||
			RCI_Request == -3 ||
			RCI_Request == -4 ||
			RCI_Request == -5 ||
			RCI_Request == -6)

			successful = true;

		if (RCI_Request == 1)
		{
			(*m_pFunctionWithUserData)(&m_m, &m_n, x, m_pResidual, userData);
		}
		else if (RCI_Request == 2)
		{
			if (djacobix(m_pFunctionWithUserData, &m_n, &m_m, m_pJacbi, x, &jac_eps, userData) != TR_SUCCESS)
			{
				//MKL_Free_Buffers();
				return false;
			}
		}
	}

	int st_cr;
	double r1, r2;
	if (dtrnlsp_get(&handle, &iter, &st_cr, &r1, &r2) != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}

	if (dtrnlsp_delete(&handle) != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}

	//MKL_Free_Buffers();
	return true;
}

bool CXNLSQMethod::Calculate3WithUserData(double* x, double* lower, double* upper, void* userData)
{
	mkl_set_num_threads(1);
	
	// eps
	double eps[6];
	for (int i = 0; i < 6; ++i)
		eps[i] = 1.0e-5;

	//eps[0] = 1.0e-14;
	//eps[3] = 1.0e-14;
	//eps[4] = 1.0e-14;

	double jac_eps = 1.0e-8;
	double rs = 0;
	int iter1 = 1000, iter2 = 200, iter;

	// set zeros
	memset(m_pJacbi, 0, sizeof(double)*m_m*m_n);
	memset(m_pResidual, 0, sizeof(double)*m_m);

	// init
	_TRNSPBC_HANDLE_t handle;
	int check0 = dtrnlspbc_init(&handle, &m_n, &m_m, x, lower, upper, eps, &iter1, &iter2, &rs);
	if (check0 != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}

	int info[6];
	if (dtrnlspbc_check(&handle, &m_n, &m_m, m_pJacbi, m_pResidual, lower, upper, eps, info) != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}
	else
	{
		if (info[0] != 0 || // The handle is not valid.
			info[1] != 0 || // The jacobi array is not valid.
			info[2] != 0 || // The y array is not valid.
			info[3] != 0 || // The lower array is not valid.
			info[4] != 0 || // The upper array is not valid.
			info[5] != 0    // The eps array is not valid.
			)
		{
			//MKL_Free_Buffers();
			return false;
		}
	}

	//	djacobi_init(&handle, &m_n, &m_m, x, m_pJacbi, &jac_eps);

	int RCI_Request = 0;
	bool successful = false;
	int curLoop = 0;
	while (!successful)
	{
		if (m_nMaxLoop<curLoop)
		{
			break;
		}
		curLoop++;
		if (dtrnlspbc_solve(&handle, m_pResidual, m_pJacbi, &RCI_Request) != TR_SUCCESS)
		{
			//MKL_Free_Buffers();
			return false;
		}

		if (RCI_Request == -1 ||
			RCI_Request == -2 ||
			RCI_Request == -3 ||
			RCI_Request == -4 ||
			RCI_Request == -5 ||
			RCI_Request == -6)

			successful = true;

		if (RCI_Request == 1)
		{
			(*m_pFunctionWithUserData)(&m_m, &m_n, x, m_pResidual, userData);
		}
		else if (RCI_Request == 2)
		{
			if (djacobix(m_pFunctionWithUserData, &m_n, &m_m, m_pJacbi, x, &jac_eps, userData) != TR_SUCCESS)
			{
				//MKL_Free_Buffers();
				return false;
			}
		}
	}

	int st_cr;
	double r1, r2;
	if (dtrnlspbc_get(&handle, &iter, &st_cr, &r1, &r2) != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}

	if (dtrnlspbc_delete(&handle) != TR_SUCCESS)
	{
		//MKL_Free_Buffers();
		return false;
	}

	//MKL_Free_Buffers();
	return true;
}
