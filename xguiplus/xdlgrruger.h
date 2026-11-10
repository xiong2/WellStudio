#ifndef CXDLGRRUGER_H
#define CXDLGRRUGER_H

#include <QDialog>
#include <QPointer>
#include "ui_xdlgrruger.h"
#include "xguiplus_global.h"
#include <qpointer.h>

class CXWidgetRCCurve;
class CXWidget3DSurface;

using std::vector;

class XGUIPLUS_EXPORT CXDlgRruger : public QDialog
{
	Q_OBJECT

public:
	CXDlgRruger(QWidget *parent = Q_NULLPTR);
	~CXDlgRruger();

private Q_SLOTS:
	void slotRun();
	void slotUpdate(int, int);
	void slotVisible(bool bVisible);
	void slotDefaultSize();

private:
	void _Init();
	void _ConnectSignals();
	void _GetParameter();
	void _GetRangePara();

	void _GenerataDataForSurface(int iIndex, float*& pData, int& m, int& n);

	std::vector<double> _GetTableDataSet(QTableWidget *pTable);

	void _GenerateDataForCurvesAlongAzi(int iIndex, vector<double>& vecAzi, vector<double>& vecInc, vector<vector<double>>& vecRC);
	void _GenerateDataForCurvesAlongInc(int iIndex, vector<double>& vecInc, vector<double>& vecAzi, vector<vector<double>>& vecRC);

private:
	struct RangePara
	{
		double dIncStart, dIncEnd, dIncInterval;
		double dAziStart, dAziEnd, dAziInterval;
	};

private:
	Ui::CXDlgRruger m_ui;

	QPointer<CXWidgetRCCurve> m_pWidgetCurve;
	QPointer<CXWidget3DSurface> m_pWidget3DSurface;

	QMap<int, vector<double>> m_mapPara;

	RangePara m_rangeAzi, m_rangeInc;

	QList<QTableWidget*> m_listTables;
	QList<QGroupBox*> m_listBox;
};

#endif // CXDLGRRUGER_H
