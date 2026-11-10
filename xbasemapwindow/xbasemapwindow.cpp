#include "xbasemapwindow.h"

#include <osg/Group>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/config/SingleWindow>
#include <osgGA/StateSetManipulator>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>
#include <osg/Notify>

#include <QFileDialog>
#include <QMessageBox>
#include <qdebug.h>

#include "xosgwidget.h"
#include "xbmpickhandle.h"
#include "xglobal.h"
#include "xbuttoncoloredit.h"
#include "xtree.h"
#include "xtreewidgetitem.h"
#include "xseismicsection.h"
#include "xseismicdatavolume.h"
#include "xeventconsole.h"
#include "xcursor.h"
#include "x3danchorpickup.h"
#include "xfaultsticks.h"
#include "xproject.h"
#include "xviewinfoobject.h"
#include "xwindowinfobasemap.h"
#include "xbmmanipulator.h"
#include "xbmdlgproperty.h"
#include "x3dutility.h"
#include "xwindowcapturecallback.h"
#include "x3dsurvey.h"
#include "xviewinfoseismicdv.h"
#include "xbaseconsole.h"

CXBaseMapWindow::CXBaseMapWindow(QString sWindowName, QWidget *parent, Qt::WindowFlags f) 
	: CXWindow(sWindowName, parent, f)
{
	m_eWindowType = e3DBaseMap;
	m_ui.setupUi(this);

	setWindowIcon(QIcon(::GetIconPath() + "BasemapWindow.png"));
	setMinimumSize(800, 600);

	m_pOSGWidget = new CXOSGWidget(this, true);
	m_pOSGWidget->setCameraManipulator(new CXBMManipulator());
	m_pOSGWidget->setCursor(Qt::PointingHandCursor);
	setCentralWidget(m_pOSGWidget);
}

CXBaseMapWindow::~CXBaseMapWindow()
{
	
}

void CXBaseMapWindow::InitWindow()
{
	m_pScene = new CXBasemapScene(this);
	m_pScene->InitScene();

	connect(m_ui.m_actionProperties, &QAction::triggered, this, &CXBaseMapWindow::slotWindowProperties);
	connect(m_ui.m_actionScreenshot, &QAction::triggered, this, &CXBaseMapWindow::slotSaveScreenshot);
	connect(m_ui.m_actionSelectMode, &QAction::toggled, this, &CXBaseMapWindow::slotSelectMode);

	// viewport
	connect(m_ui.m_actionViewAll, &QAction::triggered, this, &CXBaseMapWindow::slotViewAll);
	connect(m_ui.m_actionHome, &QAction::triggered, this, &CXBaseMapWindow::slotBacktoHome);
	connect(m_ui.m_actionSetHome, &QAction::triggered, this, &CXBaseMapWindow::slotSetHome);

	// plug-in
	connect(m_ui.m_actionCoordinate, &QAction::toggled, this, &CXBaseMapWindow::slotSetCoordVisible);
	connect(m_ui.m_actionColorbar, &QAction::toggled, this, &CXBaseMapWindow::slotSetColorBarVisible);
	connect(m_ui.m_actionCompass, &QAction::toggled, this, &CXBaseMapWindow::slotSetCompassVisible);
	connect(m_ui.m_actionScale, &QAction::toggled, this, &CXBaseMapWindow::slotSetScaleVisible);
	connect(m_ui.m_actionSynchronize, &QAction::toggled, this, &CXBaseMapWindow::slotSynchronize);
	slotSynchronize(true);

	// Tracking tools
	m_ui.m_pToolBarPolygon->hide();
	m_ui.m_pToolBarRandomSection->hide();

	connect(m_ui.m_pActionRandomSection_Mode, &QAction::toggled, this, &CXBaseMapWindow::slotRandomSectionMode);
	connect(m_ui.m_pActionPolygon_Mode, &QAction::toggled, this, &CXBaseMapWindow::slotPolygonMode);

	connect(m_ui.m_pActionRandomSectionNew, &QAction::toggled, this, &CXBaseMapWindow::slotRandomSectionNew);
	connect(m_ui.m_pActionPolygonNew, &QAction::toggled, this, &CXBaseMapWindow::slotPolygonNew);

	connect(m_ui.m_pActionRandomSectionDelete, &QAction::triggered, this, &CXBaseMapWindow::slotRandomSectionDelete);
	connect(m_ui.m_pActionPolygonDelete, &QAction::triggered, this, &CXBaseMapWindow::slotPolygonDelete);
	_InitBGColor();

	_InitScaleComboBox();
	_InitVolumeComboBox();
	_InitVCRControl();

#if defined(WIN32)
	osg::setNotifyHandler(new osg::WinDebugNotifyHandler);
#endif
	//QAction* pAction = m_ui.toolBarBottom->addAction(QIcon(::GetIconPath() + "faultDistribution.png"),"Fault Distribution",this,SLOT(slotEnabledFaultDistribution()));
	//pAction->setCheckable(true);

}

