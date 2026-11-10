#include <qmessagebox.h>
#include "xcheckboxwidget.h"
#include "gsdlgcurvaturecalculation.h"
#include "x3dhorizon.h"
#include "xdlgcalculatingprogress.h"
#include "gsthreadsurfacecurvature.h"
#include "xtree.h"

GSDlgCurvatureCalculation::GSDlgCurvatureCalculation(CXObject *pObj, QWidget * parent) : QDialog(parent) 
{
	m_pHorizon = pObj;
	ui.setupUi(this);

	initialUI();
}

GSDlgCurvatureCalculation::~GSDlgCurvatureCalculation() 
{
	
}

void GSDlgCurvatureCalculation::initialUI()
{
	QStringList sListAtt = GSThreadSurfaceCurvature::m_sListAtt;

	ui.tableWidget->setColumnWidth(0, 40);
	ui.tableWidget->setColumnWidth(1, 200);
	ui.tableWidget->setColumnWidth(2, 40);
	ui.tableWidget->setColumnWidth(3, 200);

	int iRowNum = (int)(sListAtt.size() / 2. + 0.9);
	ui.tableWidget->setRowCount(iRowNum);


	for (int i = 0; i < iRowNum; i++)
	{
		//	1st column is the check box.
		CXCheckBoxWidget *pCheckBox = new CXCheckBoxWidget;
		ui.tableWidget->setCellWidget(i, 0, pCheckBox);

		//	2nd column is the isopach name.
		QTableWidgetItem *pWItem = new QTableWidgetItem(sListAtt[2 * i]);
		ui.tableWidget->setItem(i, 1, pWItem);

		if(2 * i + 1 >= sListAtt.size())
			break;

		//	3rd column is the check box.
		pCheckBox = new CXCheckBoxWidget;
		ui.tableWidget->setCellWidget(i, 2, pCheckBox);

		//	4th column is the isopach name.
		pWItem = new QTableWidgetItem(sListAtt[2 * i + 1]);
		ui.tableWidget->setItem(i, 3, pWItem);
	}
}

void GSDlgCurvatureCalculation::accept()
{
	QVector<int> vecPara;
	vecPara << ui.spinBoxDX->value() << ui.spinBoxDY->value();

	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		CXCheckBoxWidget *pCheckBox = (CXCheckBoxWidget *)ui.tableWidget->cellWidget(i, 0);
		if (pCheckBox->IsChecked())
			vecPara << 2 * i;
		
		pCheckBox = (CXCheckBoxWidget *)ui.tableWidget->cellWidget(i, 2);
		if(!pCheckBox)
			break;

		if (pCheckBox->IsChecked())
			vecPara << 2 * i + 1;	
	}

	if (vecPara.size() <= 2)
	{
		QMessageBox::warning(NULL, "Curvature Calculation", "No curvature attributes selected!");
		return;
	}
		
	GSThreadSurfaceCurvature *pThread = new GSThreadSurfaceCurvature((CX3DHorizon *)m_pHorizon, vecPara);
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(pThread, this);

	pProgress->show();

	pThread->start();

	if (pProgress->exec() == QDialog::Accepted)
	{
		QVector<CX3DHorizon *> vecHor = pThread->GetOutputHorizons();

		foreach(CX3DHorizon *pHor, vecHor)
		{
			m_pHorizon->GetParent()->AddChild(pHor);

		}
			
		CXTree::Instance().AddOneObject(m_pHorizon->GetParent());
	}

	QDialog::accept();
}