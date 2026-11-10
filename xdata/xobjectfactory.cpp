#include "xobjectfactory.h"
#include "xio.h"


CXObjectFactory& CXObjectFactory::Instance()
{
	static CXObjectFactory object;
	return object;
}

void CXObjectFactory::RegisterObject(EXObjectType eObjType, CreateObjectPfunc pFunc)
{
	m_mapObject.insert(eObjType, pFunc);
}

IKEIO* CXObjectFactory::CreateObject(EXObjectType eObjType)
{
	CreateObjectPfunc pFunc = m_mapObject.value(eObjType, NULL);
	if (pFunc)
	{
		IKEIO* pObject = (*pFunc)();
		pObject->SetObjectType (eObjType);
		return pObject;
	}
	else
		return NULL;
}
