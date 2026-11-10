#include "xdbinmemory.h"
#include "xglobal.h"
#include <qsqlrecord.h>
#include <qmap.h>
#include <vector>

CXDBInMemory::CXDBInMemory(const QString& strTableName, const QStringList& strListKey)
	:m_strTableName(strTableName), m_strListKey(strListKey)
{
	m_pDBInMem = new CXDBIO();
	m_bOpen = m_pDBInMem->ConnectDB("", true);

	m_bModified = true;
}

CXDBInMemory::~CXDBInMemory()
{
	if (m_pDBInMem)
	{
		delete m_pDBInMem;
		m_pDBInMem = NULL;
	}
}

bool CXDBInMemory::CreateTable(const QStringList& strListFieldName, bool bInMemory)
{
	if (!m_bOpen)
		return false;
		
	QString strSql("CREATE TABLE ");

	strSql += m_strTableName;
	strSql += " ( ";

	// set all columns
	int nSize = strListFieldName.size();
	for (int i=0; i<nSize; ++i)
	{
		strSql += strListFieldName.at(i);
		strSql += " ";
		strSql += "TEXT";
		
		if (m_strListKey.contains(strListFieldName.at(i)))
		{
			strSql += " NOT NULL";
		}
		strSql += ", ";
	}

	// Set constraint
	strSql += "CONSTRAINT ";

	QString strKeyText(m_strListKey.at(0));
	for (int i=1; i<m_strListKey.size(); ++i)
	{
		strKeyText += "_";
		strKeyText += m_strListKey.at(i);
	}

	strSql += strKeyText;
	strSql += " PRIMARY KEY (";
	for (int i=0; i<m_strListKey.size(); ++i)
	{
		strSql += m_strListKey.at(i);

		if (i != m_strListKey.size()-1)
		{
			strSql += ", ";
		}
		else
		{
			strSql += ") ";
		}
	}

	strSql += ")";

	// Create table
	bool bSuccess;
	CXDBIO* pRLDB;
	if (bInMemory)
	{
		pRLDB = m_pDBInMem;
	}
	else
	{
		pRLDB = ::GetDBIO();
	}

	QSqlQuery query(*(pRLDB->GetDB()));
	{
		query.prepare(strSql);
		bSuccess = query.exec();
	}
	
	return bSuccess;
}

bool CXDBInMemory::Update(const QStringList& strFieldList, const QList<QVariant>& valueList, const QStringList& strListKeyName, const QStringList& strListKeyValue)
{
	m_bModified = true;
	return m_pDBInMem->Update(m_strTableName, strFieldList, valueList, strListKeyName, strListKeyValue);
}

bool CXDBInMemory::Insert(const QStringList& strFieldList, const QList<QVariant>& valueList)
{
	m_bModified = true;
	return m_pDBInMem->Insert(m_strTableName, strFieldList, valueList);
}

QSqlQuery CXDBInMemory::Select(const QStringList& strFieldList, const QStringList& strListKeyName, const QStringList& strListKeyValue)
{
	return m_pDBInMem->Select(m_strTableName, strFieldList, strListKeyName, strListKeyValue);
}

bool CXDBInMemory::Serialize(bool bSave)
{
	if (bSave)
	{
		if (!m_bModified)
			return true;

		// delete old table
		QString strSql ("DROP TABLE ");
		strSql += m_strTableName;
		QSqlQuery query(*(::GetDBIO()->GetDB())); 
		{
			query.prepare(strSql);
			query.exec();
		}

		// Save
		QStringList strListFieldName;		

		strSql = "SELECT * FROM ";
		strSql += m_strTableName;
		QSqlQuery queryNew(*(m_pDBInMem->GetDB())); 
		{
			queryNew.prepare(strSql);
			queryNew.exec();
		}

		// Create a new table in project DB
		{			
			QSqlRecord record = queryNew.record();
			int nCount = record.count();
			for (int i=0; i<nCount; ++i)
			{
				strListFieldName.append(record.fieldName(i));
			}
			CreateTable(strListFieldName, false);
		}

		// Save data
		while(queryNew.next())
		{
			QList<QVariant> valueList;
			QSqlRecord record = queryNew.record();
			int nCount = record.count();
			for (int i=0; i<nCount; ++i)
			{				
				valueList.append(record.value(i));
			}
			::GetDBIO()->Insert(m_strTableName, strListFieldName, valueList);
		}		

		m_bModified = false;

		return true;
	}
	else //load
	{
		QStringList strListFieldName;		

		QString strSql = "SELECT * FROM ";
		strSql += m_strTableName;
		QSqlQuery queryNew(*(::GetDBIO()->GetDB())); 
		{
			queryNew.prepare(strSql);
			queryNew.exec();
		}

		// Create a new table in memory
		{			
			QSqlRecord record = queryNew.record();
			int nCount = record.count();
			for (int i=0; i<nCount; ++i)
			{
				strListFieldName.append(record.fieldName(i));
			}
			CreateTable(strListFieldName, true);
		}
		
		// Load data
		while(queryNew.next())
		{
			QList<QVariant> valueList;
			QSqlRecord record = queryNew.record();
			int nCount = record.count();
			for (int i=0; i<nCount; ++i)
			{				
				valueList.append(record.value(i));
			}
			m_pDBInMem->Insert(m_strTableName, strListFieldName, valueList);
		}		

		m_bModified = false;

		return true;

	}
}

