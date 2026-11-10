#include "stdafx.h"
#include <QPushButton>
#include <qdebug.h>
#include <qmessagebox.h>
#include "gsdlginteractivecalculation.h"
#include "x3dhorizon.h"
#include "gsbm3dhorizonitem.h"
#include "gsstresscalculatemethods.h"
#include "gsanticline.h"
#include "gs3dhorizonfaulttraces.h"
#include "gsstructure.h"
#include "gsitemtrappoints.h"
#include "gsitemanticlines.h"
#include "gsitemfaultpolygons.h"
#include "gsitemstructures.h"
#include "gsitemstress.h"
#include "gsstressparameters.h"
#include "gsstressmap.h"
#include "gsthreadstressinterpolation.h"
#include "xdlgcalculatingprogress.h"
#include "xtree.h"
#include "xmatrix.h"

#define Z_POINTS 1
#define Z_FAULT 1
#define Z_LINES 2
#define Z_STRUCTURE 3
#define Z_STRESS 4

GSDlgInteractiveCalculation::GSDlgInteractiveCalculation(CXObject* pObj, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_pParas = new GSStressParameters;

	m_pHorizon = dynamic_cast<CX3DHorizon*>(pObj);
	Q_ASSERT(m_pHorizon);

	QString sName = pObj->GetObjectName();
	sName.replace("(Iso)", "(StressMap)");
	ui.lineEditOutput->setText(sName);

	m_pTrapPointsItem[0] = NULL;
	m_pTrapPointsItem[1] = NULL;
	m_pTrapPointsItem[2] = NULL;

	initView();

	connect(ui.checkBoxSmooth, &QCheckBox::stateChanged, this, &GSDlgInteractiveCalculation::slotSmooth);
	connect(ui.checkBoxPointsVisible, &QCheckBox::stateChanged, this, &GSDlgInteractiveCalculation::slotSetVisible);
	connect(ui.checkBoxLinesVisible, &QCheckBox::stateChanged, this, &GSDlgInteractiveCalculation::slotSetVisible);
	connect(ui.pushButtonSearch, &QPushButton::clicked, this, &GSDlgInteractiveCalculation::slotSearchPoints);
	connect(ui.pushButtonFault, &QPushButton::clicked, this, &GSDlgInteractiveCalculation::slotAdjustFaults);
	connect(ui.pushButtonFit, &QPushButton::clicked, this, &GSDlgInteractiveCalculation::slotFitLines);
	connect(ui.pushButtonCreate, &QPushButton::clicked, this, &GSDlgInteractiveCalculation::slotCreateStructures);
	connect(ui.pushButtonStress, &QPushButton::clicked, this, &GSDlgInteractiveCalculation::slotCalculate);
	connect(ui.radioButtonDirection, &QPushButton::clicked, this, &GSDlgInteractiveCalculation::slotSetColorMode);
	connect(ui.radioButtonGroup, &QPushButton::clicked, this, &GSDlgInteractiveCalculation::slotSetColorMode);
	connect(ui.pushButtonClear, &QPushButton::clicked, this, &GSDlgInteractiveCalculation::slotClear);
	connect(ui.pushButtonAccept, &QPushButton::clicked, this, &GSDlgInteractiveCalculation::slotAccept);
	connect(ui.pushButtonClose, &QPushButton::clicked, this, &GSDlgInteractiveCalculation::close);
}

GSDlgInteractiveCalculation::~GSDlgInteractiveCalculation()
{
	if (m_pSmoothHorizon)
	{
		delete m_pSmoothHorizon;
		m_pSmoothHorizon = nullptr;
	}

	for (int i = 0; i < 3; i++)
	{
		if (m_pTrapPointsItem[i])
		{
			delete m_pTrapPointsItem[i];
			m_pTrapPointsItem[i] = nullptr;
		}
	}

	if (m_pAnticlinesItem)
	{
		delete m_pAnticlinesItem;
		m_pAnticlinesItem = nullptr;
	}

	if (m_pFaultPolygonsItem)
	{
		delete m_pFaultPolygonsItem;
		m_pFaultPolygonsItem = nullptr;
	}

	if (m_pStructuresItem)
	{
		delete m_pStructuresItem;
		m_pStructuresItem = nullptr;
	}

	if (m_pStressItem)
	{
		delete m_pStressItem;
		m_pStressItem = nullptr;
	}

	delete m_pParas;

	if (m_pMap)
		delete m_pMap;
}

