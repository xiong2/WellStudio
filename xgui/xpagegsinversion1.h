#ifndef XPAGEGSINVERSION1_H
#define XPAGEGSINVERSION1_H

#include <QWizardPage>
#include "ui_xpagegsinversion1.h"

class CXParametersGSInversion;
class CXObject;

class CXPageGSInversion1 : public QWizardPage
{
	Q_OBJECT

public:
	CXPageGSInversion1(CXParametersGSInversion *pPara, QWidget *parent = 0);
	~CXPageGSInversion1();
	
	virtual bool validatePage();

	virtual void initializePage();

private slots:
	void slotSelectZone();
	void slotSetSection();
	void slotSelectWell();
	void slotSelectCProperty(int);
	void slotSetFitPrior();
	void slotSelectFitPrior(int);

private:
	Ui::CXPageGSInversion1 ui;

	CXParametersGSInversion *m_pPara;

	QList<CXObject *>	m_listSelectWells;
	unsigned int m_arrayCTmpID[3];

	//	While selected wells changed, update the well curve candidates.
	void updateCurveCandidates();
};

#endif // KEPAGEGSINVERSION1_H
