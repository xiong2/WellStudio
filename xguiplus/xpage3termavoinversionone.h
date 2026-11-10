#ifndef XPAGE3TERMAVOINVERSIONONE_H
#define XPAGE3TERMAVOINVERSIONONE_H

#include <QWizard>
#include "ui_xpage3termavoinversionone.h"
#include <QVector>
#include <QUuid>
#include <QStringList>

class CXParameter3TermInversion;

/**
*	@class	 CXPage3TermAVOInversionOne in the file "kepage3termavoinversionone.h"
*	@brief	 The class provides a wizard page one to retrieve parameters for making 3-term AVO inversion
*	@author	Yong Shu
*	@date	12/11/2015
*/

class CXPage3TermAVOInversionOne : public QWizardPage
{
	Q_OBJECT

public:
	CXPage3TermAVOInversionOne(CXParameter3TermInversion* pPara, QWidget *parent = 0);
	~CXPage3TermAVOInversionOne();

protected:
	//Re implement the virtual function
	virtual bool validatePage();

private slots:
	void slotAddDV();
	void slotDataSourceChanged(int);
	void slotAddWaveletObject();
	void slotAddWaveletDataFile();
	void slotAddOneAngle();
	void slotTableMenuRequest(const QPoint &);
	void slotDeleteCurrentAngle();

private:
	void _GetOneAngleInfo(QVector<int>& vecPos, QVector<float>& vecAngle, QVector<QUuid>& vecWaveletID, QStringList& listFileName);


private:
	Ui::Page3TermAvoInversionOne m_ui;

	CXParameter3TermInversion* m_pPara;

	int m_nOffset;

	QUuid m_uuidWaveletID;
};

#endif // KEPAGE3TERMAVOINVERSIONONE_H
