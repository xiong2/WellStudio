#include <QMdiSubWindow>
#include <QMdiArea>
#include <QDebug>

#include "xwindowmanager.h"
#include "xglobal.h"
#include "xconsole.h"
#include "xlogview.h"
#include "xcrossplot.h"
#include "xhistogramplot.h"
#include "xwindowtree.h"
#include "x2dsectionwindow.h"
#include "x3dwindow.h"
#include "xbasemapwindow.h"
#include "xtreeconsole.h"

#include "gspdgwindow.h"
#include "gsbasemapwindow.h"
#include "gssectionwindow.h"

CXWindowManager::CXWindowManager(): CXObject("Window Manager")
{
}

CXWindowManager::~CXWindowManager()
{
	CloseAllWindows();
}

CXWindow* CXWindowManager::CreateNewWindow(EXWindowType eType)
{
	CXWindow *pNewWindow = _CreateWindow(eType);

	if (!pNewWindow)
		return NULL;
		
	pNewWindow->InitWindow();

	//	Add the window to the map.
	m_mapWindows[pNewWindow->GetWindowID()] = pNewWindow;

	// Add it to the tree
	CXWindowTree::Instance().AddOneWindow(pNewWindow);

	return pNewWindow;
}

CXWindow* CXWindowManager::_CreateWindow(EXWindowType eType)
{
	QString sName;
	CXWindow *pNewWindow = NULL;

	if(eType == eLogViewWindow)
	{
		sName = "Log View";
		sName = _GetUnallocatedName(sName);
		pNewWindow = new CXLogView(sName);
	}
	else if(eType == eCrossplotWindow)
	{
		sName = "Crossplot";
		sName = _GetUnallocatedName(sName);
		pNewWindow = new CXCrossPlot(sName);
	}
	else if(eType == eHistogramWindow)
	{
		sName = "Histogram";
		sName = _GetUnallocatedName(sName);
		pNewWindow = new CXHistogramPlot(sName);
	}
	else if(eType == e3DWindow)
	{
		sName = "3DWindow";
		sName = _GetUnallocatedName(sName);
		pNewWindow = new CX3DWindow(sName);
	}
	else if(eType == eSectionWindow || eType == eSectionWindowBlank)
	{
		sName = "2D Section Window";
		sName = _GetUnallocatedName(sName);
		pNewWindow = new CX2DSectionWindow(sName);
	}	
	else if (eType == e3DBaseMap)
	{
		sName = "3D Basemap Window";
		sName = _GetUnallocatedName(sName);
		pNewWindow = new CXBaseMapWindow(sName);
	}
	else if (eType == eGSPDGWindow)
	{
		sName = "PDG Window";
		sName = _GetUnallocatedName(sName);
		pNewWindow = new GSPDGWindow(sName);
	}
	else if (eType == eGSBaseMap)
	{
		sName = "GS Basemap Window";
		sName = _GetUnallocatedName(sName);
		pNewWindow = new CGSBasemapWindow(sName);
	}
	else if (eType == eGSSectionWindow)
	{
		sName = "GS Section Window";
		sName = _GetUnallocatedName(sName);
		pNewWindow = new GSSectionWindow(sName);
	}
	else
	{
		return nullptr;
	}
	
	pNewWindow->SetWindowType(eType);
	return pNewWindow;
}

//	To find an unallocated name.
QString CXWindowManager::_GetUnallocatedName(QString sName)
{
	QStringList sListName;
	QMapIterator<QUuid, CXWindow *> it(m_mapWindows);
	while(it.hasNext()) 
	{
		it.next();
		CXWindow *pWindow = (CXWindow *)it.value();
		sListName<<pWindow->GetWindowName();
	}

	if(!sListName.contains(sName))
		return sName;

	int i = 2;
	QString sNewName = sName;
	while(sListName.contains(sNewName))
	{
		sNewName = sName + "(" + QString::number(i) + ")";
		i++;
	}

	return sNewName;
}
CXWindow *CXWindowManager::GetWindowByID(QUuid windowID)
{
	CXWindow *pWindow = NULL;
	QList<CXWindow*> listWindow;
	QMapIterator<QUuid, CXWindow*> it(m_mapWindows);
	while (it.hasNext())
	{
		it.next();
		CXWindow *pWindow = (CXWindow *)it.value();
		if (pWindow->GetObjectID() == windowID )
		{
			return pWindow;
		}
	}
	return NULL;
}

void CXWindowManager::RemoveOneWindow(QUuid windowID)
{
	CXWindowTree::Instance().DeleteOneWindow(windowID);

	/*CXWindow *pWindow = m_mapWindows.value(windowID);
	if (pWindow)
	{
		pWindow->ReleaseResource();
		delete pWindow;
		pWindow = nullptr;
	}*/

	m_mapWindows.remove(windowID);
}

