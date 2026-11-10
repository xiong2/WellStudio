#ifndef GSBMPDGITEM_H
#define GSBMPDGITEM_H

#include <memory>
#include <QGraphicsItem>

class CXObject;
class CXGlobalCoordTransform;
class GSSectionViewInfo;

class GSBMPDGItem : public QGraphicsItem
{
public:
	GSBMPDGItem(CXObject* pObj, const CXGlobalCoordTransform& coordTrans, GSSectionViewInfo* pViewInfo, QGraphicsItem* parent = Q_NULLPTR);

	QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

private:
	class Impl;
	std::unique_ptr<Impl> m_pImpl;
};

#endif