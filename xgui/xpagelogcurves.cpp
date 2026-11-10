#include <qcombobox.h>
#include <qradiobutton.h>
#include <qmessagebox.h>
#include "xpagelogcurves.h"
#include "xwelllogasciifile.h"
#include "xtemplate.h"
#include "xunit.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "xwellcurvealias.h"
#include "xtree.h"
#include "xglobal.h"
#include "xproject.h"
#include "xgeneralfolder.h"

CXPageLogCurves::CXPageLogCurves(CXWellLogASCIIFile* pLogFile, QWidget *parent)
	: QWizardPage(parent)
{
	ui.setupUi(this);

	m_pLogFile = pLogFile;
	QStringList sListHHeader;
	sListHHeader << "Depth Curve" << "Curve Name" << "Curve Template" << "Input unit" << "Project Unit";

	ui.tableWidget->setColumnCount(5);
	ui.tableWidget->setHorizontalHeaderLabels(sListHHeader);
	ui.tableWidget->setColumnWidth(0, 100);
	ui.tableWidget->setColumnWidth(1, 120);
	ui.tableWidget->setColumnWidth(2, 160);
	ui.tableWidget->setColumnWidth(3, 120);
	ui.tableWidget->setColumnWidth(4, 120);
}

void CXPageLogCurves::initializePage()
{
	int i, j, iCount = 0;
	QStringList strChosedList = m_pLogFile->GetChosenColumns();

	ui.tableWidget->setRowCount(strChosedList.size());
	for (i = 0; i < strChosedList.size(); i++)
	{
		if (strChosedList[i] == "Do not import")
			continue;

		//	1st column is the radio box.
		QRadioButton *pRadioButton = new QRadioButton;
		ui.tableWidget->setCellWidget(iCount, 0, pRadioButton);
		connect(pRadioButton, SIGNAL(toggled(bool)), this, SLOT(slotSelectDepth(bool)));

		//	2nd column is the curve name.
		ui.tableWidget->setItem(iCount, 1, new QTableWidgetItem(strChosedList[i]));

		//	3rd column is the template combo box.
		QComboBox *pCBTemplate = new QComboBox;
		pCBTemplate->addItems(CXTemplate::GetAllTemplates());
		CXTemplate *pTemplate = CXTemplate::GetTemplate(strChosedList[i]);

		//	The depth?
		if (pTemplate->GetName() == "MD" || pTemplate->GetName() == "TVD")
		{
			//	In case its TVD.
			pTemplate = CXTemplate::GetTemplate("MD");
			pRadioButton->setChecked(true);
		}

		int iIDX = pCBTemplate->findText(pTemplate->GetName());
		pCBTemplate->setCurrentIndex(iIDX);
		ui.tableWidget->setCellWidget(iCount, 2, pCBTemplate);

		//	Add slot to the template combo box.
		connect(pCBTemplate, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeTemplate(int)));

		//	4th column is the input unit.
		QString sPrjUnit = pTemplate->GetUnit();
		QStringList sListTmpUnit = CXUnit::GetAllUnits(CXUnit::GetUnitType(sPrjUnit));
		if (sListTmpUnit.size() == 1)
			ui.tableWidget->setItem(iCount, 3, new QTableWidgetItem(sPrjUnit));
		else if (sListTmpUnit.size() > 1)
		{
			QComboBox *pCBUnit = new QComboBox;
			pCBUnit->addItems(sListTmpUnit);
			ui.tableWidget->setCellWidget(iCount, 3, pCBUnit);

			int iIDX = pCBUnit->findText(pTemplate->GetUnit(), Qt::MatchFixedString);
			if (iIDX != -1)
				pCBUnit->setCurrentIndex(iIDX);
		}

		//	5th column is the project unit.
		ui.tableWidget->setItem(iCount, 4, new QTableWidgetItem(pTemplate->GetUnit()));

		iCount++;
	}
	ui.tableWidget->setRowCount(iCount);
}

void CXPageLogCurves::slotChangeTemplate(int)
{
	//	First we should know which row's template changed.
	QComboBox *pCBTemplate = dynamic_cast<QComboBox *>(sender());
	if (pCBTemplate)
	{
		for (int i = 0; i<ui.tableWidget->rowCount(); i++)
		{
			if (pCBTemplate == ui.tableWidget->cellWidget(i, 2))
			{
				//	Now according the template, change the unit.
				CXTemplate *pTemplate = CXTemplate::GetTemplate(pCBTemplate->currentText());

				QString sPrjUnit = pTemplate->GetUnit();
				QStringList sListTmpUnit = CXUnit::GetAllUnits(CXUnit::GetUnitType(sPrjUnit));
				if (sListTmpUnit.size() == 1)
					ui.tableWidget->setItem(i, 3, new QTableWidgetItem(sPrjUnit));
				else if (sListTmpUnit.size() > 1)
				{
					QComboBox *pCBUnit = new QComboBox;
					pCBUnit->addItems(sListTmpUnit);
					ui.tableWidget->setCellWidget(i, 3, pCBUnit);
					pCBUnit->setCurrentIndex(0);
				}

				ui.tableWidget->setItem(i, 4, new QTableWidgetItem(sPrjUnit));
			}
		}
	}
}

void CXPageLogCurves::slotSelectDepth(bool bChecked)
{
	if (!bChecked)
		return;

	//	First we should know which row's button checked.
	QRadioButton *pRButton = dynamic_cast<QRadioButton *>(sender());
	if (pRButton)
	{
		for (int i = 0; i < ui.tableWidget->rowCount(); i++)
		{
			if (pRButton == ui.tableWidget->cellWidget(i, 0))
			{
				QComboBox *pCBTemplate = dynamic_cast<QComboBox *>(ui.tableWidget->cellWidget(i, 2));
				if (pCBTemplate)
					pCBTemplate->setCurrentText("MD");
			}
		}
	}
}

bool CXPageLogCurves::validatePage()
{
	//	Initialize.
	QStringList& sListTemplate = m_pLogFile->GetTemplateList();
	QList<float>& fListRatio = m_pLogFile->GetAttributeUnitRatio();
	sListTemplate.clear();
	fListRatio.clear();

	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		QRadioButton *pRButton = dynamic_cast<QRadioButton *>(ui.tableWidget->cellWidget(i, 0));			
		QComboBox *pCBTemplate = dynamic_cast<QComboBox *>(ui.tableWidget->cellWidget(i, 2));			
		if (!pCBTemplate || !pRButton)
			return false;

		//	Is this curve the depth one?
		if (pRButton->isChecked())
			m_pLogFile->SetDepthID(i);

		sListTemplate << pCBTemplate->currentText();

		float fRatio = 1.;
		pCBTemplate = dynamic_cast<QComboBox *>(ui.tableWidget->cellWidget(i, 3));
		if (pCBTemplate)
		{
			QString sInputUnit = pCBTemplate->currentText();
			QString sProjectUnit = ui.tableWidget->item(i, 4)->text();
			fRatio = CXUnit::GetConvertRatio(sInputUnit, sProjectUnit);
		}
		fListRatio << fRatio;
	}

	return true;
}