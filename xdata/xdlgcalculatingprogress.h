#ifndef _GMDLGCALCULATINGPROGRESS_H__
#define _GMDLGCALCULATINGPROGRESS_H__

#include <qdialog.h>
#include "xdata_global.h"
#include "ui_xdlgattprogressbar.h"
#include <QPointer>

class CXBaseThread;
class QCloseEvent;
class QKeyEvent;

/**
 * @class CXDlgCalculatingProgress provided in the file "rldlgcalculatingprogress.h"
 * @brief The Class provides a progress bar for attribute computation
 * 
 * @author Yong Shu 
 * @date  5/22/2014
 * @see 
 * @bug	No Known bugs so far
 */

class XDATA_EXPORT CXDlgCalculatingProgress : public QDialog
{
	Q_OBJECT
public:
	 ///@ brief Constructor	
	CXDlgCalculatingProgress( CXBaseThread* pThread, QWidget *parent = NULL);

	///@ brief Destructor		 
	~CXDlgCalculatingProgress();	  

signals:
	void signalFinishedComputing();
	void signalTerminated();

public slots:
    void slotSetWindowName(const QString&);
    void slotSetTaskName(const QString&);
    void slotUpdateProgress(qint64, qint64);
    void slotStartComputing();
    void slotFinishComputing();	
	void slotTerminated();
    void slotMemoryNotEnough();
    void slotDiskSpaceNotEnough(const QString&);
    void slotGeneralErrorMsg(const QString&);
	void slotGeneralWarningMsg(const QString&);
    void slotCancel();	
    void slotReset();
    void slotCancelEnabled(bool);

protected:
    /// Reimplement the close event
    virtual void closeEvent(QCloseEvent *pEvent);

    /// Reimplement the "press Escape" event
    virtual void keyPressEvent(QKeyEvent* pEvent);

private:
    // Set connections
    void _SetConnection();

    // Update the time label   
    void _UpdateTimer();	

	// Stop the process
	void _Stopped();

private:
    // Ui for Progress Bar
    Ui_CXDlgAttProgressBar	m_ui;

	// The thread
	QPointer<CXBaseThread> m_pThread;

    // Initial time
	unsigned int	m_nStartTime;		

    // First time to update progress bar
    bool m_bFirstTimeUpdate;

    // Flag for enabling or disabling cancelling operation
    bool m_bCancelEnabled;  

	// Tell if the thread is finished
	bool m_bThreadFinished;
};

#endif //_GMDLGCALCULATINGPROGRESS_H__