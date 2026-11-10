#include <qmessagebox.h>
#include <qlineedit.h>
#include "xdlgcpsetting.h"
#include "xglobal.h"
#include "xproject.h"
#include "xtemplate.h"
#include "xbuttoncoloredit.h"
#include "xtypecombo.h"
#include "xcheckboxwidget.h"
#include "xcrossplotscene.h"
#include "xwellcurve.h"
#include "x3dhorizon.h"
#include "xseismicutmtool.h"
#include "xwelltops.h"
#include "xwell.h"

XDlgCPSetting::XDlgCPSetting(CXCrossPlotScene *pScene, QWidget *parent)
	: QDialog(parent), m_pScene(pScene)
{
	ui.setupUi(this);

	initGUI();
}

XDlgCPSetting::~XDlgCPSetting()
{
}

void XDlgCPSetting::initGUI()
{
	connect(ui.radioButtonLog, SIGNAL(clicked()), this, SLOT(slotTypeSelect()));
	connect(ui.radioButtonHor, SIGNAL(clicked()), this, SLOT(slotTypeSelect()));
	connect(ui.comboBoxC, SIGNAL(currentIndexChanged(int)), this, SLOT(slotColorCB()));
	connect(ui.buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this, SLOT(slotApply()));

	ui.comboBox->setEnabled(false);
	slotTypeSelect();
}

void XDlgCPSetting::slotTypeSelect()
{
	bool bWell = ui.radioButtonLog->isChecked();
	ui.radioButtonDDL->setVisible(bWell);
	ui.radioButtonNDL->setVisible(bWell);
	ui.radioButtonWT->setVisible(bWell);
	ui.labelTTops->setVisible(bWell);
	ui.comboBoxTTops->setVisible(bWell);
	ui.labelBTops->setVisible(bWell);
	ui.comboBoxBTops->setVisible(bWell);
	ui.label_5->setVisible(!bWell);
	ui.comboBoxResample->setVisible(!bWell);

	connect(ui.radioButtonNDL, SIGNAL(clicked()), this, SLOT(slotDepthLimit()));
	connect(ui.radioButtonDDL, SIGNAL(clicked()), this, SLOT(slotDepthLimit()));
	connect(ui.radioButtonWT, SIGNAL(clicked()), this, SLOT(slotDepthLimit()));

	if (bWell)
	{
		QList<CXObject *> listWTops = ::GetProject()->GetChildren(EXWellTops, true);
		if (listWTops.isEmpty())
		{
			ui.radioButtonWT->setEnabled(false);
		}
		else
		{
			QStringList sListWells, sListTops;
			CXWellTops *pTops = (CXWellTops *)listWTops.first();
			pTops->GetWellAndFormation(sListWells, sListTops);
			ui.comboBoxTTops->addItems(sListTops);
			ui.comboBoxBTops->addItems(sListTops);
		}
		ui.labelTTops->setEnabled(false);
		ui.labelBTops->setEnabled(false);
		ui.comboBoxTTops->setEnabled(false);
		ui.comboBoxBTops->setEnabled(false);

		refreshWellTable();
	}
	else
	{
		refreshHor();
	}
}

void XDlgCPSetting::slotDepthLimit()
{
	if (ui.radioButtonNDL->isChecked())
	{
		m_iDLType = 0;
	}
	else if (ui.radioButtonDDL->isChecked())
	{
		m_iDLType = 1;
	}
	else
	{
		m_iDLType = 2;
	}

	ui.labelTTops->setEnabled(m_iDLType == 2);
	ui.labelBTops->setEnabled(m_iDLType == 2);
	ui.comboBoxTTops->setEnabled(m_iDLType == 2);
	ui.comboBoxBTops->setEnabled(m_iDLType == 2);

	adjustWellTable();
}

void XDlgCPSetting::slotColorCB()
{
	bool bColorAxis = ui.comboBoxC->currentIndex() != 0;

	if (m_bColorAxis != bColorAxis)
	{
		m_bColorAxis = bColorAxis;
		ui.comboBox->setEnabled(m_bColorAxis);
		adjustWellTable();
	}
}

