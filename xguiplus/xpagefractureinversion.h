#ifndef PAGEFRACTUREINVERSION_H
#define PAGEFRACTUREINVERSION_H

#include <QWizard>
#include "ui_xpagfractureinversionone.h"
#include <QVector>
#include <QUuid>
#include <QStringList>

class CXParameter3TermInversion;
class CXObject;
class CXSeismicDataVolume;

/**
*	@class	 CXPageFractureInversion in the file "pagefractureinversion.h"
*	@brief	 The class provides a wizard page one to retrieve parameters for fracture inversion
*	@author	Yong Shu
*	@date	12/15/2016
*/

class CXPageFractureInversion : public QWizardPage
{
	Q_OBJECT

public:
	CXPageFractureInversion(CXParameter3TermInversion* pPara, QWidget *parent = 0);
	~CXPageFractureInversion();

	//Re implement the virtual function
	virtual void initializePage();

protected:
	//Re implement the virtual function
	virtual bool validatePage();

private slots:

	void slotTableMenuRequest(const QPoint &);
	void slotDeleteSelected();
	void slotReset();
	void slotLoadParameter();

	void slotAddEpsilon();
	void slotAddDelta();
	void slotAddGamma();
	void slotAddSymAzi();

private:
	void _SetWidgetFromPara();
	CXObject* _GetCurrentDV(const QString& strMng);

private:
	Ui::PageFractureInversion m_ui;

	CXParameter3TermInversion* m_pPara;

	CXSeismicDataVolume* m_pDV;

	int m_nOffset;

	QUuid m_uuidWaveletID;
	QUuid m_uuidDVID;
};

#endif // PAGEFRACTUREINVERSION_H
