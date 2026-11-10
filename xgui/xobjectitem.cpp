#include "xobjectitem.h"
#include "xobject.h"
#include "xglobal.h"

CXObjectItem::CXObjectItem(QUuid objectID, CXViewInfoObject *pViewInfo, QGraphicsItem *parent)
	:QGraphicsRectItem(parent)
{
	m_objectID	= objectID;
	m_pViewInfo	= pViewInfo;
}

QString CXObjectItem::GetObjectName()
{
	CXObject *pObj = ::GetObjectByID(m_objectID);
	if(pObj)
		return pObj->GetObjectName();
	else
		return "";
}

EXObjectType CXObjectItem::GetObjectType()
{
	CXObject *pObj = ::GetObjectByID(m_objectID);
	if (pObj == NULL)
	{
		return EXNullType;
	}
	else
	{
		return pObj->GetObjectType();
	}
}