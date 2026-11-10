#ifndef _GSITEMSTICKS_H__
#define _GSITEMSTICKS_H__

#include <QGraphicsRectItem>

class CX3DHorizon;
class CXGlobalCoordTransform;

class GSItemSticks : public QGraphicsRectItem
{
public:
	GSItemSticks(CX3DHorizon *, CXGlobalCoordTransform *, QGraphicsItem *parent = 0);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	CX3DHorizon*			m_pMap;
	CXGlobalCoordTransform*	m_pCoordTransform;
};

#endif