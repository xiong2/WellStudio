#include "xconsole.h"
#include "xglobal.h"
#include "xproject.h"
#include "xdlgnewproject.h"
#include "xdlgcalculator.h"
#include "xwindowmanager.h"
#include "xwindow.h"
#include "xtree.h"
#include <qfiledialog.h>
#include <QMdiArea>
#include <qmessagebox.h>
#include "xdbio.h"
#include "xdlgexportlas.h"
#include "xdlgexportsegy.h"
#include "xgeneralfolder.h"
#include "xwaitcursor.h"
#include "xtreeconsole.h"
#include "xviewinfoobject.h"
#include "xtree.h"
#include "xwindowtree.h"
#include "xdlgexporthorizons.h"
#include "xcolormap.h"
#include "xparametermanager.h"
#include "xdlgexportfaultpolygon.h"

CXConsole::CXConsole() : CXBaseConsole()
{
	m_pProject			= NULL;
	m_pMainWindow = NULL;
	m_pWindowManager	= new CXWindowManager;
}

CXConsole::~CXConsole()
{
	CloseCurrentProject();

	delete m_pWindowManager;
}

CXProject* CXConsole::NewProject()
{
	CXDlgNewProject dlg;
	dlg.exec();

	CXProject *pNewProject = dlg.GetProject();
	if (pNewProject)
	{
		CloseCurrentProject();

		m_pProject = pNewProject;
		::SetProject(m_pProject);
        m_pProject->LoadDefaultSetting();

		// read colormap
		CXColormap::InitializeColormapsFromProjectDB();

		m_pProject->AddEvent(EAdded);
		CXProcessEvent P;
	}

	return m_pProject;
}

CXProject* CXConsole::OpenProject(QString& strFileName, bool bSaveWindowsManager)
{
	CXWaitCursor waitcursor;

	if(strFileName == "")
		strFileName = QFileDialog::getOpenFileName(NULL, "Select Project","","*.rdb");

	if (strFileName.isEmpty())
	{
		return NULL;
	}
	if (!strFileName.endsWith(".rdb"))
	{
		QMessageBox::warning(0, "XStudio", "The selected file is not a valid project file.");
		return NULL;
	}

	QFileInfo qFI(strFileName);
	if (!qFI.isWritable())
	{
		QMessageBox::warning(0, "XStudio", "Can not open the specified project!");
		return NULL;
	}

	//	Close current project first, if there's one already opened.
	if (!this->CloseCurrentProject())
		return NULL;
	// merge database
	CXDBIO::MergeDB(strFileName);

	QDir dir(strFileName);
	dir.cdUp();
	QString strProjectDirectory = dir.absolutePath();

	m_pProject = new CXProject("", strProjectDirectory, false, "");
	::SetProject(m_pProject);
	::GetDBIO()->ConnectDB(strFileName);

	// vacuum the database
//	::GetDBIO()->Vacuum();

	m_pProject->Load(qFI.baseName());

	CXTree::Instance().AddProjectToTree();

	// parameter manager
	if (m_pProject->GetParaManagerID().isNull())
	{
		m_pProject->SetParaManagerID(CXParameterManager::Instance().GetObjectID());
	}
	else
	{
		CXParameterManager::Instance().SetObjectID(m_pProject->GetParaManagerID());
		CXParameterManager::Instance().Serialize(false);
	}

	// read colormap
	CXColormap::InitializeColormapsFromProjectDB();

	// Load windows
	m_pWindowManager->SetObjectID(m_pProject->GetWindowManagerID());
	if (bSaveWindowsManager)
	{
		m_pWindowManager->Serialize(false);
	}

	m_pProject->AddEvent(EAdded);
	CXProcessEvent P;
	
	return m_pProject;
}

