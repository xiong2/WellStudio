#include "stdafx.h"
#include <qdebug.h>
#include <qmessagebox.h>
#include <math.h>
#include "gsdlgrsa.h"
#include "xglobal.h"
#include "xproject.h"
#include "gsbmcoordinateitem.h"
#include "gsbm3dhorizonitem.h"
#include "gsrsitemsource.h"
#include "gsrsitemcompose.h"
#include "x3dhorizon.h"
#include "x3dsurvey.h"
#include "xseismicutmtool.h"
#include "gsgeologicstage.h"
#include "xgeneralfolder.h"
#include "xtree.h"
#include "gsstressmap.h"
#include "gsdlgselecthorizon.h"

GSDlgRSA::GSDlgRSA(QWidget *parent)
	: QDialog(parent), m_scene(m_coordTransform)
{
	ui.setupUi(this);

	initUI();

	initView();
}

GSDlgRSA::~GSDlgRSA()
{
	if (m_pComItem)
	{
		m_scene.removeItem(m_pComItem);
		delete m_pComItem;
	}
}

void GSDlgRSA::initView()
{
	ui.graphicsView->setScene(&m_scene);

	m_coordTransform.Init(m_pHorizon->GetObjectID());

	m_pCoordItem = new GSBMCoordinateItem(m_coordTransform);
	m_scene.addItem(m_pCoordItem);

	m_pHorizonItem = new GSBM3DHorizonItem(m_pHorizon, m_coordTransform, &m_horizonViewInfo);
	m_scene.addItem(m_pHorizonItem);
	m_pCoordItem->UpdateByItem(m_pHorizonItem);

	connect(ui.graphicsView, &GSBasemapView::ShowPositionInfo, this, &GSDlgRSA::slotGetPosition);
}

void GSDlgRSA::initUI()
{
	QStringList sListSurvey;
	QList<CXObject*> listSurvey = GetProject()->GetChildren(EX3DSurvey);
	foreach(CXObject* pSurvey, listSurvey)
	{
		sListSurvey << pSurvey->GetObjectName();
	}
	ui.comboBoxSurvey->addItems(sListSurvey);

	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableWidget->setColumnWidth(0, 80);
	ui.tableWidget->setColumnWidth(1, 80);
	ui.tableWidget->setColumnWidth(2, 80);
	ui.tableWidget->setColumnWidth(3, 80);

	slotSurvey();
	slotCBStage();

	connect(ui.comboBoxSurvey, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &GSDlgRSA::slotSurvey);
	connect(ui.spinBoxStage, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GSDlgRSA::slotSpinStage);
	connect(ui.comboBoxStage, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &GSDlgRSA::slotCBStage);
	connect(ui.spinBoxSSource, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GSDlgRSA::slotChangeRSSNum);
	connect(ui.pushButtonAdd, &QPushButton::clicked, this, &GSDlgRSA::slotHorizon);
	connect(ui.pushButtonRemove, &QPushButton::clicked, this, &GSDlgRSA::slotHorizon);
}

void GSDlgRSA::showEvent(QShowEvent*)
{
	reScale(true);
}

void GSDlgRSA::reScale(bool bZoomIn)
{
	if (bZoomIn == false)
		m_fScale += 0.2;
	else if (m_fScale >= 0.2)
		m_fScale -= 0.2;

	QRectF rect = m_pCoordItem->boundingRect();
	rect = rect.adjusted(-rect.width() * m_fScale, -rect.height() * m_fScale, rect.width() * m_fScale, rect.height() * m_fScale);

	ui.graphicsView->fitInView(rect, Qt::KeepAspectRatio);
}

void GSDlgRSA::slotGetPosition(const QPoint& pos, QGraphicsItem*)
{
	QPointF scenePos = ui.graphicsView->mapToScene(pos);
	const QPointF& worldCoordinate = m_coordTransform.Local2World(scenePos);
	double dAttribute = -999.25;

	double x = worldCoordinate.x();
	double y = worldCoordinate.y();

	setWindowTitle("Position" + QString("  X: %1  Y: %2 ").arg(x, 0, 'f', 2).arg(y, 0, 'f', 2));
}

