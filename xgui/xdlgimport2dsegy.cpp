#include <qfileinfo.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QFileDialog>
#include "xdlgimport2dsegy.h"
#include "xebcdicdialog.h"
#include "xsegyloadparameters.h"
#include "xebcdicdialog.h"
#include "xdlgsegylineheader.h"
#include "xdlgsegytraceheader.h"
#include "xdlgsegydataformat.h"
#include "xglobal.h"

CXDlgImport2DSEGY::CXDlgImport2DSEGY(QStringList sListFiles, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_sListSEGYFiles = sListFiles;

	//QString sSurveyName = m_ui.lineEditSurvey->text();
	//sSurveyName = ::GetProject()->GetUnallocatedName(sSurveyName);
	//m_ui.lineEditSurvey->setText(sSurveyName);

	for (int i = 0; i < m_sListSEGYFiles.size(); i++)
	{
		QStringList sListFile;
		sListFile << m_sListSEGYFiles[i];
		CXSEGYLoadParameters *pParameters = new CXSEGYLoadParameters(sListFile);
		m_listParameters << pParameters;
	}

	QStringList sListHHeader;
	sListHHeader << "File Name" << "Line Name" << "EBCDIC Header" << "Line Header" << "Trace Header" << "Data Format";

	ui.tableWidget->setColumnCount(6);
	ui.tableWidget->setHorizontalHeaderLabels(sListHHeader);
	ui.tableWidget->setColumnWidth(0, 300);
	ui.tableWidget->setColumnWidth(1, 100);
	ui.tableWidget->setColumnWidth(2, 100);
	ui.tableWidget->setColumnWidth(3, 100);
	ui.tableWidget->setColumnWidth(4, 100);
	ui.tableWidget->setColumnWidth(5, 100);

	connect(ui.pushButtonAddFiles, SIGNAL(clicked()), this, SLOT(slotAddFiles()));
	connect(ui.pushButtonRemvoeFiles, SIGNAL(clicked()), this, SLOT(slotRemoveFile()));
	connect(ui.tableWidget, SIGNAL(itemSelectionChanged()), SLOT(slotItemClicked()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

	initializeTab();
}

CXDlgImport2DSEGY::~CXDlgImport2DSEGY()
{
	qDeleteAll(m_listParameters);
	m_listParameters.clear();
}

void CXDlgImport2DSEGY::initializeTab()
{
	int i, iNumFile = m_sListSEGYFiles.size();

	ui.tableWidget->setRowCount(iNumFile);
	for (i = 0; i < iNumFile; i++)
	{
		//	File name.
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(m_sListSEGYFiles[i]));

		//	Line name.
		QFileInfo qFI(m_sListSEGYFiles[i]);
		QLineEdit *pLineEdit = new QLineEdit;
		pLineEdit->setText(qFI.baseName());
		ui.tableWidget->setCellWidget(i, 1, pLineEdit);

		//	Volume header.
		QPushButton *pBushButton = new QPushButton("View");
		ui.tableWidget->setCellWidget(i, 2, pBushButton);
		connect(pBushButton, SIGNAL(clicked()), this, SLOT(slotViewVolumeHeader()));

		//	Line header.
		pBushButton = new QPushButton("View");
		ui.tableWidget->setCellWidget(i, 3, pBushButton);
		connect(pBushButton, SIGNAL(clicked()), this, SLOT(slotViewLineHeader()));

		//	Trace header.
		pBushButton = new QPushButton("Set");
		ui.tableWidget->setCellWidget(i, 4, pBushButton);
		connect(pBushButton, SIGNAL(clicked()), this, SLOT(slotSetTraceHeader()));

		//	Data format
		pBushButton = new QPushButton("Set");
		ui.tableWidget->setCellWidget(i, 5, pBushButton);
		connect(pBushButton, SIGNAL(clicked()), this, SLOT(slotSetDataFormat()));
	}
}

void CXDlgImport2DSEGY::slotViewVolumeHeader()
{
	QPushButton *pPButton = dynamic_cast<QPushButton *>(sender());
	if (!pPButton)
		return;

	int i;
	for (i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		if (pPButton == ui.tableWidget->cellWidget(i, 2))
		{
			break;
		}
	}

	if (i >= ui.tableWidget->rowCount())
		return;

	CXEBCDICDialog *pEBCDICDialog = new CXEBCDICDialog(this);
	pEBCDICDialog->setWindowTitle("2D SEG-Y File Volume Header Information");
	pEBCDICDialog->SetEBCDIC(m_listParameters[i]->GetVolumeHeader());
	pEBCDICDialog->showNormal();
}

void CXDlgImport2DSEGY::slotViewLineHeader()
{
	QPushButton *pPButton = dynamic_cast<QPushButton *>(sender());
	if (!pPButton)
		return;

	int i;
	for (i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		if (pPButton == ui.tableWidget->cellWidget(i, 3))
		{
			break;
		}
	}

	if (i >= ui.tableWidget->rowCount())
		return;

	CXDlgSEGYLineHeader * pLineHeaderView = new CXDlgSEGYLineHeader(this);
	pLineHeaderView->setLineHeaderData(m_listParameters[i]->GetLineHeader());
	pLineHeaderView->initTreeView();
	pLineHeaderView->setWindowTitle("2D SEG-Y File Line Header Information");
	pLineHeaderView->exec();
}

void CXDlgImport2DSEGY::slotSetTraceHeader()
{
	QPushButton *pPButton = dynamic_cast<QPushButton *>(sender());
	if (!pPButton)
		return;

	int i, j;
	for (i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		if (pPButton == ui.tableWidget->cellWidget(i, 4))
		{
			break;
		}
	}

	if (i >= ui.tableWidget->rowCount())
		return;

	CXDlgSEGYTraceHeader * pTraceHeaderView = new CXDlgSEGYTraceHeader(m_listParameters[i], this);
	//pTraceHeaderView->setLineHeaderData(m_listParameters[i]->GetLineHeader());
	pTraceHeaderView->setWindowTitle("2D SEG-Y File Trace Header Information");
	pTraceHeaderView->exec();

	if (pTraceHeaderView->OKForAll())
	{
		for (j = 0; j < m_listParameters.size(); j++)
		{
			if (j == i)
				continue;

			m_listParameters[j]->SetCrosslinePosition(m_listParameters[i]->GetCrosslinePosition());
			m_listParameters[j]->SetXPosition(m_listParameters[i]->GetXPosition());
			m_listParameters[j]->SetYPosition(m_listParameters[i]->GetYPosition());
		}
	}
}

void CXDlgImport2DSEGY::slotSetDataFormat()
{
	QPushButton *pPButton = dynamic_cast<QPushButton *>(sender());
	if (!pPButton)
		return;

	int i, j;
	for (i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		if (pPButton == ui.tableWidget->cellWidget(i, 5))
		{
			break;
		}
	}

	if (i >= ui.tableWidget->rowCount())
		return;

	CXDlgSEGYDataFormat * pDataFormat = new CXDlgSEGYDataFormat(m_listParameters[i], this);
	pDataFormat->setWindowTitle("2D SEG-Y File Data Format");
	pDataFormat->exec();

	if (pDataFormat->OKForAll())
	{
		for (j = 0; j < m_listParameters.size(); j++)
		{
			if (j == i)
				continue;

			m_listParameters[j]->SetDataType(m_listParameters[i]->GetDataType());
			m_listParameters[j]->SetDataFlip(m_listParameters[i]->DataNeedFlip());
		}
	}
}

void CXDlgImport2DSEGY::slotItemClicked()
{
	QList<QTableWidgetItem*> pTableSel = ui.tableWidget->selectedItems();
	if (pTableSel.isEmpty())
	{
		ui.pushButtonRemvoeFiles->setEnabled(false);
	}
	else
	{
		ui.pushButtonRemvoeFiles->setEnabled(true);
	}
}

void CXDlgImport2DSEGY::slotRemoveFile()
{
	QList<QTableWidgetSelectionRange> pTableSel = ui.tableWidget->selectedRanges();
	if (pTableSel.empty())
		return;

	int topRow = pTableSel.at(0).topRow();
	int bottomRow = pTableSel.at(0).bottomRow();

	for (int i = topRow; i <= bottomRow; i++)
	{
		ui.tableWidget->removeRow(topRow);

		CXSEGYLoadParameters *pFI = m_listParameters.at(topRow);
		m_listParameters.removeAt(topRow);
		delete pFI;
	}

	if (ui.tableWidget->rowCount() == 0)
	{
		ui.pushButtonRemvoeFiles->setEnabled(false);
	}
}

void CXDlgImport2DSEGY::slotAddFiles()
{
	QStringList sListFiles = QFileDialog::getOpenFileNames(this, "Select one or more SEGY files", "", "SEGY files (*.sgy;*.segy");
	if (sListFiles.size() == 0)
		return;

	int i, j;
	for (i = 0; i < sListFiles.size(); i++)
	{
		//	To see if the file already be included.
		for (j = 0; j < m_listParameters.size(); j++)
		{
			if (m_listParameters[j]->GetAllSEGYFiles().contains(sListFiles[i]))
				break;
		}

		if (j < m_listParameters.size())
			continue;

		QStringList sListTmpFile;
		sListTmpFile << sListFiles[i];
		CXSEGYLoadParameters *pParameters = new CXSEGYLoadParameters(sListTmpFile);
		m_listParameters.append(pParameters);
	}

	//	New file added?
	int iTableRow = ui.tableWidget->rowCount();
	int iFileNum = m_listParameters.size();
	if (iFileNum <= iTableRow)
		return;

	ui.tableWidget->setRowCount(iFileNum);
	for (i = iTableRow; i < iFileNum; i++)
	{
		//	File name.
		QString sFileName = m_listParameters[i]->GetAllSEGYFiles()[0];
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(sFileName));

		//	Line name.
		QFileInfo qFI(sFileName);
		QLineEdit *pLineEdit = new QLineEdit;
		pLineEdit->setText(qFI.baseName());
		ui.tableWidget->setCellWidget(i, 1, pLineEdit);

		//	Volume header.
		QPushButton *pBushButton = new QPushButton("View");
		ui.tableWidget->setCellWidget(i, 2, pBushButton);
		connect(pBushButton, SIGNAL(clicked()), this, SLOT(slotViewVolumeHeader()));

		//	Line header.
		pBushButton = new QPushButton("View");
		ui.tableWidget->setCellWidget(i, 3, pBushButton);
		connect(pBushButton, SIGNAL(clicked()), this, SLOT(slotViewLineHeader()));

		//	Trace header.
		pBushButton = new QPushButton("Set");
		ui.tableWidget->setCellWidget(i, 4, pBushButton);
		connect(pBushButton, SIGNAL(clicked()), this, SLOT(slotSetTraceHeader()));

		//	Data format
		pBushButton = new QPushButton("Set");
		ui.tableWidget->setCellWidget(i, 5, pBushButton);
		connect(pBushButton, SIGNAL(clicked()), this, SLOT(slotSetDataFormat()));
	}
}

QString CXDlgImport2DSEGY::Get2DSurveyName()
{
	return ui.lineEditSurvey->text();
}

void CXDlgImport2DSEGY::accept()
{
	QDialog::accept();
}