#ifndef XVIEWINFO3DFAULTSTICKS_H
#define XVIEWINFO3DFAULTSTICKS_H

#include "xviewinfoobject.h"
#include "xdata_global.h"

///@brief	The class provides data structure for view info of fault sticks
///@author	Yong Shu
///@date	Jun. 12th, 2014
///@see	
class XDATA_EXPORT CXViewInfo3DFaultSticks : public CXViewInfoObject
{
public:
	CXViewInfo3DFaultSticks();
	~CXViewInfo3DFaultSticks() {}

	X_PROPERTY(bool, DisplayPoint);
	X_PROPERTY(bool, DisplayLine);
	X_PROPERTY(bool, DisplayPlane);

	///@brief Point
	X_PROPERTY(QColor, PointColor);
	X_PROPERTY(int, PointSize);

	///@brief Line
	X_PROPERTY(QColor, LineColor);
	X_PROPERTY(int, LineWidth);	
	X_PROPERTY(int ,LineColorMode);
	///@brief Plane
	X_PROPERTY(QColor, PlaneColor);
	X_PROPERTY(float, Opacity);	

	///@Ann
	X_PROPERTY(bool, AnnTop);
	X_PROPERTY(bool, AnnBottom);
	X_PROPERTY(QColor, AnnColor);
	X_PROPERTY(QColor, AnnBackBgrColor);
	X_PROPERTY(int, AnnColorType);

	///@breif Set object ID
	virtual void SetViewObjectID(const QUuid& objID);

	///@brief Apply some of other view info into current one
    virtual bool ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo);
};

#endif // RLVIEWINFO3DFAULTSTICKS_H
