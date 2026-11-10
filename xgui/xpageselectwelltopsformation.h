#ifndef XPAGEWELLTOPS_H
#define XPAGEWELLTOPS_H

#include <QWizardPage>
#include "ui_xpageselectwelltopsformation.h"

class CXParameterMake2DGrid;
class CXObject;
class CXWellTops;

///@brief	A wizard page for select formations
///@author	PEZY
///@date	May. 19th, 2014
///@update	Nov. 21th, 2014
///@see	

class CXPageSelectWellTopsFormation : public QWizardPage
{
	Q_OBJECT

public:
	CXPageSelectWellTopsFormation(CXParameterMake2DGrid *pPara, CXObject *pObj, QWidget *parent = 0);

	///@brief Reimplementation
	virtual void initializePage();

	///@brief Reimplementation
	virtual bool validatePage(); 

private slots:
	
	void _SelectAllItem();
	void _UnSelectAllItem();

private:
	Ui::CXPageSelectWellTopsFormation m_ui;
	QStringList m_strlistFormation;

	CXWellTops *m_pWellTops;
	CXParameterMake2DGrid* m_pPara;
};

#endif // RLPAGEWELLTOPS_H
