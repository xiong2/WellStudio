#ifndef XPARAMETERFRACTUREATTRIBUTE_H
#define XPARAMETERFRACTUREATTRIBUTE_H

#include <QString>
#include "xdataplus_global.h"
#include "xparameterinversion.h"
#include "xdef.h"	

using std::vector;
/**
* @class CXParameterFractureAttribute provided in the file "keparameterfractureattribute.h"
* @brief The class provides parameters to calculate fracture attributes from the VpVs volume
* @author Yong Shu
* @date 12/28/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXParameterFractureAttribute : public CXParameterInversion
{
public:
	///@brief Default Constructor
	CXParameterFractureAttribute();

	///@brief Destructor
	virtual ~CXParameterFractureAttribute() {}

public:
	X_PROPERTY(QUuid, AzimuthDVID)
	X_PROPERTY(QString, AzimuthDVName)
	
	X_PROPERTY(int, MinimumFold)

	X_PROPERTY(QUuid, VpDVID)
	X_PROPERTY(QUuid, VsDVID)
	X_PROPERTY(QUuid, EpsilonDVID)
	X_PROPERTY(QUuid, DeltaDVID)
	X_PROPERTY(QUuid, GammaDVID)
	X_PROPERTY(QUuid, AziSymDVID)

};


#endif // KEPARAMETERFRACTUREATTRIBUTE_H
