#ifndef _GSOBJITEM_H__
#define _GSOBJITEM_H__

#include "stdafx.h"
#include <QGraphicsRectItem>
#include <qevent.h>
#include <quuid.h>
#include "gsviewer_global.h"

class CXViewInfoObject;

enum EXGSMouseEventType
{
	eGSButtonPress,
	eGSButtonRelease,
	eGSMouseMove,
	eGSDoubleClick,
};

class GSVIEWER_EXPORT GSObjItem : public QGraphicsRectItem
{
public:
	GSObjItem(CXViewInfoObject *pViewInfo, QGraphicsItem *parent = NULL) : QGraphicsRectItem(parent)
	{
		m_pViewInfo = pViewInfo;
	}

	virtual QUuid GetObjectID() = 0;

	virtual void HandleMouseEvent(QMouseEvent *, EXGSMouseEventType)
	{
	}

	CXViewInfoObject*	m_pViewInfo;
};


#endif