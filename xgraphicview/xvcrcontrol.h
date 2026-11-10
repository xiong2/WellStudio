/*! 
* @file kevcrcontrol.h
* @brief The control is used for interface of animinate player
*
* Section window will use another structre because of it's special coordinate transform
* @author Haidong Wang
* @date 20080515             
*/

#ifndef CXVCRCONTROL_H
#define CXVCRCONTROL_H

#include <QObject>
#include "xgraphicview_global.h"

class QToolBar;
class QSlider;
class QAction;
class QComboBox;
class QTimer;
class CXSliderSpinWidget ;
class CXWindow;
 
/*! CXVCRControl which takes as player controller in XStudio
 *
 *  This controller is a standard player component which can be used in 3D, Basemap, Section and another
 *  window as you like. In addational, a reference ID can be recorded in the controller to keep the relation
 *  between object which is playing.
 */

class XGRAPHICVIEW_EXPORT CXVCRControl : public QObject
{
	Q_OBJECT
public:
	enum enumPlayMode
	{
		ePlayNone ,
		ePlayToFirst ,
		ePlayPageUp ,
		ePlayBackward ,
		ePlayerStop ,
		ePlayForward ,
		ePlayPageDown ,
		ePlayToLast 
	} ;

	QToolBar* m_pTBarVCR = nullptr; //!< The tool bar used to control the playing                            

	explicit CXVCRControl(CXWindow* pWin);
	virtual ~CXVCRControl() {}
	void CreateIt();

	void InitData(double dStart, double dEnd, double dCur, double dMinStep, double dCurStep, int nDecimal);
	void SetToolBarTitle(const QString& strToolbarName);
	void SetSliderSpinValue(double dValue);

	void ShowMe(bool bVisible);
    bool IsVisible() { return m_bVisible; }

	bool IsInited() const { return m_bInited; }
	void SetInited(bool value) { m_bInited = value; }
	
	void StopTimer();
	void SetVCRToolBarEnabled(bool bEnabled);
	void SetStepComboboxDisabled(bool b);
 
	double GetCurrentSecValue() const { return m_dCurValue; }

signals:
	void CurrentSectionChanged(double);

public slots:
	void slotStepIntervalChanged(const QString& str);
	void slotPlayForward();
	void slotPlayBackward();
	void slotPlayPageUp();
	void slotPlayPageDown();
	void slotPlayToFirst();
	void slotPlayToLast();
	void slotPlayerStop();
	void slotOnTimer();

protected:
	CXSliderSpinWidget* m_pSliderSpinWidget = nullptr;
	CXWindow* m_pCurWindow;

	QAction* m_pBtPlayToFirst	= nullptr;
	QAction* m_pBtPlayPageUp	= nullptr;
	QAction* m_pBtPlayBackward	= nullptr;
	QAction* m_pBtPlayStop		= nullptr;
	QAction* m_pBtPlayForward	= nullptr;
	QAction* m_pBtPlayPageDown	= nullptr;
	QAction* m_pBtPlayToLast	= nullptr;

	QComboBox* m_pComboStepInterval = nullptr;
	QTimer* m_pTimer = nullptr;

	enumPlayMode m_ePlayMode = ePlayNone;
	int m_nTimerInterval;

	double m_dStepInterval;
	double m_dCurValue;
	double m_dStart;
	double m_dEnd;
	double m_dMinStep;
	double m_dRatioFactor;

	bool m_bInited  = false;
    bool m_bVisible = false;

private slots:
	void OnEditFinish();

private:
	void _InitSliderSpinWidget();
	void _InitComboStepInterval();
	void _InitActions();
	void _updateToolbarStates();
	void _StopOtherVCRControl();
};

#endif // CXVCRCONTROL_H
