#include "stdafx.h"
#include <qpainter.h>
#include <qgraphicsscene.h>
#include <qdebug.h>
#include "xglobalcoordtransform.h"
#include "gsutilities.h"
#include "gsrsitemsource.h"
#include "xmathmacro.h"

GSRSItemSource::GSRSItemSource(QList<QPointF> listP, CXGlobalCoordTransform *pCT, QGraphicsItem *parent)
	: QGraphicsRectItem(parent)
{
	m_vecCorners = listP.toVector();
	m_pCoordTransform = pCT;
}

void GSRSItemSource::Relocate(QPointF pos, int iAzi)
{
	m_dAzi = iAzi * M_PI / 180;
	m_pos = pos;
	QLineF line0(m_pos, m_vecCorners[0]);
	QLineF line1(m_pos, m_vecCorners[1]);
	QLineF line2(m_pos, m_vecCorners[2]);
	QLineF line3(m_pos, m_vecCorners[3]);

	qreal minAng = qMin(line0.angle(), line1.angle());
	minAng = qMin(minAng, line2.angle());
	minAng = qMin(minAng, line3.angle());

	qreal maxAng = qMax(line0.angle(), line1.angle());
	maxAng = qMax(maxAng, line2.angle());
	maxAng = qMax(maxAng, line3.angle());

	m_dRadius = qMax(line0.length(), line1.length());
	m_dRadius = qMax(m_dRadius, line2.length());
	m_dRadius = qMax(m_dRadius, line3.length());

	m_iStartAngle = 360 * 16 - (int)(maxAng * 16);
	m_iSpanAngle = (int)((maxAng - minAng) * 16);
}

void GSRSItemSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	int i, j, iIDX = 0;
	setRect(scene()->sceneRect());

	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);

	QPointF	locPoint = m_pCoordTransform->World2Local(m_pos);

	QPointF offset(m_dRadius, m_dRadius);
	QPointF topLeft = m_pCoordTransform->World2Local(m_pos - offset), bottomRight = m_pCoordTransform->World2Local(m_pos + offset);
	QRectF rect(topLeft, bottomRight);

	QRadialGradient rG(locPoint, rect.width() / 2);
	rG.setColorAt(0, QColor(0, 255, 0, 200));
	rG.setColorAt(1, QColor(0, 255, 0, 50));
	painter->setBrush(QBrush(rG));
	painter->setPen(Qt::NoPen);
	painter->drawPie(rect, m_iStartAngle, m_iSpanAngle);

	painter->setBrush(QBrush(QColor("red")));
	qreal dL = 4000, dS = 2000;
	QPolygonF poly1, poly2;
	poly1 << locPoint + QPointF(cos(m_dAzi) * dS, sin(m_dAzi) * dS)
		<< locPoint + QPointF(sin(m_dAzi) * dS / 8, -cos(m_dAzi) * dS / 8)
		<< locPoint + QPointF(-cos(m_dAzi) * dS, -sin(m_dAzi) * dS)
		<< locPoint + QPointF(sin(m_dAzi) * dS / 8, cos(m_dAzi) * dS / 8);
	painter->drawPolygon(poly1);

	poly2 << locPoint + QPointF(sin(m_dAzi) * dL, -cos(m_dAzi) * dL)
		<< locPoint + QPointF(cos(m_dAzi) * dL / 8, sin(m_dAzi) * dL / 8)
		<< locPoint - QPointF(sin(m_dAzi) * dL, -cos(m_dAzi) * dL)
		<< locPoint + QPointF(-cos(m_dAzi) * dL / 8, -sin(m_dAzi) * dL / 8);
	painter->drawPolygon(poly2);

	if (m_bShowSticks)
	{
		double dMinX, dMaxX, dMinY, dMaxY;
		dMinX = qMin(m_vecCorners[0].x(), m_vecCorners[1].x());
		dMinX = qMin(dMinX, m_vecCorners[2].x());
		dMinX = qMin(dMinX, m_vecCorners[3].x());
		dMaxX = qMax(m_vecCorners[0].x(), m_vecCorners[1].x());
		dMaxX = qMax(dMaxX, m_vecCorners[2].x());
		dMaxX = qMax(dMaxX, m_vecCorners[3].x());
		dMinY = qMin(m_vecCorners[0].y(), m_vecCorners[1].y());
		dMinY = qMin(dMinY, m_vecCorners[2].y());
		dMinY = qMin(dMinY, m_vecCorners[3].y());
		dMaxY = qMax(m_vecCorners[0].y(), m_vecCorners[1].y());
		dMaxY = qMax(dMaxY, m_vecCorners[2].y());
		dMaxY = qMax(dMaxY, m_vecCorners[3].y());

		QPen pen(QColor("blue"));
		pen.setWidth(50);
		painter->setPen(pen);

		QPainterPath ticks = QPainterPath();
		QPolygonF boundary(m_vecCorners);
		double dLen = 1000;
		double dDelta = qMax(dMaxX - dMinX, dMaxY - dMinY) / 10;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				QPointF point(dMinX + i * dDelta, dMinY + j * dDelta);
				if (!boundary.containsPoint(point, Qt::WindingFill))
					continue;

				point = m_pCoordTransform->World2Local(point);
				ticks.moveTo(point + QPointF(sin(m_dAzi) * dLen, -cos(m_dAzi) * dLen));
				ticks.lineTo(point - QPointF(sin(m_dAzi) * dLen, -cos(m_dAzi) * dLen));
			}
		}
		painter->drawPath(ticks);
	}

	painter->restore();
}