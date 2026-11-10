#ifndef _GSITEMSTRUCTURES_H__
#define _GSITEMSTRUCTURES_H__

#include <QGraphicsRectItem>
#include <qlist.h>

class GSStructure;
class CXGlobalCoordTransform;

class GSItemStructures : public QGraphicsRectItem
{
public:
	GSItemStructures(QList<GSStructure *>, CXGlobalCoordTransform *, QGraphicsItem *parent = 0);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	void drawAzi(QPainter *painter, GSStructure *);

	QList<GSStructure *>	m_listStructures;
	CXGlobalCoordTransform *m_pCoordTransform;
};

#endif