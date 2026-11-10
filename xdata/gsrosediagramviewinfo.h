#ifndef GSROSEDIAGRAMVIEWINFO_H
#define GSROSEDIAGRAMVIEWINFO_H

#include "xviewinfoobject.h"
#include "xdata_global.h"

class XDATA_EXPORT GSRoseDiagramViewInfo : public CXViewInfoObject
{
public:
    GSRoseDiagramViewInfo();
    ~GSRoseDiagramViewInfo();

	X_PROPERTY(int, Size)
	X_PROPERTY(int, NumPetal)

	X_PROPERTY(int, RoseOpacity)
	X_PROPERTY(int, RangeOpacity)
    X_PROPERTY(QColor, PetalColor)
    X_PROPERTY(QColor, LineColor)
    X_PROPERTY(QColor, BGColor)
    X_PROPERTY(QColor, RangeColor)

	X_PROPERTY(int, RosePos)
	X_PROPERTY(bool, ShowRange)
};

#endif