#pragma once

#include <QDialog>
#include "ui_xdlgabout.h"
#include "xguiplus_global.h"

class XGUIPLUS_EXPORT XDlgAbout : public QDialog
{
	Q_OBJECT

public:
	XDlgAbout(QWidget *parent = Q_NULLPTR);
	~XDlgAbout();

private:
	Ui::XDlgAbout ui;
};