void GSDlgInteractiveCalculation::slotClear()
{
	for (int i = 0; i < 3; i++)
	{
		if (m_pTrapPointsItem[i])
		{
			m_scene.removeItem(m_pTrapPointsItem[i]);
			delete m_pTrapPointsItem[i];
			m_pTrapPointsItem[i] = nullptr;
		}
	}

	if (m_pAnticlinesItem)
	{
		m_scene.removeItem(m_pAnticlinesItem);
		delete m_pAnticlinesItem;
		m_pAnticlinesItem = nullptr;
	}

	if (m_pFaultPolygonsItem)
	{
		m_scene.removeItem(m_pFaultPolygonsItem);
		delete m_pFaultPolygonsItem;
		m_pFaultPolygonsItem = nullptr;
	}

	if (m_pStructuresItem)
	{
		m_scene.removeItem(m_pStructuresItem);
		delete m_pStructuresItem;
		m_pStructuresItem = nullptr;
	}

	if (m_pStressItem)
	{
		m_scene.removeItem(m_pStressItem);
		delete m_pStressItem;
		m_pStressItem = nullptr;
	}

	foreach(GSAnticline *pAnticline, m_listAnticline)
	{
		delete pAnticline;
	}
	m_listAnticline.clear();

	foreach(GSStructure *pStructure, m_listStructure)
	{
		delete pStructure;
	}
	m_listStructure.clear();

	if (m_pMap)
	{
		delete m_pMap;
		m_pMap = NULL;
	}
}

void GSDlgInteractiveCalculation::showEvent(QShowEvent*)
{
	ui.graphicsView->fitInView(m_pCoordItem->boundingRect(), Qt::KeepAspectRatio);
	slotSmooth(Qt::Checked);
}

void GSDlgInteractiveCalculation::initView()
{
	ui.graphicsView->setScene(&m_scene);

	m_coordTransform.Init(m_pHorizon->GetObjectID());

	m_pCoordItem = new GSBMCoordinateItem(m_coordTransform);
	m_scene.addItem(m_pCoordItem);

	m_pHorizonItem = new GSBM3DHorizonItem(m_pHorizon, m_coordTransform, &m_horizonViewInfo);
	m_scene.addItem(m_pHorizonItem);
	m_pCoordItem->UpdateByItem(m_pHorizonItem);

	connect(ui.graphicsView, &GSBasemapView::ShowPositionInfo, this, &GSDlgInteractiveCalculation::slotGetPosition);
}

GSBM3DHorizonItem* GSDlgInteractiveCalculation::getSmoothHorizonItem()
{
	if (!m_pSmoothHorizonItem)
	{
		CXSeismicUTMTool& utm = m_pHorizon->GetUTM();
		m_pSmoothHorizon = new CX3DHorizon(m_pHorizon->GetSurveyID(), utm, m_pHorizon->GetObjectName() + "_Smooth");
		float* pData = m_pSmoothHorizon->GetData();
		memcpy(pData, m_pHorizon->GetData(), utm.GetNI() * utm.GetNJ() * sizeof(float));
		smooth(utm, pData, 3750);
		m_pSmoothHorizonItem = new GSBM3DHorizonItem(m_pSmoothHorizon, m_coordTransform, &m_horizonViewInfo);
	}

	return m_pSmoothHorizonItem;
}

void GSDlgInteractiveCalculation::slotGetPosition(const QPoint& pos, QGraphicsItem* pItem)
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

	setWindowTitle("Interactive Calculation" + QString(" - X:%1  Y:%2  Value:%3").arg(x, 0, 'f', 2).arg(y, 0, 'f', 2).arg(dAttribute));
}

