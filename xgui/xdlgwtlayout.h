#pragma once

#include <QDialog>
#include "ui_xdlgwtlayout.h"

class CXDlgWellTie;

class XDlgWTLayout : public QDialog
{
	Q_OBJECT

public:
	XDlgWTLayout(CXDlgWellTie *parent);
	~XDlgWTLayout();

	void accept() override;

private:
	Ui::XDlgWTLayout ui;
};
