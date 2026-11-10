#ifndef XWINDOWTREE_H
#define XWINDOWTREE_H

#include <qlist.h>
#include <qmap.h>
#include <quuid.h>
#include "xgraphicview_global.h"

class CXWindow;
class QTreeWidget;
class QTreeWidgetItem;


class XGRAPHICVIEW_EXPORT CXWindowTree 
{
public:
	///@brief The unique instance
	static CXWindowTree& Instance();

	///@brief Delete an object
	void DeleteOneWindow(const QUuid& objID);

	///@brief Set the main window tree
	void SetWindowTree(QTreeWidget* pTree);

	///@brief Add one window to the tree
	bool AddOneWindow(CXWindow* pWindow);

	///@brief Get the item from object ID
	QTreeWidgetItem* GetTreeItemFromID(const QUuid& objID);

	///@breif Check a few nodes and uncheck the rest
	void UpdateWindowTreeStatus(const QList<QUuid>& listObjID);

	///@brief Clear tree items
	void ClearTreeItems();


private:
	void _AddWindowFolder();

private:
	QTreeWidget* m_pWindowTree;

	QMap<int, QTreeWidgetItem*> m_mapTypeToFolder;

	QMap<QUuid, QTreeWidgetItem*> m_mapObjIDToItem;

private:
	CXWindowTree() {}
	CXWindowTree(const CXWindowTree& other);
	CXWindowTree& operator=(const CXWindowTree& other);


	
};

#endif // RLWINDOWTREE_H