void CXBaseMapWindow::ReleaseResource()
{
	if (m_pPickHandle)
	{
		m_pPickHandle->ResetPickedNodeStatus();
		m_pOSGWidget->removeEventHandler(m_pPickHandle);
		m_pPickHandle = nullptr;
	}

	if (m_pScene) { delete m_pScene; m_pScene = nullptr; }
	if (m_pWindowInfo) { delete m_pWindowInfo; m_pWindowInfo = nullptr; }

	CXWindow::ReleaseResource();
}

bool CXBaseMapWindow::SetObjectVisibility(QUuid objID, bool bVisible)
{
	CXObject* pObj = ::GetObjectByID(objID);
	if (!pObj)
		return false;

	CXObject* pGeomObj = pObj->GetGeometryObject();
	CXViewInfoObject* pViewInfo = this->GetObjectViewInfo(pGeomObj->GetObjectID());
	pViewInfo->SetVisible(bVisible);

	if (_IsSeismicFoldMap(pGeomObj))
	{
		pViewInfo->SetNeedColormap(true);
	}

	if (_IsTimeSlice(pGeomObj))
	{
		if (bVisible && pViewInfo->GetAttributeObjID() == pGeomObj->GetObjectID())
		{
			UpdateAttribute(pGeomObj->GetObjectID(), pGeomObj->GetAncient(EX3DSurvey)->GetChildren(EXSeismicDataVolume, true).front()->GetObjectID());
		}
		else if (!bVisible)
		{
			CXBMPickhandle* pPickhandle = dynamic_cast<CXBMPickhandle*>(m_pOSGWidget->GetPickhandle());
			if (pPickhandle)
			{
				pPickhandle->ResetPickedNodeStatus();
			}
		}
	}

	m_pScene->SetOjbectVisiability(pGeomObj->GetObjectID(), bVisible);

	return true;
}

CXScene* CXBaseMapWindow::GetScene()
{
	return nullptr;
}

void CXBaseMapWindow::resizeEvent(QResizeEvent *event)
{
	m_pScene->UpdateHUDWithWindow();
}

void CXBaseMapWindow::UpdateAttribute(const QUuid & uuidGeom, const QUuid & uuidAttr)
{
	CXWindow::UpdateAttribute(uuidGeom, uuidAttr);
	m_pScene->UpdateAttribtue(uuidGeom);
	reinterpret_cast<CXBaseConsole*>(::GetConsole())->SetActiveWindow(this);
}

CXWindowInfoBasemap* CXBaseMapWindow::GetWindowInfo()
{
	if (m_pWindowInfo == nullptr)
		m_pWindowInfo = new CXWindowInfoBasemap;

	return m_pWindowInfo;
}

void CXBaseMapWindow::SaveScene()
{
	CXBMManipulator* pManipulator = dynamic_cast<CXBMManipulator*>(m_pOSGWidget->getCameraManipulator());
	float currentScale = pManipulator->GetCurrentScale();
	GetWindowInfo()->SetLastScale(currentScale);

	double dCenterOffsetX, dCenterOffsetY;
	pManipulator->GetOffsetCenter(dCenterOffsetX, dCenterOffsetY);
	GetWindowInfo()->SetLastCenterOffsetX(dCenterOffsetX);
	GetWindowInfo()->SetLastCenterOffsetY(dCenterOffsetY);
}

