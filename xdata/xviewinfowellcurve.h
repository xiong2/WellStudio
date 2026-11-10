#ifndef XWELLCURVEVIEWINFO_H_
#define XWELLCURVEVIEWINFO_H_

#include <QString>

#include "xdata_global.h"
#include "xviewinfoobject.h"

class XDATA_EXPORT CXViewInfoWellCurve : public CXViewInfoObject
{
public:
	CXViewInfoWellCurve();
	~CXViewInfoWellCurve(void);

	void SetViewObjectID(const QUuid& objID) override;

	enum EDisplayMode3D {ECylinder, EFlat};
	enum EDisplayModeSection {ECurve, EVI};
public:
	// Common
	X_PROPERTY(bool, LineVisible)
	X_PROPERTY(int, LineWidth)
	X_PROPERTY(QColor, LineColor)
	X_PROPERTY(int, LineColorMode) // SelectColor = 0, ObjColor, colormap, DiscreteContour, Texture

	X_PROPERTY(bool, FillVisible)
	X_PROPERTY(int, FillWidth)
	X_PROPERTY(QColor, FillColor)
	X_PROPERTY(int, FillColorMode)

	// 3D Window
	X_PROPERTY(int, DisplayMode3D)

	// Section Window
	X_PROPERTY(int, VIWidth)
	X_PROPERTY(int, DisplayModeSection)
	X_PROPERTY(int, FilterType) // 0 - no filter, 1 - low pass, 2 - band pass, 3 - high pass.
	X_PROPERTY(double, FilterLowFreq)
	X_PROPERTY(double, FilterLowOverlap)
	X_PROPERTY(double, FilterHighFreq)
	X_PROPERTY(double, FilterHighOverlap)

    bool ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo);
};

#endif // !RLWELLCURVEVIEWINFO_H_
