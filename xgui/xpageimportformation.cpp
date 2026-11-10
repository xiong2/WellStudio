#include <qcheckbox.h>
#include <qmessagebox.h>
#include "xpageimportformation.h"
#include "xwelltopsfile.h"

CXPageImportFormation::CXPageImportFormation(CXASCIIFile *pAFile, QWidget *parent)
	: QWizardPage(parent)
{
	ui.setupUi(this);
	m_pASCIIFile = pAFile;
}

CXPageImportFormation::~CXPageImportFormation()
{

}

void CXPageImportFormation::initializePage()
{
	CXWellTopsFile *pWTFile = (CXWellTopsFile *)m_pASCIIFile;
	QStringList sListFormation = pWTFile->GetAllFormationsInFile();

	ui.tableWidget->setRowCount(sListFormation.size());
	ui.tableWidget->setColumnCount(2);

	QStringList sListHHeader;
	sListHHeader << "Select" << "Formation";
	ui.tableWidget->setHorizontalHeaderLabels(sListHHeader);

	for (int i = 0; i < sListFormation.size(); i++)
	{
		QCheckBox *pCheckBox = new QCheckBox;
		pCheckBox->setChecked(true);
		ui.tableWidget->setCellWidget(i, 0, pCheckBox);

		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(sListFormation.at(i)));
	}

	ui.tableWidget->setColumnWidth(1, 200);

	connect(ui.pushButtonSelectAll, SIGNAL(clicked()), this, SLOT(slotSelectAll()));
	connect(ui.pushButtonUnselectAll, SIGNAL(clicked()), this, SLOT(slotSelectAll()));
}

bool CXPageImportFormation::validatePage()
{
	CXWellTopsFile *pWTFile = (CXWellTopsFile *)m_pASCIIFile;
	QStringList& sListSelectFormations = pWTFile->GetSelectFormations();
	sListSelectFormations.clear();

	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidget->cellWidget(i, 0));
		if (pCheckBox)
		{
			if (pCheckBox->isChecked())
				sListSelectFormations << ui.tableWidget->item(i, 1)->text();
		}
	}

	if (sListSelectFormations.size() <= 0)
	{
		QMessageBox::warning(NULL, "Import Well Tops", "No formation selected!");
		return false;
	}

	return true;
}

void CXPageImportFormation::slotSelectAll()
{
	bool bSelect = sender() == ui.pushButtonSelectAll;
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidget->cellWidget(i, 0));
		if (pCheckBox)
		{
			pCheckBox->setChecked(bSelect);
		}
	}
}