void CXBaseMapWindow::RestoreScene()
{
	slotViewAll();

	float lastScale = GetWindowInfo()->GetLastScale();
	SetScale(lastScale);
	SetCurrentScale(QString("%1:%2").arg(1).arg(qRound(lastScale) * 100)); // m -> cm
	m_pScene->SetScaleMark(qRound(lastScale));

	CXBMManipulator* pManipulator = dynamic_cast<CXBMManipulator*>(m_pOSGWidget->getCameraManipulator());
	const osg::Vec3d& center = pManipulator->getCenter();
	pManipulator->setCenter(center + osg::Vec3d(GetWindowInfo()->GetLastCenterOffsetX(), GetWindowInfo()->GetLastCenterOffsetY(), 0.0));

	update();
}

CXOSGWidget* CXBaseMapWindow::GetOSGViewWidget()
{
	return m_pOSGWidget;
}

CX3DGlobalCoordMap* CXBaseMapWindow::GetCoordMap()
{
	return m_pScene->GetCoordMap();
}

void CXBaseMapWindow::slotPolygonMode(bool bOpen)
{
	if (bOpen)
	{
		m_ui.m_pActionRandomSection_Mode->blockSignals(true);
		m_ui.m_pActionRandomSection_Mode->setChecked(false);
		m_ui.m_pActionRandomSection_Mode->blockSignals(false);

		m_ui.m_pToolBarRandomSection->hide();
		m_ui.m_pToolBarRandomSection->setEnabled(true);

		m_ui.m_actionSelectMode->setChecked(true);
	}
}

void CXBaseMapWindow::slotRandomSectionNew(bool bNew)
{
	m_pScene->CreateHudCamera();

	if (bNew)
	{
		m_ui.m_pActionPolygonNew->blockSignals(true);
		m_ui.m_pActionPolygonNew->setChecked(false);
		m_ui.m_pActionPolygonNew->blockSignals(false);

		m_ui.m_actionSelectMode->setChecked(true);
	}
}

void CXBaseMapWindow::slotPolygonNew(bool bNew)
{
	m_pScene->CreateHudCamera();

	if (bNew)
	{
		m_ui.m_pActionRandomSectionNew->blockSignals(true);
		m_ui.m_pActionRandomSectionNew->setChecked(false);
		m_ui.m_pActionRandomSectionNew->blockSignals(false);

		m_ui.m_actionSelectMode->setChecked(true);
	}
}

void CXBaseMapWindow::slotRandomSectionDelete()
{
	CXBMPickhandle* pPickhandle = dynamic_cast<CXBMPickhandle*>(m_pOSGWidget->GetPickhandle());
	Q_ASSERT(pPickhandle);

	CXObject* pPickedRandomSectionObj = pPickhandle->GetCurPickedObj();
	
	CXObject* pRandomSectionFolder = pPickedRandomSectionObj->GetParent();
	Q_ASSERT(pRandomSectionFolder);

	pRandomSectionFolder->RemoveOneChild(pPickedRandomSectionObj);

	m_ui.m_pActionRandomSectionDelete->setEnabled(false);

	CXProcessEvent processEvent;
	pPickedRandomSectionObj->AddEvent(EDeleted);
}

void CXBaseMapWindow::slotPolygonDelete()
{
	CXBMPickhandle* pPickhandle = dynamic_cast<CXBMPickhandle*>(m_pOSGWidget->GetPickhandle());
	Q_ASSERT(pPickhandle);

	CXObject* pPickedPolygonObj = pPickhandle->GetCurPickedObj();

	CXObject* pPolygonFolder = pPickedPolygonObj->GetParent();
	Q_ASSERT(pPolygonFolder);

	pPolygonFolder->RemoveOneChild(pPickedPolygonObj);

	m_ui.m_pActionPolygonDelete->setEnabled(false);

	CXProcessEvent processEvent;
	pPickedPolygonObj->AddEvent(EDeleted);
}

void CXBaseMapWindow::slotRandomSectionMode(bool bOpen)
{
	if (bOpen)
	{
		//m_pScene->CreateHudCamera();
		m_ui.m_pActionPolygon_Mode->blockSignals(true);
		m_ui.m_pActionPolygon_Mode->setChecked(false);
		m_ui.m_pActionPolygon_Mode->blockSignals(false);

		m_ui.m_pToolBarPolygon->hide();
		m_ui.m_pToolBarPolygon->setEnabled(true);

		m_ui.m_actionSelectMode->setChecked(true);
	}
}

void CXBaseMapWindow::slotSetCoordVisible(bool bVisible)
{
	GetWindowInfo()->SetCoordVisible(bVisible);
	m_pScene->UpdateCoordinateInfo();
	update();
}

