#include "kelocalcrosscorr.h"
//#include "cwp.h"

#ifndef PI
#define PI 3.141592653589793
#endif
#ifndef MAX
#define	MAX(x,y) ((x) > (y) ? (x) : (y))
#endif
#ifndef MIN
#define	MIN(x,y) ((x) < (y) ? (x) : (y))
#endif

CKELocalCrossCorr::CKELocalCrossCorr()
{
	m_pProd = nullptr;
	m_pScale = nullptr;
	m_pSQRTAA = nullptr;
	m_pSQRTBB = nullptr;
	m_pAB = nullptr;
	m_pShift = nullptr;
}

CKELocalCrossCorr::~CKELocalCrossCorr()
{
	//free1float(m_pProd);
	//free1float(m_pScale);

	//free1float(m_pSQRTAA);
	//free1float(m_pSQRTBB);
	//free1float(m_pAB);
	//free1float(m_pShift);
	if (m_pProd)
		delete[]m_pProd;
	if (m_pScale)
		delete[]m_pScale;
	if (m_pSQRTAA)
		delete[]m_pSQRTAA;
	if (m_pSQRTBB)
		delete[]m_pSQRTBB;
	if (m_pAB)
		delete[]m_pAB;
	if (m_pShift)
		delete[]m_pShift;
}

void CKELocalCrossCorr::setData(int n, float *a, float *b)
{
	m_nt = n;
	m_data1 = a;
	m_data2 = b;
	//time gate
	m_startTimeSam = 0;
	m_endTimeSam = m_nt;
}

#include <fstream>
void CKELocalCrossCorr::setPara(int nwin, int ilagmin, int nlag, float threshcc)
{
	//window
	m_nwhalf = nwin / 2 + 1;
	//m_pScale = alloc1float(m_nwhalf);
	m_pScale = new float[m_nwhalf];
	float sigma2 = float(m_nwhalf - 1) / 4.;
	sigma2 = sigma2*sigma2;
	m_pScale[0] = 0.5 / PI / sigma2;
	for (int i = 1; i < m_nwhalf; i++)
	{
		float fi = float(i);
		float scale1 = exp(-0.5*fi*fi / sigma2);
		m_pScale[i] = m_pScale[0] * scale1*scale1;
	}
	//output to disk
// 	std::ofstream fout("D:\\scale.dat", std::ios::binary);
// 	fout.write((char*)m_pScale, sizeof(float)*m_nwhalf);
// 	fout.close();
	//lag range
	m_lagmin = ilagmin;
	m_nlag = nlag;
	m_lagmax = m_lagmin + m_nlag - 1;
	
	//m_pProd = alloc1float(m_nt);
	//m_pSQRTAA = alloc1float(m_nt);
	//m_pSQRTBB = alloc1float(m_nt);
	//m_pAB = alloc1float(m_nt*m_nlag);
	m_pProd = new float[m_nt];
	m_pSQRTAA = new float[m_nt];
	m_pSQRTBB = new float[m_nt];
	m_pAB = new float[m_nt * m_nlag];

	m_threshcc = threshcc;
	//m_pShift = alloc1float(m_nt);
	m_pShift = new float[m_nt];
}

void CKELocalCrossCorr::setTimeGate(int startTimeSam, int endTimeSam)
{
	m_startTimeSam = startTimeSam;
	m_endTimeSam = endTimeSam;
}

void CKELocalCrossCorr::CrossCorrLocGauss()
{
	for (int ilag = m_lagmin; ilag <= m_lagmax; ilag++)
	{
		CrossCorrLocGaussOneLag(ilag, &m_pAB[(ilag - m_lagmin)*m_nt]);
	}
	return;
}

void CKELocalCrossCorr::CrossCorrLocGaussNorm()
{
	NormalizeHalfOneLag(m_data1, m_pSQRTAA);
	NormalizeHalfOneLag(m_data2, m_pSQRTBB);
	for (int ilag = m_lagmin; ilag <= m_lagmax; ilag++)
	{
		CrossCorrLocGaussOneLag(ilag, &m_pAB[(ilag - m_lagmin)*m_nt]);
		NormalizeOneLag(ilag, &m_pAB[(ilag - m_lagmin)*m_nt]);
	}
	return;
}

