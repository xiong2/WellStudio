#ifndef XDLGCALBIOT_H
#define XDLGCALBIOT_H

#include <QWidget>
#include "ui_xdlgcalbiot.h"
#include "xguiplus_global.h"

class CXObject;

class XGUIPLUS_EXPORT XDlgCalBiot : public QDialog
{
	Q_OBJECT

public:
	XDlgCalBiot(CXObject *, QWidget *parent = 0);
	~XDlgCalBiot();

private slots:
	virtual void accept();

private:
	void initUI();

	Ui::XDlgCalBiot ui;

	CXObject *m_pParent;
};

#endif // XDLGCALBIOT_H