void XDlgCPSetting::slotCBC()
{
	int iRow = ui.tableWidget->rowCount();
	for (int i = 0; i < iRow; i++)
	{
		CXCheckBoxWidget* pCheckBox1 = (CXCheckBoxWidget*)(ui.tableWidget->cellWidget(i, 0));
		bool bSel = pCheckBox1->IsChecked();

		QWidget *pW = ui.tableWidget->cellWidget(i, 1);
		pW->setEnabled(bSel);
		pW = ui.tableWidget->cellWidget(i, 2);
		pW->setEnabled(bSel);
		pW = ui.tableWidget->cellWidget(i, 3);
		pW->setEnabled(bSel);
		pW = ui.tableWidget->cellWidget(i, 4);
		pW->setEnabled(bSel);
		pW = ui.tableWidget->cellWidget(i, 5);
		if (pW)
			pW->setEnabled(bSel);
		pW = ui.tableWidget->cellWidget(i, 6);
		if (pW)
			pW->setEnabled(bSel);
		pW = ui.tableWidget->cellWidget(i, 7);
		if (pW)
			pW->setEnabled(bSel);
	}
}

void XDlgCPSetting::refreshWellTable()
{
	ui.tableWidget->clear();
	QStringList sListAlias;
	QList<CXObject *> listObj = ::GetProject()->GetChildren(EXWellCurveAlias, true);
	foreach(CXObject *pObj, listObj)
	{
		sListAlias << pObj->GetObjectName();
	}

	ui.comboBoxX->clear();
	ui.comboBoxX->addItems(sListAlias);
	ui.comboBoxY->clear();
	ui.comboBoxY->addItems(sListAlias);

	sListAlias.prepend("Not use");
	ui.comboBoxC->clear();
	ui.comboBoxC->addItems(sListAlias);

	QList<CXObject *> listWell = ::GetProject()->GetChildren(EXWell, true);
	m_sListCName.clear();
	m_sListCName << "Show" << "Well" << "Color" << "Size" << "Shape";
	if(!m_bColorAxis)
		m_sListCName << "Fill Color";
	if (m_iDLType == 1)
		m_sListCName << "Start MD" << "End MD";

	ui.tableWidget->setColumnCount(m_sListCName.size());
	ui.tableWidget->setHorizontalHeaderLabels(m_sListCName);

	ui.tableWidget->setRowCount(listWell.size());
	ui.tableWidget->setColumnWidth(0, 60);
	ui.tableWidget->setColumnWidth(1, 60);
	ui.tableWidget->setColumnWidth(2, 60);
	ui.tableWidget->setColumnWidth(3, 60);
	ui.tableWidget->setColumnWidth(4, 100);
	ui.tableWidget->setRowCount(listWell.size());
	for (int i = 0; i < listWell.size(); i++)
	{
		CXCheckBoxWidget* pCheckBox1 = new CXCheckBoxWidget;
		pCheckBox1->SetChecked(false);
		ui.tableWidget->setCellWidget(i, 0, pCheckBox1);
		connect(pCheckBox1, SIGNAL(StateChanged(int)), this, SLOT(slotCBC()));

		QLabel *pLabel = new QLabel(listWell[i]->GetObjectName());
		ui.tableWidget->setCellWidget(i, 1, pLabel);
		pLabel->setEnabled(false);

		CXButtonColorEdit *pColorButton = new CXButtonColorEdit;
		pColorButton->SetColor(QColor("black"));
		pColorButton->setEnabled(false);
		ui.tableWidget->setCellWidget(i, 2, pColorButton);

		QStringList strListSize;
		strListSize << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8";
		QComboBox *pSizeComboBox = new QComboBox;
		pSizeComboBox->addItems(strListSize);
		pSizeComboBox->setCurrentIndex(2);
		pSizeComboBox->setEnabled(false);
		ui.tableWidget->setCellWidget(i, 3, pSizeComboBox);

		CXTypeCombo *pPointTypeCB = new CXTypeCombo(ePointType);
		ui.tableWidget->setCellWidget(i, 4, pPointTypeCB);
		pPointTypeCB->setEnabled(false);

		int iPos = 5;
		if (!m_bColorAxis)
		{
			CXButtonColorEdit *pFillCB = new CXButtonColorEdit;
			pFillCB->SetColor(listWell[i]->GetColor());
			pFillCB->setEnabled(false);
			ui.tableWidget->setCellWidget(i, 5, pFillCB);
			iPos++;
		}

		if (m_iDLType == 1)
		{
			QLineEdit *pLE1 = new QLineEdit;
			pLE1->setValidator(new QDoubleValidator);
			pLE1->setEnabled(false);
			ui.tableWidget->setCellWidget(i, iPos, pLE1);
			QLineEdit *pLE2 = new QLineEdit;
			pLE2->setValidator(new QDoubleValidator);
			pLE2->setEnabled(false);
			ui.tableWidget->setCellWidget(i, iPos + 1, pLE2);
		}
	}
}

