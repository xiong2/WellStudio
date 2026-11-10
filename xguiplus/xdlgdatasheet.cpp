#include <QStandardItemModel>
#include <qmessagebox.h>
#include <qpushbutton.h>
#include "xdlgdatasheet.h"
#include "xdlgfactory.h"
#include "xglobal.h"
#include "xwaitcursor.h"
#include "xwell.h"
#include "xwellpath.h"
#include "xwelltd.h"
#include "xwellcurve.h"
#include "x3dpoints.h"
#include "xseismicrandomsection.h"
#include "xwelltops.h"

CXDlgDataSheet::CXDlgDataSheet(QUuid objID, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_objID = objID;

	setAttribute(Qt::WA_DeleteOnClose);

	PopulateData();

	ui.buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
	connect(ui.toolButtonRemove, SIGNAL(clicked()), this, SLOT(slotRowEdit()));
	connect(ui.toolButtonRL, SIGNAL(clicked()), this, SLOT(slotRowEdit()));
	connect(ui.toolButtonAppend, SIGNAL(clicked()), this, SLOT(slotRowEdit()));
	connect(ui.toolButtonInsert, SIGNAL(clicked()), this, SLOT(slotRowEdit()));
	connect(ui.tableView->model(), &QAbstractItemModel::dataChanged, this, &CXDlgDataSheet::slotDataChanged);
}

CXDlgDataSheet::~CXDlgDataSheet()
{
	CXDlgFactory::Instance().CloseDialog(m_objID, eDataSheetDialog);
}

