#include <qcheckbox.h>
#include <qcombobox.h>
#include <qmessagebox.h>
#include "xpagematchwells.h"
#include "xglobal.h"
#include "xproject.h"
#include "xwell.h"

CXPageMatchWells::CXPageMatchWells(QStringList sListWellInfo, QStringList& sListMatchedWells, QWidget *pParent)
	: m_sListMatchedWells(sListMatchedWells), QWizardPage(pParent)
{
	ui.setupUi(this);
	m_bSelectAll = false;
	int i, j;
	int iFileNumber = sListMatchedWells.size();
	ui.tableWidget->setRowCount(iFileNumber);
	ui.tableWidget->setColumnCount(10);

	QStringList sListHHeader;
 	if(::UsingChinese())
		sListHHeader<<GetTr("加载")<<GetTr("文件名")<<GetTr("文件中的井名")<<GetTr("文件中的UWI")<<GetTr("文件中的X坐标")<<GetTr("文件中的Y坐标")
			<<GetTr("目标井")<<GetTr("井的UWI")<<GetTr("井的X坐标")<<GetTr("井的Y坐标");
	else
		sListHHeader<<"Load"<<"File Name"<<"Well from File"<<"UWI from File"<<"X from File"<<"Y from File"
			<<"Destination Well"<<"Well UWI"<<"Well X"<<"Well Y";
	ui.tableWidget->setHorizontalHeaderLabels(sListHHeader);

	//	To get all exists wells.
	QStringList strListWells, strListWellsLower;
	QList<CXObject *> listWells;
	QList<CXObject *> listObjects = ::GetProject()->GetChildren(EXWellFolder);
	if(listObjects.size() == 1)
	{
		listWells = listObjects[0]->GetChildren(EXWell);

		for(i = 0; i < listWells.size(); i++)
		{
			strListWells << listWells[i]->GetObjectName();
			strListWellsLower << listWells[i]->GetObjectName().toLower();
		}
	}

	QStringList sListVHeader;
	for(i = 0; i < iFileNumber; i++)
	{
		sListVHeader<<QString::number(i + 1);
		
		QCheckBox *pCheckBox = new QCheckBox;
		pCheckBox->setChecked(true);
		ui.tableWidget->setCellWidget(i, 0, pCheckBox);

		for(j = 0; j < 5; j++)
			ui.tableWidget->setItem(i, j + 1, new QTableWidgetItem(sListWellInfo.at(5 * i + j)));

		//	The 5th column is the selected wells.
		QComboBox *pCBWells = new QComboBox;
		pCBWells->setEditable(true);
		pCBWells->addItems(strListWells);
		ui.tableWidget->setCellWidget(i, 6, pCBWells);
		connect(pCBWells, SIGNAL(currentIndexChanged(int)), this, SLOT(slotChangeWell(int)));

		//	Find matched well in the exists well list.
		int iIDX = strListWellsLower.indexOf(sListWellInfo.at(5 * i + 1).toLower());
		if(iIDX != -1)
		{
			if (iIDX == 0)
			{
				//	Force calling the slot to refresh the GUI.
				pCBWells->setCurrentIndex(-1);
			}

			pCBWells->setCurrentIndex(iIDX);
		}
		else
		{
			//Try fuzzy matching.
			QString sWell = sListWellInfo.at(5 * i + 1);
			if (sWell.isEmpty() || sWell == "New Well")
				sWell = sListWellInfo.at(5 * i);

			for(j = 0; j < strListWellsLower.size(); j++)
			{
				if (sWell.contains(strListWellsLower[j], Qt::CaseInsensitive))
				{
					pCBWells->setCurrentIndex(j);
					break;
				}
			}

			//	Create new candidate.
			if (j >= strListWellsLower.size())
			{
				pCBWells->addItem(sWell + " (New Created)");
				pCBWells->setCurrentIndex(strListWells.size());
			}
		}
	}
	ui.tableWidget->setVerticalHeaderLabels(sListVHeader);
	ui.tableWidget->resizeColumnsToContents();

	connect(ui.pushButtonSelectAll, SIGNAL(clicked()), this, SLOT(slotSelectAll()));
}

void CXPageMatchWells::slotSelectAll()
{
	m_bSelectAll = !m_bSelectAll;
	int iRowCount = ui.tableWidget->rowCount();
	for(int i = 0; i < iRowCount; i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidget->cellWidget(i, 0));
		pCheckBox->setChecked(m_bSelectAll);
	}
}

bool CXPageMatchWells::validatePage()
{
	int i, j, iRowCount = ui.tableWidget->rowCount();
	bool bSelected = false;
	for(i = 0; i < iRowCount; i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidget->cellWidget(i, 0));
		if(!pCheckBox->isChecked())
			m_sListMatchedWells[i] = "";
		else
		{
			bSelected = true;
			QComboBox* pCBWells = (QComboBox *)ui.tableWidget->cellWidget(i, 6);
			m_sListMatchedWells[i] = pCBWells->currentText();
			m_sListMatchedWells[i].remove(" (New Created)");
		}
	}

	if(!bSelected)
	{
 		if(::UsingChinese())
			QMessageBox::warning(NULL, "加载LAS文件", "没有选择文件！");
		else
			QMessageBox::warning(NULL, "Import Files", "No file was selected!");

		return false;
	}

	QStringList sListMatchedWells = m_sListMatchedWells;
	sListMatchedWells.removeAll("");
	int iRemoved = sListMatchedWells.removeDuplicates();
	if (iRemoved > 0)
	{
		QMessageBox::warning(NULL, "Import Files", "More than one files matched to one well!");
		return false;
	}

	return true;
}

void CXPageMatchWells::slotChangeWell(int iIDX)
{
	//	First we should know which row's template changed.
	QComboBox *pCBWells = dynamic_cast<QComboBox *>(sender());
	if(!pCBWells)
		return;

	int i;
	for(i = 0; i<ui.tableWidget->rowCount(); i++)
	{
		if(pCBWells == ui.tableWidget->cellWidget(i, 6))
		{
			QString strWell = pCBWells->currentText();
			if(strWell.indexOf(" (New Created)") == -1)
			{
				CXObject *pWellFolder = ::GetRootObjectFolder(EXWellFolder);
				CXWell *pWell = dynamic_cast<CXWell *>(pWellFolder->GetChild(strWell));
				if(pWell)
				{
					double dX, dY;
					pWell->GetWellPosition(dX, dY);
					ui.tableWidget->setItem(i, 8, new QTableWidgetItem(QString::number(dX, 'f', 0)));
					ui.tableWidget->setItem(i, 9, new QTableWidgetItem(QString::number(dY, 'f', 0)));
				}
			}
			else
			{
			}

			break;
		}
	}
}