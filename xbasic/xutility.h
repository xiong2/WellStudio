#ifndef XUTILITY_H
#define XUTILITY_H


#include "xbasic_global.h"
#include "xhistogram.h"
#include "xmathmacro.h"


using std::vector;

typedef double (*IntegralFunction)(double x, double* parameter);

namespace NXUtility
{
	///@brief Select kth smallest element
	XBASIC_EXPORT double Select(double* pData, const int n, const int k);
	XBASIC_EXPORT float Select(float* pData, const int n, const int k);

	///@brief Get the greatest common divisor
	XBASIC_EXPORT int GetGCD(int a, int b);
	XBASIC_EXPORT int GetLCM(int a, int b);

	///@brief Calculate histogram (only for double or float format data)
	template<typename T>
	bool CalcHistogram(T* pData, int nDataNum, CXHistogram& histogram)
	{
		double dEPSInvalid = qAbs(M_FINVALID*M_FEPS);

		if (pData == NULL || nDataNum == 0) 
			return false;

		// Min and Max
		int nValidDataNum = 0;
		histogram.m_dDataMin = FLT_MAX;
		histogram.m_dDataMax = -FLT_MAX;
		double dSum = 0, dValue;
		for (int i=0; i<nDataNum; ++i)
		{
			dValue = pData[i];
			if (qAbs(dValue - M_FINVALID) < dEPSInvalid)
				continue;

			histogram.m_dDataMin = qMin(histogram.m_dDataMin, dValue);
			histogram.m_dDataMax = qMax(histogram.m_dDataMax, dValue);

			dSum += dValue;
			++nValidDataNum;
		}

		if (nValidDataNum == 0)
		{
			return false;
		}

		// Mean
		histogram.m_dMean = dSum/nValidDataNum;

		// Variance
		dSum = 0;
		for (int i=0; i<nDataNum; ++i)
		{
			dValue = pData[i];
			if (qAbs(dValue - M_FINVALID) < dEPSInvalid)
				continue;

			dValue = qAbs(histogram.m_dMean -dValue);
			dSum += dValue*dValue;
		}
		histogram.m_dVariance = dSum/nValidDataNum;

		// valid data num
		histogram.m_nValidDataNum = nValidDataNum;


		// Std
		int nNum = (nValidDataNum == 1 ? 1 : nValidDataNum - 1);
		histogram.m_dStd = sqrt(histogram.m_dVariance*nValidDataNum/nNum);

		// Histogram
		double dHistogramInterval = (histogram.m_dDataMax - histogram.m_dDataMin)/256;
		if (dHistogramInterval == 0.)
		{
			histogram.m_vecHorizontal.resize(256, histogram.m_dDataMin);
			histogram.m_vecVertical.resize(256, 1.);
		}
		else
		{
			histogram.m_vecHorizontal.resize(256);
			histogram.m_vecVertical.resize(256);		 
			std::vector<int> vecFrequency(256, 0);

			// Frequency
			int iInterval;
			for (int i=0; i<nDataNum; ++i)
			{
				dValue = pData[i];
				if (qAbs(dValue - M_FINVALID) < dEPSInvalid)
					continue;

				iInterval = static_cast<int>((dValue - histogram.m_dDataMin)/dHistogramInterval);
				if (iInterval < 0 || iInterval > 256)
					return false;

				if (iInterval == 256)
					--iInterval;
				vecFrequency[iInterval]++;
			}

			// Percentage
			for (int i=0; i<256; ++i)
			{
				histogram.m_vecHorizontal[i] = histogram.m_dDataMin + i*dHistogramInterval;
				histogram.m_vecVertical[i] = 1.0*vecFrequency[i]/nValidDataNum;
			}
		}

		return true;
	}

	///@brief Create a 2-D matrix[nI][nJ]. Memory must be continuous.
	template<typename T>   
    T** New2DMatrix(int nI, int nJ)
	{
		if (nI <=0 || nJ <= 0)
			return 0;

		T* p1D = 0;
		T** p2D = 0;
		try{ p1D = new T [nI*nJ]; p2D = new T* [nI];}
		catch(...)
		{
			if (p1D != 0)
				delete []p1D;
			if (p2D != 0)
				delete []p2D;
			return 0;
		}

		p2D[0] = p1D;
		for (int i=1; i<nI; ++i)
			p2D[i] = p2D[i-1] + nJ;

		return p2D;
	}

    ///@brief Free a 2-D matrix
	template<typename T>   
    void Free2DMatrix(T** pMatrix)
	{
		delete []pMatrix[0];
		delete []pMatrix;    
	}

