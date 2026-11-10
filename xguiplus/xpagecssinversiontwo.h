#ifndef XPAGECSSINVERSIONTWO_H
#define XPAGECSSINVERSIONTWO_H

#include <QWizard>
#include "ui_xpagecssinversiontwo.h"

class CXParameterCSSInversion;

/**
*	@class	 CXPageCSSInversionTwo in the file "kepagecssinversiontwo.h"
*	@brief	 The class provides a wizard page one to retrieve parameters for CSSI
*	@author	Yong Shu
*	@date	1/15/2016
*/

class CXPageCSSInversionTwo : public QWizardPage
{
	Q_OBJECT

public:
	CXPageCSSInversionTwo(CXParameterCSSInversion* pPara, QWidget *parent = 0);
	~CXPageCSSInversionTwo();

protected:
	virtual void initializePage();

	//Re implement the virtual function
	virtual bool validatePage();

private:
	void _Init();

private:
	Ui::PageCSSInversionTwo m_ui;

	CXParameterCSSInversion* m_pPara;
};

#endif // KEPAGECSSINVERSIONTWO_H
