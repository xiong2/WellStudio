#ifndef CXParameterMakeRevInterpolation_H_H
#define CXParameterMakeRevInterpolation_H_H
#include "xbaseparameter.h"
#include "xdata_global.h"
class XDATA_EXPORT CXParameterMakeRevInterpolation:public CXBaseParameter
{

public:
	enum EAlgorithm
	{
		eSimpleKriging=0,
		eOrdinaryKriging,
		eGeneralKriging
	};

	enum EVariogram
	{
		Spherical = 0,
		Exponential,
		Gaussian
	};
public:	
	CXParameterMakeRevInterpolation();
	~CXParameterMakeRevInterpolation();

	///@brief Define Set and get algorithm
	X_PROPERTY(int, AlgorithmType);

	///@brief Inverse distance to a power
	X_PROPERTY(double, Power);
	X_PROPERTY(double, Radius);
	X_PROPERTY(int, MaxSampleNum);

	///@brief Kriging
	X_PROPERTY(int, VariogramType);
	X_PROPERTY(double, Sill);
	X_PROPERTY(double, Nugget);
	X_PROPERTY(double, MaxRange);
	X_PROPERTY(double, MinRange);
	X_PROPERTY(double, Azimuth);

	X_PROPERTY(double, A);
	X_PROPERTY(double, x);
	X_PROPERTY(double, y);
	X_PROPERTY(double, z);


};
#endif