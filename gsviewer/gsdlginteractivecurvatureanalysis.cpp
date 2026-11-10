#include "stdafx.h"
#include <qmessagebox.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include "xdlgcalculatingprogress.h"
#include "xglobal.h"
#include "xcheckboxwidget.h"
#include "xtree.h"
#include "xgeometry.h"
#include "gsdlginteractivecurvatureanalysis.h"
#include "x3dhorizon.h"
#include "gswelltops.h"
#include "gsbm3dhorizonitem.h"
#include "gsitemsticks.h"
#include "gsitemfaultpolygons.h"
#include "gsitemstructures.h"
#include "gsitemstress.h"
#include "gsitemwells.h"
#include "gsthreadsurfacecurvature.h"
#include "gsstresscalculatemethods.h"
#include "gsstressparameters.h"
#include "gsstructure.h"
#include "gsstressmap.h"
#include "gsthreadstressinterpolation.h"
#include "gsthreadutminterpolation.h"
#include "gs3dhorizonfaulttraces.h"
#include "xproject.h"
#include "xwell.h"
#include "gsbmcoordinateitem.h"

#define Z_POINTS 1
#define Z_FAULT 1
#define Z_STICK 2
#define Z_STRUCTURE 3
#define Z_STRESS 4

GSDlgInteractiveCurvatureAnalysis::GSDlgInteractiveCurvatureAnalysis(CXObject *pObj, QWidget * parent) : QDialog(parent)
{
	ui.setupUi(this);

	m_pParas = new GSStressParameters;
	m_pHorizon = dynamic_cast<CX3DHorizon *>(pObj);
	m_nI = m_pHorizon->GetUTM().GetNI();
	m_nJ = m_pHorizon->GetUTM().GetNJ();

	initView();

	initUI();
}

GSDlgInteractiveCurvatureAnalysis::~GSDlgInteractiveCurvatureAnalysis()
{
	m_scene.removeItem(m_pHorizonItem);
	delete m_pHorizonItem;

	if (m_pWellsItem)
	{
		m_scene.removeItem(m_pWellsItem);
		delete m_pWellsItem;
	}

	freeMaps();

	delete m_pParas;
}

void GSDlgInteractiveCurvatureAnalysis::initUI()
{
	//	Initialize the fault table.
	ui.tableWidget->setColumnWidth(0, 40);
	ui.tableWidget->setColumnWidth(1, 100);
	ui.tableWidget->setColumnWidth(2, 100);
	ui.tableWidget->setColumnWidth(3, 80);
	ui.tableWidget->setColumnWidth(4, 80);
	ui.tableWidget->setColumnWidth(5, 80);
	ui.tableWidget->setColumnWidth(6, 80);

	refreshFaultTable();
	refreshWellTable();

	connect(ui.pushButtonCal, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotCalculate);
	connect(ui.pushButtonBlender, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotBlender);
	connect(ui.radioButtonOri, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotChangeView);
	connect(ui.radioButtonMNC, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotChangeView);
	connect(ui.radioButtonMPC, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotChangeView);
	connect(ui.radioButtonAzi, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotChangeView);
	connect(ui.radioButtonBlender, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotChangeView);
	connect(ui.checkBox, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotShowSticks);
	connect(ui.pushButtonFS, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotCreateStructures);
	connect(ui.groupBoxFaults, &QGroupBox::toggled, this, &GSDlgInteractiveCurvatureAnalysis::slotShowFaults);
	connect(ui.groupBoxWells, &QGroupBox::toggled, this, &GSDlgInteractiveCurvatureAnalysis::slotShowWells);
	connect(ui.pushButtonFaultAll, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotSelectFaults);
	connect(ui.pushButtonFaultNone, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotSelectFaults);
	connect(ui.spinBoxFLen, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GSDlgInteractiveCurvatureAnalysis::refreshFaultTable);
	connect(ui.pushButtonClear, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotClear);
	connect(ui.pushButtonCalStress, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotCalStress);
	connect(ui.checkBoxShowFName, &QPushButton::clicked, this, &GSDlgInteractiveCurvatureAnalysis::slotShowFaults);
}

