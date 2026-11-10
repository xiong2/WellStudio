#ifndef GSBMSTRESSMAPITEM_H
#define GSBMSTRESSMAPITEM_H

#include <memory>
#include <QGraphicsItem>

class CXObject;
class CXGlobalCoordTransform;
class GSStressMapViewInfo;

/**
@class  GSBMStressMapItem provided in the file "gsbmstressmapitem.h"
@brief  The class provides a StressMap item that you can add to GSBasemapWindow.
@author pezy
@date   2018-04-18
@sa
*/
class GSBMStressMapItem : public QGraphicsItem
{
public:
	GSBMStressMapItem(CXObject* pObj, const CXGlobalCoordTransform& coordTrans, GSStressMapViewInfo* pViewInfo, QGraphicsItem* parent = Q_NULLPTR);

	QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

	double GetMag(const QPointF& pos);
	double GetAng(const QPointF& pos);

private:
	class Impl;
	std::unique_ptr<Impl> m_pImpl;
};

#endif // GSBMSTRESSMAPITEM_H
