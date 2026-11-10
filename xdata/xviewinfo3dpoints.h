#ifndef XVIEWINFO3DPOINTS_H
#define XVIEWINFO3DPOINTS_H

#include "xdata_global.h"
#include "xviewinfoobject.h"

class XDATA_EXPORT CXViewInfo3DPoints : public CXViewInfoObject
{
public:
	CXViewInfo3DPoints();
	~CXViewInfo3DPoints();

	X_PROPERTY(int, PointSize)
	X_PROPERTY(QColor, PointColor)
	X_PROPERTY(bool, IsObjectColor)

	void SetViewObjectID(const QUuid& objID) override;
};

#endif // XVIEWINFO3DPOINTS_H
