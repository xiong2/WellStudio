#include <qmessagebox.h>
#include "xpagegsinversion1.h"
#include "xparametersgsinversion.h"
#include "xglobal.h"
#include "xlfmgeometry.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xtemplate.h"
#include "xwell.h"

CXPageGSInversion1::CXPageGSInversion1(CXParametersGSInversion *pPara, QWidget *parent)
	: QWizardPage(parent)
{
	ui.setupUi(this);
	m_pPara = pPara;
}

CXPageGSInversion1::~CXPageGSInversion1()
{

}

void CXPageGSInversion1::initializePage()
{
	int i;
	CXLFMGeometry *pLFM = dynamic_cast<CXLFMGeometry *>(::GetObjectByID(m_pPara->GetSMID()));
	if (!pLFM)
		return;

	//	Zone table.
	ui.tableWidgetSM->setColumnWidth(0, 80);
	ui.tableWidgetSM->setColumnWidth(1, 200);
	ui.tableWidgetSM->setColumnWidth(2, 80);

	QStringList sListZone = pLFM->GetZoneNameList();
	int iNumZones = sListZone.size();
	ui.tableWidgetSM->setRowCount(iNumZones);
	for (i = 0; i < iNumZones; i++)
	{
		QCheckBox *pCheckBox = new QCheckBox;
		pCheckBox->setChecked(true);
		ui.tableWidgetSM->setCellWidget(i, 0, pCheckBox);

		connect(pCheckBox, SIGNAL(clicked()), this, SLOT(slotSelectZone()));

		ui.tableWidgetSM->setItem(i, 1, new QTableWidgetItem(sListZone[i]));

		pCheckBox = new QCheckBox;
		pCheckBox->setChecked(true);
		ui.tableWidgetSM->setCellWidget(i, 2, pCheckBox);
	}

	//	Output range.
	CXSeismicUTMTool utm = pLFM->GetUTM();
	ui.inlineRange->SetSliderName("Inline range:");
	ui.inlineRange->SetRangeAndPrecision(utm.GetFirstInline(), utm.GetLastInline(), utm.GetInlineIncrement());
	ui.crosslineRange->SetSliderName("Crossline range:");
	ui.crosslineRange->SetRangeAndPrecision(utm.GetFirstCrossline(), utm.GetLastCrossline(), utm.GetCrosslineIncrement());

	connect(ui.pushButtonQCSection, SIGNAL(clicked()), this, SLOT(slotSetSection()));

	// Wells table.
	ui.tableWidgetWells->setColumnWidth(0, 80);
	ui.tableWidgetWells->setColumnWidth(1, 160);
	CXObject *pWFolder = ::GetRootObjectFolder(EXWellFolder);
	QList<CXObject *> listWells = pWFolder->GetChildren(EXWell, true);

	//	Only wells with TD curves could be used.
	int iNumWells = listWells.size();
	for (i = iNumWells - 1; i >= 0; i--)
	{
		CXWell *pWell = (CXWell *)listWells[i];
		if (!pWell->GetWellTD())
			listWells.removeAt(i);
	}

	ui.tableWidgetWells->setRowCount(listWells.size());
	for (i = 0; i < listWells.size(); i++)
	{
		QCheckBox *pCheckBox = new QCheckBox;
		pCheckBox->setChecked(false);
		ui.tableWidgetWells->setCellWidget(i, 0, pCheckBox);

		connect(pCheckBox, SIGNAL(clicked()), this, SLOT(slotSelectWell()));

		ui.tableWidgetWells->setItem(i, 1, new QTableWidgetItem(listWells[i]->GetObjectName()));
	}
	m_listSelectWells.clear();

	//	Curves
	CXTemplate *pZpTemp = CXTemplate::GetTemplate("PIMP");
	if (!pZpTemp)
	{
		QMessageBox::warning(NULL, "Geostatistical Inversion", "P-wave impedance template is not available!");
	}
	else
		m_arrayCTmpID[0] = pZpTemp->GetID();

	CXTemplate *pVpVsTemp = CXTemplate::GetTemplate("Vp/Vs");
	if (!pVpVsTemp)
	{
		QMessageBox::warning(NULL, "Geostatistical Inversion", "Vp/Vs template is not available!");
	}
	else
		m_arrayCTmpID[1] = pVpVsTemp->GetID();

	CXTemplate *pRhoTemp = CXTemplate::GetTemplate("RHOB");
	if (!pRhoTemp)
	{
		QMessageBox::warning(NULL, "Geostatistical Inversion", "RHOB template is not available!");
	}
	else
		m_arrayCTmpID[2] = pRhoTemp->GetID();

	connect(ui.comboBoxContinuous, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSelectCProperty(int)));
	connect(ui.checkBox, SIGNAL(clicked()), this, SLOT(slotSetFitPrior()));
	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSelectFitPrior(int)));
}

