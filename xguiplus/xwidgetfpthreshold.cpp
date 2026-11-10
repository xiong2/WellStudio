#pragma warning( push ,0 )
#include "xwidgetfpthreshold.h"


#pragma warning( pop 



CXWidgetFPThreshold::CXWidgetFPThreshold(int nK, double dSamplingStart, double dSamplingRate)
	:m_nK(nK), m_dSamplingStart(dSamplingStart), m_dSamplingRate(dSamplingRate)
{
	m_pChart = nullptr;

	m_pXAxis = nullptr;
	m_pYAxis = nullptr;

	m_nDecim = _GetDecimalNum();
	_Init();

	m_pChart->layout()->setContentsMargins(0, 0, 0, 0);
	m_pChart->setBackgroundRoundness(0);
	m_pChart->setVisible(false);
}

CXWidgetFPThreshold::~CXWidgetFPThreshold()
{
}

int CXWidgetFPThreshold::_GetDecimalNum()
{
	int n = 0;
	QString str = QString::number(m_dSamplingRate, 'f', 3);

	while (!str.isEmpty() && str.back() == '0')
		str = str.left(str.size() - 1);

	if (!str.isEmpty() && str.back() == '.')
		str = str.left(str.size() - 1);

	if (str.contains('.'))
	{
		int pos = str.indexOf('.');
		return qMax(1, str.size() - pos - 1);
	}

	str = QString::number(m_dSamplingStart, 'f', 3);

	while (!str.isEmpty() && str.back() == '0')
		str = str.left(str.size() - 1);

	if (!str.isEmpty() && str.back() == '.')
		str = str.left(str.size() - 1);

	if (str.contains('.'))
	{
		int pos = str.indexOf('.');
		return qMax(1, str.size() - pos - 1);
	}

	return 0;
}

void CXWidgetFPThreshold::_Init()
{
	m_pChart = new QChart();
	m_pChart->setTitle("Threshold");
	m_pChart->legend()->hide();

	m_pXAxis = new QValueAxis();
	m_pXAxis->setLinePenColor(Qt::black);
	//m_pXAxis->setRange(1, 10);
	//m_pXAxis->setTickCount(10);

	QString strFormat = "%5." + QString::number(m_nDecim) + "f";
	m_pXAxis->setLabelFormat(strFormat);

	m_pYAxis = new QValueAxis();
	m_pYAxis->setLinePenColor(Qt::black);

	m_pLineSeries = new QLineSeries();
	m_pLineSeries->setColor(Qt::blue);

	QPen pen(Qt::SolidLine);
	pen.setColor(Qt::blue);
	m_pLineSeries->setPen(pen);

	m_pPointSeries = new QScatterSeries();
	m_pPointSeries->setColor(Qt::red);
	m_pPointSeries->setMarkerShape(QScatterSeries::MarkerShapeRectangle);

	m_pChart->addSeries(m_pLineSeries);
	m_pChart->addSeries(m_pPointSeries);

	m_pChart->addAxis(m_pXAxis, Qt::AlignBottom);
	m_pChart->addAxis(m_pYAxis, Qt::AlignLeft);
	m_pXAxis->setTitleText("TWT");
	m_pYAxis->setTitleText("Threshold");

	m_pLineSeries->attachAxis(m_pXAxis);
	m_pLineSeries->attachAxis(m_pYAxis);

	m_pPointSeries->attachAxis(m_pXAxis);
	m_pPointSeries->attachAxis(m_pYAxis);

	double dStart = m_dSamplingStart - 5 * m_dSamplingRate;
	if (m_dSamplingStart >= 0 && dStart < 0)
		dStart = 0;

	double dStart_new = QString::number(dStart, 'f', m_nDecim).toDouble();
	double dEnd_new = QString::number(m_dSamplingStart + (m_nK - 1)*m_dSamplingRate, 'f', m_nDecim).toDouble();

	m_pXAxis->setRange(dStart_new, dEnd_new);
	m_pYAxis->setRange(0, 4);

	//m_pXAxis->setTickCount(1 + nStep);
}



void CXWidgetFPThreshold::ClearData()
{
	m_map.clear();

	m_pLineSeries->clear();
	m_pPointSeries->clear();

	//m_pChart->setVisible(false);
}

void CXWidgetFPThreshold::AddPoint(double x, double y)
{
	m_pChart->setVisible(true);
	
	m_map[x] = y;

	m_pLineSeries->clear();
	m_pPointSeries->clear();

	for (auto a : m_map)
	{
		m_pLineSeries->append(a.first, a.second);
		m_pPointSeries->append(a.first, a.second);
	}

	m_pChart->update();
}

QChart* CXWidgetFPThreshold::GetChart()
{
	return m_pChart;
}

void CXWidgetFPThreshold::GetXYThresholdArray(QList<double>& listX, QList<double>& listY)
{
	for (auto a : m_map)
	{
		double x = a.first;
		double y = a.second;

		double xi = static_cast<int>((x - m_dSamplingStart) / m_dSamplingRate + 0.1);
		listX.append(xi);
		listY.append(y);
	}
}