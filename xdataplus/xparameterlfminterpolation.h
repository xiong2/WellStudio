#ifndef XPARAMETERLFMINTERPOLATION_H
#define XPARAMETERLFMINTERPOLATION_H

#include "xbaseparameter.h"
#include "xdataplus_global.h"

/**
* @class CXParameterLFMInterpolation in the file "keparameterlfminterpolation.h"
* @brief The class provides the parameter for LFM interpolation
*
* @author Yong Shu
* @date 11/26/2015
* @see
*/
class XDATAPLUS_EXPORT CXParameterLFMInterpolation : public CXBaseParameter
{
public:
	enum EAlgorithm
	{
		eInverseDistance = 0,
		eGLobalKriging,
		eOrdinaryKriging
	};

	enum EVariogram
	{		
		Exponential = 0,
		Gaussian,
		Spherical 
	};
public:
	///@brief Default Constructor
	CXParameterLFMInterpolation();

	///@brief Destructor
	virtual ~CXParameterLFMInterpolation() {}
public:
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


};


#endif // KEPARAMETERLFMINTERPOLATION_H
