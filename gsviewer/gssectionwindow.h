#ifndef GSSECTIONWINDOW_H
#define GSSECTIONWINDOW_H

#include <QGraphicsScene>
#include <qmainwindow.h>
#include "xwindow.h"
#include "ui_gssectionwindow.h"
#include "gssectionscene.h"
#include "xbasepropertypage.h"

class GSSectionWindow: public CXWindow
{
	Q_OBJECT

public:
	GSSectionWindow(QString strWindowName, QWidget* parent = 0);
	~GSSectionWindow();

	virtual bool SetObjectVisibility(QUuid id, bool isVisible);

	CXBasePropertyPage* CreateVisualizationPage(const QUuid& objID);

	virtual bool IsObjectCanbeDrawn(const CXObject& obj);

	void ShowState(QString);

	virtual CXScene* GetScene()
	{
		return (CXScene *)&m_scene;
	}

protected:
	virtual void addObject(CXObject* pObj);
	virtual void removeObject(CXObject* pObj);

	CXViewInfoObject* createObjectViewInfo(EXObjectType eType);

private:
	Ui::GSSectionWindow ui;
	GSSectionScene m_scene;
};

#endif // GSSECTIONWINDOW_H
