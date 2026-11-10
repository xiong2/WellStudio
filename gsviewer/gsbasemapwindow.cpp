#include "stdafx.h"
#include <QFileDialog>
#include <QGLWidget>
#include <QDebug>

#include "xcolormap.h"
#include "xeventconsole.h"
#include "xglobal.h"
#include "xobject.h"
#include "xtree.h"

#include "gsbasemapwindow.h"
#include "x3dsurvey.h"
#include "x3dhorizon.h"
#include "gsstressmap.h"

#include "xviewinfoobject.h"
#include "gs3dhorizonviewinfo.h"
#include "gsstressmapviewinfo.h"
#include "gssectionviewinfo.h"
#include "gsrosediagramviewinfo.h"

#include "gsbm3dhorizonvispage.h"
#include "gsbmsectionvispage.h"
#include "gsbmstressmapvispage.h"
#include "gsbmrosediagramvispage.h"
#include "gsdlgrosediagram.h"

#include "gsbmstressmapitem.h"
#include "gsbm3dhorizonitem.h"
#include "gsbmitemdef.h"
#include "gsbmsectionitem.h"
#include "gsbmpdgitem.h"
#include "gsbmwellitem.h"
#include "gsbmitemdefinerose.h"
#include "gsbmitemrosediagram.h"

