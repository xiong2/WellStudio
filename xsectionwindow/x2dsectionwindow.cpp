#include "x2dsectionwindow.h"

#include <QToolBar>
#include <QComboBox>
#include <QScrollBar>
#include <qdebug.h>
#include <QDockWidget>

#include "x2dsectionview.h"
#include "xsectionscene.h"
#include "x2dsectionaxis.h"
#include "xglobal.h"
#include "xwindowinfosection.h"
#include "xvcrcontrol.h"
#include "xsecwindowproperties.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xseismicdatavolume.h"
#include "xeventconsole.h"
#include "xtree.h"
#include "x3dhorizon.h"
#include "xcolormapcombo.h"
#include "xhorizontrackpar.h"
#include "xproject.h"
#include "x3dsurvey.h"
#include "xsliderspinwidget.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "x2dseismicline.h"
#include "xseismicdataline.h"
#include "xsectionscene.h"
#include "xviewinfomanager.h"
#include "xcolormapwidget.h"
#include "xdlgproperty.h"
#include "xbaseconsole.h"
#include "xdlgnewobject.h"
#include "xdlghorizontrackpara.h"
#include "xlog.h"
#include "xabstractitem.h"
#include "xsechorizonpickingitem.h"
#include "xwaitcursor.h"
#include "xviewutility.h"
#include "xcoordtransformer.h"

CX2DSectionWindow::CX2DSectionWindow(QString sWindowName, QWidget* parent, Qt::WindowFlags flags)
	: CXWindow(sWindowName, parent, flags),
	m_pScene(nullptr),
	m_pDigitizingItem(nullptr),
	m_pAxisWidget(nullptr),
	m_eEditMode(Edit_NULL),
	m_bSectionSync(false)
{
	setAttribute(Qt::WA_DeleteOnClose);

	m_eWindowType = eSectionWindowBlank;
	m_pView = nullptr;
	SetObjectID(::GetUniqueGuid());

	m_ui.setupUi(this);

	setWindowIcon(QIcon(::GetIconPath() + "SectionWindow24x24.png"));
	setMinimumSize(800, 600);

	m_p2DWindowInfo = dynamic_cast<CXWindowInfoSection*>(GetObjectViewInfo(GetObjectID()));
	m_pHorizonTrackPar = new CXHorizonTrackPar;
}

CX2DSectionWindow::~CX2DSectionWindow()
{
	m_vecRectZoomInfo.clear();

	if (m_pHorizonTrackPar)
	{
		delete m_pHorizonTrackPar;
		m_pHorizonTrackPar = nullptr;
	}
	m_p2DWindowInfo = nullptr;
}

void CX2DSectionWindow::_InitConnection()
{
	connect(m_ui.actionRectZoom, SIGNAL(triggered()), this, SLOT(slotRectZoom()));
	connect(m_ui.actionRectZoomUndo, SIGNAL(triggered()), this, SLOT(slotRectZoom()));
	connect(m_ui.actionCancelZoomin, SIGNAL(triggered()), this, SLOT(slotRectZoom()));
	connect(m_ui.m_actionProperties, SIGNAL(triggered()), this, SLOT(slotWindowProperties()));
	connect(m_ui.m_actionZoomIn, SIGNAL(triggered()), this, SLOT(slotZoom()));
	connect(m_ui.m_actionZoomOut, SIGNAL(triggered()), this, SLOT(slotZoom()));
	connect(m_ui.m_actionIncreaseHorizonScale, SIGNAL(triggered()), this, SLOT(slotZoom()));
	connect(m_ui.m_actionDecreaseHorizonScale, SIGNAL(triggered()), this, SLOT(slotZoom()));
	connect(m_ui.m_actionIncreaseVerticalScale, SIGNAL(triggered()), this, SLOT(slotZoom()));
	connect(m_ui.m_actionDecreaseVerticalScale, SIGNAL(triggered()), this, SLOT(slotZoom()));
	connect(m_ui.m_actionViewAll, SIGNAL(triggered()), this, SLOT(slotZoom()));
	connect(m_ui.m_actionFitToWindowWidth, SIGNAL(triggered()), this, SLOT(slotZoom()));
	connect(m_ui.m_actionFitToWindowHeight, SIGNAL(triggered()), this, SLOT(slotZoom()));
	connect(m_ui.m_actionIncreaseExcursion, SIGNAL(triggered()), this, SLOT(slotZoom()));
	connect(m_ui.m_actionDecreaseExcursion, SIGNAL(triggered()), this, SLOT(slotZoom()));
	connect(m_ui.m_actionVariableIntensity, SIGNAL(triggered()), this, SLOT(slotVaribleIntensity()));
	connect(m_ui.m_actionWiggle, SIGNAL(triggered()), this, SLOT(slotWiggle()));
	connect(m_ui.m_actionVariableAreaWiggle, SIGNAL(triggered()), this, SLOT(slotWiggleArea()));
	connect(m_ui.m_actionFaultDigitizingTools, SIGNAL(triggered()), this, SLOT(slotShowFaultTools()));
	connect(m_ui.m_actionHorizonTrackingTools, SIGNAL(triggered()), this, SLOT(slotShowHorizonTools()));
	connect(m_ui.m_action2ndLayerTools, &QAction::toggled, m_p2ndLayerToolbar, &QToolBar::setVisible);
	connect(m_ui.m_actionOrthoSections, SIGNAL(triggered()), this, SLOT(slotShowOrthoSectionToos()));
}
void CX2DSectionWindow::ClearContent()
{
	m_eWindowType = eSectionWindowBlank;

	QList<QUuid> listBlank;
	CXTree::Instance().UpdateTreeStatus(listBlank, m_eWindowType);

	_enableIcons(false);

	m_pScene->DeleteAllItems();
	m_pScene->update();
}

QUuid CX2DSectionWindow::_GetFirstPostStackID(const QList<CXObject*>& listAttri)
{
	if (listAttri.isEmpty())
		return QUuid();

	for (auto pObj : listAttri)
	{
		auto pSeismicObj = dynamic_cast<CXSeismicObject*>(pObj);
		if (!pSeismicObj)
			continue;

		if (!pSeismicObj->IsPrestack())
		{
			return pSeismicObj->GetObjectID();
		}
	}

	return listAttri.front()->GetObjectID();
}

void CX2DSectionWindow::_enableIcons(bool bEnable)
{
	m_ui.m_actionViewAll->setEnabled(bEnable);
	m_ui.m_actionFitToWindowWidth->setEnabled(bEnable);
	m_ui.m_actionFitToWindowHeight->setEnabled(bEnable);
	m_ui.m_actionZoomIn->setEnabled(bEnable);
	m_ui.m_actionZoomOut->setEnabled(bEnable);
	m_ui.m_actionIncreaseHorizonScale->setEnabled(bEnable);
	m_ui.m_actionDecreaseHorizonScale->setEnabled(bEnable);
	m_ui.m_actionIncreaseVerticalScale->setEnabled(bEnable);
	m_ui.m_actionDecreaseVerticalScale->setEnabled(bEnable);
	m_ui.m_actionIncreaseExcursion->setEnabled(bEnable);
	m_ui.m_actionDecreaseExcursion->setEnabled(bEnable);
	m_ui.m_actionVariableIntensity->setEnabled(bEnable);
	m_ui.m_actionVariableIntensity->setEnabled(bEnable);
	m_ui.m_actionWiggle->setEnabled(bEnable);
	m_ui.m_actionOrthoSections->setEnabled(bEnable);
	m_ui.m_actionHorizonTrackingTools->setEnabled(bEnable);
	m_ui.m_actionFaultDigitizingTools->setEnabled(bEnable);
	m_ui.m_action2ndLayerTools->setEnabled(bEnable);
	m_ui.actionRectZoom->setEnabled(bEnable);

	if (!bEnable)
	{
		m_pHorizonToolbar->setHidden(true);
		m_pFaultToolbar->setHidden(true);
		m_p2ndLayerToolbar->setHidden(true);

		m_ui.actionRectZoomUndo->setEnabled(false);
		m_ui.actionCancelZoomin->setEnabled(false);
	}
}

void CX2DSectionWindow::_initHorizonCB()
{
	m_pCbbHorizons->blockSignals(true);
	m_pCbbHorizons->clear();

	CXSeismicObject *pSObj = dynamic_cast<CXSeismicObject *>(m_pScene->GetBackgroundSection(false));
	if (!pSObj)
		return;

	CXObject *pObj = ::GetObjectByID(pSObj->GetSurveyID());
	if (!pObj)
		return;

	QList<CXObject*> listChildren = pObj->GetChildren(EX3DHorizon, true);

	m_pCbbHorizons->addItem("None", QVariant());
	foreach(CXObject *pObject, listChildren)
	{
		CX3DHorizon *pHorizon = dynamic_cast<CX3DHorizon *>(pObject);
		m_pCbbHorizons->addItem(QIcon(GetIconPath() + pHorizon->GetIconName()), pObject->GetObjectName(), QVariant(pObject->GetObjectID().toString()));
	}

	m_pCbbHorizons->blockSignals(false);
	m_pHTrackPara->setDisabled(true);
	m_pGroupHorizonTrack->setDisabled(true);
	m_pTrackingModeAction->setDisabled(true);
}

