#include <qpainter.h>
#include <qfont.h>
#include <qdebug.h>
#include "xaxisitem.h"
#include "xscene.h"
#include "xgraphicviewinfo.h"

CXAxisItem::CXAxisItem(QString sName, QGraphicsItem *parent): QGraphicsItem(parent)
{
	setZValue(-5);
	m_sName = sName;
}

//void CXAxisItem::Populate(bool bHorizontal, bool bTopLeft, bool bFixScale, double dStart, double dStep, double dScaleOrEnd)
void CXAxisItem::Populate(bool bHorizontal, bool bTopLeft, bool bFixScale, double dScaleOrEnd)
{
	CXScene *pScene = (CXScene *)scene();
	if(!pScene)
		return;

	CXGraphicViewInfo *pWViewInfo = pScene->GetWindowViewInfo();

	m_bFixScale	= bFixScale;

	if(bFixScale)
		m_dScale	= dScaleOrEnd;
	else
	{
		m_dScale	= 0.;
	}

	m_bHorizontal	= bHorizontal;
	m_bTopLeft		= bTopLeft;
}

QRectF CXAxisItem::boundingRect() const
{
	return QRectF(0, 0, scene()->width(), scene()->height());
}

bool CXAxisItem::isCrossed()
{
	CXScene *pScene = (CXScene *)scene();
	CXGraphicViewInfo *pWViewInfo = pScene->GetWindowViewInfo();

	if(m_bHorizontal)
		return pWViewInfo->m_bHAxisGrid;
	else
		return pWViewInfo->m_bVAxisGrid;
}

QColor CXAxisItem::getGridLineColor()
{
	CXScene *pScene = (CXScene *)scene();
	CXGraphicViewInfo *pWViewInfo = pScene->GetWindowViewInfo();

	if(m_bHorizontal)
		return pWViewInfo->m_hAxisGridColor;
	else
		return pWViewInfo->m_vAxisGridColor;
}

Qt::PenStyle CXAxisItem::getGridLineStyle()
{
	CXScene *pScene = (CXScene *)scene();
	CXGraphicViewInfo *pWViewInfo = pScene->GetWindowViewInfo();

	if(m_bHorizontal)
		return (Qt::PenStyle)(pWViewInfo->m_iHAxisGridStyle);
	else
		return (Qt::PenStyle)(pWViewInfo->m_iVAxisGridStyle);
}

int CXAxisItem::getGridLineWidth()
{
	CXScene *pScene = (CXScene *)scene();
	CXGraphicViewInfo *pWViewInfo = pScene->GetWindowViewInfo();

	if(m_bHorizontal)
		return pWViewInfo->m_iHAxisGridWidth;
	else
		return pWViewInfo->m_iVAxisGridWidth;
}

void CXAxisItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	CXScene *pScene = (CXScene *)scene();
	CXGraphicViewInfo *pWViewInfo = pScene->GetWindowViewInfo();

	//	Fix range or scale.
	double dScale	= m_dScale * pScene->GetZoomScale();
	qreal dOffset	= 0.;

	QPen pen(getGridLineColor());
	pen.setWidth(getGridLineWidth());
	pen.setStyle(getGridLineStyle());
	painter->setPen(pen);

	if(!m_bFixScale)
	{
		qreal dLength = pScene->GetCanvasWidth();
		dScale = dLength / (pWViewInfo->m_dHMaxValue - pWViewInfo->m_dHMinValue);
		if(!m_bHorizontal)
		{
			dLength = pScene->GetCanvasHeight();
			dScale = dLength / (pWViewInfo->m_dVMaxValue - pWViewInfo->m_dVMinValue);
		}
	}

	if(m_bHorizontal)
	{
		//	Horizontal axis.
		qreal dX = 0;
		dOffset = pScene->GetMoveOffset().x();
		if(dOffset > 0)
		{
			dX = 0 - (int)(dOffset / (pWViewInfo->m_dHStep * dScale)) * pWViewInfo->m_dHStep;
		}

		while(1 && pWViewInfo->m_dHStep != 0)
		{
			qreal dTipX = dX * dScale + dOffset;

			if(dTipX < 0)
			{
				dX += pWViewInfo->m_dHStep;
				continue;
			}

			if(dTipX > pScene->GetCanvasWidth() + 1)
				break;

			if(isCrossed())
				painter->drawLine(dTipX, -5, dTipX, 5 + pScene->GetCanvasHeight());
			else if(m_bTopLeft)
				painter->drawLine(dTipX, -5, dTipX, 0);
			else
				painter->drawLine(dTipX, pScene->GetCanvasHeight(), dTipX, 5 + pScene->GetCanvasHeight());

			if(m_bTopLeft)
			{
			}
			else
				painter->drawText(QRectF(dTipX - 5, pScene->GetCanvasHeight() + 10, 60, 20), Qt::AlignLeft, QString::number(dX + pWViewInfo->m_dHMinValue));

			dX += pWViewInfo->m_dHStep;
		}
	}
	else
	{
		//	Vertical axis.
		qreal dY = 0;
		dOffset = pScene->GetMoveOffset().y();
		if(dOffset < 0)
		{
			dY = (int)(dOffset / (pWViewInfo->m_dVStep * dScale)) * pWViewInfo->m_dVStep;
		}
		qreal dHeight = pScene->GetCanvasHeight();
		while(1)
		{
			qreal dTipY = dHeight - dY * dScale + dOffset;

			if(dTipY > dHeight)
			{
				dY += pWViewInfo->m_dVStep;
				continue;
			}

			if(dTipY < 0)
				break;

			if(isCrossed())
				painter->drawLine(-5, dTipY, pScene->GetCanvasWidth() + 5, dTipY);
			else if(m_bTopLeft)
				painter->drawLine(-5, dTipY, 0, dTipY);
			else
				painter->drawLine(pScene->GetCanvasWidth(), dTipY, pScene->GetCanvasWidth() + 5, dTipY);

			if(m_bTopLeft)
				painter->drawText(QRectF(-100, dTipY - 5, 90, 20), Qt::AlignRight, QString::number(dY + pWViewInfo->m_dVMinValue));
			else
				painter->drawText(QRectF(pScene->GetCanvasWidth() + 10, dTipY - 5, 90, 20), Qt::AlignLeft, QString::number(dY + pWViewInfo->m_dVMinValue));

			dY += pWViewInfo->m_dVStep;
		}
	}
}