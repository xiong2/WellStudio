#ifndef XEVENTCONSOLE_H
#define XEVENTCONSOLE_H

#include "xdef.h"
#include "xdata_global.h"
#include <qset.h>
#include <qmutex.h>
#include <qqueue.h>

class IKEView;

///@brief	The class provides parameters to represent specific event
///@author	Yong Shu
///@date	July, 2014
///@see	
class XDATA_EXPORT CXEventParameter
{
public:
	CXEventParameter(const QUuid& objID, EEventType eEventType, const QUuid& winID = QUuid())
		:m_objID(objID), m_eEventType(eEventType), m_winID(winID){}

	~CXEventParameter() {}

public:
	QUuid m_objID;
	EEventType m_eEventType;
	QUuid m_winID;
	uint time;
};




///@brief	The class provides console to handle all customized events
///@author	Yong Shu
///@date	July, 2014
///@see	
class XDATA_EXPORT CXEventConsole
{
public:
	~CXEventConsole();

public:
	///@brief Get the unique instance of the event console
	static CXEventConsole& Instance();

	///@brief Register and  unregister the view
	void RegisterView(IKEView* pView);
	void UnregisterView(IKEView* pView);

	///@brief Enqueue the event
	void EnqueueEvent(const CXEventParameter& eventPara);

	///@brief Process events
	void ProcessEvent();

	void SetSelfView(IKEView* pSelfView);

private:
	CXEventConsole() {}

private:
	QMutex m_mutex;

	QSet<IKEView*> m_setView;

	QQueue<CXEventParameter> m_paraQueue;

	IKEView* m_pSelfView = nullptr;
};

///@brief	The class provides class to process events automatically
///@author	Yong Shu
///@date	July, 2014
///@see	
class XDATA_EXPORT CXProcessEvent
{
public:
	CXProcessEvent() {}
	CXProcessEvent(IKEView *pSelfView);
	~CXProcessEvent();
	
};

#endif // RLEVENTCONSOLE_H
