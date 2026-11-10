#ifndef XIO_H
#define XIO_H

#include <QUuid>
#include "xdata_global.h"
#include "xobjecttype.h"
#include "xdef.h"
#include "xarchive.h"
#include <time.h>

class QThread;

class XDATA_EXPORT IKEIO 
{
public:
	IKEIO(const QUuid& uuid=QUuid());
	virtual ~IKEIO();

	///@brief Copy constructor
	IKEIO(const IKEIO& other);
	///@brief Assignment operation
	IKEIO& operator=(IKEIO& other);

	///@brief Set and get the object type
	void SetObjectType(EXObjectType eObjType) {m_eObjType = eObjType; m_bModified = true;}
	const EXObjectType GetObjectType() const {return m_eObjType;}

	///@brief Set and get object ID
	void SetObjectID(const QUuid& uuid) {m_objID = uuid; m_bModified = true;}
	const QUuid& GetObjectID()const {return m_objID;}

	///@brief Lock and unlock object with one thread
	bool LockObject(QThread* pThread);
	bool UnlockObject(QThread* pThread);

	///@brief Set and get modification flag
	void SetModifiedFlag();
	const bool GetModifiedFlag()const {return m_bModified;}

	///@brief Add specific event
	void AddEvent(EEventType eEventTypem, const QUuid& winID = QUuid());

	///@breif Tell if the record is in the database
	const bool HasInDatabase() {return m_bInDatabase; }

	///@brief Tell if can be deleted directly by users
	void SetDeletableFlag(bool bDeletable) {m_bDeletable = bDeletable;}
	const bool GetDeletableFlag()const  {return m_bDeletable;}

	///@breif Serialize function
	virtual bool Serialize(bool bSave);

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

private:
	EXObjectType m_eObjType;	

	QUuid m_objID;

	// Flags
	bool m_bModified;
	bool m_bInDatabase;	

	// tell if can be deleted directly by users
	bool m_bDeletable;


public:
	/// 更新时间戳
	virtual void updateTimeStamp();
	/// 对象最后更新的时间戳
	time_t getTimeStamp();
private:
	/// timestamp, 最后更新时间
	time_t m_ObjectTimeStamp;
};

#endif // RLIO_H
