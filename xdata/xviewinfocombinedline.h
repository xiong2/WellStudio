#pragma once

#include "xviewinfoobject.h"
#include "xdata_global.h"

class XDATA_EXPORT CXViewInfoCombinedLine : public CXViewInfoObject
{
public:
	CXViewInfoCombinedLine();
	~CXViewInfoCombinedLine() {}

	X_PROPERTY(QColor, LineColor)
	X_PROPERTY(int, LineWidth)

	virtual void SetViewObjectID(const QUuid& objID) override;
	virtual bool ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo) override;
};