void GSDlgRSA::slotSurvey()
{
	QList<CXObject*> listSurvey = GetProject()->GetChildren(EX3DSurvey);

	m_pSurvey = (CX3DSurvey *)(listSurvey[ui.comboBoxSurvey->currentIndex()]);
	QList<CXObject*> listH = m_pSurvey->GetChildren(EXGS3DHorizonDepth, true);
	if (!listH.isEmpty())
	{
		m_pHorizon = (CX3DHorizon *)listH.first();
		m_center = m_pHorizon->GetUTM().GetCenter();
	}
	else
		return;

	if (m_pComItem)
	{
		m_scene.removeItem(m_pComItem);
		delete m_pComItem;
	}

	QList<QPointF> listCorners = m_pHorizon->GetUTM().GetCorners();
	m_pComItem = new GSRSItemCompose(this, listCorners, &m_coordTransform);
	m_scene.addItem(m_pComItem);
	m_scene.SetMode(GSBasemapScene::eRegionalStress, m_pComItem);

	QList<CXObject *> listStage = m_pSurvey->GetChildren(EXGSGeologicStage, true);
	int iNumStage = listStage.count();
	ui.spinBoxStage->setValue(iNumStage);

	ui.comboBoxStage->clear();
	if (listStage.isEmpty())
	{
		m_pGStage = NULL;
		ui.comboBoxStage->setDisabled(true);
		ui.spinBoxSSource->setDisabled(true);
	}
	else
	{
		QStringList listSID;
		for (int i = 0; i < iNumStage; i++)
		{
			listSID << "stage " + QString::number(i + 1);
		}
		ui.comboBoxStage->addItems(listSID);

		ui.comboBoxStage->setDisabled(false);
		ui.spinBoxSSource->setDisabled(false);

		m_pGStage = (GSGeologicStage *)listStage.first();
		ui.comboBoxStage->setCurrentIndex(0);
	}
}

void GSDlgRSA::slotSpinStage()
{
	ui.comboBoxStage->blockSignals(true);

	ui.comboBoxStage->clear();

	int iNum = ui.spinBoxStage->value();
	if (iNum > 0)
	{
		QStringList sList;
		int iNum = ui.spinBoxStage->value();
		for (int i = 0; i < iNum; i++)
			sList << "Stage " + QString::number(i + 1);

		ui.comboBoxStage->addItems(sList);

		ui.comboBoxStage->setDisabled(false);
		ui.spinBoxSSource->setDisabled(false);
	}
	else
	{
		ui.comboBoxStage->setDisabled(true);
		ui.spinBoxSSource->setDisabled(true);
	}

	CXObject *pGFolder;
	CXObject *pSFolder = m_pSurvey->GetFolder(EXGSFolder);
	QList<CXObject *> listObj = pSFolder->GetChildren(EXGSFolderStage);
	if (listObj.isEmpty())
	{
		pGFolder = new CXGeneralFolder("Geologic Stages", EXGSFolderStage, "GeologicStageFolder.png");
		pSFolder->AddChild(pGFolder);
	}
	else
		pGFolder = listObj[0];

	QList<CXObject *> listStage = pGFolder->GetChildren(EXGSGeologicStage);
	int i;
	for (i = listStage.count(); i < iNum; i++)
	{
		//	Add new one.
		GSGeologicStage *pStage = new GSGeologicStage("Stage " + QString::number(i + 1));
		pGFolder->AddChild(pStage);

		GSStressMap *pMap = new GSStressMap(m_pHorizon->GetUTM(), "Regional Stress", NULL);
		pStage->AddChild(pMap);
	}

	for (i = listStage.count() - 1; i >= iNum; i--)
	{
		GSGeologicStage *pStage = (GSGeologicStage *)listStage[i];
		pGFolder->RemoveOneChild(pStage);
		delete pStage;
	}

	CXTree::Instance().AddOneObject(pGFolder);

	ui.comboBoxStage->blockSignals(false);
	slotCBStage();
}

