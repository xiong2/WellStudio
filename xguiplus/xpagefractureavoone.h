#ifndef XPAGEFRACTUREAVOONE_H
#define XPAGEFRACTUREAVOONE_H

#include <QWizard>
#include "ui_xpagefractureone.h"
#include <QVector>
#include <QUuid>
#include <QStringList>

class CXParameterFractureAVO;

/**
*	@class	 CXPageFractureAVOOne in the file "kepagefractureavoone.h"
*	@brief	 The class provides a wizard page one to retrieve parameters for AVO fracture analysis
*	@author	Yong Shu
*	@date	9/26/2016
*/

class CXPageFractureAVOOne : public QWizardPage
{
	Q_OBJECT

public:
	CXPageFractureAVOOne(CXParameterFractureAVO* pPara, QWidget *parent = 0);
	~CXPageFractureAVOOne();

protected:
	//Re implement the virtual function
	virtual bool validatePage();

private slots:
	void slotAddDV();
	void slotAddOneAngle();
	void slotTableMenuRequest(const QPoint &);
	void slotDeleteCurrentAngle();

private:
	void _GetAzimuthInfo( QVector<float>& vecAzimuth, QVector<QUuid>& vecDVID);


private:
	Ui::PageFractureOne m_ui;

	CXParameterFractureAVO* m_pPara;
};

#endif // KEPAGEFRACTUREAVOONE_H


