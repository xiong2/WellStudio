#include <qcheckbox.h>
#include <qmessagebox.h>

#include <QFile>
#include "xdlgmergegeobody.h"
#include "xgeobodycollection.h"
#include "xgeobody.h"
#include "xtree.h"
#include "xtreewidgetitem.h"
#include "xglobal.h"

CXDlgMergeGeobody::CXDlgMergeGeobody(CXGeobodyCollection *pGCollection, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_pGCollection = pGCollection;

	initialize();
}

CXDlgMergeGeobody::~CXDlgMergeGeobody()
{

}

void CXDlgMergeGeobody::initialize()
{
	QString sName = m_pGCollection->GetObjectName() + " Merged";
	sName = m_pGCollection->GetUnallocatedName(sName);
	ui.lineEdit->setText(sName);

	QList<CXObject *> listGeobody = m_pGCollection->GetChildren(EXGeobody);

	ui.tableWidget->setRowCount(listGeobody.size());
	ui.tableWidget->setColumnCount(4);

	QStringList sListHHeader;
	sListHHeader << "Select" << "Geobody"<<"Cell Number"<<"Merged/Single";
	ui.tableWidget->setHorizontalHeaderLabels(sListHHeader);
	for (int i = 0; i < listGeobody.size(); i++)
	{
		QString sStatus = "Single";
		CXGeobody *pGeobody = (CXGeobody *)listGeobody.at(i);
		if (pGeobody->IsMerged())
			sStatus = "Merged";

		bool bIsChecked = CXTree::Instance().GetTreeItemFromID(pGeobody->GetObjectID())->checkState(0) == Qt::Checked;

		QCheckBox *pCheckBox = new QCheckBox;
		pCheckBox->setChecked(bIsChecked);
		ui.tableWidget->setCellWidget(i, 0, pCheckBox);

		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(pGeobody->GetObjectName()));
		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(pGeobody->GetTotalCellNumber())));
		ui.tableWidget->setItem(i, 3, new QTableWidgetItem(sStatus));
	}

	ui.tableWidget->setColumnWidth(0, 60);
	ui.tableWidget->setColumnWidth(1, 200);
	ui.tableWidget->setColumnWidth(2, 100);
	ui.tableWidget->setColumnWidth(3, 100);

	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
}

void CXDlgMergeGeobody::accept()
{
	int i;
	QList<CXGeobody *> listSelected;
	QList<CXObject *> listGeobody = m_pGCollection->GetChildren(EXGeobody);
	for (i = 0; i < listGeobody.size(); i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidget->cellWidget(i, 0));
		if (pCheckBox)
		{
			if (pCheckBox->isChecked())
			{
				CXGeobody *pGeobody = (CXGeobody *)listGeobody.at(i);
				listSelected << pGeobody;
			}
		}
	}

	if (listSelected.size() <= 1)
	{
		QMessageBox::warning(NULL, "Merge Geobody", "Please select more than one geobodies!");

		return;
	}

	unsigned int iTotalNumber = 0;
	double dMinX = 99999999., dMinY = 99999999., dMinZ = 99999999., dMaxX = 0, dMaxY = 0, dMaxZ = 0;
	double dWMinX = 99999999., dWMinY = 99999999., dWMinZ = 99999999., dWMaxX = 0, dWMaxY = 0, dWMaxZ = 0;
	for (i = 0; i < listSelected.size(); i++)
	{
		iTotalNumber += listSelected.at(i)->GetTotalCellNumber();
		listSelected[i]->GetDimension(dMinX, dMaxX, dMinY, dMaxY, dMinZ, dMaxZ);
		dWMinX = dWMinX < dMinX ? dWMinX : dMinX;
		dWMaxX = dWMaxX > dMaxX ? dWMaxX : dMaxX;
		dWMinY = dWMinY < dMinY ? dWMinY : dMinY;
		dWMaxY = dWMaxY > dMaxY ? dWMaxY : dMaxY;
		dWMinZ = dWMinZ < dMinZ ? dWMinZ : dMinZ;
		dWMaxZ = dWMaxZ > dMaxZ ? dWMaxZ : dMaxZ;
	}

	std::vector<qint64> vecCells(iTotalNumber);

	unsigned int iCurrent = 0;
	for (i = 0; i < listSelected.size(); i++)
	{
		unsigned iNumCells;
		qint64 *pCells =  listSelected.at(i)->GetAllCells(iNumCells);

		std::copy(pCells, pCells + iNumCells, vecCells.begin() + iCurrent);
		iCurrent += iNumCells;
	}
	std::sort(vecCells.begin(), vecCells.end());
	vecCells.erase(std::unique(vecCells.begin(), vecCells.end()), vecCells.end());

	QString strWholeFileName = ::GetProjectPath() + "geobody_MergeBuff" + ".dat";
	QFile qWFile(strWholeFileName);
	qWFile.open(QIODevice::WriteOnly);
	qWFile.write((char *)(vecCells.data()), sizeof(qint64) * vecCells.size());
	qWFile.close();

	//	Create the geobody.
	float fSZ, fEZ;
	CXGeobody *pOriBody = listSelected[0];
	pOriBody->GetZRange(fSZ, fEZ);
	CXGeobody *pGeobody = new CXGeobody(&pOriBody->GetUTM(), fSZ, fEZ, pOriBody->GetZInc(), true);
	pGeobody->PopulateData(strWholeFileName, vecCells.size());
	pGeobody->SetDimension(dWMinX, dWMaxX, dWMinY, dWMaxY, dWMinZ, dWMaxZ);

	QString sName = ui.lineEdit->text();
	sName = m_pGCollection->GetUnallocatedName(sName);
	pGeobody->SetObjectName(sName);

	m_pGCollection->AddChild(pGeobody);

	pGeobody->AddEvent(EAdded);
	CXProcessEvent eventProcess;

	QDialog::accept();
}