void CX2DSectionWindow::_InitHorizonTrackingTools()
{
	m_pHorizonToolbar = new QToolBar(tr("Horizon interface tools"), this);
	addToolBar(Qt::BottomToolBarArea, m_pHorizonToolbar);
	m_pHorizonToolbar->setHidden(true);

	m_pCbbHorizons = new QComboBox;
	m_pCbbHorizons->setMinimumWidth(120);
	connect(m_pCbbHorizons, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentHorizonChanged(int)));
	m_pHorizonToolbar->addWidget(m_pCbbHorizons);

	m_pHorizonToolbar->addAction(QIcon(GetIconPath() + "HorizonNew.png"), "New Horizon", this, SLOT(slotNewHorizon()));
	m_pHTrackPara = m_pHorizonToolbar->addAction(QIcon(GetIconPath() + "trackpara.png"), "Horizon Tracking Parameters...", this, SLOT(slotTrackPara()));
	m_pHorizonToolbar->addSeparator();

	auto funcSetGroupProp = [](QList<QAction*> list, int checkedID)
	{
		for (int i = 0; i != list.size(); ++i)
		{
			QAction *action = list.at(i);
			action->setData(i);
			action->setCheckable(true);
		}
		list.at(checkedID)->setChecked(true);
	};

	m_pGroupHorizonTrack = new QActionGroup(this);
	connect(m_pGroupHorizonTrack, SIGNAL(triggered(QAction *)), this, SLOT(slotSetHorizonDigitMode(QAction *)));

	QAction *pAction = m_pHorizonToolbar->addAction(QIcon(GetIconPath() + "HorizonTrackManual.png"), tr("Manually Digitize")/*, this, SLOT(slotHorizonManual())*/);
	m_pGroupHorizonTrack->addAction(pAction);
	pAction = m_pHorizonToolbar->addAction(QIcon(GetIconPath() + "HorizonTrackSemiAuto.png"), tr("Semi-auto Digitize")/*, this, SLOT(slotHorizonSingleDouble())*/);
	m_pGroupHorizonTrack->addAction(pAction);
	pAction = m_pHorizonToolbar->addAction(QIcon(GetIconPath() + "HorizonTrackAuto.png"), tr("Auto Digitize")/*, this, SLOT(slotHorizonSingleLeft())*/);
	m_pGroupHorizonTrack->addAction(pAction);
	m_pHorizonToolbar->addSeparator();
	pAction = m_pHorizonToolbar->addAction(QIcon(GetIconPath() + "sectionerase.png"), tr("Section Erase")/*, this, SLOT(slotHorizonSingleDouble())*/);
	m_pGroupHorizonTrack->addAction(pAction);
	m_pHorizonToolbar->addSeparator();
	funcSetGroupProp(m_pGroupHorizonTrack->actions(), 0);

	QActionGroup* pTrackModeActionGroup = new QActionGroup(this);
	connect(pTrackModeActionGroup, SIGNAL(triggered(QAction *)), this, SLOT(slotSetCurrentTrackingMode(QAction *)));
	m_eHorizonTrackMode = ELockAndContinue;

	m_pTrackingModeAction = new QAction(this);
	QMenu* pTrackingModeMenu = new QMenu("Tracking Mode", m_pHorizonToolbar);
	pAction = pTrackingModeMenu->addAction(QIcon(GetIconPath() + "overwrite.png"), tr("Overwrite")/*, this, SLOT(slotHorizonOverwrite())*/);
	pTrackModeActionGroup->addAction(pAction);
	pAction = pTrackingModeMenu->addAction(QIcon(GetIconPath() + "stop.png"), tr("Stop")/*, this, SLOT(slotHorizonStopTrackingMode())*/);
	pTrackModeActionGroup->addAction(pAction);
	funcSetGroupProp(pTrackingModeMenu->actions(), 1);
	slotSetCurrentTrackingMode(pAction);

	m_pTrackingModeAction->setMenu(pTrackingModeMenu);
	m_pHorizonToolbar->addAction(m_pTrackingModeAction);
}

void CX2DSectionWindow::_initFaultCB()
{
	m_pCbbFaults->blockSignals(true);
	m_pCbbFaults->clear();
	m_pCbb2ndFaults->clear();

	CXSeismicObject *pSObj = dynamic_cast<CXSeismicObject *>(m_pScene->GetBackgroundSection(false));
	if (!pSObj)
		return;

	CXObject *pObj = ::GetObjectByID(pSObj->GetSurveyID());
	if (!pObj)
		return;

	QList<CXObject *> listFault = pObj->GetChildren(EXFaultSticks, true);

	m_pCbbFaults->addItem("None", QVariant());
	foreach(CXObject *pObject, listFault)
	{
		m_pCbbFaults->addItem(QIcon(GetIconPath() + pObject->GetIconName()), pObject->GetObjectName(), QVariant(pObject->GetObjectID().toString()));
		m_pCbb2ndFaults->addItem(QIcon(GetIconPath() + pObject->GetIconName()), pObject->GetObjectName(), QVariant(pObject->GetObjectID().toString()));
	}

	m_pCbbFaults->blockSignals(false);

	m_pCbb2ndFaults->setDisabled(true);
	m_pFaultAssign->setDisabled(true);
}

void CX2DSectionWindow::_InitFaultDigitizingTools()
{
	m_pFaultToolbar = new QToolBar(tr("Fault digitizing"), this);
	m_pFaultToolbar->hide();

	m_pCbbFaults = new QComboBox;
	m_pCbbFaults->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	connect(m_pCbbFaults, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrentFaultchanged(int)));
	m_pFaultToolbar->addWidget(m_pCbbFaults);

	m_pFaultToolbar->addAction(QIcon(GetIconPath() + "FaultNew.png"), "New Fault", this, SLOT(slotNewFault()));

	m_pFaultToolbar->addSeparator();

	m_pFaultAssign = m_pFaultToolbar->addAction(QIcon(GetIconPath() + "FaultAssign.png"), "Assign Fault Stick", this, SLOT(slotAssignFaultStick()));
	m_pCbb2ndFaults = new QComboBox;
	m_pCbb2ndFaults->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	m_pFaultToolbar->addWidget(m_pCbb2ndFaults);

	addToolBar(Qt::BottomToolBarArea, m_pFaultToolbar);
}

void CX2DSectionWindow::_Init2ndLayerTools()
{
	m_p2ndLayerToolbar = new QToolBar("2nd layer tools", this);
	addToolBarBreak(Qt::BottomToolBarArea); 
	addToolBar(Qt::BottomToolBarArea, m_p2ndLayerToolbar);
	m_p2ndLayerToolbar->hide();

	m_pCbb2ndLayer = new QComboBox;
	m_pCbb2ndLayer->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
	m_pCbb2ndLayer->addItem("None", QVariant());
	m_p2ndLayerToolbar->addWidget(m_pCbb2ndLayer);
	connect(m_pCbb2ndLayer, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCurrent2ndLayerChanged(int)));

	m_p2ndColormap = new CXColormapCombo(this);
	m_p2ndColormap->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	m_p2ndColormap->setDisabled(true);
	m_p2ndLayerToolbar->addWidget(m_p2ndColormap);
	connect(m_p2ndColormap, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slotChangedForeColormap(const QString&)));

	m_p2ndWiggleGroup = new QActionGroup(this);
	m_p2ndWiggleGroup->setExclusive(false);
	m_p2ndWiggleGroup->setDisabled(true);

	QAction *pAction = m_p2ndLayerToolbar->addAction(QIcon(GetIconPath() + "VaribleIntensity.png"), "Variable Intensity", this, SLOT(slotForeVaribleIntensity()));
	pAction->setCheckable(true);
	m_p2ndWiggleGroup->addAction(pAction);

	pAction = m_p2ndLayerToolbar->addAction(QIcon(GetIconPath() + "Wiggle.png"), "Wiggle", this, SLOT(slotForeWiggle()));
	pAction->setCheckable(true);
	m_p2ndWiggleGroup->addAction(pAction);

	pAction = m_p2ndLayerToolbar->addAction(QIcon(GetIconPath() + "WiggleArea.png"), "Variable Area + Wiggle", this, SLOT(slotForeWiggleArea()));
	pAction->setCheckable(true);
	m_p2ndWiggleGroup->addAction(pAction);

	m_p2ndLayerToolbar->addSeparator();
	m_p2ndAlphaWidget = new CXSliderSpinWidget;
	m_p2ndAlphaWidget->HideLabel(true);
	m_p2ndAlphaWidget->InitWidget(0.0, 1.0, 0.1, 11, 1);
	m_p2ndAlphaWidget->SetValue(0.3);
	m_p2ndAlphaWidget->SetSpinSingleStep(0.1);
	connect(m_p2ndAlphaWidget, SIGNAL(ValueChanged(double)), this, SLOT(slotChangedForeAlpha(double)));
	pAction = m_p2ndLayerToolbar->addWidget(m_p2ndAlphaWidget);
	pAction->setVisible(false);
	m_p2ndWiggleGroup->addAction(pAction);
}

