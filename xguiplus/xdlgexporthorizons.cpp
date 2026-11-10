#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include "xdlgexporthorizons.h"
#include "x3dhorizon.h"
#include "xglobal.h"
#include "xprogressbar.h"

CXDlgExportHorizons::CXDlgExportHorizons(CXObject *pObj, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	initialize(pObj);
}

CXDlgExportHorizons::~CXDlgExportHorizons()
{

}

void CXDlgExportHorizons::initialize(CXObject *pObj)
{
	ui.lineEditDir->setText(::GetProjectPath());

	if (pObj->GetObjectType() == EXHorizonFolder)
		m_listObj = pObj->GetChildren(EX3DHorizon);
	else if (pObj->GetParent()->GetObjectType() == EXHorizonFolder)
		m_listObj = pObj->GetParent()->GetChildren(EX3DHorizon);
	else if (pObj->GetObjectType() == EXSurfaceFolder)
	{
		m_listObj = pObj->GetChildren(EX3DSurface);
		ui.checkBoxLine->setText("I, J");
	}
	else if (pObj->GetParent()->GetObjectType() == EXSurfaceFolder)
	{
		m_listObj = pObj->GetParent()->GetChildren(EX3DSurface);
		ui.checkBoxLine->setText("I, J");
	}
	else
		m_listObj << pObj;

	QIcon qIcon(::GetIconPath() + "Horizon.png");
	for (int i = 0; i < m_listObj.size(); i++)
	{
		QListWidgetItem *pItem = new QListWidgetItem(qIcon, m_listObj.at(i)->GetObjectName());
		if (pObj == m_listObj.at(i))
			pItem->setCheckState(Qt::Checked);
		else
			pItem->setCheckState(Qt::Unchecked);
		ui.listWidget->addItem(pItem);
	}

	connect(ui.pushButtonBrowser, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
	connect(ui.pushButtonSelectAll, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
	connect(ui.pushButtonUnselectAll, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));

	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
}

void CXDlgExportHorizons::slotButtonClicked()
{
	if (sender() == ui.pushButtonBrowser)
	{
		QString strDirPath = ui.lineEditDir->text();

		QString strExportDir = QFileDialog::getExistingDirectory(NULL, "Export Seismic Data to  SEGY File", strDirPath);
		if (strExportDir.isEmpty())
		{
			return;
		}

		//	Make sure the file is writable.
		strExportDir += "/";
		QFile file(strExportDir + "ttttmp");
		if (!file.open(QIODevice::WriteOnly))
		{
			QMessageBox::warning(NULL, "Export to ASCII Files", GetTr("Can not write in this directory!"));
			return;
		}

		file.close();
		QFile::remove(strExportDir + "ttttmp");

		ui.lineEditDir->setText(strExportDir);
	}
	else
	{
		Qt::CheckState sta = Qt::Unchecked;
		if (sender() == ui.pushButtonSelectAll)
			sta = Qt::Checked;

		for (int i = 0; i < ui.listWidget->count(); i++)
			ui.listWidget->item(i)->setCheckState(sta);
	}
}

void CXDlgExportHorizons::accept()
{
	bool bLine = ui.checkBoxLine->isChecked();
	bool bXY = ui.checkBoxXY->isChecked();

	if (!bLine && !bXY)
	{
		QMessageBox::warning(NULL, "Export to ASCII Files", GetTr("Inline and crossline, or X and Y, at least select one of them!"));
		return;
	}

	int iNum = 0;
	for (int i = 0; i < m_listObj.size(); i++)
	{
		if (ui.listWidget->item(i)->checkState() == Qt::Unchecked)
			continue;

		if (!exportOneHorizon(m_listObj.at(i)))
			return;
		iNum++;
	}

	if (iNum == 0)
	{
		QMessageBox::warning(NULL, "Export to ASCII Files", GetTr("No horizon selected!"));
		return;
	}

	QDialog::accept();
}

bool CXDlgExportHorizons::exportOneHorizon(CXObject *pObj)
{
	QString sFile = ui.lineEditDir->text() + pObj->GetObjectName() + ".txt";
	QFile qFile(sFile);
	if (!qFile.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(NULL, "Export to ASCII file", "Can not open " + sFile + " to write!");
		return false;
	}
	QTextStream stream(&qFile);

	bool bLine = ui.checkBoxLine->isChecked();
	bool bXY = ui.checkBoxXY->isChecked();
	bool bInv = ui.checkBoxInv->isChecked();

	if (pObj->GetObjectType() == EX3DHorizon)
	{
		stream << "#\t3D Horizon File Exported by XStudio\n";
		QString str = "#	";
		if (bLine)
			str += "Inline\tCrossline\t";
		if (bXY)
			str += "X\t\tY\t\t";
		str += "Z\n";
		stream << str;

		CX3DHorizon *pHor = (CX3DHorizon *)pObj;
		CXSeismicUTMTool& utm = pHor->GetUTM();
		int i, j, nI = utm.GetNI(), nJ = utm.GetNJ();
		float *pData = pHor->GetData();

		CXProgressBar progress("Export Horizon ", "Exporting " + pObj->GetObjectName(), nI);

		int iLine, iCDP;
		double dX, dY;
		for (i = 0; i < nI; i++)
		{
			if (progress.IsAborted())
			{
				//	Delete the file!
				qFile.close();
				QFile::remove(qFile.fileName());

				return false;
			}

			//progress
			progress.SetValue(i);

			for (j = 0; j < nJ; j++)
			{
				if (!bInv && pData[i * nJ + j] == g_dInvalidData)
					continue;

				str = "";
				if (bLine)
				{
					utm.IJToLine(i, j, iLine, iCDP);
					str = QString::number(iLine) + "\t" + QString::number(iCDP) + "\t";
				}
				if (bXY)
				{
					utm.IJToXY(i, j, dX, dY);
					str = str + QString::number(dX, 'f', 2) + "\t" + QString::number(dY, 'f', 2) + "\t";
				}

				if (pData[i * nJ + j] != g_dInvalidData)
					str = str + QString::number(pData[i * nJ + j], 'f', 2) + "\n";
				else
					str = str + ui.lineEditInv->text() + "\n";

				stream << str;
			}
		}
	}
	else
	{
		stream << "#\t3D Surface File Exported by XStudio\n";
		QString str = "#	";
		if (bLine)
			str += "I\t\tJ\t\t";
		if (bXY)
			str += "X\t\tY\t\t";
		str += "Z\n";
		stream << str;

		CX3DHorizon *pHor = (CX3DHorizon *)pObj;
		CXSeismicUTMTool& utm = pHor->GetUTM();
		int i, j, nI = utm.GetNI(), nJ = utm.GetNJ();
		float *pData = pHor->GetData();

		CXProgressBar progress("Export Surface ", "Exporting " + pObj->GetObjectName(), nI);

		double dX, dY;
		for (i = 0; i < nI; i++)
		{
			if (progress.IsAborted())
			{
				//	Delete the file!
				qFile.close();
				QFile::remove(qFile.fileName());

				return false;
			}

			//progress
			progress.SetValue(i);

			for (j = 0; j < nJ; j++)
			{
				if (!bInv && pData[i * nJ + j] == g_dInvalidData)
					continue;

				str = "";
				if (bLine)
				{
					str = QString::number(i) + "\t" + QString::number(j) + "\t";
				}
				if (bXY)
				{
					utm.IJToXY(i, j, dX, dY);
					str = str + QString::number(dX, 'f', 2) + "\t" + QString::number(dY, 'f', 2) + "\t";
				}

				if (pData[i * nJ + j] != g_dInvalidData)
					str = str + QString::number(pData[i * nJ + j], 'f', 2) + "\n";
				else
					str = str + ui.lineEditInv->text() + "\n";

				stream << str;
			}
		}
	}

	qFile.close();
	return true;
}