void CXBaseMapWindow::slotSetColorBarVisible(bool bVisible)
{
	GetWindowInfo()->SetColorbarVisible(bVisible);
	m_pScene->SetColorbarVisible(bVisible);
	update();
}

void CXBaseMapWindow::slotSetCompassVisible(bool bVisible)
{
	GetWindowInfo()->SetCompassVisible(bVisible);
	m_pScene->SetCompassVisible(bVisible);
	update();
}

void CXBaseMapWindow::slotSetScaleVisible(bool bVisible)
{
	GetWindowInfo()->SetScalebarVisible(bVisible);
	m_pScene->SetScaleVisible(bVisible);

	if (bVisible)
	{
		CXBMManipulator* pManipulator = dynamic_cast<CXBMManipulator*>(m_pOSGWidget->getCameraManipulator());
		m_pScene->SetScaleMark(qRound(pManipulator->GetCurrentScale()));
	}

	update();
}

void CXBaseMapWindow::slotSelectMode(bool isSelected)
{
	if (isSelected)
	{
		m_pPickHandle = new CXBMPickhandle;
		m_pOSGWidget->addEventHandler(m_pPickHandle);
	}
	else
	{
		m_pPickHandle->ResetPickedNodeStatus();
		m_pOSGWidget->removeEventHandler(m_pPickHandle);
		m_pPickHandle = nullptr;
		ShowMessage("");
	}

	m_pOSGWidget->setCursor(isSelected ? Qt::ArrowCursor : Qt::PointingHandCursor);
}

void CXBaseMapWindow::slotChangeBGColor(const QColor& color)
{
	m_pOSGWidget->getCamera()->setClearColor(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	GetWindowInfo()->SetBackgroundColor(color);

	// coordinate grid should inverse the color.
	QColor invCol = QColor(255 - color.red(), 255 - color.green(), 255 - color.blue(), color.alpha());
	GetWindowInfo()->SetCoordColor(invCol);
	m_pScene->UpdateCoordinateInfo();

	GetWindowInfo()->SetScaleMarkColor(invCol);
	GetWindowInfo()->SetScaleFrameColor(invCol);
	m_pScene->UpdateScaleInfo();

	update();
}

void CXBaseMapWindow::slotScaleChanged(const QString& newScale)
{
	QStringList ratioList = newScale.split(':');
	int iRatio = ratioList.last().toInt() / ratioList.front().toInt();
	int iScale = iRatio / 100; // cm -> m

	SetScale(iScale);
}

void CXBaseMapWindow::slotSynchronize(bool b)
{
	m_pScene->SetCursorVisible(b);

	CXProcessEvent processEvent(m_pScene);
	CXCursor::Instance().AddEvent(m_ui.m_actionSynchronize->isChecked() ? EActivate : EDeactivate);
}

void CXBaseMapWindow::slotViewAll()
{
	osg::Vec3d eye, center, up;

	osg::Node *pNode = m_pOSGWidget->getSceneData();

	if (!pNode)
		return;

	const osg::BoundingSphere& bound = pNode->getBound();
	center = m_pScene->GetSceneBoundBox().center();

	eye = center + osg::Vec3d(0, 0, 1) * bound.radius() * 2;
	up = osg::Y_AXIS;

	CXBMManipulator* pManipulator = dynamic_cast<CXBMManipulator*>(m_pOSGWidget->getCameraManipulator());
	pManipulator->setTransformation(eye, center, up);

	const osg::BoundingBox& sceneBoundingBox = m_pScene->GetSceneBoundBox();

	if (!sceneBoundingBox.valid())
		return;

	float newWidth = (sceneBoundingBox.xMax() - sceneBoundingBox.xMin())* 1.2;
	float newHeigth = (sceneBoundingBox.yMax() - sceneBoundingBox.yMin())* 1.2;

	double left, right, bottom, top, nearz, farz;
	m_pOSGWidget->getCamera()->getProjectionMatrixAsOrtho(left, right, bottom, top, nearz, farz);

	double r = (right - left) / (top - bottom);
	float len = newWidth / newHeigth >= 1 ? newWidth : newHeigth;

	m_pOSGWidget->getCamera()->setProjectionMatrixAsOrtho2D(-len, len, -len / r, len / r);
	SetCurrentScale(QString("%1:%2").arg(1).arg(qRound(pManipulator->GetCurrentScale()) * 100)); // m -> cm
	m_pScene->SetScaleMark(qRound(pManipulator->GetCurrentScale()));

	const osg::Vec3d& mcenter = pManipulator->getCenter();
	osg::notify() << "center in viewall: " << mcenter.x() << ", " << mcenter.y() << ", " << mcenter.z();

	this->update();
}

void CXBaseMapWindow::slotBacktoHome()
{
	if (qFuzzyCompare(m_fScale, 0.f))
		return;

	m_pOSGWidget->home();
	SetScale(m_fScale);
	update();
}

void CXBaseMapWindow::slotSetHome()
{
	CXBMManipulator* pManipulator = dynamic_cast<CXBMManipulator*>(m_pOSGWidget->getCameraManipulator());
	
	osg::Vec3 eye, center, up;
	m_pOSGWidget->getCamera()->getViewMatrixAsLookAt(eye, center, up);
	
	pManipulator->setHomePosition(eye, center, up);
	m_fScale = pManipulator->GetCurrentScale();
	m_ui.m_actionHome->setEnabled(true);
}

void CXBaseMapWindow::slotWindowProperties()
{
	if (m_pDlgProperty.isNull())
	{
		m_pDlgProperty = new CXBMDlgProperty(this, dynamic_cast<CXWindowInfoBasemap*>(m_pWindowInfo));
	}
	
	m_pDlgProperty->show();
}

void CXBaseMapWindow::slotSaveScreenshot()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save Screenshot of Base map", ::g_pProject->GetProjectPath() + "screenshot", tr("Images (*.png)"));
	if (fileName.isEmpty())
	{
		QMessageBox::warning(0, "Save error", "No selected path.");
		return;
	}

	{
		QFile testFile(fileName);
		if (!testFile.open(QIODevice::WriteOnly))
		{
			QMessageBox::warning(this, "Save error", "You don't have write permission for this path.");
			return;
		}
		testFile.close();
		testFile.remove();
	}

	auto pixmap = m_pOSGWidget->grab();
	pixmap.save(fileName, "PNG");
}

