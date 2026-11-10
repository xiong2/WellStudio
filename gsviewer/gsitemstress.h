#ifndef _GSITEMSTRESS_H__
#define _GSITEMSTRESS_H__

#include <QGraphicsRectItem>

class GSStressMap;
class CXGlobalCoordTransform;

class GSItemStress : public QGraphicsRectItem
{
public:
	GSItemStress(GSStressMap *, CXGlobalCoordTransform *, QGraphicsItem *parent = 0);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	GSStressMap*			m_pMap;
	CXGlobalCoordTransform*	m_pCoordTransform;
};

#endif