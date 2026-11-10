#pragma once

#include <QDialog>
#include "ui_xdlgcpsetting.h"

class CXCrossPlotScene;

class XDlgCPSetting : public QDialog
{
	Q_OBJECT

public:
	XDlgCPSetting(CXCrossPlotScene *, QWidget *parent = Q_NULLPTR);
	~XDlgCPSetting();

	void accept() override;

protected slots:
	void slotTypeSelect();
	void slotCBC();
	void slotColorCB();
	void slotDepthLimit();
	bool slotApply();

private:
	void initGUI();
	void refreshHor();

	void refreshWellTable();
	void adjustWellTable();

	Ui::XDlgCPSetting ui;

	int			m_iDLType = 0;	//	0, no depth limit; 1, specify depth; 2 limit by tops.
	bool		m_bColorAxis = false;
	QStringList	m_sListCName;

	CXCrossPlotScene*	m_pScene;
};
