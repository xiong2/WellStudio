#include "xtree.h"
#include "xtreewidgetitem.h"
#include "xproject.h"
#include "xglobal.h"
#include "xeventconsole.h"
#include "xbaseconsole.h"
#include <algorithm>
#include "xgeneralfolder.h"

CXTree& CXTree::Instance()
{
	static CXTree object;
	return object;
}

void CXTree::UpdateView(const CXEventParameter& eventPara)
{
	if (eventPara.m_eEventType == EDeleted)
	{
		QTreeWidgetItem* pTreeItem = m_mapObjIDToItem.value(eventPara.m_objID, NULL);
		if (pTreeItem)
		{
			m_pMainWindowTree->removeItemWidget(pTreeItem, 0);
			delete pTreeItem;
			m_mapObjIDToItem.remove(eventPara.m_objID);
		}
	}
	else if (eventPara.m_eEventType == EInfoChanged || 
		     eventPara.m_eEventType == EDataChanged)
	{
		CXObject* pObj = ::GetObjectByID(eventPara.m_objID);
		if (!pObj)
			return;

		CXTreeWidgetItem *pTreeItem=GetTreeItemFromID(eventPara.m_objID);
		if (!pTreeItem)
			return;

		m_pMainWindowTree->blockSignals(true);
		pTreeItem->SetName(pObj->GetObjectName());
		pTreeItem->setIcon(0, QIcon(::GetIconPath() + pObj->GetIconName()));
		m_pMainWindowTree->blockSignals(false);
	}
	else if (eventPara.m_eEventType == EAdded)
	{
		CXObject* pObj = ::GetObjectByID(eventPara.m_objID);
		if (pObj)
		{
			AddOneObject(pObj);
		}
		//if (GetTreeItemFromID(eventPara.m_objID) == NULL)
		//{
		//}
	}
}

void CXTree::AddProjectToTree()
{
	m_pMainWindowTree->clear();
	m_mapObjIDToItem.clear();

	QList<CXObject*> listTop = ::g_pProject->GetChildrenList();
	QList<QTreeWidgetItem*> listTopTreeItem;	

	for (int i=0; i<listTop.size(); ++i)
	{
		CXObject* pTopObj = listTop.at(i);

		//if (!pTopObj || !pTopObj->GetNodeFlag())
		if (!pTopObj)	//	To be compatible with RGS project, whose survey is not tree node.
				continue;

		CXTreeWidgetItem* pTopTreeItem = new CXTreeWidgetItem(pTopObj);		

		pTopTreeItem->setData(0, Qt::CheckStateRole, QVariant());

		listTopTreeItem.append(pTopTreeItem);

		m_mapObjIDToItem.insert(pTopObj->GetObjectID(), pTopTreeItem);

		_AddTreeItem(pTopTreeItem, pTopObj);
	}

	m_pMainWindowTree->addTopLevelItems(listTopTreeItem);
}

bool CXTree::AddObjectsToTree(const QList<CXObject*>& listObj)
{
	for (int i=0; i<listObj.size(); ++i)
	{
		if (!AddOneObject(listObj.at(i)))
			return false;
	}

	return true;
}

bool CXTree::AddOneObject(CXObject* pObj)
{
	if (!pObj || (!pObj->GetNodeFlag() && !dynamic_cast<CXGeneralFolder *>(pObj)))
		return false;

	CXObject* pParentObj = pObj->GetParent();
	if (!pParentObj) return false;

	CXTreeWidgetItem* pParentTreeItem = m_mapObjIDToItem.value(pParentObj->GetObjectID(), nullptr);
	if (pParentTreeItem)
	{
		CXTreeWidgetItem* pTreeItem = this->GetTreeItemFromID(pObj->GetObjectID());
		if (!pTreeItem)
		{
			pTreeItem = new CXTreeWidgetItem(pObj);
			pParentTreeItem->addChild(pTreeItem);
			m_mapObjIDToItem.insert(pObj->GetObjectID(), pTreeItem);
		}
        if (_IsCheckable(pTreeItem, reinterpret_cast<CXBaseConsole*>(::GetConsole())->GetActiveWinowType()))
        {
            m_pMainWindowTree->blockSignals(true);
            pTreeItem->setCheckState(0, Qt::Unchecked);
            m_pMainWindowTree->blockSignals(false);
        }
        else
        {
            m_pMainWindowTree->blockSignals(true);
            pTreeItem->setData(0, Qt::CheckStateRole, QVariant());
            m_pMainWindowTree->blockSignals(false);
        }

		_AddTreeItem(pTreeItem, pObj);

		if (pParentObj->GetObjectType() == EXWellFolder)
		{
			SortChildItem(pParentTreeItem, EXWell, true);
		}
		else if (pParentObj->GetObjectType() == EXWell)
		{
			SortChildItem(pParentTreeItem, EXWellCurve, true);
		}
		return true;
	}
	
	if (pParentObj->GetObjectType() == EXProject)
	{
		CXTreeWidgetItem* pTreeItem = this->GetTreeItemFromID(pObj->GetObjectID());
		if (!pTreeItem)
		{
			pTreeItem = new CXTreeWidgetItem(pObj);
			m_pMainWindowTree->addTopLevelItem(pTreeItem);
			m_mapObjIDToItem.insert(pObj->GetObjectID(), pTreeItem);
		}

		if (_IsCheckable(pTreeItem, reinterpret_cast<CXBaseConsole*>(::GetConsole())->GetActiveWinowType()))
			pTreeItem->setCheckState(0, Qt::Unchecked);
		else
			pTreeItem->setData(0, Qt::CheckStateRole, QVariant());


		_AddTreeItem(pTreeItem, pObj);

		return true;
	}
	
	return false;
}

