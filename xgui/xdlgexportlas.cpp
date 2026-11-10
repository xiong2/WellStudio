#include <qcheckbox.h>
#include <qpushbutton.h>
#include <QFileDialog>
#include <QFile>
#include <qtextstream.h>
#include <qmessagebox.h>
#include "xdlgexportlas.h"
#include "xwell.h"
#include "xglobal.h"
#include "xwellcurve.h"
#include "xwellpath.h"
#include "xtemplate.h"

CXDlgExportLAS::CXDlgExportLAS(CXObject *pObj, QWidget *pParent): QDialog(pParent)
{
	ui.setupUi(this);
	m_pObject = pObj;

	if (pObj->GetObjectType() == EXWell)
	{
		QString sFile = ::GetProjectPath() + pObj->GetObjectName() + ".las";
		ui.lineEditDirectory->setText(sFile);

		QList<CXObject *> listCurves = pObj->GetChildren(EXWellCurve);
		int iSize = listCurves.size();
		if (iSize == 0)
			return;

		ui.tableWidget->setRowCount(iSize);
		ui.tableWidget->setColumnCount(2);
		QStringList sListVHeader;
		for (int i = 0; i < iSize; i++)
		{
			sListVHeader << QString::number(i + 1);

			//	1st column is the check box.
			QCheckBox *pCheckBox = new QCheckBox;
			pCheckBox->setChecked(true);
			ui.tableWidget->setCellWidget(i, 0, pCheckBox);

			//	2nd column is the curve name.
			ui.tableWidget->setItem(i, 1, new QTableWidgetItem(listCurves[i]->GetObjectName()));
		}
	}
	else if (pObj->GetObjectType() == EXWellFolder)
	{
		ui.label_3->setText("Export to:");
		ui.lineEditDirectory->setText(::GetProjectPath());
		ui.groupBox->setTitle("Wells");

		QList<CXObject *> listObj = pObj->GetChildren(EXWell);
		int iSize = listObj.size();
		if (iSize == 0)
			return;

		ui.tableWidget->setRowCount(iSize);
		ui.tableWidget->setColumnCount(2);
		QStringList sListVHeader;
		for (int i = 0; i < iSize; i++)
		{
			sListVHeader << QString::number(i + 1);

			//	1st column is the check box.
			QCheckBox *pCheckBox = new QCheckBox;
			pCheckBox->setChecked(true);
			ui.tableWidget->setCellWidget(i, 0, pCheckBox);

			//	2nd column is the curve name.
			ui.tableWidget->setItem(i, 1, new QTableWidgetItem(listObj[i]->GetObjectName()));
		}
	}
	else
		return;

	connect(ui.pushButtonAll, SIGNAL(clicked()), this, SLOT(slotSelectCurves()));
	connect(ui.pushButtonNone, SIGNAL(clicked()), this, SLOT(slotSelectCurves()));
	connect(ui.pushButtonBrowse, SIGNAL(clicked()), this, SLOT(slotSelectFile()));
}

CXDlgExportLAS::~CXDlgExportLAS()
{
}

void CXDlgExportLAS::slotSelectCurves()
{
	int i;
	QPushButton *pPB = dynamic_cast<QPushButton *>(sender());
	if(!pPB)
		return;

	//	Select all or dis-select all?
	bool bAll = (pPB == ui.pushButtonAll);

	for(i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidget->cellWidget(i, 0));
		pCheckBox->setChecked(bAll);
	}
}

void CXDlgExportLAS::slotSelectFile()
{
	if (m_pObject->GetObjectType() == EXWell)
	{
		QString strFilePath = ui.lineEditDirectory->text();

		QString strFilter = "Well Data Files [LAS Format] (*.las)";
		QString strExportFile = QFileDialog::getSaveFileName(NULL, "Export Well Data to File", strFilePath, strFilter) ;
		if(strExportFile.isEmpty())
		{
			return ;
		}

		//	Make sure the file is writable.
		QFile file(strExportFile) ;
		if(!file.open(QIODevice::WriteOnly))
		{
			QMessageBox::warning ( NULL, "Export to LAS file" , GetTr("文件不可写！"));
			return ;
		}

		ui.lineEditDirectory->setText(strExportFile);
	}
	else
	{
		QString sDir = QFileDialog::getExistingDirectory(NULL, "Select the export directory");

		if (!sDir.isEmpty())
			ui.lineEditDirectory->setText(sDir);
	}
}

void CXDlgExportLAS::accept()
{
	if (m_pObject->GetObjectType() == EXWell)
		exportLas();
	else
		exportPath();
}

