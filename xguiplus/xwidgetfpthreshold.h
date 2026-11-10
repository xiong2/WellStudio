#pragma once

#include <qwidget.h>
#include <QtCharts>
#include <qvector.h>
#include <qpoint.h>
#include <vector>
#include <map>


#include "xguiplus_global.h"

using std::vector;

class XGUIPLUS_EXPORT CXWidgetFPThreshold
{
public:
	CXWidgetFPThreshold(int nK, double dSamplingStart, double dSamplingRate);
	~CXWidgetFPThreshold();

	QChart* GetChart();

	void ClearData();

	void AddPoint(double x, double y);

	void GetXYThresholdArray(QList<double>& listX, QList<double>& listY);

private:
	int _GetDecimalNum();
	void _Init();

private:
	QLineSeries *m_pLineSeries;
	QScatterSeries *m_pPointSeries;
	QValueAxis *m_pXAxis, *m_pYAxis;
	QChart* m_pChart;

private:
	std::map<double, double> m_map;

private:
	int m_nK, m_nDecim;
	double m_dSamplingStart, m_dSamplingRate;

};

