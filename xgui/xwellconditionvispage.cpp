#include "xwellconditionvispage.h"

#include <cassert>

#include "ui_xwellconditionvispage.h"
#include "xviewinfoobject.h"
#include "xviewinfowellcondition.h"
#include "xglobal.h"
#include "xwell.h"

CXWellConditionVisPage::CXWellConditionVisPage(QWidget *parent, CXViewInfoObject *pViewInfo)
	: CXBasePropertyPage(parent)
{
	m_pUi = new Ui::CXWellConditionVisPage();
	m_pUi->setupUi(this);

    m_pViewInfo = dynamic_cast<CXViewInfoWellCondition*>(pViewInfo);
	assert(m_pViewInfo);

	_Init();
	_InitData();
}

CXWellConditionVisPage::~CXWellConditionVisPage()
{
	delete m_pUi;
}

void CXWellConditionVisPage::_Init()
{
	m_pUi->m_pBtSelectAll->setIcon(QIcon(::GetIconPath() + "SelectAll.png"));
	m_pUi->m_pBtDisSelectAll->setIcon(QIcon(::GetIconPath() + "DisSelectAll.png"));

	connect(m_pUi->m_pBtSelectAll, SIGNAL(clicked()), this, SLOT(_SelectAllWellItems()));
	connect(m_pUi->m_pBtDisSelectAll, SIGNAL(clicked()), this, SLOT(_DisSelectAllWellItems()));
}

void CXWellConditionVisPage::_InitData()
{
	// Well list
	const std::vector<QUuid> &vecWell = m_pViewInfo->GetWellList();
	const std::vector<int> &vecIndex = m_pViewInfo->GetWellVisibleList();
	for (int i=0; i<vecWell.size(); ++i)
	{
		CXWell *pWell = dynamic_cast<CXWell*>(::GetObjectByID(vecWell[i]));
		QListWidgetItem *item = new QListWidgetItem(QIcon(::GetIconPath() + pWell->GetIconName()), pWell->GetObjectName(), m_pUi->m_pListVisible);
		item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
		item->setCheckState(vecIndex[i] ? Qt::Checked : Qt::Unchecked);
	}

	// Geometry
	m_pUi->m_pColorEditGeo->SetColor(m_pViewInfo->GetColor());

	// Grid line
	m_pUi->m_pChkVisible->setChecked(m_pViewInfo->GetDisplayLine());
	m_pUi->m_pColorEditLine->SetColor(m_pViewInfo->GetLineColor());
}

void CXWellConditionVisPage::Apply()
{
	// Well list
	int iListSize = m_pUi->m_pListVisible->count();
	std::vector<int> vecVisible;
	vecVisible.reserve(iListSize);

	// Get well which need to calculate again.
	for (int i=0; i<iListSize; ++i)
	{
		if (m_pUi->m_pListVisible->item(i)->checkState() == Qt::Checked)
			vecVisible.push_back(1);
		else if (m_pUi->m_pListVisible->item(i)->checkState() == Qt::Unchecked)
			vecVisible.push_back(0);
	}

	m_pViewInfo->SetWellVisibleList(vecVisible);

	// Geometry
	m_pViewInfo->SetGeomColor(m_pUi->m_pColorEditGeo->GetColor());

	// Grid line
	m_pViewInfo->SetDisplayLine(m_pUi->m_pChkVisible->isChecked());
	m_pViewInfo->SetLineColor(m_pUi->m_pColorEditLine->GetColor());
}

void CXWellConditionVisPage::_SelectAllWellItems()
{
	for (int i=0; i<m_pUi->m_pListVisible->count(); ++i)
	{
		m_pUi->m_pListVisible->item(i)->setCheckState(Qt::Checked);
	}
}
void CXWellConditionVisPage::_DisSelectAllWellItems()
{
	for (int i=0; i<m_pUi->m_pListVisible->count(); ++i)
	{
		m_pUi->m_pListVisible->item(i)->setCheckState(Qt::Unchecked);
	}
}