void GSDlgInteractiveCurvatureAnalysis::refreshFaultTable()
{
	ui.tableWidget->clearContents();
	m_listHF.clear();
	int i, iLength = ui.spinBoxFLen->value();

	QList<CXObject *> listFault = m_pHorizon->GetChildren(EXGSFaultTraces);
	for (i = 0; i < listFault.count(); i++)
	{
		GS3DHorizonFaultTraces *pHF = (GS3DHorizonFaultTraces *)listFault[i];
		if (pHF->Length() < iLength)
			continue;

		m_listHF << pHF;
	}
	QStringList sListMag;
	sListMag << "Normal" << "Left-lateral Slip" << "Right-lateral Slip" << "Reverse" << "Auto";

	ui.tableWidget->setRowCount(m_listHF.count());

	for (i = 0; i < m_listHF.count(); i++)
	{
		//	1st column is the check box.
		CXCheckBoxWidget* pCheckBox = new CXCheckBoxWidget;
		pCheckBox->SetChecked(m_listHF[i]->IsActive());
		ui.tableWidget->setCellWidget(i, 0, pCheckBox);

		//	2nd column is fault name.
		QTableWidgetItem* pWItem = new QTableWidgetItem(m_listHF[i]->GetObjectName());
		pWItem->setIcon(QIcon(GetIconPath() + "Fault.png"));
		ui.tableWidget->setItem(i, 1, pWItem);

		//	3rd column is the user specified status.
		QComboBox *pCB = new QComboBox();
		pCB->addItems(sListMag);
		pCB->setCurrentIndex(m_listHF[i]->GetStatus());
		ui.tableWidget->setCellWidget(i, 2, pCB);

		//	4th column is the length.
		pWItem = new QTableWidgetItem(QString::number(m_listHF[i]->Length(), 'f', 0));
		ui.tableWidget->setItem(i, 3, pWItem);

		//	5th column is the dip.
		pWItem = new QTableWidgetItem(QString::number(m_listHF[i]->Dip(), 'f', 0));
		ui.tableWidget->setItem(i, 4, pWItem);

		//	6th column is the max throw.
		pWItem = new QTableWidgetItem(QString::number(m_listHF[i]->MaxThrow(), 'f', 0));
		ui.tableWidget->setItem(i, 5, pWItem);

		//	7th column is the percent of revserse sticks.
		pWItem = new QTableWidgetItem(QString::number(m_listHF[i]->ReversePercent(), 'f', 2));
		ui.tableWidget->setItem(i, 6, pWItem);

		connect(pCheckBox, static_cast<void(CXCheckBoxWidget::*)(int)>(&CXCheckBoxWidget::StateChanged), this, &GSDlgInteractiveCurvatureAnalysis::slotShowFaults);
	}

	slotShowFaults();
}

void GSDlgInteractiveCurvatureAnalysis::refreshWellTable()
{
	ui.tableWidgetWells->clearContents();
	ui.tableWidgetWells->setColumnWidth(0, 40);
	ui.tableWidgetWells->setColumnWidth(1, 100);
	ui.tableWidgetWells->setColumnWidth(2, 80);
	ui.tableWidgetWells->setColumnWidth(3, 80);
	ui.tableWidgetWells->setColumnWidth(4, 80);
	ui.tableWidgetWells->setColumnWidth(5, 80);
	ui.tableWidgetWells->setColumnWidth(6, 80);
	ui.tableWidgetWells->setColumnWidth(7, 80);
	ui.tableWidgetWells->setColumnWidth(8, 80);
	ui.tableWidgetWells->setColumnWidth(9, 80);
	ui.tableWidgetWells->setColumnWidth(10, 80);
	ui.tableWidgetWells->setColumnWidth(11, 80);
	ui.tableWidgetWells->setColumnWidth(12, 80);

	CXObject *pParent = m_pHorizon->GetParent();
	GSWellTops *pTops = (GSWellTops *)(pParent->GetChild("WellTops", EXGSWellTops));
	if (!pTops)
		return;

	int i = 0;
	QStringList sListLWR;
	sListLWR << "1 : 1" << "1.5 : 1" << "2 : 1" << "3 : 1" << "4 : 1" << "5 : 1";
	QMap<QUuid, GSWellTop>& topsMap = pTops->GetAllTops();
	QMapIterator<QUuid, GSWellTop> it(topsMap);
	ui.tableWidgetWells->setRowCount(topsMap.count());
	while (it.hasNext())
	{
		it.next();

		//	1st column is the check box.
		CXCheckBoxWidget* pCheckBox = new CXCheckBoxWidget;
		pCheckBox->SetChecked(true);
		ui.tableWidgetWells->setCellWidget(i, 0, pCheckBox);

		//	2nd column is well name.
		CXObject *pObj = GetObjectByID(it.key());
		QTableWidgetItem* pWItem = new QTableWidgetItem(pObj->GetObjectName());
		pWItem->setIcon(QIcon(GetIconPath() + "Well.png"));
		ui.tableWidgetWells->setItem(i, 1, pWItem);

		//	3rd column is the length of control area.
		ui.tableWidgetWells->setItem(i, 2, new QTableWidgetItem(QString::number(3000)));

		//	4th column is the azimuth of control area.
		QSpinBox *pSB = new QSpinBox();
		pSB->setRange(0, 180);
		pSB->setSingleStep(10);
		pSB->setValue(0);
		pSB->setMaximumHeight(25);
		pSB->setMaximumWidth(60);
		ui.tableWidgetWells->setCellWidget(i, 3, pSB);

		//	5th column is the azimuth of control area.
		QComboBox *pCB = new QComboBox();
		pCB->addItems(sListLWR);
		pCB->setCurrentIndex(0);
		pCB->setMaximumHeight(25);
		pCB->setMaximumWidth(60);
		ui.tableWidgetWells->setCellWidget(i, 4, pCB);

		//	6th, 7th, 8th columns are the coordinate.
		ui.tableWidgetWells->setItem(i, 5, new QTableWidgetItem(QString::number(it.value().m_pos.x(), 'f', 0)));
		ui.tableWidgetWells->setItem(i, 6, new QTableWidgetItem(QString::number(it.value().m_pos.y(), 'f', 0)));
		ui.tableWidgetWells->setItem(i, 7, new QTableWidgetItem(QString::number(it.value().m_dZ)));

		//	9th, 10th, 11th, 12th, 13th columns are SHMax Dir, SHMax, Shmin, SV, and Pp.
		ui.tableWidgetWells->setItem(i, 8, new QTableWidgetItem(QString::number(it.value().m_dDir)));
		ui.tableWidgetWells->setItem(i, 9, new QTableWidgetItem(QString::number(it.value().m_dSHMax)));
		ui.tableWidgetWells->setItem(i, 10, new QTableWidgetItem(QString::number(it.value().m_dShmin)));
		ui.tableWidgetWells->setItem(i, 11, new QTableWidgetItem(QString::number(it.value().m_dSV)));
		ui.tableWidgetWells->setItem(i, 12, new QTableWidgetItem(QString::number(it.value().m_dPp)));

		connect(pCheckBox, static_cast<void(CXCheckBoxWidget::*)(int)>(&CXCheckBoxWidget::StateChanged), this, &GSDlgInteractiveCurvatureAnalysis::slotShowWells);

		i++;
	}

	slotShowWells();
}

