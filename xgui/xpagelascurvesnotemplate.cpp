#include <QFile>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include "xpagelascurvesnotemplate.h"
#include "xlaswisfile.h"
#include "xtemplate.h"
#include "xunit.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "xwellcurvealias.h"
#include "xtree.h"
#include "xglobal.h"
#include "xproject.h"
#include "xgeneralfolder.h"

CXPageLASCurvesNoTemplate::CXPageLASCurvesNoTemplate(QList<CXLasWisFile *> listLASFile, QStringList& sListMatchedWells, QWidget *parent)
	: m_sListMatchedWells(sListMatchedWells), QWizardPage(parent)
{
	ui.setupUi(this);
	m_bSelectAll = false;
	int i;
	for(i = 0; i < listLASFile.size(); i++)
	{
		m_listLASFile.append(listLASFile.at(i));
	}

	QStringList sListHHeader;
//  	if(::UsingChinese())
// 		sListHHeader<<GetTr("加载")<<GetTr("曲线名称")<<GetTr("曲线模板")<<GetTr("输入单位")<<GetTr("项目单位");
// 	else
		sListHHeader<<"Load"<<"Curve Name"<<"Import Type";
// 	m_ui.tableWidget->setColumnCount(5);
// 	m_ui.tableWidget->setHorizontalHeaderLabels(sListHHeader);
	ui.tableWidget->setColumnWidth(0, 50);
	ui.tableWidget->setColumnWidth(1, 120);
	ui.tableWidget->setColumnWidth(2, 160);
// 	m_ui.tableWidget->setColumnWidth(3, 120);
// 	m_ui.tableWidget->setColumnWidth(4, 120);
	

	bool b =connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotRefreshPreview(int)));
}

void CXPageLASCurvesNoTemplate::initializePage()
{
	QStringList sListItem, sListAllCurves, sListAllUnits;
	QList<CXTemplate *> listTemplates;
	int i, j, iCount = m_listLASFile.size();

	//	Reset the combo-box items.
	ui.comboBox->clear();
	for(i = 0; i < iCount; i++)
	{
		if(m_sListMatchedWells[i] != "NULL")
		{
			sListItem<<m_listLASFile.at(i)->GetFileName(true);

			//	Add curve information.
			QStringList& sListCurve = m_listLASFile.at(i)->GetCurveList();
			QStringList& sListUnit	= m_listLASFile.at(i)->GetUnitList();
			for(j = 0; j < sListCurve.size(); j++)
			{
				if(sListAllCurves.contains(sListCurve.at(j)))
					continue;

				sListAllCurves.append(sListCurve.at(j));
				listTemplates.append(CXTemplate::GetTemplate(sListCurve.at(j)));
				sListAllUnits<<sListUnit.at(j);
			}
		}
	}
	ui.comboBox->addItems(sListItem);

	//	Reset the file preview content.
	if(sListItem.size() > 0)
		slotRefreshPreview(0);

	//	Now populate the curves table widget.
	ui.tableWidget->setRowCount(sListAllCurves.size());
	for(i = 0; i < sListAllCurves.size(); i++)
	{
		//	1st column is the check box.
		QCheckBox *pCheckBox = new QCheckBox;
		pCheckBox->setChecked(true);
		ui.tableWidget->setCellWidget(i, 0, pCheckBox);

		//	2nd column is the curve name.
		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(sListAllCurves[i]));

		//	3rd column is the template combo box.
		QComboBox *pCBTemplate = new QComboBox;
		pCBTemplate->addItems(CXTemplate::GetAllTemplates());
		int iIDX = pCBTemplate->findText(listTemplates[i]->GetName());
		pCBTemplate->setCurrentIndex(iIDX);
		ui.tableWidget->setCellWidget(i, 2, pCBTemplate);

		//	Add slot to the template combo box.
		connect(pCBTemplate, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeTemplate(int)));

		//	4th column is the input unit.
		QString sPrjUnit = listTemplates[i]->GetUnit();
		QStringList sListTmpUnit = CXUnit::GetAllUnits(CXUnit::GetUnitType(sPrjUnit));
		if(sListTmpUnit.size() == 1)
			ui.tableWidget->setItem(i, 3, new QTableWidgetItem(sPrjUnit));
		else if(sListTmpUnit.size() > 1)
		{
			QComboBox *pCBUnit = new QComboBox;
			pCBUnit->addItems(sListTmpUnit);
			ui.tableWidget->setCellWidget(i, 3, pCBUnit);

			int iIDX = pCBUnit->findText(sListAllUnits[i], Qt::MatchFixedString);
			if(iIDX != -1)
				pCBUnit->setCurrentIndex(iIDX);
		}

		//	5th column is the project unit.
		ui.tableWidget->setItem(i, 4, new QTableWidgetItem(listTemplates[i]->GetUnit()));
	}
}

void CXPageLASCurvesNoTemplate::slotRefreshPreview(int iIDX)
{
	if(iIDX >= m_listLASFile.size() || iIDX < 0)
		return;

	QFile qFile(m_listLASFile.at(iIDX)->GetFileName());
	if(!qFile.open(QIODevice::ReadOnly))
		return;

	QApplication::setOverrideCursor( Qt::WaitCursor );

	QTextStream stream(&qFile);
	ui.textEdit->setPlainText(stream.readAll());
	qFile.close();

	QApplication::restoreOverrideCursor();
}

void CXPageLASCurvesNoTemplate::slotSelectAll()
{
	m_bSelectAll = !m_bSelectAll;
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidget->cellWidget(i, 0));
		if (pCheckBox)
		{
			pCheckBox->setChecked(m_bSelectAll);
		}
	}
}

