#include "xio.h"
#include "xglobal.h"
#include "xthreadmanager.h"
#include "xdbio.h"
#include "xproject.h"
#include "xeventconsole.h"

IKEIO::IKEIO(const QUuid& uuid)
:m_objID(uuid)
{
	if (m_objID == ::g_InvalidObjectID)
	{
		m_objID = ::GetUniqueGuid();
	}

	m_bModified = true;
	m_bInDatabase = false;

	m_bDeletable = true;
	updateTimeStamp();
}

IKEIO::~IKEIO()
{
	g_mapIDToObject.remove(m_objID);

	if (::GetProject() && ::GetDBIO())
	{
		::GetProject()->AddDeletedObjectID(m_objID);
	}

}

IKEIO::IKEIO(const IKEIO& other)
:m_eObjType(other.m_eObjType)
{
	this->m_objID = ::GetUniqueGuid();
}

IKEIO& IKEIO::operator=(IKEIO& other)
{
	if (this == &other)
		return *this;

	this->m_eObjType = other.m_eObjType;

	return *this;
}

void IKEIO::SetModifiedFlag()
{
	m_bModified = true;
	updateTimeStamp();
}

void IKEIO::AddEvent(EEventType eEventType, const QUuid& winID)
{
	CXEventConsole::Instance().EnqueueEvent(CXEventParameter(GetObjectID(), eEventType, winID));
}

bool IKEIO::LockObject(QThread* pThread)
{
	return CXThreadManager::Instance().LockObject(this, pThread);
	
}

bool IKEIO::UnlockObject(QThread* pThread)
{
	return CXThreadManager::Instance().UnlockObject(this, pThread);
}

bool IKEIO::Serialize(bool bSave)
{
	if (!m_bModified)
		return false;

	QString strTable = "rlio";

	// save
	if (bSave)
	{
		// Init
		m_bInDatabase = true;
		m_bModified = false;

		QStringList strFieldList;
		strFieldList<<"ID";	
		strFieldList<<"Type";
		strFieldList<<"ContextBLOB";

		QList<QVariant> vtList;

		vtList.append(GetObjectID().toString());
		vtList.append(GetObjectType());

		// Context BLOB
		QByteArray byteArray;
		CXArchive ar(&byteArray, QIODevice::WriteOnly, true);
		SerializeData(ar);
		vtList.append(QVariant(byteArray));	


		return ::GetDBIO()->UpdateInsert(strTable, strFieldList, vtList, GetObjectID().toString());
	}
	else
	{		
		// Init
		m_bModified = false;
		m_bInDatabase = true;


		QStringList strFieldList;
		strFieldList<<"ContextBLOB";

		QSqlQuery query = ::GetDBIO()->Select(strTable, strFieldList, this->GetObjectID().toString());

		if( query.first() )
		{
			int nIndex = -1;		

			// Context BLOB
			QByteArray byteArray = query.value(++nIndex).toByteArray();
			CXArchive ar(&byteArray, QIODevice::ReadOnly, false);
			SerializeData(ar);
		}

		return true;
	}
}

 bool IKEIO::SerializeData(CXArchive& ar)
 {
	 return true;
 }


 /// 更新时间戳
 void IKEIO::updateTimeStamp()
 {
	 m_ObjectTimeStamp = time(NULL);
 }
 /// 对象最后更新的时间戳
 time_t IKEIO::getTimeStamp()
 {
	 return m_ObjectTimeStamp;
 }