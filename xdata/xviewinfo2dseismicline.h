#ifndef XVIEWINFO2DSEISMICSECTION_H
#define XVIEWINFO2DSEISMICSECTION_H

#include "xviewinfoobject.h"
#include "xdata_global.h"

/*!
 *	@brief	data structure for view info of 2D seismic section
 *	@author	pezy
 *	@date	2015-09-23
 *	@see	CX2DSeismicLine
 */

class XDATA_EXPORT CXViewInfo2DSeismicLine : public CXViewInfoObject
{
public:
	CXViewInfo2DSeismicLine();
	~CXViewInfo2DSeismicLine() {}

	X_PROPERTY(bool, DisplayNameOnTop)
	X_PROPERTY(bool, DisplayNameOnBottom)
	X_PROPERTY(QColor, NameColor)
	X_PROPERTY(int, NameSize)
	X_PROPERTY(QString, NameFont)

	X_PROPERTY(QColor, LineColor)
	X_PROPERTY(int, LineWidth)

	virtual void SetViewObjectID(const QUuid& objID) override;
	virtual bool ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo) override;
};

#endif // KEVIEWINFO2DSEISMICSECTION_H
