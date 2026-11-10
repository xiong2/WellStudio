#ifndef XCURVEFITTING_H
#define XCURVEFITTING_H

/**
 * @class CXCurveFitting in the file "xscurvefitting.h".
 * @brief The file defines some common curve fitting methods.
 * 
 * @author Yong Shu 
 * @date 2/22/2016
 * @see 
 * @bug	No Known bugs so far
 */

template<typename T>
class CXCurveFitting
{
public:
	/**
	* @brief Parabola fitting using three different points.
	* @brief Equation: Y = a*X*X + b*X + c
	* @param[in] pXdata : abscissa of three points.
	* @param[in] pYdata : ordinate of three points.
	* @param[out] a : see equation of three points.
	* @param[out] b : see equation 
	* @param[out] c : see equation 
	* @return true: succeed, false: if abscissa of any two points are same
	*/
	static bool ParabolaFitting(const T* pX, const T* pY, T &a, T &b, T &c)
	{
		T x1 = pX[0], x2 = pX[1], x3 = pX[2];
		T y1 = pY[0], y2 = pY[1], y3 = pY[2];
		T f1 = x3 - x2, f2 = x3 - x1, f3 = x2 - x1;

		if (qAbs(f1) < M_FEPS || qAbs(f2) < M_FEPS || qAbs(f3) < M_FEPS)
			return false;

		a = (f1*y1 - f2*y2 + f3*y3)/(f1*f2*f3);

		b = ( y2 - y1 - a*f3*(x2+x1) )/f3;

		c = y1 - x1*(a*x1 + b);

		return true;
	}

	/**
	* @brief Linear fitting using two different points.
	* @brief Equation: Y = a*X+b
	* @param[in] pXdata : abscissa of two points.
	* @param[in] pYdata : ordinate of two points.
	* @param[out] a : see equation of two points.
	* @param[out] b : see equation 
	* @return true: succeed, false: if abscissa of two points are same
	*/
	static bool LinearFitting(const T* pX, const T* pY, T &a, T &b)
	{	
		T dx = pX[1] - pX[0];
		T dy = pY[1] - pY[0];

		if (qAbs(dx) < M_FEPS)
			return false;

		a = dy/dx;
		b = pY[0] - a*pX[0];
		return true;
	}


	/**
	* @brief Get peak, trough or root after parabola fitting using three different points.
	* @param[in] pX : abscissa of three points.
	* @param[in] pY : ordinate of three points.
	* @param[in] nType : 0: Peak; 1: Trough; 2: zero crossA; 3: zero crossB
	* @param[out[ zValue : interpolation value
	* @return true: succeed, false: if no required point exists
	*/
	static bool ParabolicInterpolation(const T* pX, const T* pY, const int nType, T& zValue);
	
};

template<typename T>
bool CXCurveFitting<T>::ParabolicInterpolation(const T* pX, const T* pY, const int nType, T& zValue)
{
	T a, b, c;
	
	if (!CXCurveFitting<T>::ParabolaFitting(pX, pY, a, b, c))
		return false;

	if (qAbs(a) < M_FEPS)
		return false;

	T tMax = qMax(qMax(pX[0], pX[1]), pX[2]);
	T tMin = qMin(qMin(pX[0], pX[1]), pX[2]);

	switch(nType)
	{
	case 0:				///peak
	case 1:				///though
		{	
			zValue = -1.0*b/(2*a);
			if (zValue > tMax || zValue < tMin)
				return false;
			break;
		}
	case 2:			///zero crossa
	case 3:			///zero crossb
		{
			T delta =  b*b-4*a*c;			
			if (delta < 0)
				return false;

			T deltaRSQR = sqrt(delta);

			zValue = (-b + deltaRSQR)/(2*a);
			if (zValue > tMax || zValue < tMin)
			{
				zValue = (-b - deltaRSQR)/(2*a);
				if (zValue > tMax || zValue < tMin)
					return false;
			}
			break;
		}
	default:
		return false;
	}
    return true;
}

#endif // KECURVEFITTING_H