bool CXDlgDataSheet::PopulateData()
{
	CXWaitCursor waitCursor;

	CXObject *pObj = ::GetObjectByID(m_objID);

	if (!pObj)
		return false;

	QList<CXObject *> listObj;
	setWindowTitle("Data Sheet of " + pObj->GetObjectName());

	setTips(pObj->GetObjectType());
	m_vecColumnEditable.clear();

	unsigned int i, j, iNumber;
	double *pBuff;
	switch (pObj->GetObjectType())
	{
	case EXWellPath:
	{
		double *pData = pObj->GetData(iNumber);
		double *pMD = ((CXWellPath *)pObj)->GetMdData();
		iNumber /= 3;
		int iIDX = 0;
		pBuff = new double[4 * iNumber];
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < iNumber; j++)
			{
				pBuff[iIDX] = pData[3 * j + i];
				iIDX++;
			}
		}
		memcpy(pBuff + 3 * iNumber, pMD, sizeof(double) * iNumber);

		QStringList sListHLable;
		sListHLable << "X (m)" << "Y (m)" << "Z (m)" << "MD (m)";
		populate(sListHLable, pBuff, 4 * iNumber);
		
		//	We do not want user directly edit well path through this data sheet.
		setEditable(0);

		delete[]pBuff;
		return true;
	}
	case EXWellTD:
	{
		pBuff = pObj->GetData(iNumber);

		QStringList sListHLable;
		sListHLable << "TVDSS (m)" << "TWT (ms)";
		populate(sListHLable, pBuff, iNumber);
		return true;
	}
	case EXWellCurve:
	{
		CXWellCurve *pCurve = (CXWellCurve *)pObj;
		double dStep = pCurve->GetStep();
		double *pData = pObj->GetData(iNumber);
		pBuff = new double[2 * iNumber];
		pBuff[0] = pCurve->GetStart();
		for (i = 1; i < iNumber; i++)
		{
			pBuff[i] = pBuff[i - 1] + dStep;
		}
		memcpy(pBuff + iNumber, pData, sizeof(double) * iNumber);

		QStringList sListHLable;
		QString sCurve = pObj->GetObjectName(), sUnit = pCurve->GetUnit();
		if (!sUnit.isEmpty())
			sCurve = sCurve + " (" + sUnit + ")";
		sListHLable << "MD (m)" << sCurve;
		populate(sListHLable, pBuff, 2 * iNumber);

		//	Do not allow add/remove row, the 2nd column items can be edited.
		m_vecColumnEditable << false << true;
		setEditable(1);

		delete[]pBuff;
		return true;
	}
	case EXWell:
	{
		CXWell *pWell = (CXWell *)pObj;
		QList<CXObject *> listObj = pWell->GetChildren(EXWellCurve);
		if (listObj.isEmpty())
			return false;

		unsigned int iColumns = listObj.size();
		double dStart, dStop, dStep = pWell->GetWellStep();
		pWell->GetDepthRange(dStart, dStop);
		unsigned int iRows = (dStop - dStart) / dStep + 1.9;
		if (iRows <= 0)
			return false;

		pBuff = new double[iRows * iColumns];
		QStringList sListHLable;

		for (i = 0; i < iColumns; i++)
		{
			CXWellCurve *pCurve = (CXWellCurve *)listObj[i];
			QString sCurve = pCurve->GetObjectName(), sUnit = pCurve->GetUnit();
			if (!sUnit.isEmpty())
				sCurve = sCurve + " (" + sUnit + ")";
			sListHLable << sCurve;

			pCurve->GetData(pBuff + i * iRows, dStart, iRows);
			//pCurve->GetData(pBuff + (i + 1) * iRows, dStart, iRows);
		}

		populate(sListHLable, pBuff, iRows * iColumns);
		setEditable(0);

		delete[]pBuff;
		return true;
	}
	case EX3DPoints:
	{
		double *pData = pObj->GetData(iNumber);
		pBuff = new double[iNumber];

		iNumber /= 3;
		for (i = 0; i < 3; i++)
			for (j = 0; j < iNumber; j++)
				pBuff[i * iNumber + j] = pData[j * 3 + i];

		QStringList sListHLable;
		sListHLable << "X (m)" << "Y (m)" << "Z (m)";
		populate(sListHLable, pBuff, 3 * iNumber);

		delete[]pBuff;
		return true;
	}
	case EXRandomSection:
	{
		CXSeismicRandomSection *pRSection = (CXSeismicRandomSection *)pObj;
		vector<double> vecX, vecY;
		vector<int> vecLine, vecCDP;
		iNumber = pRSection->GetTurnPointNumber();
		pRSection->GetLineNumbers(vecLine, vecCDP);
		pRSection->GetXY(vecX, vecY);
		pBuff = new double[5 * iNumber];
		for (i = 0; i < iNumber; i++)
		{
			int iIDX = pRSection->GetTPTraceIndex(i);
			pBuff[i] = vecLine[iIDX];
			pBuff[i + iNumber] = vecCDP[iIDX];
			pBuff[i + 2 * iNumber] = vecX[iIDX];
			pBuff[i + 3 * iNumber] = vecY[iIDX];

			if (i < iNumber - 1)
				pBuff[i + 4 * iNumber] = pRSection->GetTPTraceIndex(i + 1) - iIDX + 1;
			else
				pBuff[i + 4 * iNumber] = 0;
		}

		QStringList sListHLable;
		sListHLable << "Inline" << "Crossline" << "X (m)" << "Y (m)" << "Number of Trace";
		populate(sListHLable, pBuff, 5 * iNumber);

		//	We do not want user directly edit well path through this data sheet.
		setEditable(0);

		delete[]pBuff;
		return true;
	}
	case EXWellTops:
	{
		CXWellTops *pTops = (CXWellTops *)pObj;
		iNumber = pTops->GetRecordNum();
		QStringList sListHLable;
		sListHLable << "Well" << "Formation" << "MD (m)" << "X (m)" << "Y (m)" << "Z (m)";
		QStringList sListContents = pTops->GetAllStringRecord();
		pBuff = pTops->GetAllFigureRecord();
		populate(sListHLable, sListContents, pBuff, iNumber);

		delete[]pBuff;
		return true;
	}
	default:
	{
		return false;
	}
	}

	return false;
}

bool CXDlgDataSheet::populate(QStringList sListCName, double *pData, int iLen)
{
	unsigned int i, j, iNumColumn = sListCName.size();
	if (iNumColumn == 0)
		return false;

	int iNumRow = iLen / iNumColumn;

	QStandardItemModel *pModel = new QStandardItemModel(iNumRow, iNumColumn);
	ui.tableView->setModel(pModel);
	pModel->setHorizontalHeaderLabels(sListCName);

	qint64 iOffset = 0;
	for (j = 0; j < iNumColumn; j++)
	{
		for (i = 0; i < iNumRow; i++)
		{
			pModel->setData(pModel->index(i, j), pData[iOffset], Qt::DisplayRole);
			iOffset++;
		}
	}
}

