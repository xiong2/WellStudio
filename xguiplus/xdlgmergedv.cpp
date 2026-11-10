#include <qmessagebox.h>
#include "xdlgmergedv.h"
#include "xseismicdatavolume.h"
#include "xthreadmergedv.h"
#include "xdlgcalculatingprogress.h"
#include "xalgorithmutility.h"
#include "xglobal.h"

XDlgMergeDV::XDlgMergeDV(CXObject *pObj, QWidget *parent)
	: m_pParent(pObj), QDialog(parent)
{
	ui.setupUi(this);

	initUI();
}

XDlgMergeDV::~XDlgMergeDV()
{
}

void XDlgMergeDV::initUI()
{
	ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);

	QList<CXObject *> listObj = m_pParent->GetChildren(EXSeismicDataVolume, true);
	if (listObj.isEmpty())
		return;

	QStringList sListDV;
	foreach(CXObject *pObj, listObj)
		ui.comboBox->addItem(pObj->GetObjectName(), pObj->GetObjectID());

	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableWidget_2->setColumnWidth(0, 100);
	ui.tableWidget_2->setColumnWidth(1, 60);

	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCB()));
	connect(ui.tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(slotDClickLColumn(QTableWidgetItem *)));
	connect(ui.tableWidget, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(slotActiveRowChanged(int, int, int, int)));
	connect(ui.tableWidget_2, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(slotActiveRowChanged(int, int, int, int)));
	connect(ui.pushButtonD, SIGNAL(clicked(bool)), this, SLOT(slotButtonPress()));
	connect(ui.pushButtonL, SIGNAL(clicked(bool)), this, SLOT(slotButtonPress()));
	connect(ui.pushButtonR, SIGNAL(clicked(bool)), this, SLOT(slotButtonPress()));
	connect(ui.pushButtonU, SIGNAL(clicked(bool)), this, SLOT(slotButtonPress()));

	slotCB();
}

void XDlgMergeDV::accept()
{
	int i, iNum = ui.tableWidget_2->rowCount();
	if (iNum == 0)
		return;

	QString sName = ui.lineEdit->text();
	if (sName.isEmpty())
	{
		QMessageBox::warning(NULL, QString::fromUtf8(u8"合并数据体"), QString::fromUtf8(u8"请提供输出数据体名称！"));
		return;
	}

	CXObject *pBDV = ::GetObjectByID(ui.comboBox->currentData().toUuid());
	CXParameterMergeDV *pPara = new CXParameterMergeDV;
	pPara->SetBaseDV(pBDV->GetObjectID());
	pPara->SetNewDVName(sName);

	std::vector<QUuid> vecDV;
	std::vector<float> vecWei;
	QList<CXObject *> listDV = m_pParent->GetChildren(EXSeismicDataVolume, true);
	for (i = 0; i < iNum; i++)
	{
		foreach(CXObject *pObj, listDV)
		{
			if (pObj->GetObjectName() == ui.tableWidget_2->item(i, 0)->text())
			{
				vecDV.push_back(pObj->GetObjectID());
				break;
			}
		}

		bool bSu;
		float fWei = ui.tableWidget_2->item(i, 1)->text().toFloat(&bSu);
		if (!bSu)
		{
			QMessageBox::warning(NULL, QString::fromUtf8(u8"合并数据体"), QString::fromUtf8(u8"权重必须是数值！"));
			delete pPara;
			return;
		}
		vecWei.push_back(fWei);
	}
	pPara->SetVecSubDV(vecDV);
	pPara->SetVecWeight(vecWei);

	XThreadMergeDV *pThread = new XThreadMergeDV(pPara);
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(pThread);

	pProgress->show();
	pThread->start();

	if (pProgress->exec() == QDialog::Accepted)
	{
		delete pThread;

		CXSeismicDataVolume *pDV = dynamic_cast<CXSeismicDataVolume *>(pBDV->GetParent()->GetChild(sName, EXSeismicDataVolume));
		CXAlgorithmUtility::CalculateHistogram(pDV->GetTraceFileName(), pDV->GetSamplingQty(), pDV);
	}

	QDialog::accept();
}

void XDlgMergeDV::slotCB()
{
	int iIDX = ui.comboBox->currentIndex();
	QString sName = ui.comboBox->currentText() + "_Merged";
	sName = m_pParent->GetUnallocatedName(sName);
	ui.lineEdit->setText(sName);

	ui.tableWidget->clearContents();

	QStringList sListCDVName = getCandidateDV(ui.comboBox->currentData().toUuid());
	ui.tableWidget->setRowCount(sListCDVName.size());
	for (int i = 0; i < sListCDVName.size(); i++)
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(sListCDVName[i]));

	ui.tableWidget_2->clearContents();
	ui.pushButtonR->setEnabled(false);
	ui.pushButtonL->setEnabled(false);
	ui.pushButtonU->setEnabled(false);
	ui.pushButtonD->setEnabled(false);
}

