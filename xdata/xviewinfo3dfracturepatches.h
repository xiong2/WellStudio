#pragma once
#include "xviewinfoobject.h"
#include "xdata_global.h"

class XDATA_EXPORT CXViewInfo3DFracturePatches : public CXViewInfoObject
{
public:
	CXViewInfo3DFracturePatches();
	~CXViewInfo3DFracturePatches() {}

	X_PROPERTY(bool, DisplayPoint);
	X_PROPERTY(bool, DisplayLine);
	X_PROPERTY(bool, DisplayPlane);

	///@brief Point
	X_PROPERTY(QColor, PointColor);
	X_PROPERTY(int, PointSize);

	///@brief Line
	X_PROPERTY(QColor, LineColor);
	X_PROPERTY(int, LineWidth);
	X_PROPERTY(int, LineColorMode);
	///@brief Plane
	X_PROPERTY(QColor, PlaneColor);
	X_PROPERTY(float, Opacity);

	///@breif Set object ID
	virtual void SetViewObjectID(const QUuid& objID);

	///@brief Apply some of other view info into current one
	virtual bool ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo);
};
