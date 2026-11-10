#include "xcolormapviewer.h"
#include <algorithm>    // std::find_if

#include <QPainter>
#include <cassert>
#include <QDebug>
#include <QWheelEvent>
#include <QMenu>
#include <QWidgetAction>
#include <QPropertyAnimation>

#include "xobject.h"
#include "xaxis.h"
#include "xautogrid.h"
#include "xcolormap.h"
#include "xbuttoncoloredit.h"
#include "xutility.h"

CXColormapViewer::CXColormapViewer(QWidget *parent)
	: QWidget(parent)
{
	m_menuEditColor = new QMenu(this);
	m_colorEdit = new CXButtonColorEdit(m_menuEditColor);
	QWidgetAction *actionEditColor = new QWidgetAction(m_menuEditColor);
	actionEditColor->setDefaultWidget(m_colorEdit);
	m_menuEditColor->addAction(actionEditColor);

	connect(m_colorEdit, SIGNAL(ColorSelected(const QColor&)), this, SLOT(slotColorEdited(const QColor&)));

	setMouseTracking(true);
	setMinimumHeight(250);
}

CXColormapViewer::~CXColormapViewer()
{	
}

void CXColormapViewer::Update()
{
	paintEvent(NULL);
}

void CXColormapViewer::SetDisplayedObject(CXObject* pObj)
{
	m_pObj = pObj;
	m_pObj->GetDataRange(m_dDisplayMinValue, m_dDisplayMaxValue);
	repaint();
}

void CXColormapViewer::SetDisplayedRange(double dMin, double dMax)
{
	m_dDisplayMinValue = dMin;
	m_dDisplayMaxValue = dMax;
	repaint();
}

void CXColormapViewer::SetColormap(QString colormapName)
{
	m_curColormap = CXColormap::GetColormap(colormapName);
	repaint();
}

void CXColormapViewer::paintEvent(QPaintEvent *event)
{
	/*!
	 * Draw the border of Histogram.
	 */
	QPainter painter(this);
	m_rect = this->rect();
	m_rect.adjust(30, 0, -15, -30);
	painter.drawRect(m_rect);

	if (!m_pObj) return;

	/*!
	 * Draw the Axis of Histogram
	 */
	QRect histogramRect = QRect(m_rect.left() - 1, m_rect.top(), m_rect.width() + 1, m_rect.height() - 22);
	if (m_XAxis == nullptr)
	{
		double dMin, dMax;
		m_pObj->GetDataRange(dMin, dMax);
		m_XAxis = new CXAxis(dMin, dMax, m_rect, 5);
		m_XAxis->SetAxisType(CXAxis::XAxis);
	}
	else
		m_XAxis->SetSceneRect(m_rect);

	if (m_YAxis == nullptr)
		m_YAxis = new CXAxis(0, 1, histogramRect);
	else
		m_YAxis->SetSceneRect(histogramRect);
	_drawXAxis(&painter, m_rect);
	_drawYAxis(&painter, histogramRect);

	painter.setClipRect(m_rect.left() - 1, m_rect.top(), m_rect.width() + 1, m_rect.height());
	_drawHistogram(&painter, histogramRect);
}

void CXColormapViewer::wheelEvent(QWheelEvent *event)
{
	if (!m_XAxis) return;

	int nDelta = event->delta() / 15;
	double dNewRange = nDelta*m_XAxis->GetGroundTickInterval() + m_XAxis->GetValueRange();

	m_XAxis->Zoom(dNewRange);
	update();

	event->accept();
}

void CXColormapViewer::slotDisplayMinChanged(const QString& strMin)
{
	m_dDisplayMinValue = qMin(strMin.toDouble(), m_dDisplayMaxValue);
	update();
}

void CXColormapViewer::slotDisplayMaxChanged(const QString& strMax)
{
	m_dDisplayMaxValue = qMax(strMax.toDouble(), m_dDisplayMinValue);
	update();
}

void CXColormapViewer::slotTemplateChanged(int index)
{
	m_curColormap = CXColormap::GetColormap(index);
	update();
}