bool CXDlgDataSheet::populate(QStringList sListCName, QStringList sListContents, double *pBuff, int iNumRow)
{
	unsigned int i, j, iNumColumn = sListCName.size();
	if (iNumColumn == 0)
		return false;

	QStandardItemModel *pModel = new QStandardItemModel(iNumRow, iNumColumn);
	ui.tableView->setModel(pModel);
	pModel->setHorizontalHeaderLabels(sListCName);

	if (iNumRow == 0)
		return false;
	int iNumSCol = sListContents.size() / iNumRow;

	for (i = 0; i < iNumRow; i++)
	{
		for (j = 0; j < iNumSCol; j++)
		{
			//QStandardItem *pItem = new QStandardItem(sListContents[i + j * iNumRow]);
			//pModel->setItem(i, j, pItem);
			pModel->setData(pModel->index(i, j), sListContents[i + j * iNumRow], Qt::DisplayRole);
		}

		for (j = iNumSCol; j < iNumColumn; j++)
		{
			//QStandardItem *pItem = new QStandardItem(QString::number(pBuff[i + (j - iNumSCol) * iNumRow], 'f', 2));
			//pModel->setItem(i, j, pItem);
			pModel->setData(pModel->index(i, j), pBuff[i + (j - iNumSCol) * iNumRow], Qt::DisplayRole);
		}
	}
}

bool CXDlgDataSheet::populate(QStringList sListCName, QStringList sListContents)
{
	unsigned int i, j, iNumColumn = sListCName.size();
	if (iNumColumn == 0)
		return false;

	int iNumRow = sListContents.size() / iNumColumn;

	QStandardItemModel *pModel = new QStandardItemModel(iNumRow, iNumColumn);
	ui.tableView->setModel(pModel);
	pModel->setHorizontalHeaderLabels(sListCName);

	if (iNumRow == 0)
		return false;

	qint64 iOffset1 = 0, iOffset2 = 0;
	for (i = 0; i < iNumRow; i++)
	{
		for (j = 0; j < iNumColumn; j++)
		{
			//QStandardItem *pItem = new QStandardItem(sListContents[iOffset1]);
			//pModel->setItem(i, j, pItem);
			pModel->setData(pModel->index(i, j), sListContents[iOffset1], Qt::DisplayRole);
			iOffset1++;
		}
	}
}

void CXDlgDataSheet::setEditable(int iMode)
{
	QStandardItemModel *pModel = (QStandardItemModel *)ui.tableView->model();
	int i, j, iRow = pModel->rowCount(), iColumn = pModel->columnCount();
	if (iMode == 0)
	{
		//	Uneditable at all.
		ui.toolButtonRemove->setEnabled(false);
		ui.toolButtonRL->setEnabled(false);
		ui.toolButtonAppend->setEnabled(false);
		ui.toolButtonInsert->setEnabled(false);

		for (i = 0; i < iRow; i++)
			for (j = 0; j < iColumn; j++)
				pModel->item(i, j)->setEditable(false);
	}
	else if (iMode == 1)
	{
		//	Item maybe editable, not row
		ui.toolButtonRemove->setEnabled(false);
		ui.toolButtonRL->setEnabled(false);
		ui.toolButtonAppend->setEnabled(false);
		ui.toolButtonInsert->setEnabled(false);

		if (m_vecColumnEditable.size() == pModel->columnCount())
		{
			for (i = 0; i < iRow; i++)
				for (j = 0; j < iColumn; j++)
					pModel->item(i, j)->setEditable(m_vecColumnEditable[j]);
		}
	}
	else if (iMode == 2)
	{
		//	Can only append rows, or remove rows from the end.
		ui.toolButtonRemove->setEnabled(false);
		ui.toolButtonInsert->setEnabled(false);

		if (m_vecColumnEditable.size() == pModel->columnCount())
		{
			for (i = 0; i < iRow; i++)
				for (j = 0; j < iColumn; j++)
					pModel->item(i, j)->setEditable(m_vecColumnEditable[j]);
		}
	}
	else
	{
		//	Free edit.
		if (m_vecColumnEditable.size() == pModel->columnCount())
		{
			for (i = 0; i < iRow; i++)
				for (j = 0; j < iColumn; j++)
					pModel->item(i, j)->setEditable(m_vecColumnEditable[j]);
		}
	}
}

