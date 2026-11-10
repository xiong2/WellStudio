#include "xpageselectwelltopsformation.h"

#include <cassert>
#include <QMessageBox>

#include "xwelltops.h"
#include "xparametermake2dgrid.h"
#include "xglobal.h"


CXPageSelectWellTopsFormation::CXPageSelectWellTopsFormation(CXParameterMake2DGrid* pPara, CXObject *pObj, QWidget *parent)
	: QWizardPage(parent)
{
	m_ui.setupUi(this);
	
	assert(pPara && pObj);

	m_pWellTops = dynamic_cast<CXWellTops*>(pObj);
	m_pPara = pPara;
}

void CXPageSelectWellTopsFormation::initializePage()
{
	// get formation list
	QStringList listWellTopWell;
	m_pWellTops->GetWellAndFormation(listWellTopWell, m_strlistFormation);
	assert(!m_strlistFormation.isEmpty() && !listWellTopWell.isEmpty());

// 	QList<CXObject*> listWell = ::GetRootObjectFolder(EXWellFolder)->GetChildren(EXWell);
// 
// 	// add wells and ids to combobox
// 	for (int i=0; i<listWell.size(); ++i)
// 		m_ui.m_cbbWellName->addItem(listWell.at(i)->GetObjectName(), listWell.at(i)->GetObjectID().variant());//m_pPara->GetWellID().variant());

	// list formation
	for (int i=0; i<m_strlistFormation.size(); ++i)
	{
		QListWidgetItem *item = new QListWidgetItem(m_strlistFormation.at(i), m_ui.m_lwgtFormation);
		item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
		item->setCheckState(Qt::Unchecked);
	}

	connect(m_ui.m_pbSelectAll, SIGNAL(clicked()), this, SLOT(_SelectAllItem()));
	connect(m_ui.m_pbUnSelectAll, SIGNAL(clicked()), this, SLOT(_UnSelectAllItem()));
}

bool CXPageSelectWellTopsFormation::validatePage()
{
	// get selected well
	//m_pPara->SetWellID(m_ui.m_cbbWellName->itemData(m_ui.m_cbbWellName->currentIndex()).toString());

	// get selected formation
	QStringList selected_formation_list;
	for (int i=0; i<m_strlistFormation.size(); ++i)
	{
		if (m_ui.m_lwgtFormation->item(i)->checkState())
			selected_formation_list << m_ui.m_lwgtFormation->item(i)->text();
	}

	if (selected_formation_list.size() < 2)
	{
		QMessageBox::warning(nullptr, tr("Select Formation"), tr("Please select at least two of formations!"));
		return false;
	}

	// save result
	m_pPara->SetHorizonNameList(selected_formation_list);
	
	return true;
}

void CXPageSelectWellTopsFormation::_SelectAllItem()
{
	for (int i=0; i<m_strlistFormation.size(); ++i)
	{
		m_ui.m_lwgtFormation->item(i)->setCheckState(Qt::Checked);
	}
}

void CXPageSelectWellTopsFormation::_UnSelectAllItem()
{
	for (int i=0; i<m_strlistFormation.size(); ++i)
	{
		m_ui.m_lwgtFormation->item(i)->setCheckState(Qt::Unchecked);
	}
}