void GSDlgInteractiveCurvatureAnalysis::showEvent(QShowEvent*)
{
	ui.graphicsView->fitInView(m_pCoordItem->boundingRect(), Qt::KeepAspectRatio);
}

//	iOpp == 0: all items; 1: Curvature maps; 2: structures,sticks and stress.
void GSDlgInteractiveCurvatureAnalysis::freeMaps(int iOpp)
{
	if (m_pSticksItem)
	{
		m_scene.removeItem(m_pSticksItem);
		delete m_pSticksItem;

		m_pSticksItem = NULL;
	}

	if (m_pStressItem)
	{
		m_scene.removeItem(m_pStressItem);
		delete m_pStressItem;

		m_pStressItem = NULL;
	}

	if (iOpp == 0 || iOpp == 1)
	{
		if (m_pMPC)
		{
			m_scene.removeItem(m_pMPCItem);
			delete m_pMPCItem;
			m_pMPCItem = NULL;

			delete m_pMPC;
			m_pMPC = NULL;
		}

		if (m_pMNC)
		{
			m_scene.removeItem(m_pMNCItem);
			delete m_pMNCItem;
			m_pMNCItem = NULL;

			delete m_pMNC;
			m_pMNC = NULL;
		}

		if (m_pAzi)
		{
			m_scene.removeItem(m_pAziItem);
			delete m_pAziItem;
			m_pAziItem = NULL;

			delete m_pAzi;
			m_pAzi = NULL;
		}

		if (m_pBle)
		{
			m_scene.removeItem(m_pBleItem);
			delete m_pBleItem;
			m_pBleItem = NULL;

			delete m_pBle;
			m_pBle = NULL;
		}
	}

	if (iOpp == 0 || iOpp == 2)
	{
		if (m_pFPsItem)
		{
			m_scene.removeItem(m_pFPsItem);
			delete m_pFPsItem;

			m_pFPsItem = NULL;
		}

		if (m_pStrItem)
		{
			m_scene.removeItem(m_pStrItem);
			delete m_pStrItem;

			m_pStrItem = NULL;
		}
	}
}

void GSDlgInteractiveCurvatureAnalysis::initView()
{
	ui.graphicsView->setScene(&m_scene);

	m_coordTransform.Init(m_pHorizon->GetObjectID());

	m_pCoordItem = new GSBMCoordinateItem(m_coordTransform);
	m_scene.addItem(m_pCoordItem);

	m_pHorizonItem = new GSBM3DHorizonItem(m_pHorizon, m_coordTransform, &m_horizonViewInfo);
	m_scene.addItem(m_pHorizonItem);
	m_pCoordItem->UpdateByItem(m_pHorizonItem);

	connect(ui.graphicsView, &GSBasemapView::ShowPositionInfo, this, &GSDlgInteractiveCurvatureAnalysis::slotGetPosition);

	slotShowWells();
}

void GSDlgInteractiveCurvatureAnalysis::slotGetPosition(const QPoint& pos, QGraphicsItem* pItem)
{
	QPointF scenePos = ui.graphicsView->mapToScene(pos);
	const QPointF& worldCoordinate = m_coordTransform.Local2World(scenePos);
	double dAttribute = -999.25;

	if (pItem)
	{
		auto pHorizonItem = dynamic_cast<GSBM3DHorizonItem*>(pItem);
		if (pHorizonItem)
		{
			dAttribute = pHorizonItem->ValueAt(worldCoordinate);
		}
	}

	double x = worldCoordinate.x();
	double y = worldCoordinate.y();

	setWindowTitle("Curvature Analysis" + QString(" - X:%1  Y:%2  Value:%3").arg(x, 0, 'f', 2).arg(y, 0, 'f', 2).arg(dAttribute));
}