void CXDlgExportLAS::exportLas()
{
	CXWell *pWell = dynamic_cast<CXWell *>(m_pObject);
	int i, j;
	QString strFile = ui.lineEditDirectory->text();
	QFile qFile(strFile) ;
	if(!qFile.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning ( NULL, "Export to LAS file" , GetTr("文件不可写！"));
		return ;
	}

	QTextStream stream(&qFile);

	//	File header.
	stream<<"#-----------------------------------------------------------------------------------\n";
	stream<<"~Version Information Section\n";
	stream<<"VERS.          2.0                                     : CWLS LOG ASCII Standard\n";
	stream<<"WRAP.          NO                                      : One line per depth step\n";

	//	Well header.
	bool bMetric = ::UsingMetricUnit();
	QString sUnit = "M";
	if(!bMetric)
		sUnit = "F";
	double dStart, dEnd, dStep;
	pWell->GetDepthRange(dStart, dEnd);
	dStep = pWell->GetWellStep();

	stream<<"#-----------------------------------------------------------------------------------\n";
	stream<<"~Well Information Section\n";
	stream<<"STRT."<<sUnit<<"        "<<QString::number(dStart)<<"                : Start Depth\n";
	stream<<"STOP."<<sUnit<<"        "<<QString::number(dEnd)<<"                : Stop Depth\n";
	stream<<"STEP."<<sUnit<<"        "<<QString::number(dStep)<<"                : Step\n";
	stream<<"NULL."<<"        "<<QString::number(::g_dInvalidData)<<"                : Null Value\n";
	stream<<"WELL."<<"        "<< pWell->GetObjectName()<<"                : Well\n";

	unsigned int iNumPoints = (dEnd - dStart) / dStep + 1;
	QStringList sListAtt = pWell->GetExistAttribute();
	for(i = 0; i < sListAtt.size(); i++)
	{
		QString sAtt = pWell->GetAttribute(sListAtt[i]);
		stream<<sListAtt[i]<<".        "<<sAtt<<"                :\n";
	}

	//	Curves header.
	QList<CXObject *> listObj = pWell->GetChildren(EXWellCurve);
	if(listObj.size() != ui.tableWidget->rowCount())
	{
		qFile.close();
		QMessageBox::warning ( NULL, "Export to LAS file" , GetTr("曲线数目错误！")) ;

		return;
	}

	QList<CXWellCurve *> listCurves;
	for(i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidget->cellWidget(i, 0));
		if(pCheckBox->isChecked())
		{
			CXWellCurve *pCurve = (CXWellCurve *)listObj[i];
			CXTemplate *pTemplate = CXTemplate::GetTemplate(pCurve->GetTemplateID());
			if(pTemplate->GetName() != "MD" && pTemplate->GetName() != "TVD")
				listCurves<<(CXWellCurve *)(listObj[i]);
		}
	}

	int iNumCurves = listCurves.size();
	if(iNumCurves == 0)
	{
		qFile.close();
		QMessageBox::warning ( NULL, "Export to LAS file" , GetTr("没有选择输出曲线！")) ;

		return;
	}

	QApplication::setOverrideCursor( Qt::WaitCursor );

	stream<<"#-----------------------------------------------------------------------------------\n";
	stream<<"~Curve Information Section\n";
	stream<<"DEPTH."<<sUnit<<"                :\n";
	for(i = 0; i < iNumCurves; i++)
	{
		stream<<listCurves[i]->GetObjectName()<<"."<<listCurves[i]->GetUnit()<<"                :\n";
	}

	//	Curves.
	stream<<"#-----------------------------------------------------------------------------------\n";
	stream<<"~ASCII Log Data Section\n";

	//	Read data from selected curves.
	double **pData = new double*[iNumCurves];
	for(i = 0; i < iNumCurves; i++)
	{
		pData[i] = new double[iNumPoints];
		listCurves[i]->GetData(pData[i], dStart, iNumPoints);
	}

	//	Loop to export each point.
	for(i = 0; i < iNumPoints; i++)
	{
		stream<<QString::number(dStart + i * dStep);

		for(j = 0; j < iNumCurves; j++)
		{
			stream<<"        " <<QString::number(pData[j][i]);
		}

		stream<<"\n";
	}

	//	Free the memory.
	for(i = 0; i < iNumCurves; i++)
	{
		delete []pData[i];
	}
	delete []pData;


	//	Finished!
	qFile.close();

	QApplication::restoreOverrideCursor();

	QDialog::accept();
}

void CXDlgExportLAS::exportPath()
{
	int i;
	QList<CXObject *> listObj = m_pObject->GetChildren(EXWell);
	QList<CXWell *> listWell;
	for (i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidget->cellWidget(i, 0));
		if (pCheckBox->isChecked())
		{
			listWell << (CXWell *)(listObj[i]);
		}
	}

	int iNumCurves = listWell.size();
	if (iNumCurves == 0)
	{
		QMessageBox::warning(NULL, "Export Well Path", GetTr("没有选择目标井！"));

		return;
	}

	QApplication::setOverrideCursor(Qt::WaitCursor);

	foreach(CXWell *pWell, listWell)
	{
		QString strFile = ui.lineEditDirectory->text() + "/" + pWell->GetObjectName() + ".dev";
		QFile qFile(strFile);
		if (!qFile.open(QIODevice::WriteOnly))
		{
			QMessageBox::warning(NULL, "Export Well Path", GetTr("文件不可写！"));
			return;
		}

		QTextStream stream(&qFile);

		CXWellPath *pWPath = pWell->GetWellPath();
		unsigned int iSize;
		double *pData = pWPath->GetData(iSize);
		double *pMDData = pWPath->GetMdData();

		stream << "X		Y		Z		MD\n";
		iSize /= 3;
		for (i = 0; i < iSize; i++)
		{
			stream << QString::number(pData[3 * i], 'f', 2) + "\t" + QString::number(pData[3 * i + 1], 'f', 2) + "\t" +
				QString::number(pData[3 * i + 2], 'f', 2) + "\t" + QString::number(pMDData[i]) + "\n";
		}

		qFile.close();
	}

	QApplication::restoreOverrideCursor();

	QDialog::accept();
}