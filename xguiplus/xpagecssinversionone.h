#ifndef XPAGECSSINVERSIONONE_H
#define XPAGECSSINVERSIONONE_H

#include <QWizard>
#include "ui_xpagecssinversionone.h"
#include <QVector>
#include <QUuid>

class CXParameterCSSInversion;

/**
*	@class	 CXPageCSSInversionOne in the file "kepagecssinversionone.h"
*	@brief	 The class provides a wizard page one to retrieve parameters for CSSI
*	@author	Yong Shu
*	@date	1/15/2016
*/

class CXPageCSSInversionOne : public QWizardPage
{
	Q_OBJECT

public:
	CXPageCSSInversionOne(CXParameterCSSInversion* pPara, QWidget *parent = 0);
	~CXPageCSSInversionOne();

protected:
	//Re implement the virtual function
	virtual bool validatePage();

	private slots:
	void slotAddDV();
	void slotAddZp();
	void slotDataSourceChanged(int);
	void slotAddWaveletObject();
	void slotAddWaveletDataFile();

private:
	Ui::PageCSSInversionOne m_ui;

	CXParameterCSSInversion* m_pPara;
};

#endif // KEPAGECSSINVERSIONONE_H
