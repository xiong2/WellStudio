#ifndef XPAGEBUILDLFMTWO_H
#define XPAGEBUILDLFMTWO_H

#include <QWizard>
#include "ui_xpagebuildlfmtwo.h"

class CXParameterBuildLFM;

/**
*	@class	 CXPageBuildLFMTwo in the file "kepagebuildlfmtwo.h"
*	@brief	 The class provides a wizard page two to retrieve parameters for creating a Low frequency model
*	@author	Yong Shu
*	@date	11/17/2015
*/

class CXPageBuildLFMTwo : public QWizardPage
{
	Q_OBJECT

public:
	CXPageBuildLFMTwo(CXParameterBuildLFM* pPara, QWidget *parent = 0);
	~CXPageBuildLFMTwo();

protected:
	//Re implement the virtual function
	virtual void initializePage();
	virtual bool validatePage();

private slots:
	void slotAddPolygon();
	void slotRemovePolygon();

private:
	Ui::PageBuildLowFrequencyModelTwo m_ui;

	CXParameterBuildLFM* m_pPara; 

	
};

#endif // KEPAGEBUILDLFMTWO_H