void CXDlgDataSheet::accept()
{
	if (m_bDataChanged)
		save();
}

void CXDlgDataSheet::reject()
{
	if (!m_bDataChanged)
	{
		QDialog::reject();
		return;
	}

	QMessageBox msgBox;
	msgBox.setText("Save and Exit");
	msgBox.setInformativeText("Save all modification and close the dialog?");
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	int ret = msgBox.exec();
	if (ret == QMessageBox::Discard)
	{
		QDialog::reject();
	}
	else if (ret == QMessageBox::Cancel)
	{
		return;
	}
	else
	{
		if (!check())
			return;

		save();
		QDialog::accept();
	}
}

bool CXDlgDataSheet::check()
{
	int i;
	CXObject *pObj = ::GetObjectByID(m_objID);
	switch (pObj->GetObjectType())
	{
	case EXWellPath:
	case EXWell:
	{
		//	So far is not editable.
		return true;	
	}
	case EXWellTD:
	{
		//	Well TD should have 2 columns of double figures.
		for (i = 0; i < 2; i++)
			if (!check(i, 0))
				return false;
		return true;
	}
	case EXWellCurve:
	{
		//	Only the 2nd column could be modified.
		return check(1, 0);
	}
	case EX3DPoints:
	{
		//	3D points should have 3 columns of double figures.
		for (i = 0; i < 3; i++)
			if (!check(i, 0))
				return false;
		return true;
	}
	case EXWellTops:
	{
		//	The first 2 columns are string.
		if(!check(0, 1) || !check(1, 1))
			return false;

		//	The 3rd column is double.
		if (!check(2, 0))
			return false;

		//	Well tops may has 3 or 5 columns.
		QStandardItemModel *pModel = (QStandardItemModel *)ui.tableView->model();
		int iCol = pModel->columnCount();
		if (iCol > 3)
		{
			if (!check(3, 0) || !check(4, 0))
				return false;
		}

		return true;
	}
	default:
	{
		return true;
	}
	}

	return true;
}

bool CXDlgDataSheet::check(int iCIDX, int iDataType)
{
	QStandardItemModel *pModel = (QStandardItemModel *)ui.tableView->model();
	int i, iRow = pModel->rowCount(), iColumn = pModel->columnCount();

	if (iCIDX >= iColumn)
		return false;

	if (iDataType == 0)
	{
		for (i = 0; i < iRow; i++)
		{
			bool bSu = false;
			if(pModel->item(i, iCIDX))
				pModel->item(i, iCIDX)->text().toDouble(&bSu);
			if (!bSu)
			{
				QString sError = "The item at row " + QString::number(i + 1) + ", column " + QString::number(iCIDX + 1) + " is not a double figure!";
				QMessageBox::warning(NULL, "Data Sheet", sError);
				return false;
			}
		}
	}
	else if (iDataType == 1)
	{
		for (i = 0; i < iRow; i++)
		{
			if (!pModel->item(i, iCIDX) || pModel->item(i, iCIDX)->text().isEmpty())
			{
				QString sError = "The item at row " + QString::number(i + 1) + ", column " + QString::number(iCIDX + 1) + " is blank!";
				QMessageBox::warning(NULL, "Data Sheet", sError);
				return false;
			}
		}
	}
	else
		return false;

	return true;
}