void CXTree::_AddTreeItem(CXTreeWidgetItem* pParentTreeItem, CXObject* pParentObj)
{
	QList<CXObject*> listChild = pParentObj->GetChildrenList();
	for (int i=0; i<listChild.size(); ++i)
	{
		CXObject* pObj = listChild.at(i);

		if (!pObj || (!pObj->GetNodeFlag() && !dynamic_cast<CXGeneralFolder *>(pObj)))
			//if (!pObj || !pObj->GetNodeFlag())
			continue;

		CXTreeWidgetItem* pTreeItem = this->GetTreeItemFromID(pObj->GetObjectID());
		if (!pTreeItem)
		{
			pTreeItem = new CXTreeWidgetItem(pObj);
			if (QList<EXObjectType>{EX3DPoints, EXFaultSticks, EXFaultPolygon, EX2DPolygon}.contains(pObj->GetObjectType()))
				pTreeItem->setTextColor(0, pObj->GetColor());
			pParentTreeItem->addChild(pTreeItem);
			m_mapObjIDToItem.insert(pObj->GetObjectID(), pTreeItem);
		}

		m_pMainWindowTree->blockSignals(true);
		pTreeItem->setData(0, Qt::CheckStateRole, QVariant());
		m_pMainWindowTree->blockSignals(false);
		
		// Add event
// 		CXProcessEvent eventProcess;
// 		pObj->AddEvent(EAdded);

		_AddTreeItem(pTreeItem, pObj);
	}
	if (pParentObj->GetObjectType() == EXWellFolder)
	{
		SortChildItem( pParentTreeItem, EXWell,  true);
	}
	else if (pParentObj->GetObjectType() == EXWell)
	{
		SortChildItem(pParentTreeItem, EXWellCurve, true);
	}
}

void CXTree::SetMainWindowTree(QTreeWidget* pTree)
{
	m_pMainWindowTree = pTree;
	m_pMainWindowTree->setHeaderHidden(true);
	m_pMainWindowTree->expandAll();
}

CXTreeWidgetItem *CXTree::GetCurTreeItem()
{
	return dynamic_cast<CXTreeWidgetItem *>(m_pMainWindowTree->currentItem());
}

void CXTree::SetCurTreeItem(QTreeWidgetItem *pItem)
{
	m_pMainWindowTree->setCurrentItem(pItem);
}

void CXTree::SetCurTreeItem(QUuid uid)
{
	CXTreeWidgetItem*  pItem = GetTreeItemFromID(uid);
	m_pMainWindowTree->setCurrentItem(pItem);
}

CXTreeWidgetItem* CXTree::GetTreeItemFromID(const QUuid& objID)
{
	return m_mapObjIDToItem.value(objID, NULL);
}

void CXTree::SetItemName(QUuid objID,QString itemName)
{
	CXTreeWidgetItem *pTreeItem=GetTreeItemFromID(objID);
	if(pTreeItem)	
	{ 
		pTreeItem->SetName(itemName);
	}

}

