#include "xdlgcalculatingprogress.h"

#include <cassert>
#include <QDateTime>
#include <QMessageBox>
#include <QCloseEvent>

#include "xbasethread.h"

CXDlgCalculatingProgress::CXDlgCalculatingProgress( CXBaseThread* pThread, QWidget *parent)
: QDialog(parent), m_pThread (pThread)
{
	setAttribute(Qt::WA_DeleteOnClose);

	m_ui.setupUi(this);

	assert(m_pThread);
	m_ui.m_pLabelName->setText(QString());
	//setWindowIcon(QIcon(GetImagePath()+"Product.png"));	
	setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint);
	//m_ui.m_pBtnCancel->setIcon( QIcon(GetImagePath()+ "1094.png" ) );

	m_bCancelEnabled = true;
	m_bFirstTimeUpdate = true;
	m_bThreadFinished = false;
	connect(m_ui.m_pBtnCancel, SIGNAL(clicked()), this, SLOT(slotCancel()));

	m_nStartTime = QDateTime::currentDateTime().toTime_t();
	m_ui.m_pLabelElapsedTime->setText(QString::number(0));
	m_ui.m_pProgressBar->reset();

	_SetConnection();
}

CXDlgCalculatingProgress::~CXDlgCalculatingProgress()
{
}

void CXDlgCalculatingProgress::_SetConnection()
{
    connect(m_pThread, SIGNAL(signalSetWindowName(const QString&)), this, SLOT(slotSetWindowName(const QString&)));
    connect(m_pThread, SIGNAL(signalSetTaskName(const QString&)), this, SLOT(slotSetTaskName(const QString&)));
    connect(m_pThread, SIGNAL(signalStartComputing()), this, SLOT(slotStartComputing()));
    connect(m_pThread, SIGNAL(signalUpdateProgress(qint64, qint64)), this, SLOT(slotUpdateProgress(qint64, qint64)));
    connect(m_pThread, SIGNAL(signalFinishComputing()), this, SLOT(slotFinishComputing()));
	connect(m_pThread, SIGNAL(signalTerminated()), this, SLOT(slotTerminated()));
    connect(m_pThread, SIGNAL(signalMemoryNotEnough()), this, SLOT(slotMemoryNotEnough()));
    connect(m_pThread, SIGNAL(signalDiskSpaceNotEnough(const QString&)), this, SLOT(slotDiskSpaceNotEnough(const QString&)));
    connect(m_pThread, SIGNAL(signalGeneralErrorMsg(const QString&)), this, SLOT(slotGeneralErrorMsg(const QString&)));    
	connect(m_pThread, SIGNAL(signalGeneralWarningMsg(const QString&)), this, SLOT(slotGeneralWarningMsg(const QString&)));    
    connect(m_pThread, SIGNAL(signalReset()), this, SLOT(slotReset()));
    connect(m_pThread, SIGNAL(signalCancelEnabled(bool)), this, SLOT(slotCancelEnabled(bool)));

 }

void CXDlgCalculatingProgress::slotMemoryNotEnough()
{
	slotGeneralErrorMsg("The memory is not enough!");
}

void CXDlgCalculatingProgress::slotDiskSpaceNotEnough(const QString& strAdditionalSpace)
{   
    QString strErrorMsg = "There is not enough space on the disk. You need an additional " + strAdditionalSpace + ".";
	slotGeneralErrorMsg(strErrorMsg);
}

void CXDlgCalculatingProgress::slotGeneralErrorMsg(const QString& strMsg)
{
	// Pause the thread
	if (!m_pThread.isNull())
		m_pThread->SetStopFlag();

	if (strMsg != "")
		QMessageBox::warning(NULL, "", strMsg,QMessageBox::Close);
	_Stopped();
}

void CXDlgCalculatingProgress::slotGeneralWarningMsg(const QString& strMsg)
{
	QMessageBox::warning(NULL, "", strMsg,QMessageBox::Close);
}

void CXDlgCalculatingProgress::slotSetWindowName( const QString& strName)
{
    setWindowTitle(strName);	
}

