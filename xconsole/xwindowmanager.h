#ifndef _CXWindowManager_H__
#define _CXWindowManager_H__

#include "xobject.h"
#include "xconsole_global.h"
#include <qmap.h>
#include "xwindow.h"

///@brief	It's the manager of all view windows.
///@author	Xiong Xiong
///@date	Map, 2013
///@see		
class XCONSOLE_EXPORT CXWindowManager : public CXObject
{
public:
	CXWindowManager();
	~CXWindowManager();

	///	Create a new view window and add to the manager.
	CXWindow* CreateNewWindow(EXWindowType);

	///@brief Get All windows.
	QList<CXWindow*> GetWindowList();
	CXWindow *GetWindowByID(QUuid);
	///	Close and remove one window.
	void RemoveOneWindow(QUuid);

	///	Close all windows.
	void CloseAllWindows();

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

private:
	CXWindow* _CreateWindow(EXWindowType eType);
	
	QString _GetUnallocatedName(QString);

	QList<CXWindow*> _Get3DWindowList();


private:
	QMap<QUuid, CXWindow *>	m_mapWindows;

	
};

#endif