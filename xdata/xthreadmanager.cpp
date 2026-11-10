#include "xthreadmanager.h"
#include "xio.h"
#include <qthread.h>
#include "xglobal.h"

CXThreadManager& CXThreadManager::Instance()
{
	static CXThreadManager object;
	return object;
}

bool CXThreadManager::LockObject(IKEIO* pObj, QThread* pThread)
{
	if (!pObj || !pThread)
		return false;

	QUuid uuid = ::GetUniqueGuid();

	m_mapToID.insert(uuid, pObj->GetObjectID());
	m_mapToThread.insert(uuid, pThread);

	return true;
}

bool CXThreadManager::UnlockObject(IKEIO* pObj, QThread* pThread)
{
	if (!pObj || !pThread)
		return false;

	QList<QUuid> listIDKey = m_mapToID.keys(pObj->GetObjectID());
	QList<QUuid> listThreadKey = m_mapToThread.keys(pThread);

	for (int i=0; i<listIDKey.size(); ++i)
	{
		if (listThreadKey.contains(listIDKey.at(i)))
		{
			m_mapToID.remove(listIDKey.at(i));
			m_mapToThread.remove(listIDKey.at(i));

			return true;
		}
	}

	return false;
}

bool CXThreadManager::IsLocked(IKEIO* pObj)
{
	if (!pObj)
		return false;

	QMap<QUuid, QUuid>::Iterator it;
	for (it = m_mapToID.begin(); it != m_mapToID.end(); ++it)
	{
		if (it.value() == pObj->GetObjectID())
			return true;
	}

	return false;
}