void CXDlgCalculatingProgress::slotSetTaskName( const QString& strName)
{
    m_ui.m_pLabelName->setText(strName);
}
void CXDlgCalculatingProgress::slotReset()
{
    m_ui.m_pProgressBar->reset();
    m_bFirstTimeUpdate = true;
}
void CXDlgCalculatingProgress::slotStartComputing()
{
    m_ui.m_pProgressBar->reset();
    m_bFirstTimeUpdate = true;
}

void CXDlgCalculatingProgress::slotFinishComputing()
{
	m_bThreadFinished = true;

	emit this->signalFinishedComputing();
	qApp->processEvents();

	accept();
}

void CXDlgCalculatingProgress::slotTerminated()
{
	_Stopped();
	emit this->signalTerminated();	
}

void CXDlgCalculatingProgress::_Stopped()
{
	m_bThreadFinished = true;

	if (!m_pThread.isNull())
		m_pThread->StopThread();

    reject();
}
void CXDlgCalculatingProgress::slotUpdateProgress(qint64 nCurrentStep, qint64 nTotalStep)
{	
	qint64 nFactor = 1;
	if (nTotalStep > 1000000000) // 10^9
	{
		nFactor = nTotalStep/1000; 
	}
	int nTotalStepINT = static_cast<int>(nTotalStep/nFactor);
	int nCurrentStepINT = static_cast<int>(nCurrentStep/nFactor);

    if (m_bFirstTimeUpdate)
    {        
        m_ui.m_pProgressBar->setRange(0, nTotalStepINT);
        m_bFirstTimeUpdate = false;
    }
    
    m_ui.m_pProgressBar->setValue(nCurrentStepINT);

    _UpdateTimer();
}

void CXDlgCalculatingProgress::slotCancel()
{
	if (m_bThreadFinished)
		return;

	// Pause the thread
	if (!m_pThread.isNull())
		m_pThread->SetPauseFlag();

	QMessageBox msgBox (QMessageBox::Warning,"warning","Do you want to stop calculation?",QMessageBox::Yes | QMessageBox::No,this);

    switch (msgBox.exec())
    {
    case QMessageBox::Yes:
        {
			if (!m_bThreadFinished)
			{
				QString strName = "Abandoning the process...";
				m_ui.m_pLabelName->setText(strName);
				qApp->processEvents();
				_Stopped();
			}
            break;
        }
    case QMessageBox::No:
        {
			if (!m_bThreadFinished && !m_pThread.isNull())
			{
				m_pThread->ResumeThread();
			}
            break;
        }
    default:
        break;		
    }	
}

void CXDlgCalculatingProgress::_UpdateTimer()
{
	unsigned int elapsedTime = QDateTime::currentDateTime().toTime_t() - m_nStartTime;
	int days = elapsedTime/86400;			///< 86400 = 24*60*60
	int hours = (elapsedTime - days*86400)/3600;
	int mins = (elapsedTime - days*86400 - hours*3600)/60;
	int secs = elapsedTime - days*86400 - hours*3600 - mins*60;

	QString strTime = "";

	if (days)
		strTime = QString( strTime + "%1d %2h %3m %4s").arg(days).arg(hours).arg(mins).arg(secs);
	else if (hours)
		strTime = QString( strTime + "%1h %2m %3s").arg(hours).arg(mins).arg(secs);
	else if (mins)
		strTime = QString( strTime + "%1m %2s").arg(mins).arg(secs);
	else
		strTime = QString( strTime + "%1s").arg(secs);

	m_ui.m_pLabelElapsedTime->setText(strTime);
}

void CXDlgCalculatingProgress::closeEvent(QCloseEvent *pEvent)
{
    if (m_bCancelEnabled)
        slotCancel();		

    pEvent->ignore();
}

void CXDlgCalculatingProgress::keyPressEvent(QKeyEvent* pEvent)
{
    if (pEvent->key() == Qt::Key_Escape)
    {
        if (m_bCancelEnabled)
            slotCancel();	
    }
    else
    {
        QWidget::keyPressEvent(pEvent);
    }
}

void CXDlgCalculatingProgress::slotCancelEnabled(bool bCancelEnabled)
{
    m_bCancelEnabled = bCancelEnabled;
    m_ui.m_pBtnCancel->setEnabled(m_bCancelEnabled);
}