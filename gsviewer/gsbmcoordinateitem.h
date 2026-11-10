#ifndef GSBMCOORDINATEITEM_H
#define GSBMCOORDINATEITEM_H

#include <QGraphicsRectItem>
#include <memory>

class CXGlobalCoordTransform;

class GSBMCoordinateItem : public QGraphicsRectItem
{
public:
	GSBMCoordinateItem(const CXGlobalCoordTransform& coordTrans, QGraphicsItem* parent = Q_NULLPTR);
	~GSBMCoordinateItem();

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

	void UpdateByItem(const QGraphicsItem* pItem);

private:
	class Impl;
	std::unique_ptr<Impl> m_pImpl;
};

#endif // GSBMCOORDINATEITEM_H