void XDlgCPSetting::adjustWellTable()
{
	if (m_bColorAxis)
	{
		int iIDX = m_sListCName.indexOf("Fill Color");

		if (iIDX != -1)
		{
			ui.tableWidget->removeColumn(iIDX);
			m_sListCName.removeAt(iIDX);
		}
	}
	else
	{
		int iIDX = m_sListCName.indexOf("Fill Color");

		if (iIDX == -1)
		{
			m_sListCName.insert(5, "Fill Color");
			ui.tableWidget->insertColumn(5);

			QList<CXObject *> listWell = ::GetProject()->GetChildren(EXWell, true);
			for (int i = 0; i < ui.tableWidget->rowCount(); i++)
			{
				CXCheckBoxWidget* pCheckBox1 = (CXCheckBoxWidget*)(ui.tableWidget->cellWidget(i, 0));

				CXButtonColorEdit *pFillCB = new CXButtonColorEdit;
				pFillCB->SetColor(listWell[i]->GetColor());
				pFillCB->setEnabled(pCheckBox1->IsChecked());
				ui.tableWidget->setCellWidget(i, 5, pFillCB);
			}
			ui.tableWidget->setHorizontalHeaderLabels(m_sListCName);
		}
	}

	if (m_iDLType == 1)
	{
		int iIDX = m_sListCName.indexOf("Start MD");

		if (iIDX == -1)
		{
			int iPos = m_sListCName.size();
			m_sListCName << "Start MD" << "End MD";
			ui.tableWidget->insertColumn(iPos);
			ui.tableWidget->insertColumn(iPos);

			QList<CXObject *> listWell = ::GetProject()->GetChildren(EXWell, true);
			for (int i = 0; i < ui.tableWidget->rowCount(); i++)
			{
				CXCheckBoxWidget* pCheckBox1 = (CXCheckBoxWidget*)(ui.tableWidget->cellWidget(i, 0));
				CXWell *pWell = (CXWell *)listWell[i];
				double dSDepth, dEDepth;
				pWell->GetDepthRange(dSDepth, dEDepth);

				QLineEdit *pLE1 = new QLineEdit;
				pLE1->setValidator(new QDoubleValidator);
				pLE1->setEnabled(pCheckBox1->IsChecked());
				pLE1->setText(QString::number(dSDepth));
				ui.tableWidget->setCellWidget(i, iPos, pLE1);
				QLineEdit *pLE2 = new QLineEdit;
				pLE2->setValidator(new QDoubleValidator);
				pLE2->setEnabled(pCheckBox1->IsChecked());
				pLE2->setText(QString::number(dEDepth));
				ui.tableWidget->setCellWidget(i, iPos + 1, pLE2);
			}
			ui.tableWidget->setHorizontalHeaderLabels(m_sListCName);
		}
	}
	else
	{
		int iIDX = m_sListCName.indexOf("Start MD");

		if (iIDX != -1)
		{
			m_sListCName.removeOne("Start MD");
			m_sListCName.removeOne("End MD");

			ui.tableWidget->removeColumn(iIDX);
			ui.tableWidget->removeColumn(iIDX);
		}
	}
}

void XDlgCPSetting::refreshHor()
{
	QStringList sListHor;
	QList<CXObject *> listObj = ::GetProject()->GetChildren(EX3DHorizon, true);
	if (listObj.isEmpty())
	{
		QMessageBox::warning(NULL, "Cross Plot", "Now horizons in current project yet!");
		return;
	}

	CX3DHorizon *pHor = (CX3DHorizon *)listObj.first();
	CXSeismicUTMTool utm = pHor->GetUTM();
	unsigned int iNum = utm.GetNI() * utm.GetNJ();

	foreach(CXObject *pObj, listObj)
	{
		sListHor << pObj->GetObjectName();
	}
	listObj = ::GetProject()->GetChildren(EX3DHorizonAtt, true);
	foreach(CXObject *pObj, listObj)
	{
		sListHor << pObj->GetObjectName();
	}

	ui.comboBoxX->clear();
	ui.comboBoxX->addItems(sListHor);
	ui.comboBoxY->clear();
	ui.comboBoxY->addItems(sListHor);

	ui.label_5->setText("Total points number is " + QString::number(iNum) + ", need resample?");

	ui.tableWidget->clear();
	QStringList sList;
	sList << "Color" << "Size" << "Fill Color" << "Shape";
	ui.tableWidget->setColumnCount(sList.size());
	ui.tableWidget->setHorizontalHeaderLabels(sList);
	ui.tableWidget->setRowCount(1);

	CXButtonColorEdit *pColorButton = new CXButtonColorEdit;
	pColorButton->SetColor(QColor("black"));
	ui.tableWidget->setCellWidget(0, 0, pColorButton);

	QStringList strListSize;
	strListSize << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8";
	QComboBox *pSizeComboBox = new QComboBox;
	pSizeComboBox->addItems(strListSize);
	pSizeComboBox->setCurrentIndex(2);
	ui.tableWidget->setCellWidget(0, 1, pSizeComboBox);

	CXButtonColorEdit *pFillCB = new CXButtonColorEdit;
	ui.tableWidget->setCellWidget(0, 2, pFillCB);

	CXTypeCombo *pPointTypeCB = new CXTypeCombo(ePointType);
	ui.tableWidget->setCellWidget(0, 3, pPointTypeCB);
}