void GSDlgInteractiveCalculation::slotSmooth(int checkState)
{
	if (checkState == Qt::Unchecked)
	{
		m_scene.removeItem(m_pSmoothHorizonItem);
		m_scene.addItem(m_pHorizonItem);
	}
	else
	{
		m_scene.removeItem(m_pHorizonItem);
		m_scene.addItem(getSmoothHorizonItem());
	}
}

void GSDlgInteractiveCalculation::slotSetVisible()
{
	if (sender() == ui.checkBoxPointsVisible)
	{
		for (int n = 0; n < 3; n++)
		{
			if (m_pTrapPointsItem[n])
			{
				m_pTrapPointsItem[n]->setVisible(ui.checkBoxPointsVisible->isChecked());
			}
		}
	}
	else if (sender() == ui.checkBoxLinesVisible)
	{
		if (m_pAnticlinesItem)
			m_pAnticlinesItem->setVisible(ui.checkBoxLinesVisible->isChecked());
	}
}

void GSDlgInteractiveCalculation::slotSetColorMode()
{
	for (int n = 0; n < 3; n++)
	{
		if (m_pTrapPointsItem[n])
		{
			m_pTrapPointsItem[n]->SetColorByGroup(ui.radioButtonGroup->isChecked());
		}
	}
}

void GSDlgInteractiveCalculation::slotSearchPoints()
{
	CXSeismicUTMTool utm = m_pHorizon->GetUTM();
	int i, j, k, n, nI = utm.GetNI(), nJ = utm.GetNJ();
	int iDataLen = nI * nJ;
	float *pData = m_pHorizon->GetData();
	unsigned char *pBuff = new unsigned char[nI * nJ];
	unsigned char *pMap = new unsigned char[nI * nJ];

	if (ui.groupBoxTrap1->isChecked())
	{
		if (ui.radioButtonAnti1->isChecked())
			m_pParas->m_iAnti[0] = 1;
		else
			m_pParas->m_iAnti[0] = 2;

		m_pParas->m_dSRadius[0] = ui.spinBoxRadius1->value();
		m_pParas->m_dTHeight[0] = ui.spinBoxHeight1->value();
		m_pParas->m_dCThreshold[0] = ui.doubleSpinBoxCT1->value();
		m_pParas->m_dLThreshold[0] = ui.lineEditLT1->text().toDouble();
	}
	else
		m_pParas->m_iAnti[0] = 0;

	if (ui.groupBoxTrap2->isChecked())
	{
		if (ui.radioButtonAnti2->isChecked())
			m_pParas->m_iAnti[1] = 1;
		else
			m_pParas->m_iAnti[1] = 2;

		m_pParas->m_dSRadius[1] = ui.spinBoxRadius2->value();
		m_pParas->m_dTHeight[1] = ui.spinBoxHeight2->value();
		m_pParas->m_dCThreshold[1] = ui.doubleSpinBoxCT2->value();
		m_pParas->m_dLThreshold[1] = ui.lineEditLT2->text().toDouble();
	}
	else
		m_pParas->m_iAnti[1] = 0;

	if (ui.groupBoxTrap3->isChecked())
	{
		if (ui.radioButtonAnti3->isChecked())
			m_pParas->m_iAnti[2] = 1;
		else
			m_pParas->m_iAnti[2] = 2;

		m_pParas->m_dSRadius[2] = ui.spinBoxRadius3->value();
		m_pParas->m_dTHeight[2] = ui.spinBoxHeight3->value();
		m_pParas->m_dCThreshold[2] = ui.doubleSpinBoxCT3->value();
		m_pParas->m_dLThreshold[2] = ui.lineEditLT3->text().toDouble();
	}
	else
		m_pParas->m_iAnti[2] = 0;


	ui.checkBoxPointsVisible->setChecked(true);

	GSStressCalculateMethods CM(m_pHorizon);

	for (n = 0; n < 3; n++)
	{
		if (m_pTrapPointsItem[n])
		{
			m_scene.removeItem(m_pTrapPointsItem[n]);
			delete m_pTrapPointsItem[n];
		}

		if (m_pParas->m_iAnti[n] == 0)
			continue;

		memset(pBuff, 0, iDataLen);
		memset(pMap, 0, iDataLen);

		m_vecvecTrapPoints[n] = CM.SearchPoints(m_pParas->m_iAnti[n] == 1, m_pParas->m_dTHeight[n], m_pParas->m_dSRadius[n], pBuff, pMap);

		m_pTrapPointsItem[n] = new GSItemTrapPoints(m_vecvecTrapPoints[n], &m_coordTransform);
		m_pTrapPointsItem[n]->SetColorByGroup(ui.radioButtonGroup->isChecked());
		m_pTrapPointsItem[n]->setZValue(Z_POINTS);
		m_scene.addItem(m_pTrapPointsItem[n]);
	}

	delete[]pBuff;
	delete[]pMap;
}

