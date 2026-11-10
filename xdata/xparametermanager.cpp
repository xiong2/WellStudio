#include <cassert>
#include "xparametermanager.h"
#include "xobjectfactory.h"
#include "xbaseparameter.h"

CXParameterManager::CXParameterManager()
{
}


CXParameterManager::~CXParameterManager()
{
	ClearMap();
}

void CXParameterManager::AddParameter(const QUuid& ObjID, const CXBaseParameter& parameter)
{
	CXBaseParameter* pPara = dynamic_cast<CXBaseParameter*>(CXObjectFactory::Instance().CreateObject(parameter.GetObjectType()));
	assert(pPara);
	*pPara = parameter;	
	
	m_mapIDToParameter.insert(ObjID, pPara);	

	SetModifiedFlag();
}

CXBaseParameter* CXParameterManager::GetParameterByID(const QUuid& ObjID)
{
	return m_mapIDToParameter.value(ObjID, NULL);
}

void CXParameterManager::RemoveOneParameter (const QUuid& ObjID)
{
	CXBaseParameter* pPara = m_mapIDToParameter.value(ObjID, NULL);
	m_mapIDToParameter.remove(ObjID);
	if (pPara)
		delete pPara;	

	SetModifiedFlag();
}

void CXParameterManager::ClearMap()
{
	// Parameter
	QMap<QUuid, CXBaseParameter*>::iterator it;
	for (it = m_mapIDToParameter.begin(); it != m_mapIDToParameter.end(); ++it)
	{
		CXBaseParameter* pPara = it.value();
		delete pPara;
	}
	m_mapIDToParameter.clear();	
}

bool CXParameterManager::SerializeData (CXArchive & ar)
{
	if(ar.IsSaving())
	{
		int nCount = m_mapIDToParameter.size();
		ar<<nCount;

		QMap<QUuid, CXBaseParameter*>::iterator it;
		for (it=m_mapIDToParameter.begin(); it != m_mapIDToParameter.end(); ++it)
		{
			QUuid ObjID = it.key();
			CXBaseParameter* pPara = it.value();
			assert(pPara);
			EXObjectType eType = pPara->GetObjectType();

			ar<< ObjID.toString();
			ar<< (int)eType;
			ar << pPara->GetObjectID().toString();

			pPara->Serialize(ar.IsSaving());
		}
	}
	else
	{
		ClearMap();

		int nCount;
		ar>> nCount;

		QString strObjID;	
		QString paraObj;
		int nType;
		EXObjectType eType;

		for (int i=0; i<nCount; ++i)
		{			
			ar>> strObjID;
			ar>> nType;

			ar >> paraObj;

			eType = static_cast<EXObjectType>(nType);

			CXBaseParameter* pPara = dynamic_cast<CXBaseParameter*>(CXObjectFactory::Instance().CreateObject(eType));
			assert(pPara);

			pPara->SetObjectID(QUuid(paraObj));

			pPara->Serialize(ar.IsSaving());

			m_mapIDToParameter.insert(QUuid(strObjID), pPara);
		}
	}
	
	return true;
}
