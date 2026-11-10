#ifndef XDLGPROJECTPROPERTIES_H
#define XDLGPROJECTPROPERTIES_H

#include <QDialog>
#include "ui_xdlgprojectproperties.h"
#include "xgui_global.h"

/*!
 *	@brief	the class define a dialog for project property
 *	@author	pezy
 *	@date	2015-10-09
 *	@see
 */

class CXPageProjectProperties;

class XGUI_EXPORT CXDlgProjectProperties : public QDialog
{
	Q_OBJECT

public:
	CXDlgProjectProperties(QWidget *parent = 0);
	~CXDlgProjectProperties();

private slots:
	void slotButtonClicked(QAbstractButton* pButton);

private:
	void _AddMiscPage();

	Ui::CXDlgProjectProperties m_ui;
	CXPageProjectProperties *m_pPageMisc;
};

#endif // KEDLGPROJECTPROPERTIES_H