void GSDlgInteractiveCalculation::slotAdjustFaults()
{
	ui.checkBoxFaultVisible->setChecked(true);
	m_listFT.clear();

	if (m_pFaultPolygonsItem)
	{
		m_scene.removeItem(m_pFaultPolygonsItem);
		delete m_pFaultPolygonsItem;
		m_pFaultPolygonsItem = NULL;
	}

	foreach(GSStructure *pStructure, m_listStructure)
	{
		delete pStructure;
	}
	m_listStructure.clear();

	if (m_pStructuresItem)
	{
		m_scene.removeItem(m_pStructuresItem);
		delete m_pStructuresItem;
		m_pStructuresItem = NULL;
	}

	QList<CXObject *> listObj = m_pHorizon->GetChildren(EXGSFaultTraces);

	foreach(CXObject *pObj, listObj)
	{
		GS3DHorizonFaultTraces *pFT = (GS3DHorizonFaultTraces *)pObj;
		m_listFT << pFT;
	}

	if (m_listFT.isEmpty())
		return;

	m_pFaultPolygonsItem = new GSItemFaultPolygons(m_listFT, &m_coordTransform);
	m_pFaultPolygonsItem->setZValue(Z_FAULT);
	m_scene.addItem(m_pFaultPolygonsItem);

	GSStressCalculateMethods CM(m_pHorizon);

	m_pParas->m_bFaults = true;
	m_pParas->m_dFLinearity  = ui.spinBoxFLT->value();
	m_pParas->m_dMinFLength = ui.lineEditFaultLength->text().toDouble();
	m_pParas->m_bAdjReverse = ui.groupBox_5->isChecked();
	m_pParas->m_dNormF = ui.doubleSpinBoxNorm->value();
	m_pParas->m_dESSF = ui.doubleSpinBoxESS->value();
	m_pParas->m_dSSF = ui.doubleSpinBoxSS->value();
	m_pParas->m_dCSSF = ui.doubleSpinBoxCSS->value();

	m_listStructure = CM.CreateStructuresByFaults(m_pParas);
}