void CXDlgDataSheet::save()
{
	if (!check())
		return;

	QStandardItemModel *pModel = (QStandardItemModel *)ui.tableView->model();
	int i, j, iIDX = 0, iRow = pModel->rowCount(), iColumn = pModel->columnCount();
	CXObject *pObj = ::GetObjectByID(m_objID);
	QList<CXObject *> listObj;

	switch (pObj->GetObjectType())
	{
	case EXWellTD:
	{
		CXWellTD *pWellTD = (CXWellTD *)pObj;
		double *pBuff = new double[iRow * iColumn];

		for (j = 0; j < iColumn; j++)
		{
			for (i = 0; i < iRow; i++)
			{
				pBuff[iIDX] = pModel->item(i, j)->text().toDouble();
				iIDX++;
			}
		}

		pWellTD->ResetData(pBuff, iRow * iColumn);
		break;
	}
	case EXWellCurve:
	{
		CXWellCurve *pCurve = (CXWellCurve *)pObj;
		double *pData = pCurve->GetData();
		for (i = 0; i < iRow; i++)
		{
			pData[i] = pModel->item(i, 1)->text().toDouble();
		}
		pCurve->SetModifiedFlag();
		break;
	}
	case EX3DPoints:
	{
		CX3DPoints *pPoints = (CX3DPoints *)pObj;
		double *pBuff = new double[iRow * iColumn];

		for (i = 0; i < iRow; i++)
		{
			for (j = 0; j < iColumn; j++)
			{
				pBuff[iIDX] = pModel->item(i, j)->text().toDouble();
				iIDX++;
			}
		}

		pPoints->ResetData(pBuff, iRow * iColumn);
		break;
	}
	case EXWellTops:
	{
		CXWellTops *pTops = (CXWellTops *)pObj;
		pTops->ClearData();

		if (iColumn == 3)
		{
			for (i = 0; i < iRow; i++)
			{
				pTops->AddOneRecord(pModel->item(i, 0)->text(), pModel->item(i, 1)->text(),
					pModel->item(i, 2)->text().toDouble());
			}
		}
		else
		{
			for (i = 0; i < iRow; i++)
			{
				QVector3D vt;
				vt.setX(pModel->item(i, 2)->text().toFloat());
				vt.setX(pModel->item(i, 3)->text().toFloat());
				vt.setX(pModel->item(i, 4)->text().toFloat());
				pTops->AddOneRecord(pModel->item(i, 0)->text(), pModel->item(i, 1)->text(), vt);
			}
		}

		break;
	}
	default:
	{
		return;
	}
	}

	m_bDataChanged = false;
	ui.buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
	ui.toolButtonFlush->setEnabled(false);
}

void CXDlgDataSheet::slotRowEdit()
{
	QStandardItemModel *pModel = (QStandardItemModel *)ui.tableView->model();
	int iRow = pModel->rowCount();
	m_bDataChanged = true;

	if (sender() == ui.toolButtonRemove)
	{
		QModelIndex qIndex = ui.tableView->currentIndex();
		int iCRow = qIndex.row();
		pModel->removeRow(iCRow);
	}
	else if (sender() == ui.toolButtonRL)
	{
		pModel->removeRow(iRow - 1);
	}
	else if (sender() == ui.toolButtonAppend)
	{
		pModel->insertRow(iRow);
	}
	else if (sender() == ui.toolButtonInsert)
	{
		QModelIndex qIndex = ui.tableView->currentIndex();
		int iCRow = qIndex.row();
		pModel->insertRow(iCRow + 1);
	}

	ui.buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
}

void CXDlgDataSheet::slotDataChanged()
{
	m_bDataChanged = true;

	ui.buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
	ui.toolButtonFlush->setEnabled(m_bNeedFlush);
}

void CXDlgDataSheet::setTips(EXObjectType eType)
{
	QString sTips;
	switch (eType)
	{
	case EXWell:
	{
		sTips = "<html><head/><body><p>This is a read-only dialog to just show all the log data of this well.</p>\
<p>You can edit one log curve through its own data sheet dialog.</p></body></html>";
		break;
	}
	case EXWellTD:
	{
		sTips = "<html><head/><body><p>You can edit the TD curve direclty here, \
including add/remove nodes or modify any node's value.</p>\
<p>But you should keep both TVDSS and TWT in ascending order!</p></body></html>";
		break;
	}
	case EX3DPoints:
	{
		sTips = "<html><head/><body><p>You can edit the points direclty here, \
including add/remove point or modify any point's value.</p></body></html>";
		break;
	}
	case EXWellCurve:
	{
		sTips = "<html><head/><body><p>You can not add or remove rows or modify the MD value, to avoid changing the samples' step.</p> \
<p>But you can direclty edit any curve value item!</p></body></html>";
		break;
	}
	default:
	{
		sTips = "<html><head/><body><p>This is a read-only dialog to just show the data.</p>\
<p>You can not edit the data through this dialog direclty!</p></body></html>";
	}
	}

	ui.label->setToolTip(sTips);
}