void GSDlgInteractiveCurvatureAnalysis::slotSelectFaults()
{
	bool bSelected = true;
	if (sender() == ui.pushButtonFaultNone)
	{
		bSelected = false;
	}

	int iFNum = m_listHF.size();
	for (int i = 0; i < iFNum; i++)
	{
		CXCheckBoxWidget* pCheckBox = (CXCheckBoxWidget*)(ui.tableWidget->cellWidget(i, 0));
		pCheckBox->blockSignals(true);
		pCheckBox->SetChecked(bSelected);
		pCheckBox->blockSignals(false);
	}

	slotShowFaults();
}

void GSDlgInteractiveCurvatureAnalysis::slotClear()
{
	if (m_pMap)
	{
		delete m_pMap;
		m_pMap = NULL;
	}

	ui.checkBox->setChecked(false);
	freeMaps(2);
}

void GSDlgInteractiveCurvatureAnalysis::slotCalculate()
{
	freeMaps(1);

	QVector<int> vecPara;
	vecPara << ui.spinBoxDX->value() << ui.spinBoxDY->value();
	vecPara << 7 << 8 << 15;	//	Most positive, most negative and dip-azimuth.

	GSThreadSurfaceCurvature *pThread = new GSThreadSurfaceCurvature((CX3DHorizon *)m_pHorizon, vecPara);
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(pThread, this);

	pProgress->show();
	pThread->start();

	if (pProgress->exec() == QDialog::Accepted)
	{
		QVector<CX3DHorizon *> vecHor = pThread->GetOutputHorizons();

		m_pMNC = vecHor[0];
		m_pMPC = vecHor[1];
		m_pAzi = vecHor[2];

		m_pMNCItem = new GSBM3DHorizonItem(m_pMNC, m_coordTransform, &m_horizonViewInfo);
		m_pMPCItem = new GSBM3DHorizonItem(m_pMPC, m_coordTransform, &m_horizonViewInfo);
		m_pAziItem = new GSBM3DHorizonItem(m_pAzi, m_coordTransform, &m_horizonViewInfo);

		ui.radioButtonMNC->setEnabled(true);
		ui.radioButtonMPC->setEnabled(true);
		ui.radioButtonAzi->setEnabled(true);
		ui.radioButtonBlender->setEnabled(false);
		ui.checkBox->setEnabled(false);
		ui.pushButtonBlender->setEnabled(true);

		double dDMin, dDMax, dAMax;
		m_pMNC->GetDataRange(dDMin, dDMax);
		dAMax = qAbs(dDMin);
		ui.lineEditMNC->setText(QString::number(dDMin, 'f', 4) + " ~ " + QString::number(dDMax, 'f', 4));
		m_pMPC->GetDataRange(dDMin, dDMax);
		dAMax = dAMax > qAbs(dDMax) ? dAMax : qAbs(dDMax);
		ui.lineEditMPC->setText(QString::number(dDMin, 'f', 4) + " ~ " + QString::number(dDMax, 'f', 4));

		ui.lineEditThreshold->setText(QString::number(dAMax / 2, 'f', 4));
	}
}

void GSDlgInteractiveCurvatureAnalysis::slotBlender()
{
	float fTh = ui.lineEditThreshold->text().toFloat();
	float fInvalidEPS = GetEPSofInvalidData(g_dInvalidData);

	if (m_pBleItem)
	{
		m_scene.removeItem(m_pBleItem);
		delete m_pBleItem;
	}

	if (!m_pBle)
	{
		m_pBle = new CX3DHorizon(m_pHorizon->GetSurveyID(), m_pHorizon->GetUTM(), "");
		m_pBle->SetObjectType(EX3DHorizonAtt);
	}

	float *pData = m_pBle->GetData();
	float *pPData = m_pMPC->GetData();
	float *pNData = m_pMNC->GetData();
	float *pAData = m_pAzi->GetData();
	int iSize = m_nI * m_nJ;

	for (int i = 0; i < iSize; i++)
	{
		if (qAbs(pPData[i] - g_dInvalidData) < fInvalidEPS)
			pData[i] = g_dInvalidData;
		else if (pPData[i] > fTh || qAbs(pNData[i]) > fTh)
			pData[i] = qAbs(pAData[i]);
		else
			pData[i] = 0.055;	//	A special value indicates error!
	}
	m_pBle->SetModifiedFlag();
	m_pBle->GetGrid().Clear();

	m_pBleItem = new GSBM3DHorizonItem(m_pBle, m_coordTransform, &m_horizonViewInfo);
	ui.radioButtonBlender->setEnabled(true);
	ui.checkBox->setEnabled(true);
	ui.radioButtonBlender->click();
	ui.checkBox->setChecked(false);
	if (m_pSticksItem)
	{
		m_scene.removeItem(m_pSticksItem);
	}
}

