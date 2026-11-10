#ifndef XPAGEBUILDLFMTHREE_H
#define XPAGEBUILDLFMTHREE_H

#include <QWizard>
#include "ui_xpagebuildlfmthree.h"

class CXParameterBuildLFM;

/**
*	@class	 CXPageBuildLFMThree in the file "kepagebuildlfmthree.h"
*	@brief	 The class provides a wizard page three to retrieve parameters for creating a Low frequency model
*	@author	Yong Shu
*	@date	11/17/2015
*/

class CXPageBuildLFMThree : public QWizardPage
{
	Q_OBJECT

public:
	CXPageBuildLFMThree(CXParameterBuildLFM* pPara, QWidget *parent = 0);
	~CXPageBuildLFMThree();

protected:
	//Re implement the virtual function
	virtual void initializePage();
	virtual bool validatePage();

private slots:
	// change the parameter
	void slotCellChanged(int);

private:
	Ui::PageBuildLowFrequencyModelThree m_ui;

	CXParameterBuildLFM* m_pPara;
	
};

#endif // KEPAGEBUILDLFMTHREE_H