bool CXPageGSInversion1::validatePage()
{
	//	Selected zones.
	std::vector<unsigned int> vecZoneIDX = m_pPara->GetVecZoneIDX();
	std::vector<bool> vecZoneRes = m_pPara->GetVecZoneReservoir();
	vecZoneIDX.clear();
	vecZoneRes.clear();
	unsigned int i, iNumZones = ui.tableWidgetSM->rowCount();
	for (i = 0; i < iNumZones; i++)
	{
		QCheckBox *pCB = (QCheckBox *)ui.tableWidgetSM->cellWidget(i, 0);
		if (!pCB->isChecked())
			continue;

		pCB = (QCheckBox *)ui.tableWidgetSM->cellWidget(i, 2);
		vecZoneIDX.push_back(i);
		vecZoneRes.push_back(pCB->isChecked());
	}
	
	if (vecZoneIDX.empty())
	{
		QMessageBox::warning(NULL, "Geostatistical Inversion", "No zone selected!");
		return false;
	}

	m_pPara->SetVecZoneIDX(vecZoneIDX);
	m_pPara->SetVecZoneReservoir(vecZoneRes);

	//	Output plane
	m_pPara->SetStartInline(ui.inlineRange->GetMinValue());
	m_pPara->SetEndInline(ui.inlineRange->GetMaxValue());
	m_pPara->SetStartXline(ui.crosslineRange->GetMinValue());
	m_pPara->SetEndXline(ui.crosslineRange->GetMaxValue());

	if (m_pPara->GetQCSection().isNull())
	{
		QMessageBox::warning(NULL, "Geostatistical Inversion", "No QC Section selected!");
		return false;
	}

	return true;
}

void CXPageGSInversion1::slotSelectZone()
{
	QCheckBox *pCB = (QCheckBox *)sender();

	int i, iNumZones = ui.tableWidgetSM->rowCount();
	for (i = 0; i < iNumZones; i++)
	{
		if (ui.tableWidgetSM->cellWidget(i, 0) != pCB)
			continue;

		if (pCB->isChecked())
		{
			ui.tableWidgetSM->cellWidget(i, 2)->setDisabled(false);
		}
		else
		{
			ui.tableWidgetSM->cellWidget(i, 2)->setDisabled(true);
		}

		break;
	}
}

void CXPageGSInversion1::slotSelectWell()
{
	QCheckBox *pCB = (QCheckBox *)sender();
	CXObject *pWFolder = ::GetRootObjectFolder(EXWellFolder);
	QList<CXObject *> listWells = pWFolder->GetChildren(EXWell, true);

	int i, iNumWells = ui.tableWidgetWells->rowCount();
	for (i = 0; i < iNumWells; i++)
	{
		if (ui.tableWidgetWells->cellWidget(i, 0) != pCB)
			continue;

		if (pCB->isChecked())
		{
			if (!m_listSelectWells.contains(listWells[i]))
				m_listSelectWells << listWells[i];
		}
		else
		{
			if (m_listSelectWells.contains(listWells[i]))
				m_listSelectWells.removeOne(listWells[i]);
		}

		updateCurveCandidates();

		break;
	}
}

void CXPageGSInversion1::slotSetSection()
{
	CXLFMGeometry *pLFM = dynamic_cast<CXLFMGeometry *>(::GetObjectByID(m_pPara->GetSMID()));

	CXObject *pCurObj = ::GetCurrentObject();
	if (pCurObj->GetObjectType() == EXSeismicSection)
	{
		CXSeismicSection* pSection = (CXSeismicSection *)pCurObj;
		if (pSection->GetSurveyID() != pLFM->GetSurveyID()
			|| (pSection->GetSectionType() != eInlineSection && pSection->GetSectionType() != eCrosslineSection))
		{
			QApplication::beep();
			return;
		}

		ui.lineEditQCSection->setText(pSection->GetObjectName());
		m_pPara->SetQCSection(pSection->GetObjectID());
	}
	else if (pCurObj->GetObjectType() == EXRandomSection)
	{
		CXSeismicRandomSection *pSection = (CXSeismicRandomSection *)pCurObj;
		if (pSection->GetSurveyID() != pLFM->GetSurveyID())
		{
			QApplication::beep();
			return;
		}

		ui.lineEditQCSection->setText(pSection->GetObjectName());
		m_pPara->SetQCSection(pSection->GetObjectID());
	}
	else
		QApplication::beep();
}

