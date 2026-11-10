#include "stdafx.h"
#include <QPainter>
#include "xglobalcoordtransform.h"
#include "gsbmitemrosediagram.h"
#include "gsrosediagram.h"
#include "gsbasemapscene.h"
#include "gsrosediagramviewinfo.h"

GSBMItemRoseDiagram::GSBMItemRoseDiagram(CXObject *pObj, const CXGlobalCoordTransform& coordTrans, GSRoseDiagramViewInfo *pViewInfo, QGraphicsItem* parent)
	:QGraphicsItem(parent), m_coordTrans(coordTrans), m_pViewInfo(pViewInfo), m_pRoseDiagram(dynamic_cast<GSRoseDiagram *>(pObj))
{
	setZValue(10);
}

QRectF GSBMItemRoseDiagram::boundingRect() const
{
	GSBasemapScene *pScene = dynamic_cast<GSBasemapScene *>(scene());
	if (!pScene)
		return QRectF();

	int arraySize[5] = {60, 80, 100, 150, 200};
	double dLen = pScene->GetRealPixelSize(arraySize[m_pViewInfo->GetSize() - 1]);
	QPointF offset = QPointF(dLen / 2, dLen / 2);
	QPointF centre = m_pRoseDiagram->GetCentre();

	qreal dOffset = dLen * 0.6;
	int iPos = m_pViewInfo->GetRosePos();
	if(iPos == 0)
		centre += QPointF(-dOffset, dOffset);
	else if(iPos == 1)
		centre += QPointF(0, dOffset);
	else if(iPos == 2)
		centre += QPointF(dOffset, dOffset);
	else if(iPos == 3)
		centre += QPointF(-dOffset, 0);
	else if(iPos == 5)
		centre += QPointF(dOffset, 0);
	else if(iPos == 6)
		centre += QPointF(-dOffset, -dOffset);
	else if(iPos == 7)
		centre += QPointF(0, -dOffset);
	else if(iPos == 8)
		centre += QPointF(dOffset, -dOffset);

	QPointF topLeft = m_coordTrans.World2Local(centre - offset);
	QPointF bottomRight = m_coordTrans.World2Local(centre + offset);

	return QRectF(topLeft, bottomRight);
}

void GSBMItemRoseDiagram::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	QRectF rect = boundingRect();
	QPointF center = rect.center();
	qreal dInc = rect.width() / 20;

	QColor bgColor = QColor(255, 255, 255, m_pViewInfo->GetRoseOpacity());
	painter->setBrush(QBrush(bgColor));
	painter->drawRect(rect);
	//painter->drawEllipse(rect);
	painter->setBrush(Qt::NoBrush);

	QPen pen(m_pViewInfo->GetLineColor());
	pen.setWidth(40);
	painter->setPen(pen);
	painter->setRenderHint(QPainter::Antialiasing);

	//	Lines.
	qreal dDelta = 9 * dInc / 1.4142;
	QPainterPath path;
	path.moveTo(rect.left(), center.y());
	path.lineTo(rect.right(), center.y());
	path.moveTo(center.x(), rect.top());
	path.lineTo(center.x(), rect.bottom());
	path.moveTo(center.x() - dDelta, center.y() + dDelta);
	path.lineTo(center.x() + dDelta, center.y() - dDelta);
	path.moveTo(center.x() - dDelta, center.y() - dDelta);
	path.lineTo(center.x() + dDelta, center.y() + dDelta);
	painter->drawPath(path);


	//	Circles.
	QRectF rect2 = rect;
	rect2.setCoords(rect.left() + 6 * dInc, rect.top() - 6 * dInc, rect.right() - 6 * dInc, rect.bottom() + 6 * dInc);
	painter->drawEllipse(rect2);
	rect2.setCoords(rect.left() + 2 * dInc, rect.top() - 2 * dInc, rect.right() - 2 * dInc, rect.bottom() + 2 * dInc);
	painter->drawEllipse(rect2);
	pen.setWidth(60);
	painter->setPen(pen);
	rect2.setCoords(rect.left() + dInc, rect.top() - dInc, rect.right() - dInc, rect.bottom() + dInc);
	painter->drawEllipse(rect2);

	//	Petals.
	int i, iNumPetal = m_pViewInfo->GetNumPetal();
	QColor petalColor = m_pViewInfo->GetPetalColor();
	petalColor.setAlpha(m_pViewInfo->GetRoseOpacity());
	painter->setBrush(QBrush(petalColor));
	QVector<float>& vecPetal = m_pRoseDiagram->GetPetalVector(iNumPetal);
	QPainterPath petalPath;
	petalPath.moveTo(center);

	float fMax = 0;
	for (i = 0; i < iNumPetal; i++)
	{
		if (fMax < vecPetal[i])
			fMax = vecPetal[i];
	}

	for (i = 0; i < iNumPetal; i++)
	{
		if (vecPetal[i] <= 0.02)
			continue;

		qreal dOffset = dInc + (1 - vecPetal[i] / fMax) * 10 * dInc;
		rect2.setCoords(rect.left() + dOffset, rect.top() - dOffset, rect.right() - dOffset, rect.bottom() + dOffset);
		petalPath.arcTo(rect2, (-i - 0.5) * 180 / iNumPetal, 180 / iNumPetal);
		petalPath.lineTo(center);

		petalPath.arcTo(rect2, 180 + (-i - 0.5) * 180 / iNumPetal, 180 / iNumPetal);
		petalPath.lineTo(center);
	}
	painter->drawPath(petalPath);
}
