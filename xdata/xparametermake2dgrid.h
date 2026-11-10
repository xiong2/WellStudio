#ifndef XPARAMETERMAKE2DGRID_H
#define XPARAMETERMAKE2DGRID_H

#include "xbaseparameter.h"
#include "xdata_global.h"

/**
* @class CXParameterMake2DGrid in the file "rlparametermake2dgrid.h"
* @brief The class is a base class for all parameters
* 
* @author Yong Shu 
* @date 5/16/2014
* @see 
*/
class XDATA_EXPORT CXParameterMake2DGrid : public CXBaseParameter
{
public:
	enum EAlgorithm
	{
		eInverseDistance = 0,
		eKriging
	};

	enum EVariogram
	{
		Spherical = 0,
		Exponential,
		Gaussian
	};
public:
	///@brief Default Constructor
	CXParameterMake2DGrid();   

	///@brief Destructor
	virtual ~CXParameterMake2DGrid() {}
public:
	///@brief Set and get the horizon names (or formation name for welltops)
	X_PROPERTY(QStringList, HorizonNameList);

	///@brief Set and get the rock names
	X_PROPERTY(QStringList, RockNameList);

	///@brief Set and get nI and nJ 
	///@brief define SetNI() and GetNJ()
	X_PROPERTY(int, NI);
	X_PROPERTY(int, NJ);

	///@brief three points in XY coordinates and in index coordinates
	X_PROPERTY(std::vector<int>, VecIIndex);
	X_PROPERTY(std::vector<int>, VecJIndex);
	X_PROPERTY(std::vector<double>, VecXCoords);
	X_PROPERTY(std::vector<double>, VecYCoords);

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

	///@brief Well ID
	X_PROPERTY(QUuid, WellID);

	
};

#endif // RLPARAMETERMAKE2DGRID_H