void GSDlgRSA::slotCBStage()
{
	int i;
	QList<CXObject *> listStage = m_pSurvey->GetChildren(EXGSGeologicStage, true);
	if (listStage.isEmpty())
	{
		return;
	}

	int iID = ui.comboBoxStage->currentIndex();
	if (iID < 0 || iID > listStage.count() - 1)
	{
		return;
	}

	m_pGStage = (GSGeologicStage *)listStage[ui.comboBoxStage->currentIndex()];

	ui.spinBoxSSource->blockSignals(true);
	ui.tableWidget->blockSignals(true);

	ui.tableWidget->clearContents();
	foreach(GSRSItemSource *pRSItem, m_listRSSItem)
	{
		m_scene.removeItem(pRSItem);
		delete pRSItem;
	}
	m_listRSSItem.clear();

	QList<qreal>& listSou = m_pGStage->GetAllSources();
	int iNumSou = listSou.count() / 3;
	ui.spinBoxSSource->setValue(iNumSou);
	ui.tableWidget->setRowCount(iNumSou);
	QList<QPointF> listCorners = m_pHorizon->GetUTM().GetCorners();
	for (i = 0; i < iNumSou; i++)
	{
		QTableWidgetItem *pWItem = new QTableWidgetItem(QString::number(listSou[i * 3], 'f', 0));
		ui.tableWidget->setItem(i, 0, pWItem);

		pWItem = new QTableWidgetItem(QString::number(listSou[i * 3 + 1], 'f', 0));
		ui.tableWidget->setItem(i, 1, pWItem);

		QSpinBox *pSB = new QSpinBox();
		pSB->setRange(0, 180);
		pSB->setSingleStep(5);
		pSB->setValue((int)listSou[i * 3 + 2]);
		pSB->setObjectName(QString::number(i));
		connect(pSB, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GSDlgRSA::slotSouAzi);
		ui.tableWidget->setCellWidget(i, 2, pSB);

		QLineF line(m_center, QPointF(listSou[i * 3], listSou[i * 3 + 1]));
		pWItem = new QTableWidgetItem(QString::number(line.length(), 'f', 0));
		ui.tableWidget->setItem(i, 3, pWItem);

		GSRSItemSource *pItem = new GSRSItemSource(listCorners, &m_coordTransform);
		m_listRSSItem << pItem;
	}

	ui.tableWidget->blockSignals(false);
	ui.spinBoxSSource->blockSignals(false);

	m_pComItem->ClearAllPoints();
	for (i = 0; i < iNumSou; i++)
	{
		m_pComItem->AddOneSource(listSou[3 * i], listSou[3 * i + 1], listSou[3 * i + 2]);
	}

	m_scene.update();

	QList<QUuid>& listHID = m_pGStage->GetAllHID();
	QStringList strList;
	foreach(QUuid objID, listHID)
	{
		CXObject *pObj = GetObjectByID(objID);
		strList << pObj->GetObjectName();
	}

	ui.listWidget->clear();
	ui.listWidget->addItems(strList);
}

void GSDlgRSA::slotChangeRSSNum()
{
	if (!m_pGStage)
	{
		return;
	}

	int i, iNumRow = ui.tableWidget->rowCount();
	QList<qreal>& listSou = m_pGStage->GetAllSources();
	for (i = iNumRow; i < ui.spinBoxSSource->value(); i++)
	{
		//	Add one.
		double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
		m_pHorizon->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);

		double dX = dXMin + i * (dXMax - dXMin) / 4, dY = dYMax + (dYMax - dYMin) / 2;
		ui.tableWidget->insertRow(i);

		QTableWidgetItem *pWItem = new QTableWidgetItem(QString::number(dX, 'f', 0));
		ui.tableWidget->setItem(i, 0, pWItem);

		pWItem = new QTableWidgetItem(QString::number(dY, 'f', 0));
		ui.tableWidget->setItem(i, 1, pWItem);

		QSpinBox *pSB = new QSpinBox();
		pSB->setRange(0, 180);
		pSB->setSingleStep(5);
		pSB->setValue(0);
		pSB->setObjectName(QString::number(i));
		connect(pSB, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GSDlgRSA::slotSouAzi);
		ui.tableWidget->setCellWidget(i, 2, pSB);

		pWItem = new QTableWidgetItem(QString::number(dYMax - dYMin, 'f', 0));
		ui.tableWidget->setItem(i, 3, pWItem);

		m_pComItem->AddOneSource(dX, dY, 0.);
		listSou << dX << dY << 0.;
	}

	for (i = iNumRow - 1; i >= ui.spinBoxSSource->value(); i--)
	{
		//	Remove one.
		ui.tableWidget->removeRow(i);
		m_pComItem->RemoveLastSource();
		listSou.removeLast();
		listSou.removeLast();
		listSou.removeLast();
	}

	m_scene.update();
}

