#ifndef _CXVIEWINFOCPPOLYGON_H__
#define _CXVIEWINFOCPPOLYGON_H__

#include "xdata_global.h"
#include "xviewinfoobject.h"

class XDATA_EXPORT CXViewInfoCPPolygon : public CXViewInfoObject
{
public:
	CXViewInfoCPPolygon();
	CXViewInfoCPPolygon(const CXViewInfoCPPolygon&);

	///@brief Copy assignment operator
	CXViewInfoCPPolygon& operator=(const CXViewInfoCPPolygon&);

	X_PROPERTY(QColor, Color);

	X_PROPERTY(int, LineWidth);

	X_PROPERTY(float, Alpha);
};

#endif