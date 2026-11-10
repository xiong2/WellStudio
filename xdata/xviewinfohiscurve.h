#ifndef _CXHISCURVEVIEWINFO_H__
#define _CXHISCURVEVIEWINFO_H__

#include "xdata_global.h"
#include "xviewinfoobject.h"

class XDATA_EXPORT CXViewInfoHisCurve : public CXViewInfoObject
{
public:
	CXViewInfoHisCurve();

	X_PROPERTY(bool, Solid);

	X_PROPERTY(bool, CumLine);

	X_PROPERTY(int, LineWidth);

	X_PROPERTY(int, CumLineWidth);

	X_PROPERTY(int, CumLineStyle);

	X_PROPERTY(QColor, CumColor);

};

#endif