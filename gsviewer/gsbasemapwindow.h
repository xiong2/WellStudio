#ifndef GSBASEMAPWINDOW_H
#define GSBASEMAPWINDOW_H

#include "ui_gsbasemapwindow.h"
#include "xglobalcoordtransform.h"
#include "xwindow.h"
#include "gsbmcoordinateitem.h"
#include "gsbmitembuilderfactory.h"
#include "gsbasemapscene.h"
#include "gscursoritem.h"
#include <QMainWindow>
#include "xbasepropertypage.h"

class CX3DSurvey;

class CGSBasemapWindow : public CXWindow
{
	Q_OBJECT

public:
	CGSBasemapWindow(QString strWindowName, QWidget* parent = 0);
	~CGSBasemapWindow();

	void UpdateView(const CXEventParameter& eventPara) override;
	CXBasePropertyPage* CreateVisualizationPage(const QUuid& objID);
	bool IsObjectCanbeDrawn(const CXObject& obj);

	virtual bool SetObjectVisibility(QUuid objID, bool bVisible);

	virtual CXScene* GetScene()
	{
		return (CXScene *)&m_scene;
	}

private:
	CXViewInfoObject* createObjectViewInfo(EXObjectType eType);
    void addObject(CXObject* pObj);
    void removeObject(CXObject* pObj);
	void updateColormapByID(const QUuid& id);
	void excludingSameTypeObj(CXObject* pObj);

	void setCurrentSurvey(CXObject* pObj);
	void checkCurrentSurvey(CXObject* pObj);

private slots:
	void updateCursorPosition(double dx, double dy, double dz);
	
	void slotCreateRoseDialog();

private:
    Ui::CGSBasemapWindow ui;
    CXGlobalCoordTransform m_coordTransform;
	GSBasemapScene m_scene;
	GSBMItemBuilderFactory m_itemFactory;
	GSBMCoordinateItem m_coordItem;
	GSCursorItem m_cursorItem;
};

#endif // GSBASEMAPWINDOW_H
