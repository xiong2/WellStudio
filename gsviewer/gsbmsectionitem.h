#ifndef GSBMSECTIONITEM_H
#define GSBMSECTIONITEM_H

#include <memory>
#include <QGraphicsItem>

class CXObject;
class CXGlobalCoordTransform;
class GSSectionViewInfo;

/**
@class  GSBMSectionItem provided in the file "gsbmsectionitem.h"
@brief  The class provides a Section Polyline item that you can add to GSBasemapWindow.
@author pezy
@date   2018-06-15
@sa
*/
class GSBMSectionItem : public QGraphicsItem
{
public:
	GSBMSectionItem(CXObject* pObj, const CXGlobalCoordTransform& coordTrans, GSSectionViewInfo* pViewInfo, QGraphicsItem* parent = Q_NULLPTR);

	QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = Q_NULLPTR) override;

private:
	class Impl;
	std::unique_ptr<Impl> m_pImpl;
};

#endif // GSBMSECTIONITEM_H
