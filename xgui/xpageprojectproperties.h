#ifndef XPAGEPROJECTPROPERTIES_H
#define XPAGEPROJECTPROPERTIES_H

#include "ui_xpageprojectproperties.h"
#include "xbasepropertypage.h"

/*!
 *	@brief	Misc. page of project properties dialog.
 *	@author	pezy
 *	@date	2015-10-12
 *	@see
 */

class CXPageProjectProperties : public CXBasePropertyPage
{
	Q_OBJECT

public:
	CXPageProjectProperties(QWidget *parent = 0);
	~CXPageProjectProperties();

	virtual void Apply() override;

private slots:
	void slotEnableAutoSave(int state);
	void slotVacuumProjectDataBase();

private:
	Ui::CXPageProjectProperties m_ui;
};

#endif // KEPAGEPROJECTPROPERTIES_H
