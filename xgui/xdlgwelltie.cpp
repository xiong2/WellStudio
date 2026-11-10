#include <qmessagebox.h>
#include "xdlgwelltie.h"
#include "xwell.h"
#include "xwelltd.h"
#include "xwellpath.h"
#include "xwellcurve.h"
#include "xwavelet.h"
#include "xtemplate.h"
#include "xglobal.h"
#include "xseismicdatavolume.h"
#include "xwellcurvealias.h"
#include "xproject.h"
#include "xdataplusutil.h"
#include "xseismicdatavolume.h"
#include "xgmcubicspline.h"

#include "xframewelltie.h"
#include "xframewttop.h"
#include "xframewtcorner.h"
#include "xframewtanno.h"
#include "xdlgwtlayout.h"

CXDlgWellTie::CXDlgWellTie(CXWell *pWell, QWidget *parent)
	: m_pWell(pWell), QDialog(parent)
{
	ui.setupUi(this);

	initUI();
}

CXDlgWellTie::~CXDlgWellTie()
{
	if (m_pSynData)
		delete[]m_pSynData;

	delete m_pWTFrame;
}

SLayout& CXDlgWellTie::GetSLayout()
{
	return m_pWTFrame->GetSLayout();
}

void CXDlgWellTie::initUI()
{
	setWindowTitle("Well tie of " + m_pWell->GetObjectName());

	m_pWTFrame = new CXFrameWellTie(m_pWell, this);
	ui.scrollArea->setWidget(m_pWTFrame);
	m_pTopFrame = new CXFrameWTTop(m_pWTFrame);
	ui.scrollAreaTop->setWidget(m_pTopFrame);
	m_pLAnnoFrame = new CXFrameWTAnno(this);
	ui.scrollAreaLeft->setWidget(m_pLAnnoFrame);
	m_pRAnnoFrame = new CXFrameWTAnno(this);
	ui.scrollAreaRight->setWidget(m_pRAnnoFrame);

	ui.frameTL->ShowTWT(true);
	ui.frameTR->ShowTWT(false);
	m_pRAnnoFrame->SetType(3);

	//	Seismic DV combo box.
	QList<CXObject *> listDV = ::GetProject()->GetChildren(EXSeismicDataVolume, true);
	QStringList sListDV;
	foreach(CXObject *pObj, listDV)
	{
		CXSeismicDataVolume *pDV = (CXSeismicDataVolume *)pObj;
		if (!pDV->IsPrestack())
		{
			ui.comboBoxDV->addItem(pDV->GetObjectName(), QVariant(pDV->GetObjectID()));
		}
	}

	//	AC curves combo box.
	CXTemplate *pTemplate = CXTemplate::GetTemplate("PSON");
	QList<CXObject *> listCurve = m_pWell->GetSpecialCurveList(pTemplate->GetID());
	QStringList sListCurves;
	foreach(CXObject *pObj, listCurve)
		sListCurves << pObj->GetObjectName();
	ui.comboBoxAC->addItems(sListCurves);

	ui.slideRangeWindow->SetSliderName("Correlation range");
	ui.slideRangeWindow->SetRangeAndPrecision(0, 1000, 1);

	//	DEN combo box.
	pTemplate = CXTemplate::GetTemplate("RHOB");
	listCurve = m_pWell->GetSpecialCurveList(pTemplate->GetID());
	sListCurves.clear();
	foreach(CXObject *pObj, listCurve)
		sListCurves << pObj->GetObjectName();
	sListCurves << "Not use";
	ui.comboBoxDEN->addItems(sListCurves);

	QString sOTD = m_pWell->GetUnallocatedName("Corrected TD");
	ui.lineEdit->setText(sOTD);

	connect(ui.radioButtonTrace, SIGNAL(clicked()), SLOT(slotWaveletRadio()));
	connect(ui.radioButtonTree, SIGNAL(clicked()), SLOT(slotWaveletRadio()));
	connect(ui.pushButtonWavelet, SIGNAL(clicked()), SLOT(slotWaveletSelect()));
	connect(ui.pushButtonCal, SIGNAL(clicked()), SLOT(slotCal()));
	connect(ui.pushButtonApply, SIGNAL(clicked()), SLOT(slotFlush()));

	connect(ui.pushButtonStr, SIGNAL(clicked()), SLOT(slotOperation()));
	connect(ui.pushButtonUndo, SIGNAL(clicked()), SLOT(slotOperation()));
	connect(ui.pushButtonRedo, SIGNAL(clicked()), SLOT(slotOperation()));
	connect(ui.pushButtonLast, SIGNAL(clicked()), SLOT(slotOperation()));
	connect(ui.pushButtonAll, SIGNAL(clicked()), SLOT(slotOperation()));
	connect(ui.pushButtonReset, SIGNAL(clicked()), SLOT(slotOperation()));
	connect(ui.pushButtonLayout, SIGNAL(clicked()), SLOT(slotOperation()));
	connect(ui.pushButtonSave, SIGNAL(clicked()), SLOT(slotOperation()));

	connect(ui.comboBoxSnap, SIGNAL(currentIndexChanged(int)), SLOT(slotSnap(int)));

	connect(ui.verticalScrollBar, SIGNAL(valueChanged(int)), SLOT(slotScroll(int)));
	connect(ui.horizontalScrollBar, SIGNAL(valueChanged(int)), SLOT(slotScroll(int)));

	m_canSize = QSize(0, 0);

	QList<CXObject *> listWavelet = ::GetProject()->GetChildren(EXWavelet, true);
	if (!listWavelet.isEmpty())
	{
		m_pWavelet = (CXWavelet *)listWavelet.first();
		ui.lineEditWavelet->setText(m_pWavelet->GetObjectName());
	}

	slotCal();
}