CGSBasemapWindow::CGSBasemapWindow(QString strWindowName, QWidget* parent)
	: CXWindow(strWindowName, parent), m_scene(m_coordTransform), m_coordItem(m_coordTransform), m_cursorItem(m_coordTransform)
{
	ui.setupUi(this);
	ui.graphicsView->setScene(&m_scene);
	setAttribute(Qt::WA_DeleteOnClose);
	setMinimumSize(800, 600);

	m_scene.addItem(&m_coordItem);
	m_scene.addItem(&m_cursorItem);

	connect(&m_scene, &GSBasemapScene::AddThisObjToTree, [this](const QUuid& objID)
	{
		CXTree::Instance().AddOneObject(GetObjectByID(objID));
	});

	connect(&m_scene, &GSBasemapScene::ShowThisObj, [this](const QUuid& objID)
	{
		SetObjectVisibility(objID, true);
		QList<QUuid> listID;
		listID << objID;
		CXTree::Instance().UpdateTreeStatus(listID, eGSBaseMap);
	});

	connect(ui.graphicsView, &GSBasemapView::ShowPositionInfo, [this](const QPoint& pos, QGraphicsItem* pItem)
	{
		if (!m_coordTransform.IsInitialized())
			return;

		QPointF scenePos = ui.graphicsView->mapToScene(pos);
		const QPointF& worldCoordinate = m_coordTransform.Local2World(scenePos);

		m_cursorItem.Clear();
		m_scene.update();
		//BroadcastPosition(worldCoordinate.x(), worldCoordinate.y(), 0.0);

		if (pItem)
		{
			auto pHorizonItem = dynamic_cast<GSBM3DHorizonItem*>(pItem);
			if (pHorizonItem)
			{
				double dAttribute = pHorizonItem->ValueAt(worldCoordinate);
				ui.statusBar->showMessage(QString("%1, %2, %3").arg(worldCoordinate.x(), 0, 'f', 0).arg(worldCoordinate.y(), 0, 'f', 0).arg(dAttribute, 0, 'f', 2));
				return;
			}

			auto pStressmapItem = dynamic_cast<GSBMStressMapItem*>(pItem);
			if (pStressmapItem)
			{
				double dMag = pStressmapItem->GetMag(worldCoordinate);
				double dAng = pStressmapItem->GetAng(worldCoordinate);
				ui.statusBar->showMessage(QString("%1, %2, %3, %4").arg(worldCoordinate.x(), 0, 'f', 0).arg(worldCoordinate.y(), 0, 'f', 0)
										  .arg(dMag, 0, 'f', 3).arg(dAng, 0, 'f', 2));
				return;
			}
		}

		ui.statusBar->showMessage(QString("%1, %2").arg(worldCoordinate.x(), 0, 'f', 0).arg(worldCoordinate.y(), 0, 'f', 0));
	});

	connect(ui.actionZoom_Reset, &QAction::triggered, [this]()
	{
		ui.graphicsView->fitInView(m_coordItem.boundingRect(), Qt::KeepAspectRatio);
	});

	connect(ui.actionZoom_to_height, &QAction::triggered, [this]()
	{
		QRectF currentRect = ui.graphicsView->rect();
		currentRect.setHeight(m_coordItem.boundingRect().height());
		ui.graphicsView->fitInView(currentRect, Qt::KeepAspectRatio);
	});

	connect(ui.actionZoom_to_width, &QAction::triggered, [this]()
	{
		QRectF currentRect = ui.graphicsView->rect();
		currentRect.setWidth(m_coordItem.boundingRect().width());
		ui.graphicsView->fitInView(currentRect, Qt::KeepAspectRatio);
	});

	connect(ui.actionZoom_In, &QAction::triggered, [this]()
	{
		ui.graphicsView->scale(1.2, 1.2);
	});

	connect(ui.actionZoom_Out, &QAction::triggered, [this]()
	{
		ui.graphicsView->scale(1 / 1.2, 1 / 1.2);
	});

	connect(ui.actionZoom_By_Rect, &QAction::triggered, [this](bool isChecked)
	{
		m_scene.SetMode(isChecked ? GSBasemapScene::eZoomByRect : GSBasemapScene::eNone);
	});

	connect(&m_scene, &GSBasemapScene::EnableZoomUndo, ui.actionZoom_Undo, &QAction::setEnabled);
	connect(ui.actionZoom_Undo, &QAction::triggered, &m_scene, &GSBasemapScene::UndoLastZoom);

	connect(ui.actionNewSection, &QAction::triggered, [this](bool isChecked)
	{
		m_scene.SetMode(isChecked ? GSBasemapScene::eCreateSection : GSBasemapScene::eNone);
	});

	connect(ui.actionNewPDG, &QAction::triggered, [this](bool isChecked)
	{
		m_scene.SetMode(isChecked ? GSBasemapScene::eCreatePDG : GSBasemapScene::eNone);
	});

	connect(ui.actionNewRoseDiagram, &QAction::triggered, this, &CGSBasemapWindow::slotCreateRoseDialog);

	m_itemFactory.Registered({ EXGS3DHorizonTWT, EXGS3DHorizonDepth, EXGS3DHorizonIso, EXGS3DHorizonAtt }, [this](CXObject* pObj)
	{
		auto pViewInfo = dynamic_cast<GS3DHorizonViewInfo*>(GetObjectViewInfo(pObj->GetObjectID()));
		return new GSBM3DHorizonItem(pObj, m_coordTransform, pViewInfo);
	});

	m_itemFactory.Registered(EXGSStressMap, [this](CXObject* pObj)
	{
		auto pViewInfo = dynamic_cast<GSStressMapViewInfo*>(GetObjectViewInfo(pObj->GetObjectID()));
		return new GSBMStressMapItem(pObj, m_coordTransform, pViewInfo);
	});

	m_itemFactory.Registered(EXGSSection, [this](CXObject* pObj)
	{
		auto pViewInfo = dynamic_cast<GSSectionViewInfo*>(GetObjectViewInfo(pObj->GetObjectID()));
		return new GSBMSectionItem(pObj, m_coordTransform, pViewInfo);
	});

	m_itemFactory.Registered(EXGSPDG, [this](CXObject* pObj)
	{
		auto pViewInfo = dynamic_cast<GSSectionViewInfo*>(GetObjectViewInfo(pObj->GetObjectID()));
		return new GSBMPDGItem(pObj, m_coordTransform, pViewInfo);
	});

	m_itemFactory.Registered(EXWell, [this](CXObject* pObj)
	{
		auto pViewInfo = dynamic_cast<GSSectionViewInfo*>(GetObjectViewInfo(pObj->GetObjectID()));
		return new GSBMWellItem(pObj, m_coordTransform, pViewInfo);
	});

	m_itemFactory.Registered(EXGSRoseDiagram, [this](CXObject* pObj)
	{
		auto pViewInfo = dynamic_cast<GSRoseDiagramViewInfo*>(GetObjectViewInfo(pObj->GetObjectID()));
		return new GSBMItemRoseDiagram(pObj, m_coordTransform, pViewInfo);
	});
}

CGSBasemapWindow::~CGSBasemapWindow()
{
}

void CGSBasemapWindow::slotCreateRoseDialog()
{
	GSStressMap *pMap = NULL;
	for (auto iter = m_mapObjViewInfo.cbegin(); iter != m_mapObjViewInfo.cend(); ++iter)
	{
		if (!iter.value()->GetVisible())
			continue;

		CXObject* pObj = GetObjectByID(iter.key());
		pMap = dynamic_cast<GSStressMap *>(pObj);
		if(pMap)
			break;
	}

	if (!pMap)
	{
		qDebug()<<"Something error!";
		return;
	}

	m_scene.SetMode(GSBasemapScene::eCreateRoseDiagram);
	GSBMItemDefineRose *pItem = m_scene.CreateDefineRoseItem(pMap->GetUTM().GetIInterval() * 10);

	gsdlgrosediagram  *pDlg = new gsdlgrosediagram(pMap, pItem);
	pDlg->setWindowFlag(Qt::WindowStaysOnTopHint, true);
	pDlg->show();
}

