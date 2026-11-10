#ifndef XPAGE3TERMAVOINVERSIONTWO_H
#define XPAGE3TERMAVOINVERSIONTWO_H

#include <QWizard>
#include "ui_xpage3termavoinversiontwo.h"

class CXParameter3TermInversion;
class CXObject;
class CXSeismicDataVolume;

/**
*	@class	 CXPage3TermAVOInversionTwo in the file "kepage3termavoinversiontwo.h"
*	@brief	 The class provides a wizard page one to retrieve parameters for making 3-term AVO inversion
*	@author	Yong Shu
*	@date	12/14/2015
*/

class CXPage3TermAVOInversionTwo : public QWizardPage
{
	Q_OBJECT

public:
	CXPage3TermAVOInversionTwo(CXParameter3TermInversion* pPara, QWidget *parent = 0);
	~CXPage3TermAVOInversionTwo();

	virtual void initializePage();

protected:
	//Re implement the virtual function
	virtual bool validatePage();

private slots:
	void slotAddZp();
	void slotAddZs();
	void slotAddRho();

	void slotAdvanced();

private:
	CXObject* _GetCurrentDV(const QString& strMng);

private:
	Ui::Page3TermAvoInversionTwo m_ui;

	CXParameter3TermInversion* m_pPara;
};

#endif // KEPAGE3TERMAVOINVERSIONTWO_H