	///@brief Create a 2-D matrix[nI][nJ]. Memory may be discontinous. 
	template<typename T>   
	T** New2DArray(int nI, int nJ)
	{
		if (nI <=0 || nJ <= 0)
			return 0;

		T** p2D;
		try	{p2D = new T* [nI];}
		catch(...)
		{
			return 0;
		}
		for (int i=0; i<nI; ++i)
			p2D[i] = 0;

		try
		{			
			for (int i=0; i<nI; ++i)
			{
				p2D[i] = new T [nJ];
			}
		}
		catch(...)
		{
			for (int i=0; i<nI; ++i)
			{
				if (p2D[i])
				{
					delete []p2D[i];
				}
			}
			delete []p2D;
			return 0;
		}	

		return p2D;
	}

	///@brief Free a 2-D array
	template<typename T>   
	void Free2DArray(T** p2DArray, int nI)
	{
		for (int i=0; i<nI; ++i)
		{
			if (p2DArray[i])
				delete []p2DArray[i];
		}
		delete []p2DArray;
	}

	///@brief dot product
	template<typename T>
	inline T DotProduct(T* pArray1, T* pArray2, int nI)
	{
		T sum = 0.;
		for (int i = 0; i < nI; ++i)
			sum += pArray1[i] * pArray2[i];

		return sum;
	}



	    ///@brief Calculate distance of two points
    XBASIC_EXPORT double CalDistance (double p1[3], double p2[3]);
	double CalDistance2D (double p1[2], double p2[2]);

    ///@brief Extend the line
    void ExtendLine (double p1[3], double p2[3], double fNewDist, double pNew[3]);
    void ExtendLine2D (double p1[2], double p2[2], double fNewDist, double pNew[2]);


	//************************************
	// Method:    intersect_triangle
	// FullName:  NXUtility::intersect_triangle
	// Access:    public 
	// Returns:   bool	intersector
	// Qualifier:
	// Parameter: double orig[3]	origin point
	// Parameter: double dir[3]		director vector
	// Parameter: double v0[3]		triangle vertex 0
	// Parameter: double v1[3]		triangle vertex 1
	// Parameter: double v2[3]		triangle vertex 2
	// Parameter: double * t		the distance to the plane in which the triangle lies
	// Parameter: double * u		barycentric coordinates u (0 ~ 1)
	// Parameter: double * v		barycentric coordinates v (0 ~ 1)
	//************************************
	XBASIC_EXPORT bool Intersect_RayTriangle(double orig[3], double dir[3], double v0[3], double v1[3], double v2[3], double *t, double *u, double *v);


	///@brief Get first index that arr[i] <= fValue <= arr[i+1] in the increased array
	template<typename T>
	int GetBinarySearchIndex(int nSize, const T* pData, T value)
	{
		if (nSize < 2)
			return 0;

		if (value < pData[0])
			return -1;

		else if (value > pData[nSize - 1])
			return nSize;

		int i = 0, j = nSize - 1, k;
		while (j - i > 1)
		{
			k = (i + j) / 2;

			if (value <= pData[k])
				j = k;

			else
				i = k;
		}
		return i;
	}

	///@brief Resampling
	XBASIC_EXPORT bool ReSample(int nSrcQty, double *pSrcX, double *pSrcY, int nTarQty, double *pTarX, double *pTarY,
		double fInvalidData = M_FINVALID, bool bLinear = false);

	///@brief Get The length of Fast Fourier Transform
	XBASIC_EXPORT int LengthofFFT(const int nz);

	///@brief Get The length of Fast Fourier Transform
	///@brief data: input and output transform data
	///@brief nFFT: the length of Fast Fourier Transform
	///@brief isign: 1: FFT, -1: inverse FFT
	XBASIC_EXPORT void	FourierTransform(double *data, const int nFFT, const int isign);

	///@brief   Calculate the frequency spectrum of the given samples.
	XBASIC_EXPORT void TrapzoidFilter(int nK, double* pIn, double* pOut, double* pFFTData, double fSamplingRate, double f1, double f2, double f3, double f4);

	///@brief Merge two frequency components
	XBASIC_EXPORT void MergeTwoFreqComonents(int nK, double* pInLow, double* pInHigh, double* pOut, double* pFFTDataLow, double* pFFTDataHigh, double dSamplingFreq, double dCutFreq, double dOverlapFreq);

	///@brief Digital filters (including lows pass, high pass and band pass)
	XBASIC_EXPORT void DigitalFilter(int n, double* pIn, double* pout, double dt, double f1, double f1ovp, double f2, double f2ovp, double *pFFT, double *pH1, double* pH2);

	///@brief Get millimeter per DPI
	XBASIC_EXPORT void GetMMPerDPI(float& fMMX, float& fMMY);

	///@brief Filter two data simutaneously
	XBASIC_EXPORT void FilterTwoData(int nI, int nJ, float* pDen, float* pAzi, int nWinNI, int nWinNJ, float fInvalid);


	///@brief Calculate x and w for Gaussian integral
	XBASIC_EXPORT void CalcGauLeg(double x1, double x2, int n, double *x, double* w);

	XBASIC_EXPORT double CalcGauIntegral(double a, double b, IntegralFunction function, int nStep = 100, double* parameter = NULL);
};

#endif
		