void CXPageGSInversion1::slotSelectCProperty(int iIDX)
{
	if (iIDX == 0)
	{
		ui.labelContinuousLog1->setText("Zp");
		ui.labelContinuousLog1->setText("Vp/Vs");

		CXTemplate *pZpTemp = CXTemplate::GetTemplate("PIMP");
		if (!pZpTemp)
		{
			QMessageBox::warning(NULL, "Geostatistical Inversion", "P-wave impedance template is not available!");
		}
		else
			m_arrayCTmpID[0] = pZpTemp->GetID();

		CXTemplate *pVpVsTemp = CXTemplate::GetTemplate("Vp/Vs");
		if (!pVpVsTemp)
		{
			QMessageBox::warning(NULL, "Geostatistical Inversion", "Vp/Vs template is not available!");
		}
		else
			m_arrayCTmpID[1] = pVpVsTemp->GetID();
	}
	else if (iIDX == 1)
	{
		ui.labelContinuousLog1->setText("Vp");
		ui.labelContinuousLog1->setText("Vs");

		//CXTemplate *pZpTemp = CXTemplate::GetTemplate("PIMP");
		//if (!pZpTemp)
		//{
		//	QMessageBox::warning(NULL, "Geostatistical Inversion", "P-wave impedance template is not available!");
		//}
		//else
		//	m_arrayCTmpID[0] = pZpTemp->GetID();

		//CXTemplate *pVpVsTemp = CXTemplate::GetTemplate("Vp/Vs");
		//if (!pVpVsTemp)
		//{
		//	QMessageBox::warning(NULL, "Geostatistical Inversion", "Vp/Vs template is not available!");
		//}
		//else
		//	m_arrayCTmpID[1] = pVpVsTemp->GetID();
	}
	else if (iIDX == 2)
	{
		ui.labelContinuousLog1->setText("Zp");
		ui.labelContinuousLog1->setText("Zs");
	}

	updateCurveCandidates();
}

void CXPageGSInversion1::slotSetFitPrior()
{
	if (ui.checkBox->isChecked())
	{
		ui.comboBox->setDisabled(false);
	}
	else
	{
		ui.comboBox->setDisabled(true);
	}
}

void CXPageGSInversion1::slotSelectFitPrior(int iIDX)
{
	if (iIDX == 2)
	{
		ui.labelNumBins->setDisabled(false);
		ui.spinBox->setDisabled(false);
	}
	else
	{
		ui.labelNumBins->setDisabled(true);
		ui.spinBox->setDisabled(true);
	}
}

void CXPageGSInversion1::updateCurveCandidates()
{
	int i, j;
	ui.comboBoxDiscrete->clear();
	ui.comboBoxContinuousLog1->clear();
	ui.comboBoxContinuousLog2->clear();
	ui.comboBoxContinuousLog3->clear();

	if(m_listSelectWells.isEmpty())
		return;

	unsigned int iDisTmpID = CXTemplate::GetTemplate("LITHOLOGY")->GetID();
	QStringList sListDisCurve, sListCCurve0, sListCCurve1, sListCCurve2;

	//	Initialize the candidates according to the 1st well.
	CXObject *pWell = m_listSelectWells.first();
	QList<CXObject *> listCurves = pWell->GetChildren(EXWellCurve);
	foreach(CXObject *pCurve, listCurves)
	{
		if (pCurve->GetTemplateID() == iDisTmpID)
			sListDisCurve << pCurve->GetObjectName();
		if (pCurve->GetTemplateID() == m_arrayCTmpID[0])
			sListCCurve0 << pCurve->GetObjectName();
		if (pCurve->GetTemplateID() == m_arrayCTmpID[1])
			sListCCurve1 << pCurve->GetObjectName();
		if (pCurve->GetTemplateID() == m_arrayCTmpID[2])
			sListCCurve2 << pCurve->GetObjectName();
	}

	for (i = 1; i < m_listSelectWells.size(); i++)
	{
		for (j = sListDisCurve.size() - 1; j >= 0; j--)
		{
			CXObject *pCh = m_listSelectWells[i]->GetChild(sListDisCurve[j], EXWellCurve);
			if (!pCh || pCh->GetTemplateID() != iDisTmpID)
			{
				sListDisCurve.removeAt(j);
			}
		}

		for (j = sListCCurve0.size() - 1; j >= 0; j--)
		{
			CXObject *pCh = m_listSelectWells[i]->GetChild(sListCCurve0[j], EXWellCurve);
			if (!pCh || pCh->GetTemplateID() != m_arrayCTmpID[0])
			{
				sListCCurve0.removeAt(j);
			}
		}

		for (j = sListCCurve1.size() - 1; j >= 0; j--)
		{
			CXObject *pCh = m_listSelectWells[i]->GetChild(sListCCurve1[j], EXWellCurve);
			if (!pCh || pCh->GetTemplateID() != m_arrayCTmpID[1])
			{
				sListCCurve1.removeAt(j);
			}
		}

		for (j = sListCCurve2.size() - 1; j >= 0; j--)
		{
			CXObject *pCh = m_listSelectWells[i]->GetChild(sListCCurve2[j], EXWellCurve);
			if (!pCh || pCh->GetTemplateID() != m_arrayCTmpID[2])
			{
				sListCCurve2.removeAt(j);
			}
		}
	}

	if (!sListDisCurve.empty())
		ui.comboBoxDiscrete->addItems(sListDisCurve);
	if (!sListCCurve0.empty())
		ui.comboBoxContinuousLog1->addItems(sListCCurve0);
	if (!sListCCurve1.empty())
		ui.comboBoxContinuousLog2->addItems(sListCCurve1);
	if (!sListCCurve2.empty())
		ui.comboBoxContinuousLog3->addItems(sListCCurve2);
}