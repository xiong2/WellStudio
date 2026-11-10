#ifndef XTHREADMANAGER_H
#define XTHREADMANAGER_H

#include "xdata_global.h"
#include <qmap.h>
#include <quuid.h>

class QThread;
class IKEIO;

class XDATA_EXPORT CXThreadManager
{
public:
	///@brief Get the unique instance of this manager
	static CXThreadManager& Instance();

	///@breif Lock an object
	bool LockObject(IKEIO* pObj, QThread* pThread);

	///@brief Unlock an object
	bool UnlockObject(IKEIO* pObj, QThread* pThread);	

	///@brief Tell if an object is locked or not
	bool IsLocked(IKEIO* pObj);

private:
	CXThreadManager() {}

private:
	QMap<QUuid, QUuid> m_mapToID;
	QMap<QUuid, QThread*> m_mapToThread;
		
};

#endif // RLTHREADMANAGER_H
