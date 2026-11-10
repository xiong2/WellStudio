#include "xutility.h"
#include <qstring.h>
#include "xcurvefitting.h"
#include "xfunctiontemplate.h"
#include <cmath>
#include <QDesktopWidget>
#include <QApplication>

int NXUtility::GetGCD(int a, int b)
{
	a = qAbs(a);
	b = qAbs(b);

	if (a < b)
		qSwap(a, b);

	if (b == 0)
		return a;
	else
		return GetGCD(a-b, b);
}

int NXUtility::GetLCM(int a, int b)
{
	int tmp = GetGCD(a, b);
	return tmp ? (a / tmp*b) : 0;
}

double NXUtility::Select(double* pData, const int n, const int k)
{
	int i,ir,j,l,mid;
	double a;
	l=0;
	ir=n-1;
	for (;;) 
	{
		if (ir <= l+1) 
		{
			if (ir == l+1 && pData[ir] < pData[l])
				qSwap(pData[l],pData[ir]);
			return pData[k];
		}
		else
		{
			mid=(l+ir) >> 1;
			qSwap(pData[mid],pData[l+1]);

			if (pData[l] > pData[ir])
				qSwap(pData[l],pData[ir]);

			if (pData[l+1] > pData[ir])
				qSwap(pData[l+1],pData[ir]);

			if (pData[l] > pData[l+1])
				qSwap(pData[l], pData[l+1]);

			i = l+1;
			j = ir;
			a = pData[l+1];
			for (;;) 
			{
				do i++; while (pData[i] < a);
				do j--; while (pData[j] > a);
				if (j < i) break;
				qSwap(pData[i], pData[j]);
			}
			pData[l+1]=pData[j];
			pData[j]=a;

			if (j >= k) ir=j-1;
			if (j <= k) l=i;
		}
	}
}

float NXUtility::Select(float* pData, const int n, const int k)
{
	int i, ir, j, l, mid;
	double a;
	l = 0;
	ir = n - 1;
	for (;;)
	{
		if (ir <= l + 1)
		{
			if (ir == l + 1 && pData[ir] < pData[l])
				qSwap(pData[l], pData[ir]);
			return pData[k];
		}
		else
		{
			mid = (l + ir) >> 1;
			qSwap(pData[mid], pData[l + 1]);

			if (pData[l] > pData[ir])
				qSwap(pData[l], pData[ir]);

			if (pData[l + 1] > pData[ir])
				qSwap(pData[l + 1], pData[ir]);

			if (pData[l] > pData[l + 1])
				qSwap(pData[l], pData[l + 1]);

			i = l + 1;
			j = ir;
			a = pData[l + 1];
			for (;;)
			{
				do i++; while (pData[i] < a);
				do j--; while (pData[j] > a);
				if (j < i) break;
				qSwap(pData[i], pData[j]);
			}
			pData[l + 1] = pData[j];
			pData[j] = a;

			if (j >= k) ir = j - 1;
			if (j <= k) l = i;
		}
	}
}

double NXUtility::CalDistance (double p1[3], double p2[3])
{
    return sqrt((p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]) + (p1[2]-p2[2])*(p1[2]-p2[2]));
}

double NXUtility::CalDistance2D (double p1[2], double p2[2])
{
	return sqrt((p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]));
}

void NXUtility::ExtendLine2D (double p1[2], double p2[2], double fNewDist, double pNew[2])
{
    double fRatio, fDist;
    fDist = CalDistance(p1, p2);
     
    if (fabs(fDist - fNewDist) < 0.00001)
    {
        pNew[0] = p2[0];
        pNew[1] = p2[1];
    }
    else
    {
        if (fNewDist > fDist)
        {
            fRatio = fDist/(fNewDist - fDist);
            pNew[0] = ((1+fRatio)*p2[0] - p1[0])/fRatio;
            pNew[1] = ((1+fRatio)*p2[1] - p1[1])/fRatio;
        }
        else
        {
            fRatio = fNewDist/(fDist - fNewDist);
            pNew[0] = (p1[0] + fRatio*p2[0])/(1 + fRatio);
            pNew[1] = (p1[1] + fRatio*p2[1])/(1 + fRatio);
        }
    }
}

