#ifndef XPARAMETERFRACTUREAVO_H
#define XPARAMETERFRACTUREAVO_H

#include <QString>
#include "xdataplus_global.h"
#include "xparameterinversion.h"
#include "xdef.h"	

using std::vector;
/**
* @class CXParameterFractureAVO provided in the file "keparameterfractureavo.h"
* @brief The class provides parameters for AVO fracture analysis
* @author Yong Shu
* @date 9/26/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXParameterFractureAVO : public CXParameterInversion
{
public:
	enum EMethodType
	{
		eRuger = 0,
		eFCs
	};
public:
	///@brief Default Constructor
	CXParameterFractureAVO();

	///@brief Destructor
	virtual ~CXParameterFractureAVO() {}

public:
	///@brief Calculation method
	X_PROPERTY(int, MethodType)

	X_PROPERTY(QUuid, AzimuthDVID)

	///@brief Individual poststack data volumes
	X_PROPERTY(vector<QUuid>, VecDVID)
	X_PROPERTY(QStringList, ListDVName)

	///@brief Azimuth
	X_PROPERTY(vector<float>, VecAzimuth)

	X_PROPERTY(int, Dx)
	X_PROPERTY(int, Dy)
	X_PROPERTY(int, MinimumFold)

	X_PROPERTY(int, IncidenceAngle)


};


#endif // KEPARAMETERFRACTUREAVO_H
