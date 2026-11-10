#ifndef XVIEWINFO2DPOLYGON_H
#define XVIEWINFO2DPOLYGON_H

/*!
 *	@brief	data structure for view info of 2D Polygon
 *	@author	pezy
 *	@date	2016-08-19
 *	@see	CX2DPolygon
 */

#include "xviewinfoobject.h"
#include "xdata_global.h"

class XDATA_EXPORT CXViewInfo2DPolygon : public CXViewInfoObject
{
public:
	CXViewInfo2DPolygon();
	~CXViewInfo2DPolygon();

	//! @brief	basemap window
	X_PROPERTY(bool, BMLineUseObjectColor)
	X_PROPERTY(QColor, BMPickedColor)
	X_PROPERTY(int, BMPickedWidth)
	X_PROPERTY(QColor, BMLineColor)
	X_PROPERTY(int, BMLineWidth)
	X_PROPERTY(bool, BMPivotUseObjectColor)
	X_PROPERTY(QColor, BMPivotColor)
	X_PROPERTY(int, BMPivotSize)
	X_PROPERTY(bool, BMIsFill)
	X_PROPERTY(bool, BMFillUseObjectColor)
	X_PROPERTY(QColor, BMFillColor)

	void SetViewObjectID(const QUuid& objID) override;
	bool ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo) override;
};

#endif // KEVIEWINFO2DPOLYGON_H
