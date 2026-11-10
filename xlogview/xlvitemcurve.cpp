#include <qpainter.h>
#include <qpainterpath.h>
#include <qbitmap.h>
#include "xlvitemcurve.h"
#include "xlvitemwell.h"
#include "xlvscene.h"
#include "xlvwindowinfo.h"
#include "xviewinfolpcurve.h"
#include "xviewinfolpwell.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "xglobal.h"
#include "xtypecombo.h"

CXLVItemCurve::CXLVItemCurve(CXLVScene *pScene, QUuid objectID, CXViewInfoObject *pViewInfo, QGraphicsRectItem *pWItem)
	: QGraphicsRectItem(pWItem), m_objectID(objectID), m_pScene(pScene)
{
	m_pWinInfo = (CXLVWindowInfo *)m_pScene->GetWindowViewInfo();
	m_pViewInfo = (CXViewInfoLPCurve *)pViewInfo;
	Configure();
}

void CXLVItemCurve::Configure()
{
	CXLVItemWell *pWItem = (CXLVItemWell *)parentItem();
	qreal width = m_pWinInfo->m_dTrackWidth;
	QRectF wellRect = pWItem->rect();
	setRect(wellRect.right(), wellRect.top() + m_pWinInfo->m_iHeaderHeight, m_pWinInfo->m_dTrackWidth, pWItem->boundingRect().height() - m_pWinInfo->m_iHeaderHeight);

	wellRect.setRight(wellRect.right() + m_pWinInfo->m_dTrackWidth);
	pWItem->setRect(wellRect);

	m_polyline.clear();
	CXWellCurve *pCurve = (CXWellCurve *)::GetObjectByID(m_objectID);
	CXWell *pWell = (CXWell *)pCurve->GetParent();
	qreal dStep = pWell->GetWellStep();

	//pWell->GetDepthRange(m_dStart, m_dStop);
	CXViewInfoLPWell *pWViewInfo = pWItem->GetWellViewInfo();
	m_dStart = pWViewInfo->GetStartDepth();
	m_dStop = pWViewInfo->GetEndDepth();
	int iNum = (m_dStop - m_dStart) / dStep + 1.9;
	if (iNum <= 0)
		return;

	double dMin = m_pViewInfo->GetDisplayDataMin();
	double dMax = m_pViewInfo->GetDisplayDataMax();
	double dSpan = (dMax - dMin);
	if (qAbs(dSpan) <= 0.000001)
		return;

	double *pData = new double[iNum];
	pCurve->GetData(pData, m_dStart, iNum);

	qreal x, y;
	QRectF rect = this->rect();
	if (m_pViewInfo->GetBLogScale())
	{
		qreal dHScale = rect.width() / (log10(dMax) - log10(dMin));
		qreal dLgMin = log10(dMin);
		for (int i = 0; i < iNum; i++)
		{
			if (pData[i] == ::g_dInvalidData)
				continue;

			if (pData[i] < dMin)
				x = rect.x();
			else
				x = rect.x() + (log10(pData[i]) - dLgMin) * dHScale;
			y = rect.y() + m_pWinInfo->m_iHeaderHeight + i * dStep * m_pWinInfo->m_dVScale;

			m_polyline << QPointF(x, y);
		}
	}
	else
	{
		for (int i = 0; i < iNum; i++)
		{
			if (pData[i] == ::g_dInvalidData)
				continue;

			x = rect.x() + rect.width() * (pData[i] - dMin) / dSpan;
			y = rect.y() + m_pWinInfo->m_iHeaderHeight + i * dStep * m_pWinInfo->m_dVScale;

			m_polyline << QPointF(x, y);
		}
	}

	delete[]pData;

	//	Now begin to calculate the filling polygons.
	QPolygonF polygon;
	x = m_pViewInfo->GetFillFrom();
	if (x != ::g_dInvalidData)
	{
		if (m_pViewInfo->GetBLogScale())
			x = rect.x() + (log10(x) - log10(dMin)) * rect.width() / (log10(dMax) - log10(dMin));
		else
			x = rect.x() + rect.width() * (x - dMin) / dSpan;

		foreach(QPointF point, m_polyline)
		{
			if ((point.x() - x) * dSpan > 0)
			{
				if (polygon.isEmpty())
				{
					//	The first point, add one point on the prepend line.
					QPointF p(x, point.y());
					polygon << p;
				}

				polygon << point;
			}
			else
			{
				if (!polygon.isEmpty())
				{
					//	Add one point on the prepend line.
					QPointF p(x, point.y());
					polygon << p;

					//	Store the polygon.
					m_vecFFPolygon << polygon;
					polygon.clear();
				}
			}
		}

		if (!polygon.isEmpty())
		{
			//	Add one point on the prepend line.
			QPointF p(x, polygon.last().y());
			polygon << p;

			//	Store the polygon.
			m_vecFFPolygon << polygon;
			polygon.clear();
		}
	}

	x = m_pViewInfo->GetFillTo();
	if (x != ::g_dInvalidData)
	{
		if (m_pViewInfo->GetBLogScale())
			x = rect.x() + (log10(x) - log10(dMin)) * rect.width() / (log10(dMax) - log10(dMin));
		else
			x = rect.x() + rect.width() * (x - dMin) / dSpan;

		foreach(QPointF point, m_polyline)
		{
			if ((point.x() - x) * dSpan < 0)
			{
				if (polygon.isEmpty())
				{
					//	The first point, add one point on the prepend line.
					QPointF p(x, point.y());
					polygon << p;
				}

				polygon << point;
			}
			else
			{
				if (!polygon.isEmpty())
				{
					//	Add one point on the prepend line.
					QPointF p(x, point.y());
					polygon << p;

					//	Store the polygon.
					m_vecFTPolygon << polygon;
					polygon.clear();
				}
			}
		}

		if (!polygon.isEmpty())
		{
			//	Add one point on the prepend line.
			QPointF p(x, polygon.last().y());
			polygon << p;

			//	Store the polygon.
			m_vecFTPolygon << polygon;
			polygon.clear();
		}
	}
}