void NXUtility::ExtendLine (double p1[3], double p2[3], double fNewDist, double pNew[3])
{
    double fRatio, fDist;
    fDist = CalDistance(p1, p2);
     
    if (fabs(fDist - fNewDist) < 0.00001)
    {
        pNew[0] = p2[0];
        pNew[1] = p2[1];
        pNew[2] = p2[2];
    }
    else
    {
        if (fNewDist > fDist)
        {
            fRatio = fDist/(fNewDist - fDist);
            pNew[0] = ((1+fRatio)*p2[0] - p1[0])/fRatio;
            pNew[1] = ((1+fRatio)*p2[1] - p1[1])/fRatio;
            pNew[2] = ((1+fRatio)*p2[2] - p1[2])/fRatio;
        }
        else
        {
            fRatio = fNewDist/(fDist - fNewDist);
            pNew[0] = (p1[0] + fRatio*p2[0])/(1 + fRatio);
            pNew[1] = (p1[1] + fRatio*p2[1])/(1 + fRatio);
            pNew[2] = (p1[2] + fRatio*p2[2])/(1 + fRatio);
        }
    }
}

#define VEC3_EPSILON 0.000001

#define VEC3_SUB(dest, v1, v2) \
			dest[0]=v1[0]-v2[0]; \
			dest[1]=v1[1]-v2[1]; \
			dest[2]=v1[2]-v2[2];

#define VEC3_CROSS(dest, v1, v2) \
			dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
			dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
			dest[2]=v1[0]*v2[1]-v1[1]*v2[0];

#define VEC3_DOT(v1, v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])

bool NXUtility::Intersect_RayTriangle(double orig[3], double dir[3], double v0[3], double v1[3], double v2[3], double *t, double *u, double *v)
{
	double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	double det, inv_det;

	// find vectors for two edges sharing vertex 0
	VEC3_SUB(edge1, v1, v0);
	VEC3_SUB(edge2, v2, v0);

	// begin calculating determinant - also used to calculate U parameter
	VEC3_CROSS(pvec, dir, edge2);

	// if determinant is near zero, ray lies in plane of triangle.
	det = VEC3_DOT(edge1, pvec);

	if (det > -VEC3_EPSILON && det < VEC3_EPSILON)
		return false;
	inv_det = 1.0 / det;

	// calculate distance from vertex 0 to ray origin
	VEC3_SUB(tvec, orig, v0);

	// calculate U parameter and test bounds
	*u = VEC3_DOT(tvec, pvec) * inv_det;
	if (*u < 0.0 || *u > 1.0)
		return false;

	// prepare to test V parameter
	VEC3_CROSS(qvec, tvec, edge1);

	// calculate V parameter and test bounds
	*v = VEC3_DOT(dir, qvec) * inv_det;
	if (*v < 0.0 || *u + *v > 1.0)
		return false;

	// calculate t, ray intersects triangle
	*t = VEC3_DOT(edge2, qvec) * inv_det;

	return true;
}

