#include "stdafx.h"
#include "gsbm3dhorizonitem.h"
#include "x3dhorizon.h"
#include "gs3dhorizonviewinfo.h"
#include "gsanticline.h"
#include "gshorizongrid.h"
#include "xbicubic.h"
#include "xcolormap.h"
#include "xgeometry.h"
#include "xglobalcoordtransform.h"
#include "xisolines.h"
#include "xmath.h"
#include "xviewinfoobject.h"
#include "xseismicutmtool.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

class GSBM3DHorizonItem::Impl
{
public:
    Impl(CX3DHorizon* pHorizon, const CXGlobalCoordTransform& coordTrans, GS3DHorizonViewInfo* pViewInfo);

    QRectF GetBoundingRect() const;
    const std::vector<std::pair<QPolygonF, int>>& GetCellColorIndices();
    void GetIsolinesPen(QPen& coarsePen, QPen& normalPen);
    void GetIsolinesPath(QPainterPath* coarsePath, QPainterPath* normalPath);
    double GetValue(const QPointF& worldPos) const;
    QColor GetColor(int index) const;
    bool IsIsolinesChecked() const;
	QPolygonF CoordTranslate(const QPolygonF& polygon) const;

private:
	CX3DHorizon* m_pHorizon     = nullptr;

    const CXGlobalCoordTransform& m_coordTrans;
    GS3DHorizonViewInfo* m_pViewInfo = nullptr;
    CXColormap* m_pColormap          = nullptr;
    float* m_pData                   = nullptr;

	std::vector<std::pair<QPolygonF, int>> m_cells; // pair: polygon, color index
};

GSBM3DHorizonItem::GSBM3DHorizonItem(CXObject* pHorizon, const CXGlobalCoordTransform& coordTrans, GS3DHorizonViewInfo* pViewInfo, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_pImpl(std::make_unique<Impl>(dynamic_cast<CX3DHorizon*>(pHorizon), coordTrans, pViewInfo))
{
}

QRectF GSBM3DHorizonItem::boundingRect() const
{
    return m_pImpl->GetBoundingRect();
}

void GSBM3DHorizonItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::NoPen);
    for (auto&& p : m_pImpl->GetCellColorIndices())
    {
        QPainterPath path;
        path.addPolygon(m_pImpl->CoordTranslate(p.first));
        const QColor& color = m_pImpl->GetColor(p.second);
        painter->fillPath(path, color);
    }

    if (m_pImpl->IsIsolinesChecked())
    {
        QPen coarsePen, normalPen;
        QPainterPath coarsePath, normalPath;
        m_pImpl->GetIsolinesPen(coarsePen, normalPen);
        m_pImpl->GetIsolinesPath(&coarsePath, &normalPath);

		painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(coarsePen);
        painter->drawPath(coarsePath);
        painter->setPen(normalPen);
        painter->drawPath(normalPath);
		painter->setRenderHint(QPainter::Antialiasing, false);
    }
}

double GSBM3DHorizonItem::ValueAt(const QPointF& pos)
{
    return m_pImpl->GetValue(pos);
}

GSBM3DHorizonItem::Impl::Impl(CX3DHorizon* pHorizon, const CXGlobalCoordTransform& coordTrans, GS3DHorizonViewInfo* pViewInfo)
    : m_pHorizon(pHorizon), m_coordTrans(coordTrans), m_pViewInfo(pViewInfo)
{
    Q_ASSERT(m_pHorizon);
	Q_ASSERT(m_pViewInfo);

    m_pColormap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());
    m_pData     = m_pHorizon->GetData();
	m_cells = m_pHorizon->GetGrid().GetCellPolygonWithColorIndex(m_pData);
}

QRectF GSBM3DHorizonItem::Impl::GetBoundingRect() const
{
    double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
    m_pHorizon->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);

    QPointF topLeftPoint     = m_coordTrans.World2Local(QPointF(dXMin, dYMax));
    QPointF bottomRightPoint = m_coordTrans.World2Local(QPointF(dXMax, dYMin));

    return QRectF(topLeftPoint, bottomRightPoint);
}

const std::vector<std::pair<QPolygonF, int>>& GSBM3DHorizonItem::Impl::GetCellColorIndices()
{
#if _DEBUG
	return m_pHorizon->GetGrid().GetOriginCellWithColorIndex();
#else
	return m_cells;
#endif
}

void GSBM3DHorizonItem::Impl::GetIsolinesPen(QPen& coarsePen, QPen& normalPen)
{
    QColor coarseColor = m_pViewInfo->GetIsolineCoarseColor();
    QColor normalColor = m_pViewInfo->GetIsolineNormalColor();
    int coarseWidth    = m_pViewInfo->GetIsolineCoarseWidth();
    int normalWidth    = m_pViewInfo->GetIsolineNormalWidth();

    coarsePen = QPen(coarseColor, coarseWidth);
    normalPen = QPen(normalColor, normalWidth);
}

void GSBM3DHorizonItem::Impl::GetIsolinesPath(QPainterPath* coarsePath, QPainterPath* normalPath)
{
    double dLevelFirst = m_pViewInfo->GetIsolineLevelFirst();
    double dLevelLast  = m_pViewInfo->GetIsolineLevelLast();
    int nLevel         = m_pViewInfo->GetIsolineLevelNum();
    int nCoarseFreq    = m_pViewInfo->GetIsolineCoarseFreq();

    m_pHorizon->GetGrid().GetIsolinesPath(dLevelFirst, dLevelLast, nLevel, nCoarseFreq, m_coordTrans, coarsePath, normalPath, m_pViewInfo->GetIsolineLevelChanged());

	if (m_pViewInfo->GetIsolineLevelChanged())
		m_pViewInfo->SetIsolineLevelChanged(false);
}

double GSBM3DHorizonItem::Impl::GetValue(const QPointF& worldPos) const
{
    int i, j;
    if (!m_pHorizon->GetUTM().XYToIJ(worldPos.x(), worldPos.y(), i, j))
        return -999.25;

    double zValue = m_pData[i * m_pHorizon->GetUTM().GetNJ() + j];
    return zValue;
}

QColor GSBM3DHorizonItem::Impl::GetColor(int index) const
{
    if (index == -1)
        return Qt::black;

    Q_ASSERT(0 <= index && index <= 255);
    return m_pColormap->GetColorAt(index);
}

bool GSBM3DHorizonItem::Impl::IsIsolinesChecked() const
{
    return m_pViewInfo->GetIsolineDisplay();
}

QPolygonF GSBM3DHorizonItem::Impl::CoordTranslate(const QPolygonF& polygon) const
{
	QPolygonF translated;

	for (auto&& p : polygon)
	{
		translated << m_coordTrans.World2Local(p);
	}

	return translated;
}