void CX2DSectionWindow::_SetSection(CXObject* pNewObj, bool bVisable)
{
	// deactivate
	m_pScene->DeactiveItem();

	CXObject* pCurrentSectionObj = GetCurrentGeometryObj();
	CXViewInfoObject* pObjViewInfo = GetObjectViewInfo(pNewObj->GetObjectID());

	if (bVisable)
	{
		// Create
		if (pCurrentSectionObj == pNewObj) 
			return;

		_UpdateVolumeList(pNewObj);
		QUuid attObjID = pObjViewInfo->GetAttributeObjID();
		if (attObjID == pNewObj->GetObjectID())
		{
			attObjID = GetCurrentAttributeID();
		}
		else
		{
			m_pCbbVolumes->blockSignals(true);
			m_pCbbVolumes->setCurrentIndex(m_pCbbVolumes->findData(attObjID));
			m_pCbbVolumes->blockSignals(false);
		}

		if (dynamic_cast<CX2DSeismicLine*>(pNewObj))
		{
			UpdateAttribute(pNewObj->GetObjectID(), attObjID);
		}

		if(!m_pScene->SetBackData((CXSeismicObject *)::GetObjectByID(attObjID), pNewObj))
			return;

		pObjViewInfo->SetAttributeObjID(attObjID);
		m_pAxisWidget->SetDisplaySection(pNewObj);
		
		if (EXSeismicSection == pNewObj->GetObjectType())
		{
			_InitVcrControl(dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(attObjID)), dynamic_cast<CXSeismicSection*>(pNewObj));
			m_pVcrContrl->ShowMe(true);
		}

        CXViewInfoObject *pAttrObjViewInfo = GetObjectViewInfo(attObjID);
        
        if (!m_pColormapWidget)
        {
            m_pColormapWidget = new CXColormapWidget(pAttrObjViewInfo->GetColormapName());
            m_pColormapDock->setWidget(m_pColormapWidget);
            connect(m_pColormapWidget, SIGNAL(OpenColormapEditingDialog()), this, SLOT(slotOpenColormapEditor()));
        }

        SetColormapName(pAttrObjViewInfo->GetColormapName());
        m_pColormapWidget->SetColormapName(pAttrObjViewInfo->GetColormapName());
        m_pColormapWidget->SetDisplayRange(pAttrObjViewInfo->GetDisplayDataMin(), pAttrObjViewInfo->GetDisplayDataMax());
		
		// update seismic data
		//m_pScene->UpdateSectionData();

		// process viewer resize event to get right viewer size
		QCoreApplication::instance()->processEvents();

		double dWidth, dHeight;
		NXViewUtility::GetSizeFromViewInfo(m_p2DWindowInfo, m_pScene, dWidth, dHeight);
		
		// rect
		m_pView->verticalScrollBar()->setRange(0, 0);
		m_pView->horizontalScrollBar()->setRange(0, 0);
		QRectF rect(0, 0, dWidth, dHeight);
		SetSceneRect(rect, false);

		m_eWindowType = eSectionWindow;

		QList<QUuid> listBlank;
		listBlank << pNewObj->GetObjectID();
		CXTree::Instance().UpdateTreeStatus(listBlank, m_eWindowType);

		_enableIcons(true);
		slotShowOrthoSectionToos();
	}
	else
	{
		// Remove
		if (!pCurrentSectionObj || pCurrentSectionObj != pNewObj)
			return;
		if (EXSeismicSection == pCurrentSectionObj->GetObjectType())
		{
			m_pVcrContrl->ShowMe(false);
		}

        m_pScene->SetBackData(nullptr, nullptr);
		m_pAxisWidget->SetDisplaySection(NULL);

        m_pColormapDock->setWindowTitle("Colormap");
        delete m_pColormapWidget;
        m_pColormapWidget = nullptr;

		m_pScene->SetEditMode(Edit_NULL);
		m_pScene->DeactiveItem();
	}
}

void CX2DSectionWindow::InitWindow()
{
	m_pScene = new CXSectionScene(this, this);
	m_pView = new CX2DSectionView(m_pScene, eSectionWindowBlank, nullptr);

	m_pAxisWidget = new CX2DSectionAxis(this);
	m_pAxisWidget->show();
	setCentralWidget(m_pAxisWidget);
	m_pAxisWidget->AddWidget(m_pView);	

	connect(m_pView->horizontalScrollBar(), &QScrollBar::valueChanged, this, &CX2DSectionWindow::slotSynHorizonAxis);
	connect(m_pView->verticalScrollBar(), &QScrollBar::valueChanged, this, &CX2DSectionWindow::slotSynVerticalAxis);

	///! Colormap
	m_pCcbColorMap = new CXColormapCombo(this);
	m_ui.m_toolbarColormap->addWidget(m_pCcbColorMap);
	connect(m_pCcbColorMap, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slotChangedColormap(const QString&)));

	///! Volumes
	m_pCbbVolumes = new QComboBox;
	m_pCbbVolumes->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	m_ui.m_toolBarVolumes->addWidget(m_pCbbVolumes);
	connect(m_pCbbVolumes, SIGNAL(currentIndexChanged(int)), SLOT(slotCurrentAttributeChanged(int)));

	QActionGroup* pToolsGroup = new QActionGroup(this);
	connect(pToolsGroup, &QActionGroup::triggered, this, &CX2DSectionWindow::slotSetToolsDigitMode);
	pToolsGroup->addAction(m_ui.m_actionFaultDigitizingTools);
	pToolsGroup->addAction(m_ui.m_actionHorizonTrackingTools);
	pToolsGroup->addAction(m_ui.m_action2ndLayerTools);
	pToolsGroup->addAction(m_ui.m_actionOrthoSections);
	pToolsGroup->setExclusive(false);

	_InitHorizonTrackingTools();
	_InitFaultDigitizingTools();
	_Init2ndLayerTools();

	m_pVcrContrl = new CXVCRControl(this);
	m_pVcrContrl->CreateIt();
	insertToolBarBreak(m_pVcrContrl->m_pTBarVCR);
	connect(m_pVcrContrl, SIGNAL(CurrentSectionChanged(double)), this, SLOT(slotSectionValueChanged(double)));

    m_pColormapDock = new QDockWidget("Colormap");
    addDockWidget(Qt::RightDockWidgetArea, m_pColormapDock);

	//	Disable all icons.
	_enableIcons(false);

	_InitConnection();
}

void CX2DSectionWindow::InitOpenGL()
{
	if (!m_pScene)
		return;

	m_pScene->InitOpenGLBuilder();
}

void CX2DSectionWindow::SetColormapName(QString colormapName, bool bFore)
{
	if (bFore)
	{
		disconnect(m_p2ndColormap, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slotChangedForeColormap(const QString&)));
		m_p2ndColormap->SetCurrentText(colormapName);
		m_p2ndColormap->UpdateCurrentColormapIcon();
		connect(m_p2ndColormap, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slotChangedForeColormap(const QString&)));
	}
		
	else
	{
		disconnect(m_pCcbColorMap, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slotChangedColormap(const QString&)));
		disconnect(m_pColormapWidget, &CXColormapWidget::signalChangedColormap, this, &CX2DSectionWindow::slotChangedColormap);
		m_pCcbColorMap->SetCurrentText(colormapName);
		m_pCcbColorMap->UpdateCurrentColormapIcon();
		connect(m_pCcbColorMap, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(slotChangedColormap(const QString&)));
		connect(m_pColormapWidget, &CXColormapWidget::signalChangedColormap, this, &CX2DSectionWindow::slotChangedColormap);
	}
}

QList<CXObject*> CX2DSectionWindow::_FetchAttributesByGeometry(CXObject* pGeo)
{
	QList<CXObject*> listResult;

	if (!pGeo) return listResult;

	// Seismic
	if (pGeo->GetParent() && QList<EXObjectType>{EXSeismicSection, EXRandomSection}.contains(pGeo->GetObjectType()))
	{
		auto pSeismicObj = dynamic_cast<CXSeismicSection*>(pGeo);
		if (pSeismicObj && eTimeSlice == pSeismicObj->GetSectionType())
		{
			return listResult;
		}

		listResult << pGeo->GetParent()->GetChildren(EXSeismicDataVolume, true);
	}
	
	if (EX2DSeismicLine == pGeo->GetObjectType())
	{
		listResult << pGeo->GetChildren(EXSeismicDataLine, true);
	}

	return listResult;
}

