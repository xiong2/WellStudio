#include "stdafx.h"
#include <qpainter.h>
#include <qgraphicsscene.h>
#include <xmathmacro.h>
#include "xglobalcoordtransform.h"
#include "gsutilities.h"
#include "gsitemstructures.h"
#include "gsstructure.h"
#include "xglobal.h"

GSItemStructures::GSItemStructures(QList<GSStructure *> listStructures, CXGlobalCoordTransform *pCT, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
	m_listStructures = listStructures;
	m_pCoordTransform = pCT;
}

void GSItemStructures::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	int i, j, iIDX = 0;
	setRect(scene()->sceneRect());

	QColor color("brown");
	color.setAlpha(100);
	QPen pen(QColor("brown"));
	pen.setWidth(10);
	QPointF p1, p2;

	for (i = 0; i < m_listStructures.size(); i++)
	{
		painter->setPen(pen);
		painter->setBrush(QBrush(color));
		QPolygonF polygon = m_listStructures[i]->GetBoundaryPolygon();
		QPolygonF localPolygon;

		foreach(QPointF point, polygon)
		{
			QPointF lP = m_pCoordTransform->World2Local(point);
			localPolygon << lP;
		}

		painter->drawPolygon(localPolygon);

		drawAzi(painter, m_listStructures[i]);
	}
}

void GSItemStructures::drawAzi(QPainter *painter, GSStructure *pStr)
{
	QPointF p0, p1, p2, p3, pc;
	pStr->GetEndPoints(p0, p1);
	pc = (p0 + p1) / 2;
	double dHalfLen = pStr->GetLength() * 0.3;

	double dAzi = pStr->GetStressAzimuth();
	if (dAzi == g_dInvalidData)
		return;

	dAzi = dAzi * M_PI / 180;

	painter->save();
	QColor color("blue");
	color.setAlpha(200);
	QPen pen(QColor("blue"));
	pen.setWidth(10);
	painter->setPen(pen);
	painter->setBrush(QBrush(color));

	p0.setX(pc.x() + dHalfLen * cos(dAzi));
	p0.setY(pc.y() + dHalfLen * sin(dAzi));
	p1.setX(pc.x() - dHalfLen * cos(dAzi));
	p1.setY(pc.y() - dHalfLen * sin(dAzi));
	p2.setX(pc.x() + dHalfLen * sin(dAzi) * 0.1);
	p2.setY(pc.y() - dHalfLen * cos(dAzi) * 0.1);
	p3.setX(pc.x() - dHalfLen * sin(dAzi) * 0.1);
	p3.setY(pc.y() + dHalfLen * cos(dAzi) * 0.1);

	QPolygonF localPolygon;
	p0 = m_pCoordTransform->World2Local(p0);
	localPolygon << p0;
	p2 = m_pCoordTransform->World2Local(p2);
	localPolygon << p2;
	p1 = m_pCoordTransform->World2Local(p1);
	localPolygon << p1;
	p3 = m_pCoordTransform->World2Local(p3);
	localPolygon << p3;

	painter->drawPolygon(localPolygon);

	painter->restore();
}