void CXDlgWellTie::resizeEvent(QResizeEvent* event)
{
	QSize qSize = ui.scrollArea->maximumViewportSize();

	if (m_canSize.height() > 200)
		adjustSBar();
}

void CXDlgWellTie::SetCanvasSize(int iVal, bool bV)
{
	if (bV)
	{
		m_pLAnnoFrame->setFixedHeight(iVal);
		m_pRAnnoFrame->setFixedHeight(iVal);
		m_canSize.setHeight(iVal);
	}
	else
	{
		m_pTopFrame->setFixedWidth(iVal);
		m_canSize.setWidth(iVal);
	}

	QSize qSize = ui.scrollArea->maximumViewportSize();
	if (qSize.height() > 200)
		adjustSBar();
}

void CXDlgWellTie::slotSnap(int iVal)
{
	m_pWTFrame->GetSLayout().m_iSnap = iVal;
}

CXWellTD* CXDlgWellTie::GetWellTD()
{
	if (!m_pTD)
		m_pTD = m_pWell->GetWellTD();

	return m_pTD;
}

void CXDlgWellTie::SetWellTD(CXWellTD *pTD)
{
	m_pTD = pTD;
}

void CXDlgWellTie::adjustSBar()
{
	QSize qSize = ui.scrollArea->maximumViewportSize();
	int iDelta = m_canSize.height() - qSize.height();
	ui.verticalScrollBar->setMinimum(0);
	ui.verticalScrollBar->setPageStep(qSize.height());
	ui.verticalScrollBar->setMaximum(iDelta);

	iDelta = m_canSize.width() - qSize.width();
	if (iDelta < 0)
		iDelta = 0;
	ui.horizontalScrollBar->setMinimum(0);
	ui.horizontalScrollBar->setPageStep(qSize.width());
	ui.horizontalScrollBar->setMaximum(iDelta);
}

void CXDlgWellTie::slotWaveletRadio()
{
	ui.pushButtonWavelet->setEnabled(ui.radioButtonTree->isChecked());
	ui.lineEditWavelet->setEnabled(ui.radioButtonTree->isChecked());
	ui.labelWavelet->setEnabled(!ui.radioButtonTree->isChecked());
	ui.lineEditLength->setEnabled(!ui.radioButtonTree->isChecked());
}

void CXDlgWellTie::slotWaveletSelect()
{
	m_pWavelet = dynamic_cast<CXWavelet *>(::GetCurrentObject());
	if (!m_pWavelet)
	{
		QMessageBox::warning(NULL, "Well Tie", "Please select wavelet from data tree!");
		return;
	}

	ui.lineEditWavelet->setText(m_pWavelet->GetObjectName());
}