bool CX2DSectionWindow::SetObjectVisibility(QUuid objID, bool bVisible)
{
    if (!::GetObjectByID(objID))
        return false;

	CXViewInfoObject* pObjViewInfo = GetObjectViewInfo(objID);
    if (!pObjViewInfo)
        return false;

	pObjViewInfo->SetVisible(bVisible);

	auto pObj = dynamic_cast<CXObject*>(::GetObjectByID(objID));
	if (!pObj) return false;
	if (IsSection(objID))
	{
		_SetSection(pObj, bVisible);
	}

	// items
	if (bVisible)
	{
		m_pScene->CreateItem(objID, pObjViewInfo);
	}
	else
	{
		m_pScene->DeleteItem(objID);
	}
	
	return true;
}

bool CX2DSectionWindow::SerializeData(CXArchive& ar)
{
	if (!CXWindow::SerializeData(ar))
		return false;

	return true;
}

void CX2DSectionWindow::slotCurrentFaultchanged(int nIdx)
{
	if (nIdx == 0)
	{
		m_pCbb2ndFaults->setDisabled(true);
		m_pFaultAssign->setDisabled(true);
	}
	else
	{
		m_pCbb2ndFaults->setDisabled(m_pCbb2ndFaults->count() < 2);
		m_pFaultAssign->setDisabled(m_pCbb2ndFaults->count() < 2);
	}

	m_pScene->SetActiveItem(m_pCbbFaults->itemData(nIdx).toString());

	//	The active node should be check on the tree!
	SetObjectVisibility(QUuid(m_pCbbFaults->itemData(nIdx).toString()), true);

	QList<QUuid> listObjID;
	listObjID << QUuid(m_pCbbFaults->itemData(nIdx).toString());
	CXTree::Instance().ChangeTreeItemStatus(listObjID, true);

	m_pView->update();
	m_pScene->update();
}

void CX2DSectionWindow::slotCurrent2ndLayerChanged(int nIndex)
{
	if (0 > nIndex) 
		return;

	m_p2ndWiggleGroup->actions().front()->setChecked(nIndex != 0);
	m_p2ndWiggleGroup->actions().back()->setVisible(nIndex != 0);

	if (0 == nIndex) // none
	{
		m_p2ndColormap->setDisabled(true);
		m_p2ndWiggleGroup->setDisabled(true);
		m_pScene->SetForeData(nullptr, nullptr);
	}
	else
	{
		m_p2ndColormap->setDisabled(false);
		m_p2ndWiggleGroup->setDisabled(false);

		QUuid attribute2rdID = m_pCbb2ndLayer->itemData(nIndex).toUuid();

		auto pSeismicObj = dynamic_cast<CXSeismicObject*>(GetObjectByID(attribute2rdID));
		if (!pSeismicObj)
			return;

		CXObject* pCurrSection = GetCurrentGeometryObj();
		if (!pCurrSection)
			return;

		m_pScene->SetForeData(pSeismicObj, pCurrSection);

		// set colormap
		CXViewInfoObject* pAttrObjViewInfo = GetObjectViewInfo(attribute2rdID);
		SetColormapName(pAttrObjViewInfo->GetColormapName(), true);
	}

	_ChangeScale(false);
}

void CX2DSectionWindow::slotCurrentAttributeChanged(int index)
{
	CXWaitCursor waitCursor;
	QUuid attributeID = m_pCbbVolumes->itemData(index).toUuid();

	auto pSeismicObj = dynamic_cast<CXSeismicObject*>(GetObjectByID(attributeID));
	if (!pSeismicObj)
		return;
	CXObject* pCurrSection = GetCurrentGeometryObj();
	if (!pCurrSection)
		return;

	CXViewInfoObject *pGeoViewInfo = GetObjectViewInfo(pCurrSection->GetObjectID());
	GetObjectViewInfo(pGeoViewInfo->GetAttributeObjID())->SetVisible(false);
	pGeoViewInfo->SetAttributeObjID(attributeID);
	GetObjectViewInfo(attributeID)->SetVisible(true);

	m_pScene->SetBackData(pSeismicObj, pCurrSection);
	m_pAxisWidget->SetDisplaySection(pCurrSection);
		
	auto pDV = dynamic_cast<CXSeismicDataVolume*>(pSeismicObj);
	if (pDV)
	{
		_InitVcrControl(pDV, dynamic_cast<CXSeismicSection*>(pCurrSection));
		m_pVcrContrl->ShowMe(true);
	}
	else
	{
		m_pVcrContrl->ShowMe(false);
	}

	// set colormap
	CXViewInfoObject* pAttrObjViewInfo = GetObjectViewInfo(attributeID);
	SetColormapName(pAttrObjViewInfo->GetColormapName());

	if (!m_pColormapWidget)
	{
		m_pColormapWidget = new CXColormapWidget(pAttrObjViewInfo->GetColormapName());
		m_pColormapDock->setWidget(m_pColormapWidget);
		connect(m_pColormapWidget, SIGNAL(OpenColormapEditingDialog()), this, SLOT(slotOpenColormapEditor()));
	}

	m_pColormapDock->setWindowTitle(pSeismicObj->GetObjectName());
	m_pColormapWidget->SetColormapName(pAttrObjViewInfo->GetColormapName());
	m_pColormapWidget->SetDisplayRange(pAttrObjViewInfo->GetDisplayDataMin(), pAttrObjViewInfo->GetDisplayDataMax());

	_ChangeScale(false);;
}

void CX2DSectionWindow::slotCurrentHorizonChanged(int iIdx)
{
	if (iIdx == 0)
	{
		m_pHTrackPara->setDisabled(true);
		m_pGroupHorizonTrack->setDisabled(true);
		m_pTrackingModeAction->setDisabled(true);
	}
	else
	{
		m_pHTrackPara->setEnabled(true);
		m_pGroupHorizonTrack->setEnabled(true);
		m_pTrackingModeAction->setEnabled(true);
	}

	m_pScene->SetActiveItem(m_pCbbHorizons->itemData(iIdx).toString());

	//	The active node should be check on the tree!
	SetObjectVisibility(QUuid(m_pCbbHorizons->itemData(iIdx).toString()), true);

	QList<QUuid> listObjID;
	listObjID << QUuid(m_pCbbHorizons->itemData(iIdx).toString());
	CXTree::Instance().ChangeTreeItemStatus(listObjID, true);

	m_pView->update();
	m_pScene->update();
}

void CX2DSectionWindow::slotSynVerticalAxis(int nValue)
{
	//	Is there section?
	if (!GetCurrentGeometryObj())
		return;

	if (nValue < 0)
		return;

	m_rectScene.moveTop(-nValue);
	m_pScene->blockSignals(true);
	m_pScene->setSceneRect(m_rectScene);
	m_pAxisWidget->repaint();
	m_pScene->blockSignals(false);

	// view port
	_UpdateROI();
	m_pScene->update();
}

void CX2DSectionWindow::slotSynHorizonAxis(int nValue)
{
	//	Is there section?
	if (!GetCurrentGeometryObj())
		return;


	if (nValue < 0)
		return;

	m_rectScene.moveLeft(-nValue);
	m_pScene->blockSignals(true);
	m_pScene->setSceneRect(m_rectScene);
	m_pAxisWidget->repaint();
	m_pScene->blockSignals(false);

	// view port
	_UpdateROI();
	m_pScene->update();

}

void CX2DSectionWindow::slotSetCurrentTrackingMode(QAction* a)
{
	m_pTrackingModeAction->setIcon(a->icon());
	m_pTrackingModeAction->setText(a->text());
	m_pTrackingModeAction->setToolTip(a->toolTip());
	m_pTrackingModeAction->setStatusTip(a->statusTip());
	int ndata = a->data().toInt();
	SetHorizonTrackMode(static_cast<EXHorizonTrackMode>(ndata));
}

void CX2DSectionWindow::slotSetHorizonDigitMode(QAction* pAction)
{
	int ndata = pAction->data().toInt();
	
	CXSecHorizonPickingItem *pHPickingItem = dynamic_cast<CXSecHorizonPickingItem *>(m_pScene->GetActiveItem());
	if (pHPickingItem)
	{
		pHPickingItem->SetHorizonPickingMode((ESecHorizonPickingMode) ndata);
	}
}

void CX2DSectionWindow::slotSetToolsDigitMode(QAction* pAction)
{
	QList<QAction*> listAct = m_ui.m_toolbarDigitizingAndForeground->actions();
	foreach(QAction *pAct, listAct)
	{
		pAction->blockSignals(true);
		if (pAct != pAction)
			pAct->setChecked(false);
		pAction->blockSignals(false);
	}
}