bool CXConsole::SaveProject(bool bSaveWindowsManager)
{
	if (!m_pProject)
	{
		return false;
	}
	CXWaitCursor waitcursor;

	for (auto pWindow : m_listDeleteWindow)
		pWindow->ReleaseResource();

	if (m_pWindowManager->GetWindowList().size() == 0)
	{
		qDeleteAll(m_listDeleteWindow);
		m_listDeleteWindow.clear();
	}

	m_pProject->SetWindowManagerID(m_pWindowManager->GetObjectID());
	m_pProject->SetParaManagerID(CXParameterManager::Instance().GetObjectID());
	m_pProject->Save();

	::GetDBIO()->Transaction();

	// Save parameters
	CXParameterManager::Instance().Serialize(true);

	// Load windows
	m_pWindowManager->SetModifiedFlag();
	if (bSaveWindowsManager)
	{
		m_pWindowManager->Serialize(true);
	}

	::GetDBIO()->Commit();
	::SetProjectDirty(false);
	return true;
}

bool CXConsole::CloseCurrentProject()
{
	if(m_pProject)
	{
		if(::IsProjectDirty())
		{
			QMessageBox msgBox;
			QString sMessage = "Do you want to save the changes of current project (" + m_pProject->GetObjectName() + ") ?";
			msgBox.setText(sMessage);
			msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Save);
			int ret = msgBox.exec();

			if(ret == QMessageBox::Save)
			{
				SaveProject();
			}
			else if(ret == QMessageBox::Cancel)
			{
				//	User do not want close current project.
				return false;
			}
		}

		QMapIterator<QUuid, CXDlgCalculator *> itC(m_mapCalculator);
		while (itC.hasNext()) 
		{
			itC.next();
			delete itC.value();
		}
		m_mapCalculator.clear();

		//	Close all views here.
		m_pWindowManager->CloseAllWindows();
		delete m_pProject;
		m_pProject = NULL;
		::SetProject(NULL);

		// Clear tree items
		CXTree::Instance().ClearTreeItems();
		CXWindowTree::Instance().ClearTreeItems();
	}

	return true;
}

bool CXConsole::OpenCalculator(QUuid objID)
{
	//	Check exist calculator.
	if(m_mapCalculator.contains(objID))
	{
		m_mapCalculator[objID]->show();
		return true;
	}

	CXObject *pObject = ::GetObjectByID(objID);
	if(!pObject)
		return false;

	if( pObject->GetObjectType() == EXWellCurve || 
		pObject->GetObjectType() == EX3DSurface ||
		pObject->GetObjectType() == EX3DHorizon ||
		pObject->GetObjectType() == EXGS3DHorizonTWT ||
		pObject->GetObjectType() == EXGS3DHorizonDepth ||
		pObject->GetObjectType() == EXGS3DHorizonIso ||
		pObject->GetObjectType() == EXGS3DHorizonAtt)
	{
		pObject = pObject->GetParent();
		objID = pObject->GetObjectID();

		if(m_mapCalculator.contains(objID))
		{
			m_mapCalculator[objID]->show();
			return true;
		}
	}
	else if(pObject->GetObjectType() != EXWell && pObject->GetObjectType() != EXSurfaceFolder
		&& pObject->GetObjectType() != EXHorizonFolder && pObject->GetObjectType() != EXSeismicDataVolume)
	{
		return false;
	}

	CXDlgCalculator *pCalculator = new CXDlgCalculator(objID);
	pCalculator->setWindowTitle("Calculator for " + pObject->GetObjectName());
	m_mapCalculator[objID] = pCalculator;
	pCalculator->show();

	return true;
}

void CXConsole::CloseCalculator(QUuid objID)
{
	if(m_mapCalculator.contains(objID))
	{
		m_mapCalculator.erase(m_mapCalculator.find(objID));
	}
}

void CXConsole::ExportDialog(CXObject *pObj)
{
	if (pObj->GetObjectType() == EXWell || pObj->GetObjectType() == EXWellFolder)
	{
		CXDlgExportLAS dlgExport(pObj);
		dlgExport.exec();
	}
	else if (pObj->GetObjectType() == EXSeismicDataVolume || pObj->GetObjectType() == EXSeismicDataLine)
	{
		CXDlgExportSEGY dlgExport(pObj);
		dlgExport.exec();
	}
	else if (pObj->GetObjectType() == EX3DHorizon || pObj->GetObjectType() == EXHorizonFolder ||
		pObj->GetObjectType() == EX3DSurface || pObj->GetObjectType() == EXSurfaceFolder ||
		pObj->GetObjectType() == EXGS3DHorizonTWT || pObj->GetObjectType() == EXGS3DHorizonDepth ||
		pObj->GetObjectType() == EXGS3DHorizonIso || pObj->GetObjectType() == EXGS3DHorizonAtt)
	{
		CXDlgExportHorizons dlgExport(pObj);
		dlgExport.exec();
	}
	else if (pObj->GetObjectType() == EXFaultPolygonFolder)
	{
		CXDlgExportFaultPolygon dlgExport(pObj);
		dlgExport.exec();
	}
}