void CXBaseMapWindow::slotVolumesChanged(int index)
{
	auto pPickhandle = dynamic_cast<CXBMPickhandle*>(m_pOSGWidget->GetPickhandle());
	if (!pPickhandle)
		return;

	auto pSection = dynamic_cast<CXSeismicSection*>(pPickhandle->GetCurPickedObj());
	if (!pSection || eTimeSlice != pSection->GetSectionType())
		return;

	CXViewInfoObject *pViewInfoSection = GetObjectViewInfo(pSection->GetObjectID());
	m_pScene->SetColorbarObjVisible(pViewInfoSection->GetAttributeObjID(), false);

	QUuid uuidCurrentVolume = m_pCbbVolumes->itemData(index).toUuid();
	UpdateAttribute(pSection->GetObjectID(), uuidCurrentVolume);
	m_pScene->SetColorbarObjVisible(uuidCurrentVolume, true);
}

QUuid CXBaseMapWindow::_GetCurrentVolumeID(CXObject* pSectionObj)
{
	QUuid currentVolumeComboBoxID = m_pCbbVolumes->currentData().toUuid();

	if (!pSectionObj)
		return currentVolumeComboBoxID;

	CXViewInfoObject* pSectionViewInfo = GetObjectViewInfo(pSectionObj->GetObjectID());
	Q_ASSERT(pSectionViewInfo);

	QUuid attributeID = pSectionViewInfo->GetAttributeObjID();

	if (attributeID.isNull())
	{
		attributeID = currentVolumeComboBoxID;
		pSectionViewInfo->SetAttributeObjID(attributeID);
	}
	else
	{
		m_pCbbVolumes->blockSignals(true);
		m_pCbbVolumes->setCurrentIndex(m_pCbbVolumes->findData(attributeID));
		m_pCbbVolumes->blockSignals(false);
	}

	return attributeID;
}

void CXBaseMapWindow::_InitBGColor()
{
	const QColor& colorBackground = GetWindowInfo()->GetBackgroundColor();

	auto pColorButton = new CXButtonColorEdit(this, colorBackground, "Change Background Color");
	pColorButton->setFixedWidth(40);
	m_ui.toolBarTop->addWidget(pColorButton);
	connect(pColorButton, SIGNAL(ColorSelected(const QColor&)), SLOT(slotChangeBGColor(const QColor&)));
	emit pColorButton->ColorSelected(colorBackground);
}

