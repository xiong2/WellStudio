#ifndef XBLAS_H
#define XBLAS_H


#include "xbasic_global.h"

/**
 * @ namespace NXBLAS in the file "rlblas.h"
 * @brief The file provides Basic Linear Algebra Subprograms
 * 
 * @author Yong Shu 
 * @date 5/20/2014
 * @see 
 * @bug	No Known bugs so far
 */

namespace NXBLAS 
{
    /// Compute root square of the sum of two squares without destructive underflow or overflow (double)  
    inline double  Pythag(const double a, const double b);

    /// Compute root square of the sum of two squares without destructive underflow or overflow (float)  
    inline float  Pythag(const float a, const float b);
 
    /**
    * @brief Solve the Linear Equation using LU Decomposition of a square matrix (AX = b)
    * @param[in] a : n*n
    * @param[out] x : n
    * @param[in] b: n 
    * @param[in] n: dimension of a
    * @param[in] index: temporay data buffer (n) 
    * @param[in] v: temporay data buffer (n) 
    * @return false if a is singular matrix
    */
    bool SolveLinearEQU_LU(float **a, float *x, float *b, const int n, int* index, float* v);
	bool SolveLinearEQU_LU(double **a, double *x, float *b, const int n, int* index, double* v);

  
    /**
    * @brief Singular Value Decomposition of real symmetric matrix using Householder and QL method
    * @param[in][out] z : two dimensional input matrix (n*n), and replaced by eigenvectors after computation
    * @param[in][out] d : empty vector (n), and replaced by eigenvalues 
    * @param[in] e : empty vector (n), intermediate array
    * @parXBASIC_EXPORTam[in] n : dimension of the matrix z
    * @param[in] hasVector : true means z replaced by eigenvectors, false otherwise
    */
    XBASIC_EXPORT void SolveSVD(float** z, float* d, float* e, int n, bool hasVector=true);
	XBASIC_EXPORT void SolveSVD(double** z, double* d, double* e, int n, bool hasVector=true);

    /**
    * @brief Singular Value Decomposition of general m*n matrix (a = u w v')
    * @param[in] m: row number of matrix a (m*n)
    * @param[in] n:  column number of matrix a (m*n)
    * @param[out] u: m*m matrix
    * @param[out] v: n*n matrix
    * @param[out] w: n vecter (eigen values)
    * @param[in] mtmp: intermediate vector (m)
    * @param[in] ntmp: intermediate vector (n)
    * @return true if succeed, false failed
    */
	bool  SolveGeneralSVD(const int m, const int n, double **u, double **v, double *w, double *mtmp,double *ntmp);

    /**
    * @brief Gauss-Jordan Elimination for a*x = b (a: n*n;  x: n*m; b: n*m)
    * @param[in] a : n*n square matrix
    * @param[in] n : dimension of a
    * @param[in] b : right side matrix (n*m)
    * @param[in] m : column dimension of b 
    * @param[in] indxc,  indxr, ipiv : three temporary data buffer (n)
    * @date 5/26/2010
    */
    XBASIC_EXPORT bool GaussJordanElimination(float **a, int n, float **b, int m, int* indxc, int* indxr, int* ipiv);
	bool GaussJordanElimination(double **a, int n, double **b, int m, int* indxc, int* indxr, int* ipiv);


	/**
	* @brief Cholesky decomposition a = el*el' (a is positive definite matrix)
	* @param n : the dimension of the matrix a 
	* @param a : the target matrix
	* @param el : lower triangle matrix
	* @date 6/27/2011
	* @see 
	*/
	bool CholeskyDecomposition (int n, float**a, float**el);
	bool CholeskyDecomposition (int n, double**a, double**el);

	/**  
	* @brief Solve a*x = b (a is positive definite matrix) using Cholesky decomposition
	* @param n : matrix dimension, a : target matrix, el: lower triangle matrix, b: input vector, x: output 
	* @date 6/27/2011
	* @see 
	*/
	bool CholeskySolver (int n, float**a, float**el, float*b, float*x);
	bool CholeskySolver (int n, double**a, double**el, double*b, double*x);

	/**
	* @brief Inverse a (a is positive definite matrix)
	* @param  n: matrix dimension, a : target matrix, el: lower triangle matrix, aInv : output matrix
	* @date 6/27/2011
	* @see 
	*/
	XBASIC_EXPORT bool CholeskyInverse (int n, float**a, float**el, float**aInv);
	XBASIC_EXPORT bool CholeskyInverse (int n, double**a, double**el, double**aInv);

	/**
	* @brief Matrix multiplication c = a * b
	* @param[in]  a : (m n)
	* @param[in]  b : (n, p)
	* @param[out] c : (m, p)
	*/
	XBASIC_EXPORT void MultiplyMaxtrix(int m, int n, int p, double**a, double**b, double**c);
	XBASIC_EXPORT void MultiplyMaxtrix(int m, int n, int p, float**a, float**b, float**c);

	/**
	* @brief Transpose matrix
	* @param[in]  a : (m n)
	* @param[out] b : (n, m)
	*/
	XBASIC_EXPORT void TransposeMaxtrix(int m, int n, double**a, double**b);
	XBASIC_EXPORT void TransposeMaxtrix(int m, int n, float**a, float**b);

	///@brief Solve c = A*b
	///@brief A: (n, n)
	///@brief b: (n, 1)
	XBASIC_EXPORT void MultiplyRight(int n, double**a, double* b, double* c, bool bTranspose = false);
	XBASIC_EXPORT void MultiplyRight(int n, float**a, float* b, float* c, bool bTranspose = false);

	///@brief Solve c = A*b
	///@brief A: (m, n)
	///@brief b: (n, 1)
	///@brief x: (m, 1)
	XBASIC_EXPORT void MultiplyRight(int m, int n, double**a, double* b, double* c, bool bTranspose = false);
	XBASIC_EXPORT void MultiplyRight(int m, int n, float**a, float* b, float* c, bool bTranspose = false);


	///@brief Solve AX=b using bi-conjugate gradient method
	XBASIC_EXPORT void SolveLinearEQUWithBICG(int n, double**a, double*x, double*b, double tol, int itmax, int& iter, double& err);
	XBASIC_EXPORT void SolveLinearEQUWithBICG(int n, float**a, float*x, float*b, float tol, int itmax, int& iter, float& err);

	XBASIC_EXPORT void SolveLinearEQUWithBICGTwo(int n, double**a, double*x, double*b, double tol, int itmax, int& iter, double& err);


	///@brief Calculate norm
	XBASIC_EXPORT double CalcNorm (int n, double* pData);
	XBASIC_EXPORT float CalcNorm(int n, float* pData);

	///@brief Solve AX=b if A is diagonal
	XBASIC_EXPORT void SolveDiagLinearEQU(int n, double** a, double* b, double* x);	
	XBASIC_EXPORT void SolveDiagLinearEQU(int n, float** a, float* b, float* x);


};

#endif // RLBLAS_H
