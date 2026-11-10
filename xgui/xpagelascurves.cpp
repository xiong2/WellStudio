#include <QFile>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include "xpagelascurves.h"
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
#include "xwellpath.h"
#include "xwelltd.h"

CXPageLASCurves::CXPageLASCurves(QList<CXLasWisFile *> listLASFile, QStringList& sListMatchedWells, bool bLas, QWidget *parent)
	: m_sListMatchedWells(sListMatchedWells), QWizardPage(parent)
{
	ui.setupUi(this);
	m_bSelectAll = false;
	m_bLAS = bLas;

	int i;
	for(i = 0; i < listLASFile.size(); i++)
	{
		m_listLASFile.append(listLASFile.at(i));
	}

	QStringList sListHHeader;
 	if(::UsingChinese())
		sListHHeader << GetTr("加载") << GetTr("曲线名称") << GetTr("曲线模板") << GetTr("输入单位") << GetTr("项目单位") << GetTr("类型");
	else
		sListHHeader<<"Load"<<"Curve Name"<<"Curve Template"<<"Input unit"<<"Project Unit"<<"Tpye";
	ui.tableWidget->setColumnCount(6);
	ui.tableWidget->setHorizontalHeaderLabels(sListHHeader);
	ui.tableWidget->setColumnWidth(0, 50);
	ui.tableWidget->setColumnWidth(1, 120);
	ui.tableWidget->setColumnWidth(2, 160);
	ui.tableWidget->setColumnWidth(3, 120);
	ui.tableWidget->setColumnWidth(4, 120);
	ui.tableWidget->setColumnWidth(5, 120);
	
	if (m_bLAS)
	{
		bool b =connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotRefreshPreview(int)));
	}
	else
	{
		ui.groupBox_2->setVisible(false);
	}

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slotSelectAll()));
}

void CXPageLASCurves::initializePage()
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
		if (sListAllUnits[i] != "")
		{
			ui.tableWidget->setItem(i, 3, new QTableWidgetItem(sListAllUnits[i]));
		}
		else
		{
			QString sPrjUnit = listTemplates[i]->GetUnit();
			QStringList sListTmpUnit = CXUnit::GetAllUnits(CXUnit::GetUnitType(sPrjUnit));
			if (sListTmpUnit.size() == 1)
				ui.tableWidget->setItem(i, 3, new QTableWidgetItem(sPrjUnit));
			else if (sListTmpUnit.size() > 1)
			{
				QComboBox *pCBUnit = new QComboBox;
				pCBUnit->addItems(sListTmpUnit);
				ui.tableWidget->setCellWidget(i, 3, pCBUnit);

				int iIDX = pCBUnit->findText(sListAllUnits[i], Qt::MatchFixedString);
				if (iIDX != -1)
					pCBUnit->setCurrentIndex(iIDX);
				else
				{
					pCBUnit->setCurrentIndex(pCBUnit->findText(listTemplates[i]->GetUnit(), Qt::MatchFixedString));
				}
			}
		}

		//	5th column is the project unit.
		ui.tableWidget->setItem(i, 4, new QTableWidgetItem(listTemplates[i]->GetUnit()));

		//	6th column is the template combo box.
		QComboBox *pCBType = new QComboBox;
		QStringList lstType;
		lstType << ""<< "*time" << "*tvd" << "*dx" << "*dy" << "*x" << "*y"<<"*azi"<<"*dip";
		pCBType->addItems(lstType);
		ui.tableWidget->setCellWidget(i, 5, pCBType);
	}
}

void CXPageLASCurves::slotRefreshPreview(int iIDX)
{
	if (!m_bLAS)
		return;

	if(iIDX >= m_listLASFile.size() || iIDX < 0)
		return;

	QFile qFile(m_listLASFile.at(iIDX)->GetFileName());
	if(!qFile.open(QIODevice::ReadOnly))
		return;

	QApplication::setOverrideCursor( Qt::WaitCursor );

	QTextStream stream(&qFile);
	ui.textEdit->setPlainText(stream.read(10000));
	qFile.close();

	QApplication::restoreOverrideCursor();
}

void CXPageLASCurves::slotSelectAll()
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

