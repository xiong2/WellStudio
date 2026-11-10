#ifndef GSSECTIONVIEWINFO_H
#define GSSECTIONVIEWINFO_H

#include "xviewinfoobject.h"
#include "xdata_global.h"

class XDATA_EXPORT GSSectionViewInfo : public CXViewInfoObject
{
public:
	GSSectionViewInfo();
	~GSSectionViewInfo();

	X_PROPERTY(int, Width)
	X_PROPERTY(bool, ShowTurningPoint)
	X_PROPERTY(int, TurningPointRadius)

	X_PROPERTY(bool, FillByStress)
	X_PROPERTY(bool, LeftHName)
	X_PROPERTY(bool, RightHName)
	X_PROPERTY(bool, LeftPName)
	X_PROPERTY(bool, RightPName)
};

#endif // GSSECTIONVIEWINFO_H