void CXBaseMapWindow::_InitScaleComboBox()
{
	m_pCbbScale = new QComboBox(this);
	m_pCbbScale->addItems(QStringList({ "1:500", "1:1000", "1:5000", "1:10000", "1:15000", "1:20000", "1:25000", "1:30000", "1:50000", "1:100000", "1:200000", "1:500000", "1:1000000" }));
	m_pCbbScale->setEditable(true);
	m_ui.toolBarTop->addSeparator();
	m_ui.toolBarTop->addWidget(new QLabel("Scale:", this));
	m_ui.toolBarTop->addWidget(m_pCbbScale);
	connect(m_pCbbScale.data(), &QComboBox::currentTextChanged, this, &CXBaseMapWindow::slotScaleChanged);
}

void CXBaseMapWindow::_InitVolumeComboBox()
{
	m_pCbbVolumes = new QComboBox;
	m_pCbbVolumes->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	m_ui.toolBarVolume->addWidget(m_pCbbVolumes);
	m_ui.toolBarVolume->setVisible(false);
	connect(m_pCbbVolumes, SIGNAL(currentIndexChanged(int)), this, SLOT(slotVolumesChanged(int)));
}

void CXBaseMapWindow::_InitVCRControl()
{
	m_pVcrContrl = new CXVCRControl(this);
	m_pVcrContrl->CreateIt();
	m_pVcrContrl->ShowMe(false);
	connect(m_pVcrContrl, SIGNAL(CurrentSectionChanged(double)), this, SLOT(slotSectionValueChanged(double)));
}

void CXBaseMapWindow::SetVolumeToolbarVisible(CXSeismicSection * pSection, bool bVisible)
{
	m_ui.toolBarVolume->setVisible(bVisible);

	CXViewInfoObject* pViewInfo = GetObjectViewInfo(pSection->GetObjectID());

	if (bVisible)
	{
		m_pCbbVolumes->blockSignals(true);
		m_pCbbVolumes->clear();

		for (auto pObj : pSection->GetAncient(EX3DSurvey)->GetChildren(EXSeismicDataVolume, true))
		{
			m_pCbbVolumes->addItem(QIcon(::GetIconPath() + pObj->GetIconName()), pObj->GetObjectName(), pObj->GetObjectID().toString());
		}

		m_pCbbVolumes->setCurrentIndex(m_pCbbVolumes->findData(pViewInfo->GetAttributeObjID()));
		m_pCbbVolumes->blockSignals(false);
	}

	m_pScene->SetColorbarObjVisible(pViewInfo->GetAttributeObjID(), bVisible);
}

void CXBaseMapWindow::SetVCRControlVisible(CXSeismicSection * pSection, bool bVisible)
{
	m_pVcrContrl->ShowMe(bVisible);

	if (bVisible)
	{
		_UpdateVCRControlObject(pSection);
	}
}

void CXBaseMapWindow::UpdateSectionNumber(QUuid changedObjID)
{
	if (!m_pVcrContrl || !m_pVcrContrl->IsVisible())
		return;

	auto pPickhandle = dynamic_cast<CXBMPickhandle*>(m_pOSGWidget->GetPickhandle());
	if (!pPickhandle || pPickhandle->GetCurPickedObj()->GetObjectID() != changedObjID)
		return;

	auto pSection = dynamic_cast<CXSeismicSection*>(::GetObjectByID(changedObjID));
	if (!pSection)
		return;

	m_pVcrContrl->SetSliderSpinValue(pSection->GetSectionNumber());
}

void CXBaseMapWindow::SetRandomSectionReady(bool bReady)
{
	m_bRandomSectionReadyToBorn = bReady;

	if (!bReady)
	{
		m_ui.m_pActionRandomSectionNew->blockSignals(true);
		m_ui.m_pActionRandomSectionNew->setChecked(false);
		m_ui.m_pActionRandomSectionNew->blockSignals(false);
	}
}

