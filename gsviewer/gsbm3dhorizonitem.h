#ifndef GS3DHORIZONITEM_H
#define GS3DHORIZONITEM_H

#include <QGraphicsItem>
#include <memory>

class CX3DHorizon;
class CXObject;
class CXGlobalCoordTransform;
class GS3DHorizonViewInfo;

/**
@class  GSBM3DHorizonItem provided in the file "gs3dhorizonitem.h"
@brief  The class provides a 3-D Horizon item that you can add to GSBasemapWindow.
@author pezy
@date   2018-03-21
@sa
*/
class GSBM3DHorizonItem : public QGraphicsItem
{
public:
    GSBM3DHorizonItem(CXObject* pHorizon, const CXGlobalCoordTransform& coordTrans, GS3DHorizonViewInfo* pViewInfo, QGraphicsItem* parent = Q_NULLPTR);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

	double ValueAt(const QPointF& pos);

private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

#endif // GS3DHORIZONITEM_H
