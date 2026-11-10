#ifndef XPAGESEISMICFORWARDINGTWO_H
#define XPAGESEISMICFORWARDINGTWO_H

#include <QWizard>
#include "ui_xpageseismicforwardingtwo.h"


class CXParameterAnisotropyForwarding;

/**
*	@class	 CXPageSeismicForwardingTwo in the file "kepageseismicforwardingtwo.h"
*	@brief	 The class provides a wizard page two to retrieve parameters for anisotropic seismic forwarding
*	@author	Yong Shu
*	@date	1/9/2017
*/

class CXPageSeismicForwardingTwo : public QWizardPage
{
	Q_OBJECT

public:
	CXPageSeismicForwardingTwo(CXParameterAnisotropyForwarding* pPara, QWidget *parent = 0);
	~CXPageSeismicForwardingTwo();

protected:
	//Reimplement the virtual function
	virtual void initializePage();
	virtual bool validatePage();


private:
	Ui::PageSeismicForwardingTwo m_ui;

	CXParameterAnisotropyForwarding* m_pPara;
};

#endif // KEPAGESEISMICFORWARDINGTWO_H
