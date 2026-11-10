#pragma once

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgmergedv.h"

class CXObject;

class XGUIPLUS_EXPORT XDlgMergeDV : public QDialog
{
	Q_OBJECT

public:
	XDlgMergeDV(CXObject *, QWidget *parent = Q_NULLPTR);
	~XDlgMergeDV();

	void accept() override;

private slots:
	void slotDClickLColumn(QTableWidgetItem *);
	void slotCB();
	void slotButtonPress();
	void slotActiveRowChanged(int, int, int, int);

private:
	void initUI();

	//	Get all dv with the same sample rate and inline/xline inc.
	QStringList getCandidateDV(QUuid);

	Ui::XDlgMergeDV ui;

	CXObject*	m_pParent;
};
