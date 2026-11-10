#ifndef XABSTRACTITEM_H
#define XABSTRACTITEM_H

#include <qgraphicsitem.h>

#include "xdef.h"
#include <QPainter>
#include "x2dsectionaxis.h"
#include "x2dsectionwindow.h"
#include "xsectionwindow_global.h"

class CXObject;
class CXViewInfoObject;

class CXAbstractItem : public QGraphicsItem 
{
public:
    CXAbstractItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent = nullptr);
    ~CXAbstractItem(void);

    virtual void UpdateView(EEventType eType);
    
	void ResetData(QUuid objID);
	CXObject* GetItemObject() const;
	QUuid GetObjectID()
	{
		return m_objID;
	}

	//	Calculate item from logical coords into scene coords.
	virtual void MapToScene()
	{
	}

	virtual void HandleMouseEvent(QMouseEvent *, EXMouseEventType)
	{
	}

protected:
    virtual void _UpdateData() = 0;

    QRectF _CalcDrawPathBoundingRect(const QPainterPath& path, const QPen& pen) const;
    QPainterPath _CalcShapeFromPath(const QPainterPath& path, const QPen& pen) const;

	QUuid	m_objID;

    CXViewInfoObject* m_pViewInfo = nullptr;
    CX2DSectionWindow* m_pSectionWindow = nullptr;
    CX2DSectionAxis* m_pAxis = nullptr;
};

#endif // KEABSTRACTITEM_H

