#ifndef XPARAMETEREXTRACTHORIZONATT_H
#define XPARAMETEREXTRACTHORIZONATT_H

#include <vector>
#include <QString>
#include "xdataplus_global.h"
#include "xbaseparameter.h"
#include "xdef.h"	

using std::vector;

/**
* @class CXParameterExtractHorizonAtt provided in the file "keparameterextracthorizonatt.h"
* @brief The class provides parameters for extracting horizon attributes
* @author Yong Shu
* @date 9/29/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXParameterExtractHorizonAtt : public CXBaseParameter
{
public:
	///@brief Contact type
	enum EMethodType
	{
		eInstant,
		eArithMean
	};
public:
	///@brief Default Constructor
	CXParameterExtractHorizonAtt();

	///@brief Destructor
	virtual ~CXParameterExtractHorizonAtt() {}

public:
	///@brief Method
	X_PROPERTY(int, MethodType)

	///@brief Horizon ID
	X_PROPERTY(QUuid, HorizonID)

	///@brief Data volume IDs
	X_PROPERTY(vector<QUuid>, VecDVID)

	///@brief Top and Bottom shift
	X_PROPERTY(float, TopShift)
	X_PROPERTY(float, BottomShift)

public:
	QString GetPrefix();

};

#endif // KEPARAMETEREXTRACTHORIZONATT_H