void CXTree::UpdateTreeStatus(const QList<QUuid>& listObjID, EXWindowType eWindowType)
{
	m_pMainWindowTree->blockSignals(true);

	// all reset states.
	const QList<CXTreeWidgetItem*>& listAllItem = m_mapObjIDToItem.values();
	for (auto pItem : listAllItem)
	{
		if (_IsCheckable(pItem, eWindowType))
		{
			pItem->setCheckState(0, Qt::Unchecked);
		}
		else
		{
			pItem->setData(0, Qt::CheckStateRole, QVariant());
		}
	}

	// check
	for (auto it = m_mapObjIDToItem.begin(); it != m_mapObjIDToItem.end(); ++it)
	{
		CXTreeWidgetItem* pItem = it.value();
		if (!pItem) 
			continue;

		if (listObjID.contains(it.key()))
		{
			if (!_IsCheckable(pItem, eWindowType)) 
				continue;

			pItem->setCheckState(0, Qt::Checked);
			QTreeWidgetItem* pParentItem = pItem->parent();
			while (pParentItem)
			{
				if (pParentItem->data(0, Qt::CheckStateRole) != QVariant() && pParentItem->checkState(0) != Qt::Checked)
				{
					pParentItem->setCheckState(0, Qt::Checked);
				}
				pParentItem = pParentItem->parent();
			}
		}
	}

	m_pMainWindowTree->blockSignals(false);
}

void CXTree::ChangeTreeItemStatus(const QList<QUuid>& listObjID, bool bChecked)
{
	m_pMainWindowTree->blockSignals(true);
	for (auto iter = m_mapObjIDToItem.begin(); iter != m_mapObjIDToItem.end(); ++iter)
	{
		if (!listObjID.contains(iter.key()) || iter.value()->data(0, Qt::CheckStateRole).isNull())
			continue;

		iter.value()->setCheckState(0, bChecked ? Qt::Checked : Qt::Unchecked);
	}
	m_pMainWindowTree->blockSignals(false);
}

bool CXTree::_IsCheckable(CXTreeWidgetItem *pItem, EXWindowType eWinType)
{
	CXObject *pObj = pItem->GetKEObject();
	EXObjectType eObjType = EXBegin;
	if(pObj)
		eObjType = pObj->GetObjectType();

	if(eWinType == eNoWindow)
	{
		//	No window means no item could be checked.!
		return false;
	}
	else if(eWinType == eLogViewWindow)
	{
		//	So far only accept well, curve and well tops.
		if(eObjType != EXWell && eObjType != EXWellCurve && eObjType != EXWellTops)
		{
			return false;
		}
	}
	else if(eWinType == eCrossplotWindow)
	{
		//	Now we select objects on crossplot window, not on tree.
		return false;
	}
	else if(eWinType == eHistogramWindow)
	{
		return pObj->HasHistogram();
	}
	else if (eWinType == eSectionWindowBlank)
	{
		if (eObjType == EXSeismicSection || eObjType == EXRandomSection || eObjType == EX2DSeismicLine)
		{
			return true;
		}
		else
			return false;
	}
	else if (eWinType == eSectionWindow)
	{
		if (eObjType == EXSeismicSection || eObjType == EXRandomSection
			|| eObjType == EXWell || eObjType == EXWellCurve || eObjType == EXWellCurveAlias || eObjType == EXWellFolder
			|| eObjType == EXFaultFolder || eObjType == EXFaultSticks
			|| eObjType == EX3DSurface || eObjType == EX3DHorizon || eObjType == EXSurfaceFolder || eObjType == EXHorizonFolder
			|| eObjType == EX2DSeismicLine
			|| eObjType == EXWellTops || eObjType == EXWellTopFormation
			|| eObjType == EXLowFrequencyModel)
		{
			return true;
		}
		else
			return false;
	}
	else if(eWinType == e3DBaseMap)
	{
		//	So far well curves, curve alias, well tops, sub volume can not display on base map.
		if(eObjType == EXWellCurve || eObjType == EXWellCurveAlias || eObjType == EXWellCurveAliasFolder
			|| eObjType == EXWellTops || eObjType == EXWellTopFormation || eObjType == EXSeismicDataLine
			|| eObjType == EXSeismicSubVolume)
		{
			return false;
		}
	}
	else if(eWinType == e3DWindow)
	{
		//	So far only reservoir model node could not be checked.
		if (eObjType == EXReservoirModel || eObjType == EX2DSeismicLine || eObjType == EXLFMAttributeFolder
			 || eObjType == EXWellCurveAliasFolder)
			return false;
	}
	else if (eWinType == eGSBaseMap)
	{
		if (eObjType == EXGS3DHorizonTWT || eObjType == EXGS3DHorizonDepth
			|| eObjType == EXGS3DHorizonIso || eObjType == EXGS3DHorizonAtt
			|| eObjType == EXGSStressMap || eObjType == EXGSSection
			|| eObjType == EXGSPDG || eObjType == EXGSRoseDiagram)
			return true;
		else
			return false;
	}
	else if (eWinType == eGSPDGWindow)
	{
		if (eObjType == EXGSPDG)
			return true;
		else
			return false;
	}
	else if (eWinType == eGSSectionWindow)
	{
		if (eObjType == EXGSSection)
			return true;
		else
			return false;
	}

	return true;
}

