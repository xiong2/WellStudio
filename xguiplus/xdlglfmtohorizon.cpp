#include <QListWidgetItem>
#include <qmessagebox.h>
#include "xdlglfmtohorizon.h"
#include "xprocessfactory.h"
#include "xlfmgeometry.h"
#include "x3dhorizon.h"
#include "xglobal.h"
#include "xtree.h"

CXDlgLFMToHorizon::CXDlgLFMToHorizon(CXObject* pParentObj, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_pLFMGeometry = (CXLFMGeometry *)pParentObj;

	initialize();
}

CXDlgLFMToHorizon::~CXDlgLFMToHorizon()
{

}

void CXDlgLFMToHorizon::initialize()
{
	QIcon qIcon(::GetIconPath() + "Horizon.png");
	int iRow = m_pLFMGeometry->GetNK();
	for (int i = 0; i < iRow; i++)
	{
		QListWidgetItem *pItem = new QListWidgetItem(qIcon, "Slice " + QString::number(i + 1));
		pItem->setCheckState(Qt::Unchecked);
		ui.listWidget->addItem(pItem);
	}

	ui.lineEdit->setText(m_pLFMGeometry->GetObjectName());

	connect(ui.pushButtonSelectAll, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
	connect(ui.pushButtonUnselectAll, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));

	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
}

void CXDlgLFMToHorizon::slotButtonClicked()
{
	Qt::CheckState sta = Qt::Unchecked;
	if (sender() == ui.pushButtonSelectAll)
		sta = Qt::Checked;

	for (int i = 0; i < ui.listWidget->count(); i++)
		ui.listWidget->item(i)->setCheckState(sta);
}

void CXDlgLFMToHorizon::accept()
{
	int iNum = 0;
	CXObject *pHFolder = ::GetRootObjectFolder(EXHorizonFolder);
	float *pData = new float[m_pLFMGeometry->GetUTM().GetNI() * m_pLFMGeometry->GetUTM().GetNJ()];

	for (int i = 0; i < ui.listWidget->count(); i++)
	{
		if (ui.listWidget->item(i)->checkState() == Qt::Unchecked)
			continue;

		m_pLFMGeometry->ReadOneSlice(i, pData);
		QString sName = ui.lineEdit->text() + " Slice " + QString::number(i + 1);
		CX3DHorizon *pHor = new CX3DHorizon(m_pLFMGeometry->GetSurveyID(), m_pLFMGeometry->GetUTM(), pHFolder->GetUnallocatedName(sName));
		pHor->SetData(pData);
		pHFolder->AddChild(pHor);
		::AddObjectEvent(pHor);

		iNum++;
	}
		
	delete[]pData;

	if (iNum == 0)
	{
		QMessageBox::warning(NULL, "Convert to Horizons", "No slice selected!");
		return;
	}

	QDialog::accept();
}