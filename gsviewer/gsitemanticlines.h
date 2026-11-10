#ifndef _GSITEMANTICLINES_H__
#define _GSITEMANTICLINES_H__

#include <QGraphicsRectItem>
#include <qlist.h>

class GSAnticline;
class CXGlobalCoordTransform;

class GSItemAnticlines : public QGraphicsRectItem
{
public:
	GSItemAnticlines(QList<GSAnticline *>, CXGlobalCoordTransform *, QGraphicsItem *parent = 0);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	QList<GSAnticline *>	m_listAnticlines;
	CXGlobalCoordTransform *m_pCoordTransform;
};

#endif