bool XDlgCPSetting::slotApply()
{
	QString sHTitle, sVTitle, sCTitle;
	double dXMin = 9999999, dXMax = -9999999, dYMin = 9999999, dYMax = -9999999, dCMin = 99999999, dCMax = -999999;
	if(m_bColorAxis)
		m_pScene->SetColormapIDX(ui.comboBox->currentIndex());
	else
		m_pScene->SetColormapIDX(-1);

	if (ui.radioButtonLog->isChecked())
	{
		QString sTTops, sBTops;
		CXWellTops *pTops = NULL;
		if (m_iDLType == 2)
		{
			sTTops = ui.comboBoxTTops->currentText();
			sBTops = ui.comboBoxBTops->currentText();
			if (sTTops == sBTops)
			{
				QMessageBox::warning(NULL, "CrossPlot", "The top formation and bottom formation should not be the same one!");
				return false;
			}

			QList<CXObject *> listWTops = ::GetProject()->GetChildren(EXWellTops, true);
			pTops = (CXWellTops *)listWTops.first();
		}

		int i;
		QList<CXObject *> listAlias = ::GetProject()->GetChildren(EXWellCurveAlias, true);
		QUuid xID = listAlias.at(ui.comboBoxX->currentIndex())->GetObjectID();
		QUuid yID = listAlias.at(ui.comboBoxY->currentIndex())->GetObjectID();
		QUuid cID;
		if (m_bColorAxis)
		{
			cID = listAlias.at(ui.comboBoxC->currentIndex() - 1)->GetObjectID();
			sCTitle = listAlias.at(ui.comboBoxX->currentIndex() - 1)->GetObjectName();
		}

		sHTitle = listAlias.at(ui.comboBoxX->currentIndex())->GetObjectName();
		sVTitle = listAlias.at(ui.comboBoxY->currentIndex())->GetObjectName();

		QVector<int> vecIDX;
		QVector<CXObject *> vecCurves;
		QList<CXObject *> listWell = ::GetProject()->GetChildren(EXWell, true);
		for (i = 0; i < listWell.size(); i++)
		{
			CXCheckBoxWidget* pCheckBox1 = (CXCheckBoxWidget*)(ui.tableWidget->cellWidget(i, 0));
			if (!pCheckBox1->IsChecked())
				continue;

			CXObject *pWell = listWell[i];
			QList<CXObject *> listCurves = pWell->GetChildren(EXWellCurve, true);
			CXObject *pXCurve = NULL, *pYCurve = NULL, *pCCurve = NULL;
			foreach(CXObject *pObj, listCurves)
			{
				CXWellCurve *pCurve = (CXWellCurve *)pObj;
				QUuid aID = pCurve->GetAliasID();
				if (aID == xID)
					pXCurve = pCurve;
				if (aID == yID)
					pYCurve = pCurve;
				if (aID == cID)
					pCCurve = pCurve;
			}

			if (!pXCurve || !pYCurve || (!pCCurve && m_bColorAxis))
				continue;

			double dDMin, dDMax;
			pXCurve->GetDataRange(dDMin, dDMax);
			dXMin = qMin(dXMin, dDMin);
			dXMax = qMax(dXMax, dDMax);
			pYCurve->GetDataRange(dDMin, dDMax);
			dYMin = qMin(dYMin, dDMin);
			dYMax = qMax(dYMax, dDMax);

			if (m_bColorAxis)
			{
				pCCurve->GetDataRange(dDMin, dDMax);
				dCMin = qMin(dCMin, dDMin);
				dCMax = qMax(dCMax, dDMax);
			}

			vecCurves << pXCurve << pYCurve << pCCurve;
			vecIDX << i;
		}

		if (vecCurves.isEmpty())
		{
			QMessageBox::warning(NULL, "Cross Plot", "No valid wells be selected!");
			return false;
		}
		m_pScene->SetRange(sHTitle, sVTitle, dXMin, dXMax, dYMin, dYMax, dCMin, dCMax);

		double dSZ = ::g_dInvalidData, dEZ = ::g_dInvalidData;
		for (i = 0; i < vecIDX.size(); i++)
		{
			CXButtonColorEdit *pCButton = (CXButtonColorEdit *)ui.tableWidget->cellWidget(vecIDX[i], 2);
			QColor penColor = pCButton->GetColor();
			QComboBox *pSizeComboBox = (QComboBox *)ui.tableWidget->cellWidget(vecIDX[i], 3);
			int iSize = pSizeComboBox->currentText().toInt();
			QComboBox *pShapeComboBox = (QComboBox *)ui.tableWidget->cellWidget(vecIDX[i], 4);
			int iShape = pShapeComboBox->currentIndex();

			if (m_iDLType == 1)
			{
				QLineEdit *pLE1 = (QLineEdit *)ui.tableWidget->cellWidget(vecIDX[i], m_sListCName.size() - 2);
				dSZ = pLE1->text().toDouble();
				QLineEdit *pLE2 = (QLineEdit *)ui.tableWidget->cellWidget(vecIDX[i], m_sListCName.size() - 1);
				dEZ = pLE2->text().toDouble();
			}
			else if (m_iDLType == 2)
			{
				QLabel *pLabel= (QLabel *)ui.tableWidget->cellWidget(vecIDX[i], 1);
				dSZ = pTops->GetOneRecord(pLabel->text(), sTTops);
				dEZ = pTops->GetOneRecord(pLabel->text(), sBTops);
			}

			if (!m_bColorAxis)
			{
				pCButton = (CXButtonColorEdit *)ui.tableWidget->cellWidget(vecIDX[i], 5);
				QColor fillColor = pCButton->GetColor();
				m_pScene->CreateItem(vecCurves[3 * i], vecCurves[3 * i + 1], penColor, fillColor, iSize, iShape, 0, dSZ, dEZ);
			}
			else
				m_pScene->CreateItem(vecCurves[3 * i], vecCurves[3 * i + 1], vecCurves[3 * i + 2], penColor, iSize, iShape, 0, dSZ, dEZ);
		}
	}
	else
	{
		QList<CXObject *> listH = ::GetProject()->GetChildren(EX3DHorizon, true);
		QList<CXObject *> listAH = ::GetProject()->GetChildren(EX3DHorizonAtt, true);
		CXObject *pHObj = NULL, *pVObj = NULL;
		int iIDX = ui.comboBoxX->currentIndex();
		if (iIDX < listH.size())
			pHObj = listH.at(iIDX);
		else
			pHObj = listAH.at(iIDX - listH.size());
		iIDX = ui.comboBoxY->currentIndex();
		if (iIDX < listH.size())
			pVObj = listH.at(iIDX);
		else
			pVObj = listAH.at(iIDX - listH.size());

		pHObj->GetDataRange(dXMin, dXMax);
		pVObj->GetDataRange(dYMin, dYMax);
		m_pScene->SetRange(pHObj->GetObjectName(), pVObj->GetObjectName(), dXMin, dXMax, dYMin, dYMax, dCMin, dCMax);

		CXButtonColorEdit *pCButton = (CXButtonColorEdit *)ui.tableWidget->cellWidget(0, 0);
		QColor penColor = pCButton->GetColor();
		pCButton = (CXButtonColorEdit *)ui.tableWidget->cellWidget(0, 2);
		QColor fillColor = pCButton->GetColor();
		QComboBox *pSizeComboBox = (QComboBox *)ui.tableWidget->cellWidget(0, 1);
		int iSize = pSizeComboBox->currentText().toInt();
		QComboBox *pShapeComboBox = (QComboBox *)ui.tableWidget->cellWidget(0, 3);
		int iShape = pShapeComboBox->currentIndex();

		m_pScene->CreateItem(pHObj, pVObj, penColor, fillColor, iSize, iShape, ui.comboBoxResample->currentIndex());
	}

	return true;
}

void XDlgCPSetting::accept()
{
	if (slotApply())
		QDialog::accept();
}