#ifndef _CXWindow_H__
#define _CXWindow_H__

#include "xgui_global.h"
#include <qmainwindow.h>
#include <qmap.h>
#include <qgraphicsview.h>
#include <qgraphicsscene.h>
#include "xobject.h"
#include "xdef.h"
#include "xio.h"
#include "xview.h"

class CXViewInfoObject;
class CXBaseParameter;
class CXScene;

///@brief	It's the super class of all view window in RockLog
///@author	Xiong Xiong
///@date	May, 2013
///@see		
class XGUI_EXPORT CXWindow: public QMainWindow, public IKEIO, public IKEView
{
	Q_OBJECT
public:
	CXWindow(QString sWindowName, QWidget *parent = 0, Qt::WindowFlags f = Qt::Window);
	virtual ~CXWindow();

	//	Really initialize the window, should be called after contstructor.
	virtual void InitWindow();
	virtual void ReleaseResource();
	virtual void SetActive(bool bActive){}

	///	Set and get the window type.
	void SetWindowType(EXWindowType eType) {m_eWindowType = eType;}
	EXWindowType GetWindowType() {	return m_eWindowType;}

	///	Set current window's visibility.
	virtual void SetWindowVisibility(bool bVisible);

	///	Set one object's visibility.
	virtual bool SetObjectVisibility(QUuid objID, bool bVisible);

	///@brief Get the specified object's viewinfo on this window.
	CXViewInfoObject* GetObjectViewInfo(const QUuid& objID);

	///	Get a list of displayed objects.
	QList<QUuid> GetDisplayedObjects();

	///	Get window name.
	QString GetWindowName() {return m_sName;}

	///	Get window ID.
	QUuid GetWindowID() { return GetObjectID();}

	///	Force the scene to refresh.
	void RefreshScene();

	///@breif Serialize function
	virtual bool Serialize(bool bSave);

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	//	To get the actual scene.
	virtual CXScene* GetScene() = 0;
	virtual IKEView* GetOSGScene() { return nullptr; }

	///@brief Get object ID from the view info
	QUuid GetObjIDFromViewInfo(CXViewInfoObject* pViewInfo);

	///@brief Reimplement function from IRLView
	virtual void UpdateView(const CXEventParameter& eventPara); 

	//!@brief Get window viewinfo
	virtual CXBaseParameter* GetWindowInfo();

	//!@brief Save and Restore current scene.
	virtual void SaveScene();
	virtual void RestoreScene();
	virtual void InitOpenGL();

	virtual void UpdateAttribute(const QUuid& uuidGeom, const QUuid& uuidAttr);

signals:
	void signalClose();

private:
	void _FreeOwnResource();

protected:
	//add while don't use mdi to handle window change event
	bool event(QEvent *e);
	//	Add/Remove item may affect the window GUI.
	virtual void itemChanged(bool bAdd, QUuid objectID) {;}		

	QGraphicsView*						m_pView = nullptr;
	CXScene*							m_pScene = nullptr;

	EXWindowType						m_eWindowType;
	QMap<QUuid, CXViewInfoObject *>		m_mapObjViewInfo;
private:
	QString								m_sName;
	
};

#endif