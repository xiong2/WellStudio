#ifndef XPAGESEISMICFORWARDINGTHREE_H
#define XPAGESEISMICFORWARDINGTHREE_H


#include <QWizard>
#include "ui_xpageseismicforwardingthree.h"


class CXParameterAnisotropyForwarding;

/**
*	@class	 CXPageSeismicForwardingThree in the file "kepageseismicforwardingthree.h"
*	@brief	 The class provides a wizard page three to retrieve parameters for anisotropic seismic forwarding
*	@author	Yong Shu
*	@date	1/9/2017
*/

class CXPageSeismicForwardingThree : public QWizardPage
{
	Q_OBJECT

public:
	CXPageSeismicForwardingThree(CXParameterAnisotropyForwarding* pPara, QWidget *parent = 0);
	~CXPageSeismicForwardingThree();

protected:
	//Reimplement the virtual function
	virtual void initializePage();
	virtual bool validatePage();


private:
	Ui::PageSeismicForwardingThree m_ui;

	CXParameterAnisotropyForwarding* m_pPara;
};

#endif // KEPAGESEISMICFORWARDINGTHREE_H
