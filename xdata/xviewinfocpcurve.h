#ifndef _CXCPCURVEVIEWINFO_H__
#define _CXCPCURVEVIEWINFO_H__

#include <QString>
#include "xdata_global.h"
#include "xviewinfoobject.h"

class XDATA_EXPORT CXViewInfoCPCurve : public CXViewInfoObject
{
public:
	CXViewInfoCPCurve();

	X_PROPERTY(int, PointSize);

	X_PROPERTY(int, PointType);

	X_PROPERTY(QColor, FillColor);
};

#endif