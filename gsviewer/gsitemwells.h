#ifndef _GSITEMWELLS_H__
#define _GSITEMWELLS_H__

#include <QGraphicsRectItem>
#include <qlist.h>

class CXWell;
class CXGlobalCoordTransform;

class GSItemWells : public QGraphicsRectItem
{
public:
	GSItemWells(QList<CXWell *>, CXGlobalCoordTransform *, QGraphicsItem *parent = 0);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	QList<CXWell *>	m_listWells;
	QRectF m_bRect;
	CXGlobalCoordTransform *m_pCoordTransform;
};

#endif