void CXColormapViewer::_drawXAxis(QPainter *pDC, QRect rect)
{
	m_XAxis->calculatorGroundTickInterval();
	int nTickCount = m_XAxis->GetTickCount();
	if (nTickCount < 1) return;
	for (int i = 0; i != nTickCount; ++i)
	{
		double dDepth = m_XAxis->GetGroundGradValue(i);
		int  nSceneValue = m_XAxis->MapGroundToScene(dDepth);
		if (m_XAxis->IsMainTick(dDepth))
		{
			QString strTickValue = CXAutoGrid::TrimToString(dDepth);
			pDC->drawLine(nSceneValue, rect.bottom() + 1, nSceneValue, rect.bottom() + 5);
			QRect textRect = CXAutoGrid::TextRect(QFont(), strTickValue);
			pDC->drawText(nSceneValue - textRect.width() / 2, rect.bottom() + textRect.height() + 6, strTickValue);
		}
		else
		{
			pDC->drawLine(nSceneValue, rect.bottom() + 1, nSceneValue, rect.bottom() + 3);
		}
	}
}
void CXColormapViewer::_drawYAxis(QPainter *pDC, QRect rect)
{
	m_YAxis->calculatorGroundTickInterval();
	int nTickCount = m_YAxis->GetTickCount();
	if (nTickCount < 1) return;
	for (int i = nTickCount; i >= 0; i--)
	{
		double dDepth = m_YAxis->GetGroundGradValue(i);
		int  nSceneValue = m_YAxis->MapGroundToScene(dDepth, true);
		if (m_YAxis->IsMainTick(dDepth))
		{
			QString strTickValue = CXAutoGrid::TrimToString(dDepth * 100);
			pDC->drawLine(rect.x(), nSceneValue, rect.x() - 5, nSceneValue);
			QRect textRect = CXAutoGrid::TextRect(QFont(), strTickValue);
			pDC->drawText(rect.x() - 7 - textRect.width(), nSceneValue + textRect.height() / 2, strTickValue);
		}
		else
		{
			pDC->drawLine(rect.x(), nSceneValue, rect.x() - 2, nSceneValue);
		}
	}

}

void CXColormapViewer::SetStatic(bool bStatic)
{
	m_bStatic = bStatic;
}

