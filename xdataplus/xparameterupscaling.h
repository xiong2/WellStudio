#ifndef XPARAMETERUPSCALING_H
#define XPARAMETERUPSCALING_H

#include <vector>
#include <QStringList>
#include "xdataplus_global.h"
#include "xbaseparameter.h"

/**
* @class CXParameterUpscaling provided in the file "keparameterupscaling.h"
* @brief The class provides parameters for calculating upscaling
* @author Yong Shu
* @date 11/23/2015
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXParameterUpscaling : public CXBaseParameter
{
public:
	enum EAverageMethod
	{
		eArithemtic = 0,
		eGeometric,
		eRMS,
		eMedian
	};

public:
	///@brief Default Constructor
	CXParameterUpscaling();

	///@brief Destructor
	virtual ~CXParameterUpscaling() {}

public:
	///@brief Set and get well info
	X_PROPERTY(std::vector<QUuid>, VecAliasID);

	X_PROPERTY(int, AverageMethod);

};

#endif // KEPARAMETERUPSCALING_H
