#ifndef X2DSECTIONWINDOW_H
#define X2DSECTIONWINDOW_H

/*!
 *	@brief	section window
 *	@author	Xiong
 *	@date	17, Aug. 2015
 */

#include <qvector.h>
#include "xwindow.h"
#include "ui_x2dsectionwindow.h"
#include "xsectionwindow_global.h"

class QComboBox;
class CX2DSectionView;
class CXSectionScene;
class CX2DSectionAxis;
class CXWindowInfoSection;
class CXOrthoProjector;
class QToolBar;
class CXVCRControl;
class QAction;
class CXSectionDigitizingItem;
class CXHorizonTrackPar;
class CXColormapCombo;
class CXSliderSpinWidget;
class CXSeismicSection;
class CXSeismicRandomSection;
class CX2DSeismicLine;
class CXColormapWidget;
class CXSeismicDataVolume;

struct SKERectZoomInfo
{
	SKERectZoomInfo() = default;
	SKERectZoomInfo(QUuid sectionID, float fHScale, float fVScale, double dXCentorRatio, double dYCentorRatio)
	{
		m_sectionID = sectionID;
		m_fHScale = fHScale;
		m_fVScale = fVScale;
		m_dXCentorRatio = dXCentorRatio;
		m_dYCentorRatio = dYCentorRatio;
	}

	QUuid	m_sectionID;
	float	m_fHScale;
	float	m_fVScale;
	double	m_dXCentorRatio;
	double	m_dYCentorRatio;
};

class XSECTIONWINDOW_EXPORT CX2DSectionWindow : public CXWindow
{
    Q_OBJECT
public:
    CX2DSectionWindow(QString sWindowName, QWidget* parent = nullptr, Qt::WindowFlags flags = 0);
    ~CX2DSectionWindow();
	
	virtual CXScene* GetScene() override;
	virtual void InitWindow() override;
	virtual void InitOpenGL() override;
	virtual bool SetObjectVisibility(QUuid objID, bool bVisible) override;
	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar) override;

	static bool IsSection(const QUuid& objID);

	CXObject *GetCurrentGeometryObj();

    void SetSceneRect(const QRectF& rect, bool bChangeScale,double dHorCenterRatio = -1, double dVerCenterRatio = -1);
    const QRectF& GetSceneRect();

	EXSectionEditMode GetEditMode();
	EXHorizonSnapMode GetHorizonSnapMode();
	void SetHorizonSnapMode(EXHorizonSnapMode eHorizonSnapMode);
	EXHorizonTrackMode GetHorizonTrackMode();
	void SetHorizonTrackMode(EXHorizonTrackMode eHorizonTrackMode);
	void SetColormapName(QString colormapName, bool bFore = false);

    CXWindowInfoSection*		GetSecWindowViewInfo();
    CX2DSectionAxis*			GetAxisWidget();
	CX2DSectionView*			GetView();
	CXSectionDigitizingItem*	GetDigitizingItem();
	CXHorizonTrackPar*			GetHorizonTrackPar();

    QComboBox* GetFaultComboBox();
    QComboBox* GetHorizonComboBox();

	void ShowMessage(const QString& msg) const
	{
		m_ui.statusbar->showMessage(msg);
	}

    void UpdateColormap();
    void UpdateColormapWidgetRange(double dMin, double dMax);
    void UpdateVCRControlData(QUuid changedObjID);
    void AddNewItemToComboBox(QUuid newObjID);
    void RemoveItemFromComboBox(QUuid deleteObjID);

    void SetCurrentAttribute(QUuid attributeID);
	QUuid GetCurrentAttributeID();

	void ClearContent();

	void RectZoomIn(QRectF rect);

	void UpdateVolumesName(const QUuid& volumesID);

	///@brief Change viewer size
	void ChangeViewerSize();

	///@brief Change display parameters
	void ChangeDisplayParameter();

	///@brief Get scrollbar widget width and height
	void GetScollbarDimension(int& width, int& height);

