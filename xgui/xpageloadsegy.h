#ifndef XLOADSEGYPAGE1_H
#define XLOADSEGYPAGE1_H

#include <QWizardPage>
#include "xgui_global.h"
#include "ui_xpageloadsegydatastep1.h"
#include "ui_xpageloadsegydatastep2.h"
#include "ui_xpageloadsegydatastep3.h"
#include "ui_xpageloadsegydatastep4.h"

class CXSEGYLoadParameters;
class CXSEGYTraceHeader;
class CXSeismicUTMTool ;
class CXTraceHeaderScanThread;
class CXSEGYLineHeader;

class XGUI_EXPORT CXPageLoadSegyStep1 : public QWizardPage
{
	Q_OBJECT

public:
	CXPageLoadSegyStep1(QWizard *parent,QStringList  sListFiles);
	~CXPageLoadSegyStep1();
	virtual void	initializePage(); 
	virtual bool   validatePage();
	CXSEGYLoadParameters *GetDataParameters()
	{
		return m_pDataPara;
	}
private slots:
	void slotSelectDisplayMode();
	void slotCurrentTraceChanged(int );
	void slotFlipData();
	void slotSampleFormatChanged(int );
	void slotSampleIntervalChanged();
	void slotSampleNumberChanged();
	void slotLineHeaderViewClicked();
	void slotVolumeHeaderViewClicked();//show volume header viewer .
private:
	void _connect();
	void _refrashPreview();
private:
	float * m_pTraceData;
	Ui_loadsegystep1 m_page1;
	CXSEGYLoadParameters *m_pDataPara;
	QStringList m_listFile;
};

class XGUI_EXPORT CXPageLoadSegyStep2 : public QWizardPage
{
	friend class CXTableForLoadSegy;
	Q_OBJECT
public:
	CXPageLoadSegyStep2(QWidget *parent);
	virtual ~CXPageLoadSegyStep2(void);
	virtual void	initializePage ();//This virtual function is called by QWizard::initializePage() to prepare the page just before it is shown either as a result of QWizard::restart() being called.
	/**
	*@ brief This virtual function is called by QWizard::validateCurrentPage() when the user clicks Next or Finish to perform some last-minute validation. If it returns true, the next page is shown (or the wizard finishes); otherwise, the current page stays up.
		The default implementation returns true.
	**/
	virtual bool validatePage ();
	void GetCoordinatePara(int &nInline,int &nCrossline,int &nX,int &nY);//< Get Coordinate from scan seg-y file .
	bool IsFromScan();//Get coordinate from input or scan.
	bool IsScaned()//Get need thread scan state.
	{
		return m_bScanned;
	}
private slots:
	void slotSEGYTypeChanged(int nValue);	//	SEGY type change.
	void slotTraceValueChanged(int nValue);//Current Trace changed;
	void slotFloatFormatChanged();//Trace Header Float Fromat changed.//IEEE or IBM
	void slotCoordinateFromChanged();//Trace Coordinate points form // Input 3 points or Scan SEG-Y File
	void slotOverrideScaleChanged();//Override X,Y Scale is changed.
	void slotOverrideScaleEnabled();//Override X,Y Scale is Enabled.
	void slotThreadFinished();
	void slotFlipData();//need flip bytes
	void slotRefreshProgressBar(qint64 nValue);//Refresh progress bar  when load segy thread is running
	void slotNeedRescan();
	void slotCancelThread();//Cancel Load segy thread.
	void slotEditLineNumber();//Valid Line start end edit finished.

private:
	void _updateTableWidget();
	float * m_pTraceData;
	void _connect();
	void _initUiFromPara();

	bool	m_bScanned;
	Ui_loadsegystep2 m_page2;
	CXSEGYLoadParameters*		m_pDataPara;
	CXSEGYTraceHeader*			m_pTraceHeader;
	CXTraceHeaderScanThread*	m_pScanHeaderThread;
};

class XGUI_EXPORT CXPageLoadSegyStep3 : public QWizardPage
{
	Q_OBJECT
public:
	CXPageLoadSegyStep3(QWidget *parent);
	virtual ~CXPageLoadSegyStep3(void);

	virtual void	cleanupPage();//back button is clicked.
	virtual void	initializePage ();///This virtual function is called by QWizard::initializePage() to prepare the page just before it is shown either as a result of QWizard::restart() being called.
	virtual bool	validatePage ();///This virtual function is called by QWizard::validateCurrentPage() when the user clicks Next or Finish to perform some last-minute validation. If it returns true, the next page is shown (or the wizard finishes); otherwise, the current page stays up.

protected:
	void initUI();
	void initConnect();//init widget connect.
protected slots:
	void UpdateUiPara();

private:
	int m_nInline1 ;
	int m_nInline2 ;
	int m_nInline3 ;
	int m_nXline1 ;
	int m_nXline2 ;
	int m_nXline3 ;
	Ui_LoadSegyDataRange m_page3;
	CXSEGYLoadParameters* m_pDataPara;
	CXSeismicUTMTool* m_pUTMTool;
	CXSeismicUTMTool * m_pOriUTMTool ;
};

class XGUI_EXPORT CXPageLoadSegyStep4 : public QWizardPage
{
	Q_OBJECT
public:
	CXPageLoadSegyStep4(QWidget *parent);
	virtual ~CXPageLoadSegyStep4(void);

	virtual void	initializePage ();///This virtual function is called by QWizard::initializePage() to prepare the page just before it is shown either as a result of QWizard::restart() being called.
	virtual bool	validatePage ();///This virtual function is called by QWizard::validateCurrentPage() when the user clicks Next or Finish to perform some last-minute validation. If it returns true, the next page is shown (or the wizard finishes); otherwise, the current page stays up.

protected:
	void InitUI();
	void initConnect();

private slots:
	void slotEnabledShiftTime();//shift start time to given value
	void slotImportDataChanged();//Import Range Start or End  Value Changed
	void slotZUnitChanged();
	void slotEnableCreateSliceFileState();// Create slice file state.
	void slotEnableCreateBrickFileState();//create brick file state.
	void slotDomainTypeChanged();
	void slotSurveyNameChanged();
	void slotSurveChanged(int nIdx);
	void slotSurveModeChanged();
	void slotCmbTextChanged(int);
private:
	Ui_loadsegydatastep4 m_page4;
	CXSEGYLoadParameters* m_pDataPara;
	CXSeismicUTMTool* m_pUTMTool;
	CXSeismicUTMTool * m_pOriUTMTool ;
	
	float m_dOrgTimeStart;
	float m_dOrgTimeEnd;
	float m_dOrgTimeStep;
	
	float m_dImpTimeStart;
	float m_dImpTimeEnd;
	float m_dImpTimeStep;
};
#endif // RFLOADSEGYPAGE1_H