#include <QStandardItemModel>
#include <qvalidator.h>
#include "xdlgac2td.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "xwellpath.h"
#include "xwelltd.h"
#include "xtemplate.h"

CXDlgAC2TD::CXDlgAC2TD(CXWell *pObj, QWidget *parent)
	: m_pWell(pObj), QDialog(parent)
{
	ui.setupUi(this);

	initUI();
}

CXDlgAC2TD::~CXDlgAC2TD()
{
}

void CXDlgAC2TD::initUI()
{
	CXTemplate *pTemplate = CXTemplate::GetTemplate("PSON");
	QList<CXObject *> listCurve = m_pWell->GetSpecialCurveList(pTemplate->GetID());
	QStringList sListCurves;
	foreach(CXObject *pObj, listCurve)
		sListCurves << pObj->GetObjectName();

	ui.comboBox->addItems(sListCurves);

	ui.lineEdit->setValidator(new QDoubleValidator);
	ui.lineEditStart->setValidator(new QIntValidator);
	ui.lineEditEnd->setValidator(new QIntValidator);

	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)), SLOT(slotSelAC(int)));
	connect(ui.pushButton, SIGNAL(clicked()), SLOT(slotCalculate()));

	slotSelAC(0);
}

void CXDlgAC2TD::slotSelAC(int iIDX)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);

	CXTemplate *pTemplate = CXTemplate::GetTemplate("PSON");
	QList<CXObject *> listCurve = m_pWell->GetSpecialCurveList(pTemplate->GetID());
	CXWellCurve *pCurve = (CXWellCurve *)listCurve[iIDX];
	CXWellPath *pWellPath = m_pWell->GetWellPath();

	int iNum = pCurve->GetPointNumber();
	double *pCurveData = pCurve->GetData();
	double dMD = pCurve->GetStart(), dStep = pCurve->GetStep();

	QStringList sListHLable;
	sListHLable << "MD (m)" << "TVDSS (m)" << "AC (us/m)" << "TWT (ms)";
	QStandardItemModel *pModel = new QStandardItemModel(iNum, 4);
	ui.tableView->setModel(pModel);
	pModel->setHorizontalHeaderLabels(sListHLable);

	int i;
	for (i = 0; i < iNum; i++)
	{
		QStandardItem *pItem = new QStandardItem(QString::number(dMD, 'f', 2));
		pModel->setItem(i, 0, pItem);

		float fTVD = pWellPath->Md2Tvd(dMD);
		pItem = new QStandardItem(QString::number(fTVD, 'f', 2));
		pModel->setItem(i, 1, pItem);

		pItem = new QStandardItem(QString::number(pCurveData[i], 'f', 2));
		pModel->setItem(i, 2, pItem);

		dMD += dStep;
	}

	//	Guess the last valid sample.
	for (i = iNum - 1; i >= 0; i--)
	{
		if (pCurveData[i] > 0.)
			break;
	}
	ui.lineEditEnd->setText(QString::number(i + 1));

	if (m_pBuff)
	{
		delete[]m_pBuff;
		m_pBuff = NULL;
	}
	ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

	QApplication::restoreOverrideCursor();
}

void CXDlgAC2TD::slotCalculate()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);

	QStandardItemModel *pModel = (QStandardItemModel *)ui.tableView->model();
	int iRNum = pModel->rowCount();

	if (m_pBuff)
		delete[]m_pBuff;

	int iS = ui.lineEditStart->text().toInt() - 1;
	int iE = ui.lineEditEnd->text().toInt() - 1;
	iS = iS < 0 ? 0 : iS;
	iE = iE > iRNum - 1 ? iRNum - 1 : iE;

	m_iNum = iE - iS + 1;
	if (m_iNum < 1)
		return;

	m_pBuff = new double[2 * m_iNum];
	double dVel = ui.lineEdit->text().toDouble();
	double dDep = pModel->item(iS, 1)->text().toDouble();
	m_pBuff[0] = dDep;
	m_pBuff[m_iNum] = dDep * 1000 / dVel;
	QStandardItem *pItem = new QStandardItem(QString::number(m_pBuff[m_iNum], 'f', 2));
	pModel->setItem(iS, 3, pItem);

	for (int i = 1; i < m_iNum; i++)
	{
		m_pBuff[i] = pModel->item(iS + i, 1)->text().toDouble();
		m_pBuff[m_iNum + i] = m_pBuff[m_iNum + i - 1] + (m_pBuff[i] - m_pBuff[i - 1]) * pModel->item(i + iS, 2)->text().toDouble() / 1000;

		pItem = new QStandardItem(QString::number(m_pBuff[m_iNum + i], 'f', 2));
		pModel->setItem(i + iS, 3, pItem);
	}

	ui.widget->Populate(m_pBuff, m_iNum);
	ui.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);

	QApplication::restoreOverrideCursor();
}

void CXDlgAC2TD::accept()
{
	CXWellTD *pTD = new CXWellTD;

	QString sName = m_pWell->GetUnallocatedName("TD");
	pTD->SetObjectName(sName);
	pTD->SetIconName("Calculated from AC curve: " + ui.comboBox->currentText());
	pTD->ResetData(m_pBuff, 2 * m_iNum);
	m_pWell->AddChild(pTD);

	QDialog::accept();
}