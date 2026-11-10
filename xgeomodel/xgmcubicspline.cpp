#include "xgmcubicspline.h"
#include <cassert>

CXGMCubicSpline::CXGMCubicSpline(int nSize, const double* pX, const double* pY, double y21, double y2n)
:m_nSize(nSize), m_pX(pX), m_pY(pY), m_Y21(y21), m_Y2n(y2n)
{
	assert(m_nSize >= 2);

	m_pY2 = NULL;
	m_pU = NULL;	
}

CXGMCubicSpline::~CXGMCubicSpline()
{
	if (m_pY2) {delete []m_pY2; m_pY2 = NULL;}
	if (m_pU)  {delete []m_pU; m_pU = NULL;}
}

void CXGMCubicSpline::_SetY2()
{
	if (m_nSize < 2 || m_pX == NULL || m_pY == NULL)
		return;

	try
	{
		m_pY2 = new double [m_nSize];
		m_pU = new double [m_nSize-1];
	}
	catch(...)
	{
		return;
	}

	double p, qn, sig, un;
	if (m_Y21 > 0.99e99)
	{
		m_pY2[0] = m_pU[0] = 0.;
	}
	else
	{
		m_pY2[0] = -0.5;
		m_pU[0] = (3.0/(m_pX[1] - m_pX[0]))*((m_pY[1] - m_pY[0])/(m_pX[1] - m_pX[0]) - m_Y21);
	}

	for (int i=1; i<m_nSize-1; ++i)
	{
		sig = (m_pX[i] - m_pX[i-1])/(m_pX[i+1] - m_pX[i-1]);
		p = sig*m_pY2[i-1] + 2.0;
		m_pY2[i] = (sig - 1.0)/p;

		m_pU[i] = (m_pY[i+1] - m_pY[i])/(m_pX[i+1] - m_pX[i]) - (m_pY[i] - m_pY[i-1])/(m_pX[i] - m_pX[i-1]);
		m_pU[i] = (6.0*m_pU[i]/(m_pX[i+1] - m_pX[i-1]) - sig*m_pU[i-1])/p;
	}

	if (m_Y2n > 0.99e99)
	{
		qn = un = 0.;
	}
	else
	{
		qn = 0.5;
		un = (3.0/(m_pX[m_nSize-1] - m_pX[m_nSize-2]))*(m_Y2n - (m_pY[m_nSize-1] - m_pY[m_nSize-2])/(m_pX[m_nSize-1] - m_pX[m_nSize-2]));
	}

	m_pY2[m_nSize-1] = (un - qn*m_pU[m_nSize-2])/(qn*m_pY2[m_nSize-2] + 1.0);

	for (int k=m_nSize-2; k>=0; --k)
	{
		m_pY2[k] = m_pY2[k]*m_pY2[k+1] + m_pU[k];
	}

	if (m_pU)
	{
		delete []m_pU;
		m_pU = NULL;
	}
}

double CXGMCubicSpline::GetY(const double x)
{
	if (m_pY2 == NULL)
		_SetY2();

	if (x <= m_pX[0])
	{
		return m_pY[0];
	}
	else if ( x >= m_pX[m_nSize-1])
	{
		return m_pY[m_nSize-1];
	}

	// Get an lower and higher indices
	int il, ih, i;
	il = 0;
	ih = m_nSize-1;

	while(ih - il > 1)
	{
		i = (il + ih) >> 1;

		if (x > m_pX[i])
			il = i;
		else
			ih = i;
	}

	// interpolation
	double a, b, h, y;

	h = m_pX[ih] - m_pX[il];
	a = (m_pX[ih] - x)/h;
	b = 1 - a;

	y = a*m_pY[il] + b*m_pY[ih] + ((a*a*a - a)*m_pY2[il] + (b*b*b-b)*m_pY2[ih])*(h*h)/6.;

	return y;
}

