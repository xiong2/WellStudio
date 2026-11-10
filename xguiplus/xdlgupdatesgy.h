#pragma once

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgupdatesgy.h"

class CXSEGYLoadParameters;

class XGUIPLUS_EXPORT XDlgUpdateSGY : public QDialog
{
	Q_OBJECT

public:
	XDlgUpdateSGY(QWidget *parent = Q_NULLPTR);
	~XDlgUpdateSGY();

	void accept() override;

private slots:
	void slotBrowse();

private:
	Ui::XDlgUpdateSGY ui;
	CXSEGYLoadParameters *m_pPara = nullptr;

	void convertOneFile(QString sPath, QString sFile, int iID);
};
