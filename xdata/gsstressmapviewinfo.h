#ifndef GSSTRESSMAPVIEWINFO_H
#define GSSTRESSMAPVIEWINFO_H

#include "xviewinfoobject.h"
#include "xdata_global.h"

class XDATA_EXPORT GSStressMapViewInfo : public CXViewInfoObject
{
public:
    GSStressMapViewInfo();
    ~GSStressMapViewInfo();

	X_PROPERTY(bool, ShowStressStates)
	X_PROPERTY(bool, ShowAsTrafficLight)
	X_PROPERTY(double, StressStatesOpacity)

    X_PROPERTY(QColor, StresslinesColor)
    X_PROPERTY(int, StresslinesLength)
    X_PROPERTY(int, StresslinesWidth)
	X_PROPERTY(int, StresslinesStep)
	X_PROPERTY(bool, StresslineAll)

	X_PROPERTY(bool, ShowCapsule)
	X_PROPERTY(double, CapsuleOpacity)
	X_PROPERTY(QColor, CapsuleLineColor)

	X_PROPERTY(bool, ShowAnticline)
	X_PROPERTY(QColor, AnticlineColor)
	X_PROPERTY(int, AnticlineWidth)
	X_PROPERTY(QColor, AnticlineMarkerLineColor)
	X_PROPERTY(int, AnticlineMarkerSize)
	X_PROPERTY(int, AnticlineStressArrowSize)

	X_PROPERTY(bool, ShowFaultPolygon)
	X_PROPERTY(QColor, FPLineColor)
    X_PROPERTY(int, FPLineWidth)
	X_PROPERTY(QColor, FPFillColor)
};

#endif // GSSTRESSMAPVIEWINFO_H
