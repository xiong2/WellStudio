#include <QStandardItemModel>
#include <QtCore/QSettings>
#include <qfiledialog.h>
#include "xdlgtdcalculate.h"
#include "xwelltd.h"
#include "xwell.h"
#include "xtemplate.h"
#include "xdlgac2td.h"
#include "xwellcheckshotfile.h"
#include "xpageasciifile.h"
#include "xpagematchwells.h"
#include "xpageattributes.h"

CXDlgTDCalculate::CXDlgTDCalculate(CXWell *pObj, QWidget *parent)
	: m_pWell(pObj), QDialog(parent)
{
	ui.setupUi(this);

	initUI();
}

CXDlgTDCalculate::~CXDlgTDCalculate()
{
}

void CXDlgTDCalculate::initUI()
{
	CXTemplate *pTemplate = CXTemplate::GetTemplate("PSON");
	if (pTemplate)
	{
		QList<CXObject *> listCurve = m_pWell->GetSpecialCurveList(pTemplate->GetID());
		ui.pushButtonCal->setDisabled(listCurve.isEmpty());
		ui.label_2->setDisabled(listCurve.isEmpty());
	}
	else
	{
		ui.pushButtonCal->setDisabled(true);
		ui.label_2->setDisabled(true);
	}

	connect(ui.pushButtonImport, SIGNAL(clicked()), SLOT(slotImport()));
	connect(ui.pushButtonCal, SIGNAL(clicked()), SLOT(slotCalculate()));
	connect(ui.pushButtonAct, SIGNAL(clicked()), SLOT(slotSetAct()));
	connect(ui.pushButtonDel, SIGNAL(clicked()), SLOT(slotDel()));

	initCurveTab();
	populateTDModel(m_pWell->GetWellTD());
}

void CXDlgTDCalculate::initCurveTab()
{
	connect(ui.tableWidget, SIGNAL(itemSelectionChanged()), SLOT(slotSelectTD()));

	QList<CXObject *> listTD = m_pWell->GetChildren(EXWellTD);
	int i, iNum = listTD.size();
	ui.tableWidget->setRowCount(iNum);
	for (i = 0; i < iNum; i++)
	{
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(listTD[i]->GetObjectName()));
		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(listTD[i]->GetIconName()));
	}
}

void CXDlgTDCalculate::slotCalculate()
{
	CXDlgAC2TD dlg(m_pWell);
	if (dlg.exec() == QDialog::Accepted)
	{
		initCurveTab();
	}
}

void CXDlgTDCalculate::slotSelectTD()
{
	QList<QTableWidgetItem*> listSItems = ui.tableWidget->selectedItems();
	ui.pushButtonAct->setEnabled(!listSItems.isEmpty());
	ui.pushButtonDel->setEnabled(!listSItems.isEmpty());
}

void CXDlgTDCalculate::populateTDModel(CXWellTD *pTD)
{
	QItemSelectionModel *pM = ui.tableView->selectionModel();
	if (pM)
		delete pM;
	
	if (!pTD)
	{
		ui.tableView->setModel(NULL);
		ui.groupBoxAct->setTitle("Activated T-D Curve: ");
		return;
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);

	ui.groupBoxAct->setTitle("Activated T-D Curve: " + pTD->GetObjectName());

	QStringList sListHLable;
	sListHLable << "TVDSS (m)" << "TWT (ms)";
	unsigned int i, iNumber;
	double *pData = pTD->GetData(iNumber);
	iNumber /= 2;

	QStandardItemModel *pModel = new QStandardItemModel(iNumber, 2);
	ui.tableView->setModel(pModel);
	pModel->setHorizontalHeaderLabels(sListHLable);
	for (i = 0; i < iNumber; i++)
	{
		QStandardItem *pItem = new QStandardItem(QString::number(pData[i], 'f', 2));
		pModel->setItem(i, 0, pItem);

		pItem = new QStandardItem(QString::number(pData[i + iNumber], 'f', 2));
		pModel->setItem(i, 1, pItem);
	}

	QApplication::restoreOverrideCursor();
}

void CXDlgTDCalculate::slotSetAct()
{
	QList<QTableWidgetItem*> listSItems = ui.tableWidget->selectedItems();
	if (listSItems.size() != 2)
		return;

	QString sName = listSItems[0]->text();
	if (sName == m_pWell->GetActivatedTDName())
		return;

	CXWellTD *pTD = (CXWellTD *)m_pWell->GetChild(sName, EXWellTD);
	if (!pTD)
		return;

	m_pWell->SetActivatedTDName(sName);
	populateTDModel(pTD);
}

void CXDlgTDCalculate::slotDel()
{
	QList<QTableWidgetItem*> listSItems = ui.tableWidget->selectedItems();
	if (listSItems.size() != 2)
		return;

	QString sName = listSItems[0]->text();
	if (sName == m_pWell->GetActivatedTDName())
	{
		m_pWell->SetActivatedTDName("");
		populateTDModel(NULL);
	}

	CXObject *pTD = m_pWell->GetChild(sName, EXWellTD);
	m_pWell->RemoveOneChild(pTD);
	initCurveTab();
}

void CXDlgTDCalculate::slotImport()
{
	QFileDialog dialog(NULL, "Import Check Shot Files");
	dialog.setFileMode(QFileDialog::ExistingFiles);
	dialog.setNameFilter("Check Short File (*)");

	QSettings settings("RGS", "RecentDataDir");
	QString recentDataDir = settings.value("lastPath").toString();
	if (!recentDataDir.isEmpty()) dialog.setDirectory(recentDataDir);

	QStringList sListFiles;
	QString strSelectedFilter;
	if (dialog.exec())
	{
		QDir currentDir = dialog.directory();
		settings.setValue("lastPath", currentDir.absolutePath());
		sListFiles = dialog.selectedFiles();
		strSelectedFilter = dialog.selectedNameFilter();
	}

	if (sListFiles.isEmpty())
		return;

	CXASCIIFile *pAFile = new CXWellCheckShotFile(sListFiles[0]);
	QStringList sListWellInfo;
	QStringList sListMatchedWells;

	for (int i = 0; i < sListFiles.size(); i++)
	{
		QFileInfo qFI(sListFiles.at(i));
		sListWellInfo << qFI.baseName() << qFI.baseName() << "" << "" << "";
		sListMatchedWells << "";
	}

	QWizard wizard;
	wizard.setWindowTitle("Import Well Check Shot File");
	wizard.setWizardStyle(QWizard::ClassicStyle);
	CXPageMatchWells *pPageMatchWells = new CXPageMatchWells(sListWellInfo, sListMatchedWells);
	wizard.addPage(pPageMatchWells);
	CXPageASCIIFile *pFilePage = new CXPageASCIIFile(pAFile);
	wizard.addPage(pFilePage);
	CXPageAttributes *pAttPage = new CXPageAttributes(pAFile);
	wizard.addPage(pAttPage);
	wizard.resize(1000, 600);

	//	Populate the candidates of each column for well header files.
	QStringList& sListCandidates = pAFile->GetColumnCandidates();
	sListCandidates << "Do not import" << "TVD" << "TVDSS" << "MD" << "TWT";

	if (wizard.exec() == QDialog::Accepted)
	{
		for (int i = 0; i < sListFiles.size(); i++)
		{
			pAFile->SetFile(sListFiles.at(i), sListMatchedWells[i]);
			pAFile->Import();
		}
	}

	delete pAFile;

	initCurveTab();
}