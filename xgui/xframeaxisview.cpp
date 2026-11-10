#include "xframeaxisview.h"

#include <QWheelEvent>
#include <qpainter.h>

#include "xautogrid.h"

CXFrameAxisView::CXFrameAxisView(QWidget *parent)
	: QFrame(parent), m_pXAxis(nullptr), m_pYAxis(nullptr), m_dXMin(0.0), m_dYMin(0.0)
	, m_dXMax(0.0), m_dYMax(0.0), m_bGridEnabled(false), m_bYZoomEnabled(false)
{
}

QRect CXFrameAxisView::_UpdateAxies()
{
	QRect sceneRect = _CalcRect();
	_CalcXAxis(sceneRect);
	_CalcYAxis(sceneRect);

	return sceneRect;
}

void CXFrameAxisView::paintEvent(QPaintEvent *pPaintEvent)
{
	Q_UNUSED(pPaintEvent);

	if (m_dXMin == 0.0 && m_dYMin == 0.0 && m_dXMax == 0.0 && m_dYMax == 0.0)
		return;

	QPainter painter(this);
	QRect sceneRect = _UpdateAxies();

	_DrawGraphics(&painter, sceneRect);
	_DrawXAxis(&painter, sceneRect);
	_DrawYAxis(&painter, sceneRect);

	painter.drawRect(sceneRect);
	painter.setClipRect(sceneRect);
}

void CXFrameAxisView::_CalcXAxis(QRect sceneRect)
{
	if (!m_pXAxis)
	{
		m_pXAxis = new CXAxis(m_dXMin, m_dXMax);
		m_pXAxis->SetAxisType(CXAxis::XAxis);
	}
	else
	{
		m_pXAxis->SetBegin(m_dXMin);
		m_pXAxis->SetEnd(m_dXMax);
	}

	m_pXAxis->SetSceneRect(sceneRect);
	m_pXAxis->calculatorGroundTickInterval();
}

void CXFrameAxisView::_DrawXAxis(QPainter* pPainter, QRect sceneRect)
{
	int nTickCount = m_pXAxis->GetTickCount();
	if (nTickCount < 1) return;

	for (int i = 0; i <= nTickCount; ++i)
	{
		double dX = m_pXAxis->GetGroundGradValue(i);
		int x = m_pXAxis->MapGroundToScene(dX);
		
		if (m_pXAxis->IsMainTick(dX) || nTickCount < m_pXAxis->GetStepUnit())
		{
			QString xMark = CXAutoGrid::TrimToString(dX);
			QRect xMarkRect = CXAutoGrid::TextRect(font(), xMark);
			pPainter->drawLine(x, sceneRect.bottom() + 1, x, sceneRect.bottom() + 5);
			pPainter->drawText(x - xMarkRect.width() / 2, sceneRect.bottom() + xMarkRect.height() + 6, xMark);
			if (m_bGridEnabled)
			{
				pPainter->save();
				pPainter->setPen(QPen(Qt::lightGray, 1.0));
				pPainter->drawLine(x, sceneRect.bottom(), x, sceneRect.top());
				pPainter->restore();
			}
		}
		else
		{
			pPainter->drawLine(x, sceneRect.bottom() + 1, x, sceneRect.bottom() + 3);
		}
	}
}

void CXFrameAxisView::_CalcYAxis(QRect sceneRect)
{
	if (!m_pYAxis)
	{
		m_pYAxis = new CXAxis(m_dYMin, m_dYMax);
	}
	else
	{
		m_pYAxis->SetBegin(m_dYMin);
		m_pYAxis->SetEnd(m_dYMax);
	}

	m_pYAxis->SetSceneRect(sceneRect);
	m_pYAxis->calculatorGroundTickInterval();
}

void CXFrameAxisView::_DrawYAxis(QPainter* pPainter, QRect sceneRect)
{
	int nTickCount = m_pYAxis->GetTickCount();
	if (nTickCount < 1) return;

    for (int i = 0; i != nTickCount; ++i)
	{
		double dY = m_pYAxis->GetGroundGradValue(i);
		int y = m_pYAxis->MapGroundToScene(dY, true);
		if (m_pYAxis->IsMainTick(dY) || nTickCount < m_pYAxis->GetStepUnit())
		{
			QString yMark = CXAutoGrid::TrimToString(dY);
			pPainter->drawLine(sceneRect.x(), y, sceneRect.x() - 5, y);
			QRect textRect = CXAutoGrid::TextRect(font(), yMark);
			pPainter->drawText(sceneRect.x() - 7 - textRect.width(), y + textRect.height() / 2, yMark);
			if (m_bGridEnabled)
			{
				pPainter->save();
				pPainter->setPen(QPen(Qt::lightGray, 1));
				pPainter->drawLine(sceneRect.left(), y, sceneRect.right(), y);
				pPainter->restore();
			}
		}
		else
		{
			pPainter->drawLine(sceneRect.x(), y, sceneRect.x() - 2, y);
		}
	}
}

void CXFrameAxisView::wheelEvent(QWheelEvent* event)
{
	int nDelta = event->delta() / 15;
	double xNewRange = nDelta * m_pXAxis->GetGroundTickInterval() + m_pXAxis->GetValueRange();
	double yNewRange = nDelta * m_pYAxis->GetGroundTickInterval() + m_pYAxis->GetValueRange();
	m_pXAxis->Zoom(xNewRange);
	if (m_bYZoomEnabled) m_pYAxis->Zoom(yNewRange);
	
	repaint();
}

QRect CXFrameAxisView::_CalcRect()
{
	return rect().adjusted(m_iOffsetX, 30, -20, -30);
}