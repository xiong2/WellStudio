#include "x3dwindow.h"

#include "xosgwidget.h"
#include <osg/Group>
//#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>

#include "xglobal.h"
#include "xbuttoncoloredit.h"
#include <QAction>
#include <QComboBox>
#include "xviewinfoobject.h"
#include "xsliderspinwidget.h"
#include "xfaultsticks.h"
#include "xproject.h"
#include "xseismicsection.h"
#include "xseismicdatavolume.h"
#include "xutmtool.h"
#include "xtree.h"
#include "xtreewidgetitem.h"
#include <cassert>
#include "xeventconsole.h"
#include "xcursor.h"
#include "xdlg3dlightingsetting.h"
#include "xbaseconsole.h"
#include "xsubgridsetting.h"
#include "x3danchorpickup.h"
#include "x3dsurvey.h"
#include "xviewinfomanager.h"
#include "xlog.h"
#include "xbaseconsole.h"

CX3DWindow::CX3DWindow(QString sWindowName, QWidget *parent, Qt::WindowFlags f)
	:CXWindow(sWindowName, parent, f)
{
	m_eWindowType = e3DWindow;
	m_ui.setupUi(this);

	setMinimumSize(800, 600);

	m_pOSGWidget = new CXOSGWidget(this);
	m_pOSGWidget->setCameraManipulator(new osgGA::TrackballManipulator);
	setCentralWidget(m_pOSGWidget);
}

CX3DWindow::~CX3DWindow()
{
	if (m_pScene) { delete m_pScene; m_pScene = nullptr; }
}

void CX3DWindow::InitWindow()
{
	m_pScene = new CX3dscene(this);
	m_pScene->InitScene();
	
	connect(m_ui.actionSelect_Mode, &QAction::toggled, this, &CX3DWindow::slotSelectMode);
	connect(m_ui.actionHome, &QAction::triggered, this, &CX3DWindow::slotBacktoHome);
	connect(m_ui.actionSet_Home, &QAction::triggered, this, &CX3DWindow::slotSetHome);
	
	connect(m_ui.actionView_All, &QAction::triggered, this, &CX3DWindow::slotViewAll);
	connect(m_ui.actionXY_Plane_View, &QAction::triggered, this, &CX3DWindow::slotXYPlaneView);
	connect(m_ui.actionXZ_Plane_View, &QAction::triggered, this, &CX3DWindow::slotXZPlaneView);
	connect(m_ui.actionYZ_Plane_View, &QAction::triggered, this, &CX3DWindow::slotYZPlaneView);
	connect(m_ui.actionPerspective_Orthogonal_View_Mode, &QAction::toggled, m_pScene, &CX3dscene::slotSetProjectionMode);

	connect(m_ui.actionShow_Hide_Coordinates, &QAction::toggled, this, &CX3DWindow::slotShowCoordinates);
	connect(m_ui.actionShow_Hide_Coordinates_Grid, &QAction::toggled, this, &CX3DWindow::slotShowCoordinatesGrid);
	connect(m_ui.actionCompass, &QAction::toggled, this, &CX3DWindow::slotShowCompass);
	connect(m_ui.actionSynchronize, &QAction::toggled, this, &CX3DWindow::slotSynchronize);
	connect(m_ui.actionColorbar, &QAction::toggled, this, &CX3DWindow::slotShowColormap);
	connect(m_ui.actionLight_Setting, &QAction::triggered, this, &CX3DWindow::slotLightSetting);
	
	_InitZScale();
	_InitBGColor();
	_InitVolumeComboBox();
	_InitVCRControl();

	//	m_ui.mainToolBar->addSeparator();
	//	QAction* pAction = m_ui.bottomToolBar->addAction(QIcon(::GetIconPath() + "faultDistribution.png"),"Fault Distribution",this,SLOT(slotEnabledFaultDistribution()));
	//	pAction->setCheckable(true);

}

void CX3DWindow::ReleaseResource()
{
	if (m_pPickHandle)
	{
		m_pOSGWidget->removeEventHandler(m_pPickHandle);
		m_pPickHandle = nullptr;
	}

	if (m_pScene)
		m_pScene->ReleaseResource();

	if (m_pWindowInfo) { delete m_pWindowInfo; m_pWindowInfo = nullptr; }

	if (m_pOSGWidget) { delete m_pOSGWidget; m_pOSGWidget = nullptr; }

	CXWindow::ReleaseResource();
}

