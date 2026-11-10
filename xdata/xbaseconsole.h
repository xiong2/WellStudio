#ifndef _CXBaseConsole_H__
#define _CXBaseConsole_H__

#include "xdata_global.h"
#include "xdef.h"

///@brief	It's the super class of RockLog's console, just used for class comunication.
///@author	Xiong Xiong
///@date	Nov, 2013
///@see		

class CXViewInfoObject;
class CXWindow;
class QWidget;

class XDATA_EXPORT CXBaseConsole
{
public:
    CXBaseConsole();
    virtual ~CXBaseConsole();

	///	Remove one window.
	virtual void RemoveOneWindow(QUuid windowID) = 0;

	///	Close one calculator.
	virtual void CloseCalculator(QUuid objID) = 0;

	// Get ActiveWindow ViewInfo
	virtual CXViewInfoObject* GetViewInfoForActiveWindow(QUuid objID)=0;
	virtual CXViewInfoObject* GetViewInfoOfWindow(QUuid objID, CXWindow* pWindow) = 0;

	///@brief Get the main window widget
	virtual QWidget* GetMainWindowWidget() = 0;
	///@brief Get Active Window.
	virtual 	QWidget* GetActiveWinow() = 0;
	virtual 	EXWindowType  GetActiveWinowType() = 0;
	///	Change the active window.
	virtual void SetActiveWindow(CXWindow *pWindow) = 0;
	virtual QWidget* GetWindowByID(QUuid){return NULL;}

	virtual CXWindow* CreateNewWindow(EXWindowType eType) = 0;

	virtual bool SaveProject(bool bSave = true) = 0;
};

#endif