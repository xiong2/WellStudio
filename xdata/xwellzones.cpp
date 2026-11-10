#include "xwellzones.h"

#include <QSqlQuery>
#include <qsqlrecord.h>

#include "xobjectfactory.h"
#include "xdbinmemory.h"
#include "xglobal.h"
#include "xproject.h"
#include "x3dpoints.h"
#include "xwell.h"
#include "xwellpath.h"
#include "xwelltopformation.h"


BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellZones)
EXWellZones
END_REGISTER_OBJECT_TO_FACTORY(CXWellZones)

CXWellZones::CXWellZones(const QString& strName)
: CXObject(strName)
{
	SetObjectType(EXWellZones);
	SetIconName("WellTops.png");
	if (strName.isEmpty())
	{
		SetObjectName("WellZones");
	}
}

CXWellZones::~CXWellZones()
{
}

void CXWellZones::GenerateFormations()
{
	//QStringList strListWell, strListFormation;
	//GetWellAndFormation(strListWell, strListFormation);
	//for (int i = 0; i < strListFormation.size(); ++i)
	//{
	//	if (GetChild(strListFormation.at(i), EXWellTopFormation) == NULL)
	//	{
	//		CXWellTopFormation* pFormation = new CXWellTopFormation(strListFormation.at(i));
	//		this->AddChild(pFormation);
	//	}
	//}
}

bool CXWellZones::Serialize(bool bSave)
{
	return  CXObject::Serialize(bSave);
}

// bool CXWellZones::AddOneRecord(const QStringList& strListFieldName, const QList<QVariant>& listVt)
// {
// 	SetModifiedFlag();
// 
// 	return m_pDBInMemory->Insert(strListFieldName, listVt);
// }

bool CXWellZones::AddOneRecord( QString strFormation, QPointF vt)
{
	return AddOneRecord(  strFormation, QString::number(vt.x()), QString::number(vt.y()));
}

bool CXWellZones::AddOneRecord( QString strFormation, QString str1, QString str2, QColor cr)
{
	SetModifiedFlag();

	m_mapPen[strFormation.toLower()].setColor(cr);
	int index = GetOneRecordIndex( strFormation);
	if (index != -1)
	{
		m_lstData[index] = QPair<QString, QString>(str1, str2);
		return true;
	}
	m_lstTopNames.append(strFormation);
	m_lstData.append(QPair<QString, QString>(str1, str2));
	return true;
}
bool CXWellZones::DelOneRecord( QString strFormation)
{

	int index = GetOneRecordIndex( strFormation);
	if (index == -1)
	{
		return true;
	}
	SetModifiedFlag();
	m_lstTopNames.removeAt(index);
	m_lstData.removeAt(index);
	return true;
}
QPair<QString, QString> CXWellZones::GetOneRecord( QString strFormation)
{
	int index = GetOneRecordIndex( strFormation);
	if (index != -1)
	{
		return m_lstData[index];
	}
	return QPair<QString, QString>("","");
}


QColor CXWellZones::GetOneRecordColor(QString strFormation)
{
	strFormation = strFormation.toLower();
	if (m_mapPen.contains(strFormation))
	{
		return m_mapPen[strFormation].color();
	}
	return Qt::blue;

}


QStringList CXWellZones::GetZonesByWell(QString strWellName)
{
	QStringList lstTops;
	strWellName = strWellName.toLower();
	int i;
	for (i = 0; i < m_lstTopNames.count(); i++)
	{
		if (lstTops.contains(m_lstTopNames[i].toLower()) == false)
		{
			lstTops.append(m_lstTopNames[i].toLower());
		}
	}
	return lstTops;
}

int CXWellZones::GetOneRecordIndex( QString strFormation)
{
	strFormation = strFormation.toLower();
	for (int i = 0; i < m_lstData.count(); i++)
	{
		if (m_lstTopNames[i].toLower() == strFormation)
		{
			return i;
		}
	}
	return -1;
}
int CXWellZones::GetRecordNum()
{
	return m_lstData.size();
}

void CXWellZones::GetFormation( QStringList& strListFormation)
{
	int i;

	strListFormation.clear();
	for (i = 0; i < m_lstTopNames.count(); i++)
	{
		if (strListFormation.contains(m_lstTopNames[i].toLower()) == false)
		{
			strListFormation.append(m_lstTopNames[i].toLower());
		}
	}
}


bool CXWellZones::SerializeData(CXArchive& ar)
{
	int flags0 = 201510;
	int flags1;
	QStringList lst;
	if (ar.IsSaving())
	{
		ar << flags0
			<< lst
			<< m_lstTopNames
			<< m_lstData
			<< m_mapPen;
	}
	else
	{
		ar >> flags1
			>> lst
			>> m_lstTopNames
			>> m_lstData
			>> m_mapPen;
	}

	return true;
}
void CXWellZones::ClearData()
{
	m_lstTopNames.clear();
	m_lstData.clear();
	m_mapPen.clear();
}