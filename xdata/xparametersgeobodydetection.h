#ifndef _CXPARAMETERSGEOBODYDETECTION_H__
#define _CXPARAMETERSGEOBODYDETECTION_H__

#include <quuid.h>
#include "xbaseparameter.h"
#include "xdata_global.h"

class CXSeismicDataVolume;

///@brief	The class represents parameters used to detect a geobody.
///@author	Xiong Xiong
///@date	Aug, 2015
class XDATA_EXPORT CXParametersGeobodyDetection :public CXBaseParameter
{
public:
	CXParametersGeobodyDetection();
	~CXParametersGeobodyDetection(){}

	X_PROPERTY(QString, GeobodyName);

	///	ID of original data volume.
	X_PROPERTY(QUuid, DVID);

	///	Parameters of plane dimension.
	X_PROPERTY(QUuid, BoundaryPolygonID);
	X_PROPERTY(int, StartInline);
	X_PROPERTY(int, EndInline);
	X_PROPERTY(int, StartXline);
	X_PROPERTY(int, EndXline);

	///	Parameters of Z dimension.
	X_PROPERTY(QUuid, IntervalID);
	X_PROPERTY(QUuid, TopSurfaceID);
	X_PROPERTY(QUuid, BottomSurfaceID);
	X_PROPERTY(float, StartZ);
	X_PROPERTY(float, EndZ);

	///	Detect threshold
	X_PROPERTY(float, LowThreshold);
	X_PROPERTY(float, HighThreshold);

	///	Minimal size of each geobody.
	X_PROPERTY(int, MiniSize);

	///	Face or corner way connectivity.
	X_PROPERTY(bool, FaceConnectivity);

	///	Generate mergerd geobody.
	X_PROPERTY(bool, Merge);
};

#endif