void CKELocalCrossCorr::CrossCorrLocGaussOneLag(int ilag, float *c)
{
// 	if (m_pProd == NULL || m_pScale || NULL)
// 	{
// 		return;
// 	}
	int icmin = MAX(0, -ilag);
	int icmax = MIN(m_nt, m_nt - ilag);
	for (int ip = 0; ip < icmin; ip++)
	{
		m_pProd[ip] = 0.;
	}
	for (int ip = icmin; ip < icmax; ip++)
	{
		m_pProd[ip] = m_data1[ip] * m_data2[ip + ilag];
	}
	for (int ip = icmax; ip < m_nt; ip++)
	{
		m_pProd[ip] = 0.;
	}
	int ipl, ipr;
	float prodl, prodr;

	for (int ic = 0; ic < m_nt; ic++)
	{
		c[ic] = m_pProd[ic] * m_pScale[0];
		for (int iw = 1; iw < m_nwhalf; iw++)
		{
			ipl = ic - iw;
			ipr = ic + iw;
			if (ipl >= 0 && ipl < m_nt)
				prodl = m_pProd[ipl];
			else
				prodl = 0.;
			if (ipr >= 0 && ipr < m_nt)
				prodr = m_pProd[ipr];
			else
				prodr = 0.;
			c[ic] += m_pScale[iw] * (prodl + prodr);
		}
	}

	return;
}

void CKELocalCrossCorr::NormalizeHalfOneLag(float *a, float *c)
{
	for (int ip = 0; ip < m_nt; ip++)
	{
		m_pProd[ip] = a[ip]*a[ip];
	}
	int ipl, ipr;
	float prodl, prodr;
	float czerolag;

	for (int ic = 0; ic < m_nt; ic++)
	{
		czerolag = m_pProd[ic] * m_pScale[0];
		for (int iw = 1; iw < m_nwhalf; iw++)
		{
			ipl = ic - iw;
			ipr = ic + iw;
			if (ipl >= 0 && ipl < m_nt)
				prodl = m_pProd[ipl];
			else
				prodl = 0.;
			if (ipr >= 0 && ipr < m_nt)
				prodr = m_pProd[ipr];
			else
				prodr = 0.;
			czerolag += m_pScale[iw] * (prodl + prodr);
		}
		czerolag = sqrt(czerolag);
		c[ic] = (czerolag == 0) ? 0. : (1. / czerolag);
	}

	return;
}