void GSDlgInteractiveCurvatureAnalysis::slotChangeView()
{
	m_scene.removeItem(m_pHorizonItem);
	m_scene.removeItem(m_pMNCItem);
	m_scene.removeItem(m_pMPCItem);
	m_scene.removeItem(m_pAziItem);
	m_scene.removeItem(m_pBleItem);

	if (ui.radioButtonMPC->isChecked())
	{
		m_scene.addItem(m_pMPCItem);
	}
	else if (ui.radioButtonMNC->isChecked())
	{
		m_scene.addItem(m_pMNCItem);
	}
	else if (ui.radioButtonOri->isChecked())
	{
		m_scene.addItem(m_pHorizonItem);
	}
	else if (ui.radioButtonAzi->isChecked())
	{
		m_scene.addItem(m_pAziItem);
	}
	else if (ui.radioButtonBlender->isChecked())
	{
		m_scene.addItem(m_pBleItem);
	}
}

void GSDlgInteractiveCurvatureAnalysis::slotShowSticks()
{
	if (ui.checkBox->isChecked() == false)
	{
		if (m_pSticksItem)
			m_scene.removeItem(m_pSticksItem);
	}
	else
	{
		if (!m_pSticksItem)
		{
			m_pSticksItem = new GSItemSticks(m_pBle, &m_coordTransform);
			m_pSticksItem->setZValue(Z_STICK);
		}

		m_scene.addItem(m_pSticksItem);
	}
}

void GSDlgInteractiveCurvatureAnalysis::slotShowWells()
{
	if (ui.groupBoxWells->isChecked())
	{
		if (m_pWellsItem)
		{
			m_scene.removeItem(m_pWellsItem);
			delete m_pWellsItem;
			m_pWellsItem = NULL;
		}

		QList<CXWell *> listWells;
		CXObject *pParent = m_pHorizon->GetParent();
		GSWellTops *pTops = (GSWellTops *)(pParent->GetChild("WellTops", EXGSWellTops));
		if (!pTops)
			return;

		int i = 0;
		QMap<QUuid, GSWellTop>& topsMap = pTops->GetAllTops();
		QMapIterator<QUuid, GSWellTop> it(topsMap);
		if (ui.tableWidgetWells->rowCount() != topsMap.count())
		{
			return;
		}

		while (it.hasNext())
		{
			it.next();
			CXCheckBoxWidget* pCheckBox = (CXCheckBoxWidget*)(ui.tableWidgetWells->cellWidget(i, 0));
			i++;

			if (!pCheckBox->IsChecked())
			{
				continue;
			}

			CXWell *pWell = dynamic_cast<CXWell *>(GetObjectByID(it.key()));
			listWells << pWell;
		}

		if (listWells.isEmpty())
			return;

		m_pWellsItem = new GSItemWells(listWells, &m_coordTransform);
		m_pWellsItem->setZValue(Z_STICK);
		m_scene.addItem(m_pWellsItem);
	}
	else
	{
		if (m_pWellsItem)
		{
			m_scene.removeItem(m_pWellsItem);
			delete m_pWellsItem;
			m_pWellsItem = NULL;
		}
	}
}

void GSDlgInteractiveCurvatureAnalysis::slotShowFaults()
{
	if (m_pFPsItem)
	{
		m_scene.removeItem(m_pFPsItem);
		delete m_pFPsItem;

		m_pFPsItem = NULL;
	}

	m_listSHF.clear();
	if (ui.groupBoxFaults->isChecked())
	{
		int iFNum = m_listHF.size();
		for (int i = 0; i < iFNum; i++)
		{
			CXCheckBoxWidget* pCheckBox = (CXCheckBoxWidget*)(ui.tableWidget->cellWidget(i, 0));
			m_listHF[i]->SetActive(pCheckBox->IsChecked());
			if (!pCheckBox->IsChecked())
				continue;

			m_listSHF << m_listHF[i];
		}

		m_pFPsItem = new GSItemFaultPolygons(m_listSHF, &m_coordTransform, ui.checkBoxShowFName->isChecked());
		m_pFPsItem->setZValue(Z_FAULT);

		m_scene.addItem(m_pFPsItem);
	}
}

