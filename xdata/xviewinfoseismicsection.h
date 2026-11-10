#ifndef XVIEWINFOSEISMICSECTION_H
#define XVIEWINFOSEISMICSECTION_H

/*!
 *	@brief	data structure for view info of seismic section
 *	@author	pezy
 *	@date	2016-06-21
 *	@see	CXSeismicDataVolume
 */

#include "xviewinfoobject.h"
#include "xdata_global.h"

class XDATA_EXPORT CXViewInfoSeismicSection : public CXViewInfoObject
{
public:
	CXViewInfoSeismicSection();
	~CXViewInfoSeismicSection();

	//! @brief	basemap window:
	X_PROPERTY(bool, BMLineUseObjectColor)
	X_PROPERTY(QColor, BMLineColor)
	X_PROPERTY(int, BMLineWidth)

	X_PROPERTY(QColor, BMPickedLineColor)
	X_PROPERTY(int, BMPickedLineWidth)

	//! @brief	3D window;
	X_PROPERTY(QColor, 3DPickedFrameColor)
	X_PROPERTY(int, 3DPickedFrameWidth)

	virtual void SetViewObjectID(const QUuid& objID) override;
	
};

#endif // KEVIEWINFOSEISMICSECTION_H
