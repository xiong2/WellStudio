#ifndef XPAGE3TERMAVOINVERSIONTHREE_H
#define XPAGE3TERMAVOINVERSIONTHREE_H

#include <QWizard>
#include "ui_xpage3termavoinversionthree.h"

class CXParameter3TermInversion;
class CXObject;

/**
*	@class	 CXPage3TermAVOInversionThree in the file "kepage3termavoinversionthree.h"
*	@brief	 The class provides a wizard page one to retrieve parameters for making 3-term AVO inversion
*	@author	Yong Shu
*	@date	12/14/2015
*/

class CXPage3TermAVOInversionThree : public QWizardPage
{
	Q_OBJECT

public:
	CXPage3TermAVOInversionThree(CXParameter3TermInversion* pPara, QWidget *parent = 0);
	~CXPage3TermAVOInversionThree();

protected:
	virtual void initializePage();

	//Re implement the virtual function
	virtual bool validatePage();

private slots:
	void slotAddTop();
	void slotAddBot();
	void slotHorizon();

private:
	void _Init();
	void _InitByPara();
	void _SetEnableConstraint(bool bEnabled);

private:
	Ui::Page3TermAvoInversionThree m_ui;

	CXParameter3TermInversion* m_pPara;
};

#endif // KEPAGE3TERMAVOINVERSIONTHREE_H
