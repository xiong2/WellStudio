#ifndef _CXPAGELOGCURVES_H__
#define _CXPAGELOGCURVES_H__

#include "xgui_global.h"

#include <QWizardPage>
#include <qlist.h>
#include "ui_xpagelogcurves.h"

class CXWellLogASCIIFile;

///@brief	A page to parse log curves.
///@author	Xiong Xiong
///@date	Sep, 2015
///@see		
class XGUI_EXPORT CXPageLogCurves : public QWizardPage
{
	Q_OBJECT
public:
	CXPageLogCurves(CXWellLogASCIIFile * pLogFile, QWidget *parent = 0);

	///	Reimplement super class' function.
	void initializePage();

	bool validatePage();

protected:
	Ui::CXPagelogcurves ui;

	CXWellLogASCIIFile*	m_pLogFile;			//	Hold the log file.

	private slots:
	void slotSelectDepth(bool);
	void slotChangeTemplate(int);			//	User change the template mannually.
};

#endif // KEPAGELOGCURVES_H
