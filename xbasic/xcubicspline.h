#ifndef XCUBICSPLINE_H
#define XCUBICSPLINE_H

#include "xbasic_global.h"

class XBASIC_EXPORT CXCubicSpline
{
public:
	///@brief Constructor and destructor
	CXCubicSpline(int nSize, const double* pX, const double* pY, double y21 = 1.e99, double y2n = 1.e99);
	~CXCubicSpline();

	///@brief Get Y value at the given X
	double GetY(const double x);

private:
	void _SetY2();

private:
	int m_nSize;
	const double* m_pX;
	const double* m_pY;

	double* m_pY2;
	double* m_pU;
	double m_Y21, m_Y2n;
};

#endif // KECUBICSPLINE_H
