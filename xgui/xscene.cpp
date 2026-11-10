#include "xscene.h"
#include "xwindow.h"
#include "xobjectitem.h"
#include "xeventconsole.h"
#include "xgraphicviewinfo.h"
#include "xglobal.h"

CXScene::CXScene(CXWindow * pWindow, QObject *pParent): QGraphicsScene(pParent)
{
	m_pWindow			= pWindow;
	m_pWindowViewInfo	= NULL;
	m_moveOffset		= QPointF(0, 0);
	m_dZoomScale		= 1.;
}

CXScene::~CXScene()
{
	if(m_pWindowViewInfo)
	{
		delete m_pWindowViewInfo;
		m_pWindowViewInfo = NULL;
	}
}

void CXScene::UpdateView(const CXEventParameter& eventPara)
{
	if (eventPara.m_eEventType == EDeleted)
	{
		DeleteItem(eventPara.m_objID);
	}
}

bool CXScene::DeleteItem(QUuid objectID)
{
	CXObjectItem* pItem = FindItem(objectID);
	if(pItem)
	{
		removeItem(pItem);
		delete pItem;
		return true;
	}

	return false;
}

CXObjectItem* CXScene::FindItem(QUuid objectID, ERLItemType eType)
{
	foreach (QGraphicsItem *item, items())
	{
		CXObjectItem *pItem = dynamic_cast<CXObjectItem *>(item);
		if(pItem)
		{
			if(pItem->GetObjectID() == objectID && (eType == pItem->GetItemType() || eType == eNone))
			{
				return pItem;
			}
		}
	}

	return NULL;
}

QList<CXObjectItem *> CXScene::FindAllItems(EXObjectType eObjType)
{
	QList<CXObjectItem *> listItems;

	foreach(QGraphicsItem *item, items())
	{
		CXObjectItem *pItem = dynamic_cast<CXObjectItem *>(item);
		if (pItem)
		{
			CXObject *pObj = ::GetObjectByID(pItem->GetObjectID());
			if (pObj && pObj->GetObjectType() == eObjType)
			{
				listItems << pItem;
			}
		}
	}

	return listItems;
}

QList<CXObjectItem *> CXScene::FindAllItems(QUuid objectID, ERLItemType eType)
{
	QList<CXObjectItem *> listItems;

	foreach(QGraphicsItem *item, items())
	{
		CXObjectItem *pItem = dynamic_cast<CXObjectItem *>(item);
		if (pItem)
		{
			if (pItem->GetObjectID() == objectID && (eType == pItem->GetItemType() || eType == eNone))
			{
				listItems << pItem;
			}
		}
	}

	return listItems;
}

qreal CXScene::GetCanvasHeight()
{
	return height();
}

qreal CXScene::GetCanvasWidth()
{
	return width();
}