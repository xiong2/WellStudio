#include "stdafx.h"
#include "gspdgwindow.h"
#include "xtree.h"
#include "xglobal.h"
#include "xviewinfoobject.h"
#include "xobject.h"
#include "gsobjitem.h"

GSPDGWindow::GSPDGWindow(QString strWindowName, int iType, QWidget* parent)
	: CXWindow(strWindowName, parent), m_scene(this), m_iType(iType)
{
	setMinimumSize(800, 600);
	ui.setupUi(this);
	ui.PDGView->setScene(&m_scene);

	if(iType == 1)
		setWindowTitle("Fault Seal Graph");
}

GSPDGWindow::~GSPDGWindow()
{

}

CXScene* GSPDGWindow::GetScene()
{
	return (CXScene *)&m_scene;
}

bool GSPDGWindow::IsObjectCanbeDrawn(const CXObject& obj)
{
	if (m_iType == 0)
	{
		if (!QList<EXObjectType>{ EXGSPDG }.contains(obj.GetObjectType()))
			return false;
	}
	else if (m_iType == 1)
	{
		if (!QList<EXObjectType>{ EXGSFRG }.contains(obj.GetObjectType()))
			return false;
	}

	return true;
}

bool GSPDGWindow::SetObjectVisibility(QUuid id, bool isVisible)
{
	CXViewInfoObject* pViewInfo = GetObjectViewInfo(id);
	pViewInfo->SetVisible(isVisible);

	CXObject* pObj = GetObjectByID(id);
	Q_ASSERT(pObj);

	if (isVisible)
	{
		addObject(pObj);

		//	Try to update other objects' status.
		bool bRemoved = false;
		QMapIterator<QUuid, CXViewInfoObject*> it(m_mapObjViewInfo);
		while (it.hasNext())
		{
			it.next();

			if (id == it.key())
				continue;

			CXViewInfoObject *pVInfo = it.value();

			if (!pVInfo->GetVisible())
				continue;

			CXObject* pAObj = GetObjectByID(it.key());
			Q_ASSERT(pAObj);

			if (pObj->GetObjectType() == EXGSPDG)
			{
				if (pAObj->GetObjectType() == EXGSPDG)
				{
					removeObject(pAObj);
					pVInfo->SetVisible(false);
					bRemoved = true;
				}
			}
		}

		//if (bRemoved)
		//	CXTree::Instance().ReloadStatusByCurrentWindow();
	}
	else
	{
		removeObject(pObj);
	}

	return true;
}

void GSPDGWindow::addObject(CXObject* pObj)
{
	m_scene.AddObjectItem(pObj);
}

void GSPDGWindow::removeObject(CXObject* pObj)
{
	m_scene.RemoveObjectItem(pObj);
}

void GSPDGWindow::ShowState(QString str)
{
	ui.statusbar->showMessage(str);
}

CXBasePropertyPage* GSPDGWindow::CreateVisualizationPage(const QUuid& objID)
{
    EXObjectType type           = GetObjectByID(objID)->GetObjectType();
    CXViewInfoObject* pViewInfo = GetObjectViewInfo(objID);
    switch (type)
    {
  //  case EXSection:
		//return new GSSecSectionVisPage(pViewInfo);
    default:
        return nullptr;
    }
}