void GSDlgInteractiveCalculation::slotFitLines()
{
	if (m_pAnticlinesItem)
	{
		m_scene.removeItem(m_pAnticlinesItem);
		delete m_pAnticlinesItem;
	}

	GSStressCalculateMethods CM(m_pHorizon);

	foreach(GSAnticline *pAnticline, m_listAnticline)
	{
		delete pAnticline;
	}
	m_listAnticline.clear();

	slotSearchPoints();

	m_pParas->m_bRemoveOverlap = ui.groupBoxRemoveOverlap->isChecked();
	m_pParas->m_dTWidth = ui.lineEditTrapWidth->text().toDouble();
	m_pParas->m_dORatio = ui.doubleSpinBoxOverlap->value();

	if (m_pTrapPointsItem[0] || m_pTrapPointsItem[1] || m_pTrapPointsItem[2])
	{
		ui.checkBoxLinesVisible->setChecked(true);

		double dWidth = m_pParas->m_dTWidth;
		if (!m_pParas->m_bRemoveOverlap)
			dWidth = 0;

		for (int n = 0; n < 3; n++)
		{
			if (m_vecvecTrapPoints[n].empty())
				continue;

			QList<GSAnticline *> listAnti = CM.GenerateAnticlines(m_vecvecTrapPoints[n], n, m_pParas);

			m_listAnticline += listAnti;
		}
	}

	m_pParas->m_bFaults = ui.groupBoxFaults->isChecked();
	m_pParas->m_dMinFLength = ui.lineEditFaultLength->text().toDouble();
	if (m_pParas->m_bFaults)
	{
		if (m_listStructure.isEmpty())
		{
			slotAdjustFaults();
		}

		m_listAnticline = CM.RemoveAnticlinesByFaults(m_listAnticline, m_listStructure, m_pParas->m_dMinFLength);
	}
		
	m_pAnticlinesItem = new GSItemAnticlines(m_listAnticline, &m_coordTransform);
	m_pAnticlinesItem->setZValue(Z_LINES);
	m_scene.addItem(m_pAnticlinesItem);
}

void GSDlgInteractiveCalculation::slotCreateStructures()
{
	int i;
	if (m_pStructuresItem)
	{
		m_scene.removeItem(m_pStructuresItem);
		delete m_pStructuresItem;
		m_pStructuresItem = NULL;
	}

	foreach(GSStructure *pStructure, m_listStructure)
	{
		delete pStructure;
	}
	m_listStructure.clear();

	//	Faults.
	if (ui.groupBoxFaults->isChecked())
	{
		slotAdjustFaults();
	}

	//	Anticlines/synclines.
	slotFitLines();
	QPointF end0, end1;
	foreach(GSAnticline *pAnticline, m_listAnticline)
	{
		int iType = 1;
		if (pAnticline->IsAnticline())
			iType = 2;
		pAnticline->GetEndPoints(end0, end1);
		GSStructure *pCapsule = new GSStructure(iType, end0, end1);
		pCapsule->AdjustBoundaryPolygon(ui.spinBoxSRatio->value(), ui.spinBoxSRadius->value());
		m_listStructure << pCapsule;
	}

	GSStressCalculateMethods CM(m_pHorizon);
	m_pParas->m_bMerge = ui.groupBoxStructureMerge->isChecked();
	m_pParas->m_dMergeRatio = ui.doubleSpinBoxMergeOverlap->value();
	m_pParas->m_iMergeAngle = ui.spinBoxMergeAngle->value();
	m_pParas->m_bAdjReverse = ui.groupBox_5->isChecked();
	m_pParas->m_dNormF = ui.doubleSpinBoxNorm->value();
	m_pParas->m_dESSF = ui.doubleSpinBoxESS->value();
	m_pParas->m_dSSF = ui.doubleSpinBoxSS->value();
	m_pParas->m_dCSSF = ui.doubleSpinBoxCSS->value();

	m_listStructure = CM.StructuresAdjust(m_listStructure, m_pParas);

	m_pStructuresItem = new GSItemStructures(m_listStructure, &m_coordTransform);
	m_pStructuresItem->setZValue(Z_STRUCTURE);
	m_scene.addItem(m_pStructuresItem);
}

