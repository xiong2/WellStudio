#include "xpageloadsegyhistogram.h"

#include <qpainter.h>
#include "xutility.h"
#include "xautogrid.h"

CXPageLoadSegyHistogram::CXPageLoadSegyHistogram(QWidget *parent)
	: CXFrameAxisView(parent)
{

}

CXPageLoadSegyHistogram::~CXPageLoadSegyHistogram()
{

}

void CXPageLoadSegyHistogram::_DrawGraphics(QPainter *pDC, QRect& rect)
{
	const std::vector<double>& vecHorizontal = m_histogram.m_vecHorizontal;
	const std::vector<double>& vecVertical = m_histogram.m_vecVertical;

	for (int i = 0; i < vecHorizontal.size() - 1; i++)
	{
		double dYValue = vecVertical.at(i);
		double dXValue = vecHorizontal.at(i);
		double dXValueNext = vecHorizontal.at(i + 1);

		int nSenPosY = m_pYAxis->MapGroundToScene(dYValue, true);
		int nSenPosX = m_pXAxis->MapGroundToScene(dXValue);
		int nSenPosXNext = m_pXAxis->MapGroundToScene(dXValueNext);

		QRect rect(QPoint(nSenPosX, nSenPosY), QPoint(nSenPosXNext, rect.bottom()));
		pDC->save();
		pDC->setPen(Qt::NoPen);
		pDC->fillRect(rect, Qt::blue);
		pDC->restore();
	}
}

void CXPageLoadSegyHistogram::SetTraceData(float * pTraceData, int nSampleNumber)
{
	NXUtility::CalcHistogram(pTraceData, nSampleNumber, m_histogram);

	const std::vector<double>& vecVertical = m_histogram.m_vecVertical;
	double dMaxValue = *std::max_element(vecVertical.begin(), vecVertical.end());
	double dMinValue = *std::min_element(vecVertical.begin(), vecVertical.end());

	QString maxText = CXAutoGrid::TrimToString(dMaxValue);
	m_iOffsetX = CXAutoGrid::TextRect(font(), maxText).width();

	SetXAxisRange(m_histogram.m_dDataMin, m_histogram.m_dDataMax);
	SetYAxisRange(dMinValue, dMaxValue*1.05);
	repaint();
}