void GSDlgRSA::slotSouAzi()
{
	int iID = sender()->objectName().toInt();
	QList<qreal>& listSou = m_pGStage->GetAllSources();
	int iNumSou = listSou.count() / 3;

	if (iID >= iNumSou || !m_pComItem)
		return;

	QSpinBox *pSB = (QSpinBox *)sender();
	int iAzi = pSB->value();
	listSou[iID * 3 + 2] = iAzi;
	m_pComItem->ModifyOneSource(iID, listSou[iID * 3], listSou[iID * 3 + 1], iAzi);

	m_scene.update();
}

bool GSDlgRSA::UpdateOneSou(int iIDX, QPointF point)
{
	if (!m_pGStage)
		return false;

	QList<qreal>& listSou = m_pGStage->GetAllSources();
	if (listSou.count() / 3 <= iIDX)
		return false;

	listSou[3 * iIDX] = point.x();
	listSou[3 * iIDX + 1] = point.y();
	ui.tableWidget->item(iIDX, 0)->setText(QString::number(point.x(), 'f', 0));
	ui.tableWidget->item(iIDX, 1)->setText(QString::number(point.y(), 'f', 0));

	QLineF line(m_center, point);
	ui.tableWidget->item(iIDX, 3)->setText(QString::number(line.length(), 'f', 0));

	return true;
}

GSStressMap* GSDlgRSA::GetCurrentMap()
{
	if (!m_pGStage)
		return NULL;

	QList<CXObject *> listMap = m_pGStage->GetChildren(EXGSStressMap);
	if (listMap.empty())
		return NULL;

	return (GSStressMap *)listMap[0];
}

void GSDlgRSA::slotHorizon()
{
	if (sender() == ui.pushButtonAdd)
	{
		GSDlgSelectHorizon dlg(m_pSurvey, m_pGStage);
		if (dlg.exec() == QDialog::Accepted)
		{
			QList<QUuid>& listHID = m_pGStage->GetAllHID();
			QStringList strList;
			foreach(QUuid objID, listHID)
			{
				CXObject *pObj = GetObjectByID(objID);
				strList << pObj->GetObjectName();
			}

			ui.listWidget->clear();
			ui.listWidget->addItems(strList);
		}
	}
	else
	{
		QList<QListWidgetItem *> listItem = ui.listWidget->selectedItems();
		if (listItem.isEmpty())
		{
			QMessageBox::warning(NULL, "Remove horizons", "No horizon selected!");
			return;
		}

		QList<CXObject *> listHor = m_pSurvey->GetChildren(EXGSFolderHorizon);
		QList<QUuid>& listHID = m_pGStage->GetAllHID();
		foreach(QListWidgetItem *pItem, listItem)
		{
			QString sName = pItem->text();
			CXObject *pHor = NULL;

			foreach(CXObject *pObj, listHor)
			{
				if (sName == pObj->GetObjectName())
				{
					pHor = pObj;
					break;
				}
			}

			listHID.removeOne(pHor->GetObjectID());
		}

		QStringList strList;
		foreach(QUuid objID, listHID)
		{
			CXObject *pObj = GetObjectByID(objID);
			strList << pObj->GetObjectName();
		}

		ui.listWidget->clear();
		ui.listWidget->addItems(strList);
	}
}