void CXDlgWellTie::slotCal()
{
	CXObject *pDV = ::GetObjectByID(ui.comboBoxDV->currentData().toUuid());
	CXTemplate *pTemplate = CXTemplate::GetTemplate("PSON");
	QList<CXObject *> listCurve = m_pWell->GetSpecialCurveList(pTemplate->GetID());
	CXWellCurve *pAC = (CXWellCurve *)(listCurve[ui.comboBoxAC->currentIndex()]);

	pTemplate = CXTemplate::GetTemplate("RHOB");
	listCurve = m_pWell->GetSpecialCurveList(pTemplate->GetID());
	CXWellCurve *pDEN = NULL;
	if (ui.comboBoxDEN->currentIndex() < listCurve.size())
		pDEN = (CXWellCurve *)(listCurve[ui.comboBoxDEN->currentIndex()]);

	CXWellCurve *pRC = calculateRC(pAC, pDEN);
	double *pTRC = NULL;

	if (m_pSynData)
	{
		delete[]m_pSynData;
		m_pSynData = NULL;
	}

	if (m_pWavelet)
	{
		if (!calculateSyn(pRC, m_pSynData))
			return;

		calculateCorrelation(m_pSynData, m_dSTime, m_dStep, m_iNum);

		ui.slideRangeWindow->SetRangeAndPrecision(m_dSTime, m_dSTime + (m_iNum - 1) * m_dStep, m_dStep);
		ui.pushButtonApply->setEnabled(true);
	}

	m_pWTFrame->Populate(pDV, pAC, pDEN, pRC, m_pSynData, m_dSTime, m_dStep, m_iNum);
	m_pWTFrame->update();

	m_pLAnnoFrame->Populate((CXSeismicDataVolume *)pDV, GetWellTD());
	m_pLAnnoFrame->update();
	m_pRAnnoFrame->Populate((CXSeismicDataVolume *)pDV, GetWellTD());
	m_pRAnnoFrame->update();

	//	Move the vertical scroll bar.
	double dSZ, dEZ, dZInc;
	CXSeismicDataVolume *pDVolume = (CXSeismicDataVolume *)pDV;
	pDVolume->GetSamplingRange(dSZ, dEZ, dZInc);
	dEZ = m_dSTime + m_dStep * m_iNum;
	m_pTopFrame->Populate(pDV->GetObjectName(), ui.comboBoxAC->currentText(), ui.comboBoxDEN->currentText(), m_pWavelet, dSZ, dEZ);
	m_pTopFrame->update();
}

void CXDlgWellTie::slotOperation()
{
	if (sender() == ui.pushButtonLayout)
	{
		XDlgWTLayout dlg(this);
		dlg.exec();
	}
	else if (sender() == ui.pushButtonStr)
		stretch();
	else if (sender() == ui.pushButtonUndo)
	{
		if (m_vecUndoTD.isEmpty())
		{
			QMessageBox::warning(this, "Well Tie", "Can not undo, something error here!");
			return;
		}

		CXWellTD *pTD = GetWellTD();
		m_vecRedoTD << pTD;
		pTD = m_vecUndoTD.takeLast();
		SetWellTD(pTD);
		m_pWTFrame->Interact(6);

		slotCal();
		m_pWTFrame->SetCorRect((int)m_dSTime, (int)(m_dSTime + (m_iNum - 1) * m_dStep));
	}
	else if (sender() == ui.pushButtonRedo)
	{
		if (m_vecRedoTD.isEmpty())
		{
			QMessageBox::warning(this, "Well Tie", "Can not redo, something error here!");
			return;
		}

		CXWellTD *pTD = GetWellTD();
		m_vecUndoTD << pTD;
		pTD = m_vecRedoTD.takeLast();
		SetWellTD(pTD);
		m_pWTFrame->Interact(7);

		slotCal();
		m_pWTFrame->SetCorRect((int)m_dSTime, (int)(m_dSTime + (m_iNum - 1) * m_dStep));
	}
	else if (sender() == ui.pushButtonLast)
	{
		m_pWTFrame->Interact(1);
	}
	else if (sender() == ui.pushButtonAll)
	{
		m_pWTFrame->Interact(2);
	}
	else if (sender() == ui.pushButtonReset)
	{
		m_pWTFrame->Interact(0);

		if (m_vecUndoTD.isEmpty())
			return;

		CXWellTD *pTD = m_vecUndoTD.takeFirst();
		foreach(CXWellTD *pTD, m_vecUndoTD)
			delete pTD;
		m_vecUndoTD.clear();

		foreach(CXWellTD *pTD, m_vecRedoTD)
			delete pTD;
		m_vecRedoTD.clear();

		SetWellTD(pTD);

		slotCal();
		m_pWTFrame->SetCorRect((int)m_dSTime, (int)(m_dSTime + (m_iNum - 1) * m_dStep));
	}
	else if (sender() == ui.pushButtonSave)
	{
		CXWellTD *pTD = GetWellTD();
		if (pTD == m_pWell->GetWellTD())
		{
			//	Something error!
			return;
		}

		QString sName = ui.lineEdit->text();
		if (sName.isEmpty())
		{
			QMessageBox::warning(this, "Well Tie", "Please give the output TD name!");
			return;
		}
		sName = m_pWell->GetUnallocatedName(sName);
		pTD->SetObjectName(sName);
		m_pWell->AddChild(pTD);
		m_pWell->SetActivatedTDName(sName);

		ui.pushButtonReset->setEnabled(false);
		ui.pushButtonSave->setEnabled(false);
	}
}