void XDlgMergeDV::slotActiveRowChanged(int iRow, int, int, int)
{
	if (sender() == ui.tableWidget)
	{
		ui.pushButtonR->setEnabled(true);
	}
	else
	{
		ui.pushButtonL->setEnabled(true);
		ui.pushButtonU->setEnabled(true);
		ui.pushButtonD->setEnabled(true);

		if (iRow == 0)
		{
			ui.pushButtonU->setEnabled(false);
		}

		if (iRow == ui.tableWidget_2->rowCount() - 1)
		{
			ui.pushButtonD->setEnabled(false);
		}
	}
}

void XDlgMergeDV::slotButtonPress()
{
	QTableWidgetItem *pCItem;

	if (sender() == ui.pushButtonR)
	{
		pCItem = ui.tableWidget->currentItem();
		if (!pCItem)
			return;

		slotDClickLColumn(pCItem);
	}
	else if (sender() == ui.pushButtonL)
	{
		pCItem = ui.tableWidget_2->currentItem();
		if (!pCItem)
			return;

		QString sText = pCItem->text();

		//  Remove from the right table.
		ui.tableWidget_2->removeRow(ui.tableWidget_2->row(pCItem));
		if (ui.tableWidget_2->rowCount() == 0)
		{
			ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
			ui.pushButtonL->setEnabled(false);
		}

		//  Add to the left table.
		int i, iRow = ui.tableWidget->rowCount();
		ui.tableWidget->setRowCount(iRow + 1);
		ui.tableWidget->setItem(iRow, 0, new QTableWidgetItem(sText));
	}
	else if (sender() == ui.pushButtonU || sender() == ui.pushButtonD)
	{
		bool bUp = true;
		if (sender() == ui.pushButtonD)
			bUp = false;

		int iIDX = ui.tableWidget_2->currentRow();
		if (bUp && iIDX == 0)
			return;
		if (!bUp && iIDX >= ui.tableWidget_2->rowCount() - 1)
			return;

		int iNewIDX;
		if (bUp)
		{
			iNewIDX = iIDX - 1;
			iIDX++;
		}
		else
		{
			iNewIDX = iIDX + 2;
		}

		ui.tableWidget_2->insertRow(iNewIDX);
		ui.tableWidget_2->setItem(iNewIDX, 0, ui.tableWidget_2->takeItem(iIDX, 0));
		ui.tableWidget_2->setItem(iNewIDX, 1, ui.tableWidget_2->takeItem(iIDX, 1));

		ui.tableWidget_2->setCurrentCell(iNewIDX, 0);
		ui.tableWidget_2->removeRow(iIDX);
	}
}

void XDlgMergeDV::slotDClickLColumn(QTableWidgetItem *pItem)
{
	QString sText = pItem->text();

	//  Remove from the left table.
	ui.tableWidget->removeRow(ui.tableWidget->row(pItem));

	//  Add to the right table.
	int iRow = ui.tableWidget_2->rowCount();
	ui.tableWidget_2->setRowCount(iRow + 1);
	ui.tableWidget_2->setItem(iRow, 0, new QTableWidgetItem(sText));
	ui.tableWidget_2->setItem(iRow, 1, new QTableWidgetItem("1.0"));

	ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
}

QStringList XDlgMergeDV::getCandidateDV(QUuid dvID)
{
	QStringList sListCDVName;

	CXSeismicDataVolume *pBDV = dynamic_cast<CXSeismicDataVolume *>(::GetObjectByID(dvID));
	if (!pBDV)
		return sListCDVName;

	CXSeismicUTMTool& utm = pBDV->GetUTM();
	int iInlineInc = utm.GetInlineIncrement();
	int iXlineInc = utm.GetCrosslineIncrement();
	float fSampleInv = pBDV->GetSampleInterval();

	QList<CXObject *> listObj = m_pParent->GetChildren(EXSeismicDataVolume, true);
	foreach(CXObject *pObj, listObj)
	{
		if (pObj->GetObjectID() == dvID)
			continue;

		CXSeismicDataVolume *pDV = dynamic_cast<CXSeismicDataVolume *>(pObj);
		CXSeismicUTMTool& utm2 = pDV->GetUTM();

		if (iInlineInc == utm2.GetInlineIncrement()
			&& iXlineInc == utm2.GetCrosslineIncrement()
			&& fSampleInv == pDV->GetSampleInterval())
			sListCDVName << pDV->GetObjectName();
	}

	return sListCDVName;
}