void CXColormapViewer::_drawHistogram(QPainter* pDC, QRect rect)
{
	std::vector<double> vecHorizontal;
	std::vector<double> vecVertical, vecSortedVertical(256);
	m_pObj->GetHistogram(vecHorizontal, vecVertical);
	std::copy(vecVertical.begin(), vecVertical.end(), vecSortedVertical.begin());
	std::sort(vecSortedVertical.begin(), vecSortedVertical.end());
	double dSuitableMax = vecSortedVertical[254];

	m_YAxis->SetEnd(dSuitableMax * 1.25);

	if (!m_curColormap) return;

	int	minDisplayPos = m_XAxis->MapGroundToScene(m_dDisplayMinValue);
	int	maxDisplayPos = m_XAxis->MapGroundToScene(m_dDisplayMaxValue);
	int baseHeight = m_rect.top() + m_rect.height() - 10;
	double factor = (vecHorizontal[255] - vecHorizontal[0]) / (m_dDisplayMaxValue - m_dDisplayMinValue);

	QLinearGradient gradient(minDisplayPos, baseHeight, maxDisplayPos, baseHeight);
	if (m_bStatic)
	{
		gradient.setStart(m_rect.left(), baseHeight);
		gradient.setFinalStop(m_rect.right(), baseHeight);
	}

	// draw histogram
	for (int i = 0, j = 0; i != 256; ++i)
	{
		if (m_bCustom)
		{
			gradient.setColorAt(i / 255.0f, _getCustomColor(m_bReverse ? 255 - i : i));
		}
		else
		{
			gradient.setColorAt(i / 255.0f, m_curColormap->GetColorAt(static_cast<unsigned char>(m_bReverse ? 255 - i : i)));
		}
		if (i == 255) break;

		double dHorValue = vecHorizontal[i];
		double dVerValue = vecVertical[i];
		double dHorValueNext = vecHorizontal[i + 1];

		int nSenPosY = m_YAxis->MapGroundToScene(dVerValue, true);
		int nSenPosXL = m_XAxis->MapGroundToScene(dHorValue);
		int nSenPosXN = m_XAxis->MapGroundToScene(dHorValueNext);
		int nSenPosXR = 3 * (nSenPosXN - nSenPosXL) / 4 + nSenPosXL;

		QRect histogram_rect(QPoint(nSenPosXL, nSenPosY), QPoint(nSenPosXR, rect.bottom()));
		pDC->setPen(Qt::NoPen);

		int iCol = dHorValue < m_dDisplayMinValue ? 0 : dHorValue > m_dDisplayMaxValue ? 255 : qRound(factor*j++);
		if (m_bStatic)
		{
			iCol = i;
		}

		if (m_bCustom)
		{
			pDC->fillRect(histogram_rect, QBrush(_getCustomColor(m_bReverse ? 255 - iCol : iCol)));
		}
		else
		{
			pDC->fillRect(histogram_rect, QBrush(m_curColormap->GetColorAt(static_cast<unsigned char>(m_bReverse ? 255 - iCol : iCol))));
		}
	}

	// draw rianbow
	pDC->setRenderHint(QPainter::Antialiasing, true);
	pDC->setPen(QPen(QBrush(gradient), 20));

	if (m_bStatic)
	{
		pDC->drawLine(m_rect.left(), baseHeight, m_rect.right(), baseHeight);
	}
	else
	{
		pDC->drawLine(minDisplayPos, baseHeight, maxDisplayPos, baseHeight);
		if (rect.left() < minDisplayPos)
		{
			pDC->setPen(QPen(QBrush(m_curColormap->GetColorAt(m_bReverse?255:0)), 20));
			pDC->drawLine(m_rect.left(), baseHeight, minDisplayPos, baseHeight);
		}
		if (maxDisplayPos < m_rect.right())
		{
			pDC->setPen(QPen(QBrush(m_curColormap->GetColorAt(m_bReverse?0:255)), 20));
			pDC->drawLine(maxDisplayPos, baseHeight, m_rect.right(), baseHeight);
		}
	}

	// draw range line
	pDC->setPen(QPen(Qt::red, 3));
	pDC->drawLine(QPoint(minDisplayPos, m_rect.top()), QPoint(minDisplayPos, baseHeight - 13));
	pDC->drawLine(QPoint(maxDisplayPos, m_rect.top()), QPoint(maxDisplayPos, baseHeight - 13));
	pDC->setPen(QPen(QBrush(m_curColormap->GetColorAt(m_bReverse ? 255 : 0)), 3));
	pDC->drawLine(QPoint(minDisplayPos, baseHeight - 13), QPoint(minDisplayPos, baseHeight - 10));
	pDC->setPen(QPen(QBrush(m_curColormap->GetColorAt(m_bReverse ? 0 : 255)), 3));
	pDC->drawLine(QPoint(maxDisplayPos, baseHeight - 13), QPoint(maxDisplayPos, baseHeight - 10));

	// color edit
	QMapIterator<double, QColor> iter(m_mapColorMark);
	while (iter.hasNext())
	{
		iter.next();

		if (iter.key() > m_dDisplayMaxValue || iter.key() < m_dDisplayMinValue) continue;
		if (m_bReverse)
		{
			int iCol = qRound(255 * (iter.key() - m_dDisplayMinValue) / (m_dDisplayMaxValue - m_dDisplayMinValue));
			if (m_bCustom) pDC->setPen(QPen(_getCustomColor(255 - iCol), 3));
			else pDC->setPen(QPen(m_curColormap->GetColorAt(255 - iCol), 3));
		}
		else pDC->setPen(QPen(iter.value(), 3));
		int pos = m_XAxis->MapGroundToScene(iter.key());
		pDC->drawLine(QPoint(pos, m_rect.top()), QPoint(pos, baseHeight - 10));
	}
}

void CXColormapViewer::mouseMoveEvent(QMouseEvent *event)
{
	if (!m_XAxis) return;

	int minPos = m_XAxis->MapGroundToScene(m_dDisplayMinValue);
	int maxPos = m_XAxis->MapGroundToScene(m_dDisplayMaxValue);

	if (event->pos().x() >= minPos - 2 && event->pos().x() <= minPos + 2 ||
		event->pos().x() >= maxPos - 2 && event->pos().x() <= maxPos + 2 ||
		m_draggingLeft || m_draggingRight)
		setCursor(Qt::SizeHorCursor);
	else
		setCursor(QCursor());

	if (m_draggingLeft && m_rect.left() <= event->pos().x() && event->pos().x() <= maxPos)
		m_dDisplayMinValue = m_XAxis->MapSceneToGround(event->pos().x());
	else if (m_draggingRight && minPos <= event->pos().x() && event->pos().x() <= m_rect.right() + 1)
		m_dDisplayMaxValue = m_XAxis->MapSceneToGround(event->pos().x());

	emit DisplayedRangeChanged(m_dDisplayMinValue, m_dDisplayMaxValue);
	update();
}

