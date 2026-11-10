#ifndef XVIEWINFOLFMGEOMETRY_H
#define XVIEWINFOLFMGEOMETRY_H

#include "xviewinfoobject.h"
#include "xdataplus_global.h"

/*!
 *	@brief	View info of LFM Geometry
 *	@author	pezy
 *	@date	2015-12-02
 *	@see
 */

class XDATAPLUS_EXPORT CXViewInfoLFMGeometry : public CXViewInfoObject
{
public:
	CXViewInfoLFMGeometry();
	~CXViewInfoLFMGeometry();

	///@breif Set object ID
	virtual void SetViewObjectID(const QUuid& objID) override;

	X_PROPERTY(int, MinInline)
	X_PROPERTY(int, MaxInline)
	X_PROPERTY(int, MinCrossline)
	X_PROPERTY(int, MaxCrossline)

    X_PROPERTY(QColor, LineColor)
	X_PROPERTY(bool, DisplayTopAndBottomLine)
    X_PROPERTY(bool, DisplayHorizontalSideLine)
    X_PROPERTY(bool, DisplayVerticalSideLine)
    X_PROPERTY(int, LineSize)
    X_PROPERTY(int, VerticalLineSpacing)

	X_PROPERTY(std::vector<bool>, VecZoneDisplay)
	X_PROPERTY(std::vector<QRgb>, VecZoneColor)
	X_PROPERTY(std::vector<int>, VecZoneMinSlice)
	X_PROPERTY(std::vector<int>, VecZoneMaxSlice)
};

#endif // KEVIEWINFOLFMGEOMETRY_H
