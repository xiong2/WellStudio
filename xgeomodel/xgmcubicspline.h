#ifndef XGMCUBICSPLINE_H__
#define XGMCUBICSPLINE_H__

#include "xgeomodel_global.h"

/**
 * @class CGmCubicSpline in the file "gmcubicspline.h"
 * @brief The class provides cubic spline interpolation
 * 
 * @author Yong Shu 
 * @date 1/8/2015
 * @see 
 * @bug	No Known bugs so far
 */

class XGEOMODEL_EXPORT CXGMCubicSpline
{
public:
	///@brief Constructor and destructor
	CXGMCubicSpline(int nSize, const double* pX, const double* pY, double y21 = 1.e99, double y2n = 1.e99);
	~CXGMCubicSpline();

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

#endif