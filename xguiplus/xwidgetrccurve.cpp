#include "xwidgetrccurve.h"

#include <QGridLayout>
#include <QChart>
#include <QChartView>
#include <QTime>
#include <QSplineSeries>
#include <QGridLayout>
#include <QValueAxis>

#include "xglobal.h"

CXWidgetRCCurve::CXWidgetRCCurve(QWidget *parent)
	: QWidget(parent, Qt::Window)
{
	setAttribute(Qt::WA_DeleteOnClose);

	_Init();
}

CXWidgetRCCurve::~CXWidgetRCCurve()
{

}

void CXWidgetRCCurve::AddCurve(int iRow, int iColumn, const vector<double>& vecX, const vector<double>& vecLines, const vector<vector<double>>& vecYs)
{
	QChart* pChart = m_mapCharts.value(qMakePair(iRow, iColumn), nullptr);
	if (!pChart)
	{
		// new chart
		pChart = new QChart;
		pChart->setTitle(QString("RC with %1").arg(iColumn ? "incident" : "Azimuth"));
		pChart->setTheme(QChart::ChartThemeHighContrast);

		QChartView *pChartView = new QChartView(pChart);
		pChartView->setRenderHint(QPainter::Antialiasing, true);

		m_pLayout->addWidget(pChartView, iRow, iColumn);

		m_mapCharts.insert(qMakePair(iRow, iColumn), pChart);
	}

	_UpdateData(pChart, vecX, vecLines, vecYs);
}

void CXWidgetRCCurve::SetVisibility(int iIndex, bool bVisible)
{
	auto pLeftView = m_pLayout->itemAtPosition(iIndex, 0);
	auto pRightView = m_pLayout->itemAtPosition(iIndex, 1);

	if (!pLeftView && !pRightView)
		return;

	pLeftView->widget()->setVisible(bVisible);
	pRightView->widget()->setVisible(bVisible);
}

void CXWidgetRCCurve::_Init()
{
	m_pLayout = new QGridLayout;
	m_pLayout->setColumnStretch(0, 1);
	m_pLayout->setColumnStretch(1, 1);
	setLayout(m_pLayout);
	setMinimumSize(1200, 400);
	m_mapCharts.clear();
}

void CXWidgetRCCurve::_UpdateData(QChart * pChart, const vector<double>& vecX, const vector<double>& vecLines, const vector<vector<double>>& vecYs)
{
	pChart->removeAllSeries();

	for (decltype(vecYs.size()) i = 0; i != vecYs.size(); ++i)
	{
		QSplineSeries* pSeries = new QSplineSeries;
		pSeries->setName(QString("%1 deg").arg(vecLines.at(i)));
		pSeries->setPen(QPen(::GetCurveColor(i), 1.5));

		for (decltype(vecX.size()) j = 0; j != vecX.size(); ++j)
		{
			pSeries->append(vecX.at(j), vecYs.at(i).at(j));
		}

		pChart->addSeries(pSeries);
	}

	pChart->createDefaultAxes();

	auto pAxisY = dynamic_cast<QValueAxis*>(pChart->axisY());
	qreal dBound = qMax(qAbs(pAxisY->min()), qAbs(pAxisY->max()));
	dBound *= 1.15;
	pAxisY->setRange(-dBound, dBound);
}