void CGSBasemapWindow::UpdateView(const CXEventParameter& eventPara)
{
	if (eventPara.m_eEventType == EInfoChanged)
	{
		auto itemList = m_scene.items();
		auto foundItem = std::find_if(itemList.begin(), itemList.end(), [eventPara](QGraphicsItem* pItem) {
			return pItem->data(NGSBMItem::eObjectID).toUuid() == eventPara.m_objID;
		});
		if (foundItem != itemList.end())
			(*foundItem)->setData(NGSBMItem::eIsViewInfoChanged, true);

		m_scene.update();
	}
}

CXBasePropertyPage* CGSBasemapWindow::CreateVisualizationPage(const QUuid& objID)
{
	EXObjectType type = GetObjectByID(objID)->GetObjectType();
	CXViewInfoObject* pViewInfo = GetObjectViewInfo(objID);
	switch (type)
	{
	case EXGS3DHorizonTWT:
	case EXGS3DHorizonDepth:
	case EXGS3DHorizonIso:
	case EXGS3DHorizonAtt:
		return new GSBM3DHorizonVisPage(pViewInfo);
	case EXGSStressMap:
		return new GSBMStressMapVisPage(pViewInfo);
	case EXGSSection:
		return new GSBMSectionVisPage(pViewInfo);
	case EXGSRoseDiagram:
		return new GSBMRoseDiagramVisPage(pViewInfo);
	default:
		return nullptr;
	}
}

bool CGSBasemapWindow::IsObjectCanbeDrawn(const CXObject& obj)
{
	if (!QList<EXObjectType>{ EXGS3DHorizonTWT, EXGS3DHorizonDepth, EXGS3DHorizonIso, EXGS3DHorizonAtt, EXGSStressMap, EXGSSection, EXGSPDG, EXWell, EXGSRoseDiagram}.contains(obj.GetObjectType()))
		return false;

	return true;
}

CXViewInfoObject* CGSBasemapWindow::createObjectViewInfo(EXObjectType eType)
{
	switch (eType)
	{
	case EXGS3DHorizonTWT:
	case EXGS3DHorizonDepth:
	case EXGS3DHorizonIso:
	case EXGS3DHorizonAtt:
		return new GS3DHorizonViewInfo;
	case EXGSStressMap:
		return new GSStressMapViewInfo;
	case EXGSSection:
		return new GSSectionViewInfo;
	case EXGSRoseDiagram:
		return new GSRoseDiagramViewInfo;
	default:
		return new CXViewInfoObject;
	}
}

bool CGSBasemapWindow::SetObjectVisibility(QUuid id, bool isVisible)
{
	CXViewInfoObject* pViewInfo = GetObjectViewInfo(id);
	pViewInfo->SetVisible(isVisible);

	CXObject* pObj = GetObjectByID(id);
	Q_ASSERT(pObj);

	if (isVisible)
	{
		bool isTheFirstObj = false;
		if (!m_coordTransform.IsInitialized())
		{
			m_coordTransform.Init(pObj->GetObjectID());
			isTheFirstObj = true;
		}

		setCurrentSurvey(pObj);
		addObject(pObj);
		excludingSameTypeObj(pObj);

		if (isTheFirstObj)
		{
			ui.actionZoom_Reset->triggered();
		}
	}
	else
	{
		removeObject(pObj);
		checkCurrentSurvey(pObj);
	}

	return true;
}

void CGSBasemapWindow::addObject(CXObject* pObj)
{
	QGraphicsItem* pItem = m_itemFactory.Create(pObj);
	pItem->setData(NGSBMItem::eObjectID, pObj->GetObjectID());
	pItem->setData(NGSBMItem::eIsViewInfoChanged, false);
	m_scene.addItem(pItem);

	m_coordItem.UpdateByItem(pItem);
	updateColormapByID(pObj->GetObjectID());
}

