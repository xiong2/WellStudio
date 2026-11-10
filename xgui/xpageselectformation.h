#ifndef XPAGESELECTFORMATION_H
#define XPAGESELECTFORMATION_H

#include <QWizardPage>
#include "ui_xpageselectformation.h"

///@brief	A wizard page for select all the formations
///@author	pezy
///@date	Jun. 9th, 2014
///@see	

class CXParameterWellHorzionIntersect;
class CXObject;

class CXPageSelectFormation : public QWizardPage
{
	Q_OBJECT

public:
	CXPageSelectFormation(CXParameterWellHorzionIntersect* pPara, QWidget *parent = 0);

	///@brief Reimplementation
	virtual void initializePage();

	///@brief Reimplementation
	virtual bool validatePage(); 

private slots:

	void _SelectAllItem();
	void _UnSelectAllItem();

private:
	Ui::CXPageSelectFormation m_ui;

	CXParameterWellHorzionIntersect* m_pPara;
	QMap<double, CXObject* > m_mapSurfaceObj;
};

#endif // RLPAGESELECTFORMATION_H
