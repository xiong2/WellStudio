#ifndef XPAGEINTERPOLATION_H
#define XPAGEINTERPOLATION_H

#include <QWizardPage>
#include "ui_xpageinterpolation.h"

///@brief	A wizard page for selecting interpolation method
///@author	PEZY
///@date	May. 21th, 2014
///@update	Nov. 21th, 2014
///@see	

class CXParameterMake2DGrid;
class CXObject;

class CXPageInterpolation : public QWizardPage
{
	Q_OBJECT

public:
	CXPageInterpolation(CXParameterMake2DGrid *pPara, CXObject *pObj, QWidget *parent = 0);
	~CXPageInterpolation();

	///@brief Reimplementation
	virtual void initializePage();

	///@brief Reimplementation
	virtual bool validatePage();

private slots:
	void slotShowParameter(int);

private:
	Ui::CXPageInterpolation m_ui;

	CXParameterMake2DGrid* m_pPara;
};

#endif // RLPAGEINTERPOLATION_H
