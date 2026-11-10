#ifndef XDLGCALSH_H
#define XDLGCALSH_H

#include <QDialog>
#include "ui_xdlgcalsh.h"
#include "xguiplus_global.h"

class CXObject;

class XGUIPLUS_EXPORT XDlgCalSH : public QDialog
{
	Q_OBJECT

public:
	XDlgCalSH(CXObject *, QWidget *parent = 0);
	~XDlgCalSH();

private slots:
	virtual void accept();

private:
	void initUI();

	Ui::XDlgCalSH ui;

	CXObject *m_pParent;
};

#endif // XDLGCALSH_H
