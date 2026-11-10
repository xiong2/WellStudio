#ifndef _GSRSITEMCOMPOSE_H__
#define _GSRSITEMCOMPOSE_H__

#include <QGraphicsRectItem>
#include <qlist.h>

class GSDlgRSA;
class CXGlobalCoordTransform;

class GSRSItemCompose : public QGraphicsRectItem
{
public:
	GSRSItemCompose(GSDlgRSA *, QList<QPointF> listCorners, CXGlobalCoordTransform *, QGraphicsItem *parent = 0);

	void AddOneSource(qreal x, qreal y, qreal dAzi);

	bool RemoveLastSource();

	void ClearAllPoints()
	{
		m_listSouPoint.clear();
	}

	bool ModifyOneSource(int iIDX, qreal x, qreal y, qreal dZai = -999.);

	void MouseHandler(QGraphicsSceneMouseEvent *);

protected:
	int findOneSource(QPointF, qreal dTor = 1000.);

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	void compose();

	GSDlgRSA*				m_pDlgRSA;
	CXGlobalCoordTransform*	m_pCoordTransform;

	//	Sextuple of x, y, azi, radius, start angle, span angle;  Azi in degrees, start from north, clockwise.
	QList<qreal>			m_listSouPoint;		
	QVector<QPointF>		m_vecCorners;

	QPainterPath			m_stressLines;
	int						m_iSouID = -1;
};

#endif