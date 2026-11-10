#pragma once

#include <QDialog>
#include "xgui_global.h"
#include "ui_xdlgwelltie.h"
#include "xframewelltie.h"

class CXWell;
class CXWellTD;
class CXWellCurve;
class CXFrameWTTop;
class CXFrameWTAnno;
class CXWavelet;

#define TMARGIN 30
#define TWIDTH 100
#define TRACEW 10

class XGUI_EXPORT CXDlgWellTie : public QDialog
{
	Q_OBJECT

public:
	CXDlgWellTie(CXWell *, QWidget *parent = Q_NULLPTR);
	~CXDlgWellTie();

	void SetCanvasSize(int, bool bV = true);

	CXWellTD* GetWellTD();
	void SetWellTD(CXWellTD *);

	void MoveScrollBar(int iDelta);

	void ShowMessage(QString);

	///	The meaning of iSta, see the comments of CXFrameWellTie::Interact(int iSta)
	void UpdateButtons(int iSta);

	SLayout& GetSLayout();

	void RefreshLayout()
	{
		m_pWTFrame->RefreshLayout();
	}

protected:
	virtual void resizeEvent(QResizeEvent* event) override;

private slots:
	void slotWaveletRadio();
	void slotWaveletSelect();
	void slotFlush();
	void slotSnap(int);
	void slotOperation();
	void slotCal();
	void slotScroll(int);

private:
	void initUI();

	void adjustSBar();

	void stretch();

	CXWellCurve *calculateRC(CXWellCurve *pAC, CXWellCurve *pDen);
	bool calculateSyn(CXWellCurve *, float *& pSynData);
	void calculateCorrelation(float *pSynData, double dSTime, double dStep, unsigned int iNum);

	Ui::CXDlgWellTie ui;

	CXWell*			m_pWell;
	CXWavelet*		m_pWavelet = NULL;
	CXFrameWTTop*	m_pTopFrame;
	CXFrameWTAnno*	m_pLAnnoFrame;
	CXFrameWTAnno*	m_pRAnnoFrame;
	CXFrameWellTie*	m_pWTFrame;

	CXWellTD*				m_pTD = NULL;
	QVector<CXWellTD *>		m_vecUndoTD;
	QVector<CXWellTD *>		m_vecRedoTD;

	QSize			m_canSize;

	//	Synthetic seismogram
	float*			m_pSynData = NULL;
	double			m_dSTime;
	double			m_dStep;
	unsigned int	m_iNum;
};
