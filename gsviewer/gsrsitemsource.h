#ifndef _GSRSITEMSOURCE_H__
#define _GSRSITEMSOURCE_H__

#include <QGraphicsRectItem>
#include <qlist.h>

class CXGlobalCoordTransform;

class GSRSItemSource : public QGraphicsRectItem
{
public:
	GSRSItemSource(QList<QPointF> listP, CXGlobalCoordTransform *, QGraphicsItem *parent = 0);

	void Relocate(QPointF, int);

	void EnableShowSticks(bool bShow)
	{
		m_bShowSticks = bShow;
	}

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	CXGlobalCoordTransform *m_pCoordTransform;
	
	bool			m_bShowSticks = true;
	QPointF			m_pos;
	qreal			m_dAzi;
	double			m_dRadius;
	int				m_iStartAngle;
	int				m_iSpanAngle;
	QVector<QPointF>	m_vecCorners;
};

#endif