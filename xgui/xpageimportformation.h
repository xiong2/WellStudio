#ifndef XPAGEIMPORTFORMATION_H
#define XPAGEIMPORTFORMATION_H

#include "xgui_global.h"

#include <QWizardPage>
#include "ui_xpageimportformation.h"

class CXASCIIFile;

class XGUI_EXPORT CXPageImportFormation : public QWizardPage
{
	Q_OBJECT

public:
	CXPageImportFormation(CXASCIIFile *pAFile, QWidget *parent = 0);
	~CXPageImportFormation();

	///@brief Reimplementation
	virtual void initializePage();

	///@brief Reimplementation
	virtual bool validatePage();

private slots:
	void slotSelectAll();

private:
	Ui::CXPageImportFormation ui;
	
	CXASCIIFile*			m_pASCIIFile;
};

#endif // KEPAGEIMPORTFORMATION_H