void GSDlgInteractiveCurvatureAnalysis::slotCreateStructures()
{
	if (m_pStrItem)
	{
		m_scene.removeItem(m_pStrItem);
		delete m_pStrItem;

		m_pStrItem = NULL;
	}

	while (!m_listStructure.isEmpty())
	{
		GSStructure *pStr = m_listStructure.takeFirst();
		delete pStr;
	}

	int i, j;
	//	Now create structures by faults.
	if (ui.groupBoxFaults->isChecked())
	{
		int iFNum = m_listHF.size();
		for (i = 0, j = 0; i < iFNum; i++)
		{
			CXCheckBoxWidget* pCheckBox = (CXCheckBoxWidget*)(ui.tableWidget->cellWidget(i, 0));
			if (!pCheckBox->IsChecked())
				continue;

			QComboBox *pCB = (QComboBox *)(ui.tableWidget->cellWidget(i, 2));
			m_listSHF[j]->SetStatus(pCB->currentIndex());

			j++;
		}

		GSStressCalculateMethods CM(m_pHorizon);

		m_pParas->m_dFLinearity = ui.spinBoxLinearity->value() * 100.;
		m_pParas->m_dMinFLength = ui.spinBoxFLen->value();
		m_pParas->m_bMerge = ui.checkBoxMerge->isChecked();
		m_pParas->m_iLWRatio = ui.spinBoxLWR->value();
		m_pParas->m_iLowestStatus = ui.comboBoxStatus->currentIndex();
		m_pParas->m_fThrow = ui.spinBoxThrow->value();

		m_listStructure = CM.CreateStructuresByFaults(m_pParas, m_listSHF);

		if (!m_listStructure.isEmpty())
			m_listStructure = CM.StructuresAdjust(m_listStructure, m_pParas);
	}

	//	Now create structures by well.
	QVector<double> vecRatio;
	vecRatio << 1. << 1.5 << 2 << 3 << 4 << 5;
	if (ui.groupBoxWells->isChecked())
	{
		int iRowNum = ui.tableWidgetWells->rowCount();
		for (i = 0; i < iRowNum; i++)
		{
			CXCheckBoxWidget* pCheckBox = (CXCheckBoxWidget*)(ui.tableWidgetWells->cellWidget(i, 0));
			if (!pCheckBox->IsChecked())
				continue;

			double x = ui.tableWidgetWells->item(i, 5)->text().toDouble();
			double y = ui.tableWidgetWells->item(i, 6)->text().toDouble();
			QPointF point(x, y);
			double len = ui.tableWidgetWells->item(i, 2)->text().toDouble();

			QSpinBox *pSB = (QSpinBox *)(ui.tableWidgetWells->cellWidget(i, 3));
			int iAng = pSB->value();
			QComboBox *pCB = (QComboBox *)(ui.tableWidgetWells->cellWidget(i, 4));
			double ratio = vecRatio[pCB->currentIndex()];

			GSStructure *pCapsule = new GSStructure(point, len, iAng, ratio);

			double dSHAzi = ui.tableWidgetWells->item(i, 8)->text().toDouble();
			double dSH = ui.tableWidgetWells->item(i, 9)->text().toDouble();
			double dSh = ui.tableWidgetWells->item(i, 10)->text().toDouble();
			double dSV = ui.tableWidgetWells->item(i, 11)->text().toDouble();
			double dPp = ui.tableWidgetWells->item(i, 12)->text().toDouble();
			pCapsule->PopulateWellData(dSHAzi, dSH, dSh, dSV, dPp);

			m_listStructure << pCapsule;
		}
	}

	if (m_listStructure.isEmpty())
		return;

	m_pStrItem = new GSItemStructures(m_listStructure, &m_coordTransform);
	m_pStrItem->setZValue(Z_STRUCTURE);
	m_scene.addItem(m_pStrItem);
}

