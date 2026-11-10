#ifndef XVIEWINFOPRESTACKGATHER_H
#define XVIEWINFOPRESTACKGATHER_H

#include "xviewinfoobject.h"
#include "xdata_global.h"

/**
@class CXViewInfoPreStackGather provided in the file "xviewinfoprestackgather.h"
@brief The class provides the view info for prestack gather.
@author pezy
@date 2017-09-30
@sa CXPreStackGather
*/
class XDATA_EXPORT CXViewInfoPreStackGather : public CXViewInfoObject
{
public:
	CXViewInfoPreStackGather();
	~CXViewInfoPreStackGather();

	X_PROPERTY(bool, IsViewAll)
	X_PROPERTY(int, MINShotID)
	X_PROPERTY(int, MAXShotID)
	X_PROPERTY(int, ShotIDStep)
	X_PROPERTY(int, ShotIDNum)
	X_PROPERTY(int, CURShotID)
	X_PROPERTY(int, SourcePointShape)
	X_PROPERTY(int, SourcePointSize)
	X_PROPERTY(QColor, SourcePointColor)
	X_PROPERTY(int, DetectPointShape)
	X_PROPERTY(int, DetectPointSize)
	X_PROPERTY(QColor, DetectPointColor)

	void SetViewObjectID(const QUuid& objID) override;
	bool ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo) override;
	
};

#endif // XVIEWINFOPRESTACKGATHER_H
