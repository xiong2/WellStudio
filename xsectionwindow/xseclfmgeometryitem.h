#ifndef XSECLFMGEOMETRYITEM_H
#define XSECLFMGEOMETRYITEM_H

#include "xabstractitem.h"

class CXSecLFMGeometryItem : public CXAbstractItem 
{
public:
	CXSecLFMGeometryItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent = 0);
	~CXSecLFMGeometryItem(void);

	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QRectF boundingRect() const
	{
		return scene()->sceneRect();
	}

	virtual void MapToScene();

protected:
	virtual void _UpdateData();

	QVector<QPolygonF>		m_vecDataLines;
	QVector<QPolygonF>		m_vecDrawLines;
	QVector<QColor>			m_vecColors;
};

#endif