void CXBaseMapWindow::SetPolygonlineReady(bool bReady)
{
	m_bPolygonReadyToBorn = bReady;

	if (!bReady)
	{
		m_ui.m_pActionPolygonNew->blockSignals(true);
		m_ui.m_pActionPolygonNew->setChecked(false);
		m_ui.m_pActionPolygonNew->blockSignals(false);
	}
}

void CXBaseMapWindow::_UpdateVCRControlObject(CXObject* pObj)
{
	if (!pObj || EXSeismicSection != pObj->GetObjectType())
		return;

	CXSeismicSection *pSection = dynamic_cast<CXSeismicSection*>(pObj);
	const CXSeismicUTMTool& utm = pSection->GetUTM();
	double dNumber = pSection->GetSectionNumber();
	QUuid volumeID = _GetCurrentVolumeID(pSection);
	auto pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(volumeID));

	switch (pSection->GetSectionType())
	{
	case eInlineSection:
		m_pVcrContrl ->InitData(utm.GetFirstInline(), utm.GetLastInline(), dNumber, 1, utm.GetInlineIncrement(), -1);
		break;
	case eCrosslineSection:
		m_pVcrContrl->InitData(utm.GetFirstCrossline(), utm.GetLastCrossline(), dNumber, 1, utm.GetCrosslineIncrement(), -1);
		break;
	case eTimeSlice:
		if (pDV)
		{
			double dStartZ, dStopZ, dStep;
			pDV->GetSamplingRange(dStartZ, dStopZ, dStep);
			m_pVcrContrl->InitData(dStartZ, dStopZ, dNumber, 1, dStep, -1);
		}
		break;
	default:
		Q_ASSERT(!"error section type");
	}
}

void CXBaseMapWindow::slotSectionValueChanged(double changedValue)
{
	//m_pOSGWidget->getEventQueue()->addEvent(new CXEventAdapter(changedValue));
	_BroadcastSectionNumber(qRound(changedValue));
}

void CXBaseMapWindow::SetVCRControlDataValue(int secNum)
{
	m_pVcrContrl->SetSliderSpinValue(secNum);
	_BroadcastSectionNumber(secNum);
}

void CXBaseMapWindow::EnableRandomSectionMode(bool bEnable)
{
	m_ui.m_pActionRandomSection_Mode->setEnabled(bEnable);
}

void CXBaseMapWindow::EnablePolygonMode(bool bEnable)
{
	m_ui.m_pActionPolygon_Mode->setEnabled(bEnable);
}

void CXBaseMapWindow::EnableRandomSectionDeleteAction(bool bEnable)
{
	m_ui.m_pActionRandomSectionDelete->setEnabled(bEnable);
}

void CXBaseMapWindow::EnablePolygonDeleteAction(bool bEnable)
{
	m_ui.m_pActionPolygonDelete->setEnabled(bEnable);
}

bool CXBaseMapWindow::IsRandomSectionMode()
{
	return m_ui.m_pActionRandomSection_Mode->isChecked();
}

bool CXBaseMapWindow::IsPolygonMode()
{
	return m_ui.m_pActionPolygon_Mode->isChecked();
}

bool CXBaseMapWindow::IsRandomSectionCreating()
{
	return m_ui.m_pActionRandomSectionNew->isChecked();
}

bool CXBaseMapWindow::IsPolygonCreating()
{
	return m_ui.m_pActionPolygonNew->isChecked();
}

//void CXBaseMapWindow::slotEnabledFaultDistribution()
//{
//	QAction *pAction = dynamic_cast<QAction*> (sender());
//	m_bEnabledFaultDistribution = pAction->isChecked();
//	m_pOSGWidget->EnabledMouseEvent(pAction->isChecked());
//}

void CXBaseMapWindow::ShowMessage(const QString& msg) const
{
	m_ui.statusbar->showMessage(msg);
}

bool CXBaseMapWindow::IsSelectMode() const
{
	return m_ui.m_actionSelectMode->isChecked();
}

void CXBaseMapWindow::SetCurrentScale(const QString& strScale)
{
	if (m_pCbbScale)
	{
		m_pCbbScale->blockSignals(true);
		m_pCbbScale->setCurrentText(strScale);
		m_pCbbScale->blockSignals(false);
	}
}

