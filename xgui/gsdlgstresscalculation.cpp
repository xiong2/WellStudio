#include <qmessagebox.h>
#include "xcheckboxwidget.h"
#include "x3dhorizon.h"
#include "gsstressmap.h"
#include "xglobal.h"
#include "xproject.h"
#include "gsdlgstresscalculation.h"
#include "gsthreadstresscalculation.h"
#include "xdlgcalculatingprogress.h"
#include "gsthreadutminterpolation.h"
#include <memory>
#include "gsstressparameters.h"
#include "gsthreadstressinterpolation.h"

GSDlgStressCalculation::GSDlgStressCalculation(CXObject *pIsopach, QWidget *parent)
	: QDialog(parent)
{
	m_pIsopach = pIsopach;
	ui.setupUi(this);
	initialUI();
}

GSDlgStressCalculation::~GSDlgStressCalculation()
{
}

void GSDlgStressCalculation::initialUI()
{
	QStringList sListSurvey;
	if (m_pIsopach)
	{
		ui.comboBoxSurvey->setDisabled(true);
	}
	else
	{
		QList<CXObject *> listSurvey = GetProject()->GetChildren(EX3DSurvey);
		foreach(CXObject *pSurvey, listSurvey)
		{
			sListSurvey << pSurvey->GetObjectName();
		}
		ui.comboBoxSurvey->addItems(sListSurvey);
	}

	ui.tableWidget->setColumnWidth(0, 80);
	ui.tableWidget->setColumnWidth(1, 200);

	refreshTable(0);

	ui.groupBoxShape2->setChecked(false);
	ui.groupBoxShape3->setChecked(false);

	connect(ui.comboBoxSurvey, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &GSDlgStressCalculation::refreshTable);
	connect(ui.checkBoxAuto, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), this, &GSDlgStressCalculation::slotCheckBox);
	connect(ui.checkBoxAuto_2, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), this, &GSDlgStressCalculation::slotCheckBox);
	connect(ui.checkBoxAuto_3, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), this, &GSDlgStressCalculation::slotCheckBox);
	connect(ui.pushButtonSAll, &QPushButton::clicked, this, &GSDlgStressCalculation::slotButtonClicked);
	connect(ui.pushButtonDAll, &QPushButton::clicked, this, &GSDlgStressCalculation::slotButtonClicked);
}

void GSDlgStressCalculation::refreshTable(int iSurveyID)
{
	QList<CXObject *> listSurvey = GetProject()->GetChildren(EX3DSurvey);
	QList<CXObject *> listHFolder = listSurvey[iSurveyID]->GetChildren(EXGSFolderHorizon, true);

	m_listIsopach.clear();
	if (m_pIsopach)
	{
		m_listIsopach << m_pIsopach;
	}
	else
	{
		foreach(CXObject *pHFolder, listHFolder)
		{
			QList<CXObject *> listChildren = pHFolder->GetChildren(EXGS3DHorizonIso);
			if (!listChildren.isEmpty())
				m_listIsopach << listChildren.first();
		}
	}

	ui.tableWidget->setRowCount(m_listIsopach.count());
	for (int i = 0; i < m_listIsopach.count(); i++)
	{
		//	1st column is the check box.
		CXCheckBoxWidget *pCheckBox = new CXCheckBoxWidget;
		pCheckBox->SetChecked(true);
		ui.tableWidget->setCellWidget(i, 0, pCheckBox);

		//	2nd column is the isopach name.
		QTableWidgetItem *pWItem = new QTableWidgetItem(m_listIsopach[i]->GetObjectName());
		pWItem->setIcon(QIcon(GetIconPath() + "Horizon4.png"));
		ui.tableWidget->setItem(i, 1, pWItem);
	}

}

void GSDlgStressCalculation::slotButtonClicked()
{
	bool bSele = sender() == ui.pushButtonSAll;
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		CXCheckBoxWidget *pCheckBox = (CXCheckBoxWidget *)ui.tableWidget->cellWidget(i, 0);
		pCheckBox->SetChecked(bSele);
	}
}

void GSDlgStressCalculation::slotCheckBox(int iState)
{
	if (sender() == ui.checkBoxAuto)
	{
		ui.labelHeight->setEnabled(iState == 0);
		ui.spinBoxHeight->setEnabled(iState == 0);
		ui.labelRadius->setEnabled(iState == 0);
		ui.spinBoxRadius->setEnabled(iState == 0);
	}
	else if (sender() == ui.checkBoxAuto_2)
	{
		ui.labelHeight_2->setEnabled(iState == 0);
		ui.spinBoxHeight_2->setEnabled(iState == 0);
		ui.labelRadius_2->setEnabled(iState == 0);
		ui.spinBoxRadius_2->setEnabled(iState == 0);
	}
	else if (sender() == ui.checkBoxAuto_3)
	{
		ui.labelHeight_3->setEnabled(iState == 0);
		ui.spinBoxHeight_3->setEnabled(iState == 0);
		ui.labelRadius_3->setEnabled(iState == 0);
		ui.spinBoxRadius_3->setEnabled(iState == 0);
	}
}