void CXTree::ClearTreeItems()
{
	m_pMainWindowTree->clear();
	m_mapObjIDToItem.clear();
}

QList<QUuid> CXTree::GetSelectedSiblingIDs(const QUuid& uuid)
{
	QList<QUuid> listID;

	CXTreeWidgetItem* pItem = this->GetTreeItemFromID(uuid);
	if (!pItem)
		return listID;

	CXTreeWidgetItem* pParent = dynamic_cast<CXTreeWidgetItem*>(pItem->parent());
	if (!pParent)
	{
		int nCount = m_pMainWindowTree->topLevelItemCount();
		for (int i=0; i<nCount; ++i)
		{
			CXTreeWidgetItem* pChildItem = dynamic_cast<CXTreeWidgetItem*>(m_pMainWindowTree->topLevelItem(i));
			if (pChildItem && pChildItem->isSelected())
				listID.append(pChildItem->GetObjID());				
		}
	}
	else
	{
		int nCount = pParent->childCount();
		for (int i=0; i<nCount; ++i)
		{
			CXTreeWidgetItem* pChildItem = dynamic_cast<CXTreeWidgetItem*>(pParent->child(i));
			if (pChildItem && pChildItem->isSelected())
				listID.append(pChildItem->GetObjID());
		}
	}

	return listID;
}

///@brief Get IDs of seleceted  items
QList<QUuid> CXTree::GetSelectedIDs()
{
	QList<QUuid> listID;
	QList<QTreeWidgetItem *>lst = m_pMainWindowTree->selectedItems();
	for (int i = 0; i < lst.count();i++)
	{
		CXTreeWidgetItem* pChildItem = dynamic_cast<CXTreeWidgetItem*>(lst[i]);
		if (pChildItem )
			listID.append(pChildItem->GetObjID());
	}
	return listID;
}

CXObject* CXTree::GetCurrentSelectedObject()
{
	if (!m_pMainWindowTree)
		return NULL;

	QList<QTreeWidgetItem*> listItem = m_pMainWindowTree->selectedItems();
	if (listItem.isEmpty())
		return NULL;

	for (int i = 0; i < listItem.size(); ++i)
	{
		CXTreeWidgetItem* pItem = dynamic_cast<CXTreeWidgetItem*>(listItem[i]);
		if (!pItem)
			continue;

		CXObject* pObj = pItem->GetKEObject();
		if (!pObj)
			continue;

		return pObj;
	}

	return NULL;

}

bool CXTree::SortChildItem(CXTreeWidgetItem* pParentItem, EXObjectType eType, bool bAscendant)
{
	if (!pParentItem)
		return false;

	CXObject* pObj = ::GetObjectByID(m_mapObjIDToItem.key(pParentItem));
	if (!pObj)
		return false;

	QList<CXObject*> listChild = pObj->GetChildren(eType, false);
	if (listChild.isEmpty())
		return false;

	// sort
	std::vector<CXTreeWidgetItem*> vecItem;
	for (int i = 0; i < listChild.size(); ++i)
	{
		CXTreeWidgetItem* pItem = m_mapObjIDToItem.value(listChild[i]->GetObjectID());
		if (pItem)
		{
			vecItem.push_back(pItem);
		}
	}
	if (vecItem.size() < 1)
	{
		return true;
	}
	std::sort(vecItem.begin(), vecItem.end(), [](CXTreeWidgetItem* p1, const CXTreeWidgetItem* p2)
	{
		return p1->GetName().toLower() < p2->GetName().toLower(); 
	});

	if (!bAscendant)
	{
		std::reverse(vecItem.begin(), vecItem.end());
	}

	// take from parent item
	for (int i = 0; i < vecItem.size(); ++i)
	{
		pParentItem->takeChild(pParentItem->indexOfChild(vecItem[i]));
	}

	// re-add all items
	QList<QTreeWidgetItem*> listItem;
	for (int i = 0; i < vecItem.size(); ++i)
	{
		listItem.append(vecItem[i]);
	}
	pParentItem->insertChildren(pParentItem->childCount(), listItem);

	return true;
}