void CXBaseMapWindow::SetScale(float fScale)
{
	CXBMManipulator* pManipulator = dynamic_cast<CXBMManipulator*>(m_pOSGWidget->getCameraManipulator());
	
	float factor = fScale / pManipulator->GetCurrentScale();

	double dLeft, dRight, dBottom, dTop, dNear, dFar;
	m_pOSGWidget->getCamera()->getProjectionMatrixAsOrtho(dLeft, dRight, dBottom, dTop, dNear, dFar);
	m_pOSGWidget->getCamera()->setProjectionMatrixAsOrtho2D(dLeft * factor, dRight * factor, dBottom * factor, dTop * factor);

	update();
}

void CXBaseMapWindow::Update()
{
	m_pOSGWidget->update();
}

//void CXBaseMapWindow::slotAssignTo()
//{
//	QAction *pAction = dynamic_cast<QAction*>(sender());
//	QUuid uid(pAction->data().toString());
//	CXFaultSticks *pStricks = dynamic_cast<CXFaultSticks*>( GetObjectByID(uid));
//	QList<CXObject *> listObjects = GetProject()->GetChildren(EXFaultSticks, true);
//	QPolygonF polygon = m_pOSGWidget->GetAnchorPickup()->GetFillPolygon();
//	float fZScale = 1;
//	osg::Matrix viewMat=m_pOSGWidget->getCamera()->getViewMatrix();
//	osg::Matrix projMat=m_pOSGWidget->getCamera()->getProjectionMatrix();
//	osg::Matrix winMat=m_pOSGWidget->getCamera()->getViewport()->computeWindowMatrix();
//	osg::Matrix pipeMat=viewMat*projMat*winMat;
//	QList<QUuid> lstAll = m_pScene->GetAllDisplayObject();
//	foreach(CXObject*pObject ,listObjects)
//	{
//		if (!lstAll.contains(pObject->GetObjectID()))
//		{
//			continue;
//		}
//		CXFaultSticks *pFaultStrick = dynamic_cast<CXFaultSticks*>(pObject);
//		QList<CXFaultStick*> lstSticks= pFaultStrick->GetAllSticks();
//		foreach(CXFaultStick *pStick , lstSticks)
//		{
//			unsigned int nDataNum;
//			double* pData = pStick->GetData(nDataNum);
//			int nPointNum = nDataNum/3;	
//			osg::Vec3d  vecPos( pData[3*nPointNum/2],pData[3*nPointNum/2+1],pData[3*nPointNum/2+2]);	
//			osg::Vec3 vecLocal;
//			this->GetCoordMap()->MapWorldToLocal(vecPos,vecLocal);
//			vecLocal[2]*=fZScale;
//			osg::Vec3d vecPoint =vecLocal * pipeMat;
//			QPointF ScreenPos(vecPoint.x(),m_pOSGWidget->size().height()-vecPoint.y());
//			if (polygon.containsPoint(ScreenPos,Qt::WindingFill) && !pStricks->GetAllSticks().contains(pStick))
//			{
//				pStricks->GetAllSticks().append(pStick);
//			}
//		}
//	}
//	m_pOSGWidget->RemoveAnchorPickup();
//}

void CXBaseMapWindow::_BroadcastSectionNumber(int sectionValue)
{
	auto pPickhandle = dynamic_cast<CXBMPickhandle*>(m_pOSGWidget->GetPickhandle());
	if (!pPickhandle)
		return;

	CXSeismicSection *pCurObject = dynamic_cast<CXSeismicSection*>(pPickhandle->GetCurPickedObj());
	if (!pCurObject) // only support 3d seismic data.
		return;

	pCurObject->SetSectionNumber(sectionValue);

	CXProcessEvent processEvent;
	pCurObject->AddEvent(EDataChanged);
}

bool CXBaseMapWindow::_IsTimeSlice(CXObject* pObj)
{
	auto pSection = dynamic_cast<CXSeismicSection*>(pObj);
	if (!pSection)
		return false;

	if (eTimeSlice == pSection->GetSectionType())
		return true;

	return false;
}

bool CXBaseMapWindow::_IsSeismicFoldMap(CXObject * pObj)
{
	auto pDV = dynamic_cast<CXSeismicDataVolume*>(pObj);
	if (!pDV || !pDV->IsPrestack())
		return false;

	auto pViewInfoDV = dynamic_cast<CXViewInfoSeismicDV*>(GetObjectViewInfo(pDV->GetObjectID()));
	if (!pViewInfoDV || !pViewInfoDV->HasFold())
		return false;

	return true;
}