void CX2DSectionWindow::SetHorizonTrackMode(EXHorizonTrackMode eHorizonTrackMode)
{
	m_eHorizonTrackMode = eHorizonTrackMode;
}

void CX2DSectionWindow::SetHorizonSnapMode(EXHorizonSnapMode eHorizonSnapMode)
{
	m_eHorizonSnapMode = eHorizonSnapMode;
	QList<QAction*> listAct = m_pHorizonToolbar->actions();
	foreach(QAction *pAct, listAct)
	{
		if (eHorizonSnapMode == ENone)
		{
			if (pAct->data().toInt() == 0)
			{
				pAct->setEnabled(true);
			}
			else
			{
				pAct->setEnabled(false);
			}
		}
		else
		{
			pAct->setEnabled(true);
		}
	}
	m_pHorizonTrackPar->SetSnapType(int(eHorizonSnapMode));
}

QComboBox* CX2DSectionWindow::GetFaultComboBox()
{
	return m_pCbbFaults;
}

QComboBox* CX2DSectionWindow::GetHorizonComboBox()
{
	return m_pCbbHorizons;
}

EXSectionEditMode CX2DSectionWindow::GetEditMode()
{
	return m_eEditMode;
}

EXHorizonSnapMode CX2DSectionWindow::GetHorizonSnapMode()
{
	return m_eHorizonSnapMode;
}

EXHorizonTrackMode CX2DSectionWindow::GetHorizonTrackMode()
{
	return m_eHorizonTrackMode;
}

CXWindowInfoSection* CX2DSectionWindow::GetSecWindowViewInfo()
{
	return m_p2DWindowInfo;
}

CX2DSectionAxis* CX2DSectionWindow::GetAxisWidget()
{
	return m_pAxisWidget;
}

void CX2DSectionWindow::slotShowFaultTools()
{
	m_pScene->SetEditMode(Edit_NULL);
	m_pScene->DeactiveItem();

	QAction* pAct = dynamic_cast<QAction*>(sender());
	if (pAct->isChecked())
	{
		_initFaultCB();
		m_pFaultToolbar->setHidden(false);
		m_pHorizonToolbar->setHidden(true);
		m_p2ndLayerToolbar->setHidden(true);
	}
	else
	{
		m_pFaultToolbar->setHidden(true);
	}
}

void CX2DSectionWindow::slotShowHorizonTools()
{
	m_pScene->SetEditMode(Edit_NULL);
	m_pScene->DeactiveItem();

	QAction* pAct = dynamic_cast<QAction*>(sender());
	if (pAct->isChecked())
	{
		_initHorizonCB();
		m_pHorizonToolbar->setHidden(false);
		m_pFaultToolbar->setHidden(true);
		m_p2ndLayerToolbar->setHidden(true);
	}
	else
	{
		m_pHorizonToolbar->setHidden(true);
	}
}

void CX2DSectionWindow::slotShowOrthoSectionToos()
{
	if (m_ui.m_actionOrthoSections->isChecked())
		m_pScene->SetEditMode(Edit_OrthoSection);
	else
		m_pScene->SetEditMode(Edit_NULL);

	m_pScene->DeactiveItem();
	m_pScene->ShowOrthoSections(m_ui.m_actionOrthoSections->isChecked());
}

void CX2DSectionWindow::slotNewHorizon()
{
	CXObject *pGeoObj = m_pScene->GetBackgroundSection();
	if (!pGeoObj)
		return;

	CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey *>(pGeoObj->GetParent()->GetParent());
	if (!pSurvey)
		return;

	CXDlgNewObject* pNewObjDlg = new CXDlgNewObject(pSurvey, EX3DHorizon, this);
	pNewObjDlg->show();
}

CXSectionDigitizingItem* CX2DSectionWindow::GetDigitizingItem()
{
	return m_pDigitizingItem;
}

CXHorizonTrackPar* CX2DSectionWindow::GetHorizonTrackPar()
{
	return m_pHorizonTrackPar;
}

void CX2DSectionWindow::slotSectionValueChanged(double changedValue)
{
	CXSeismicSection* pSectionObject = dynamic_cast<CXSeismicSection *>(GetCurrentGeometryObj());
	if (pSectionObject)
	{
		CXProcessEvent processEvent;
		pSectionObject->SetSectionNumber(changedValue);
		pSectionObject->AddEvent(EDataChanged);

		_UpdateVolumeList(pSectionObject); // !会造成重新排序
	}
}

bool CX2DSectionWindow::_IsAttributeListChanged(CXObject *pObject)
{
	QList<CXObject*> listAttribute = _FetchAttributeList(pObject);

    if (listAttribute.size() != m_pCbbVolumes->count())
        return true;

    for (int i = 0; i != m_pCbbVolumes->count(); ++i)
    {
        QUuid currentID = m_pCbbVolumes->itemData(i).toUuid();
        if (currentID != listAttribute.at(i)->GetObjectID())
            return true;
    }

    return false;
}

void CX2DSectionWindow::_UpdateVolumeList(CXObject *pObject)
{
	if (!_IsAttributeListChanged(pObject))
        return;

	QList<CXObject*> listUpdatedAttributes = _FetchAttributeList(pObject);

	QUuid uuidCurrent2ndLayer = m_pCbb2ndLayer->currentData().toUuid();
	QUuid uuidCurrentVolume = m_pCbbVolumes->currentData().toUuid();

	if (!listUpdatedAttributes.contains(::GetObjectByID(uuidCurrentVolume)))
	{
		uuidCurrentVolume = _GetFirstPostStackID(listUpdatedAttributes);
	}

	if (!listUpdatedAttributes.contains(::GetObjectByID(uuidCurrent2ndLayer)))
	{
		uuidCurrent2ndLayer = QUuid();
	}

	m_pCbb2ndLayer->blockSignals(true);
	m_pCbbVolumes->blockSignals(true);

    m_pCbb2ndLayer->clear();
    m_pCbbVolumes->clear();

    m_pCbb2ndLayer->addItem(QIcon(GetIconPath() + "SeismicDataVolume.png"), "None", QUuid());

	for (CXObject* pObj : listUpdatedAttributes)
	{
		m_pCbb2ndLayer->addItem(QIcon(GetIconPath() + pObj->GetIconName()), pObj->GetObjectName(), pObj->GetObjectID());
		m_pCbbVolumes->addItem(QIcon(GetIconPath() + pObj->GetIconName()), pObj->GetObjectName(), pObj->GetObjectID());
	}

	m_pCbbVolumes->setCurrentIndex(m_pCbbVolumes->findData(uuidCurrentVolume));
	m_pCbb2ndLayer->setCurrentIndex(m_pCbb2ndLayer->findData(uuidCurrent2ndLayer));

	m_pCbb2ndLayer->blockSignals(false);
	m_pCbbVolumes->blockSignals(false);
}

QList<CXObject*> CX2DSectionWindow::_FetchAttributeList(CXObject *pGeoObj)
{
    QList<CXObject*> listAttribute;

	switch (pGeoObj->GetObjectType())
    {
    case EXSeismicSection:
    case EXRandomSection:
    {
		auto pSurvey = dynamic_cast<CX3DSurvey*>(pGeoObj->GetAncient(EX3DSurvey));
        Q_ASSERT(pSurvey);

        listAttribute = pSurvey->GetAllCandidates(pGeoObj);
        Q_ASSERT(!listAttribute.isEmpty());

        break;
    }
    case EX2DSeismicLine:
    {
		listAttribute = pGeoObj->GetChildren(EXSeismicDataLine);
        Q_ASSERT(!listAttribute.isEmpty());

        break;
    }
    default:
        Q_ASSERT(!"cannot find this seismic type.");
    }

    return listAttribute;
}

void CX2DSectionWindow::UpdateColormap()
{
    CXViewInfoObject *pViewInfo = GetObjectViewInfo(m_pScene->GetBackgroundSection(false)->GetObjectID());
	SetColormapName(pViewInfo->GetColormapName());
    m_pColormapWidget->SetColormapName(pViewInfo->GetColormapName());
}

void CX2DSectionWindow::UpdateColormapWidgetRange(double dMin, double dMax)
{
    m_pColormapWidget->SetDisplayRange(dMin, dMax);
}

void CX2DSectionWindow::UpdateVCRControlData(QUuid changedObjID)
{
	CXSeismicSection *pSection = dynamic_cast<CXSeismicSection *>(GetCurrentGeometryObj());
	if (!pSection || pSection->GetObjectID() != changedObjID)
        return;

	m_pVcrContrl->SetSliderSpinValue(pSection->GetSectionNumber());
    m_pAxisWidget->update();
}

