#ifndef GSPDGWINDOW_H
#define GSPDGWINDOW_H

#include "stdafx.h"
#include <QGraphicsScene>
#include "xwindow.h"
#include "ui_gspdgwindow.h"
#include "gspdgscene.h"
#include "xbasepropertypage.h"
#include "gsviewer_global.h"

class GSVIEWER_EXPORT GSPDGWindow: public CXWindow
{
	Q_OBJECT

public:
	GSPDGWindow(QString strWindowName, int iType = 0, QWidget* parent = 0);
	~GSPDGWindow();

	virtual bool SetObjectVisibility(QUuid objID, bool bVisible);

	CXBasePropertyPage* CreateVisualizationPage(const QUuid& objID);

	virtual bool IsObjectCanbeDrawn(const CXObject& obj);

	void ShowState(QString);

	virtual CXScene* GetScene();

protected:
	virtual void addObject(CXObject* pObj);
	virtual void removeObject(CXObject* pObj);

private:
	Ui::GSPDGWindow ui;

	GSPDGScene	m_scene;
	int			m_iType;		//	0 for PDG, 1 for FRG;
};

#endif // GSPDGWINDOW_H