CX3DGlobalCoordMap* CX3DWindow::GetCoordMap()
{
	return m_pScene->GetCoordMap();
}

bool CX3DWindow::IsCoordShow()
{
	return m_ui.actionShow_Hide_Coordinates->isChecked();
}

bool CX3DWindow::IsCoordGridShow()
{
	return m_ui.actionShow_Hide_Coordinates_Grid->isChecked();
}

void CX3DWindow::slotSelectMode(bool b)
{
	if (m_ui.actionSelect_Mode->isChecked())
	{
		m_pPickHandle = new CXPickhandle;
		m_pOSGWidget->addEventHandler(m_pPickHandle);
	}
	else
	{
		m_pPickHandle->ResetPickedObject(nullptr);
		SetVolumeToolbarVisible(nullptr, false);
		SetVCRControlData(nullptr, false);
		m_pOSGWidget->removeEventHandler(m_pPickHandle);
		m_pPickHandle = nullptr;
	}
}

void CX3DWindow::slotXYPlaneView(bool b)
{
	osg::ref_ptr<osgGA::TrackballManipulator> manipulator = dynamic_cast<osgGA::TrackballManipulator*>(m_pOSGWidget->getCameraManipulator());
	if (!manipulator.valid())
		return;

	if (!m_pOSGWidget->getSceneData())
		return;

	osg::Vec3d eye, center, up;

	const osg::BoundingSphere& bound = m_pOSGWidget->getSceneData()->getBound();
	center = bound.center();

	eye = center + osg::Vec3d(0, 0, 1)*bound.radius() * 2;
	up = osg::Y_AXIS;

	manipulator->setTransformation(eye, center, up);
}

void CX3DWindow::slotXZPlaneView(bool b)
{
	osg::ref_ptr<osgGA::TrackballManipulator> manipulator = dynamic_cast<osgGA::TrackballManipulator*>(m_pOSGWidget->getCameraManipulator());
	if (!manipulator.valid())
		return;

	if (!m_pOSGWidget->getSceneData())
		return;

	osg::Vec3d eye, center, up;

	const osg::BoundingSphere& bound = m_pOSGWidget->getSceneData()->getBound();
	center = bound.center();

	eye = center + osg::Vec3d(0, -1, 0)*bound.radius() * 2;
	up = osg::Z_AXIS;

	manipulator->setTransformation(eye, center, up);
}

void CX3DWindow::slotYZPlaneView(bool b)
{
	osg::ref_ptr<osgGA::TrackballManipulator> manipulator = dynamic_cast<osgGA::TrackballManipulator*>(m_pOSGWidget->getCameraManipulator());
	if (!manipulator.valid())
		return;

	if (!m_pOSGWidget->getSceneData())
		return;

	osg::Vec3d eye, center, up;

	const osg::BoundingSphere& bound = m_pOSGWidget->getSceneData()->getBound();
	center = bound.center();

	eye = center + osg::Vec3d(1, 0, 0)*bound.radius() * 2;
	up = osg::Z_AXIS;

	manipulator->setTransformation(eye, center, up);
}

void CX3DWindow::slotViewAll()
{

	osg::ref_ptr<osgGA::TrackballManipulator> manipulator = dynamic_cast<osgGA::TrackballManipulator*>(m_pOSGWidget->getCameraManipulator());
	if (!manipulator.valid())
		return;

	if (!m_pOSGWidget->getSceneData())
		return;

	osg::Vec3d eye, center, up;

	const osg::BoundingSphere& bound = m_pOSGWidget->getSceneData()->getBound();
	center = bound.center();

	eye = center + osg::Vec3d(0.7, -0.8, 0.4)*bound.radius();
	up = osg::Vec3d(-1, 1, 1);
	up.normalize();

	manipulator->setTransformation(eye, center, up);
	update();
}

void CX3DWindow::slotBacktoHome()
{
	osg::ref_ptr<osgGA::TrackballManipulator> manipulator = dynamic_cast<osgGA::TrackballManipulator*>(m_pOSGWidget->getCameraManipulator());
	if (!manipulator.valid())
		return;

	osg::Vec3d eye, center, up;
	manipulator->getHomePosition(eye, center, up);
	manipulator->setTransformation(eye, center, up);
	update();
}

