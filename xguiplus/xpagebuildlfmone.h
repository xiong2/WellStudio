#ifndef XPAGEBUILDLFMONE_H
#define XPAGEBUILDLFMONE_H

#include <QWizard>
#include "ui_xpagebuildlfmone.h"

class CXParameterBuildLFM;
class CX3DHorizon;
class CXObject;

/**
*	@class	 CXPageBuildLFMOne in the file "kepagebuildlfmone.h"
*	@brief	 The class provides a wizard page one to retrieve parameters for creating a Low frequency model
*	@author	Yong Shu
*	@date	11/16/2015
*/

class CXPageBuildLFMOne : public QWizardPage
{
	Q_OBJECT

public:
	CXPageBuildLFMOne(CXParameterBuildLFM* pPara, QWidget *parent = 0);
	~CXPageBuildLFMOne();

protected:
	//Re implement the virtual function
	virtual bool validatePage();

private slots:
	void slotAddHorizon();
	void slotRemoveHorizon();

private:
	void _AddOneObject(CXObject* pObj);
	bool _AddOneHorizon(CX3DHorizon* pHorizon);
	void _GenerateName();


private:
	Ui::PageBuildLowFrequencyModel m_ui;

	CXParameterBuildLFM* m_pPara;
};

#endif // KEPAGEBUILDLFMONE_H
