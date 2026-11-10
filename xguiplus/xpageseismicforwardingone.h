#ifndef XPAGESEISMICFORWARDINGONE_H
#define XPAGESEISMICFORWARDINGONE_H


#include <QWizard>
#include "ui_xpageseismicforwardingone.h"


class CXParameterAnisotropyForwarding;
class CXSeismicDataVolume;

/**
*	@class	 CXPageSeismicForwardingOne in the file "kepageseismicforwardingone.h"
*	@brief	 The class provides a wizard page one to retrieve parameters for anisotropic seismic forwarding
*	@author	Yong Shu
*	@date	1/9/2017
*/

class CXPageSeismicForwardingOne : public QWizardPage
{
	Q_OBJECT

public:
	CXPageSeismicForwardingOne(CXParameterAnisotropyForwarding* pPara, QWidget *parent = 0);
	~CXPageSeismicForwardingOne();

protected:
	//Reimplement the virtual function
	virtual void initializePage();
	virtual bool validatePage();

private slots:
	void slotFinishAzi();
	void slotFinishIncidence();
	void slotSelectDV();

	void slotLoadParameter();



private:
	Ui::PageSeismicForwardingOne m_ui;

	CXParameterAnisotropyForwarding* m_pPara;

	CXSeismicDataVolume* m_pDV;
};

#endif // KEPAGESEISMICFORWARDINGONE_H