void CX2DSectionWindow::AddNewItemToComboBox(QUuid newObjID)
{
    CXObject* pObject = ::GetObjectByID(newObjID);
    if (!pObject)
        return;

    QString strObjName = pObject->GetObjectName();

    switch (pObject->GetObjectType())
    {
    case EXFaultSticks:
    {
        m_pCbbFaults->addItem(QIcon(GetIconPath() + pObject->GetIconName()), strObjName, pObject->GetObjectID().toString());
        m_pCbbFaults->setCurrentIndex(m_pCbbFaults->findText(strObjName));

		m_pCbb2ndFaults->addItem(QIcon(GetIconPath() + pObject->GetIconName()), strObjName, pObject->GetObjectID().toString());
		if (m_pCbb2ndFaults->count() > 1)
		{
			m_pCbb2ndFaults->setDisabled(false);
			m_pFaultAssign->setDisabled(false);
		}
		break;
    }
    case EX3DHorizon:
    {
		m_pCbbHorizons->blockSignals(true);

	    m_pCbbHorizons->addItem(QIcon(GetIconPath() + pObject->GetIconName()), strObjName, pObject->GetObjectID().toString());
        m_pCbbHorizons->setCurrentIndex(m_pCbbHorizons->findText(strObjName));
		
		m_pCbbHorizons->blockSignals(false);

        break;
    }
    case EXSeismicDataVolume:
	case EXSeismicDataLine:
    {
		CXObject *pSection = m_pScene->GetBackgroundSection();
		if (!pSection)
			return;
		
		_UpdateVolumeList(pSection);

        break;
    }
    case EX3TermAVOInversionFolder:
	case EXFractureInversionFolder:
	case EXAnisotropyForwardingFolder:
    {
		QList<QUuid> listExistedDV;
		for (int i = 0; i != m_pCbbVolumes->count(); ++i)
		{
			listExistedDV << m_pCbbVolumes->itemData(i).toUuid();
		}

		m_pCbbVolumes->blockSignals(true);
		m_pCbb2ndLayer->blockSignals(true);

		for (CXObject *pObj : pObject->GetChildren(EXSeismicDataVolume, true))
		{
			if (listExistedDV.contains(pObj->GetObjectID()))
				continue;

			m_pCbb2ndLayer->addItem(QIcon(GetIconPath() + pObj->GetIconName()), pObj->GetObjectName(), pObj->GetObjectID());
			m_pCbbVolumes->addItem(QIcon(GetIconPath() + pObj->GetIconName()), pObj->GetObjectName(), pObj->GetObjectID());
		}

		m_pCbbVolumes->blockSignals(false);
		m_pCbb2ndLayer->blockSignals(false);

		break;
    }
    }
}

void CX2DSectionWindow::RemoveItemFromComboBox(QUuid deleteObjID)
{
    CXObject* pObject = ::GetObjectByID(deleteObjID);
    Q_ASSERT(pObject);

    QString strObjName = pObject->GetObjectName();

    switch (pObject->GetObjectType())
    {
    case EXFaultSticks:
		m_pCbbFaults->removeItem(m_pCbbFaults->findText(strObjName));

		m_pCbb2ndFaults->removeItem(m_pCbbFaults->findText(strObjName));
		if (m_pCbb2ndFaults->count() < 2)
		{
			m_pCbb2ndFaults->setDisabled(true);
			m_pFaultAssign->setDisabled(true);
		}
		break;
    case EX3DHorizon:
        m_pCbbHorizons->removeItem(m_pCbbHorizons->findText(strObjName));
        break;
    case EXSeismicDataVolume:
	case EXSeismicDataLine:
        m_pCbb2ndLayer->removeItem(m_pCbb2ndLayer->findText(strObjName));
        m_pCbbVolumes->removeItem(m_pCbbVolumes->findText(strObjName));
        break;
    }
}

void CX2DSectionWindow::SetCurrentAttribute(QUuid attributeID)
{
    int index = m_pCbbVolumes->findText(::GetObjectByID(attributeID)->GetObjectName());
    m_pCbbVolumes->setCurrentIndex(index);
}

QUuid CX2DSectionWindow::GetCurrentAttributeID()
{
	return m_pCbbVolumes->currentData().toUuid();
}

void CX2DSectionWindow::_InitVcrControl(CXSeismicDataVolume* pDV, CXSeismicSection *pSection)
{
	if (!pSection || !pDV)
		return;

	CXSeismicUTMTool& utmTool = pDV->GetUTM();
	double sampleStart = 0.0f, sampleEnd = 0.0f, sampleInterval = 0.0f;
	pDV->GetSamplingRange(sampleStart, sampleEnd, sampleInterval);

	switch (pSection->GetSectionType())
	{
	case eInlineSection:
		m_pVcrContrl->InitData(utmTool.GetFirstInline(), utmTool.GetLastInline(), pSection->GetSectionNumber(), utmTool.GetInlineIncrement(), utmTool.GetInlineIncrement(), -1);
		break;
	case eCrosslineSection:
		m_pVcrContrl->InitData(utmTool.GetFirstCrossline(), utmTool.GetLastCrossline(), pSection->GetSectionNumber(), utmTool.GetCrosslineIncrement(), utmTool.GetCrosslineIncrement(), -1);
		break;
	case eTimeSlice:
		m_pVcrContrl->InitData(sampleStart, sampleEnd, pSection->GetSectionNumber(), sampleInterval, sampleInterval, -1);
		break;
	default:
		CXLog::AddLog("[SectionWindow: InitVcrControl] Error section type.");
	}
}

CXObject* CX2DSectionWindow::GetCurrentGeometryObj()
{
	return m_pScene->GetBackgroundSection();
}

void CX2DSectionWindow::slotChangedForeAlpha(double currValue)
{
	m_p2DWindowInfo->SetForeAlpha(currValue);
	m_pScene->update();
}

void CX2DSectionWindow::slotOpenColormapEditor()
{
	CXDlgProperty *pDlg = CXPropertyDialogFactory::Instance().CreatePropertyDialog(m_pScene->GetBackgroundSection(false));
    pDlg->ShowColormapPage();
    pDlg->show();
}

void CX2DSectionWindow::slotChangedColormap(const QString& colormapName)
{
	CXObject* pAttributeObj = m_pScene->GetBackgroundSection(false);
	if (!pAttributeObj) 
		return;

    CXViewInfoObject* pAttributeViewInfo = GetObjectViewInfo(pAttributeObj->GetObjectID());
    Q_ASSERT(pAttributeViewInfo);
    pAttributeViewInfo->SetColormapName(colormapName);
    m_pColormapWidget->SetColormapName(colormapName);
	
	CXProcessEvent processEvent;
	pAttributeObj->AddEvent(EColormapChanged);
}

void CX2DSectionWindow::slotChangedForeColormap(const QString& colormapName)
{
	CXObject* pCurrSection = GetCurrentGeometryObj();
	if (!pCurrSection) 
		return;

	QUuid attribute2rdID = m_pCbb2ndLayer->currentData().toUuid();
	CXObject *pAttributeObj = ::GetObjectByID(attribute2rdID);
	if (!pAttributeObj)
		return;

	CXViewInfoObject* pAttributeViewInfo = GetObjectViewInfo(pAttributeObj->GetObjectID());
	Q_ASSERT(pAttributeViewInfo);
	pAttributeViewInfo->SetColormapName(colormapName);

	CXProcessEvent processEvent;
	pAttributeObj->AddEvent(EColormapChanged);
}

void CX2DSectionWindow::ChangeDisplayParameter()
{
	_ChangeScale(true);
	update();
}

void CX2DSectionWindow::UpdateVolumesName(const QUuid& volumesID)
{
	int foundIndex = m_pCbbVolumes->findData(volumesID);
	if (foundIndex == -1)
		return;

	m_pCbb2ndLayer->blockSignals(true);
	m_pCbbVolumes->blockSignals(true);

	m_pCbb2ndLayer->setItemText(foundIndex, ::GetObjectByID(volumesID)->GetObjectName());
	m_pCbbVolumes->setItemText(foundIndex, ::GetObjectByID(volumesID)->GetObjectName());

	m_pCbb2ndLayer->blockSignals(false);
	m_pCbbVolumes->blockSignals(false);

	m_pCbb2ndLayer->update();
	m_pCbbVolumes->update();
}

void CX2DSectionWindow::slotRectZoom()
{
	if (sender() == m_ui.actionRectZoom)
		m_pScene->SwitchRectZoom(m_ui.actionRectZoom->isChecked());

	else if (sender() == m_ui.actionRectZoomUndo)
	{
		_undoRectZoomIn(false);
	}
	else if (sender() == m_ui.actionCancelZoomin)
	{
		_undoRectZoomIn(true);
	}
}

