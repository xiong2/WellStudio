#ifndef XWINDOWINFOBASEMAP_H
#define XWINDOWINFOBASEMAP_H

#include "xdata_global.h"
#include "xwindowinfo.h"
#include <QColor>

class XDATA_EXPORT CXWindowInfoBasemap : public CXWindowInfo
{
public:
	CXWindowInfoBasemap();
	~CXWindowInfoBasemap();

	// Current scene states
	X_PROPERTY(float, LastScale)
	X_PROPERTY(double, LastCenterOffsetX)
	X_PROPERTY(double, LastCenterOffsetY)

	// Scalebar
	X_PROPERTY(bool, ScalebarVisible)
	X_PROPERTY(int, ScalebarPosition)
	X_PROPERTY(QColor, ScaleMarkColor)
	X_PROPERTY(int, ScaleMarkSize)
	X_PROPERTY(QString, ScaleMarkFont)
	X_PROPERTY(QColor, ScaleFrameColor)
};

#endif // KEWINDOWINFOBASEMAP_H