void GSDlgStressCalculation::accept()
{
	//	To construct the original isopaches first.
	int i;
	QList<CX3DHorizon *> listHor;
	for (i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		CXCheckBoxWidget *pCheckBox = (CXCheckBoxWidget *)ui.tableWidget->cellWidget(i, 0);
		if (pCheckBox->IsChecked())
			listHor << (CX3DHorizon *)m_listIsopach[i];
	}

	if (listHor.isEmpty())
	{
		QMessageBox::warning(NULL, "Stress Calculation", "No isopach map selected!");
		return;
	}

	if (!ui.checkBoxFaults->isChecked() && !ui.groupBoxShape1->isChecked()
		&& !ui.groupBoxShape2->isChecked() && !ui.groupBoxShape3->isChecked())
	{
		QMessageBox::warning(NULL, "Stress Calculation", "No faults, anticline, nor syncline be selected!");
		return;
	}

	GSStressParameters paras;

	//	Shape1
	if (ui.groupBoxShape1->isChecked())
	{
		if (ui.radioButtonAnti->isChecked())
			paras.m_iAnti[0] = 1;
		else
			paras.m_iAnti[0] = 2;

		paras.m_dCThreshold[0] = ui.doubleSpinBox->value();
		paras.m_dLThreshold[0] = ui.lineEditLength->text().toFloat();

		if (ui.checkBoxAuto->isChecked())
		{
			paras.m_dTHeight[0] = -1;
			paras.m_dSRadius[0] = -1;
		}
		else
		{
			paras.m_dTHeight[0] = ui.spinBoxHeight->value();
			paras.m_dSRadius[0] = ui.spinBoxRadius->value();
		}
	}
	else
	{
		paras.m_iAnti[0] = 0;
	}

	//	Shape2
	if (ui.groupBoxShape2->isChecked())
	{
		if (ui.radioButtonAnti_2->isChecked())
			paras.m_iAnti[1] = 1;
		else
			paras.m_iAnti[1] = 2;

		paras.m_dCThreshold[1] = ui.doubleSpinBox_2->value();
		paras.m_dLThreshold[1] = ui.lineEditLength_2->text().toFloat();

		if (ui.checkBoxAuto_2->isChecked())
		{
			paras.m_dTHeight[1] = -1;
			paras.m_dSRadius[1] = -1;
		}
		else
		{
			paras.m_dTHeight[1] = ui.spinBoxHeight_2->value();
			paras.m_dSRadius[1] = ui.spinBoxRadius_2->value();
		}
	}
	else
	{
		paras.m_iAnti[1] = 0;
	}

	//	Shape3
	if (ui.groupBoxShape3->isChecked())
	{
		if (ui.radioButtonAnti_3->isChecked())
			paras.m_iAnti[2] = 1;
		else
			paras.m_iAnti[2] = 2;

		paras.m_dCThreshold[2] = ui.doubleSpinBox_3->value();
		paras.m_dLThreshold[2] = ui.lineEditLength_3->text().toFloat();

		if (ui.checkBoxAuto_3->isChecked())
		{
			paras.m_dTHeight[2] = -1;
			paras.m_dSRadius[2] = -1;
		}
		else
		{
			paras.m_dTHeight[2] = ui.spinBoxHeight_3->value();
			paras.m_dSRadius[2] = ui.spinBoxRadius_3->value();
		}
	}
	else
	{
		paras.m_iAnti[2] = 0;
	}

	//	Merging parameters.
	if (ui.groupBoxMerge->isChecked())
	{
		paras.m_bMerge = true;
		paras.m_dMergeRatio = ui.doubleSpinBoxOverlap->value();
		paras.m_iMergeAngle = ui.spinBoxAngle->value();
	}
	else
	{
		paras.m_bMerge = false;
	}
	paras.m_bFaults = ui.checkBoxFaults->isChecked();

	//	Loop to calculate on each isopach.
	QList<GSStressMap *> listMap;
	bool bMapped = true;
	for (i = 0; i < listHor.size(); i++)
	{
		CXSeismicUTMTool utm(listHor[i]->GetUTM());
		utm.ChangeCellSize(utm.GetIInterval() / 2);
		QString sHName = listHor[i]->GetObjectName();
		sHName.replace("Iso", "StressMap");
		sHName = listHor[i]->GetParent()->GetUnallocatedName(sHName);
		GSStressMap *pSMap = new GSStressMap(utm, sHName, &paras);
		listMap << pSMap;

		GSThreadStressCalculation *pThread = new GSThreadStressCalculation(pSMap->GetParas());
		CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(pThread, this);

		pProgress->show();

		pThread->SetHorizon(listHor[i], pSMap);
		pThread->start();

		if (pProgress->exec() != QDialog::Accepted)
		{
			bMapped = false;
			break;
		}
	}

	if(bMapped)
	{

		for (GSStressMap *pMap : listMap)
		{
			CXSeismicUTMTool& utm = pMap->GetUTM();
			//	First generate stress inside capsules.
			QVector<double> vecStressPoints = pMap->CalculateStressInsideCapsules();
			if(vecStressPoints.isEmpty())
				continue;

			//	Then interpolate to the whole map.
			auto pThread = std::make_unique<GSThreadStressInterpolation>(utm, vecStressPoints, pMap);
			pThread->LockRead(pMap);
			pThread->SetObjectName(pMap->GetObjectName());

			auto pProgress = new CXDlgCalculatingProgress(pThread.get(), this);
			pProgress->show();
			pThread->start();

			if (pProgress->exec() == QDialog::Accepted)
			{
				float *pData = pMap->GetData();
				memcpy(pData, &pThread->GetResult()[0], utm.GetNI() * utm.GetNJ() * 2 * sizeof(float));
				pMap->SetModifiedFlag();
			}

			pThread->UnlockRead(pMap);
		}

		QDialog::accept();
	}
}