bool CXLVItemCurve::GetValue(qreal oriy, qreal& dDepth, qreal& dValue)
{
	QRectF rect = this->rect();
	qreal y = oriy - rect.y() - m_pWinInfo->m_iHeaderHeight;
	if (y < 0)
		return false;

	dDepth = (m_dStop - m_dStart) * y / (rect.height() - m_pWinInfo->m_iHeaderHeight) + m_dStart;

	dValue = -999.25;
	if (!m_polyline.isEmpty())
	{
		qreal sY = m_polyline.first().y();
		qreal eY = m_polyline.last().y();

		if (oriy < sY || oriy > eY)
			return true;

		int iIDX = (int)(m_polyline.size() * (oriy - sY) / (eY - sY) + 0.5);
		iIDX = qBound(0, iIDX, m_polyline.size() - 1);
		dValue = m_polyline.at(iIDX).x();
		double dMin = m_pViewInfo->GetDisplayDataMin();
		double dMax = m_pViewInfo->GetDisplayDataMax();
		if (m_pViewInfo->GetBLogScale())
		{
			qreal dHScale = rect.width() / (log10(dMax) - log10(dMin));
			qreal dLgMin = log10(dMin);
			dValue = pow(10, (dValue - rect.x()) / dHScale + dLgMin);
		}
		else
			dValue = dMin + (dMax - dMin) * (dValue - rect.x()) / rect.width();

		return true;
	}
	return false;
}

void CXLVItemCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QRectF rect = this->rect();

	painter->drawRect(rect.toRect());

	drawHeader(painter);
	if(m_pWinInfo->m_bShowBinGrid)
		drawGrid(painter);
	drawCurve(painter);
}

void CXLVItemCurve::drawHeader(QPainter *painter)
{
	painter->save();
	QRectF rect = this->rect();
	rect.setBottom(rect.top() + m_pWinInfo->m_iHeaderHeight);
	painter->setBrush(QBrush(QColor("lightGray")));
	painter->drawRect(rect.toRect());

	rect.setBottom(rect.top() + rect.height() / 2);
	painter->drawText(rect, Qt::AlignCenter, ::GetObjectByID(m_objectID)->GetObjectName());

	double dMin = m_pViewInfo->GetDisplayDataMin();
	double dMax = m_pViewInfo->GetDisplayDataMax();
	rect.moveTop(rect.bottom());
	painter->drawText(rect, Qt::AlignLeft, " " + QString::number(dMin));
	painter->drawText(rect, Qt::AlignRight, QString::number(dMax) + " ");
	painter->setPen(QPen(m_pViewInfo->GetColor(), 2));
	painter->drawLine(rect.x() + 35, rect.center().y(), rect.right() - 35, rect.center().y());
	painter->restore();
}