void CXDlgWellTie::MoveScrollBar(int iDelta)
{
	int iVal = ui.verticalScrollBar->value();
	ui.verticalScrollBar->setValue(iVal - iDelta);
}

void CXDlgWellTie::slotScroll(int)
{
	int iH = 0 - ui.horizontalScrollBar->value(), iV = 0 - ui.verticalScrollBar->value();

	m_pWTFrame->move(iH, iV);
	m_pTopFrame->move(iH, 0);
	m_pLAnnoFrame->move(0, iV);
	m_pRAnnoFrame->move(0, iV);
}

void CXDlgWellTie::slotFlush()
{
	double dSTime = ui.slideRangeWindow->GetMinValue();
	double dETime = ui.slideRangeWindow->GetMaxValue();

	calculateCorrelation(m_pSynData + (int)((dSTime - m_dSTime) / m_dStep), dSTime, m_dStep, (dETime - dSTime) / m_dStep + 1);
	m_pWTFrame->SetCorRect((int)dSTime, (int)dETime);
}

CXWellCurve* CXDlgWellTie::calculateRC(CXWellCurve *pAC, CXWellCurve *pDen)
{
	double dStart = pAC->GetStart();
	double dStep = pAC->GetStep();
	int iNum = pAC->GetPointNumber();
	double *pACData = pAC->GetData();
	double *pDenData = NULL;
	if (pDen)
		pDenData = pDen->GetData();
	double dDData1 = 1., dDData2 = 1.;

	double *pData = new double[iNum];
	memset(pData, 0, iNum * sizeof(double));
	double dMax = 0;
	int i, iD = 16;
	for (i = iD; i < iNum; i += iD)
	{
		if (pDenData)
		{
			dDData1 = pDenData[i - iD];
			dDData2 = pDenData[i];
		}

		if (dDData1 != g_dInvalidData && dDData1 != 0. && dDData2 != g_dInvalidData && dDData2 != 0.
			&& pACData[i - iD] != g_dInvalidData && pACData[i - iD] != 0. && pACData[i] != g_dInvalidData && pACData[i] != 0.)
			pData[i] = (dDData2 / pACData[i] - dDData1 / pACData[i - iD]) / (dDData2 / pACData[i] + dDData1 / pACData[i - iD]);
	}

	QString sName = m_pWell->GetUnallocatedName("RC");
	CXWellCurve *pCurve = new CXWellCurve(sName);
	pCurve->ResetData(dStart, dStep, iNum, pData);

	CXObject *pAlias = CXWellCurveAlias::GetAlias("RC");
	CXTemplate *pTemplate = CXTemplate::GetTemplate("RC");
	pAlias->SetTemplateID(pTemplate->GetID());
	pCurve->SetAliasID(pAlias->GetObjectID());
	pAlias->AddEvent(EAdded);

	return pCurve;
}

