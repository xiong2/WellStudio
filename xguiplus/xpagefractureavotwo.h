#ifndef XPAGEFRACTUREAVOTWO_H
#define XPAGEFRACTUREAVOTWO_H

#include <QWizard>
#include "ui_xpagefracturetwo.h"

class CXParameterFractureAVO;
class CXObject;

/**
*	@class	 CXPageFractureAVOTwo in the file "kepagefractureavotwo.h"
*	@brief	 The class provides a wizard page one to retrieve parameters for AVO fracture analysis
*	@author	Yong Shu
*	@date	9/26/2016
*/

class CXPageFractureAVOTwo : public QWizardPage
{
	Q_OBJECT

public:
	CXPageFractureAVOTwo(CXParameterFractureAVO* pPara, QWidget *parent = 0);
	~CXPageFractureAVOTwo();

protected:
	virtual void initializePage();

	//Re implement the virtual function
	virtual bool validatePage();

private slots:
	void slotMethodChanged(int);

private:
	void _Init();
	void _InitByPara();

private:
	Ui::PageFractureTwo m_ui;

	CXParameterFractureAVO* m_pPara;
};


#endif // KEPAGEFRACTUREAVOTWO_H
