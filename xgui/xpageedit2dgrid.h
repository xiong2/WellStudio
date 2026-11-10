#ifndef XPAGEEDIT2DGRID_H
#define XPAGEEDIT2DGRID_H

#include <QWizardPage>
#include "ui_xpageedit2dgrid.h"

class CXParameterMake2DGrid;
class CXObject;
class CX2DGrid;

///@brief	A wizard page for editing 2D grid
///@author	PEZY
///@date	May. 20th, 2014
///@update	Nov. 21th, 2014
///@see	

class CXPageEdit2DGrid : public QWizardPage
{
	Q_OBJECT

public:
	CXPageEdit2DGrid(CXParameterMake2DGrid *pPara, CXObject *pObj, QWidget *parent = 0);
	~CXPageEdit2DGrid();

	///@brief Reimplementation
	virtual void initializePage() override;

	///@brief Reimplementation
    virtual bool validatePage() override;

private slots:
	void slotSetSliderValue(double value);
	void slotSetDoubleSpinBoxValue(int value);
	void slotAutoAdjust(int state);
	void slotShrink();
	void slotExpand();
	void slotRotate(double value);
	void slotReset();
	void slotNIChanged(int value);
	void slotNJChanged(int value);
	void slotNIItervalChanged(double value);
	void slotNJItervalChanged(double value);

private:
	void _SetParameter();
	void _Reset3BasicPoint();
	void _RotateItem(double angle);

private:
	Ui::CXPageEdit2DGrid m_ui;
	QGraphicsScene *m_pScene;
	CX2DGrid *m_pGrid;

	CXParameterMake2DGrid *m_pPara;
	CXObject *m_pObj;

	int m_nI, m_nJ;
	double m_dXMin, m_dXMax, m_dYMin, m_dYMax, m_dZMin, m_dZMax;

	std::vector<int> m_vecIIndex;
	std::vector<int> m_vecJIndex;
	std::vector<double> m_vecXCoords;
	std::vector<double> m_vecYCoords;
};

#endif // RLPAGEEDIT2DGRID_H
