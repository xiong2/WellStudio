#ifndef X2DWELLTOPSITEM_H
#define X2DWELLTOPSITEM_H

#include "xabstractitem.h"

class CX2DWelltopsItem : public CXAbstractItem
{
public:
	CX2DWelltopsItem(CX2DSectionWindow *pWindow, QGraphicsItem *parent = 0 );
	~CX2DWelltopsItem(void);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget  = 0 );
	virtual QRectF boundingRect() const;

	//	Calculate item from logical coords into scene coords.
	virtual void MapToScene();

protected:
	virtual void  _UpdateData();

	QVector<QPointF>	m_VecPoints;
};

#endif // KE2DWELLTOPSITEM_H