CXWindow* CXConsole::CreateNewWindow(EXWindowType eType)
{
	CXWindow *pWindow = m_pWindowManager->CreateNewWindow(eType);

	//	New window should be the active one.
	SetActiveWindow(pWindow);

	return pWindow;
}

void CXConsole::SetActiveWindow(CXWindow *pWindow)
{
	if (!pWindow)
	{
		//	No active window, clear all check boxes.
		QList<QUuid> listBlank;
		CXTree::Instance().UpdateTreeStatus(listBlank, eNoWindow);
	}
	else
	{
		if (!m_pCurrentWindow.isNull()) // previous 
		{
			m_pCurrentWindow->SetActive(false);
		}

		m_pCurrentWindow = pWindow;
		m_pCurrentWindow->SetActive(true);
		CXTree::Instance().UpdateTreeStatus(m_pCurrentWindow->GetDisplayedObjects(), m_pCurrentWindow->GetWindowType());
	}
}

void CXConsole::RemoveOneWindow(QUuid windowID)
{
	if (!m_pCurrentWindow.isNull() && 
		m_pCurrentWindow->GetWindowID() == windowID
		&& (m_pCurrentWindow->GetWindowType() == e3DWindow ||
			m_pCurrentWindow->GetWindowType() == e3DBaseMap))
	{
		m_listDeleteWindow << m_pCurrentWindow.data();		
		CXEventConsole::Instance().UnregisterView(m_pCurrentWindow->GetOSGScene());
		IKEView* pCurrentView = m_pCurrentWindow.data();
		CXEventConsole::Instance().UnregisterView(pCurrentView);

		QMdiArea *pMDI = dynamic_cast<QMdiArea *>(m_pMainWindow->centralWidget());
		if (pMDI)
		{
			pMDI->removeSubWindow(m_pCurrentWindow.data());
		}
	}
	
	m_pCurrentWindow.clear();

	m_pWindowManager->RemoveOneWindow(windowID);
}

void CXConsole::SetWindowVisibility(QUuid windowID, bool bVisible)
{
}
CXWindowManager *CXConsole::GetWindowManager()
{
	return m_pWindowManager; 

}

CXViewInfoObject* CXConsole::GetViewInfoOfWindow(QUuid objID, CXWindow* pWindow)
{
	if (!pWindow)
	{
		return nullptr;
	}

	if (!pWindow->GetDisplayedObjects().contains(objID))
	{
		return nullptr;
	}
	else
	{
		return pWindow->GetObjectViewInfo(objID);
	}
}

CXViewInfoObject *CXConsole::GetViewInfoForActiveWindow(QUuid objID)
{
	return GetViewInfoOfWindow(objID, m_pCurrentWindow.data());
}

void CXConsole::SetObjectVisibility(QUuid objectID, bool bVisible)
{
	if(m_pCurrentWindow.isNull())
		return;

	CXWaitCursor waitCursor;

	CXTreeConsole::SetObjectVisibility(m_pCurrentWindow, objectID, bVisible);
}

void CXConsole::SetMainWindowWidget(QMainWindow*p)
{
	m_pMainWindow = p; 
}

QWidget* CXConsole::GetMainWindowWidget()
{
	return m_pMainWindow;
}

QWidget* CXConsole::GetWindowByID(QUuid uid)
{
	return m_pWindowManager->GetWindowByID(uid);
}

EXWindowType  CXConsole::GetActiveWinowType()
{
	if (m_pCurrentWindow.isNull())
		return eNoWindow;
	else
		return m_pCurrentWindow->GetWindowType();
}
