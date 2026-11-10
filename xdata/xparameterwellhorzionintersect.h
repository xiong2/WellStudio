#ifndef XPARAMETERWELLHORZIONINTERSECT_H
#define XPARAMETERWELLHORZIONINTERSECT_H


#include "xbaseparameter.h"
#include "xdata_global.h"

/**
* @class CXParameterWellHorzionIntersect in the file "rlparameterwellhorzionintersect.h"
* @brief The class is a base class for intersection between vertical well profile and 3-D horizon
* 
* @author Yong Shu 
* @date 6/9/2014
* @see 
*/
class XDATA_EXPORT CXParameterWellHorzionIntersect : public CXBaseParameter
{
public:
	///@brief Default Constructor
	CXParameterWellHorzionIntersect();   

	///@brief Destructor
	virtual ~CXParameterWellHorzionIntersect() {}

public:
	///@brief Set and get the horizon IDs and  names (or formation name for welltops)
	X_PROPERTY(std::vector<QUuid>, vecHorizonID);
	X_PROPERTY(QStringList, HorizonNameList);

	///@brief Set and get the rock names
	X_PROPERTY(QStringList, RockNameList);

	
};

#endif // RLPARAMETERWELLHORZIONINTERSECT_H
