#ifndef XSECFAULTITEM_H__
#define XSECFAULTITEM_H__

#include "xabstractitem.h"

class CXSecFaultItem : public CXAbstractItem 
{
public:
	CXSecFaultItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent = 0);
	~CXSecFaultItem(void);

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QRectF boundingRect() const
	{
		return m_boundRect;
	}

	//	Calculate item from logical coords into scene coords.
	virtual void MapToScene();

protected:
	virtual void _UpdateData();

	QList<QPolygonF>	m_listDataLines;
	QList<QPolygonF>	m_listDrawLines;
	QList<QPointF>		m_listDataPoints;
	QList<QPointF>		m_listDrawPoints;

	QRectF	m_boundRect;
};

#endif