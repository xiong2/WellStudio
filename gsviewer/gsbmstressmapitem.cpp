#include "stdafx.h"
#include "gsbmstressmapitem.h"
#include <QPainter>
#include "gsanticline.h"
#include "gsstructure.h"
#include "gsstressmap.h"
#include "gs3dhorizonfaulttraces.h"
#include "xglobalcoordtransform.h"
#include "xcolormap.h"
#include "gsstressmapviewinfo.h"
#include "gsgeometry.h"
#include "gsbmitemdef.h"
#include "gsdef.h"

class GSBMStressMapItem::Impl
{
public:
    Impl(GSStressMap* pStressMap, const CXGlobalCoordTransform& coordTrans, GSStressMapViewInfo* pViewInfo);

	QRectF GetBoundingRect() const;
    const QPainterPath& GetStresslines() const;
	const QPainterPath& GetAnticlineMarks() const;
	const QVector<QLineF>& GetAnticlines() const;
	const std::vector<std::pair<QPolygonF, QColor>>& GetCapsulePolygonWithColor() const;
	const std::vector<std::pair<QPolygonF, QColor>>& GetStressCellPloygonWithColor() const;
	QPen GetStresslinesPen() const;
	QPen GetFPPen() const;
	QPen GetCapsulePen() const;
	QColor GetAnticlineColor() const;
	QColor GetAnticlineMarkerLineColor() const;
	QColor GetCapsuleBrush(const QColor& color) const;
	void ViewInfoChanged();
	bool ShowStressStatesAsBaseColormap() const;
	QColor GetStressStatesBrush(const QColor& color) const;

	double GetMag(const QPointF& worldPos) const;
	double GetAng(const QPointF& worldPos) const;

	GSStressMapViewInfo* GetViewInfo()
	{
		return m_pViewInfo;
	}

	QList<QPolygonF>& GetFaultPolygons()
	{
		return m_listFP;
	}

	void CheckStressMode(bool bTL)
	{
		if (m_bTL != bTL)
		{
			m_bTL = bTL;
			buildStressMap();
		}
	}

private:
	void buildFaultPolygons();
    void buildCapsulePolygons();
    void buildStresslines();
	void buildStressMap();

private:
    GSStressMap* m_pStressMap   = nullptr;

	bool	m_bTL = false;

    const CXGlobalCoordTransform& m_coordTrans;
    GSStressMapViewInfo* m_pViewInfo = nullptr;
    std::vector<std::pair<QPolygonF, QColor>> m_capsuleWithColor;
	QPainterPath m_anticlineMarks;
	QVector<QLineF> m_anticlines;
    QPainterPath m_stresslines;
	std::vector<std::pair<QPolygonF, QColor>> m_stressCellWithColor;
	QList<QPolygonF>	m_listFP;
};

GSBMStressMapItem::GSBMStressMapItem(CXObject* pObj, const CXGlobalCoordTransform& coordTrans, GSStressMapViewInfo* pViewInfo, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_pImpl(std::make_unique<Impl>(dynamic_cast<GSStressMap*>(pObj), coordTrans, pViewInfo))
{
    setZValue(1);
}

QRectF GSBMStressMapItem::boundingRect() const
{
    return m_pImpl->GetBoundingRect();
}

void GSBMStressMapItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	GSStressMapViewInfo *pViewInfo = m_pImpl->GetViewInfo();

	if (data(NGSBMItem::eIsViewInfoChanged).toBool())
	{
		m_pImpl->ViewInfoChanged();
		setData(NGSBMItem::eIsViewInfoChanged, false);
	}

	if (m_pImpl->ShowStressStatesAsBaseColormap())
	{
		m_pImpl->CheckStressMode(pViewInfo->GetShowAsTrafficLight());

		painter->setPen(Qt::NoPen);
		for (auto&& cell : m_pImpl->GetStressCellPloygonWithColor())
		{
			QPainterPath path;
			path.addPolygon(cell.first);
			painter->fillPath(path, m_pImpl->GetStressStatesBrush(cell.second));
		}
	}

	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(m_pImpl->GetStresslinesPen());
	painter->drawPath(m_pImpl->GetStresslines());

	if (pViewInfo->GetShowFaultPolygon())
	{
		painter->setPen(m_pImpl->GetFPPen());
		//painter->setBrush(pViewInfo->GetFPFillColor());
		foreach(QPolygonF polygon, m_pImpl-> GetFaultPolygons())
		{
			QPainterPath path;
			path.addPolygon(polygon);
			painter->drawPath(path);
		}
	}

	if (pViewInfo->GetShowCapsule())
	{
		painter->setPen(m_pImpl->GetCapsulePen());
		for (auto&& capsule : m_pImpl->GetCapsulePolygonWithColor())
		{
			QPainterPath path;
			path.addPolygon(capsule.first);
			painter->setBrush(m_pImpl->GetCapsuleBrush(capsule.second));
			painter->drawPath(path);
		}

	}	

	if (pViewInfo->GetShowAnticline())
	{
		painter->drawLines(m_pImpl->GetAnticlines());
		painter->setPen(m_pImpl->GetAnticlineMarkerLineColor());
		painter->setBrush(m_pImpl->GetAnticlineColor());
		painter->drawPath(m_pImpl->GetAnticlineMarks());
	}

	painter->setRenderHint(QPainter::Antialiasing, false);
}

