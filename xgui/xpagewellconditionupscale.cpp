#include "xpagewellconditionupscale.h"
#include "ui_xpagewellconditionupscale.h"
#include "xwellcondition.h"
#include "xglobal.h"
#include "xwellcurvealias.h"
#include "xcurvecells.h"
#include "xtree.h"

#include <cassert>

CXPageWellConditionUpscale::CXPageWellConditionUpscale(CXWellCondition *pWellCondition, QWidget *parent)
	: QDialog(parent)
{
	m_pUi = new Ui::CXPageWellConditionUpscale();
	m_pUi->setupUi(this);

	assert(pWellCondition);
	m_pWellCondition = pWellCondition;

	_Init();
	_InitData();
}

CXPageWellConditionUpscale::~CXPageWellConditionUpscale()
{
	delete m_pUi;
}

void CXPageWellConditionUpscale::accept(void)
{
	QList<QString> listSelectedLogAlias;
	
	for (int i=0; i<m_pUi->m_pListLogAlias->count(); ++i)
		if (m_pUi->m_pListLogAlias->item(i)->checkState() == Qt::Checked)
			listSelectedLogAlias << m_pUi->m_pListLogAlias->item(i)->text();

	QList<CXObject *> listCurveCells = m_pWellCondition->GetChildren(EXCurveCells);
	QMap<QUuid, CXCurveCells*> mapIdToCurveCells;
	for (CXObject *pChild : listCurveCells)
	{
		CXCurveCells *pCurveCells = dynamic_cast<CXCurveCells*>(pChild);
		if (pCurveCells) 
			mapIdToCurveCells.insert(pCurveCells->GetWellCurveAliasID(), pCurveCells);
	}

	// Calculate each selected curve alais
	for (CXObject *pObj : m_listLogAlias)
	{
		if (listSelectedLogAlias.contains(pObj->GetObjectName()))
		{
			CXWellCurveAlias *pLogAlias = dynamic_cast<CXWellCurveAlias *>(pObj);
			assert(pLogAlias);

			CXCurveCells *pCurveCells = NULL;

			// if already in the tree, calculate again.
			if (listCurveCells.empty() || mapIdToCurveCells.find(pLogAlias->GetObjectID()) == mapIdToCurveCells.end())
			{
				pCurveCells = new CXCurveCells(pLogAlias);
				m_pWellCondition->AddChild(pCurveCells);
				::AddObjectEvent(pCurveCells);
			}
			else
			{
				pCurveCells = mapIdToCurveCells.value(pLogAlias->GetObjectID());
			}
			pCurveCells->CalculateCurve(m_pWellCondition);
		}
	}

	QDialog::accept();
}


void CXPageWellConditionUpscale::_Init(void)
{
	m_pUi->m_pBtnSelectAll->setIcon(QIcon(::GetIconPath() + "SelectAll.png"));
	m_pUi->m_pBtnDisSelectAll->setIcon(QIcon(::GetIconPath() + "DisSelectAll.png"));

	connect(m_pUi->m_pBtnSelectAll, SIGNAL(clicked()), this, SLOT(slotSelectAll()));
	connect(m_pUi->m_pBtnDisSelectAll, SIGNAL(clicked()), this, SLOT(slotDisSelectAll()));

	connect(m_pUi->m_pBtnGroupOkCancel, SIGNAL(accepted()), this, SLOT(accept()));
	connect(m_pUi->m_pBtnGroupOkCancel, SIGNAL(rejected()), this, SLOT(reject()));

	m_pUi->m_pCbbFunctions->addItem("Arithmetic average method");
}


void CXPageWellConditionUpscale::_InitData(void)
{
	m_listLogAlias = ::GetRootObjectFolder(EXWellCurveAliasFolder)->GetChildren(EXWellCurveAlias);
	for (CXObject *pObj : m_listLogAlias)
	{
		CXWellCurveAlias *pLogAlias = dynamic_cast<CXWellCurveAlias*>(pObj);
		if (pLogAlias)
		{
			QListWidgetItem *item = new QListWidgetItem(QIcon(::GetIconPath() + pLogAlias->GetIconName()), pLogAlias->GetObjectName(), m_pUi->m_pListLogAlias);
			item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
			item->setCheckState(Qt::Unchecked);
		}
	}
}


void CXPageWellConditionUpscale::slotSelectAll(void)
{
	for (int i=0; i<m_pUi->m_pListLogAlias->count(); ++i)
	{
		m_pUi->m_pListLogAlias->item(i)->setCheckState(Qt::Checked);
	}
}


void CXPageWellConditionUpscale::slotDisSelectAll(void)
{
	for (int i=0; i<m_pUi->m_pListLogAlias->count(); ++i)
	{
		m_pUi->m_pListLogAlias->item(i)->setCheckState(Qt::Unchecked);
	}
}