void CX3DWindow::slotSetHome()
{
	osg::ref_ptr<osgGA::TrackballManipulator> manipulator = dynamic_cast<osgGA::TrackballManipulator*>(m_pOSGWidget->getCameraManipulator());
	if (!manipulator.valid())
		return;

	osg::Vec3d eye, center, up;
	manipulator->getTransformation(eye, center, up);
	manipulator->setHomePosition(eye, center, up);
}

void CX3DWindow::slotSynchronize(bool b)
{
	CXProcessEvent processEvent(m_pScene);
	CXCursor::Instance().AddEvent(m_ui.actionSynchronize->isChecked() ? EActivate : EDeactivate);
}

void CX3DWindow::_InitBGColor()
{
	const QColor& colorBackground = GetWindowInfo()->GetBackgroundColor();

	CXButtonColorEdit *pColorButton = new CXButtonColorEdit(this, colorBackground, "Change Background Color");
	pColorButton->setFixedWidth(40);
	m_ui.mainToolBar->addWidget(pColorButton);
	connect(pColorButton, SIGNAL(ColorSelected(const QColor&)), this, SLOT(slotChangeBGColor(const QColor&)));
	connect(pColorButton, SIGNAL(ColorSelected(const QColor&)), m_pScene, SLOT(slotChangeBGColor(const QColor&)));
	emit pColorButton->ColorSelected(colorBackground);
}

void CX3DWindow::_InitVolumeComboBox()
{
	m_pCbbDV = new QComboBox;
	m_pCbbDV->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	m_pActionDV = m_ui.bottomToolBar->addWidget(m_pCbbDV);
	m_pActionDV->setVisible(false);
	connect(m_pCbbDV, SIGNAL(currentIndexChanged(int)), SLOT(slotAttributeChanged(int)));
}

void CX3DWindow::_InitVCRControl()
{
	m_pVcrContrl = new CXVCRControl(this);
	m_pVcrContrl->CreateIt();
	m_pVcrContrl->ShowMe(false);
	connect(m_pVcrContrl, SIGNAL(CurrentSectionChanged(double)), this, SLOT(slotSectionValueChanged(double)));
}

void CX3DWindow::_InitZScale()
{
	// Z scale
	// CombBox
	m_pCombBoxZ = new QComboBox;

	QList<double> listValue;
	listValue << 0.1 << 0.2 << 0.5 << 1. << 2. << 3. << 4. << 5. << 7.5 << 10. << 20. << 50. << 100. << 200. << 500.;
	QStringList strItem;
	for (int i = 0; i < listValue.size(); ++i)
	{
		strItem.append(vtos(listValue.at(i), 3));
	}
	m_pCombBoxZ->addItems(strItem);
	m_pCombBoxZ->setMaximumWidth(80);
	m_pCombBoxZ->setMinimumWidth(80);
	m_pCombBoxZ->setEditable(false);
	m_pCombBoxZ->setCurrentIndex(5);
	m_ui.mainToolBar->addWidget(m_pCombBoxZ);

	connect(m_pCombBoxZ, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slotChangeZScale(const QString&)));

	// QAction
	// Increase Z
	QAction* pZIncreaseAction = new QAction(QIcon(::GetIconPath() + "ZIncrease.png"), tr("Increase Z"), this);
	m_ui.mainToolBar->addAction(pZIncreaseAction);
	connect(pZIncreaseAction, SIGNAL(triggered(bool)), this, SLOT(slotIncreaseZ(bool)));

	// Decrease Z
	QAction* pZDecreaseAction = new QAction(QIcon(::GetIconPath() + "ZDecrease.png"), tr("Decrease Z"), this);
	m_ui.mainToolBar->addAction(pZDecreaseAction);
	connect(pZDecreaseAction, SIGNAL(triggered(bool)), this, SLOT(slotDecreaseZ(bool)));
}

