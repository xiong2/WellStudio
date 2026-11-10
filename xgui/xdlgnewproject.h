#ifndef _CXDLGNEWPROJECT_H__
#define _CXDLGNEWPROJECT_H__

#include <qdialog.h>
#include "xgui_global.h"
#include "ui_xnewproject.h"

class CXProject;

class XGUI_EXPORT CXDlgNewProject: public QDialog
{
	Q_OBJECT

public:
	CXDlgNewProject(QWidget *parent = 0);
	CXProject*	GetProject()
	{
		return m_pProject;
	}

public slots:
	void accept();
	void slotSelectDir();

protected:

	bool checkName(QString);
	
	Ui::NewProject ui;

	CXProject*		m_pProject;

private:
	void _InitProjectName();
};

#endif