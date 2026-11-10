#ifndef _CXViewInfoLPWellTops_H__
#define _CXViewInfoLPWellTops_H__

#include "xdata_global.h"
#include "xviewinfoobject.h"

class XDATA_EXPORT CXViewInfoLPWellTops : public CXViewInfoObject
{
public:
	CXViewInfoLPWellTops();

	X_PROPERTY(bool, Connect);
	X_PROPERTY(bool, ShowNameOnLeft);
	X_PROPERTY(bool, ShowNameOnRight);
	X_PROPERTY(int, LineWidth);
	X_PROPERTY(int, LineStyle);
};

#endif