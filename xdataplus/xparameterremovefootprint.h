#pragma once

#include <QString>
#include "xdataplus_global.h"
#include "xbaseparameter.h"
#include "xdef.h"	

using std::vector;
/**
* @class CXParameterRemoveFootprint provided in the file "xparameterremovefootprint.h"
* @brief The class provides parameters for removing footprint
* @author Pr
* @date 5/17/2025
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXParameterRemoveFootprint : public CXBaseParameter
{
public:
	///@brief Default Constructor
	CXParameterRemoveFootprint();

	///@brief Destructor
	virtual ~CXParameterRemoveFootprint() {}

public:
	///@brief poststack seismic data
	X_PROPERTY(float, Threshold);
	X_PROPERTY(QString, Wavelet);

	X_PROPERTY(int, Level);
	X_PROPERTY(int, Window);

	X_PROPERTY(QString, Direction);

};