void CX2DSectionWindow::RectZoomIn(QRectF rect)
{
	m_ui.actionRectZoom->setChecked(false);
	m_pScene->SwitchRectZoom(false);

	// save current status
	QRect rectWidget = m_pView->rect();
	int nWidth = rectWidget.width() - m_pView->verticalScrollBar()->width();
	int nHeight = rectWidget.height() - m_pView->horizontalScrollBar()->height();

	double scenex1, sceney1, scenex2, sceney2;
	double ratiox1, ratioy1, ratiox2, ratioy2;
	CXCoordTransformer transformer(m_pScene);
	transformer.View2Scene(0, 0, scenex1, sceney1);
	transformer.View2Scene(nWidth, nHeight, scenex2, sceney2);
	transformer.Scene2Ratio(scenex1, sceney1, ratiox1, ratioy1);
	transformer.Scene2Ratio(scenex2, sceney2, ratiox2, ratioy2);
		
	SKERectZoomInfo zoomInfo(m_pScene->GetBackgroundSection()->GetObjectID(),
		m_p2DWindowInfo->GetTraceScale(), m_p2DWindowInfo->GetVerScale(), (ratiox1+ ratiox2)/2, (ratiox2 + ratiox2) / 2);
	// max 50 stacks
	if (m_vecRectZoomInfo.size() == 50)
	{
		m_vecRectZoomInfo.takeFirst();		
	}
	m_vecRectZoomInfo.push_back(zoomInfo);

	// set scale
	qreal fHScale = rect.width() / (ratiox2- ratiox1);
	qreal fVScale = rect.height() / (ratioy2 - ratioy1);
	m_p2DWindowInfo->SetTraceScale(m_p2DWindowInfo->GetTraceScale() * fHScale);
	m_p2DWindowInfo->SetVerScale(m_p2DWindowInfo->GetVerScale() * fVScale);

	// update
	_ChangeScale(true, rect.x() + rect.width() / 2, rect.y() + rect.height() / 2);

	//Enable the other 2 actions.
	m_ui.actionCancelZoomin->setEnabled(true);
	m_ui.actionRectZoomUndo->setEnabled(true);
}

void CX2DSectionWindow::_undoRectZoomIn(bool bAll)
{
	if (m_vecRectZoomInfo.isEmpty())
	{
		m_ui.actionCancelZoomin->setDisabled(true);
		m_ui.actionRectZoomUndo->setDisabled(true);
		return;
	}

	SKERectZoomInfo zoomInfo;
	if (bAll)
	{
		zoomInfo = m_vecRectZoomInfo.takeFirst();	
		m_vecRectZoomInfo.clear();
	}
	else
	{
		zoomInfo = m_vecRectZoomInfo.takeLast();
	}

	if (m_vecRectZoomInfo.isEmpty())
	{
		m_ui.actionCancelZoomin->setDisabled(true);
		m_ui.actionRectZoomUndo->setDisabled(true);
	}

	double dHorCenterRatio(-1), dVerCenterRatio(-1);
	if (zoomInfo.m_sectionID == m_pScene->GetBackgroundSection()->GetObjectID())
	{
		dHorCenterRatio = zoomInfo.m_dXCentorRatio;
		dVerCenterRatio = zoomInfo.m_dYCentorRatio;
	}

	m_p2DWindowInfo->SetTraceScale(zoomInfo.m_fHScale);
	m_p2DWindowInfo->SetVerScale(zoomInfo.m_fVScale);	

	// update
	_ChangeScale(true, dHorCenterRatio, dVerCenterRatio);
}

void CX2DSectionWindow::slotZoom()
{
	//	Is there section?
	if (m_pScene->GetBackgroundSection() == NULL)
		return;

	QAction* pAction = dynamic_cast<QAction*>(sender());
	if (!pAction)
		return;

	bool bChangeData = false;

	if (pAction == m_ui.m_actionZoomIn)
	{
		m_p2DWindowInfo->SetTraceScale(0.94f*m_p2DWindowInfo->GetTraceScale());
		m_p2DWindowInfo->SetVerScale(0.94f*m_p2DWindowInfo->GetVerScale());
	}
	else if (pAction == m_ui.m_actionZoomOut)
	{
		m_p2DWindowInfo->SetTraceScale(1.04f*m_p2DWindowInfo->GetTraceScale());
		m_p2DWindowInfo->SetVerScale(1.06f*m_p2DWindowInfo->GetVerScale());
	}
	else if (pAction == m_ui.m_actionIncreaseHorizonScale)
	{
		m_p2DWindowInfo->SetTraceScale(0.94f*m_p2DWindowInfo->GetTraceScale());
	}
	else if (pAction == m_ui.m_actionDecreaseHorizonScale)
	{
		m_p2DWindowInfo->SetTraceScale(1.04f*m_p2DWindowInfo->GetTraceScale());
	}
	else if (pAction == m_ui.m_actionIncreaseVerticalScale)
	{
		m_p2DWindowInfo->SetVerScale(0.94f*m_p2DWindowInfo->GetVerScale());
	}
	else if (pAction == m_ui.m_actionDecreaseVerticalScale)
	{
		m_p2DWindowInfo->SetVerScale(1.06f*m_p2DWindowInfo->GetVerScale());
	}
	else if (pAction == m_ui.m_actionIncreaseExcursion)
	{
		m_p2DWindowInfo->SetExcursion(1.1f*m_p2DWindowInfo->GetExcursion());
		bChangeData = true;
	}
	else if (pAction == m_ui.m_actionDecreaseExcursion)
	{
		m_p2DWindowInfo->SetExcursion(0.9f*m_p2DWindowInfo->GetExcursion());
		bChangeData = true;
	}
	else if (pAction == m_ui.m_actionFitToWindowWidth)
	{
		int nWidth = m_pView->rect().width() - m_pView->verticalScrollBar()->width();
		int nHeight = m_rectScene.toRect().height();
		NXViewUtility::SetViewInfoFromSize(m_p2DWindowInfo, m_pScene, nWidth, nHeight);

		m_rectScene.setX(0);
		m_pView->horizontalScrollBar()->setRange(0, 0);
	}
	else if (pAction == m_ui.m_actionFitToWindowHeight)
	{
		int nWidth = m_rectScene.toRect().width();
		int nHeight = m_pView->rect().height() - m_pView->horizontalScrollBar()->height();
		NXViewUtility::SetViewInfoFromSize(m_p2DWindowInfo, m_pScene, nWidth, nHeight);

		m_rectScene.setY(0);
		m_pView->verticalScrollBar()->setRange(0, 0);
	}
	else if (pAction == m_ui.m_actionViewAll)
	{
		int nWidth = m_pView->rect().width() - m_pView->verticalScrollBar()->width();
		int nHeight = m_pView->rect().height() - m_pView->horizontalScrollBar()->height();
		NXViewUtility::SetViewInfoFromSize(m_p2DWindowInfo, m_pScene, nWidth, nHeight);

		m_rectScene.setX(0);
		m_rectScene.setY(0);
		m_pView->horizontalScrollBar()->setRange(0, 0);
		m_pView->verticalScrollBar()->setRange(0, 0);
	}
	else
	{
		return;
	}

	_ChangeScale(bChangeData);

}

void CX2DSectionWindow::_ChangeScale(bool bChangeData, double dHorCenterRatio, double dVerCenterRatio)
{
	if (bChangeData)
		m_pScene->UpdateSectionData();

	double dWidth, dHeight;
	NXViewUtility::GetSizeFromViewInfo(m_p2DWindowInfo, m_pScene, dWidth, dHeight);

	// rect
	QRectF rect(m_rectScene.toRect().x(), m_rectScene.toRect().y(), dWidth, dHeight);
	SetSceneRect(rect, true, dHorCenterRatio, dVerCenterRatio);

	m_pScene->UpdateItems(EInfoChanged);
}

void CX2DSectionWindow::slotVaribleIntensity()
{
	QAction* pAct = dynamic_cast<QAction*>(sender());
	m_p2DWindowInfo->SetVariableIntensity(pAct->isChecked());
	m_pScene->update();
}

void CX2DSectionWindow::slotWiggle()
{
	QAction* pAct = dynamic_cast<QAction*>(sender());
	m_p2DWindowInfo->SetWiggle(pAct->isChecked());
	m_pScene->update();
}

void CX2DSectionWindow::slotWiggleArea()
{
	QAction* pAct = dynamic_cast<QAction*>(sender());
	m_p2DWindowInfo->SetWiggleVariableArea(pAct->isChecked());
	m_pScene->update();
}

void CX2DSectionWindow::slotForeVaribleIntensity()
{
	QAction* pAct = dynamic_cast<QAction*>(sender());
	m_p2DWindowInfo->SetForeVariableIntensity(pAct->isChecked());
	m_p2ndWiggleGroup->actions().back()->setVisible(pAct->isChecked());
	m_pScene->update();
}

