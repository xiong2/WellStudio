#ifndef _CXPAGEMATCHWELLS_H__
#define _CXPAGEMATCHWELLS_H__
#include "xgui_global.h"

#include <QWizardPage>
#include <qstringlist.h>
#include "ui_xpagewellmatch.h"

///@brief	A page to represent an ASCII file.
///@author	Xiong Xiong
///@date	Apr, 2013
///@see		
class XGUI_EXPORT CXPageMatchWells : public QWizardPage
{
	Q_OBJECT
public:
	CXPageMatchWells(QStringList sListWellInfo, QStringList& sListMatchedWells, QWidget *parent = 0);

	bool validatePage();

protected:
	Ui::PageMatchWells ui;

	QStringList&	m_sListMatchedWells;		//	Not selected files set as NULL.

	bool m_bSelectAll;
private slots:
	void slotSelectAll();
	void slotChangeWell(int);				//	Change matched well manually.
};

#endif