double GSBMStressMapItem::GetMag(const QPointF & pos)
{
	return m_pImpl->GetMag(pos);
}

double GSBMStressMapItem::GetAng(const QPointF & pos)
{
	return m_pImpl->GetAng(pos);
}

GSBMStressMapItem::Impl::Impl(GSStressMap* pStressMap, const CXGlobalCoordTransform& coordTrans, GSStressMapViewInfo* pViewInfo)
    : m_pStressMap(pStressMap), m_coordTrans(coordTrans), m_pViewInfo(pViewInfo)
{
    Q_ASSERT(m_pStressMap);
    Q_ASSERT(m_pViewInfo);

	buildFaultPolygons();
    buildCapsulePolygons();
    buildStresslines();
	buildStressMap();
}

QRectF GSBMStressMapItem::Impl::GetBoundingRect() const
{
	if (!m_pViewInfo->GetShowStressStates())
	{
		QRectF boundingRect = m_stresslines.boundingRect();
		for (auto capsule : m_capsuleWithColor)
		{
			boundingRect.united(capsule.first.boundingRect());
		}
		return boundingRect;
	}

	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
    m_pStressMap->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);

    QPointF topLeftPoint     = m_coordTrans.World2Local(QPointF(dXMin, dYMax));
    QPointF bottomRightPoint = m_coordTrans.World2Local(QPointF(dXMax, dYMin));

    return QRectF(topLeftPoint, bottomRightPoint);
}

const QPainterPath& GSBMStressMapItem::Impl::GetStresslines() const
{
    return m_stresslines;
}

const QPainterPath& GSBMStressMapItem::Impl::GetAnticlineMarks() const
{
    return m_anticlineMarks;
}

const QVector<QLineF>& GSBMStressMapItem::Impl::GetAnticlines() const
{
	return m_anticlines;
}

const std::vector<std::pair<QPolygonF, QColor>>& GSBMStressMapItem::Impl::GetCapsulePolygonWithColor() const
{
	return m_capsuleWithColor;
}

const std::vector<std::pair<QPolygonF, QColor>>& GSBMStressMapItem::Impl::GetStressCellPloygonWithColor() const
{
	return m_stressCellWithColor;
}

QPen GSBMStressMapItem::Impl::GetStresslinesPen() const
{
	QColor color = m_pViewInfo->GetStresslinesColor();
	int width = m_pViewInfo->GetStresslinesWidth() * 10;
	return QPen(color, width);
}

QPen GSBMStressMapItem::Impl::GetFPPen() const
{
	QColor color = m_pViewInfo->GetFPLineColor();
	int width = m_pViewInfo->GetFPLineWidth() * 10;
	return QPen(color, width);
}

QPen GSBMStressMapItem::Impl::GetCapsulePen() const
{
	QColor color = m_pViewInfo->GetCapsuleLineColor();
	int width = m_pViewInfo->GetAnticlineWidth() * 10;
	return QPen(color, width);
}

QColor GSBMStressMapItem::Impl::GetAnticlineColor() const
{
	QColor color = m_pViewInfo->GetAnticlineColor();
	return color;
}

QColor GSBMStressMapItem::Impl::GetAnticlineMarkerLineColor() const
{
	QColor color = m_pViewInfo->GetAnticlineMarkerLineColor();
	return color;
}

QColor GSBMStressMapItem::Impl::GetCapsuleBrush(const QColor& color) const
{
	QColor c(color);
	c.setAlphaF(m_pViewInfo->GetCapsuleOpacity());
	return c;
}

void GSBMStressMapItem::Impl::ViewInfoChanged()
{
	buildFaultPolygons();
	buildCapsulePolygons();
	buildStresslines();
}

