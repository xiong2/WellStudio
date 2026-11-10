#include "xwindowtree.h"
#include <qtreewidget.h>
#include "xproject.h"
#include "xglobal.h"
#include "xwindow.h"
#include "xdef.h"


CXWindowTree& CXWindowTree::Instance()
{
	static CXWindowTree object;
	return object;
}

void CXWindowTree::DeleteOneWindow(const QUuid& objID)
{
	QTreeWidgetItem* pTreeItem = m_mapObjIDToItem.value(objID, NULL);
	if (pTreeItem)
	{
		m_pWindowTree->removeItemWidget(pTreeItem, 0);
		delete pTreeItem;
		m_mapObjIDToItem.remove(objID);
	}
}

void CXWindowTree::_AddWindowFolder()
{
	if (!m_mapTypeToFolder.empty())
		return;

	QList<QTreeWidgetItem*> listTopTreeItem;	

	QTreeWidgetItem* pLogWinItem = new QTreeWidgetItem();
	pLogWinItem->setText(0 , "Logplot Window");

	QTreeWidgetItem* pCPWinItem = new QTreeWidgetItem();
	pCPWinItem->setText(0 , "Crossplot Window");

	QTreeWidgetItem* pHistoWinItem = new QTreeWidgetItem();
	pHistoWinItem->setText(0 , "Histogram Window");

	QTreeWidgetItem* p3DWindow = new QTreeWidgetItem();
	p3DWindow->setText(0,"3D Window");

	QTreeWidgetItem* pSectionWindow = new QTreeWidgetItem();
	pSectionWindow->setText(0, "Section Window");

	QTreeWidgetItem* pBasemapWindow = new QTreeWidgetItem();
	pBasemapWindow->setText(0, "Basemap Window");

	listTopTreeItem.append(pLogWinItem);
	listTopTreeItem.append(pCPWinItem);
	listTopTreeItem.append(pHistoWinItem);
	listTopTreeItem.append(p3DWindow);
	listTopTreeItem.append(pSectionWindow);
	listTopTreeItem.append(pBasemapWindow);

	m_mapTypeToFolder.insert(static_cast<int>(eLogViewWindow), pLogWinItem);
	m_mapTypeToFolder.insert(static_cast<int>(eCrossplotWindow), pCPWinItem);
	m_mapTypeToFolder.insert(static_cast<int>(eHistogramWindow), pHistoWinItem);
	m_mapTypeToFolder.insert(static_cast<int>(e3DWindow),p3DWindow);
	m_mapTypeToFolder.insert(static_cast<int>(eSectionWindow), pSectionWindow);
	m_mapTypeToFolder.insert(static_cast<int>(e3DBaseMap), pBasemapWindow);

	m_pWindowTree->addTopLevelItems(listTopTreeItem);
}

bool CXWindowTree::AddOneWindow(CXWindow* pWindow)
{
	if (!pWindow)
		return false;

	EXWindowType eType = pWindow->GetWindowType();

	QTreeWidgetItem* pWinItem = new QTreeWidgetItem();
	pWinItem->setCheckState(0, Qt::Checked);
	pWinItem->setText(0, pWindow->GetWindowName());

	QTreeWidgetItem* pFolderItem = m_mapTypeToFolder.value((int)eType);
	if (!pFolderItem)
		return false;

	pFolderItem->addChild(pWinItem);
	m_mapObjIDToItem.insert(pWindow->GetWindowID(), pWinItem);

	return true;
}

void CXWindowTree::SetWindowTree(QTreeWidget* pTree)
{
	m_pWindowTree = pTree;
	m_pWindowTree->setHeaderHidden(true);
	m_pWindowTree->expandAll();

	_AddWindowFolder();
}

QTreeWidgetItem* CXWindowTree::GetTreeItemFromID(const QUuid& objID)
{
	return m_mapObjIDToItem.value(objID, NULL);
}

void CXWindowTree::UpdateWindowTreeStatus(const QList<QUuid>& listObjID)
{
	QMap<QUuid, QTreeWidgetItem*>::iterator it;

	for (it=m_mapObjIDToItem.begin(); it!= m_mapObjIDToItem.end(); ++it)
	{
		if (listObjID.contains(it.key()))
		{
			it.value()->setCheckState(0, Qt::Checked);
		}
		else
		{
			it.value()->setCheckState(0, Qt::Unchecked);
		}
	}
}
void CXWindowTree::ClearTreeItems()
{
	QList<QUuid> listID = m_mapObjIDToItem.keys();
	for (int i=0; i<listID.size(); ++i)
	{
		DeleteOneWindow(listID.at(i));
	}
}

