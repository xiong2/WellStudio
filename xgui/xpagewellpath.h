#ifndef _CXPAGEWELLPATH_H__
#define _CXPAGEWELLPATH_H__

#include <QWizardPage>
#include "xgui_global.h"
#include "ui_xpagewellpath.h"

class CXASCIIFile;

///@brief	A page to represent an import well path GUI.
///@author	Xiong Xiong
///@date	Mar, 2014
///@see		
class XGUI_EXPORT CXPageWellPath : public QWizardPage
{
	Q_OBJECT
public:
	CXPageWellPath(CXASCIIFile *pASCIIFile, QWidget *parent = 0);

	virtual void initializePage();

	bool validatePage();

protected:
	Ui::PageWellPath	ui;

	CXASCIIFile*		m_pASCIIFile;
};

#endif