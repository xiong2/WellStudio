#include "xbaseparameter.h"
#include "xglobal.h"
#include "xarchive.h"
#include <qvariant.h>
#include "xobject.h"

CXBaseParameter::CXBaseParameter()
{
	// Prevent this obejct from sending the event (dynamicpropertychange) when invoking setProperty(...)
	moveToThread(NULL);
}

CXBaseParameter::CXBaseParameter(const CXBaseParameter& other)
{
	moveToThread(NULL);
	_CloneObj(other);
}

CXBaseParameter& CXBaseParameter::operator=(const CXBaseParameter& other)
{
	if (this != &other)
	{
		_CloneObj(other);
	}
	return *this;
}

CXBaseParameter::~CXBaseParameter()
{
}

 bool CXBaseParameter::SerializeData(CXArchive& ar)
 {
	 if (ar.IsSaving())
	 {
		 int nCount = dynamicPropertyNames().count();
		 ar<<nCount;	

		 for (QByteArray propertyName : dynamicPropertyNames())
		 {	 
			 ar << QString(propertyName);
			 ar << property(propertyName.data());
		 }
	 }
	 else
	 {
		 int nCount;
		 ar>> nCount;

		 QString strPropertyName;
		 QVariant varPropertyValue;
		 for(int i=0;i<nCount; ++i)
		 {				
			 ar >> strPropertyName;
			 ar >> varPropertyValue;
			 setProperty(strPropertyName.toLatin1().data(), varPropertyValue);
		 }
	 }
	
	 return true;
 }


QString CXBaseParameter::GetTrueName (const QUuid& ObjID, const QString& strName)
{
	CXObject* pObj = ::GetObjectByID(ObjID);
	if (NULL != pObj)
		return pObj->GetObjectName();

	else
		return strName;
}

QStringList CXBaseParameter::GetTrueNameList (const std::vector<QUuid>& vecObjID, const QStringList& strNameList)
{
	QStringList strList;
	for (int i=0; i<vecObjID.size(); ++i)
	{
		QString strNameTmp = "";
		if (strNameList.size() > i)
			strNameTmp = strNameList.at(i);
		QString strName = GetTrueName(vecObjID.at(i), strNameTmp );
		strList<<strName;
	}

	return strList;
}

void CXBaseParameter::_CloneObj(const CXBaseParameter& Other)
{	
	SetObjectType(Other.GetObjectType());

	for (QByteArray propertyName : Other.dynamicPropertyNames())
	{	
		setProperty(propertyName.data(), Other.property(propertyName.data()));
	}
}