bool CXDlgWellTie::calculateSyn(CXWellCurve *pRC, float *& pData)
{
	pData = NULL;
	CXWavelet *pWavelet = NULL;
	if (ui.radioButtonTree->isChecked())
	{
		if (!m_pWavelet)
		{
			QMessageBox::warning(NULL, "Well Tie", "Please select wavelet from data tree!");
			return false;
		}

		pWavelet = m_pWavelet;
	}
	else
	{
		//	Need extract wavelet from nearby seismic trace, not implement yet!
		return false;
	}

	unsigned int i, j, k, iWNum = pWavelet->GetPointNumber();
	double *pWData = pWavelet->GetData();
	m_dStep = pWavelet->GetStep();

	double dSZ = pRC->GetStart();
	double dEZ = pRC->GetStop();
	double dZStep = pRC->GetStep();
	double dDMin, dDMax;
	pRC->GetDataRange(dDMin, dDMax);
	dDMax = qMax(qAbs(dDMin), qAbs(dDMax));
	double *pR = pRC->GetData();
	unsigned int iRNum = pRC->GetPointNumber();

	CXWellTD *pTD = GetWellTD();
	CXWellPath *pPath = m_pWell->GetWellPath();

	//	First we need re-sample the RC curve into time domain and seismic resolution.
	m_dSTime = pTD->GetAValue(pPath->Md2Tvd(dSZ));
	m_dSTime = ((int)(m_dSTime / m_dStep)) * m_dStep;
	double dETime = pTD->GetAValue(pPath->Md2Tvd(dEZ));
	dETime = ((int)(dETime / m_dStep)) * m_dStep;
	m_iNum = (dETime - m_dSTime) / m_dStep + 1;
	double *pTRC = new double[m_iNum];
	double *pBuff = new double[m_iNum];
	pData = new float[m_iNum];
	memset(pTRC, 0, m_iNum * sizeof(double));

	dDMax *= 0.1;
	for (i = 0; i < iRNum; i++)
	{
		//if (pR[i] == g_dInvalidData || qAbs(pR[i]) < dDMax)
		if (pR[i] == g_dInvalidData)
			continue;

		double dTVD = pPath->Md2Tvd(dSZ + i * dZStep);
		double dTWT = pTD->GetAValue(dTVD);
		unsigned int iIDX = (dTWT - m_dSTime) / m_dStep;
		if (iIDX >= m_iNum)
			break;

		if (qAbs(pR[i]) > qAbs(pTRC[iIDX]))
			pTRC[iIDX] = pR[i];
	}

	XDataPlusUtil::ConvolutionWavletandR(iWNum, pWData, m_iNum, pTRC, pBuff);

	for (i = 0; i < m_iNum; i++)
		pData[i] = pBuff[i];

	delete[]pBuff;
	delete[]pTRC;

	return true;
}

