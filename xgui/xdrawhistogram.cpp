#include "xdrawhistogram.h"
#include "xpagehistogram.h"
#include "xobject.h"
#include <assert.h>
#include <QPainter>
#include <QWheelEvent>
#include "xaxis.h"
#include "xautogrid.h"
#include "xutility.h"
#include <algorithm>

CXDrawHistogram::CXDrawHistogram(QWidget *parent) : QFrame(parent)
{
}

CXDrawHistogram::~CXDrawHistogram()
{
}

void CXDrawHistogram::SetHistogram(const CXHistogram & histogram)
{
	m_histogram = histogram;
}

void CXDrawHistogram::slotSetInterval(const QString& strInterval)
{
	m_dBinWidth = strInterval.toDouble();

	double dTruncMin = CXAutoGrid::Trunc(m_histogram.m_dDataMin);
	double dTruncMax = CXAutoGrid::Trunc(m_histogram.m_dDataMax);

	m_vecX.clear();
	m_vecY.clear();

	for (double d = dTruncMin; d < dTruncMax; d += m_dBinWidth)
	{
		m_vecX.push_back(d + m_dBinWidth / 2);
	}

	const std::vector<double>& vecX = m_histogram.m_vecHorizontal;
	const std::vector<double>& vecY = m_histogram.m_vecVertical;

	for (decltype(m_vecX.size()) i = 0; i != m_vecX.size(); ++i)
	{
		if (0 == i)
		{
			auto iterUpperX = std::upper_bound(vecX.cbegin(), vecX.cend(), m_vecX.at(i));
			auto iterUpperY = std::next(vecY.cbegin(), std::distance(vecX.cbegin(), iterUpperX));
			
			m_vecY.push_back(std::accumulate(vecY.cbegin(), iterUpperY, 0.0));
		}
		else
		{
			auto iterLowerX = std::lower_bound(vecX.cbegin(), vecX.cend(), m_vecX.at(i - 1));
			auto iterUpperX = std::upper_bound(vecX.cbegin(), vecX.cend(), m_vecX.at(i));
			auto iterLowerY = std::next(vecY.cbegin(), std::distance(vecX.cbegin(), iterLowerX));
			auto iterUpperY = std::next(vecY.cbegin(), std::distance(vecX.cbegin(), iterUpperX));

			m_vecY.push_back(std::accumulate(iterLowerY, iterUpperY, 0.0));
		}
	}

	// the remainder.
	auto iterLastX = std::lower_bound(vecX.cbegin(), vecX.cend(), m_vecX.back());
	auto iterLastY = std::next(vecY.cbegin(), std::distance(vecX.cbegin(), iterLastX));

	m_vecY.back() += std::accumulate(iterLastY, vecY.cend(), 0.0);

	update();
}

void CXDrawHistogram::slotSetNum(const QString& strNum)
{
	int nNum = strNum.toInt();
	int nSpan = m_histogram.HISTSIZE / nNum;

	m_vecX.clear();
	m_vecY.clear();
	m_vecX.resize(nNum);
	m_vecY.resize(nNum);

	for (int i = 0; i != 256; ++i)
	{
		m_vecX[i / nSpan] += m_histogram.m_vecHorizontal.at(i);
		m_vecY[i / nSpan] += m_histogram.m_vecVertical.at(i);
	}

	std::for_each(m_vecX.begin(), m_vecX.end(), [nSpan](double& dX) { dX /= nSpan; }); // average.

	Q_ASSERT(m_vecX.size() >= 2);

	m_dBinWidth = (m_vecX.at(1) - m_vecX.at(0)) * 0.9;

	update();
}

void CXDrawHistogram::slotYRepresentationChanged(int iIndex)
{
	m_bYNumber = iIndex == 1;

	update();
}

void CXDrawHistogram::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	m_rect = this->geometry();
	painter.drawText(m_rect.adjusted(15, 0, 0, 0), Qt::AlignLeft, m_bYNumber ? "N" : "%");
	m_rect.adjust(30, 0, -20, -39);
	painter.drawRect(m_rect);

	if (!m_pAxisX)
	{
		m_pAxisX = new CXAxis(m_histogram.m_dDataMin, m_histogram.m_dDataMax);
		m_pAxisX->SetAxisType(CXAxis::XAxis);
	}

	if (!m_pAxisY)
	{
		m_pAxisY = new CXAxis(0, 100);
	}

	m_pAxisX->SetSceneRect(m_rect);
	m_pAxisY->SetSceneRect(m_rect);

	_DrawXAxis(&painter, m_rect);
	_DrawYAxis(&painter, m_rect);

	painter.setClipRect(m_rect);

	_DrawHistogram(&painter, m_rect);
	_DrawAnnotation(&painter, m_rect);
}

void CXDrawHistogram::_DrawXAxis(QPainter *painter, QRect rect)
{
	m_pAxisX->calculatorGroundTickInterval();
	int nTickCount = m_pAxisX->GetTickCount();
	if (nTickCount < 1)
		return;

	painter->save();

	for (int i = 0; i <= nTickCount; ++i)
	{
		double dDepth = m_pAxisX->GetGroundGradValue(i);
		int  iScenePos = m_pAxisX->MapGroundToScene(dDepth);
		QString strTickValue = CXAutoGrid::TrimToString(dDepth);

		if (m_pAxisX->IsMainTick(dDepth))
		{
			painter->drawLine(iScenePos, rect.bottom() + 1, iScenePos, rect.bottom() + 5);
			QRect textRect = CXAutoGrid::TextRect(QFont(), strTickValue);
			painter->drawText(iScenePos - textRect.width() / 2, rect.bottom() + textRect.height() + 6, strTickValue);
		}
		else
		{
			painter->drawLine(iScenePos, rect.bottom() + 1, iScenePos, rect.bottom() + 3);
		}
	}

	painter->restore();
}

