#ifndef XBASEMAPWINDOW_H
#define XBASEMAPWINDOW_H

#include "xwindow.h"
#include <QPointer>
#include "xbasemapwindow_global.h"
#include "ui_xbasemapwindow.h"
#include "xvcrcontrol.h"
#include "xosgwidget.h"
#include "xwindowinfobasemap.h"
#include "xbasemapscene.h"

class CX3DGlobalCoordMap;
class CXBMPickhandle;
class CXBMDlgProperty;
class CXSeismicSection;

class XBASEMAPWINDOW_EXPORT CXBaseMapWindow : public CXWindow
{
	Q_OBJECT
public:
	CXBaseMapWindow(QString sWindowName, QWidget *parent = 0, Qt::WindowFlags f = Qt::Window);
	virtual ~CXBaseMapWindow();

	virtual void InitWindow() override;
	virtual void ReleaseResource() override;
	virtual bool SetObjectVisibility(QUuid objID, bool bVisible) override;
	virtual CXScene* GetScene() override;
	virtual CXBasemapScene* GetOSGScene() override { return m_pScene; }
	virtual void resizeEvent(QResizeEvent *event);
	virtual void UpdateAttribute(const QUuid& uuidGeom, const QUuid& uuidAttr) override;

	CXWindowInfoBasemap* GetWindowInfo() override;
	void SaveScene() override;
	void RestoreScene() override;

	CXOSGWidget* GetOSGViewWidget();
	CX3DGlobalCoordMap* GetCoordMap();

	void SetVolumeToolbarVisible(CXSeismicSection* pSection, bool bVisible);
	void SetVCRControlVisible(CXSeismicSection* pSection, bool bVisible);
	void SetVCRControlDataValue(int secNum);
	void UpdateSectionNumber(QUuid changedObjID);

	void SetRandomSectionReady(bool bReady);
	void SetPolygonlineReady(bool bReady);
	void EnableRandomSectionMode(bool bEnable);
	void EnablePolygonMode(bool bEnable);
	void EnableRandomSectionDeleteAction(bool bEnable);
	void EnablePolygonDeleteAction(bool bEnable);
	bool IsRandomSectionMode();
	bool IsPolygonMode();
	bool IsRandomSectionCreating();
	bool IsPolygonCreating();
	bool IsRandomSectionReady() { return m_bRandomSectionReadyToBorn; }
	bool IsPolygonReady() { return m_bPolygonReadyToBorn; }

	void ShowMessage(const QString&) const;
	bool IsSelectMode() const;
	void SetCurrentScale(const QString& strScale);
	void SetScale(float fScale);
	void Update();

public slots:
	void slotSelectMode(bool isSelected);
	void slotChangeBGColor(const QColor&);
	void slotScaleChanged(const QString& newScale);
	void slotSectionValueChanged(double changedValue);
	void slotRandomSectionMode(bool bOpen);
	void slotPolygonMode(bool bOpen);
	void slotRandomSectionNew(bool bNew);
	void slotPolygonNew(bool bNew);
	void slotRandomSectionDelete();
	void slotPolygonDelete();

	void slotSetCoordVisible(bool bVisible);
	void slotSetColorBarVisible(bool bVisible);
	void slotSetCompassVisible(bool bVisible);
	void slotSetScaleVisible(bool bVisible);
	void slotSynchronize(bool b);
	//void slotEnabledFaultDistribution();
	//void slotAssignTo();
	void slotViewAll();
	void slotBacktoHome();
	void slotSetHome();
	void slotWindowProperties();
	void slotSaveScreenshot();
	void slotVolumesChanged(int index);

private:
	QUuid _GetCurrentVolumeID(CXObject* pSectionObj);

	void _InitBGColor();
	void _InitScaleComboBox();
	void _InitVolumeComboBox();
	void _InitVCRControl();
	void _UpdateVCRControlObject(CXObject* pObj);
	void _BroadcastSectionNumber(int sectionValue);
	bool _IsTimeSlice(CXObject* pObj);
	bool _IsSeismicFoldMap(CXObject* pObj);

private:
	Ui::rlbasemapmainwindow m_ui;
	CXVCRControl *m_pVcrContrl = nullptr;
	CXBMPickhandle* m_pPickHandle = nullptr;

	CXOSGWidget* m_pOSGWidget = nullptr;
	CXBasemapScene* m_pScene = nullptr;

	bool m_bRandomSectionReadyToBorn = false;
	bool m_bPolygonReadyToBorn = false;

	float m_fScale = 0.f;

	QPointer<CXBMDlgProperty> m_pDlgProperty;
	QPointer<QComboBox> m_pCbbScale;
	QPointer<QComboBox> m_pCbbVolumes;


	CXWindowInfoBasemap* m_pWindowInfo = nullptr;
};

#endif // RLBASEMAPWINDOW_H