bool NXUtility::ReSample(int nSrcQty, double *pSrcX, double *pSrcY, int nTarQty, double *pTarX, double *pTarY, double fInvalidData, bool bLinear)
{
	if (nSrcQty < 2)
		return false;
	memset(pTarY, 0, sizeof(double)*nTarQty);
	double fInvalidEPS = fInvalidData*M_FEPS;

	double fTargetX, fSourceX;
	int iMin, iMax;
	double p3X[3], p3Y[3], a, b, c;
	// left end
	p3X[0] = pSrcX[0], p3X[1] = pSrcX[1];
	p3Y[0] = pSrcY[0], p3Y[1] = pSrcY[1];
	iMin = -1;
	for (int i = 0; i < nTarQty; ++i)
	{
		fTargetX = pTarX[i];
		if (fTargetX < p3X[0])
		{
			if (qAbs(p3Y[0] - fInvalidData) < fInvalidEPS)
				pTarY[i] = fInvalidData;
			else if (qAbs(p3Y[1] - fInvalidData) < fInvalidEPS)
				pTarY[i] = p3Y[0];
			else
			{
				if (CXCurveFitting<double>::LinearFitting(p3X, p3Y, a, b))
					pTarY[i] = a*fTargetX + b;
				else
					pTarY[i] = p3Y[0];
			}
			iMin = i;
		}
		else
		{
			break;
		}
	}
	// right end
	p3X[0] = pSrcX[nSrcQty - 1], p3X[1] = pSrcX[nSrcQty - 2];
	p3Y[0] = pSrcY[nSrcQty - 1], p3Y[1] = pSrcY[nSrcQty - 2];
	iMax = nTarQty;
	for (int i = nTarQty - 1; i >= 0; --i)
	{
		fTargetX = pTarX[i];
		if (fTargetX > p3X[0])
		{
			if (qAbs(p3Y[0] - fInvalidData) < fInvalidEPS)
				pTarY[i] = fInvalidData;
			else if (qAbs(p3Y[1] - fInvalidData) < fInvalidEPS)
				pTarY[i] = p3Y[0];
			else
			{
				if (CXCurveFitting<double>::LinearFitting(p3X, p3Y, a, b))
					pTarY[i] = a*fTargetX + b;
				else
					pTarY[i] = p3Y[0];
			}
			iMax = i;
		}
		else
		{
			break;
		}
	}

	// middle data
	int j = 0;
	bool bContinue, b1, b2, b3;
	int i0, i1, i2, i3;
	for (int i = iMin + 1; i <= iMax - 1; ++i)
	{
		fTargetX = pTarX[i];
		bContinue = false;
		while (j < nSrcQty)
		{
			fSourceX = pSrcX[j];
			if (fTargetX == fSourceX)
			{
				pTarY[i] = pSrcY[j];
				bContinue = true;
				break;
			}
			else if (fTargetX < fSourceX)
			{
				i2 = j;
				break;
			}
			++j;
		}

		if (bContinue)
			continue;
		else
		{
			i1 = i2 - 1;
			while (i1 >= 0 && pSrcX[i1] == pSrcX[i2])
				--i1;
			i0 = i1 - 1;
			while (i0 >= 0 && pSrcX[i0] == pSrcX[i1])
				--i0;
			i3 = i2 + 1;
			while (i3<nSrcQty && pSrcX[i3] == pSrcX[i2])
				++i3;

			if (i0 < 0)
			{
				p3X[0] = pSrcX[i1], p3X[1] = pSrcX[i2];
				p3Y[0] = pSrcY[i1], p3Y[1] = pSrcY[i2];
				b1 = qAbs(p3Y[0] - fInvalidData) > fInvalidEPS;
				b2 = qAbs(p3Y[1] - fInvalidData) > fInvalidEPS;

				if (i3<nSrcQty)
				{
					p3X[2] = pSrcX[i3];
					p3Y[2] = pSrcY[i3];
					b3 = qAbs(p3Y[2] - fInvalidData) > fInvalidEPS;
					if (b1 && b2 && b3)
					{
						if (bLinear)
						{
							CXCurveFitting<double>::LinearFitting(p3X, p3Y, a, b);
							pTarY[i] = a*fTargetX + b;
						}
						else
						{
							CXCurveFitting<double>::ParabolaFitting(p3X, p3Y, a, b, c);
							pTarY[i] = a*fTargetX*fTargetX + b*fTargetX + c;
						}
						continue;
					}
				}
				if (b1 && b2)
				{
					CXCurveFitting<double>::LinearFitting(p3X, p3Y, a, b);
					pTarY[i] = a*fTargetX + b;
				}
				else
				{
					if (fTargetX - p3X[0] < p3X[1] - fTargetX)
						pTarY[i] = p3Y[0];
					else
						pTarY[i] = p3Y[1];
				}
			}
			else
			{
				p3X[0] = pSrcX[i0], p3X[1] = pSrcX[i1], p3X[2] = pSrcX[i2];
				p3Y[0] = pSrcY[i0], p3Y[1] = pSrcY[i1], p3Y[2] = pSrcY[i2];
				b1 = qAbs(p3Y[0] - fInvalidData) > fInvalidEPS;
				b2 = qAbs(p3Y[1] - fInvalidData) > fInvalidEPS;
				b3 = qAbs(p3Y[2] - fInvalidData) > fInvalidEPS;
				if (b1 && b2 && b3)
				{
					if (bLinear)
					{
						CXCurveFitting<double>::LinearFitting(p3X + 1, p3Y + 1, a, b);
						pTarY[i] = a*fTargetX + b;
					}
					else
					{
						CXCurveFitting<double>::ParabolaFitting(p3X, p3Y, a, b, c);
						pTarY[i] = a*fTargetX*fTargetX + b*fTargetX + c;
					}
				}
				else if (b2 && b3)
				{
					CXCurveFitting<double>::LinearFitting(p3X + 1, p3Y + 1, a, b);
					pTarY[i] = a*fTargetX + b;
				}
				else
				{
					if (fTargetX - p3X[1] < p3X[2] - fTargetX)
						pTarY[i] = p3Y[1];
					else
						pTarY[i] = p3Y[2];
				}
			}
		}
	}
	return true;
}