void CXDlgWellTie::calculateCorrelation(float *pSynData, double dSTime, double dStep, unsigned int iNum)
{
	int iInline, iXline, i, j;
	double dX, dY, dZS, dZE, dZStep;
	CXSeismicDataVolume *pDV = (CXSeismicDataVolume *)::GetObjectByID(ui.comboBoxDV->currentData().toUuid());
	pDV->GetSamplingRange(dZS, dZE, dZStep);
	CXSeismicUTMTool utm = pDV->GetUTM();
	m_pWell->GetWellPosition(dX, dY);
	utm.XYToLine(dX, dY, iInline, iXline);

	int iHW = ui.spinBox->value();
	iHW = (int)(iHW / dStep) * dStep;
	int iNHW = iHW / dStep;
	double dRZS = dZS + (int)((dSTime - iHW - dZS) / dZStep) * dZStep;
	double dRZE = dZS + (int)((dSTime + dStep * (iNum - 1) + iHW) / dZStep + 0.99) * dZStep;
	dRZS = qMax(dRZS, dZS);
	dRZE = qMin(dRZE, dZE);
	int iRNum = (dRZE - dRZS) / dZStep + 1;
	float *pSeiData = new float[iRNum];

	pDV->ReadInline(iInline, iXline, iXline, dRZS, dRZE, pSeiData);

	double *pX = new double[iRNum];
	double *pY = new double[iRNum];
	for (i = 0; i < iRNum; i++)
	{
		pX[i] = dRZS + i * dZStep;
		pY[i] = (double)pSeiData[i];
	}

	CXGMCubicSpline spline(iRNum, pX, pY);

	dRZS = dSTime - iHW;
	dRZE = dSTime + dStep * (iNum - 1) + iHW;
	int iNNum = (dRZE - dRZS) / dStep + 1;
	double *pNData = new double[iNNum];
	for (i = 0; i < iNNum; i++)
	{
		pNData[i] = spline.GetY(dRZS + i * dStep);
	}

	//	Mean X.
	double dSumX = 0., dSumY = 0.;
	for (i = 0; i < iNum; i++)
	{
		dSumX += pSynData[i];
		dSumY += pNData[i];
	}
	double dMeanX = dSumX / iNum;
	double dMeanY = dSumY / iNum;

	double dSumX2 = 0., dSumY2 = 0.;
	for (i = 0; i < iNum; i++)
		dSumX2 += (pSynData[i] - dMeanX) * (pSynData[i] - dMeanX);

	float *dResData = new float[2 * iNHW + 1];
	float fMax = -999., fMin = 999.;
	for (i = 0; i <= 2 * iNHW; i++)
	{
		double dSum = 0.;
		dSumY2 = 0.;
		for (j = 0; j < iNum; j++)
		{
			dSum += (pSynData[j] - dMeanX) * (pNData[j + i] - dMeanY);
			dSumY2 += (pNData[j + i] - dMeanY) * (pNData[j + i] - dMeanY);
		}

		dResData[i] = dSum / sqrt(dSumX2 * dSumY2);
		fMax = qMax(fMax, dResData[i]);
		fMin = qMin(fMin, dResData[i]);

		if (i != 2 * iNHW)
		{
			dSumY -= pNData[i];
			dSumY += pNData[i + iNum];
			dMeanY = dSumY / iNum;
		}
	}

	ui.frame->Populate(iNHW, dStep, dResData);

	delete[]pSeiData;
	delete[]pNData;
	delete[]dResData;
}

void CXDlgWellTie::ShowMessage(QString sMes)
{
	ui.labelMessage->setText(sMes);
}

void CXDlgWellTie::UpdateButtons(int iSta)
{
	if (iSta == 0 || iSta == 2)
	{
		//	Reset or clear all.
		ui.pushButtonStr->setEnabled(false);

		ui.pushButtonLast->setEnabled(false);
		ui.pushButtonAll->setEnabled(false);
	
		if (iSta == 0)
		{
			//	Reset.
			ui.pushButtonRedo->setEnabled(false);
			ui.pushButtonUndo->setEnabled(false);
			ui.pushButtonReset->setEnabled(false);
			ui.pushButtonSave->setEnabled(false);
		}
	}
	else if (iSta == 4 || iSta == 5)
	{
		//	Pick on Syn or WT.
		ui.pushButtonAll->setEnabled(true);
		ui.pushButtonLast->setEnabled(true);
		ui.pushButtonReset->setEnabled(true);

		ui.pushButtonRedo->setEnabled(false);
		ui.pushButtonUndo->setEnabled(false);
		ui.pushButtonStr->setEnabled(iSta == 5);
	}
	else if(iSta == 3)
	{
		//	Stretched.
		ui.pushButtonStr->setEnabled(false);
		ui.pushButtonRedo->setEnabled(false);
		ui.pushButtonUndo->setEnabled(true);

		ui.pushButtonLast->setEnabled(false);
		ui.pushButtonAll->setEnabled(false);
		ui.pushButtonReset->setEnabled(true);

		ui.pushButtonSave->setEnabled(true);
	}
	else if (iSta == 6)
	{
		//	Undo.
		ui.pushButtonStr->setEnabled(false);
		ui.pushButtonUndo->setEnabled(!m_vecUndoTD.isEmpty());
		ui.pushButtonRedo->setEnabled(true);

		ui.pushButtonLast->setEnabled(false);
		ui.pushButtonAll->setEnabled(false);
		ui.pushButtonReset->setEnabled(!m_vecUndoTD.isEmpty());

		ui.pushButtonSave->setEnabled(!m_vecUndoTD.isEmpty());
	}
	else if (iSta == 7)
	{
		//	Redo.
		ui.pushButtonStr->setEnabled(false);
		ui.pushButtonUndo->setEnabled(true);
		ui.pushButtonRedo->setEnabled(!m_vecRedoTD.isEmpty());

		ui.pushButtonLast->setEnabled(false);
		ui.pushButtonAll->setEnabled(false);
		ui.pushButtonReset->setEnabled(true);

		ui.pushButtonSave->setEnabled(true);
	}
}

