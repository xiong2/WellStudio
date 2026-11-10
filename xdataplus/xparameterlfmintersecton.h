#ifndef XPARAMETERLFMINTERSECTON_H
#define XPARAMETERLFMINTERSECTON_H

#include <vector>
#include <QStringList>
#include "xdataplus_global.h"
#include "xbaseparameter.h"

/**
* @class CXParameterLFMIntersecton provided in the file "keparameterlfmintersecton.h"
* @brief The class provides parameters for calculating calculate intersection between well and Low frequency model
* @author Yong Shu
* @date 11/23/2015
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXParameterLFMIntersecton : public CXBaseParameter
{
public:
	///@brief Default Constructor
	CXParameterLFMIntersecton();

	///@brief Destructor
	virtual ~CXParameterLFMIntersecton() {}

public:
	///@brief Set and get well info
	X_PROPERTY(std::vector<QUuid>, VecWellID);

	X_PROPERTY(QStringList, ListWellName);

};


#endif // KEPARAMETERLFMINTERSECTON_H