void CGSBasemapWindow::removeObject(CXObject* pObj)
{
	auto getLastColormapItemObjectID = [this]()
	{
		const QList<QGraphicsItem*>& items = m_scene.items();
		for (auto iter = items.rbegin(); iter != items.rend(); ++iter)
		{
			QUuid objID = (*iter)->data(NGSBMItem::eObjectID).toUuid();
			if (!objID.isNull())
			{
				CXViewInfoObject* pViewInfo = GetObjectViewInfo(objID);
				if (pViewInfo && !pViewInfo->GetColormapName().isEmpty())
				{
					return objID;
				}
			}
		}

		return QUuid();
	};

	auto itemList = m_scene.items();
	auto foundItem = std::find_if(itemList.begin(), itemList.end(), [pObj](QGraphicsItem* pItem) {
		return pItem->data(NGSBMItem::eObjectID).toUuid() == pObj->GetObjectID();
	});
	if (foundItem != itemList.end())
		m_scene.removeItem(*foundItem);

	QUuid lastColormapItemObjectID = getLastColormapItemObjectID();
	if (lastColormapItemObjectID.isNull())
	{
		ui.colormapWidget->hide();
	}
	else
	{
		updateColormapByID(lastColormapItemObjectID);
	}
}

void CGSBasemapWindow::updateColormapByID(const QUuid& id)
{
	CXViewInfoObject* pViewInfo = GetObjectViewInfo(id);
	if (pViewInfo->GetColormapName().isEmpty())
		return;

	double dMin = pViewInfo->GetDisplayDataMin();
	double dMax = pViewInfo->GetDisplayDataMax();
	if (dMin == M_FINVALID || dMax == M_FINVALID || dMin == dMax)
		return;

	ui.colormapWidget->show();
	ui.colormapWidget->SetColormapName(pViewInfo->GetColormapName());
	ui.colormapWidget->SetDisplayRange(dMin, dMax);
}

void CGSBasemapWindow::excludingSameTypeObj(CXObject* pObj)
{
	auto isSameType = [this](const QList<EXObjectType>& typeList, CXObject* pObj, CXObject* pObjCheck)
	{
		return typeList.contains(pObj->GetObjectType()) && typeList.contains(pObjCheck->GetObjectType());
	};

	bool isNeedUpdateTreeStatus = false;

	for (auto iter = m_mapObjViewInfo.begin(); iter != m_mapObjViewInfo.end(); ++iter)
	{
		if (iter.key() == pObj->GetObjectID() || !iter.value()->GetVisible())
			continue;

		CXObject* pCurrentObj = GetObjectByID(iter.key());
		if (isSameType({ EXGS3DHorizonTWT, EXGS3DHorizonDepth, EXGS3DHorizonIso, EXGS3DHorizonAtt }, pObj, pCurrentObj) ||
			isSameType({ EXGSStressMap }, pObj, pCurrentObj))
		{
			removeObject(pCurrentObj);
			iter.value()->SetVisible(false);
			isNeedUpdateTreeStatus = true;
		}
	}

	if (isNeedUpdateTreeStatus)
	{
		QList<QUuid> listID;
		listID << pObj->GetObjectID();
		CXTree::Instance().UpdateTreeStatus(listID, eGSBaseMap);
		//CXTree::Instance().ReloadStatusByCurrentWindow();
	}
}

void CGSBasemapWindow::setCurrentSurvey(CXObject* pObj)
{
	if (m_scene.GetCurrentSurvey())
		return;

	QUuid surveyID = pObj->GetSurveyID();
	if (surveyID.isNull())
		return;

	m_scene.SetCurrentSurvey(dynamic_cast<CX3DSurvey*>(GetObjectByID(surveyID)));
	ui.actionNewSection->setVisible(true);
	ui.actionNewPDG->setVisible(true);

	//	Only available while there's a stress map!
	if (pObj->GetObjectType() == EXGSStressMap)
		ui.actionNewRoseDiagram->setVisible(true);
}

void CGSBasemapWindow::checkCurrentSurvey(CXObject * pObj)
{
	bool doWeStillHaveASurvey = false;
	bool doWeStillHaveStressMap = false;

	for (auto iter = m_mapObjViewInfo.cbegin(); iter != m_mapObjViewInfo.cend(); ++iter)
	{
		if (!iter.value()->GetVisible())
			continue;

		CXObject* pObj = GetObjectByID(iter.key());

		if (pObj->GetObjectType() == EXGSStressMap)
			doWeStillHaveStressMap = true;

		if (pObj->GetSurveyID().isNull())
			continue;

		doWeStillHaveASurvey = true;
	}

	if (!doWeStillHaveASurvey)
	{
		m_scene.SetCurrentSurvey(nullptr);
		ui.actionNewSection->setVisible(false);
		ui.actionNewPDG->setVisible(false);
	}

	if (!doWeStillHaveStressMap)
		ui.actionNewRoseDiagram->setVisible(false);
}

void CGSBasemapWindow::updateCursorPosition(double dx, double dy, double dz)
{
	//qDebug() << windowTitle();
	m_cursorItem.UpdatePosition(dx, dy);
	m_scene.update();
}