bool CXPageLASCurves::validatePage()
{
	int i, j, iRowCount = ui.tableWidget->rowCount();
	QStringList sListSelectedCurves;
	QStringList sListTypes;
	QStringList sListTemplates;
	QVector<float>	fVecUnitRatio;
	
	//	Check which curve be selected.
	for(i = 0; i < iRowCount; i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidget->cellWidget(i, 0));
		if(pCheckBox->isChecked())
		{
			sListSelectedCurves << ui.tableWidget->item(i, 1)->text();
			QComboBox *pCB = (QComboBox *)ui.tableWidget->cellWidget(i, 5);
			sListTypes << pCB->currentText(); 
			pCB = (QComboBox *)ui.tableWidget->cellWidget(i, 2);
			sListTemplates << pCB->currentText();

			double dRatio = 1.;
			QString sCurUnit = "", sPrjUnit = "";
			if (ui.tableWidget->item(i, 4))
				sPrjUnit = ui.tableWidget->item(i, 4)->text();
			pCB = dynamic_cast<QComboBox *>(ui.tableWidget->cellWidget(i, 3));
			if (pCB)
				sCurUnit = pCB->currentText();
			else if (ui.tableWidget->item(i, 3))
				sCurUnit = ui.tableWidget->item(i, 3)->text();
			if (sPrjUnit != "" && sCurUnit != "")
				dRatio = CXUnit::GetConvertRatio(sCurUnit, sPrjUnit);
			fVecUnitRatio << dRatio;
		}
	}

	if(sListSelectedCurves.size() == 0)
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
			pWell->SetObjectName(m_sListMatchedWells[i]);
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
		if(!m_listLASFile[i]->LoadCurves(sListSelectedCurves, listCurves))
			continue;

		CXWellCurve* pDevXTrack = NULL;
		CXWellCurve* pDevYTrack = NULL;
		CXWellCurve* pAbsXTrack = NULL;
		CXWellCurve* pAbsYTrack = NULL;
		CXWellCurve* pTvdTrack = NULL;
		CXWellCurve* pDipTrack = NULL;
		CXWellCurve* pAziTrack = NULL;
		CXWellCurve* pTimeTrack2222 = NULL;
		QString strTimeUnit;
		//	To set the alias, template and unit for each curve.
		for(j = 0; j < listCurves.size(); j++)
		{
			CXWellCurve *pCurve = dynamic_cast<CXWellCurve *>(listCurves[j]);
			if (!pCurve)
				continue;

			int iIDX = sListSelectedCurves.indexOf((pCurve->GetObjectName()));
			if (iIDX == -1)
			{
				qDebug() << "Error!";
				QMessageBox::warning(NULL, "Import LAS Files", pCurve->GetObjectName() + " not found in the selected list!");
				return false;
			}

			CXObject *pAlias = CXWellCurveAlias::GetAlias(pCurve->GetObjectName());
			listAlias<<pAlias;

			//	Template.
			CXTemplate *pTemplate = CXTemplate::GetTemplate(sListTemplates[iIDX]);
			pAlias->SetTemplateID(pTemplate->GetID());
			pCurve->SetAliasID(pAlias->GetObjectID());

			//	Unit.

			float dRatio = fVecUnitRatio[iIDX];
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

			QString strType = sListTypes[iIDX];
			if (strType == "*tvd")
			{
				pTvdTrack = pCurve;
			}
			else if (strType == "*dx")
			{
				pDevXTrack = pCurve;
			}
			else if (strType == "*dy")
			{
				pDevYTrack = pCurve;
			}
			else if (strType == "*x")
			{
				pAbsXTrack = pCurve;
			}
			else if (strType == "*y")
			{
				pAbsYTrack = pCurve;
			}
			else if (strType == "*dip")
			{
				pDipTrack = pCurve;
			}
			else if (strType == "*azi")
			{
				pAziTrack = pCurve;
			}
			if (strType == "*time")
			{
				pTimeTrack2222 = pCurve;
				//if (sCurUnit.toLower() == "s")
				//{
				//	strTimeUnit = "s";
				//}
				//else
				//{
				//	strTimeUnit = "ms";
				//}
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

		//	Then set range and step.
		double dStart, dStop;
		pWell->GetDepthRange(dStart, dStop);
		//pTargetWell->SetWellStep(pWell->GetWellStep());
		pWell->ExpandWellRange(dStart, dStop, pWell->GetWellStep());
		pWell->updateTDWellPath( pTimeTrack2222,  pTvdTrack,
			pDevXTrack, pDevYTrack,
			pAbsXTrack, pAbsYTrack,
			pAziTrack,pDipTrack);


		CXProcessEvent eventProcess;
		//::AddObjectEvent
		//CXTree::Instance().AddObjectsToTree(listAlias);
		//CXTree::Instance().AddObjectsToTree(listCurves);
	}

	QApplication::restoreOverrideCursor();

	return true;
}

void CXPageLASCurves::slotChangeTemplate(int)
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