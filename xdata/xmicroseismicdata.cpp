#include "xmicroseismicdata.h"
#include "xobjectfactory.h"
#include "xdbinmemory.h"
#include <qsqlrecord.h>


BEGIN_REGISTER_OBJECT_TO_FACTORY(CXMicroSeismicData)
EXMicroSeismicData
END_REGISTER_OBJECT_TO_FACTORY(CXMicroSeismicData)

CXMicroSeismicData::CXMicroSeismicData(const QString& strName)
	: CXObject(strName)
{
	m_nRecordNum = 0;

	SetObjectType(EXMicroSeismicData);
	SetIconName("MicroSeismic.png");
	m_strTableName = "microseismic";	
	m_strListKeyName<<"RecordID";

	m_pDBInMemory = new CXDBInMemory(m_strTableName, m_strListKeyName);
}

CXMicroSeismicData::~CXMicroSeismicData()
{
	if (m_pDBInMemory)
	{
		delete m_pDBInMemory;
		m_pDBInMemory = NULL;
	}
}

bool  CXMicroSeismicData::InitTables(const QStringList& strListOtherColumnName)
{
	QStringList strEntireListColumnName(m_strListKeyName);

	strEntireListColumnName.append(strListOtherColumnName);

	SetModifiedFlag();

	return m_pDBInMemory->CreateTable(strEntireListColumnName, true);
}


bool CXMicroSeismicData::Serialize(bool bSave)
{
	// base object
	if (!CXObject::Serialize(bSave))
		return false;

	return  m_pDBInMemory->Serialize(bSave);	
}

bool CXMicroSeismicData::AddOneRecord(const QStringList& strListFieldName, QList<QVariant>& listVt)
{
	SetModifiedFlag();

	QStringList strListField(strListFieldName);

	strListField.prepend(m_strListKeyName.front());
	listVt.prepend(QString::number(m_nRecordNum++));

	return m_pDBInMemory->Insert(strListField, listVt);
}

int CXMicroSeismicData::GetPointNum()
{
	m_nRecordNum = m_pDBInMemory->GetRecordNum();
	return m_nRecordNum;
}

QStringList CXMicroSeismicData::GetAllFieldNames()
{
	QStringList strListFieldName = m_pDBInMemory->GetAllFieldNames();

	for (int i=0; i<m_strListKeyName.size(); ++i)
	{
		strListFieldName.removeAll(m_strListKeyName.at(i));
	}

	return strListFieldName;
}

void CXMicroSeismicData::GetPointPosition(vector<double>& vecX, vector<double>& vecY, vector<double>& vecZ)
{
	GetPointNum();

	// resize vectors
	vecX.resize(m_nRecordNum);
	vecY.resize(m_nRecordNum);
	vecZ.resize(m_nRecordNum);

	QString strSql = "SELECT * FROM ";
	strSql += m_strTableName;
	QSqlQuery queryNew(*(m_pDBInMemory->GetDB())); 
	{
		queryNew.prepare(strSql);
		queryNew.exec();
	}

	int index = 0;
	while (queryNew.next())
	{
		QSqlRecord record = queryNew.record();
		vecX[index] = record.value("X").toDouble();
		vecY[index] = record.value("Y").toDouble();
		vecZ[index] = record.value("Z").toDouble();

		++index;
	}
}

void CXMicroSeismicData::GetOtherAttribute(const QString& strAttName, vector<QVariant>& vecVariant)
{
	GetPointNum();

	// resize vectors
	vecVariant.resize(m_nRecordNum);

	QString strSql = "SELECT * FROM ";
	strSql += m_strTableName;
	QSqlQuery queryNew(*(m_pDBInMemory->GetDB())); 
	{
		queryNew.prepare(strSql);
		queryNew.exec();
	}

	int index = 0;
	while (queryNew.next())
	{
		QSqlRecord record = queryNew.record();
		vecVariant[index++] = record.value(strAttName);
	}
}

void CXMicroSeismicData::_SetSelfDimension()
{
	GetPointNum();
	if (m_nRecordNum < 1)
		return;

	double dX, dY, dZ, dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	QString strSql = "SELECT * FROM ";
	strSql += m_strTableName;
	QSqlQuery queryNew(*(m_pDBInMemory->GetDB()));
	{
		queryNew.prepare(strSql);
		queryNew.exec();
	}

	if (queryNew.next())
	{
		QSqlRecord record = queryNew.record();
		dXMin = dXMax = record.value("X").toDouble();
		dYMin = dYMax = record.value("Y").toDouble();
		dZMin = dZMax = record.value("Z").toDouble();
	}

	while (queryNew.next())
	{
		QSqlRecord record = queryNew.record();
		dX = record.value("X").toDouble();
		dY = record.value("Y").toDouble();
		dZ = record.value("Z").toDouble();

		dXMin = dXMin < dX ? dXMin : dX;
		dXMax = dXMax > dX ? dXMax : dX;
		dYMin = dYMin < dY ? dYMin : dY;
		dYMax = dYMax > dY ? dYMax : dY;
		dZMin = dZMin < dZ ? dZMin : dZ;
		dZMax = dZMax > dZ ? dZMax : dZ;
	}

	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}

QStringList CXMicroSeismicData::GetDescription()
{
	QStringList strListDesc;
	GetPointNum();
	
	strListDesc << "Events Number:" << QString::number(m_nRecordNum);

	return strListDesc;
}