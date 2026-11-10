#include <QFile>
#include <qfileinfo.h>
#include "xdlgimportreservoir.h"
#include "xdlgcalculatingprogress.h"
#include "ximportreservoirthread.h"
#include "xeclipseobject.h"
#include "xgridmodel.h"
#include "xreservoirmodel.h"
#include "xpropertymodel.h"
#include "xglobal.h"
#include "xproject.h"
#include "xtree.h"

CXDlgImportReservoir::CXDlgImportReservoir(QString sFileName, QWidget *parent): QDialog(parent)
{
	ui.setupUi(this);

	m_sFileName = sFileName;

	QFileInfo qFI(sFileName);
	ui.lineEditName->setText(qFI.baseName());
	ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);

	//	Unit.
	if(::UsingMetricUnit())
	{
		ui.lineEditPrjXUnit->setText("m");
		ui.lineEditPrjZUnit->setText("m");
	}
	else
	{
		ui.lineEditPrjXUnit->setText("ft");
		ui.lineEditPrjZUnit->setText("ft");
	}

	//	Range.
	QStringList sListRangeHHeader, sListRangeVHeader;
	sListRangeHHeader<<GetTr("Min")<<GetTr("Max")<<GetTr("Delta");
	sListRangeVHeader<<GetTr(" X ")<<GetTr(" Y ")<<GetTr(" Z ");
	ui.tableWidgetDimension->setColumnCount(3);
	ui.tableWidgetDimension->setRowCount(3);
	ui.tableWidgetDimension->setHorizontalHeaderLabels(sListRangeHHeader);
	ui.tableWidgetDimension->setVerticalHeaderLabels(sListRangeVHeader);
	ui.tableWidgetDimension->setColumnWidth(0, 160);
	ui.tableWidgetDimension->setColumnWidth(1, 160);
	ui.tableWidgetDimension->setColumnWidth(2, 160);

	//	Properties.
	QStringList sListPropHHeader;
 	if(::UsingChinese())
		sListPropHHeader<<GetTr("加载")<<GetTr("输入关键字")<<GetTr("曲线模板")<<GetTr("属性名称");
	else
		sListPropHHeader<<"Load"<<"Input Keyword"<<"Curve Template"<<"Property Name";
	ui.tableWidgetProperties->setColumnCount(4);
	ui.tableWidgetProperties->setHorizontalHeaderLabels(sListPropHHeader);
	ui.tableWidgetDimension->setColumnWidth(0, 60);
	ui.tableWidgetDimension->setColumnWidth(1, 160);
	ui.tableWidgetDimension->setColumnWidth(2, 160);
	ui.tableWidgetDimension->setColumnWidth(3, 160);

	connect(ui.pushButtonScan, SIGNAL(clicked()), this, SLOT(slotScan()));
	connect(ui.pushButtonSelectAll, SIGNAL(clicked()), this, SLOT(slotSelectAll()));
	connect(ui.pushButtonDeselectAll, SIGNAL(clicked()), this, SLOT(slotDeselectAll()));

	m_pThread = NULL;
}

CXDlgImportReservoir::~CXDlgImportReservoir()
{
	if(m_pThread)
		delete m_pThread;
}