void GSDlgInteractiveCurvatureAnalysis::slotCalStress()
{
	if (m_pStressItem)
	{
		m_scene.removeItem(m_pStressItem);
		delete m_pStressItem;

		m_pStressItem = NULL;
	}

	if (m_pMap)
	{
		delete m_pMap;
		m_pMap = NULL;
	}

	CXSeismicUTMTool utm = m_pHorizon->GetUTM();
	utm.ChangeCellSize(utm.GetIInterval() / 2);
	QString sHName = m_pHorizon->GetObjectName();
	sHName.replace("Depth", "Stress");
	sHName = m_pHorizon->GetParent()->GetUnallocatedName(sHName);
	m_pMap = new GSStressMap(utm, sHName, m_pParas);

	for (GSStructure *pCapsule : m_listStructure)
	{
		pCapsule->SetNodeFlag(false);
		m_pMap->AddChild(pCapsule);
	}

	//	Copy the faults to the map.
	int i, iFNum = m_listSHF.size();
	for (i = 0; i < iFNum; i++)
	{
		GS3DHorizonFaultTraces *pDupFT = new GS3DHorizonFaultTraces(*((GS3DHorizonFaultTraces *)m_listSHF[i]));
		m_pMap->AddChild(pDupFT);
	}

	//	Seed points from fault polygons.
	QVector<double> vecStressPoints = m_pMap->CalculateStressInsideCapsulesMethod2();

	/////
	int iSize = vecStressPoints.size() / 4;
	double dMin = 999, dMax = -999;
	for (i = 0; i < iSize; i++)
	{
		dMin = qMin(dMin, vecStressPoints[4 * i + 3]);
		dMax = qMax(dMax, vecStressPoints[4 * i + 3]);
	}

	//	Add seed points from curvature.
	bool bCurvature = ui.checkBox->isChecked();
	if (ui.checkBox->isChecked())
	{
		int i, j, k, nI = utm.GetNI(), nJ = utm.GetNJ();
		double dBAzi = 90 - m_pHorizon->GetBaseSHDirection();
		double dX, dY, dAzi;
		float *pData = NULL;
		if(bCurvature)
			pData = m_pBle->GetData();

		QPolygonF totalPolygon;
		for (CXObject* pObj : m_listStructure)
		{
			GSStructure* pCapsule = dynamic_cast<GSStructure*>(pObj);
			Q_ASSERT(pCapsule);

			QPolygonF bigPolygon;
			pCapsule->GetBigBoundary(bigPolygon);
			totalPolygon = totalPolygon.united(bigPolygon);
		}

		for (i = 0; i < nI; i++)
		{
			for (j = 0; j < nJ; j++)
			{
				utm.IJToXY(i, j, dX, dY);

				if (!totalPolygon.isEmpty() && totalPolygon.containsPoint(QPointF(dX, dY), Qt::WindingFill))
					continue;

				if (bCurvature)
				{
					dAzi = pData[i * nJ + j];
					if (dAzi == g_dInvalidData || qAbs(dAzi - 0.055) < 0.001)
					{
							continue;
					}
				}

				vecStressPoints << dX << dY << 1. << dAzi;
			}
		}
	}

	if (vecStressPoints.isEmpty())
	{
		QMessageBox::warning(NULL, "Stress Calculation", "No valid stress points!");
		return;
	}

	bool bLSQ = true;
	if (!bLSQ)
	{
		std::vector<XPoint> vecStressX, vecStressY, vecStressMag;
		vecStressX.reserve(vecStressPoints.size() / 4);
		vecStressY.reserve(vecStressPoints.size() / 4);
		vecStressMag.reserve(vecStressPoints.size() / 4);

		for (size_t i = 0; i < vecStressPoints.size(); i += 4)
		{
			double dX = vecStressPoints.at(i);
			double dY = vecStressPoints.at(i + 1);
			double dMag = vecStressPoints.at(i + 2);
			double dDir = vecStressPoints.at(i + 3);

			vecStressMag.emplace_back(dX, dY, dMag);

			if (dDir == M_FINVALID)
				continue;

			double dRadian = dDir * M_PI / 180;
			vecStressX.emplace_back(dX, dY, std::cos(dRadian) * dMag);
			vecStressY.emplace_back(dX, dY, std::sin(dRadian) * dMag);
		}

		//	Now interpolate the magnitude map.
		interpolateMag(vecStressMag);

		//	Then interpolate the direction map.
		interpolateDir(vecStressX, vecStressY);
	}
	else
	{
		auto pThread = std::make_unique<GSThreadStressInterpolation>(utm, vecStressPoints, m_pMap);
		pThread->LockRead(m_pMap);
		pThread->SetObjectName(m_pMap->GetObjectName());

		auto pProgress = new CXDlgCalculatingProgress(pThread.get(), this);
		pProgress->show();
		pThread->start();

		if (pProgress->exec() == QDialog::Accepted)
		{
			float *pData = m_pMap->GetData();
			//pData += utm.GetNI() * utm.GetNJ();
			memcpy(pData, &pThread->GetResult()[0], 2 * utm.GetNI() * utm.GetNJ() * sizeof(float));
			m_pMap->SetModifiedFlag();
		}

		pThread->UnlockRead(m_pMap);
	}

	//if (ui.checkBoxBaseDir->isChecked())
	//{
	//	int i, iSize = utm.GetNI() * utm.GetNJ();
	//	float *pData = m_pMap->GetData();
	//	pData += iSize;
	//	double dAng = m_pHorizon->GetBaseSHDirection() * M_PI / 180.;
	//	for (i = 0; i < iSize; i++)
	//	{
	//		pData[i] = dAng + pData[i] * 0.1;
	//	}
	//}	

	m_pStressItem = new GSItemStress(m_pMap, &m_coordTransform);
	m_pStressItem->setZValue(Z_STRESS);
	m_scene.addItem(m_pStressItem);
}

