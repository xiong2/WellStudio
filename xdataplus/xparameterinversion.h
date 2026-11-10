#ifndef XPARAMETERINVERSION_H
#define XPARAMETERINVERSION_H

#include <QString>
#include "xdataplus_global.h"
#include "xbaseparameter.h"

/**
* @class CXParameterInversion provided in the file "keparameterinversion.h"
* @brief The class provides base class for all inversion parameter
* @author Yong Shu
* @date 1/15/2016
*
* @see
* @bug No known bugs so far.
*/

class XDATAPLUS_EXPORT CXParameterInversion : public CXBaseParameter
{
public:
	///@brief Default Constructor
	CXParameterInversion();

	///@brief Destructor
	virtual ~CXParameterInversion() {}

public:
	///@brief Range
	X_PROPERTY(int, MinInlineNum);
	X_PROPERTY(int, MaxInlineNum);
	X_PROPERTY(int, InlineInc);
	X_PROPERTY(int, MinXlineNum);
	X_PROPERTY(int, MaxXlineNum);
	X_PROPERTY(int, XlineInc);

	X_PROPERTY(double, SamplingStart);
	X_PROPERTY(double, SamplingEnd);

	///@brief Sampling rate
	X_PROPERTY(double, SamplingRate);

	///@brief CPU number for computation
	X_PROPERTY(int, CPUNumber);

	X_PROPERTY(bool, ApplyFiltering);
	X_PROPERTY(double, LowCut);
	X_PROPERTY(double, LowOverlap);
	X_PROPERTY(double, HighCut);
	X_PROPERTY(double, HighOverlap);
};


#endif // KEPARAMETERINVERSION_H