void CX3DWindow::slotChangeZScale(const QString& strValue)
{
	double dValue = strValue.toDouble();

	QList<double> listValue;
	for (int i = 0; i < m_pCombBoxZ->count(); ++i)
	{
		double dItemValue = m_pCombBoxZ->itemText(i).toDouble();
		listValue.append(dItemValue);
	}

	// tell if the data within the items
	for (int i = 0; i < listValue.size(); ++i)
	{
		if (qAbs(listValue.at(i) - dValue) < 0.0001)
		{
			m_pCombBoxZ->blockSignals(true);
			m_pCombBoxZ->setCurrentIndex(i);
			m_pCombBoxZ->blockSignals(false);
			m_pScene->slotUpdateZScale(dValue);
			return;
		}
	}

	// not within the items
	m_pCombBoxZ->blockSignals(true);
	int index = 0;
	if (dValue < listValue.front())
	{
		index = 0;
		listValue[index] = dValue;
	}
	else if (dValue > listValue.back())
	{
		index = listValue.size() - 1;
		listValue[index] = dValue;
	}
	else
	{
		for (int i = 1; i < listValue.size() - 1; ++i)
		{
			if (dValue > listValue.at(i - 1) && dValue < listValue.at(i + 1))
			{
				index = i;
				listValue[i] = dValue;
				break;
			}
		}
	}
	m_pCombBoxZ->clear();
	QStringList strItem;
	for (int i = 0; i < listValue.size(); ++i)
	{
		strItem.append(vtos(listValue.at(i), 3));
	}
	m_pCombBoxZ->addItems(strItem);
	m_pCombBoxZ->setCurrentIndex(index);
	m_pCombBoxZ->blockSignals(false);

	m_pScene->slotUpdateZScale(dValue);
}

void CX3DWindow::slotIncreaseZ(bool)
{
	double dZSscale = m_pCombBoxZ->currentText().toDouble();
	dZSscale *= 1.2;

	QString strValue = QString::number(dZSscale, 'f', 6);
	slotChangeZScale(strValue);
}

void CX3DWindow::slotDecreaseZ(bool)
{
	double dZSscale = m_pCombBoxZ->currentText().toDouble();
	dZSscale /= 1.2;

	QString strValue = QString::number(dZSscale, 'f', 6);
	slotChangeZScale(strValue);
}

void CX3DWindow::slotSectionValueChanged(double changedValue)
{
	//Update tree node name using new section number
	CXPickhandle* pickHandle = m_pOSGWidget->GetPickhandle();
	if (!pickHandle)
		return;

	CXObject *pCurSection = pickHandle->GetCurPickedObj();
	if (!pCurSection)
		return;

	CXProcessEvent processEvent;
	CXSeismicSection *pSection = dynamic_cast<CXSeismicSection*>(pCurSection);
	pSection->SetSectionNumber(changedValue);
	pCurSection->AddEvent(EDataChanged);
}

void CX3DWindow::slotAttributeChanged(int iIndex)
{
	auto pPickhandle = m_pOSGWidget->GetPickhandle();
	if (!pPickhandle)
		return;

	auto pSection = dynamic_cast<CXSeismicSection*>(pPickhandle->GetCurPickedObj());
	if (!pSection)
		return;

	CXViewInfoObject *pViewInfoSection = GetObjectViewInfo(pSection->GetObjectID());
	m_pScene->SetColorbarObjVisible(pViewInfoSection->GetAttributeObjID(), false);

	QUuid uuidCurrentVolume = m_pCbbDV->itemData(iIndex).toUuid();
	UpdateAttribute(pSection->GetObjectID(), uuidCurrentVolume);
	m_pScene->SetColorbarObjVisible(uuidCurrentVolume, true);
}

CXScene* CX3DWindow::GetScene()
{
	return NULL;
}

bool CX3DWindow::SetObjectVisibility(QUuid objID, bool bVisible)
{
	CXObject* pObj = ::GetObjectByID(objID);
	if (!pObj)
		return false;

	CXObject* pGeomObj = pObj->GetGeometryObject();
	CXViewInfoObject *pViewInfo = GetObjectViewInfo(pGeomObj->GetObjectID());
	pViewInfo->SetVisible(bVisible);

	if (_IsSection(pGeomObj) && bVisible)
	{
		if (pViewInfo->GetAttributeObjID() == pGeomObj->GetObjectID())
		{
			UpdateAttribute(pGeomObj->GetObjectID(), pGeomObj->GetAncient(EX3DSurvey)->GetChildren(EXSeismicDataVolume, true).front()->GetObjectID());
		}
	}
	
	m_pScene->SetOjbectVisiability(pGeomObj->GetObjectID(), bVisible);

	return true;
}

void CX3DWindow::UpdateAttribute(const QUuid & uuidGeom, const QUuid & uuidAttr)
{
	CXWindow::UpdateAttribute(uuidGeom, uuidAttr);
	m_pScene->UpdateAttribtue(uuidGeom);

	reinterpret_cast<CXBaseConsole*>(::GetConsole())->SetActiveWindow(this);
}

