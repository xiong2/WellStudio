#ifndef XDLGWLINTEGRATION_H
#define XDLGWLINTEGRATION_H

#include <QDialog>
#include "xguiplus_global.h"
#include "ui_xdlgwlintegration.h"

class CXObject;
class CXWellCurve;

class XGUIPLUS_EXPORT XDlgWLIntegration : public QDialog
{
	Q_OBJECT

public:
	XDlgWLIntegration(CXObject *, QWidget *parent = 0);
	~XDlgWLIntegration();
	
public slots:
	virtual void accept();

private:
	Ui::XDlgWLIntegration ui;

	CXWellCurve*	m_pDenCurve;
};

#endif // XDLGWLINTEGRATION_H
