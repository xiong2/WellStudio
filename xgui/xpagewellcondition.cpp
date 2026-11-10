#include "xpagewellcondition.h"
#include "ui_xpagewellcondition.h"
#include "xreservoirmodel.h"
#include "xwellcondition.h"
#include "xglobal.h"
#include "xwell.h"
#include "xtree.h"

#include <cassert>

CXPageWellCondition::CXPageWellCondition(CXReservoirModel *pModel, QWidget *parent)
	: QDialog(parent)
{
	m_pUi = new Ui::CXPageWellCondition();
	m_pUi->setupUi(this);
	assert(pModel);
	m_pModel = pModel;
	m_pWellCondition = NULL;

	_Init();
	_InitData();
}

CXPageWellCondition::~CXPageWellCondition()
{
	delete m_pUi;
}

void CXPageWellCondition::_InitData()
{
	QList<CXObject *> listWellCondition = m_pModel->GetChildren(EXWellCondition);
	assert(listWellCondition.size() == 0 || listWellCondition.size() == 1);

	QList<QString> listCalculatedWell;
	if (listWellCondition.size() == 0)
	{
		// Create a new WellCondition for ReservoirModel.
		m_pWellCondition = new CXWellCondition(QList<CXWell*>());
		m_pModel->AddChild(m_pWellCondition);
		::AddObjectEvent(m_pWellCondition);
	}
	else
	{
		m_pWellCondition = dynamic_cast<CXWellCondition*>(listWellCondition.at(0));
		m_listCalculatedWell = m_pWellCondition->GetCalculatedWells();
		foreach(CXWell *pWell, m_listCalculatedWell)
		{
			listCalculatedWell << pWell->GetObjectName();
			QListWidgetItem *item = new QListWidgetItem(QIcon(::GetIconPath() + pWell->GetIconName()), pWell->GetObjectName(), m_pUi->m_pListCalc);
			item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
			item->setCheckState(Qt::Unchecked);
		}
	}

	// List well from console tree without above.
	QList<CXObject *> listWell = ::GetRootObjectFolder(EXWellFolder)->GetChildren(EXWell);
	foreach(CXObject *pWell, listWell)
	{
		if (!listCalculatedWell.contains(pWell->GetObjectName()))
		{
			m_listUnCalcWell << dynamic_cast<CXWell*>(pWell);
			QListWidgetItem *item = new QListWidgetItem(QIcon(::GetIconPath() + pWell->GetIconName()), pWell->GetObjectName(), m_pUi->m_pListUnCalc);
			item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
			item->setCheckState(Qt::Unchecked);
		}	
	}

	if (m_pUi->m_pListCalc->count() == 0 && m_pUi->m_pListUnCalc->count() == 0)
	{
		m_pUi->m_pBtnGroupOkCancel->button(QDialogButtonBox::Ok)->setDisabled(true);
	}
}

void CXPageWellCondition::_Init()
{
	m_pUi->m_pBtnCalcSelectAll->setIcon(QIcon(::GetIconPath() + "SelectAll.png"));
	m_pUi->m_pBtnCalcClear->setIcon(QIcon(::GetIconPath() + "DisSelectAll.png"));
	m_pUi->m_pBtnUnCalcSelectAll->setIcon(QIcon(::GetIconPath() + "SelectAll.png"));
	m_pUi->m_pBtnUnCalcClear->setIcon(QIcon(::GetIconPath() + "DisSelectAll.png"));

	connect(m_pUi->m_pBtnCalcSelectAll, SIGNAL(clicked()), this, SLOT(slotSelectAllCalcItem()));
	connect(m_pUi->m_pBtnCalcClear, SIGNAL(clicked()), this, SLOT(slotUnSelectAllCalcItem()));
	connect(m_pUi->m_pBtnUnCalcSelectAll, SIGNAL(clicked()), this, SLOT(slotSelectAllUnCalcItem()));
	connect(m_pUi->m_pBtnUnCalcClear, SIGNAL(clicked()), this, SLOT(slotUnSelectAllUnCalcItem()));

	connect(m_pUi->m_pBtnGroupOkCancel, SIGNAL(accepted()), this, SLOT(accept()));
	connect(m_pUi->m_pBtnGroupOkCancel, SIGNAL(rejected()), this, SLOT(reject()));
}

void CXPageWellCondition::slotSelectAllCalcItem()
{
	for (int i=0; i<m_pUi->m_pListCalc->count(); ++i)
	{
		m_pUi->m_pListCalc->item(i)->setCheckState(Qt::Checked);
	}
}

void CXPageWellCondition::slotUnSelectAllCalcItem()
{
	for (int i=0; i<m_pUi->m_pListCalc->count(); ++i)
	{
		m_pUi->m_pListCalc->item(i)->setCheckState(Qt::Unchecked);
	}
}

void CXPageWellCondition::slotSelectAllUnCalcItem()
{
	for (int i=0; i<m_pUi->m_pListUnCalc->count(); ++i)
	{
		m_pUi->m_pListUnCalc->item(i)->setCheckState(Qt::Checked);
	}
}

void CXPageWellCondition::slotUnSelectAllUnCalcItem()
{
	for (int i=0; i<m_pUi->m_pListUnCalc->count(); ++i)
	{
		m_pUi->m_pListUnCalc->item(i)->setCheckState(Qt::Unchecked);
	}
}

void CXPageWellCondition::accept()
{
	QList<QString> listReCalcWell;
	QList<QString> listCalcWell;

	// Get well which need to calculate again.
	for (int i=0; i<m_pUi->m_pListCalc->count(); ++i)
		if (m_pUi->m_pListCalc->item(i)->checkState() == Qt::Checked)
			listReCalcWell << m_pUi->m_pListCalc->item(i)->text();

	// Get well which need to calculate.
	for (int i=0; i<m_pUi->m_pListUnCalc->count(); ++i)
		if (m_pUi->m_pListUnCalc->item(i)->checkState() == Qt::Checked)
			listCalcWell << m_pUi->m_pListUnCalc->item(i)->text();

	// Calculate each well
	foreach(CXWell *pWell, m_listCalculatedWell)
		if (listReCalcWell.contains(pWell->GetObjectName()))
			m_pWellCondition->CalculateOneWell(pWell);

	foreach(CXWell *pWell, m_listUnCalcWell)
		if (listCalcWell.contains(pWell->GetObjectName()))
			m_pWellCondition->CalculateOneWell(pWell);

	QDialog::accept();
}