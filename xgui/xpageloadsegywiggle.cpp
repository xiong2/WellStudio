#include "xpageloadsegywiggle.h"
#include <QPainter>
#include "xautogrid.h"

CXPageLoadSegyWiggle::CXPageLoadSegyWiggle(QWidget *parent) : CXFrameAxisView(parent)
{
	SetGridEnable(true);
}

CXPageLoadSegyWiggle::~CXPageLoadSegyWiggle()
{

}

void CXPageLoadSegyWiggle::_DrawGraphics(QPainter *pDC, QRect& rect)
{
	if (!m_pTraceData)
		return;

	QPainterPath path;
	for (int i = 0; i != m_nSampleNumber; ++i)
	{
		int nPosY = m_pYAxis->MapGroundToScene(m_pTraceData[i], true);
		int nPosX = m_pXAxis->MapGroundToScene(i + 1);
		
		if (i == 0)
		{
			path.moveTo(nPosX, nPosY);
		}
		else
		{
			path.lineTo(nPosX, nPosY);
		}
	}

	pDC->save();
	pDC->setPen(QPen(Qt::blue));
	pDC->setRenderHint(QPainter::Antialiasing, true);
	pDC->drawPath(path);
	pDC->restore();
}

void CXPageLoadSegyWiggle::SetTraceData(float * pTraceData, int nSampleNumber)
{
	m_pTraceData = pTraceData;
	m_nSampleNumber = nSampleNumber;
	
	float fMin = *std::min_element(m_pTraceData, m_pTraceData + m_nSampleNumber);
	float fMax = *std::max_element(m_pTraceData, m_pTraceData + m_nSampleNumber);
	
	QString minText = CXAutoGrid::TrimToString(qRound(fMin));
	m_iOffsetX = CXAutoGrid::TextRect(font(), minText).width() + 20;

	SetXAxisRange(1, m_nSampleNumber + 3);
	SetYAxisRange(fMin*1.1, fMax*1.1);
	repaint();
}