// void CKELocalCrossCorr::CrossCorrLocGaussOneLag2(int ilag, float *c)
// {
// 	// 	if (m_pProd == NULL || m_pScale || NULL)
// 	// 	{
// 	// 		return;
// 	// 	}
// 	int icmin = MAX(0, -ilag);
// 	int icmax = MIN(m_nt, m_nt - ilag);
// 	for (int ip = 0; ip < icmin; ip++)
// 	{
// 		m_pProd[ip] = 0.;
// 	}
// 	for (int ip = icmin; ip < icmax; ip++)
// 	{
// 		m_pProd[ip] = m_data1[ip] * m_data2[ip + ilag];
// 	}
// 	for (int ip = icmax; ip < m_nt; ip++)
// 	{
// 		m_pProd[ip] = 0.;
// 	}
// 	int ipl, ipr;
// 	float prodl, prodr;
// 	for (int ic = 0; ic < m_startTimeSam; ic++)
// 		c[ic] = 0.;
// 	for (int ic = m_startTimeSam; ic < m_endTimeSam; ic++)
// 	{
// 		c[ic] = m_pProd[ic] * m_pScale[0];
// 		for (int iw = 1; iw < m_nwhalf; iw++)
// 		{
// 			ipl = ic - iw;
// 			ipr = ic + iw;
// 			if (ipl >= 0 && ipl < m_nt)
// 				prodl = m_pProd[ipl];
// 			else
// 				prodl = 0.;
// 			if (ipr >= 0 && ipr < m_nt)
// 				prodr = m_pProd[ipr];
// 			else
// 				prodr = 0.;
// 			c[ic] += m_pScale[iw] * (prodl + prodr);
// 		}
// 	}
// 	for (int ic = m_endTimeSam; ic < m_nt; ic++)
// 		c[ic] = 0.;
// 	return;
// }
// 
// void CKELocalCrossCorr::NormalizeHalfOneLag2(float *a, float *c)
// {
// 	for (int ip = 0; ip < m_nt; ip++)
// 	{
// 		m_pProd[ip] = a[ip] * a[ip];
// 	}
// 	int ipl, ipr;
// 	float prodl, prodr;
// 	float czerolag;
// 	for (int ic = 0; ic < m_startTimeSam; ic++)
// 		c[ic] = 0.;
// 	for (int ic = m_startTimeSam; ic < m_endTimeSam; ic++)
// 	{
// 		czerolag = m_pProd[ic] * m_pScale[0];
// 		for (int iw = 1; iw < m_nwhalf; iw++)
// 		{
// 			ipl = ic - iw;
// 			ipr = ic + iw;
// 			if (ipl >= 0 && ipl < m_nt)
// 				prodl = m_pProd[ipl];
// 			else
// 				prodl = 0.;
// 			if (ipr >= 0 && ipr < m_nt)
// 				prodr = m_pProd[ipr];
// 			else
// 				prodr = 0.;
// 			czerolag += m_pScale[iw] * (prodl + prodr);
// 		}
// 		czerolag = sqrt(czerolag);
// 		c[ic] = (czerolag == 0) ? 0. : (1. / czerolag);
// 	}
// 	for (int ic = m_endTimeSam; ic < m_nt; ic++)
// 		c[ic] = 0.;
// 
// 	return;
// }



void CKELocalCrossCorr::NormalizeOneLag(int ilag, float *c)
{
	int icmin = MAX(0, -ilag);
	int icmax = MIN(m_nt, m_nt - ilag);
	for (int ip = 0; ip < icmin; ip++)
	{
		c[ip] *= m_pSQRTAA[ip] * m_pSQRTBB[0];
	}
	for (int ip = icmin; ip < icmax; ip++)
	{
		c[ip] *= m_pSQRTAA[ip] * m_pSQRTBB[ip + ilag];
	}
	for (int ip = icmax; ip < m_nt; ip++)
	{
		c[ip] *= m_pSQRTAA[ip] * m_pSQRTBB[m_nt - 1];
	}
	return;
}

void CKELocalCrossCorr::FindShifts(float threshcc)
{
	CrossCorrLocGaussNorm();
	int ilagtop;
	float cctop;
	float cctmp;
	int ilagindex;
	float p0, p1, p2;
	for (int it = 0; it < m_nt; it++)
	{
		ilagtop = -1000000;
		cctop = -1000000;
		for (int ilag = m_lagmin; ilag <= m_lagmax; ilag++)
		{
			ilagindex = (ilag - m_lagmin)*m_nt + it;
			cctmp = abs(m_pAB[ilagindex]);
			if (cctmp >= threshcc && cctmp >= cctop)
			{
				if (cctmp == cctop && abs(ilag) > abs(ilagtop))
				{
					continue;
				}
				else
				{
					ilagtop = ilag;
					cctop = m_pAB[ilagindex];
				}
			}
		}
		//parabolic ...
		m_pShift[it] = ilagtop;
	}
	return;
}

void CKELocalCrossCorr::getNormalizedCorrelation(float *lcc)
{
	CrossCorrLocGaussNorm();
	for (int ilag = 0; ilag < m_nlag; ilag++)
	{
		for (int it = 0; it < m_nt; it++)
		{
			lcc[ilag*m_nt + it] = m_pAB[ilag*m_nt + it];
		}
	}
}

void CKELocalCrossCorr::getShifts(float *shift)
{
	FindShifts(m_threshcc);
	for (int it = 0; it < m_startTimeSam; it++)
		shift[it] = 0.;
	for (int it = m_startTimeSam; it < m_endTimeSam; it++)
	{
		shift[it] = m_pShift[it];
	}
	for (int it = m_endTimeSam; it < m_nt; it++)
		shift[it] = 0.;
}