bool GSBMStressMapItem::Impl::ShowStressStatesAsBaseColormap() const
{
	return m_pViewInfo->GetShowStressStates();
}

QColor GSBMStressMapItem::Impl::GetStressStatesBrush(const QColor& color) const
{
	QColor c(color);
	c.setAlphaF(m_pViewInfo->GetStressStatesOpacity());
    return c;
}

double GSBMStressMapItem::Impl::GetMag(const QPointF& worldPos) const
{
    int i, j;
    CXSeismicUTMTool& utm = m_pStressMap->GetUTM();
	if (!utm.XYToIJ(worldPos.x(), worldPos.y(), i, j))
		return -999.25;

	return m_pStressMap->GetData()[i * utm.GetNJ() + j];
}

double GSBMStressMapItem::Impl::GetAng(const QPointF & worldPos) const
{
	int i, j;
	CXSeismicUTMTool& utm = m_pStressMap->GetUTM();
	if (!utm.XYToIJ(worldPos.x(), worldPos.y(), i, j))
		return -999.25;

	return m_pStressMap->GetData()[utm.GetNI() * utm.GetNJ() + i * utm.GetNJ() + j];
}

void GSBMStressMapItem::Impl::buildFaultPolygons()
{
	m_listFP.clear();

	QList<CXObject *> listObj = m_pStressMap->GetChildren(EXGSFaultTraces);
	foreach(CXObject *pObj, listObj)
	{
		GS3DHorizonFaultTraces *pFT = (GS3DHorizonFaultTraces *)pObj;
		std::vector<GSFaultTrace>& vecFT = pFT->GetTraces();
		QPolygonF polygon;
		for (int j = 0; j < vecFT.size(); j++)
		{
			QPointF point1 = m_coordTrans.World2Local(QPointF(vecFT[j].m_p1[0], vecFT[j].m_p1[1]));
			QPointF point2 = m_coordTrans.World2Local(QPointF(vecFT[j].m_p2[0], vecFT[j].m_p2[1]));
			QPointF point = (point1 + point2) / 2;
			polygon.prepend(point);
			//point = m_coordTrans.World2Local(QPointF(vecFT[j].m_p2[0], vecFT[j].m_p2[1]));
			//polygon.append(point);
		}

		m_listFP<<polygon;
	}
}

void GSBMStressMapItem::Impl::buildCapsulePolygons()
{
	m_capsuleWithColor.clear();
	m_anticlineMarks = QPainterPath();

    if (m_pStressMap->GetObjectType() != EXGSStressMap)
        return;

	CXColormap* pColormap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());

    const QList<CXObject*>& capsules = m_pStressMap->GetChildren(EXGSStructure);
    for (auto pObj : capsules)
    {
        auto pCapsule = dynamic_cast<GSStructure*>(pObj);
        if (!pCapsule)
            continue;

        QPolygonF capsulePolygon = pCapsule->GetBoundaryPolygon();
        for (auto& p : capsulePolygon)
        {
            p = m_coordTrans.World2Local(p);
        }
        m_capsuleWithColor.emplace_back(capsulePolygon, pColormap->GetColorAt(pCapsule->GetAdjMagState()));
    }

	int markerSize = m_pViewInfo->GetAnticlineMarkerSize();
	int arrowSize = m_pViewInfo->GetAnticlineStressArrowSize();

    const QList<CXObject*>& anticlines = m_pStressMap->GetChildren(EXGSAnticline);
    for (auto pObj : anticlines)
    {
        auto pAnticline = dynamic_cast<GSAnticline*>(pObj);
        if (!pAnticline)
            continue;

        QPointF p0, p1;
        pAnticline->GetEndPoints(p0, p1);
        p0 = m_coordTrans.World2Local(p0);
        p1 = m_coordTrans.World2Local(p1);

		QLineF anticline(p0, p1);
        m_anticlines << anticline;

		// marker
        QPointF markP0(p0.x() + (p1.x() - p0.x()) * 1.0 / 4.0, p0.y() + (p1.y() - p0.y()) * 1.0 / 4.0);
        QPointF markP1(p0.x() + (p1.x() - p0.x()) * 3.0 / 4.0, p0.y() + (p1.y() - p0.y()) * 3.0 / 4.0);
		double angle = anticline.angle();
		GSGeom::EMarkerType markerType = pAnticline->IsAnticline() ? GSGeom::eAnticline : GSGeom::eSyncline;
		QPolygonF mark0 = GSGeom::CreateMarker(markerType, markP0, 600 + 100 * markerSize, -angle);
		QPolygonF mark1 = GSGeom::CreateMarker(markerType, markP1, 600 + 100 * markerSize, -angle);
        m_anticlineMarks.addPolygon(mark0);
        m_anticlineMarks.addPolygon(mark1);

		// arrows
		QPointF center((anticline.x1() + anticline.x2()) / 2, (anticline.y1() + anticline.y2()) / 2);
		QPolygonF arrow1 = GSGeom::CreateMarker(GSGeom::eStressArrow, center, 2000 + 500 * arrowSize, -angle + 90.0);
		QPolygonF arrow2 = GSGeom::CreateMarker(GSGeom::eStressArrow, center, 2000 + 500 * arrowSize, -angle - 90.0);
		m_anticlineMarks.addPolygon(arrow1);
		m_anticlineMarks.addPolygon(arrow2);
    }
}