void CX2DSectionWindow::slotForeWiggle()
{
	QAction* pAct = dynamic_cast<QAction*>(sender());
	m_p2DWindowInfo->SetForeWiggle(pAct->isChecked());
	m_pScene->update();
}

void CX2DSectionWindow::slotForeWiggleArea()
{
	QAction* pAct = dynamic_cast<QAction*>(sender());
	m_p2DWindowInfo->SetForeWiggleVariableArea(pAct->isChecked());
	m_pScene->update();
}

CXScene* CX2DSectionWindow::GetScene()
{
	return m_pScene;
}

const QRectF& CX2DSectionWindow::GetSceneRect()
{
	return m_rectScene;
}

CX2DSectionView* CX2DSectionWindow::GetView()
{
	return dynamic_cast<CX2DSectionView*>(m_pView);
}

void CX2DSectionWindow::SetSceneRect(const QRectF& rect, bool bChangeScale, double dHorCenterRatio, double dVerCenterRatio)
{
	m_rectScene = rect;
	m_pScene->blockSignals(true);
	m_pScene->setSceneRect(m_rectScene);
	m_pAxisWidget->repaint();
	m_pScene->blockSignals(false);

	// view port
	_SetScrollbarPosition(bChangeScale, dHorCenterRatio, dVerCenterRatio);
	_UpdateROI();

	// scene
	m_pScene->update();
}

void CX2DSectionWindow::_SetScrollbarPosition(bool bChangeScale, double dHorCenterRatio, double dVerCenterRatio)
{
	QRect rectWidget = m_pView->rect();
	int nWidth = rectWidget.width() - m_pView->verticalScrollBar()->width();
	int nHeight = rectWidget.height() - m_pView->horizontalScrollBar()->height();

	int nHorPos = m_pView->horizontalScrollBar()->value();
	int nVerPos = m_pView->verticalScrollBar()->value();

	// change scale	
	if (bChangeScale && dHorCenterRatio == -1)
	{
		double dHorMin = m_pView->horizontalScrollBar()->minimum();
		double dHorMax = m_pView->horizontalScrollBar()->maximum();
		if (dHorMin != dHorMax)
		{
			dHorCenterRatio = (nHorPos + 0.5*nWidth) / (nWidth + dHorMax - dHorMin);
		}

		double dVerMin = m_pView->verticalScrollBar()->minimum();
		double dVerMax = m_pView->verticalScrollBar()->maximum();
		if (dVerMin != dVerMax)
		{
			dVerCenterRatio = (nVerPos + 0.5*nHeight) / (nHeight + dVerMax - dVerMin);
		}
	}

	int nMaxValue = qMax(0, m_rectScene.toRect().width() - nWidth);
	m_pView->horizontalScrollBar()->setRange(0, nMaxValue);
	m_pView->horizontalScrollBar()->setPageStep(m_rectScene.toRect().width() - nMaxValue);

	if (bChangeScale)
	{
		nHorPos = static_cast<int>(dHorCenterRatio*m_rectScene.toRect().width() - 0.5*nWidth);
		nHorPos = qBound(0, nHorPos, nMaxValue);
	}
	else
	{
		nHorPos = qMin(nHorPos, nMaxValue);
	}
	m_pView->horizontalScrollBar()->setValue(nHorPos);


	nMaxValue = qMax(0, m_rectScene.toRect().height() - nHeight);
	m_pView->verticalScrollBar()->setRange(0, nMaxValue);
	m_pView->verticalScrollBar()->setPageStep(m_rectScene.toRect().height() - nMaxValue);

	if (bChangeScale)
	{
		nVerPos = static_cast<int>(dVerCenterRatio*m_rectScene.toRect().height() - 0.5*nHeight);
		nVerPos = qBound(0, nVerPos, nMaxValue);
	}
	else
	{
		nVerPos = qMin(nVerPos, nMaxValue);
	}
	m_pView->verticalScrollBar()->setValue(nVerPos);
}

void CX2DSectionWindow::_UpdateROI()
{
	// possible view rect
	QRect rectWidget = m_pView->rect();
	int nWidth = rectWidget.width() - m_pView->verticalScrollBar()->width();
	int nHeight = rectWidget.height() - m_pView->horizontalScrollBar()->height();

	// scrollbar
	int nHorPos = m_pView->horizontalScrollBar()->value();
	int nVerPos = m_pView->verticalScrollBar()->value();

	QRect rectView;
	rectView.setX(nHorPos + m_rectScene.toRect().x());
	rectView.setY(nVerPos + m_rectScene.toRect().y());
	rectView.setWidth(qMin(m_rectScene.toRect().width() - nHorPos, nWidth));
	rectView.setHeight(qMin(m_rectScene.toRect().height() - nVerPos, nHeight));

	float fLeft = 2.*(rectView.left() - m_rectScene.left()) / m_rectScene.width() - 1.;
	float fRight = 2.*(rectView.right() - m_rectScene.left()) / m_rectScene.width() - 1.;

	float fBottom = 1. - 2.*(rectView.bottom() - m_rectScene.top()) / m_rectScene.height();
	float fTop = 1. - 2.*(rectView.top() - m_rectScene.top()) / m_rectScene.height();

	m_pScene->UpdateROI(fLeft, fRight, fBottom, fTop);
	m_pView->viewport()->setFixedSize(rectView.width(), rectView.height());
	m_pView->viewport()->update();
}

void CX2DSectionWindow::resizeEvent(QResizeEvent* event)
{
	if (!GetCurrentGeometryObj())
        return;

	_SetScrollbarPosition(false);
	_UpdateROI();

	m_pScene->update();
}

void CX2DSectionWindow::GetScollbarDimension(int& width, int& height)
{
	width = m_pView->verticalScrollBar()->width();
	height = m_pView->horizontalScrollBar()->height();
}

void CX2DSectionWindow::ChangeViewerSize()
{
	_SetScrollbarPosition(false);
}

void CX2DSectionWindow::slotWindowProperties()
{
	CXSecWindowProperties* pDlg = new CXSecWindowProperties(this, m_p2DWindowInfo);
	pDlg->show();
}

void CX2DSectionWindow::slotNewFault()
{
	CXObject *pGeoObj = m_pScene->GetBackgroundSection();
	if (!pGeoObj)
		return;

	CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey *>(pGeoObj->GetParent()->GetParent());
	if (!pSurvey)
		return;

	CXDlgNewObject* pNewObjDlg = new CXDlgNewObject(pSurvey, EXFaultSticks, this);
	pNewObjDlg->show();
}

void CX2DSectionWindow::slotAssignFaultStick()
{
	QUuid sourceFaultID = m_pCbbFaults->currentData().toString();
	QUuid destFaultID = m_pCbb2ndFaults->currentData().toString();

	//	The same, do nothing.
	if (sourceFaultID == destFaultID || sourceFaultID.isNull() || destFaultID.isNull())
		return;

	//	Let the scene do the other work.
	m_pScene->FaultStickAssign(sourceFaultID, destFaultID);

	//	If the dest fault not visible now, show it!
	QList<QUuid> listObjID;
	listObjID << destFaultID;
	CXTree::Instance().ChangeTreeItemStatus(listObjID, true);
	SetObjectVisibility(destFaultID, true);
}

void CX2DSectionWindow::slotTrackPara()
{
	//int iIdx = m_pCbbHorizons->currentIndex();
	//QUuid uid(m_pCbbHorizons->itemData(iIdx).toString());
	//CX3DHorizon* pHorizons = dynamic_cast<CX3DHorizon*>(GetObjectByID(uid));
	//CXPageHorizonTrackPara pDlg(this, pHorizons, m_pOrthoProjector->GetCurrentSection());
	//pDlg.SetTrackPara(m_pHorizonTrackPar);
	//pDlg.exec();

	CXDlgHorizonTrackPara* pTrackParaDlg = new CXDlgHorizonTrackPara(this);
	pTrackParaDlg->show();
}

bool CX2DSectionWindow::IsSection(const QUuid& objID)
{
    // Exactly, section is the background geometry of section window. It can lead to axes' change.

    CXObject* pKEObj = ::GetObjectByID(objID);

    if (!pKEObj)
        return false;

    QList<EXObjectType> listSectionType{EXRandomSection, EX2DSeismicLine};
    if (listSectionType.contains(pKEObj->GetObjectType()))
        return true;
  
	if (pKEObj->GetObjectType() == EXSeismicSection)
	{
		CXSeismicSection* pSection = dynamic_cast<CXSeismicSection*>(pKEObj);
		if (pSection &&
			(pSection->GetSectionType() == eInlineSection ||
				pSection->GetSectionType() == eCrosslineSection ||
				pSection->GetSectionType() == eInlineProfile))
			return true;
	}

	return false;
	
}
