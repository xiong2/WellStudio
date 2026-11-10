#ifndef XPARAMETERMODELINTERSECTION_H
#define XPARAMETERMODELINTERSECTION_H

#include "xbaseparameter.h"
#include "xdata_global.h"

/**
* @class CXParameterModelIntersection in the file "rlparametermodelintersection.h"
* @brief The class is a base class for cutting the Grid Model
* 
* @author Pezy
* @date 3/11/2015
* @see 
*/

class XDATA_EXPORT CXParameterModelIntersection : public CXBaseParameter
{
public:
	CXParameterModelIntersection();
	virtual ~CXParameterModelIntersection() {}

	X_PROPERTY(std::vector<double>, VecX);
	X_PROPERTY(std::vector<double>, VecY);
};

#endif // RLPARAMETERMODELINTERSECTION_H