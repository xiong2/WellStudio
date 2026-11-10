#ifndef XSECHORIZONITEM_H
#define XSECHORIZONITEM_H

#include "xabstractitem.h"

class CXSecHorizonItem : public CXAbstractItem 
{
public:
    CXSecHorizonItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent = 0);
    ~CXSecHorizonItem(void);

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QRectF boundingRect() const
	{
		return scene()->sceneRect();
	}

	virtual void MapToScene();

protected:
    virtual void _UpdateData();

	bool m_bPreStackSection;
	int m_iSTrace;
	int m_iTraceInc;
	std::vector<float>	m_vecZ;

    QPainterPath		m_Path;
	QVector<QPointF>	m_vecIntPoints;
};

#endif