void CXWindowManager::CloseAllWindows()
{
	QList<QUuid> listID = m_mapWindows.keys();
	auto pMainWindow = dynamic_cast<QMainWindow*>(::GetConsole()->GetMainWindowWidget());
	auto pMDI = dynamic_cast<QMdiArea*>(pMainWindow->centralWidget());
		
	for (auto winID : m_mapWindows.keys())
	{
		CXWindowTree::Instance().DeleteOneWindow(winID);
		CXWindow *pWindow = m_mapWindows.value(winID);
		if (pWindow)
		{
			if (pMDI)
			{
				QWidget* pParentWidet = pWindow->parentWidget();
				pMDI->removeSubWindow(pParentWidet);
			}

			pWindow->ReleaseResource();
			delete pWindow;
			pWindow = nullptr;
		}
	}

	m_mapWindows.clear();
}

QList<CXWindow*> CXWindowManager::GetWindowList()
{
	return m_mapWindows.values();
}

QList<CXWindow*> CXWindowManager::_Get3DWindowList()
{
	QList<CXWindow*> listWindow;
	QMap<QUuid, CXWindow *>::iterator it;
	for (it=m_mapWindows.begin(); it!=m_mapWindows.end(); ++it)
	{
		if (it.value()->GetWindowType() == e3DWindow||it.value()->GetWindowType()==e3DBaseMap)
			listWindow.append(it.value());
	}
	return listWindow;
}

bool CXWindowManager::SerializeData(CXArchive &ar)
{
	int i;
	if (ar.IsSaving())
	{
		QList<CXWindow*> listWindow = m_mapWindows.values();/*_Get3DWindowList();*/
		int nSize = listWindow.size();
		ar<<nSize;

		for ( i=0; i<nSize; ++i)
		{
			ar<<listWindow[i]->GetWindowID().toString();
			ar<<listWindow[i]->GetWindowType();

			listWindow[i]->SetModifiedFlag();
			listWindow[i]->SaveScene();
			listWindow[i]->Serialize(true);
		}
	}
	else
	{
		CloseAllWindows();

		if (Qt::ShiftModifier == QApplication::queryKeyboardModifiers()) // security mode
		{
			return true;
		}

		int nSize;
		ar>>nSize;

		for ( i=0; i<nSize; ++i)
		{
			QString windowID;
			int iType;
			ar >> windowID;
			ar >> iType;

			EXWindowType eType = static_cast<EXWindowType>(iType);

			CXWindow *pWindow = _CreateWindow(eType);
			Q_ASSERT(pWindow);
			pWindow->SetObjectID(QUuid(windowID));
			pWindow->Serialize(false);
			pWindow->InitWindow();
			
			m_mapWindows.insert(pWindow->GetWindowID(), pWindow);
			// Add it to the tree
			CXWindowTree::Instance().AddOneWindow(pWindow);

			// Add to the main window
			QMainWindow* pMainWindow = dynamic_cast<QMainWindow*>(::GetConsole()->GetMainWindowWidget());
			QMdiArea *pMDI = dynamic_cast<QMdiArea*>(pMainWindow->centralWidget());
			if(pMDI)
				pMDI->addSubWindow(pWindow);		

			pWindow->show();
			pWindow->InitOpenGL();

			// show objects
			
			QList<QUuid> listObjID = pWindow->GetDisplayedObjects();
			
			// For section window, we should be sure that section is first to display.
			if (eType == eSectionWindow || eType == eSectionWindowBlank)
			{
				auto iter = std::find_if(listObjID.begin(), listObjID.end(), [](const QUuid& id){
					return CX2DSectionWindow::IsSection(id);
				});
				if (iter != listObjID.end())
				{
					std::swap(*iter, *listObjID.begin());
				}
			}
			else if (eType == eGSBaseMap)
			{
				auto iter = std::find_if(listObjID.begin(), listObjID.end(), [](const QUuid& id) {
					EXObjectType eObjType = GetObjectByID(id)->GetObjectType();
					return eObjType == EXGSStressMap || eObjType == EXGS3DHorizonDepth
						|| eObjType == EXGS3DHorizonTWT || eObjType == EXGS3DHorizonIso
						|| eObjType == EXGS3DHorizonAtt;
				});
				if (iter != listObjID.end())
				{
					std::swap(*iter, *listObjID.begin());
				}
			}

			for (const QUuid& id : listObjID)
			{				
				CXTreeConsole::SetObjectVisibility(pWindow, id, true);
			}

			pWindow->RestoreScene();
		}
	}

	return true;
}