QStringList CXDBInMemory::GetAllFieldNames()
{
	QStringList strList;
	if (!m_bOpen)
		return strList;

	QSqlRecord record = m_pDBInMem->GetDB()->record(m_strTableName);
	int nCount = record.count();
	for (int i=0; i<nCount; ++i)
	{
		strList.append(record.fieldName(i));
	}

	return strList;
}

int CXDBInMemory::GetRecordNum()
{
	QString strSql = "SELECT * FROM ";
	strSql += m_strTableName;
	QSqlQuery queryNew(*(m_pDBInMem->GetDB())); 
	{
		queryNew.prepare(strSql);
		queryNew.exec();
	}

	int nCount = 0;
	while (queryNew.next())
	{
		++nCount;
	}

	return nCount;
}

QSqlDatabase* CXDBInMemory::GetDB()
{
	return m_pDBInMem->GetDB();
}

void CXDBInMemory::GetAllWellNameFormation(QStringList& strListWell, QStringList& strListFormation)
{
	QString strSql = "SELECT * FROM ";
	strSql += m_strTableName;
	QSqlQuery queryNew(*(m_pDBInMem->GetDB())); 
	{
		queryNew.prepare(strSql);
		queryNew.exec();
	}

	QString strWellName, strFormation;
	while(queryNew.next())
	{
		QSqlRecord record = queryNew.record();
		strWellName = record.value(m_strListKey.at(0)).toString().toLower();
		strFormation = record.value(m_strListKey.at(1)).toString().toLower();

		if (!strListWell.contains(strWellName))
			strListWell.append(strWellName);

		if (!strListFormation.contains(strFormation))
			strListFormation.append(strFormation);
	}

	strListFormation.clear();
	_SortFormation(strListWell, strListFormation);
}

bool CXDBInMemory::_SortFormation(const QStringList& strListWell, QStringList& strListFormation)
{
	// Get all field names
	QStringList strListFieldNames = GetAllFieldNames();
	QString strZName;
	if (strListFieldNames.contains("Depth"))
		strZName = "Depth";
	else
		strZName = "Z";


	// Get sorted formation for each well
	QStringList strFieldList, strListKeyName;
	strFieldList.append(m_strListKey.at(1));
	strFieldList.append(strZName);
	strListKeyName.append(m_strListKey.at(0));

	QList<QStringList> listlistFormation;

	for (int i=0; i<strListWell.size(); ++i)
	{
		QStringList strListKeyValue;
		strListKeyValue.append(strListWell.at(i));

		QSqlQuery query = this->Select(strFieldList, strListKeyName, strListKeyValue);

		QMap<double, QString> map;

		while(query.next())
		{
			QString strFormation = query.value(0).toString();
			double dDepth = query.value(1).toDouble();

			map.insert(dDepth, strFormation);
		}

		QStringList strListForm;
		QMap<double, QString>::iterator it;
		for (it=map.begin(); it != map.end(); ++it)
		{
			strListForm.append(it.value());
		}
		listlistFormation.append(strListForm);
	}

	if (listlistFormation.empty())
		return false;

	int nTotalNum;
	bool bForce = false;
	while(!listlistFormation.empty())
	{
		nTotalNum = _GetTotalNum(listlistFormation);

		for (int i=0; i<listlistFormation.size(); ++i)
		{
			if (listlistFormation[i].empty())
				continue;			

			QString strName = listlistFormation[i][0];
			bool bFoundOne = true;
			for (int j=0; j<listlistFormation.size(); ++j)
			{
				if (i==j)
					continue;				

				if (listlistFormation[j].empty())
					continue;

				if (listlistFormation[j].indexOf(strName, 1) != -1)
				{
					bFoundOne = false;
					break;
				}
			}
			if (!bFoundOne)
			{
				// in case imcompatible formations (F1 > F2 in one well, and F1 < F2 in another well)
				if (!bForce)
					continue;
				else
					bForce = false;
			}				

			strListFormation.append(strName);

			// Delete
			for (int j=0; j<listlistFormation.size(); ++j)
			{
				listlistFormation[j].removeAll(strName);
			}
			break;
		}

		for (int i=0; i<listlistFormation.size(); ++i)
		{
			if (listlistFormation[i].empty())
				listlistFormation.removeAt(i);
		}

		if (nTotalNum == _GetTotalNum(listlistFormation))
		{
			bForce = true;
		}
	}

	return true;
}

int CXDBInMemory::_GetTotalNum(QList<QStringList>& liststrList)
{
	int nSum = 0;
	for (int i=0; i<liststrList.size(); ++i)
	{
		nSum += liststrList[i].size();
	}
	return nSum;
}


