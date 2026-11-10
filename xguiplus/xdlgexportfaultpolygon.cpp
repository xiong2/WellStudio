#include "xdlgexportfaultpolygon.h"
#include <QFileDialog>
#include <QMessageBox>

#include "xglobal.h"
#include "x2dpolygon.h"
#include "xguiutility.h"
#include "x2dpolygon.h"
#include "xprogressbar.h"

CXDlgExportFaultPolygon::CXDlgExportFaultPolygon(CXObject* pObj, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	Q_ASSERT(pObj && pObj->GetObjectType() == EXFaultPolygonFolder);
	_Init(pObj);
}

CXDlgExportFaultPolygon::~CXDlgExportFaultPolygon()
{

}

void CXDlgExportFaultPolygon::slotSelectFile()
{
	QString strExportFile = QFileDialog::getSaveFileName(nullptr, "Export fault polygons to ASCII file.", ui.lineEditPath->text(), "ASCII File (*.txt)");
	if (strExportFile.isEmpty()) return;

	if (!NXGUIUtility::IsFileCanWritable("Export to ASCII File", strExportFile))
		return;

	ui.lineEditPath->setText(strExportFile);
}

void CXDlgExportFaultPolygon::slotSelectItems()
{
	Qt::CheckState chkState = sender() == ui.btnSelectAll ? Qt::Checked : Qt::Unchecked;
	for (int i = 0; i != ui.listFaultPolygon->count(); ++i)
		ui.listFaultPolygon->item(i)->setCheckState(chkState);
}

void CXDlgExportFaultPolygon::slotConflict(int iState)
{
	if (sender() == ui.chkTab && iState > 0)
	{
		ui.chkSpace->setChecked(false);
	}
	else if (sender() == ui.chkSpace && iState > 0)
	{
		ui.chkTab->setChecked(false);
	}
}

void CXDlgExportFaultPolygon::_Init(CXObject* pObj)
{
	ui.lineEditPath->setText(::GetProjectPath() + pObj->GetObjectName() + ".txt");
	
	for (auto pObjFaultPolygon : pObj->GetChildren(EXFaultPolygon))
	{
		auto pItem = new QListWidgetItem(QIcon(::GetIconPath() + pObjFaultPolygon->GetIconName()), pObjFaultPolygon->GetObjectName());
		pItem->setData(Qt::UserRole, pObjFaultPolygon->GetObjectID());
		pItem->setCheckState(Qt::Checked);
		ui.listFaultPolygon->addItem(pItem);
	}

	connect(ui.btnSelectPath, &QPushButton::clicked, this, &CXDlgExportFaultPolygon::slotSelectFile);
	connect(ui.btnSelectAll, &QPushButton::clicked, this, &CXDlgExportFaultPolygon::slotSelectItems);
	connect(ui.btnUnselectAll, &QPushButton::clicked, this, &CXDlgExportFaultPolygon::slotSelectItems);
	connect(ui.chkTab, &QCheckBox::stateChanged, this, &CXDlgExportFaultPolygon::slotConflict);
	connect(ui.chkSpace, &QCheckBox::stateChanged, this, &CXDlgExportFaultPolygon::slotConflict);
}

void CXDlgExportFaultPolygon::accept()
{
	auto _CheckDelimiters = [](const Ui::CXDlgExportFaultPolygon& ui) {
		return ui.chkTab->isChecked() || ui.chkSpace->isChecked() || ui.chkComma->isChecked();
	};

	if (!_CheckDelimiters(ui))
	{
		QMessageBox::warning(this, "Export Fault Polygon", "You must choose at least one delimiter.");
		return;
	}

	QString strDelimiter = [this]() {
		QString str;
		if (ui.chkComma->isChecked())
			str += ",";
		if (ui.chkTab->isChecked())
			str += "\t";
		else if (ui.chkSpace->isChecked())
			str += " ";
		return str;
	}();

	QFile file(ui.lineEditPath->text());
	if (!file.open(QIODevice::WriteOnly)) return;

	QTextStream stream(&file);

	auto _GetListWidgetCheckedItems = [](QListWidget* pWidget) {
		QList<QListWidgetItem*> listItem;
		for (int i = 0; i < pWidget->count(); ++i)
		{
			if (pWidget->item(i)->checkState() == Qt::Checked)
				listItem << pWidget->item(i);
		}
		return listItem;
	};

	QList<QListWidgetItem*> listItem = _GetListWidgetCheckedItems(ui.listFaultPolygon);
	CXProgressBar progress("Export Fault Polygon ", "Exporting " + file.fileName(), listItem.size());

	for (int i = 0; i != listItem.size(); ++i)
	{
		if (progress.IsAborted())
		{
			//	Delete the file!
			file.close();
			QFile::remove(file.fileName());
			return;
		}

		//progress
		progress.SetValue(i);

		QUuid itemID = listItem[i]->data(Qt::UserRole).toUuid();
		auto pFaultPolygon = dynamic_cast<CX2DPolygon*>(::GetObjectByID(itemID));
		if (!pFaultPolygon || pFaultPolygon->GetObjectType() != EXFaultPolygon) continue;

		uint nNum;
		double *pData = pFaultPolygon->GetData(nNum);
		for (uint j = 0; j < nNum; j += 2)
		{
			stream << QString("%1%2%3%4%5").arg(pData[j], 0, 'f', 1).arg(strDelimiter)
				.arg(pData[j + 1], 0, 'f', 1).arg(strDelimiter)
				.arg(ui.listFaultPolygon->row(listItem[i]) + 1);
			if (ui.chkExportName->isChecked())
				stream << strDelimiter << listItem[i]->text();
			stream << "\n";
		}
	}

	QDialog::accept();
}