#include "xsecfaultitem.h"
#include "xsectionscene.h"
#include "xfaultsticks.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xviewinfo3dfaultsticks.h"
#include "xcoordtransformer.h"

CXSecFaultItem::CXSecFaultItem(CX2DSectionWindow *pWindow, QGraphicsItem *parent) :CXAbstractItem(pWindow)
{
	setZValue(2);
}


CXSecFaultItem::~CXSecFaultItem(void)
{
}

void CXSecFaultItem::_UpdateData()
{
	m_listDataLines.clear();
	m_listDrawLines.clear();
	m_listDataPoints.clear();
	m_listDrawPoints.clear();

	CXSectionScene *pScene = (CXSectionScene *)scene();
	CXFaultSticks *pFS = dynamic_cast<CXFaultSticks *>(GetItemObject());
	if (!pFS)
		return;

	CXObject *pGeoObj = pScene->GetBackgroundSection();
	if (!pGeoObj)
		return;

	QList<CXFaultStick *> listStick;
	if (pGeoObj->GetObjectType() == EXSeismicSection)
	{
		CXSeismicSection *pSection = dynamic_cast<CXSeismicSection *>(pGeoObj);
		if (!pSection)
			return;

		if (pSection->GetSurveyID() != pFS->GetSurveyID())
			return;

		pFS->GetSticksIntersectSection((int)(pSection->GetSectionNumber()), pSection->GetSectionType(), m_listDataPoints, listStick);

		listStick.clear();
		pFS->GetSticksOnSection((int)(pSection->GetSectionNumber()), pSection->GetSectionType(), listStick);
	}
	else if (pGeoObj->GetObjectType() == EXRandomSection)
	{
		CXSeismicRandomSection *pSection = dynamic_cast<CXSeismicRandomSection *>(pGeoObj);
		if (!pSection)
			return;

		if (pSection->GetParent()->GetObjectID() != pFS->GetSurveyID())
			return;

		pFS->GetSticksOnSection(pSection->GetObjectID(), listStick);
	}

	foreach(CXFaultStick *pStick, listStick)
	{
		unsigned int iNumPoint;
		double *pData = pStick->GetXYZData(iNumPoint);
		int *pTraceNumber = pStick->GetTraceNumber();

		if (iNumPoint < 2 || !pData || !pTraceNumber)
			continue;

		QPolygonF line;
		for (int i = 0; i < iNumPoint; i++)
		{
			line << QPointF((float)pTraceNumber[i], pData[3 * i + 2]);
		}
		m_listDataLines << line;
	}

	MapToScene();
}

void CXSecFaultItem::MapToScene()
{
	CXSectionScene* pScene = (CXSectionScene*)scene();
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);
	double scenex, sceney;

	m_listDrawLines.clear();
	m_listDrawPoints.clear();
	m_boundRect = QRectF();

	foreach(QPolygonF line, m_listDataLines)
	{
		QPolygonF sceneLine;
		int nNum = line.size();
		for (int i = 0; i < nNum; i++)
		{
			QPointF pos = line[i];

			transformer.World2Scene(pos.x(), pos.y(), scenex, sceney);
			QPointF scenPoint(scenex, sceney);
			sceneLine << scenPoint;
		}

		m_listDrawLines << sceneLine;
		m_boundRect |= sceneLine.boundingRect();
	}

	foreach(QPointF point, m_listDataPoints)
	{
		transformer.World2Scene(point.x(), point.y(), scenex, sceney);
		QPointF scenePoint(scenex, sceney);

		m_listDrawPoints << scenePoint;
		m_boundRect |= QRectF(scenePoint + QPointF(-5, -5), scenePoint + QPointF(5, 5));
	}

	update();
}

void CXSecFaultItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (m_listDrawLines.isEmpty() && m_listDrawPoints.isEmpty())
		return;

	CXViewInfo3DFaultSticks *pVInfo = dynamic_cast<CXViewInfo3DFaultSticks *>(m_pViewInfo);

	painter->save();
	QPen pen;
	pen.setColor(pVInfo->GetLineColor());
	pen.setWidth(pVInfo->GetLineWidth());
	painter->setPen(pen);

	foreach(QPolygonF line, m_listDrawLines)
	{
		painter->drawPolyline(line);

		if (pVInfo->GetAnnTop())
			painter->drawText(line[0] - QPointF(0, 10), GetItemObject()->GetObjectName());

		if (pVInfo->GetAnnBottom())
			painter->drawText(line.last() + QPointF(0, 20), GetItemObject()->GetObjectName());
	}

	foreach(QPointF point, m_listDrawPoints)
	{
		painter->drawLine(point.x() - 5, point.y() - 5, point.x() + 5, point.y() + 5);
		painter->drawLine(point.x() - 5, point.y() + 5, point.x() + 5, point.y() - 5);
	}

	painter->restore();
}