#ifndef _RLBASETHREAD_H__
#define _RLBASETHREAD_H__

#include "xdata_global.h"
#include <QThread>
#include <QWaitCondition>
#include <QMutex>

class CXObject;
class CXBaseThread;

/**
* @class CXBaseThreadManager in the file "gmbasethread.h"
* @brief The class provides a manager to handle all CXBaseThread derived classes.
* 
* @author Yong Shu
* @date 11/18/2010
* @see 
*/
class XDATA_EXPORT CXBaseThreadManager
{
	friend class CXBaseThread;
public:
	///@brief Destructor
	~CXBaseThreadManager();

	///@brief Unique instance of this manager
	static CXBaseThreadManager& Instance()
	{
		static CXBaseThreadManager object;
		return object;
	}

	///@brief Get the number of available threads
	int GetActiveThreadNum();

	///@brief Handle the threads when closing the application
	void DoWhenCloseSystem();

private:
	CXBaseThreadManager();

	// Register the thread. It can only be invoked by the constructor of CXBaseThread class.
	void _RegisterThread( CXBaseThread* pThread);

	// Unregister the thread. It can only be invoked by the destructor of CXBaseThread class.
	void _UnregisterThread(CXBaseThread* pThread);

private:
	QMutex m_Mutex;
	QList<CXBaseThread *> m_listThread;
};

/**
 * @class CXBaseThread provided in the file "gmbasethread.h"
 * @brief The Class provides a base thread interface all attribute computation threads
 * 
 * @author Yong Shu 
 * @date 3/5/2010
 * @see 
 * @bug	No Known bugs so far
 */

class XDATA_EXPORT CXBaseThread : public QThread
{
	Q_OBJECT

public:
	///@brief Constructor
    CXBaseThread();

	///@brief Destructor
    virtual ~CXBaseThread();

	///@brief Set the stop flag
	void SetStopFlag();

	///@brief Stop the concurrent thread 
	void StopThread();

	///@brief Terminate the concurrent thread 
	void TerminateThread();

	///@brief Query if the current thread is stopped
	bool IsStopped();

	///@brief Query if the current thread is terminated
	bool IsTerminated();

    ///@brief Lock the object for reading
    bool LockRead(CXObject* pObject);

    ///@brief Unlock the object for reading
    bool UnlockRead(CXObject* pObject);

    ///@brief Lock the object for writing
    bool LockWrite(CXObject* pObject);

    ///@brief Unlock the object for writing
    bool UnlockWrite(CXObject* pObject);

	///@brief Set Pause flag
	void SetPauseFlag();

	///@brief Resume the paused thread
	void ResumeThread();

	///@ Set a few public signal
	void EmitStartComputing();
	void EmitSetWindowName(const QString& strWindowName);
	void EmitSetTaskName (const QString& strTaskName);
	void EmitUpdateProgress(qint64 iCurrent, qint64 nTotal, qint64 nStep = -1);
	void EmitMemoryNotEnough();
	void EmitDiskSpaceNotEnough(const QString& strErrMsg);
	void EmitGeneralErrorMsg (const QString& strErrMsg);
	void EmitWarningMessage(const QString& strWarningMsg);
	void EmitResetProgressBar ();
	void EmitCancelEnabled(bool);

signals:  
    void signalSetWindowName(const QString&);
    void signalSetTaskName(const QString&);
    void signalUpdateProgress(qint64, qint64);
    void signalStartComputing();
    void signalFinishComputing();	
	void signalTerminated();
    void signalMemoryNotEnough();
    void signalDiskSpaceNotEnough(const QString&);
    void signalGeneralErrorMsg(const QString&);
	void signalGeneralWarningMsg(const QString&);
    void signalReset();
    void signalCancelEnabled(bool);

protected:
	virtual void RunThread()=0;

protected:
	///@brief Wait the paused thread
	void WaitPausedThread();

protected:  
	// Stop flag
	volatile bool	m_bStop;	

	// Terminate
	volatile bool m_bTerminated;

protected:
	// Pause thread
	QMutex m_mutexPause;
	QWaitCondition m_conditionPause;
	volatile bool m_bPause;

private:
	// Invoke this function at the end of run
	void _FinishRunning();
	
	// Virtual function of run
	virtual void run();		
private:
	// For progress bar
	int m_nTotal;
	int m_nStep;
	int m_iCurrent;
};

#endif ///<_GMBASETHREAD_H__