bool CXPageLASCurvesNoTemplate::validatePage()
{
	int i, j, iRowCount = ui.tableWidget->rowCount();
	QStringList sListCurves;
	
	//	Check which curve be selected.
	for(i = 0; i < iRowCount; i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidget->cellWidget(i, 0));
		if(pCheckBox->isChecked())
		{
			sListCurves<<ui.tableWidget->item(i, 1)->text();
		}
	}

	if(sListCurves.size() == 0)
	{
 		if(::UsingChinese())
			QMessageBox::warning(NULL, "加载LAS文件", "没有选中曲线！");
		else
			QMessageBox::warning(NULL, "Import LAS Files", "No curve was selected!");

		return false;
	}

	QApplication::setOverrideCursor( Qt::WaitCursor );

	// Find the well folder, create one if not found.
	CXGeneralFolder *pWellFolder = (CXGeneralFolder *)::GetRootObjectFolder(EXWellFolder);

	//	Now Iterate each LAS file.
	for(i = 0; i < m_listLASFile.size(); i++)
	{
		if(m_sListMatchedWells[i] == "")
			continue;

		//	Is the well already exist?
		CXWell *pWell = m_listLASFile[i]->GetWell();
		CXWell *pTargetWell = (CXWell *)(pWellFolder->GetChild(m_sListMatchedWells[i]));
		if(!pTargetWell)
		{
			//	The well not exist in project, add the well to the project.
			pWellFolder->AddChild(pWell);
			::AddObjectEvent(pWell);
		}
		else
		{
			//	Well exist, merge them, copy attributes first.
			QStringList sListAtt = pWell->GetExistAttribute();
			for(j = 0; j < sListAtt.size(); j++)
			{
				pTargetWell->AddAttribute(sListAtt[j], pWell->GetAttribute(sListAtt[j]));
			}

			//	Then set range and step.
			double dStart, dStop;
			pWell->GetDepthRange(dStart, dStop);
			//pTargetWell->SetWellStep(pWell->GetWellStep());
			pTargetWell->ExpandWellRange(dStart, dStop, pWell->GetWellStep());

			delete pWell;
			pWell = pTargetWell;
			m_listLASFile[i]->SetWell(pWell);
		}

		//	Load the curves from the LAS file.
		QList<CXObject *> listCurves, listAlias;
		if(!m_listLASFile[i]->LoadCurves(sListCurves, listCurves))
			continue;

		//	To set the alias, template and unit for each curve.
		for(j = 0; j < listCurves.size(); j++)
		{
			CXWellCurve *pCurve = (CXWellCurve *)listCurves[j];
			int iIDX = sListCurves.indexOf(pCurve->GetObjectName());

			CXObject *pAlias = CXWellCurveAlias::GetAlias(pCurve->GetObjectName());
			listAlias<<pAlias;

			//	Template.
			QComboBox *pCB = (QComboBox *)ui.tableWidget->cellWidget(iIDX, 2);
			QString sTemplate = pCB->currentText();
			CXTemplate *pTemplate = CXTemplate::GetTemplate(sTemplate);
			pAlias->SetTemplateID(pTemplate->GetID());
			pCurve->SetAliasID(pAlias->GetObjectID());

			//	Unit.
			double dRatio = 1.;
			QString sCurUnit = "", sPrjUnit = "";
			if(ui.tableWidget->item(iIDX, 4))
				sPrjUnit = ui.tableWidget->item(iIDX, 4)->text();
			if(ui.tableWidget->item(iIDX, 3))
				sCurUnit= ui.tableWidget->item(iIDX, 3)->text();
			else
			{
				QComboBox *pCB = dynamic_cast<QComboBox *>(ui.tableWidget->cellWidget(iIDX, 3));
				if(pCB)
					sCurUnit = pCB->currentText();
			}
			if(sPrjUnit != "" && sCurUnit != "")
				dRatio = CXUnit::GetConvertRatio(sCurUnit, sPrjUnit);

			if(dRatio != 1)
			{
				double *pData = pCurve->GetData();
				unsigned int iPointNum = pCurve->GetPointNumber();

				for(int n = 0; n < iPointNum; n++)
				{
					if(pData[n] != g_dInvalidData)
						pData[n] *= dRatio;
				}
			}
		}

		int z;
		for (z = 0; z < listAlias.count(); z++)
		{
			listAlias[z]->AddEvent(EAdded);
		}
		for (z = 0; z < listCurves.count(); z++)
		{
			listCurves[z]->AddEvent(EAdded);
		}
		CXProcessEvent eventProcess;
		//::AddObjectEvent
		//CXTree::Instance().AddObjectsToTree(listAlias);
		//CXTree::Instance().AddObjectsToTree(listCurves);
	}

	QApplication::restoreOverrideCursor();

	return true;
}

void CXPageLASCurvesNoTemplate::slotChangeTemplate(int)
{
	//	First we should know which row's template changed.
	QComboBox *pCBTemplate = dynamic_cast<QComboBox *>(sender());
	if(pCBTemplate)
	{
		for(int i = 0; i<ui.tableWidget->rowCount(); i++)
		{
			if(pCBTemplate == ui.tableWidget->cellWidget(i, 2))
			{
				//	Now according the template, change the unit.
				CXTemplate *pTemplate = CXTemplate::GetTemplate(pCBTemplate->currentText());

				QString sPrjUnit = pTemplate->GetUnit();
				QStringList sListTmpUnit = CXUnit::GetAllUnits(CXUnit::GetUnitType(sPrjUnit));
				if(sListTmpUnit.size() == 1)
					ui.tableWidget->setItem(i, 3, new QTableWidgetItem(sPrjUnit));
				else if(sListTmpUnit.size() > 1)
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