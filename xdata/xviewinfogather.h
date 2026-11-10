#pragma once
#include "xdata_global.h"
#include "xviewinfoobject.h"

class XDATA_EXPORT CXViewInfoGather : public CXViewInfoObject
{
public:
	CXViewInfoGather();

	X_PROPERTY(float, HScale);
	X_PROPERTY(float, VScale);
	X_PROPERTY(float, Excusion);

	X_PROPERTY(bool, ShowWiggle);
	X_PROPERTY(bool, ShowVA);
	X_PROPERTY(bool, ShowVI);

	X_PROPERTY(QColor, FBColor);
};