void CXLVItemCurve::drawGrid(QPainter *painter)
{
	painter->save();
	painter->setPen(QPen(Qt::lightGray, 1));
	QRectF rect = this->rect();

	int iZ = ((int)(m_dStart / 100) + 1) * 100;
	while (iZ < m_dStop)
	{
		qreal y = (iZ - m_dStart) * m_pWinInfo->m_dVScale + rect.y() + m_pWinInfo->m_iHeaderHeight;
		painter->drawLine(rect.x(), y, rect.right(), y);
		iZ += 100;
	}

	if (m_pViewInfo->GetBLogScale())
	{
		int i, iStart = -999, iStop, j;
		double dMin = m_pViewInfo->GetDisplayDataMin();
		double dMax = m_pViewInfo->GetDisplayDataMax();

		for (i = -3; ; i++)
		{
			if (pow(10., i) > dMin && iStart == -999)
			{
				iStart = i - 1;
			}

			if (pow(10., i) > dMax)
			{
				iStop = i - 1;
				break;
			}
		}
		qreal dHScale = rect.width() / (log10(dMax) - log10(dMin));
		for (i = iStart; i <= iStop; i++)
		{
			for (j = 1; j <= 10; j++)
			{
				double dVal = (double)(pow(10., i) * j);

				if (dVal < dMin)
					continue;

				if (dVal > dMax)
					break;

				qreal fX = rect.x() + (log10(dVal) - log10(dMin)) * dHScale;
				painter->drawLine(fX, rect.y() + m_pWinInfo->m_iHeaderHeight, fX, rect.bottom());
			}
		}
	}
	else
	{
		for (int i = 1; i < 4; i++)
		{
			qreal x = rect.x() + i * rect.width() / 4;
			painter->drawLine(x, rect.y() + m_pWinInfo->m_iHeaderHeight, x, rect.bottom());
		}
	}

	painter->restore();
}

void CXLVItemCurve::drawCurve(QPainter *painter)
{
	if (m_polyline.isEmpty())
		return;

	QRectF rect = this->rect();
	painter->setClipRect(rect);

	if (!m_vecFFPolygon.isEmpty())
	{
		painter->save();
		int iPattern = m_pViewInfo->GetFFPattern();
		if (iPattern == 0)
			painter->setBrush(QBrush(QColor(m_pViewInfo->GetFFColor())));
		else
		{
			QPixmap pixmap = CXTypeCombo::GetPatternPixmap(iPattern);
			int nWidth = pixmap.width();
			int nHeight = pixmap.height();

			QImage image(QSize(nWidth, nHeight), QImage::Format_ARGB32);
			image.fill(0x00000000);
			QColor color = m_pViewInfo->GetFFColor();
			QBitmap bitmap = QBitmap::fromImage(pixmap.toImage());
			QBrush Bgr(bitmap);
			QPainter paintImage(&image);
			paintImage.fillRect(0, 0, nWidth, nHeight, color);
			paintImage.fillRect(0, 0, nWidth, nHeight, Bgr);

			QBrush paintBrush(image);
			painter->setBrush(paintBrush);
		}

		foreach(QPolygonF polygon, m_vecFFPolygon)
		{
			painter->drawPolygon(polygon);
		}
		painter->restore();
	}

	if (!m_vecFTPolygon.isEmpty())
	{
		painter->save();
		int iPattern = m_pViewInfo->GetFTPattern();
		if (iPattern == 0)
			painter->setBrush(QBrush(QColor(m_pViewInfo->GetFTColor())));
		else
		{
			QPixmap pixmap = CXTypeCombo::GetPatternPixmap(iPattern);
			int nWidth = pixmap.width();
			int nHeight = pixmap.height();

			QImage image(QSize(nWidth, nHeight), QImage::Format_ARGB32);
			image.fill(0x00000000);
			QColor color = m_pViewInfo->GetFTColor();
			QBitmap bitmap = QBitmap::fromImage(pixmap.toImage());
			QBrush Bgr(bitmap);
			QPainter paintImage(&image);
			paintImage.fillRect(0, 0, nWidth, nHeight, color);
			paintImage.fillRect(0, 0, nWidth, nHeight, Bgr);

			QBrush paintBrush(image);
			painter->setBrush(paintBrush);
		}

		foreach(QPolygonF polygon, m_vecFTPolygon)
		{
			painter->drawPolygon(polygon);
		}
		painter->restore();
	}

	QPen pen(m_pViewInfo->GetColor());
	pen.setWidth(m_pViewInfo->GetLineWidth());
	pen.setStyle((Qt::PenStyle)(m_pViewInfo->GetLineStyle()));
	painter->setPen(pen);
	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->drawPolyline(m_polyline);
}