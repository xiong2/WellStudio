#ifndef XPARAMETERSEISMICFILTERING_H
#define XPARAMETERSEISMICFILTERING_H

#include <vector>
#include <QStringList>
#include "xdataplus_global.h"
#include "xbaseparameter.h"

/**
* @class CXParameterSeismicFiltering provided in the file "keparameterseismicfiltering.h"
* @brief The class provides parameters for seismic filtering
* @author Yong Shu
* @date 5/18/2016
*
*/

class XDATAPLUS_EXPORT CXParameterSeismicFiltering : public CXBaseParameter
{
public:
	enum EFilterType
	{
		eLowCut=0,
		eBandPass,
		eHighCut
	};
public:
	///@brief Default Constructor
	CXParameterSeismicFiltering();

	///@brief Destructor
	virtual ~CXParameterSeismicFiltering() {}

public:
	///@brief Set and get well info
	X_PROPERTY(int, FilterType);

	///@brief sampling rate in terms of ms
	X_PROPERTY(double, SamplingRate);

	X_PROPERTY(double, LowCutFreq);
	X_PROPERTY(double, LowCutOverlapped);

	X_PROPERTY(double, HighCutFreq);
	X_PROPERTY(double, HighCutOverlapped);

	X_PROPERTY(bool, TreatZeroInvalid);

public:
	QString GetFilteringName();

};


#endif // KEPARAMETERSEISMICFILTERING_H
