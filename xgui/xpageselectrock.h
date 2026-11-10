#ifndef XPAGESELECTROCK_H
#define XPAGESELECTROCK_H

#include <QWizardPage>
#include "ui_xpageselectrock.h"

///@brief	A wizard page for select rock between the surface
///@author	pezy
///@date	Jun. 9th, 2014
///@see	

class CXParameterWellHorzionIntersect;
class CXTypeCombo;

class CXPageSelectRock : public QWizardPage
{
	Q_OBJECT

public:
	CXPageSelectRock(CXParameterWellHorzionIntersect* pPara, QWidget *parent = 0);
	
	///@brief Reimplementation
	virtual void initializePage();

	///@brief Reimplementation
	virtual bool validatePage();

private:
	Ui::CXPageSelectRock m_ui;
	CXParameterWellHorzionIntersect* m_pPara;

	QVector<CXTypeCombo*> m_vecRock;
};

#endif // RLPAGESELECTROCK_H
