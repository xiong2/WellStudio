#ifndef XSECRECTZOOMITEM_H__
#define XSECRECTZOOMITEM_H__

#include <qgraphicsitem.h>
#include <qevent.h>
#include "xsectionwindow_global.h"

class CX2DSectionWindow;

class CXSecRectZoomItem : public QGraphicsItem
{
public:
	CXSecRectZoomItem(CX2DSectionWindow *, QGraphicsItem* parent = 0);

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	virtual QRectF boundingRect() const;
	virtual void HandleMouseEvent(QMouseEvent *, EXMouseEventType);

private:
	void _leftButtonPressed(QMouseEvent *);
	void _buttonRelease();
	void _mouseMoving(QMouseEvent *);

	QPointF m_topLeft;
	QPointF m_bottomRight;

	CX2DSectionWindow *m_pWindow;
};

#endif