#ifndef _GSITEMTRAPPOINTS_H__
#define _GSITEMTRAPPOINTS_H__

#include <QGraphicsRectItem>
#include <qvector.h>

class CXGlobalCoordTransform;

class GSItemTrapPoints : public QGraphicsRectItem
{
public:
	GSItemTrapPoints(QVector<QVector<double>>, CXGlobalCoordTransform *, QGraphicsItem *parent = 0);

	void SetColorByGroup(bool bCBGroup)
	{
		m_bColorByGroup = bCBGroup;
	}

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	bool m_bColorByGroup;
	QVector<QVector<double>> m_vecvecPoints;
	CXGlobalCoordTransform *m_pCoordTransform;
};

#endif