public slots:
    void slotZoom();
    //void slotZoomReset();
    //void slotFitToWidth();
    //void slotFitToHeight();
	void slotRectZoom();

	void slotVaribleIntensity();
    void slotWiggle();
    void slotWiggleArea();
	void slotForeVaribleIntensity();
	void slotForeWiggle();
	void slotForeWiggleArea();

    void slotCurrentAttributeChanged(int);
	void slotCurrent2ndLayerChanged(int);
    void slotChangedColormap(const QString& strClrName);
	void slotChangedForeColormap(const QString& colormapName);
    //void SlotIncreaseExcursion();
    //void SlotDecaseExcursion();
    void slotWindowProperties();
    void slotSectionValueChanged(double changedValue);

	//	Fault relevant slots.
    void slotShowFaultTools();
    void slotCurrentFaultchanged(int);
    void slotNewFault();
	void slotAssignFaultStick();

	//	Horizon
    void slotShowHorizonTools();
    void slotCurrentHorizonChanged(int);
    void slotNewHorizon();
    void slotSetCurrentTrackingMode(QAction*);
    void slotSetToolsDigitMode(QAction*);
    void slotSetHorizonDigitMode(QAction*);

	//	Ortho sections
	void slotShowOrthoSectionToos();

    void slotSynVerticalAxis(int);
    void slotSynHorizonAxis(int);
    void slotTrackPara();
	void slotChangedForeAlpha(double currValue);

    void slotOpenColormapEditor();

protected:
    virtual void resizeEvent(QResizeEvent* event) override;
    

private:
	QUuid _GetFirstPostStackID(const QList<CXObject*>& listAttri);
	void _enableIcons(bool bEnable);

	void _undoRectZoomIn(bool bAll);

	void _InitConnection();

	void _initHorizonCB();
	void _InitHorizonTrackingTools();

	void _initFaultCB();
	void _InitFaultDigitizingTools();

	void _Init2ndLayerTools();
    void _UpdateVolumeList(CXObject *);
	QList<CXObject*> _FetchAttributeList(CXObject *);
	bool _IsAttributeListChanged(CXObject *);
	void _SetSection(CXObject* pNewObj, bool bVisable);
	QList<CXObject*> _FetchAttributesByGeometry(CXObject* pGeo);

	void _InitVcrControl(CXSeismicDataVolume* pObj, CXSeismicSection *pSection);

private:
	void _ChangeScale(bool bChangeData = false, double dHorCenterRatio = -1, double dVerCenterRatio = -1);
	void _SetScrollbarPosition(bool bChangeScale, double dHorCenterRatio=-1, double dVerCenterRatio=-1);
	void _UpdateROI();

private:

	Ui_CX2DSectionWindow m_ui;
	CXSectionScene* m_pScene;
	CXSectionDigitizingItem* m_pDigitizingItem;
    
    CX2DSectionAxis* m_pAxisWidget;
    CXWindowInfoSection* m_p2DWindowInfo;
	CXOrthoProjector* m_pOrthoProjector;
	CXVCRControl* m_pVcrContrl;
	CXHorizonTrackPar* m_pHorizonTrackPar;

	QToolBar* m_p2ndLayerToolbar;
    
	QToolBar* m_pFaultToolbar;
	QComboBox*	m_pCbbFaults;
	QComboBox*	m_pCbb2ndFaults;
	QAction*	m_pFaultAssign;

    QToolBar*		m_pHorizonToolbar;
	QComboBox*		m_pCbbHorizons;
	QAction*		m_pHTrackPara;
    QAction*		m_pTrackingModeAction;
	QActionGroup*	m_pGroupHorizonTrack;

	QComboBox* m_pCbb2ndLayer;
    QComboBox* m_pCbbVolumes;
	CXColormapCombo* m_pCcbColorMap;
	CXColormapCombo* m_p2ndColormap;
	CXSliderSpinWidget* m_p2ndAlphaWidget;

	QActionGroup* m_p2ndWiggleGroup;

	EXSectionEditMode m_eEditMode;
    EXHorizonSnapMode m_eHorizonSnapMode;
    EXHorizonTrackMode m_eHorizonTrackMode;
   
	QRectF m_rectScene;		

	bool m_bSectionSync;

    QDockWidget* m_pColormapDock;
    CXColormapWidget* m_pColormapWidget = nullptr;

	QVector<SKERectZoomInfo> m_vecRectZoomInfo;
};

#endif // RL2DSECTIONWINDOW_H