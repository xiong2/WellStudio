#ifndef XPAGEGSINVERSION2_H
#define XPAGEGSINVERSION2_H

#include <QWizardPage>
#include "ui_xpagegsinversion2.h"

class CXParametersGSInversion;
class CXObject;

class CXPageGSInversion2 : public QWizardPage
{
	Q_OBJECT

public:
	CXPageGSInversion2(CXParametersGSInversion *pPara, QWidget *parent = 0);
	~CXPageGSInversion2();

private:
	Ui::CXPageGSInversion2 ui;

	CXParametersGSInversion *m_pPara;

	void initGUI();
};

#endif // KEPAGEGSINVERSION2_H
