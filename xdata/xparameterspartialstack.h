#ifndef _CXPARAMETERSPARTIALSTACK_H__
#define _CXPARAMETERSPARTIALSTACK_H__

#include <quuid.h>
#include "xbaseparameter.h"
#include "xdata_global.h"

///@brief	The class represents parameters used to do a partial stack.
///@author	Xiong Xiong
///@date	Jul, 2016
class XDATA_EXPORT CXParametersPartialStack :public CXBaseParameter
{
public:
	CXParametersPartialStack();
	~CXParametersPartialStack(){}

	X_PROPERTY(QString, OutputDVName);

	///	ID of original data volume.
	X_PROPERTY(QUuid, InputDVID);

	///	Parameters of dimension.
	X_PROPERTY(int, StartInline);
	X_PROPERTY(int, EndInline);
	X_PROPERTY(int, StartXline);
	X_PROPERTY(int, EndXline);

	///	Parameters of Z dimension.
	X_PROPERTY(int, StartZ);
	X_PROPERTY(int, EndZ);
	X_PROPERTY(int, ZInterval);

	///	Rolling window size.
	X_PROPERTY(int, RollingInlines);
	X_PROPERTY(int, RollingXlines);

	///	Sort by offset first or azimuth first.
	X_PROPERTY(bool, OffsetFirst);

	///	Gather parameters.
	X_PROPERTY(int, StackOption);						//	0 both;	1 offset;	2 azimuth.	
	X_PROPERTY(std::vector<int>, VectorOffsets);		//	vector of start offset, end offset, output offset.
	X_PROPERTY(std::vector<int>, VectorAzimuth);		//	vector of start azimuth, end azimnuth, output azimuth.
};

#endif