void CX3DWindow::SetGridModelControl(bool bShow)
{
	if (bShow) {
		if (0 == m_nCountActionGridModel) {
			m_pActionGridModel = new QAction(QIcon(::GetIconPath() + "SubGrid.png"), tr("Reservoir Sub-Gird"), this);
			m_ui.bottomToolBar->addAction(m_pActionGridModel);
			m_ui.bottomToolBar->setVisible(true);
			connect(m_pActionGridModel, SIGNAL(triggered()), this, SLOT(slotSubGridSetting()));
		}
		++m_nCountActionGridModel;
	}
	else
		--m_nCountActionGridModel;

	if (0 == m_nCountActionGridModel)
	{
		m_ui.bottomToolBar->removeAction(m_pActionGridModel);
		if (m_ui.bottomToolBar->actions().isEmpty())
		{
			m_ui.bottomToolBar->setVisible(true);
		}
	}
}

void CX3DWindow::ShowMessage(const QString& msg) const
{
	m_ui.statusBar->showMessage(msg);
}

void CX3DWindow::SetVolumeToolbarVisible(CXObject * pObj, bool bVisible)
{
	m_pActionDV->setVisible(bVisible);

	if (!pObj)
		return;

	CXViewInfoObject* pViewInfo = GetObjectViewInfo(pObj->GetObjectID());

	if (bVisible)
	{
		m_pCbbDV->blockSignals(true);
		m_pCbbDV->clear();

		for (auto pObj : pObj->GetAncient(EX3DSurvey)->GetChildren(EXSeismicDataVolume, true))
		{
			m_pCbbDV->addItem(QIcon(::GetIconPath() + pObj->GetIconName()), pObj->GetObjectName(), pObj->GetObjectID().toString());
		}

		m_pCbbDV->setCurrentIndex(m_pCbbDV->findData(pViewInfo->GetAttributeObjID()));
		m_pCbbDV->blockSignals(false);
	}

	m_pScene->SetColorbarObjVisible(pViewInfo->GetAttributeObjID(), bVisible);
}

CXWindowInfo3D* CX3DWindow::GetWindowInfo()
{
	if (m_pWindowInfo == nullptr)
		m_pWindowInfo = new CXWindowInfo3D;
	
	return m_pWindowInfo;
}

void CX3DWindow::SaveScene()
{
	GetWindowInfo()->SetZScale(GetZScale());
	if (m_pActionDV && m_pActionDV->isVisible())
	{
		GetWindowInfo()->SetCurrentDV(m_pCbbDV->currentData().toUuid());
	}
}

void CX3DWindow::RestoreScene()
{
	float fZScale = GetWindowInfo()->GetZScale();
	QString strValue = QString::number(fZScale, 'f', 6);
	slotChangeZScale(strValue);
	
	if (m_pActionDV && m_pActionDV->isVisible())
	{
		int foundDVIndex = m_pCbbDV->findData(GetWindowInfo()->GetCurrentDV());
		if (foundDVIndex != -1)
		{
			m_pCbbDV->setCurrentIndex(foundDVIndex);
		}
	}
}

void CX3DWindow::SetVCRControlData(CXSeismicSection *pSection, bool bShow)
{
	m_pVcrContrl->ShowMe(bShow);

	if (bShow)
	{
		const CXSeismicUTMTool& utm = pSection->GetUTM();
		double dNumber = pSection->GetSectionNumber();
		QUuid volumeID = GetObjectViewInfo(pSection->GetObjectID())->GetAttributeObjID();
		auto pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(volumeID));

		double start, end, interval;
		pDV->GetSamplingRange(start, end, interval);

		switch (pSection->GetSectionType())
		{
		case eInlineSection:
			m_pVcrContrl->InitData(utm.GetFirstInline(), utm.GetLastInline(), pSection->GetSectionNumber(), utm.GetInlineIncrement(), utm.GetInlineIncrement(), -1);
			break;
		case eCrosslineSection:
			m_pVcrContrl->InitData(utm.GetFirstCrossline(), utm.GetLastCrossline(), pSection->GetSectionNumber(), utm.GetCrosslineIncrement(), utm.GetCrosslineIncrement(), -1);
			break;
		case eTimeSlice:
			m_pVcrContrl->InitData(start, end, pSection->GetSectionNumber(), interval, interval, -1);
			break;
		default:
			Q_ASSERT(!"error section type");
		}
	}
}

