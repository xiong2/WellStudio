#ifndef CXVIEWINFOTIMESLICE_H
#define CXVIEWINFOTIMESLICE_H

#include "xviewinfoseismicsection.h"
#include "xdata_global.h"

class XDATA_EXPORT CXViewInfoTimeSlice : public CXViewInfoSeismicSection
{
public:
	CXViewInfoTimeSlice(void);
	~CXViewInfoTimeSlice(void);

	// section window
	X_PROPERTY(QColor, LineColor)
	X_PROPERTY(int, LineStyle)
	X_PROPERTY(int, LineSize)

	// fracture feature
	X_PROPERTY(int, DisplayMode) // 0-seismic 1-fracture
	X_PROPERTY(bool, SeismicDisplay)
	X_PROPERTY(QUuid, FracAzimuth)
	X_PROPERTY(QUuid, FracDensity)
	X_PROPERTY(QColor, FracColor)
	X_PROPERTY(int, FracDX)
	X_PROPERTY(int, FracDY)
	X_PROPERTY(float, FracScale)
	X_PROPERTY(float, FracMinThreshold)
	X_PROPERTY(float, FracMaxThreshold)
	X_PROPERTY(int, FracWidth)

	// 3-D window
	X_PROPERTY(int, FracHeight)
};

#endif // CXVIEWINFOTIMESLICE_H
