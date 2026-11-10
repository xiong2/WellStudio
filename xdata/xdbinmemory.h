#ifndef XDBINMEMORY_H
#define XDBINMEMORY_H

#include "xdata_global.h"
#include "xdbio.h"

class CXDBIO;
class QSqlDatabase;

///@brief	The class to represent a database in memory
///@author	Yong Shu
///@date	Sep. 2013
///@see	

class XDATA_EXPORT CXDBInMemory 
{
public:
	CXDBInMemory(const QString& strTableName, const QStringList& strListKey);
	~CXDBInMemory();	
	

	///@brief Create a table. Each field type is TEXT.
	bool CreateTable(const QStringList& strListFieldName, bool bInMemory);

	///@brief Update (Support multiple-column primary key)
	bool Update(const QStringList& strFieldList, const QList<QVariant>& valueList, const QStringList& strListKeyName, const QStringList& strListKeyValue);

	///@breif Select one record (Support multiple-column primary key)
	QSqlQuery Select(const QStringList& strFieldList, const QStringList& strListKeyName, const QStringList& strListKeyValue);

	///@brief Insert DB
	bool Insert(const QStringList& strFieldList, const QList<QVariant>& valueList);

	///@brief Save/Load
	bool Serialize(bool bSave);

	///@brief Get the field names
	QStringList GetAllFieldNames();		

	///@brief Get number of record
	int GetRecordNum();

	///@brief Get well name and formation list
	void GetAllWellNameFormation(QStringList& strListWell, QStringList& strListFormation);

	///@brief Get the database
	QSqlDatabase* GetDB();

private:
	bool _SortFormation(const QStringList& strListWell, QStringList& strListFormation);
	int _GetTotalNum(QList<QStringList>& liststrList);

private:
	CXDBIO* m_pDBInMem;

	QString m_strTableName;

	QStringList m_strListKey;

	bool m_bOpen;

	bool m_bModified;	
	
};

#endif // RLDBINMEMORY_H
