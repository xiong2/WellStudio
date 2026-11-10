#include "xpageloadsegyutmview.h"

#include <qpainter.h>
#include "xautogrid.h"

CXPageLoadSegyUtmView::CXPageLoadSegyUtmView(QWidget *parent) : CXFrameAxisView(parent)
{
    SetGridEnable(true);
    SetYAxisZoomEnabled(false);
    m_squareGridRect.setSize(QSize(0, 0));
}

CXPageLoadSegyUtmView::~CXPageLoadSegyUtmView()
{

}

void CXPageLoadSegyUtmView::_DrawGraphics(QPainter* painter, QRect& rect)
{
    rect = _UpdateAxies();

    if (m_vecPoints.empty()) return;

    QPolygon polygon;
    for (decltype(m_vecPoints.size()) i = 0; i != m_vecPoints.size(); ++i)
    {
		QPoint pointScene(m_pXAxis->MapGroundToScene(m_vecPoints.at(i).x()), m_pYAxis->MapGroundToScene(m_vecPoints.at(i).y(), true));
        polygon.push_back(pointScene);
		painter->drawText(pointScene, QString("P%1").arg(m_vecIndex.at(i)));
    }
    polygon.push_back(polygon.front());
	std::swap(polygon[2], polygon[3]);

    painter->save();
    painter->setPen(QPen(Qt::blue, 2));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawPolygon(polygon);
    painter->restore();
}

QRect CXPageLoadSegyUtmView::_CalcRect()
{
    auto sceneRect = rect().adjusted(60, 20, -20, -20);

    if (!m_pXAxis || !m_pYAxis) return sceneRect;

    if (!m_squareGridRect.isEmpty()) return m_squareGridRect;

	m_pXAxis->SetStepUnit(m_pXAxis->GetStepUnit() * 1.5);
    auto nRangeX = m_pXAxis->GetEnd() - m_pXAxis->GetBegin();
    auto nRangeY = m_pYAxis->GetEnd() - m_pYAxis->GetBegin();

    auto d = qMin(sceneRect.width() / nRangeX, sceneRect.height() / nRangeY);

    m_squareGridRect.setRect(60, 20, nRangeX * d, nRangeY * d);

    return m_squareGridRect;
}

void CXPageLoadSegyUtmView::SetPoints(std::vector<QPointF> vecPoints, std::vector<int> vecIndex)
{
	Q_ASSERT(vecPoints.size() == vecIndex.size());

    m_vecPoints.swap(vecPoints);
	m_vecIndex.swap(vecIndex);

    std::vector<float> vecXpos;
    std::vector<float> vecYpos;
    for (const auto& point : m_vecPoints)
    {
        vecXpos.push_back(point.x());
        vecYpos.push_back(point.y());
    }

    float fXMinValue = *min_element(vecXpos.begin(), vecXpos.end());
    float fXMaxValue = *max_element(vecXpos.begin(), vecXpos.end());
    float fYMinValue = *min_element(vecYpos.begin(), vecYpos.end());
    float fYMaxValue = *max_element(vecYpos.begin(), vecYpos.end());
    float offsetX = (fXMaxValue - fXMinValue) / 8;
    float offsetY = (fYMaxValue - fYMinValue) / 8;

    SetXAxisRange(fXMinValue - offsetX, fXMaxValue + offsetX);
    SetYAxisRange(fYMinValue - offsetY, fYMaxValue + offsetY);
}
