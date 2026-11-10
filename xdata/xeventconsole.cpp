#include "xeventconsole.h"
#include "xview.h"
#include <QDateTime>

CXEventConsole::~CXEventConsole()
{

}

CXEventConsole& CXEventConsole::Instance()
{
	static CXEventConsole console;
	return console;
}

void CXEventConsole::RegisterView(IKEView* pView)
{
	QMutexLocker locker(&m_mutex);

	m_setView.insert(pView);
}

void CXEventConsole::UnregisterView(IKEView* pView)
{
	QMutexLocker locker(&m_mutex);

	m_setView.remove(pView);
}

void CXEventConsole::EnqueueEvent(const CXEventParameter& eventPara)
{
	QMutexLocker locker(&m_mutex);

	m_paraQueue.enqueue(eventPara);
}

void CXEventConsole::ProcessEvent()
{
	QMutexLocker locker(&m_mutex);
	uint time = QDateTime::currentDateTime().toTime_t();
	while (!m_paraQueue.isEmpty())
	{
		CXEventParameter para = m_paraQueue.dequeue();
		para.time = time;
		for (auto it = m_setView.begin(); it != m_setView.end(); ++it)
		{
			if (m_pSelfView && m_pSelfView == *it)
				continue;

			(*it)->UpdateView(para);
		}
	}
}

void CXEventConsole::SetSelfView(IKEView* pSelfView)
{
	m_pSelfView = pSelfView;
}

CXProcessEvent::CXProcessEvent(IKEView *pSelfView)
{
	CXEventConsole::Instance().SetSelfView(pSelfView);
}

CXProcessEvent::~CXProcessEvent()
{
	CXEventConsole::Instance().ProcessEvent();
	CXEventConsole::Instance().SetSelfView(nullptr);
}