int NXUtility::LengthofFFT(const int nz)
{
	int m = 1;
	while (m < nz)
		m <<= 1;
	return m;
}

void NXUtility::FourierTransform(double *data, const int nFFT, const int isign)
{
	int n, mmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta;
	double tempr, tempi;
	double thetatmp = -1.0*isign*M_2XPI;

	n = nFFT << 1;
	j = 1;
	for (i = 1; i < n; i += 2)
	{
		if (j > i)
		{
			qSwap(data[i], data[j]);
			qSwap(data[i - 1], data[j - 1]);
		}
		m = nFFT;
		while (m >= 2 && j > m)
		{
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	mmax = 2;
	while (n > mmax)
	{
		istep = mmax << 1;
		theta = thetatmp / mmax;
		wtemp = sin(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi = sin(theta);
		wr = 1.0;
		wi = 0.0;
		for (m = 1; m < mmax; m += 2)
		{
			for (i = m; i <= n; i += istep)
			{
				j = i + mmax;
				tempr = wr*data[j - 1] - wi*data[j];
				tempi = wr*data[j] + wi*data[j - 1];
				data[j - 1] = data[i - 1] - tempr;
				data[j] = data[i] - tempi;
				data[i - 1] += tempr;
				data[i] += tempi;
			}
			wr = (wtemp = wr)*wpr - wi*wpi + wr;
			wi = wi*wpr + wtemp*wpi + wi;
		}
		mmax = istep;
	}
}

void NXUtility::TrapzoidFilter(int nK, double* pIn, double* pOut, double* pFFTData, double fSamplingRate, double f1, double f2, double f3, double f4)
{
	int nFFTSize = LengthofFFT(nK);
	memset(pFFTData, 0, sizeof(double)*nFFTSize * 2);
	for (int k = 0; k < nK; ++k)
	{
		pFFTData[2 * k] = pIn[k];
	}
	FourierTransform(pFFTData, nFFTSize, 1);

	double deltaFreq = 1000.f / fSamplingRate / nFFTSize;

	int index1 = qBound(0, static_cast<int>(f1 / deltaFreq), nFFTSize / 2);
	int index2 = qBound(0, static_cast<int>(f2 / deltaFreq), nFFTSize / 2);
	int index3 = qBound(0, static_cast<int>(f3 / deltaFreq), nFFTSize / 2);
	int index4 = qBound(0, static_cast<int>(f4 / deltaFreq), nFFTSize / 2);

	// < f1
	if (index1 > 0)
	{
		pFFTData[0] = 0;
		pFFTData[1] = 0;
	}
	for (int k = 1; k < index1; ++k)
	{
		pFFTData[2 * k] = 0;
		pFFTData[2 * k + 1] = 0;
		pFFTData[2 * (nFFTSize - k)] = 0;
		pFFTData[2 * (nFFTSize - k) + 1] = 0;
	}

	// > f4
	for (int k = index4 + 1; k <= nFFTSize / 2; ++k)
	{
		pFFTData[2 * k] = 0;
		pFFTData[2 * k + 1] = 0;
		pFFTData[2 * (nFFTSize - k)] = 0;
		pFFTData[2 * (nFFTSize - k) + 1] = 0;
	}

	// f1-f2
	if (index2 > index1)
	{
		for (int k = index1; k <= index2; ++k)
		{
			if (k == 0)
			{
				pFFTData[0] = 0;
				pFFTData[1] = 0;
			}
			else
			{
				pFFTData[2 * k] *= SQR(sin((1.f*k - index1) / (index2 - index1)*M_PI_2));
				pFFTData[2 * k + 1] *= SQR(sin((1.f*k - index1) / (index2 - index1)*M_PI_2));

				pFFTData[2 * (nFFTSize - k)] *= SQR(sin((1.f*k - index1) / (index2 - index1)*M_PI_2));
				pFFTData[2 * (nFFTSize - k) + 1] *= SQR(sin((1.f*k - index1) / (index2 - index1)*M_PI_2));
			}
		}

	}

	// f3-f4
	if (index4 > index3)
	{
		for (int k = index3; k <= index4; ++k)
		{
			if (k == 0)
			{
				continue;
			}
			else
			{
				pFFTData[2 * k] *= SQR(sin((1.f - (1.f*k - index3) / (index4 - index3))*M_PI_2));
				pFFTData[2 * k + 1] *= SQR(sin((1.f - (1.f*k - index3) / (index4 - index3))*M_PI_2));

				pFFTData[2 * (nFFTSize - k)] *= SQR(sin((1.f - (1.f*k - index3) / (index4 - index3))*M_PI_2));
				pFFTData[2 * (nFFTSize - k) + 1] *= SQR(sin((1.f - (1.f*k - index3) / (index4 - index3))*M_PI_2));
			}
		}
	}

	//inverse fft
	FourierTransform(pFFTData, nFFTSize, -1);

	for (int i = 0; i < 2 * nFFTSize; ++i)
		pFFTData[i] /= nFFTSize;

	//set data
	for (int k = 0; k < nK; ++k)
	{
		pOut[k] = pFFTData[2 * k];
	}

}

void NXUtility::MergeTwoFreqComonents(int nK, double* pInLow, double* pInHigh, double* pOut, double* pFFTDataLow, double* pFFTDataHigh, double dSamplingFreq, double dCutFreq, double dOverlapFreq)
{	
	int nFFTSize = LengthofFFT(nK);
	double deltaFreq = dSamplingFreq / nFFTSize;

	int iCutIndex = qBound(0, static_cast<int>(dCutFreq / deltaFreq), nFFTSize / 2);
	int iLowPass = qBound(0, static_cast<int>((dCutFreq + dOverlapFreq) / deltaFreq), nFFTSize / 2);
	int iHightPass = qBound(0, static_cast<int>((dCutFreq - dOverlapFreq) / deltaFreq), nFFTSize / 2);

	// Low pass
	memset(pFFTDataLow, 0, sizeof(double)*nFFTSize * 2);
	for (int k = 0; k < nK; ++k)
		pFFTDataLow[2 * k] = pInLow[k];

	FourierTransform(pFFTDataLow, nFFTSize, 1);

	for (int i = iCutIndex+1; i < iLowPass; ++i)
	{
		double dCoef = sinc((i - iCutIndex)*1. / (iLowPass - iCutIndex));

		pFFTDataLow[2 * i] *= dCoef;
		pFFTDataLow[2 * i + 1] *= dCoef;

		pFFTDataLow[2 * (nFFTSize - i)] *= dCoef;
		pFFTDataLow[2 * (nFFTSize - i) + 1] *= dCoef;
	}

	for (int i = iLowPass; i <= nFFTSize / 2; ++i)
	{
		pFFTDataLow[2 * i] = 0;
		pFFTDataLow[2 * i + 1] = 0;

		pFFTDataLow[2 * (nFFTSize - i)] = 0;
		pFFTDataLow[2 * (nFFTSize - i) + 1] = 0;
	}

	// high pass
	memset(pFFTDataHigh, 0, sizeof(double)*nFFTSize * 2);
	for (int k = 0; k < nK; ++k)
		pFFTDataHigh[2 * k] = pInHigh[k];

	FourierTransform(pFFTDataHigh, nFFTSize, 1);

	for (int i = iCutIndex - 1; i > iHightPass; --i)
	{
		double dCoef = sinc((iCutIndex - i)*1. / (iCutIndex - iHightPass));

		pFFTDataHigh[2 * i] *= dCoef;
		pFFTDataHigh[2 * i + 1] *= dCoef;

		pFFTDataHigh[2 * (nFFTSize - i)] *= dCoef;
		pFFTDataHigh[2 * (nFFTSize - i) + 1] *= dCoef;
	}

	for (int i = iHightPass; i >= 0; --i)
	{
		if (i == 0)
		{
			pFFTDataHigh[0] = 0;
			pFFTDataHigh[1] = 0;
		}
		else
		{
			pFFTDataHigh[2 * i] = 0;
			pFFTDataHigh[2 * i + 1] = 0;

			pFFTDataHigh[2 * (nFFTSize - i)] = 0;
			pFFTDataHigh[2 * (nFFTSize - i) + 1] = 0;
		}
	}

	// merge
	//inverse fft
	FourierTransform(pFFTDataLow, nFFTSize, -1);
	FourierTransform(pFFTDataHigh, nFFTSize, -1);

	for (int i = 0; i < 2 * nFFTSize; ++i)
	{
		pFFTDataLow[i] /= nFFTSize;
		pFFTDataHigh[i] /= nFFTSize;
	}

	//set data
	for (int k = 0; k < nK; ++k)
	{
		pOut[k] = pFFTDataLow[2 * k] + pFFTDataHigh[2 * k];
	}
	
}

void NXUtility::DigitalFilter(int n, double* pIn, double* pout, double dt, double f1, double f1ovp, double f2, double f2ovp, double *pFFT, double *pH1, double* pH2)
{
	double fNquist = 500. / dt;
	int n2 = n * 2;
	int nFFTSize = LengthofFFT(n2);
	int nh = nFFTSize / 2;
	memset(pFFT, 0, sizeof(double) * 2 * nFFTSize);

	// data flipping	
	for (int i = 0; i < n; ++i)
		pFFT[2 * i] = pIn[i];

	for (int i = n; i < n2; ++i)
		pFFT[2 * i] = pIn[n2-1-i];

	// padding
	for (int i = n2; i < nFFTSize; ++i)
		pFFT[2 * i] = pIn[0];

	//low cut
double dFreq;
double deltaF = fNquist / nh;
if (f1 == 0)
{
	for (int i = 0; i <= nh; ++i)
		pH1[i] = 1.;
}
else
{
	f1 = qBound(0., f1, fNquist);
	f1ovp = qAbs(f1ovp);
	double f1half = f1ovp / 2.;
	for (int i = 0; i <= nh; ++i)
	{
		dFreq = i*deltaF;
		if (dFreq < f1 - f1half)
			pH1[i] = 0.;
		else if (dFreq > f1 + f1half)
			pH1[i] = 1.;
		else
			pH1[i] = 0.5*(1. + sin(M_PI*(dFreq - f1) / f1ovp));
	}
}

// high cut
if (f2 == 0)
{
	for (int i = 0; i <= nh; ++i)
		pH2[i] = 1.;
}
else
{
	f2 = qBound(0., f2, fNquist);
	f2ovp = qAbs(f2ovp);
	double f2half = f2ovp / 2.;
	for (int i = 0; i <= nh; ++i)
	{
		dFreq = i*deltaF;
		if (dFreq < f2 - f2half)
			pH2[i] = 1.;
		else if (dFreq > f2 + f2half)
			pH2[i] = 0.;
		else
			pH2[i] = 0.5*(1. - sin(M_PI*(dFreq - f2) / f2ovp));
	}
}

// H
for (int i = 0; i <= nh; ++i)
pH1[i] = qMin(pH1[i], pH2[i]) / nFFTSize;

for (int i = nh + 1; i < nFFTSize; ++i)
{
	pH1[i] = pH1[nFFTSize - i];
}

// FFT
FourierTransform(pFFT, nFFTSize, 1);

// *H
for (int i = 0; i < nFFTSize; ++i)
{
	pFFT[2 * i] *= pH1[i];
	pFFT[2 * i + 1] *= pH1[i];
}

// inverse FFT
FourierTransform(pFFT, nFFTSize, -1);

//out
for (int i = 0; i < n; ++i)
	pout[i] = pFFT[2 * i];

}

void NXUtility::GetMMPerDPI(float& fMMX, float& fMMY)
{
	QWidget* pDesktop = QApplication::desktop();

	float fLogicX = pDesktop->logicalDpiX();
	float fLogicY = pDesktop->logicalDpiY();

	float fMMPerInch = 25.4f;

	fMMX = fMMPerInch / fLogicX;
	fMMY = fMMPerInch / fLogicY;
}

void NXUtility::FilterTwoData(int nI, int nJ, float* pDen, float* pAzi, int nWinNI, int nWinNJ, float fInvalid)
{
	int iHalfI = qMax(1, nWinNI / 2);
	int iHalfJ = qMax(1, nWinNJ / 2);
	nWinNI = iHalfI * 2 + 1;
	nWinNJ = iHalfJ * 2 + 1;

	std::vector<float> vecDen(nI*nJ), vecAZi(nI*nJ);
	memcpy(&vecDen[0], pDen, sizeof(float)*nI*nJ);
	memcpy(&vecAZi[0], pAzi, sizeof(float)*nI*nJ);
	

	for (int i = 0; i < nI; ++i)
	{
		int iMin = qBound(0, i- iHalfI, nI - 1);
		int iMax = qBound(0, i + iHalfI, nI - 1);
		for (int j = 0; j < nJ; ++j)
		{
			int jMin = qBound(0, j - iHalfJ, nJ - 1);
			int jMax = qBound(0, j + iHalfJ, nJ - 1);

			int iPos = -1, jPos = -1;
			float fMax = M_FLT_NEGATIVEMAX;
			for (int iI = iMin; iI <= iMax; ++iI)
			{
				for (int iJ = jMin; iJ < jMax; ++iJ)
				{
					if (fInvalid == vecDen[iI*nJ + iJ])
						continue;

					if (vecDen[iI*nJ + iJ] > fMax)
					{
						fMax = vecDen[iI*nJ + iJ];
						iPos = iI;
						jPos = iJ;
					}
				}
			}
			if (iPos != -1)
			{
				pDen[i*nJ + j] = vecDen[iPos*nJ + jPos];
				pAzi[i*nJ + j] = vecAZi[iPos*nJ + jPos];
			}
		}
	}
}

void NXUtility::CalcGauLeg(double x1, double x2, int n, double *x, double* w)
{
	const double EPS = 1.0e-14;
	double z1, z, xm, xl, pp, p3, p2, p1;
	int m = (n + 1) / 2;
	xm = 0.5*(x2 + x1);
	xl = 0.5*(x2 - x1);
	for (int i = 0; i<m; i++) {
		z = cos(3.141592654*(i + 0.75) / (n + 0.5));
		do {
			p1 = 1.0;
			p2 = 0.0;
			for (int j = 0; j<n; j++) {
				p3 = p2;
				p2 = p1;
				p1 = ((2.0*j + 1.0)*z*p2 - j*p3) / (j + 1);
			}
			pp = n*(z*p1 - p2) / (z*z - 1.0);
			z1 = z;
			z = z1 - p1 / pp;
		} while (qAbs(z - z1) > EPS);
		x[i] = xm - xl*z;
		x[n - 1 - i] = xm + xl*z;
		w[i] = 2.0*xl / ((1.0 - z*z)*pp*pp);
		w[n - 1 - i] = w[i];
	}
}

double NXUtility::CalcGauIntegral(double a, double b, IntegralFunction function, int nStep, double* parameter)
{
	double *x = new double [nStep];
	double *w = new double [nStep];

	CalcGauLeg(a, b, nStep, x, w);

	double dResult = 0.;
	for (int i = 0; i < nStep; ++i)
	{
		dResult += w[i] * function(x[i], parameter);
	}

	delete[]x;
	delete[]w;

	return dResult;
}