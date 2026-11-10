#include "gsgeologicstage.h"
#include "xobjectfactory.h"
#include "xproject.h"
#include "xglobal.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(GSGeologicStage)
EXGSGeologicStage
END_REGISTER_OBJECT_TO_FACTORY(GSGeologicStage)

GSGeologicStage::GSGeologicStage()
{
	SetObjectType(EXGSGeologicStage);
	SetIconName("GeologicStage.png");
}

GSGeologicStage::GSGeologicStage(const QString& strName) :CXObject(strName)
{
	SetObjectType(EXGSGeologicStage);
	SetIconName("GeologicStage.png");
}

bool GSGeologicStage::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_listSources;
		ar << m_listHFID;
	}
	else
	{
		m_listSources.clear();
		ar >> m_listSources;
		ar >> m_listHFID;
	}

	return true;
}

QStringList GSGeologicStage::GetDescription()
{
	QStringList strList;

	strList << "Number of regional stress source" << QString::number(m_listSources.count() / 3);

	QStringList strHList;
	foreach(QUuid objID, m_listHFID)
	{
		CXObject *pObj = GetObjectByID(objID);
		strHList << pObj->GetObjectName();
	}

	strList << "Horizons belong to this geologic stage";
	if (strHList.isEmpty())
	{
		strList << "None";
	}
	else
	{
		strList << strHList.join(", ");
	}

	return strList;
}