void CXDlgWellTie::stretch()
{
	QPolygonF polyStr = m_pWTFrame->GetStretchPairs();
	if (polyStr.isEmpty())
		return;

	unsigned int i, j, k, iNum, iNNum, iPNum = polyStr.size();
	CXWellTD *pCTD = GetWellTD();
	double *pNZData, *pZData = pCTD->GetData(iNum);
	double dShift = polyStr[0].y() - polyStr[0].x();

	if (iPNum == 1)
	{
		//	Only need shift the whole line.
		iNNum = iNum;
		pNZData = new double[iNNum];
		memcpy(pNZData, pZData, sizeof(double) * iNNum);

		//	Then add the time shift.
		iNum /= 2;
		double *pTData = pNZData + iNum;
		for (i = 0; i < iNum; i++)
			pTData[i] += dShift;
	}
	else
	{
		iNNum = iNum + 2 * iPNum;
		pNZData = new double[iNNum];

		iNum /= 2;
		double *pTData = pZData + iNum;
		double *pNTData = pNZData + iNum + iPNum;

		//	The first point.
		qreal dT = polyStr[0].x();
		for (i = 0; i < iNum; i++)
			if (pTData[i] > dT)
				break;

		for (j = 0; j < i; j++)
		{
			pNZData[j] = pZData[j];
			pNTData[j] = pTData[j] + dShift;
		}
		pNZData[i] = pZData[i - 1] + (pZData[i] - pZData[i - 1]) * (dT - pTData[i - 1]) / (pTData[i] - pTData[i - 1]);
		pNTData[i] = polyStr[0].y();

		//	The following points.
		unsigned int iID1 = i, iID = i;
		for (k = 1; k < iPNum; k++)
		{
			dT = polyStr[k].x();
			double dShift2 = polyStr[k].y() - polyStr[k].x();
			for (i = iID1; i < iNum; i++)
				if (pTData[i] > dT)
					break;

			int n = i - iID1 + 1;
			qreal dDelta = (dShift2 - dShift) / n;
			for (j = iID1; j < i; j++)
			{
				iID++;
				dShift += dDelta;
				pNZData[iID] = pZData[j];
				pNTData[iID] = pTData[j] + dShift;
			}

			iID++;
			pNZData[iID] = pZData[i - 1] + (pZData[i] - pZData[i - 1]) * (dT - pTData[i - 1]) / (pTData[i] - pTData[i - 1]);
			pNTData[iID] = polyStr[k].y();

			iID1 = i;
			dShift = dShift2;
		}

		//	From the last point to the ends;
		for (j = i; j < iNum; j++)
		{
			iID++;
			pNZData[iID] = pZData[j];
			pNTData[iID] = pTData[j] + dShift;
		}
	}

	CXWellTD *pNewTD = new CXWellTD;
	pNewTD->ResetData(pNZData, iNNum);

	//	Push current TD into undo vector and clear redo vector.
	CXWellTD *pCurTD = GetWellTD();
	m_vecUndoTD << pCurTD;

	foreach(CXWellTD *pTD, m_vecRedoTD)
		delete pTD;
	m_vecRedoTD.clear();

	SetWellTD(pNewTD);
	m_pWTFrame->Interact(3);

	slotCal();
	m_pWTFrame->SetCorRect((int)m_dSTime, (int)(m_dSTime + (m_iNum - 1) * m_dStep));
}