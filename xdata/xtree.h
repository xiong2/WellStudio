#ifndef XTREE_H
#define XTREE_H

#include <qlist.h>
#include <qmap.h>
#include <quuid.h>
#include "xdata_global.h"
#include "xdef.h"
#include "xview.h"
#include "xobjecttype.h"
#include "xeventconsole.h"

class CXObject;
class QTreeWidget;
class CXTreeWidgetItem;
class QTreeWidgetItem;

class XDATA_EXPORT CXTree : public IKEView
{
public:
	///@brief The unique instance
	static CXTree& Instance();

	///@brief Set the main window tree
	void SetMainWindowTree(QTreeWidget* pTree);

	CXTreeWidgetItem *GetCurTreeItem();
	void SetCurTreeItem(QTreeWidgetItem *pItem);
	void SetCurTreeItem(QUuid uid);

	///@brief Add project to the tree
	void AddProjectToTree();

	///@brief Add a few objects to the tree
	bool AddObjectsToTree(const QList<CXObject*>& listObj);

	///@brief Add one object to the tree
	bool AddOneObject(CXObject* pObj);

	///@brief Get the item from object ID
	CXTreeWidgetItem* GetTreeItemFromID(const QUuid& objID);

	///@breif Check a few nodes and uncheck the rest
	void UpdateTreeStatus(const QList<QUuid>& listObjID, EXWindowType);

	///@brief Only check or uncheck tree items
	void ChangeTreeItemStatus(const QList<QUuid>& listObjID, bool bCheck);
	
	///@brief Change name of tree item when display tree.
	void SetItemName(QUuid objID,QString itemName);

	///@brief Reimplement function from IKEView
	virtual void UpdateView(const CXEventParameter& eventPara) override; 

	///@brief Clear tree items
	void ClearTreeItems();

	///@brief Get IDs of seleceted sibling items
	QList<QUuid> GetSelectedSiblingIDs(const QUuid& uuid);
	///@brief Get IDs of seleceted  items
	QList<QUuid> GetSelectedIDs();

	///@brief Get current selected objects
	CXObject* GetCurrentSelectedObject();

	///@brief Sort child items with given object type under the parent item by name
	bool SortChildItem(CXTreeWidgetItem* pParentItem, EXObjectType eType, bool bAscendant=true);

private:
	CXTree(){}
	CXTree(const CXTree& other) = delete;
	CXTree& operator=(const CXTree& other) = delete;

	void _AddTreeItem(CXTreeWidgetItem* pParentTreeItem, CXObject* pParentObj);
	//	A special kind item whehter be checkable for a special window.
	bool _IsCheckable(CXTreeWidgetItem *, EXWindowType);
	
	QTreeWidget* m_pMainWindowTree = nullptr;
	QMap<QUuid, CXTreeWidgetItem*> m_mapObjIDToItem;	
};

#endif // RLTREE_H
