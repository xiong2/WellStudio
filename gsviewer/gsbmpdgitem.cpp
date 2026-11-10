#include "stdafx.h"
#include "gsbmpdgitem.h"
#include "gspdg.h"
#include "gssectionviewinfo.h"
#include "xglobalcoordtransform.h"
#include "gsbasemapscene.h"
#include <QPainter>

class GSBMPDGItem::Impl
{
public:
    Impl(GSPDG* pPDG, const CXGlobalCoordTransform& coordTrans, GSSectionViewInfo* pViewInfo);

    QPointF GetPoint() const;
    QPen GetPointPen(GSBasemapScene* pScene) const;

private:
    GSPDG* m_pPDG = nullptr;
    const CXGlobalCoordTransform& m_coordTrans;
    GSSectionViewInfo* m_pViewInfo = nullptr;
};

GSBMPDGItem::GSBMPDGItem(CXObject* pObj, const CXGlobalCoordTransform& coordTrans, GSSectionViewInfo* pViewInfo, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_pImpl(std::make_unique<Impl>(dynamic_cast<GSPDG*>(pObj), coordTrans, pViewInfo))
{
    setZValue(5);
}

QRectF GSBMPDGItem::boundingRect() const
{
    return QRectF(m_pImpl->GetPoint() - QPointF(200, 200), m_pImpl->GetPoint() + QPointF(200, 200));
}

void GSBMPDGItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pImpl->GetPointPen(dynamic_cast<GSBasemapScene*>(scene())));
	painter->drawEllipse(boundingRect());
}

GSBMPDGItem::Impl::Impl(GSPDG* pPDG, const CXGlobalCoordTransform& coordTrans, GSSectionViewInfo* pViewInfo)
    : m_pPDG(pPDG), m_coordTrans(coordTrans), m_pViewInfo(pViewInfo)
{
}

QPointF GSBMPDGItem::Impl::GetPoint() const
{
    QPolygonF polyline = m_pPDG->GetTrajectoryPoints();
	QPointF	p = m_coordTrans.World2Local(polyline[0]);
	return p;
}

QPen GSBMPDGItem::Impl::GetPointPen(GSBasemapScene* pScene) const
{
	//return QPen(m_pViewInfo->GetColor(), pScene->GetRealPixelSize(m_pViewInfo->GetWidth()));
	return QPen(QColor("blue"), pScene->GetRealPixelSize(2));
}