void GSDlgInteractiveCalculation::slotCalculate()
{
	if (m_pMap)
		delete m_pMap;

	if (m_pStressItem)
	{
		m_scene.removeItem(m_pStressItem);
		delete m_pStressItem;
		m_pStressItem = nullptr;
	}

	slotCreateStructures();

	CXSeismicUTMTool utm = m_pHorizon->GetUTM();
	utm.ChangeCellSize(utm.GetIInterval() / 2);
	QString sHName = m_pHorizon->GetObjectName();
	sHName.replace("Iso", "Stress");
	sHName = m_pHorizon->GetParent()->GetUnallocatedName(sHName);
	m_pMap = new GSStressMap(utm, sHName, m_pParas);

	for (GSAnticline *pAnticline : m_listAnticline)
	{
		pAnticline->SetNodeFlag(false);
		m_pMap->AddChild(pAnticline);
	}

	for (GSStructure *pCapsule : m_listStructure)
	{
		pCapsule->SetNodeFlag(false);
		m_pMap->AddChild(pCapsule);
	}

	QVector<double> vecStressPoints = m_pMap->CalculateStressInsideCapsules();

	//	Then interpolate to the whole map.
	auto pThread = std::make_unique<GSThreadStressInterpolation>(utm, vecStressPoints, m_pMap);
	pThread->LockRead(m_pMap);
	pThread->SetObjectName(m_pMap->GetObjectName());

	auto pProgress = new CXDlgCalculatingProgress(pThread.get(), this);
	pProgress->show();
	pThread->start();

	if (pProgress->exec() == QDialog::Accepted)
	{
		float *pData = m_pMap->GetData();
		memcpy(pData, &pThread->GetResult()[0], utm.GetNI() * utm.GetNJ() * 2 * sizeof(float));
		m_pMap->SetModifiedFlag();
	}

	pThread->UnlockRead(m_pMap);

	m_pStressItem = new GSItemStress(m_pMap, &m_coordTransform);
	m_pStressItem->setZValue(Z_STRESS);
	m_scene.addItem(m_pStressItem);
}

void GSDlgInteractiveCalculation::slotAccept()
{
	if (!m_pMap)
	{
		QMessageBox::warning(NULL, "Calculate Stress", "Please calculate stress before accepting!");
		return;
	}

	CXObject *pFolder = m_pHorizon->GetParent();
	QString sName = ui.lineEditOutput->text();
	sName = pFolder->GetUnallocatedName(sName);
	m_pMap->SetObjectName(sName);

	pFolder->AddChild(m_pMap);
	CXTree::Instance().AddOneObject(pFolder);

	m_pMap = NULL;
	m_listAnticline.clear();
	m_listStructure.clear();

	slotClear();
}

void GSDlgInteractiveCalculation::smooth(const CXSeismicUTMTool& utm, float* pData, double dWindowSize)
{
	std::vector<float> sdata(utm.GetNI() * utm.GetNJ()); // smooth data

	double cellSize = ceil(std::min(utm.GetIInterval(), utm.GetJInterval()));
	int windowSize = (int)ceil(dWindowSize / cellSize);
	int windowHalfSize = std::max(windowSize / 2, 1);
	windowSize = windowHalfSize + 1 + windowHalfSize;

	XMatrix filt(windowSize, windowSize);
	filt.SmoothSavitzkyGolay(3);

	for (int i = 0; i < utm.GetNI(); ++i)
	{
		for (int j = 0; j < utm.GetNJ(); ++j)
		{
			double sum = 0.0; // convolution sum
			double box_sum = 0.0; // simple sum of values
			int count = 0; // entries in the sum

			double z = pData[i * utm.GetNJ() + j];
			if (z == M_FINVALID)
			{
				sdata[i * utm.GetNJ() + j] = M_FINVALID;
				continue;
			}

			for (int m = 0; m < windowSize; ++m)
			{
				int mm = qBound(0, i + m - windowHalfSize, utm.GetNI() - 1);
				for (int n = 0; n < windowSize; ++n)
				{
					int nn = qBound(0, j + n - windowHalfSize, utm.GetNJ() - 1);

					z = pData[mm * utm.GetNJ() + nn];
					if (z == M_FINVALID) continue;

					sum += z * filt.Get(m, n);
					box_sum += z;
					++count;
				}
			}

			if (count == windowSize * windowSize) // no invalid values
				sdata[i * utm.GetNJ() + j] = sum;
			else
				sdata[i * utm.GetNJ() + j] = box_sum / count;
		}
	}

	memcpy(pData, &sdata[0], sdata.size() * sizeof(float));
}