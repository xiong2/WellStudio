#ifndef X3DWINDOW_H
#define X3DWINDOW_H

#include "x3dwindow_global.h"
#include "xwindow.h"
#include "ui_x3dwindow.h"
#include "xvcrcontrol.h"
#include "xpickhandle.h"
#include "xseismicobject.h"
#include "xwindowinfo3d.h"
#include <QPointer>
#include "x3dscene.h"

class CXOSGWidget;
class QAction;
class QComboBox;
class CXPickhandle;
class CXDlg3DLightingSetting;
class CXSubGridSetting;
class CX3DGlobalCoordMap;
class CXSeismicSection;

class X3DWINDOW_EXPORT CX3DWindow :public CXWindow
{
    Q_OBJECT
public:
    CX3DWindow(QString sWindowName, QWidget *parent = 0, Qt::WindowFlags f = Qt::Window);
    virtual ~CX3DWindow();

signals:
    void UpdateWindowSize(int width, int height);

public:
    virtual void InitWindow();
	virtual void ReleaseResource() override;
	virtual CXScene* GetScene();
	///@brief Get the 3-D scene
	virtual CX3dscene* GetOSGScene() override { return m_pScene; }

    virtual bool SetObjectVisibility(QUuid objID, bool bVisible) override;
	virtual void UpdateAttribute(const QUuid& uuidGeom, const QUuid& uuidAttr) override;

	//!@brief Get window viewinfo
	CXWindowInfo3D* GetWindowInfo() override;

	//!@brief Save and Restore current scene.
	void SaveScene() override;
	void RestoreScene() override;

    ///@brief Get the OSG view widget
    CXOSGWidget* GetOSGViewWidget() { return m_pOSGWidget; }

    ///@brief Get the Z scale
    float GetZScale();

    ///@brief Get current size of widget
    virtual void resizeEvent(QResizeEvent *event);

    ///@brief Close setting dialog which related with this window.
    virtual void closeEvent(QCloseEvent * event);

    void SetVCRControlData(CXSeismicSection *pSection, bool bShow);
    void UpdateVCRControlData(QUuid changedObjID);

    ///@brief Set grid model Toolbar whether show.
    void SetGridModelControl(bool bShow);

    ///@brief Get the coordinate map
    CX3DGlobalCoordMap* GetCoordMap();

	bool IsCoordShow();
	bool IsCoordGridShow();

	void ShowMessage(const QString&) const;

	void SetVolumeToolbarVisible(CXObject* pObj, bool bVisible);

public slots:
    void slotSelectMode(bool);
    void slotChangeBGColor(const QColor&);
    void slotShowCoordinates(bool);
    void slotShowCoordinatesGrid(bool);
    void slotChangeZScale(const QString&);
    void slotIncreaseZ(bool);
    void slotDecreaseZ(bool);
    void slotSectionValueChanged(double changedValue);
    void slotAttributeChanged(int iIndex);
    
    void slotShowCompass(bool);
    void slotSynchronize(bool);
    void slotShowColormap(bool);

    void slotXYPlaneView(bool);
    void slotXZPlaneView(bool);
    void slotYZPlaneView(bool);
    void slotLightSetting();
    void slotSubGridSetting();
    //void slotAssignTo();
    //void slotEnabledFaultDistribution();
	void slotViewAll();
	void slotBacktoHome();
	void slotSetHome();
    
private:
	void _InitBGColor();
	void _InitZScale();
	void _InitVolumeComboBox();
	void _InitVCRControl();
	bool _IsSection(CXObject* pObj);

private:
    Ui::X3DWindow m_ui;
    QAction* m_pActionGridModel = nullptr;
    int m_nCountActionGridModel = 0;

protected:
    CXVCRControl*				m_pVcrContrl = nullptr;
    QComboBox*					m_pCombBoxZ = nullptr;
	QComboBox*					m_pCbbDV = nullptr;
	QAction*					m_pActionDV = nullptr;
    CXOSGWidget*				m_pOSGWidget = nullptr;
    CX3dscene*					m_pScene = nullptr;
    CXPickhandle*				m_pPickHandle = nullptr;
	CXDlg3DLightingSetting*	m_pDlgLightingSetting = nullptr;
    CXSubGridSetting*			m_subGridDialog = nullptr;
	CXWindowInfo3D*			m_pWindowInfo = nullptr;
};

#endif // KE3DWINDOW_H
