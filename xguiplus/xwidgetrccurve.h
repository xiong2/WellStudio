#ifndef XWIDGETRCCURVE_H
#define XWIDGETRCCURVE_H

#include <QWidget>
#include <QPair>
#include <QMap>
#include <QChartGlobal>

/*!
 *	@class	CXWidgetRCCurve in the file "kewidgetrccurve.h"
 *	@brief	The class provide a widget for rendering 2-D RC curve.
 *	@author	pezy
 *	@date	2016-11-03
 */

QT_BEGIN_NAMESPACE
class QGridLayout;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE
using std::vector;

class CXWidgetRCCurve : public QWidget
{
	Q_OBJECT

public:
	CXWidgetRCCurve(QWidget *parent = Q_NULLPTR);
	~CXWidgetRCCurve();

	void AddCurve(int iRow, int iColumn, const vector<double>& vecX, const vector<double>& vecLines, const vector<vector<double>>& vecYs);
	void SetVisibility(int iIndex, bool bVisible);

private:
	void _Init();
	void _UpdateData(QChart* pChart, const vector<double>& vecX, const vector<double>& vecLines, const vector<vector<double>>& vecYs);

private:
	QList<QChartView *> m_listCharts;
	QGridLayout *m_pLayout;

	QMap<QPair<int, int>, QChart*> m_mapCharts;
};

#endif // KEWIDGETRCCURVE_H
