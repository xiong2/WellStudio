#include "xdlgsegylineheader.h"
#include "xsegylineheader.h"

void CXDlgSEGYLineHeader::initTreeView()
{
	m_pLineHeader->SetNeedFlip(m_bIsFlip);
	QStringList listLineHeaderData = m_pLineHeader->GetItems();
	for (int nRow = 0; nRow < m_LineHeaderViewUi.m_LineHeaderView->topLevelItemCount(); ++nRow)
	{
		QTreeWidgetItem *pItem = m_LineHeaderViewUi.m_LineHeaderView->topLevelItem(nRow);
		if (pItem != NULL)
		{
			pItem->setText(2, listLineHeaderData[nRow]);
		}
	}
}
void CXDlgSEGYLineHeader::slotFlipData()
{
	m_bIsFlip = m_LineHeaderViewUi.m_ChkFlip->isChecked();
	initTreeView();
	emit lineHeaderDataFliped(m_bIsFlip);
}

void CXDlgSEGYLineHeader::setLineHeaderData(CXSEGYLineHeader* pLineHeader)
{
	m_pLineHeader = pLineHeader;
	m_bIsFlip = m_pLineHeader->GetNeedFlip();
	m_LineHeaderViewUi.m_ChkFlip->setChecked(m_bIsFlip);
}