void CXColormapViewer::mousePressEvent(QMouseEvent *event)
{
	if (!m_XAxis) return;

	QMap<double, QColor>::iterator iter;
	if (Qt::MiddleButton == event->button() && _hasInMarkMap(m_mapColorMark.begin(), m_mapColorMark.end(), iter))
	{
		m_mapColorMark.remove(iter.key());
		if (m_mapColorMark.empty()) m_bCustom = false;
		update();
		return;
	}

	int minPos = m_XAxis->MapGroundToScene(m_dDisplayMinValue);
	int maxPos = m_XAxis->MapGroundToScene(m_dDisplayMaxValue);

	if (event->pos().x() >= minPos - 1 && event->pos().x() <= minPos + 5)
		m_draggingLeft = true;
	else if (event->pos().x() >= maxPos - 5 && event->pos().x() <= maxPos + 1)
		m_draggingRight = true;
}

void CXColormapViewer::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_draggingLeft)
		m_draggingLeft = false;
	else if (m_draggingRight)
		m_draggingRight = false;
}

void CXColormapViewer::slotReset()
{
	if (!m_pObj || !m_XAxis) return;

	m_pObj->GetDataRange(m_dDisplayMinValue, m_dDisplayMaxValue);
	m_XAxis->Zoom(m_dDisplayMaxValue - m_dDisplayMinValue);
	update();
}

void CXColormapViewer::slotReverse(int state)
{
	if (state == Qt::Checked)
		m_bReverse = true;
	else if (state == Qt::Unchecked)
		m_bReverse = false;
	update();
}

void CXColormapViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (event->button() != Qt::LeftButton || !m_XAxis) return;

	int	minDisplayPos = m_XAxis->MapGroundToScene(m_dDisplayMinValue);
	int	maxDisplayPos = m_XAxis->MapGroundToScene(m_dDisplayMaxValue);

	if (event->pos().x() > minDisplayPos && event->pos().y() < maxDisplayPos)
	{
		double value = m_XAxis->MapSceneToGround(event->pos().x());
		int iCol = qRound(255.0 * (event->pos().x() - minDisplayPos) / (maxDisplayPos - minDisplayPos));
		if (m_bCustom) m_mapColorMark.insert(value, _getCustomColor(m_bReverse ? 255 - iCol : iCol));
		else m_mapColorMark.insert(value, m_curColormap->GetColorAt(static_cast<unsigned char>(m_bReverse ? 255 - iCol : iCol)));
	}
	update();
}

bool CXColormapViewer::_hasInMarkMap(QMap<double, QColor>::iterator iBeg, QMap<double, QColor>::iterator iEnd, QMap<double, QColor>::iterator& it)
{
	for (QMap<double, QColor>::iterator i = iBeg; i != iEnd; ++i)
	{
		int iPos = m_XAxis->MapGroundToScene(i.key());
		int iCursor = mapFromGlobal(cursor().pos()).x();
		if (iCursor - 2 < iPos && iPos < iCursor + 2)
		{
			it = i;
			return true;
		}
	}
	return false;
}

void CXColormapViewer::contextMenuEvent(QContextMenuEvent *)
{
	if (_hasInMarkMap(m_mapColorMark.begin(), m_mapColorMark.end(), m_iterCurrentEdit))
	{
		m_colorEdit->SetColor(CXButtonColorEdit::SelectColor, m_iterCurrentEdit.value());
		m_menuEditColor->exec(cursor().pos());
	}
}

void CXColormapViewer::slotColorEdited(const QColor& c)
{
	if (m_iterCurrentEdit.value() != c)
	{
		m_iterCurrentEdit.value() = c;
		m_bCustom = true;
		update();
		m_menuEditColor->hide();
	}
}

QColor CXColormapViewer::_getCustomColor(int pos) const
{
	QPropertyAnimation interpolator;
	interpolator.setEasingCurve(QEasingCurve::Linear);
	interpolator.setDuration(256);
	interpolator.setKeyValueAt(0, m_curColormap->GetColorAt(0));
	QMapIterator<double, QColor> iter(m_mapColorMark);
	while (iter.hasNext())
	{
		iter.next();
		qreal factor = (iter.key() - m_dDisplayMinValue) / (m_dDisplayMaxValue - m_dDisplayMinValue);
		interpolator.setKeyValueAt(factor, iter.value());
	}
	interpolator.setKeyValueAt(1, m_curColormap->GetColorAt(255));
	interpolator.setCurrentTime(pos);
	return interpolator.currentValue().value<QColor>();
}
