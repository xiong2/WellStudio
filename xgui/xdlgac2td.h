#pragma once

#include <QDialog>
#include "xgui_global.h"
#include "ui_xdlgac2td.h"

class CXWell;

class XGUI_EXPORT CXDlgAC2TD : public QDialog
{
	Q_OBJECT

public:
	CXDlgAC2TD(CXWell *, QWidget *parent = Q_NULLPTR);
	~CXDlgAC2TD();

	virtual void accept() override;

private slots:
	void slotSelAC(int);
	void slotCalculate();

private:
	void initUI();

	Ui::CXDlgAC2TD ui;

	CXWell*	m_pWell;
	double*	m_pBuff = NULL;
	int		m_iNum = 0;
};
