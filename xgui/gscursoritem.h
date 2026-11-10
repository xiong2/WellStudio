#ifndef GSCURSORITEM_H
#define GSCURSORITEM_H

#include <QGraphicsItem>
#include "xgui_global.h"

class CXGlobalCoordTransform;

class XGUI_EXPORT GSCursorItem : public QGraphicsItem
{
public:
	GSCursorItem(const CXGlobalCoordTransform& coordTrans, QGraphicsItem* parent = Q_NULLPTR);
	~GSCursorItem();

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

	void UpdatePosition(double dx, double dy);
	void Clear();

private:
	double getRealPixelSize(int size) const;

private:
	const CXGlobalCoordTransform& m_coordTrans;
	QPainterPath m_crossPath;
};

#endif // GSCURSORITEM_H
