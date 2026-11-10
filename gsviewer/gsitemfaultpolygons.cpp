#include "stdafx.h"
#include <qpainter.h>
#include <qgraphicsscene.h>
#include "xglobalcoordtransform.h"
#include "gsutilities.h"
#include "gsitemfaultpolygons.h"
#include "gs3dhorizonfaulttraces.h"

GSItemFaultPolygons::GSItemFaultPolygons(QList<GS3DHorizonFaultTraces *> listFTs, CXGlobalCoordTransform *pCT, bool bShowName, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
	m_bShowName = bShowName;
	m_listFTs = listFTs;
	m_pCoordTransform = pCT;
}

void GSItemFaultPolygons::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	int i, j, iIDX = 0;
	setRect(scene()->sceneRect());

	QPen pen(QColor("black"));
	pen.setWidth(50);
	painter->setPen(pen);
	QFont font = painter->font();
	font.setPixelSize(800);
	painter->setFont(font);

	QPointF p1, p2;
	for (i = 0; i < m_listFTs.size(); i++)
	{
		GS3DHorizonFaultTraces *pFT = m_listFTs[i];
		std::vector<GSFaultTrace>& vecFT = pFT->GetTraces();
		QPolygonF polygon;
		for (j = 0; j < vecFT.size(); j++)
		{
			QPointF point = m_pCoordTransform->World2Local(QPointF(vecFT[j].m_p1[0], vecFT[j].m_p1[1]));
			polygon.prepend(point);
			point = m_pCoordTransform->World2Local(QPointF(vecFT[j].m_p2[0], vecFT[j].m_p2[1]));
			polygon.append(point);
		}
		painter->drawPolygon(polygon);

		if (m_bShowName)
		{					
			painter->drawText(polygon[0].x() - 1600, polygon[0].y() - 1600, 3200, 800, Qt::AlignCenter, pFT->GetObjectName());
		}
	}
}