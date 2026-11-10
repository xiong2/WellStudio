#ifndef XPAGE3DTERMAVOINVERSIONONEEXT_H
#define XPAGE3DTERMAVOINVERSIONONEEXT_H

#include <QWizard>
#include "ui_xpage3termavoinversiononeext.h"
#include <QVector>
#include <QUuid>
#include <QStringList>

class CXParameter3TermInversion;

/**
*	@class	 CXPage3TermAVOInversionOneExt in the file "kepage3termavoinversiononeext.h"
*	@brief	 The class provides a wizard page one to retrieve parameters for making 3-term AVO inversion
*	@author	Yong Shu
*	@date	12/11/2015
*/

class CXPage3TermAVOInversionOneExt : public QWizardPage
{
	Q_OBJECT

public:
	CXPage3TermAVOInversionOneExt(CXParameter3TermInversion* pPara, QWidget *parent = 0);
	~CXPage3TermAVOInversionOneExt();

	//Re implement the virtual function
	virtual void initializePage();

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

	void slotLoadParameter();

private:
	void _GetOneAngleInfo(QVector<QUuid>& vecDVID, QVector<float>& vecAngle, QVector<QUuid>& vecWaveletID, QStringList& listFileName);


private:
	Ui::Page3TermAvoInversionOneExt m_ui;

	CXParameter3TermInversion* m_pPara;

	int m_nOffset;

	QUuid m_uuidWaveletID;
	QUuid m_uuidDVID;
};

#endif // KEPAGE3DTERMAVOINVERSIONONEEXT_H
