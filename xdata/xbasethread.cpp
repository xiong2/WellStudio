#include <QApplication>

#include "xbasethread.h"
#include "xobject.h"

CXBaseThreadManager::CXBaseThreadManager()
{
	m_listThread.clear();
}

CXBaseThreadManager::~CXBaseThreadManager()
{
	DoWhenCloseSystem();
}

int CXBaseThreadManager::GetActiveThreadNum()
{
	QMutexLocker locker(&m_Mutex);

	return (int) m_listThread.size();
}

void CXBaseThreadManager::DoWhenCloseSystem()
{
	for (int i=0; i<m_listThread.size(); ++i)
	{
		m_listThread.at(i)->TerminateThread();
	}

	qApp->processEvents();
	for (int i=0; i<m_listThread.size(); ++i)
	{
		delete m_listThread.at(i);
	}

	m_listThread.clear();
}

void CXBaseThreadManager::_RegisterThread( CXBaseThread* pThread)
{
	if (!m_Mutex.tryLock())
		return;

	m_listThread.append(pThread);

	m_Mutex.unlock();
}

void CXBaseThreadManager::_UnregisterThread( CXBaseThread* pThread)
{
	if (!m_Mutex.tryLock()) 
		return;

	m_listThread.removeAll(pThread);
	
	m_Mutex.unlock();
}

CXBaseThread::CXBaseThread()
{
    m_bStop = false;
	m_bTerminated = false;
	m_bPause = false;

	m_nTotal = -1;
	m_nStep = -1;
	m_iCurrent = -1;

	CXBaseThreadManager::Instance()._RegisterThread(this);
}

CXBaseThread::~CXBaseThread()
{
    this->wait();

	CXBaseThreadManager::Instance()._UnregisterThread(this);
}

void CXBaseThread::SetStopFlag()
{
	m_bStop = true;
}

void CXBaseThread::StopThread()
{
    m_bStop = true;
	ResumeThread();
    this->wait();
}

void CXBaseThread::TerminateThread()
{
	m_bStop = true;
	m_bTerminated = true;
	ResumeThread();
	this->wait();
}

bool	CXBaseThread::IsStopped()
{
    return m_bStop;
}

bool CXBaseThread::IsTerminated()
{
	return m_bTerminated;
}

// Lock the object for reading
bool CXBaseThread::LockRead(CXObject* pObject)
{
	if (NULL == pObject)
		return false;

    return pObject->LockObject(this);
}

// Unlock the object for reading
bool CXBaseThread::UnlockRead(CXObject* pObject)
{
	if (NULL == pObject)
		return false;

    return pObject->UnlockObject(this);
}

// Lock the object for writing
bool CXBaseThread::LockWrite(CXObject* pObject)
{
	if (NULL == pObject)
		return false;

    //return pObject->LockWrite(this);
	return false;
}

// Unlock the object for writing
bool CXBaseThread::UnlockWrite(CXObject* pObject)
{
	if (NULL == pObject)
		return false;

    //return pObject->UnLockWrite(this);
	return false;
}

void CXBaseThread::_FinishRunning()
{
	if (IsStopped())
	{
		if (IsTerminated())
			emit signalTerminated(); //send signal to pick up unacomplished data
	}
	else
		emit signalFinishComputing();
}

void CXBaseThread::run()
{
	RunThread();

	WaitPausedThread();

	_FinishRunning();
}

void CXBaseThread::WaitPausedThread()
{
	if (!m_bPause)
		return;
	else
	{
		m_mutexPause.lock();
		while(m_bPause)
			m_conditionPause.wait(&m_mutexPause);
		m_mutexPause.unlock();
	}
}

void CXBaseThread::SetPauseFlag()
{	
	m_bPause = true;
}

void CXBaseThread::ResumeThread()
{	
	QMutexLocker locker(&m_mutexPause);
	m_bPause = false;
	m_conditionPause.wakeOne();
}

void CXBaseThread::EmitStartComputing()
{
	emit this->signalStartComputing();
}

void CXBaseThread::EmitSetTaskName (const QString& strTaskName)
{
	emit this->signalSetTaskName(strTaskName);
}

void CXBaseThread::EmitSetWindowName(const QString& strWindowName)
{
	emit this->signalSetWindowName(strWindowName);
}

void CXBaseThread::EmitUpdateProgress(qint64 iCurrent, qint64 nTotal, qint64 nStep)
{
	if (m_nTotal < 0)
	{
		if (nStep > 0)
			m_nStep = nStep;
		else
		{
			m_nStep = qMax((qint64)1, nTotal / 1000);			
		}

		m_nTotal = static_cast<int>(nTotal / m_nStep);
		m_iCurrent = 0;
	}

	WaitPausedThread();

	int iNewCurrent = static_cast<int>(iCurrent / m_nStep);
	if (iNewCurrent > m_iCurrent)
	{		
		m_iCurrent = iNewCurrent;
		emit this->signalUpdateProgress(m_iCurrent, m_nTotal);
	}	
}

void CXBaseThread::EmitMemoryNotEnough()
{
	m_bStop = true;
	emit this->signalMemoryNotEnough();
}

void CXBaseThread::EmitDiskSpaceNotEnough(const QString& strErrMsg)
{
	m_bStop = true;
	emit this->signalDiskSpaceNotEnough(strErrMsg);
}

void CXBaseThread::EmitGeneralErrorMsg(const QString& strErrMsg)
{
	m_bStop = true;
	emit this->signalGeneralErrorMsg(strErrMsg);
}

void CXBaseThread::EmitWarningMessage(const QString& strWarningMsg)
{
	emit this->signalGeneralWarningMsg(strWarningMsg);
}

void CXBaseThread::EmitResetProgressBar ()
{
	m_nTotal = m_nStep = -1;
	emit this->signalReset();
}

void CXBaseThread::EmitCancelEnabled(bool bEnabled)
{
	emit this->signalCancelEnabled(bEnabled);
}