void CXDrawHistogram::_DrawYAxis(QPainter *painter, QRect rect)
{
	m_pAxisY->calculatorGroundTickInterval();
	int nTickCount = m_pAxisY->GetTickCount();
	if (nTickCount < 1)
		return;

	painter->save();

	for (int i = nTickCount; i >= 0; i--)
	{
		double dDepth = m_pAxisY->GetGroundGradValue(i);
		int  iScenePos = m_pAxisY->MapGroundToScene(dDepth, true);
		QString strTickValue = CXAutoGrid::TrimToString(m_bYNumber ? dDepth * m_histogram.m_nValidDataNum : dDepth * 100);

		if (m_pAxisY->IsMainTick(dDepth))
		{
			painter->drawLine(rect.x(), iScenePos, rect.x() - 5, iScenePos);
			QRect textRect = CXAutoGrid::TextRect(QFont(), strTickValue);
			painter->drawText(rect.x() - 7 - textRect.width(), iScenePos + textRect.height() / 2, strTickValue);
		}
		else
		{
			painter->drawLine(rect.x(), iScenePos, rect.x() - 2, iScenePos);
		}
	}

	painter->restore();
}

void CXDrawHistogram::_DrawHistogram(QPainter* painter, QRect rect)
{
	m_pAxisY->SetEnd(_GetSecondMaxValue(m_vecY) * 1.2);

	if (m_vecX.empty() || m_vecY.empty() || m_dBinWidth == 0.0)
		return;

	painter->save();
	
	for (decltype(m_vecX.size()) i = 0; i != m_vecX.size(); ++i)
	{
		int iPosY = m_pAxisY->MapGroundToScene(m_vecY.at(i), true);
		int iPosXL = m_pAxisX->MapGroundToScene(m_vecX.at(i) - m_dBinWidth / 2);
		int iPosXR = m_pAxisX->MapGroundToScene(m_vecX.at(i) + m_dBinWidth / 2);

		QRect rect(QPoint(iPosXL, iPosY), QPoint(iPosXR, rect.bottom()));
		painter->setPen(QPen(Qt::black, 2));
		painter->drawRect(rect);
		painter->fillRect(rect, QColor("green"));
	}

	painter->restore();
}

void CXDrawHistogram::_DrawAnnotation(QPainter * painter, QRect rect)
{
	QRect rectAnno = rect.adjusted(0, 5, -5, 0);

	painter->save();

	QFont font = painter->font();
	font.setPixelSize(13);
	painter->setFont(font);

	QRect rectValue = rectAnno.adjusted(0, 5, -5, 0);
	QRect boundingRect;
	int iWidthMax = 0;

	auto _DrawValue = [&](double dValue) 
	{
		painter->drawText(rectValue, Qt::AlignRight, QString("%1").arg(dValue, 0, 'f', 2), &boundingRect);
		rectValue.setTop(boundingRect.bottom());
		iWidthMax = qMax(iWidthMax, boundingRect.width());
	};

	_DrawValue(m_histogram.m_dDataMin);
	_DrawValue(m_histogram.m_dDataMax);
	_DrawValue(m_histogram.m_dMean);
	_DrawValue(m_histogram.m_dVariance);
	_DrawValue(m_histogram.m_dStd);
	_DrawValue(m_histogram.m_nValidDataNum);

	rectAnno.setBottom(boundingRect.bottom() + 5);

	QFontMetrics fontMetrics(font);
	int iWidthMaxTitle = fontMetrics.width("No. of Samples:");
	rectAnno.setLeft(rectValue.right() - iWidthMax - iWidthMaxTitle - 5);

	QRect rectTitle = rectAnno.adjusted(5, 5, 0, 0);

	auto _DrawTitle = [&](const QString& strTitle)
	{
		painter->drawText(rectTitle, Qt::AlignLeft, strTitle, &boundingRect);
		rectTitle.setTop(boundingRect.bottom());
	};

	_DrawTitle("Min Value:");
	_DrawTitle("Max Value:");
	_DrawTitle("Mean Value:");
	_DrawTitle("Variance:");
	_DrawTitle("Std.Dev:");
	_DrawTitle("No. of Samples:");

	painter->setPen(QPen(Qt::DotLine));
	painter->drawRect(rectAnno);

	painter->restore();
}

double CXDrawHistogram::_GetSecondMaxValue(const vector<double>& vec)
{
	if (vec.size() == 1)
		return vec.back();

	vector<double> vecExcludeMax = vec;
	auto iterMax = std::max_element(vecExcludeMax.begin(), vecExcludeMax.end());
	vecExcludeMax.erase(iterMax);

	return *std::max_element(vecExcludeMax.begin(), vecExcludeMax.end());
}

void CXDrawHistogram::_CalcBins()
{

}

void CXDrawHistogram::wheelEvent(QWheelEvent *event)
{
	int nDelta = event->delta() / 15;
	double dNewRange = nDelta * m_pAxisX->GetGroundTickInterval() + m_pAxisX->GetValueRange();
	m_pAxisX->Zoom(dNewRange);

	update();
}