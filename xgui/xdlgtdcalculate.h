#pragma once

#include <QDialog>
#include "xgui_global.h"
#include "ui_xdlgtdcalculate.h"

class CXWell;
class CXWellTD;

class XGUI_EXPORT CXDlgTDCalculate : public QDialog
{
	Q_OBJECT

public:
	CXDlgTDCalculate(CXWell *, QWidget *parent = Q_NULLPTR);
	~CXDlgTDCalculate();

protected slots:
	void slotSelectTD();
	void slotImport();
	void slotCalculate();
	void slotSetAct();
	void slotDel();

private:
	void initUI();
	void initCurveTab();
	void populateTDModel(CXWellTD *);

	Ui::CXDlgTDCalculate ui;

	CXWell*	m_pWell;
};
