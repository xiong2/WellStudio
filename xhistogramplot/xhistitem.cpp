#include <qgraphicsscene.h>
#include <qpainter.h>
#include "xhistitem.h"
#include "xaxis.h"


CXHistItem::CXHistItem(const CXHistogram& histogram, QRectF rect, CXAxis *pXAxis, CXAxis *pYAxis, int iBinNum, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent), m_histogram(histogram)
{
	m_pAxisX = pXAxis;
	m_pAxisY = pYAxis;
	SetBinNum(iBinNum);
}

CXHistItem::~CXHistItem()
{
}

void CXHistItem::SetBinNum(int nNum)
{
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

double CXHistItem::Get2ndMaxValue()
{
	if (m_vecY.size() == 0)
		return 0.;

	if (m_vecY.size() == 1)
		return m_vecY.back();

	vector<double> vecExcludeMax = m_vecY;
	auto iterMax = std::max_element(vecExcludeMax.begin(), vecExcludeMax.end());
	vecExcludeMax.erase(iterMax);

	return *std::max_element(vecExcludeMax.begin(), vecExcludeMax.end());
}

void CXHistItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	if (m_vecX.empty() || m_vecY.empty() || m_dBinWidth == 0.0)
		return;
	
	QRectF rect = scene()->sceneRect();
	rect.adjust(70, 30, -30, -60);

	painter->save();
	painter->setClipRect(rect);

	for (decltype(m_vecX.size()) i = 0; i != m_vecX.size(); ++i)
	{
		int iPosY = m_pAxisY->MapGroundToScene(m_vecY.at(i), true);
		int iPosXL = m_pAxisX->MapGroundToScene(m_vecX.at(i) - m_dBinWidth / 2);
		int iPosXR = m_pAxisX->MapGroundToScene(m_vecX.at(i) + m_dBinWidth / 2);

		QRect rect(QPoint(iPosXL, iPosY), QPoint(iPosXR, rect.bottom()));
		painter->setPen(QPen(Qt::black, 2));
		painter->drawRect(rect);
		painter->fillRect(rect, m_color);
	}

	painter->restore();
}
