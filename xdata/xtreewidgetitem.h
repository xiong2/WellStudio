#ifndef XTREEWIDGETITEM_H
#define XTREEWIDGETITEM_H

#include <qtreewidget.h>
#include "xdata_global.h"
#include <quuid.h>

class CXObject;

class XDATA_EXPORT CXTreeWidgetItem : public QTreeWidgetItem
{
public:
	CXTreeWidgetItem(CXObject* pObj);
	virtual ~CXTreeWidgetItem();

	///@brief Set and get the name
	void SetName(const QString& strName);
	QString GetName() const {return m_strName;}

	///@brief Set and get status
	void SetEnabled(bool bEnabled);
	bool Enabled() {return m_bEnabled;}

	///@brief Set and get the object ID
	void SetObjID(const QUuid& objID) {m_objID = objID;}
	QUuid GetObjID() {return m_objID;}

	///@brief Get the object
	CXObject* GetKEObject();

	///@brief Tell if it can be deleted or not
	bool IsDeletable();

	///@brief Tell if the item is a folder
	bool IsFolder();
private:
	bool m_bEnabled;

	QString m_strName;

	QUuid m_objID;

	CXObject* m_pObject;
	
};

#endif // RLTREEWIDGETITEM_H