bool CX3DWindow::_IsSection(CXObject* pObj)
{
	QList<EXObjectType> listSectionType{ EXSeismicSection, EXRandomSection, EXSeismicSubVolume };
	if (listSectionType.contains(pObj->GetObjectType()))
		return true;
	else
		return false;
}

void CX3DWindow::UpdateVCRControlData(QUuid changedObjID)
{
	if (!m_pVcrContrl->IsVisible())
		return;

	auto pPickhandle = dynamic_cast<CXPickhandle*>(m_pOSGWidget->GetPickhandle());
	if (!pPickhandle || pPickhandle->GetCurPickedObj()->GetObjectID() != changedObjID)
		return;

	auto pSection = dynamic_cast<CXSeismicSection*>(::GetObjectByID(changedObjID));
	m_pVcrContrl->SetSliderSpinValue(pSection->GetSectionNumber());
}

void CX3DWindow::slotChangeBGColor(const QColor& color)
{
	m_pOSGWidget->getCamera()->setClearColor(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
}

void CX3DWindow::slotShowCoordinates(bool bShow)
{
	m_pWindowInfo->SetCoordVisible(bShow);
	m_pScene->ShowCoordinate(bShow);
}

void CX3DWindow::slotShowCoordinatesGrid(bool bGridShow)
{
	m_pWindowInfo->SetCoordGridVisible(bGridShow);
	m_pScene->ShowCoordinateGrid(bGridShow);
}

float CX3DWindow::GetZScale()
{
	return m_pCombBoxZ->currentText().toFloat();
}

void CX3DWindow::resizeEvent(QResizeEvent *event)
{
	emit UpdateWindowSize(this->width(), this->height());
}

void CX3DWindow::closeEvent(QCloseEvent * event)
{
	if (m_pDlgLightingSetting)
		m_pDlgLightingSetting->close();
	if (m_subGridDialog)
		m_subGridDialog->reject();
}

void CX3DWindow::slotShowCompass(bool bShow)
{
	m_pScene->ShowCompass(bShow);
}

void CX3DWindow::slotShowColormap(bool bShow)
{
	m_pScene->ShowColormap(bShow);
}

void CX3DWindow::slotLightSetting()
{
	if (!m_pDlgLightingSetting)
	{
		m_pDlgLightingSetting = new CXDlg3DLightingSetting(this);
	}
	m_pDlgLightingSetting->show();
}

void CX3DWindow::slotSubGridSetting()
{
    m_ui.bottomToolBar->setVisible(true);
	if (m_subGridDialog == NULL)
	{
		QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
		m_subGridDialog = new CXSubGridSetting(pParentWidget, this);
	}
	m_subGridDialog->show();
}

//void CXOSGWindow::slotAssignTo()
//{
//	QAction *pAction = dynamic_cast<QAction*>(sender());
//	QUuid uid(pAction->data().toString());
//	CXFaultSticks *pStricks = dynamic_cast<CXFaultSticks*>( GetObjectByID(uid));
//	QList<CXObject *> listObjects = GetProject()->GetChildren(EXFaultSticks, true);
//	QPolygonF polygon = m_pOSGWidget->GetAnchorPickup()->GetFillPolygon();//
//	float fZScale = GetZScale();
//	osg::Matrix viewMat=m_pOSGWidget->getCamera()->getViewMatrix();
//	osg::Matrix projMat=m_pOSGWidget->getCamera()->getProjectionMatrix();
//	osg::Matrix winMat=m_pOSGWidget->getCamera()->getViewport()->computeWindowMatrix();
//	osg::Matrix pipeMat=viewMat*projMat*winMat;
//	QList<QUuid> lstAll = Get3DScene()->GetAllDisplayObject();
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
//			GetCoordMap()->MapWorldToLocal(vecPos,vecLocal);
//			vecLocal[2]*=fZScale;
//			osg::Vec3d vecPoint =vecLocal * pipeMat;
//			QPointF ScreenPos(vecPoint.x(),m_pOSGWidget->size().height()-vecPoint.y());
//			if (polygon.containsPoint(ScreenPos,Qt::WindingFill) && !pStricks->GetAllSticks().contains(pStick))
//			{
//				pStricks->GetAllSticks().append(pStick);
//			}
//		}	
//		pFaultStrick->SetModifiedFlag();
//		CXProcessEvent processEvent;
//		pFaultStrick->AddEvent(EDataChanged);
//	}
//	m_pOSGWidget->RemoveAnchorPickup();
//}
