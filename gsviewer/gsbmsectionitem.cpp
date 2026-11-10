#include "stdafx.h"
#include "gsbmsectionitem.h"
#include "gssection.h"
#include "gssectionviewinfo.h"
#include "xglobalcoordtransform.h"
#include "gsbasemapscene.h"
#include <QPainter>

class GSBMSectionItem::Impl
{
public:
    Impl(GSSection* pSection, const CXGlobalCoordTransform& coordTrans, GSSectionViewInfo* pViewInfo);

    QPolygonF GetSectionPolyline() const;
    QPen GetSectionPen(GSBasemapScene* pScene) const;
	double GetSectionPointRadius(GSBasemapScene* pScene) const;
	bool DrawTurningPoint() const;

private:
    GSSection* m_pSection = nullptr;
    const CXGlobalCoordTransform& m_coordTrans;
    GSSectionViewInfo* m_pViewInfo = nullptr;
};

GSBMSectionItem::GSBMSectionItem(CXObject* pObj, const CXGlobalCoordTransform& coordTrans, GSSectionViewInfo* pViewInfo, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_pImpl(std::make_unique<Impl>(dynamic_cast<GSSection*>(pObj), coordTrans, pViewInfo))
{
    setZValue(5);
}

QRectF GSBMSectionItem::boundingRect() const
{
    return m_pImpl->GetSectionPolyline().boundingRect();
}

void GSBMSectionItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_pImpl->GetSectionPen(dynamic_cast<GSBasemapScene*>(scene())));
	painter->drawPolyline(m_pImpl->GetSectionPolyline());

	if (!m_pImpl->DrawTurningPoint())
		return;

	for (auto&& p : m_pImpl->GetSectionPolyline())
	{
		double dRadius = m_pImpl->GetSectionPointRadius(dynamic_cast<GSBasemapScene*>(scene()));
		painter->drawEllipse(p, dRadius, dRadius);
	}
}

GSBMSectionItem::Impl::Impl(GSSection* pSection, const CXGlobalCoordTransform& coordTrans, GSSectionViewInfo* pViewInfo)
    : m_pSection(pSection), m_coordTrans(coordTrans), m_pViewInfo(pViewInfo)
{
}

QPolygonF GSBMSectionItem::Impl::GetSectionPolyline() const
{
    QPolygonF polyline = m_pSection->GetTurnPoints();
	for (auto&& p : polyline)
	{
		p = m_coordTrans.World2Local(p);
	}
	return polyline;
}

QPen GSBMSectionItem::Impl::GetSectionPen(GSBasemapScene* pScene) const
{
	return QPen(m_pViewInfo->GetColor(), pScene->GetRealPixelSize(m_pViewInfo->GetWidth()));
}

double GSBMSectionItem::Impl::GetSectionPointRadius(GSBasemapScene* pScene) const
{
	return pScene->GetRealPixelSize(m_pViewInfo->GetTurningPointRadius());
}

bool GSBMSectionItem::Impl::DrawTurningPoint() const
{
	return m_pViewInfo->GetShowTurningPoint();
}
