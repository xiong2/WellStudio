#include "stdafx.h"
#include "gsbmitemdefinerose.h"
#include "gspdg.h"
#include "gssectionviewinfo.h"
#include "gsbasemapscene.h"
#include "xglobalcoordtransform.h"
#include "gsbasemapscene.h"
#include <QPainter>
#include <qdebug.h>

GSBMItemDefineRose::GSBMItemDefineRose(GSBasemapScene *pScene, const CXGlobalCoordTransform& coordTrans, double dRadius, QGraphicsItem* parent) :
	QGraphicsItem(parent), m_coordTrans(coordTrans), m_pScene(pScene)
{
	m_iMode = 0;
	m_dRadius = dRadius;
	setZValue(8);

	m_pointCentre = QPointF();
}

QRectF GSBMItemDefineRose::boundingRect() const
{
	if (m_iMode == 0)
	{
		if (m_pointCentre.isNull())
			return QRectF();
		else
		{
			QPointF topLeft = m_pointCentre - QPointF(m_dRadius, m_dRadius);
			QPointF bottomRight = m_pointCentre + QPointF(m_dRadius, m_dRadius);
			QPointF localTL = m_coordTrans.World2Local(topLeft);
			QPointF localBR = m_coordTrans.World2Local(bottomRight);
			return QRectF(localTL, localBR);
		}
	}
	else
	{
		return m_boundaryPolygon.boundingRect();
	}
}

void GSBMItemDefineRose::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	painter->setRenderHint(QPainter::Antialiasing);

	if (m_iMode == 0)
	{
		QColor color("blue");
		color.setAlpha(100);
		QPen pen(QColor("brown"));
		pen.setWidth(10);
		painter->setPen(pen);
		painter->setBrush(QBrush(color));

		QRectF rect = boundingRect();
		painter->drawEllipse(rect);
	}
}

void GSBMItemDefineRose::SetCentre(QPointF point)
{
	m_pointCentre = point;
	m_pScene->update();
}

void GSBMItemDefineRose::SetRadius(double dRadius)
{
	m_dRadius = dRadius;
	m_pScene->update();
}

void GSBMItemDefineRose::SetMode(int iMode)
{
	m_iMode = iMode;
}
