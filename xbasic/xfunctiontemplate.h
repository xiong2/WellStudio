#ifndef XFUNCTIONTEMPLATE_H
#define XFUNCTIONTEMPLATE_H

#include <cmath>
#include "xmathmacro.h"

template<typename T>
inline T SQR(T a) {return  a*a;}

template<typename T>
inline T Cube(T a) {return a*a*a;}

template<typename T>
inline T CubicRoot(T a) {return pow(static_cast<double>(a), 1.0/3.0);}

template<typename T>
inline T Sign(T a) {return (a > 0 ? 1 : (a < 0 ? -1 : 0));}

template <typename T>
inline bool IsBound(const T& val, const T& min, const T& max)
{ return (min <= val && val <= max);}

template <typename T>
inline double DotProduct(int n, T* p1, T* p2)
{
	double value(0);
	for (int i = 0; i < n; ++i)
		value += p1[i] * p2[i];
	return value;
}

template <typename T>
inline T sinc(T x)
{
	if (x == 0)
		return 1;
	else
	{
		return sin(M_PI*x) / (M_PI*x);
	}
}

template <typename T1, typename T2>
void ForceConverter(int n, T1* pFrom, T2* pTo)
{
	for (int i = 0; i < n; ++i)
		pTo[i] = (T2)pFrom[i];
}

inline bool IsEqualDouble(double d1, double d2, double tolerance)
{
	return fabs(d2 - d1) < tolerance * (std::max(fabs(d1), 1.0) + std::max(fabs(d2), 1.0));
}


#endif // RLFUNCTIONTEMPLATE_H