void CXDlgImportReservoir::slotScan()
{
	double dInv = ui.lineEditInvalid->text().toDouble();

	m_pThread = new CXImportReservoirThread(m_sFileName);
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, this);
	m_pThread->m_dInvalid = dInv;

	pProgress->show();
	m_pThread->start();
	bool bAccept = false;
	if ( pProgress->exec() == QDialog::Accepted)
	{	
		ui.lineEditNI->setText(QString::number(m_pThread->m_pEObj->m_nI));
		ui.lineEditNJ->setText(QString::number(m_pThread->m_pEObj->m_nJ));
		ui.lineEditNK->setText(QString::number(m_pThread->m_pEObj->m_nK));
		ui.lineEditTotalCells->setText(QString::number(m_pThread->m_pEObj->m_nTotalCells));

		unsigned int iSize = m_pThread->m_pGridModel->GetAllCells().count();
		ui.lineEditValidCells->setText(QString::number(iSize));
		ui.lineEditValidPercentage->setText(QString::number((int)(iSize * 100 / m_pThread->m_pEObj->m_nTotalCells)));

		//	Update the X, Y, Z range.
		double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
		m_pThread->m_pGridModel->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
		ui.tableWidgetDimension->setItem(0, 0, new QTableWidgetItem(QString::number(dXMin)));
		ui.tableWidgetDimension->setItem(0, 1, new QTableWidgetItem(QString::number(dXMax)));
		ui.tableWidgetDimension->setItem(0, 2, new QTableWidgetItem(QString::number(dXMax - dXMin)));
		ui.tableWidgetDimension->setItem(1, 0, new QTableWidgetItem(QString::number(dYMin, 'f', 0)));
		ui.tableWidgetDimension->setItem(1, 1, new QTableWidgetItem(QString::number(dYMax, 'f', 0)));
		ui.tableWidgetDimension->setItem(1, 2, new QTableWidgetItem(QString::number(dYMax - dYMin)));
		ui.tableWidgetDimension->setItem(2, 0, new QTableWidgetItem(QString::number(dZMin)));
		ui.tableWidgetDimension->setItem(2, 1, new QTableWidgetItem(QString::number(dZMax)));
		ui.tableWidgetDimension->setItem(2, 2, new QTableWidgetItem(QString::number(dZMax - dZMin)));

		//	Update the properties table.
		int i = 0;
		QStringList sListPropVHeader, sListPropName;
		ui.tableWidgetProperties->setRowCount(m_pThread->m_listProps.size());
		foreach(CXPropertyModel *pProp, m_pThread->m_listProps)
		{
			sListPropVHeader<<QString::number(i + 1);
			QCheckBox *pCheckBox = new QCheckBox;
			pCheckBox->setChecked(true);
			ui.tableWidgetProperties->setCellWidget(i, 0, pCheckBox);

			QString sPropName = pProp->GetObjectName(), sPropNewName = pProp->GetObjectName();
			ui.tableWidgetProperties->setItem(i, 1, new QTableWidgetItem(sPropName));

			if(sListPropName.contains(sPropNewName))
			{
				int j = 2;
				sPropNewName = sPropName + " (" + QString::number(j) + ")";
				while(sListPropName.contains(sPropNewName))
				{
					j++;
					sPropNewName = sPropName + " (" + QString::number(j) + ")";
				}
			}
			sListPropName<<sPropNewName;

			QLineEdit *pLineEt = new QLineEdit;
			pLineEt->setText(sPropNewName);
			ui.tableWidgetProperties->setCellWidget(i, 3, pLineEt);

			i++;
		}
		ui.tableWidgetProperties->setVerticalHeaderLabels(sListPropVHeader);

		ui.pushButtonScan->setDisabled(true);
		ui.lineEditInvalid->setDisabled(true);
		ui.buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
	}
}

void CXDlgImportReservoir::slotSelectAll()
{
	for(int i = 0; i < ui.tableWidgetProperties->rowCount(); i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidgetProperties->cellWidget(i, 0));
		pCheckBox->setChecked(true);
	}
}

void CXDlgImportReservoir::slotDeselectAll()
{
	for(int i = 0; i < ui.tableWidgetProperties->rowCount(); i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidgetProperties->cellWidget(i, 0));
		pCheckBox->setChecked(false);
	}
}

void CXDlgImportReservoir::accept()
{
	if(!m_pThread)
		return;
			
	QString strModelName = ui.lineEditName->text();
	m_pThread->m_pGridModel->SetObjectName("Geometry");

	CXReservoirModel *pResModel = new CXReservoirModel(m_pThread->m_pGridModel, strModelName);
	m_pThread->m_pGridModel = NULL;

	for(int i = 0; i < m_pThread->m_listProps.size(); i++)
	{
		QCheckBox *pCheckBox = (QCheckBox *)(ui.tableWidgetProperties->cellWidget(i, 0));
		if(pCheckBox->isChecked())
		{
			QLineEdit *pLineEt = (QLineEdit *)(ui.tableWidgetProperties->cellWidget(i, 3));
			m_pThread->m_listProps.at(i)->SetObjectName(pLineEt->text());
			pResModel->AddChild(m_pThread->m_listProps.at(i));
		}
		else
		{
			delete m_pThread->m_listProps.at(i);
		}
	}
	m_pThread->m_listProps.clear();

	::GetProject()->AddChild(pResModel);
	::AddObjectEvent(pResModel);

	QDialog::accept();
}