void GSDlgInteractiveCurvatureAnalysis::interpolateMag(std::vector<XPoint>& vecStressMag)
{
	CXSeismicUTMTool utm = m_pMap->GetUTM();
	int i, j, nI = utm.GetNI(), nJ = utm.GetNJ();
	float *pMData = new float[nI * nJ];
	for (i = 0; i < nI * nJ; i++)
		pMData[i] = g_dInvalidData;

	//	The seed points.
	for (auto&& p : vecStressMag)
	{
		utm.XYToIJ(p.x, p.y, i, j);
		pMData[i * nJ + j] = p.z;
	}

	//	Fill the boundary.
	double x, y, zmin = gStressMagRange[MAG_NORMAL].m_fSHMagLower;
	double dTh = 5 * utm.GetIInterval();
	double dHDis = (nJ - 1) * utm.GetJInterval();
	double dVDis = (nI - 1) * utm.GetIInterval();

	for (i = 0; i < nI; i++)
	{
		utm.IJToXY(i, 0, x, y);
		XPoint p = XGeom::ClosestPoint(vecStressMag, x, y);
		double dDis = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, y));
		if (dDis > dTh)
		{
			if (dDis > dVDis)
				dDis = dVDis;
			pMData[i * nJ] = p.z - (p.z - zmin) * dDis / dVDis;
		}

		utm.IJToXY(i, nJ - 1, x, y);
		p = XGeom::ClosestPoint(vecStressMag, x, y);
		dDis = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, y));
		if (dDis > dTh)
		{
			if (dDis > dVDis)
				dDis = dVDis;
			pMData[(i + 1) * nJ - 1] = p.z - (p.z - zmin) * dDis / dVDis;
		}
	}

	for (j = 1; j < nJ - 1; j++)
	{
		utm.IJToXY(0, j, x, y);
		XPoint p = XGeom::ClosestPoint(vecStressMag, x, y);
		double dDis = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, y));
		if (dDis > dTh)
		{
			if (dDis > dHDis)
				dDis = dHDis;
			pMData[j] = p.z - (p.z - zmin) * dDis / dHDis;
		}

		utm.IJToXY(nI - 1, j, x, y);
		p = XGeom::ClosestPoint(vecStressMag, x, y);
		dDis = XGeom::Distance(XVec2d(p.x, p.y), XVec2d(x, y));
		if (dDis > dTh)
		{
			if (dDis > dHDis)
				dDis = dHDis;
			pMData[(nI - 1) * nJ + j] = p.z - (p.z - zmin) * dDis / dHDis;
		}
	}

	//	Now interpolate the magnitudes.
	auto pThread = std::make_unique<GSThreadUTMInterpolation>(utm, pMData, utm, 100);
	pThread->LockRead(m_pMap);
	pThread->SetObjectName(m_pMap->GetObjectName());

	auto pProgress = new CXDlgCalculatingProgress(pThread.get());
	pProgress->show();
	pThread->start();

	if (pProgress->exec() == QDialog::Accepted)
	{
		float *pData = m_pMap->GetData();

		const std::vector<float>& vecData = pThread->GetResult();
		memcpy(pData, &vecData[0], vecData.size() * sizeof(float));
	}

	delete[]pMData;
	pThread->UnlockRead(m_pMap);
}

void GSDlgInteractiveCurvatureAnalysis::interpolateDir(std::vector<XPoint>& vecStressX, std::vector<XPoint>& vecStressY)
{
	CXSeismicUTMTool utm = m_pMap->GetUTM();
	int i, j, nI = utm.GetNI(), nJ = utm.GetNJ();
	float *pXData = new float[nI * nJ], *pYData = new float[nI * nJ];
	for (i = 0; i < nI * nJ; i++)
	{
		pXData[i] = g_dInvalidData;
		pYData[i] = g_dInvalidData;
	}

	//	The seed points.
	for (auto&& p : vecStressX)
	{
		utm.XYToIJ(p.x, p.y, i, j);
		pXData[i * nJ + j] = p.z;
	}

	auto pThread = std::make_unique<GSThreadUTMInterpolation>(utm, pXData, utm, 200);
	pThread->LockRead(m_pMap);
	pThread->SetObjectName(m_pMap->GetObjectName());

	auto pProgress = new CXDlgCalculatingProgress(pThread.get());
	pProgress->show();
	pThread->start();

	if (pProgress->exec() == QDialog::Accepted)
	{
		const std::vector<float>& vecData = pThread->GetResult();
		memcpy(pXData, &vecData[0], vecData.size() * sizeof(float));
	}
	pThread->UnlockRead(m_pMap);

	//	The seed points.
	for (auto&& p : vecStressY)
	{
		utm.XYToIJ(p.x, p.y, i, j);
		pYData[i * nJ + j] = p.z;
	}

	pThread = std::make_unique<GSThreadUTMInterpolation>(utm, pYData, utm, 200);
	pThread->LockRead(m_pMap);
	pThread->SetObjectName(m_pMap->GetObjectName());

	pProgress = new CXDlgCalculatingProgress(pThread.get());
	pProgress->show();
	pThread->start();

	if (pProgress->exec() == QDialog::Accepted)
	{
		const std::vector<float>& vecData = pThread->GetResult();
		memcpy(pYData, &vecData[0], vecData.size() * sizeof(float));
	}
	pThread->UnlockRead(m_pMap);

	float *pData = m_pMap->GetData();
	pData += utm.GetNI() * utm.GetNJ();
	float fRatio = 180. / M_PI;
	for (i = 0; i < nI * nJ; i++)
	{
		pData[i] = atan2(pYData[i], pXData[j]) * fRatio;
		if (pData[i] < 0)
			pData[i] += 180.;
	}

	delete[]pXData;
	delete[]pYData;
}

void GSDlgInteractiveCurvatureAnalysis::accept()
{
	if (m_pMap)
	{

		CXObject *pFolder = m_pHorizon->GetParent();
		m_pMap->SetObjectName(pFolder->GetUnallocatedName(m_pMap->GetObjectName()));

		pFolder->AddChild(m_pMap);
		CXTree::Instance().AddOneObject(pFolder);
	}

	QDialog::accept();
}