void GSBMStressMapItem::Impl::buildStresslines()
{
    m_stresslines = QPainterPath();

    if (m_pStressMap->GetObjectType() != EXGSStressMap)
        return;

    CXSeismicUTMTool& utm = m_pStressMap->GetUTM();
    float* pData        = m_pStressMap->GetData();

    double dIInterval = utm.GetIInterval();
	int nStep = m_pViewInfo->GetStresslinesStep();
	bool bShowAll = m_pViewInfo->GetStresslineAll();
	float arrayLen[10] = {16, 8, 4, 2, 1.5, 1, 0.8, 0.5, 0.25, 0.1};
	float fLen = arrayLen[m_pViewInfo->GetStresslinesLength() - 1];

    for (int i = 0; i < utm.GetNI(); i += nStep)
    {
        for (int j = 0; j < utm.GetNJ(); j += nStep)
        {
            double x, y;
            utm.IJToXY(i, j, x, y);
			float mag = pData[i * utm.GetNJ() + j];
            float ang = pData[utm.GetNI() * utm.GetNJ() + i * utm.GetNJ() + j];

			// Don't draw direction marker if magnitude is less than ESS.
			if (!bShowAll && mag <= gStressMagRange[MAG_UPLIFT].m_fSHMagLower)
				continue;

            QPointF p(x, y);
            QPointF p1(x - dIInterval * nStep / fLen, y);
            QPointF p2(x + dIInterval * nStep / fLen, y);

            QLineF line1(p, p2);
            line1.setAngle(-ang);
			QLineF line2(p, p1);
			line2.setAngle(180-ang);

			QPointF line1p2 = m_coordTrans.World2Local(line1.p2());
			QPointF line2p2 = m_coordTrans.World2Local(line2.p2());

            m_stresslines.moveTo(line1p2);
			m_stresslines.lineTo(line2p2);
        }
    }
}

void GSBMStressMapItem::Impl::buildStressMap()
{
    m_stressCellWithColor.clear();

    CXColormap* pColormap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());
    CXSeismicUTMTool& utm   = m_pStressMap->GetUTM();
    float* pData          = m_pStressMap->GetData();	

	std::vector<float> levels; // from low to high.
	for (int i = 0; i < sizeof(gStressMagRange) / sizeof(gStressMagRange[0]); ++i)
	{
		levels.push_back(gStressMagRange[i].m_fSHMagLower);
	}

	bool bTL = m_bTL;
	auto getColorByStressValue = [pColormap, &levels, &bTL](float mag)
	{
		if (bTL)
		{
			if(mag < 1.2)
				return QColor("green");
			else if(mag > 1.397)
				return QColor("red");
			else
				return QColor("yellow");
		}
		else
		{
			for (size_t i = levels.size() - 2; i >= 0; --i)
			{
				if (mag >= levels[i])
					return pColormap->GetColorAt(i);
			}

			return QColor("black");
		}
	};

    for (int i = 0; i < utm.GetNI() - 1; ++i)
    {
        for (int j = 0; j < utm.GetNJ() - 1; ++j)
        {
            float mag = pData[i * utm.GetNJ() + j];
			if (mag < levels.front() || mag > levels.back())
				continue;

			QPolygonF cell(4);

			utm.IJToXY(i, j, cell[0].rx(), cell[0].ry());
            utm.IJToXY(i + 1, j, cell[1].rx(), cell[1].ry());
            utm.IJToXY(i + 1, j + 1, cell[2].rx(), cell[2].ry());
            utm.IJToXY(i, j + 1, cell[3].rx(), cell[3].ry());

			for (auto&& p : cell)
			{
				p = m_coordTrans.World2Local(p);
			}

			m_stressCellWithColor.push_back(std::make_pair(cell, getColorByStressValue(mag)));
        }
    }
}
