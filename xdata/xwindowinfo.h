#ifndef XWINDOWINFO_H
#define XWINDOWINFO_H

#include "xbaseparameter.h"
#include <QColor>

/*!
 *	@brief	Generate property of windows viewinfo.
 *	@author	pezy
 *	@date	2016-06-16
 *	@see
 */

class CXWindowInfo : public CXBaseParameter
{
public:
	CXWindowInfo();
	~CXWindowInfo();

	// Current scene states
	X_PROPERTY(QColor, BackgroundColor)

	// Colorbar
	X_PROPERTY(bool, ColorbarVisible)

	X_PROPERTY(bool, ColorbarTitleVisible)
	X_PROPERTY(QColor, ColorbarTitleColor)
	X_PROPERTY(int, ColorbarTitleSize)
	X_PROPERTY(QString, ColorbarTitleFont)

	X_PROPERTY(QColor, ColorbarTickColor)
	X_PROPERTY(int, ColorbarTickSize)

	X_PROPERTY(QColor, ColorbarMarkColor)
	X_PROPERTY(int, ColorbarMarkSize)
	X_PROPERTY(QString, ColorbarMarkFont)

	X_PROPERTY(int, ColorbarPosition)

	// Coordinate axis
	X_PROPERTY(bool, CoordVisible)
	X_PROPERTY(QColor, CoordColor)
	X_PROPERTY(int, CoordLineWidth)
	X_PROPERTY(int, CoordTickLength)

	X_PROPERTY(int, CoordMarkSize)
	X_PROPERTY(QString, CoordMarkFont)

	X_PROPERTY(bool, CoordLabelVisible)
	X_PROPERTY(int, CoordLabelSize)
	X_PROPERTY(QString, CoordLabelFont)
	X_PROPERTY(QString, CoordLabelX)
	X_PROPERTY(QString, CoordLabelY)

	X_PROPERTY(bool, CoordGridVisible)
	X_PROPERTY(QColor, CoordGridColor)
	X_PROPERTY(int, CoordGridLineWidth)

	// Compass
	X_PROPERTY(bool, CompassVisible)
	X_PROPERTY(QColor, CompassTopColor)
	X_PROPERTY(QColor, CompassBottomColor)
	X_PROPERTY(QColor, CompassFrameColor)
	X_PROPERTY(int, CompassPosition)
};

#endif // KEWINDOWINFO_H
