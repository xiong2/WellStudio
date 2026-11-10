#include "stdafx.h"
#include "xtree.h"
#include "xglobal.h"
#include "xviewinfoobject.h"
#include "gssectionwindow.h"
#include "xobject.h"
#include "gsobjitem.h"
#include "gssecsectionvispage.h"
#include "gssectionviewinfo.h"

GSSectionWindow::GSSectionWindow(QString strWindowName, QWidget* parent)
	: CXWindow(strWindowName, parent), m_scene(this)
{
	setMinimumSize(800, 600);
	ui.setupUi(this);
	ui.sectionView->setScene(&m_scene);
}

GSSectionWindow::~GSSectionWindow()
{

}

bool GSSectionWindow::IsObjectCanbeDrawn(const CXObject& obj)
{
	if (!QList<EXObjectType>{ EXGSSection }.contains(obj.GetObjectType()))
		return false;

	return true;
}

bool GSSectionWindow::SetObjectVisibility(QUuid id, bool isVisible)
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

			if (pObj->GetObjectType() == EXGSSection)
			{
				if (pAObj->GetObjectType() == EXGSSection)
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

void GSSectionWindow::addObject(CXObject* pObj)
{
	m_scene.AddObjectItem(pObj);
}

void GSSectionWindow::removeObject(CXObject* pObj)
{
	m_scene.RemoveObjectItem(pObj);
}

void GSSectionWindow::ShowState(QString str)
{
	ui.statusbar->showMessage(str);
}

CXViewInfoObject* GSSectionWindow::createObjectViewInfo(EXObjectType eType)
{
    switch (eType)
    {
	case EXGSSection:
		return new GSSectionViewInfo;
    default:
        return new CXViewInfoObject;
    }
}

CXBasePropertyPage* GSSectionWindow::CreateVisualizationPage(const QUuid& objID)
{
    EXObjectType type           = GetObjectByID(objID)->GetObjectType();
    CXViewInfoObject* pViewInfo = GetObjectViewInfo(objID);
    switch (type)
    {
    case EXGSSection:
		return new GSSecSectionVisPage(pViewInfo);
    default:
        return nullptr;
    }
}