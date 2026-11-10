#include "xtreewidgetitem.h"
#include "xproject.h"
#include "xglobal.h"
#include <cassert>
#include "xgeneralfolder.h"

CXTreeWidgetItem::CXTreeWidgetItem(CXObject* pObj)
: QTreeWidgetItem(), m_pObject(pObj)
{
	assert(m_pObject);

	m_strName = m_pObject->GetObjectName();
	SetObjID(m_pObject->GetObjectID());

	setText(0, m_pObject->GetObjectName());
	setIcon(0, QIcon(::GetIconPath() + m_pObject->GetIconName()));
	//setFlags(flags() | Qt::ItemIsEditable);
}

CXTreeWidgetItem::~CXTreeWidgetItem()
{
}

void CXTreeWidgetItem::SetName(const QString& strName)
{
	m_strName = strName;	
	setText(0, m_strName);
}


void CXTreeWidgetItem::SetEnabled(bool bEnabled)
{
	m_bEnabled = bEnabled;
	this->setDisabled(!m_bEnabled);
}

CXObject* CXTreeWidgetItem::GetKEObject()
{
	return m_pObject;
}

bool CXTreeWidgetItem::IsDeletable()
{
	if (!m_pObject)
		return true;
	else
		return !m_pObject->IsLocked();
}

bool CXTreeWidgetItem::IsFolder()
{
	if (!m_pObject)
		return false;

	if (dynamic_cast<CXGeneralFolder*>(m_pObject))
		return true;
	else
		return false;
}