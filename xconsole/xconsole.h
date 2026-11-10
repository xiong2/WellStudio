#ifndef CRLCONSOLE_H
#define CRLCONSOLE_H

#include "xconsole_global.h"
#include <quuid.h>
#include <qmap.h>
#include <QPointer>
#include "xdef.h"
#include "xbaseconsole.h"
#include "xwindow.h"

class CXObject;
class CXProject;
class CMainWindow;
class CXDlgCalculator;
class CXWindowManager;
class CXWindow;

///@brief	It's the main console of a RockLog app instance.
///@author	Xiong Xiong
///@date	Apr, 2013
///@see		
class XCONSOLE_EXPORT CXConsole: public CXBaseConsole
{
public:
	CXConsole();
	~CXConsole();

	///	To create a new project.
	CXProject* NewProject();

	///@brief Open a project
	CXProject* OpenProject(QString& strProject, bool bSaveWindowsManager = true);

	///@brief Save a project
	bool SaveProject(bool bSaveWindowsManager = true) override;

	///	Close current project, return false means not close it, maybe user canceled.
	bool CloseCurrentProject();

	///	Open a calculator.
	bool OpenCalculator(QUuid);

	///	Close a calculator.
	void CloseCalculator(QUuid);

	///	Export.
	void ExportDialog(CXObject *);

	///	Change the active window.
	void SetActiveWindow(CXWindow *pWindow);
	QWidget* GetActiveWinow()
	{
		return (QWidget*)m_pCurrentWindow;
	}
	// Get the  window manager
	CXWindowManager *GetWindowManager();

	// Get the viewinfo of current active window
	virtual CXViewInfoObject *GetViewInfoForActiveWindow(QUuid objID);
	virtual CXViewInfoObject* GetViewInfoOfWindow(QUuid objID, CXWindow* pWindow);

	virtual void SetMainWindowWidget(QMainWindow*p);
	virtual QWidget* GetMainWindowWidget();
	virtual EXWindowType  GetActiveWinowType();

	///	Create new window.
	CXWindow* CreateNewWindow(EXWindowType eType);
	virtual QWidget* GetWindowByID(QUuid);
	///	Remove one window.
	void RemoveOneWindow(QUuid windowID);

	void SetWindowVisibility(QUuid windowID, bool bVisible);

	void SetObjectVisibility(QUuid objectID, bool bVisible);

protected:
	CXProject*							m_pProject;				//	The project currently using.
	QPointer<CXWindow>					m_pCurrentWindow;		//	The window currently actived.
	QMainWindow*					m_pMainWindow;
	QMap<QUuid, CXDlgCalculator *>		m_mapCalculator;		//	Map of opened calculator.
	CXWindowManager*					m_pWindowManager;
	QList<CXWindow*>                   m_listDeleteWindow;
};

#endif // RLCONSOLE_H
