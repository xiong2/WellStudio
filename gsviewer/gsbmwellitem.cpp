#include "stdafx.h"
#include "gsbmwellitem.h"
#include "xwell.h"
#include "gssectionviewinfo.h"
#include "xglobalcoordtransform.h"
#include "gsbasemapscene.h"
#include <QPainter>

class GSBMWellItem::Impl
{
public:
    Impl(CXWell* pWell, const CXGlobalCoordTransform& coordTrans, GSSectionViewInfo* pViewInfo);

	QString GetWellName() const;
    QPointF GetPoint() const;
    QPen GetPointPen(GSBasemapScene* pScene) const;

private:
	CXWell* m_pWell = nullptr;
    const CXGlobalCoordTransform& m_coordTrans;
    GSSectionViewInfo* m_pViewInfo = nullptr;
};

GSBMWellItem::GSBMWellItem(CXObject* pObj, const CXGlobalCoordTransform& coordTrans, GSSectionViewInfo* pViewInfo, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_pImpl(std::make_unique<Impl>(dynamic_cast<CXWell*>(pObj), coordTrans, pViewInfo))
{
    setZValue(5);
}

QRectF GSBMWellItem::boundingRect() const
{
    return QRectF(m_pImpl->GetPoint() - QPointF(1200, 1000), m_pImpl->GetPoint() + QPointF(2000, 200));
}

void GSBMWellItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pImpl->GetPointPen(dynamic_cast<GSBasemapScene*>(scene())));
	painter->drawEllipse(QRectF(m_pImpl->GetPoint() - QPointF(200, 200), m_pImpl->GetPoint() + QPointF(200, 200)));

	QFont font = painter->font();
	font.setPixelSize(600);
	painter->setFont(font);
	painter->drawText(m_pImpl->GetPoint().x() - 1200, m_pImpl->GetPoint().y() - 1000, 3200, 600, Qt::AlignCenter, m_pImpl->GetWellName());
}

GSBMWellItem::Impl::Impl(CXWell* pWell, const CXGlobalCoordTransform& coordTrans, GSSectionViewInfo* pViewInfo)
    : m_pWell(pWell), m_coordTrans(coordTrans), m_pViewInfo(pViewInfo)
{
}

QPointF GSBMWellItem::Impl::GetPoint() const
{
	double dX, dY;
	m_pWell->GetWellPosition(dX, dY);
	QPointF	p = m_coordTrans.World2Local(QPointF(dX, dY));
	return p;
}

QPen GSBMWellItem::Impl::GetPointPen(GSBasemapScene* pScene) const
{
	//return QPen(m_pViewInfo->GetColor(), pScene->GetRealPixelSize(m_pViewInfo->GetWidth()));
	return QPen(QColor("black"), pScene->GetRealPixelSize(2));
}

QString GSBMWellItem::Impl::GetWellName() const
{
	return m_pWell->GetObjectName();
}