#include "xpagewellvis.h"
#include "xviewinfowellpath.h"

CXPageWellVis::CXPageWellVis(QWidget *parent, CXViewInfoObject * pWellViewInfo)
	: CXBasePropertyPage(parent)
{
	m_ui.setupUi(this);

	m_pViewInfo = dynamic_cast<CXViewInfoWellPath*>(pWellViewInfo);
	Q_ASSERT(m_pViewInfo);

	_Init();
}

CXPageWellVis::~CXPageWellVis()
{

}

void CXPageWellVis::Apply()
{
	m_pViewInfo->SetWellNameVisible(m_ui.m_cbNameVisible->isChecked());
	m_pViewInfo->SetWellNameUseObjColor(m_ui.m_cbbNameColor->ColorType() == 1);
	m_pViewInfo->SetWellNameColor(m_ui.m_cbbNameColor->GetColor());
	m_pViewInfo->SetWellPathVisible(m_ui.m_cbPathVisible->isChecked());
	m_pViewInfo->SetWellPathUseObjColor(m_ui.m_cbbPathColor->ColorType() == 1);
	m_pViewInfo->SetWellPathColor(m_ui.m_cbbPathColor->GetColor());
	m_pViewInfo->SetWellPathRadius(m_ui.m_cbbPathWidth->GetLineWidth());
}

void CXPageWellVis::SetObjectColorBuddyButton(CXButtonColorEdit* pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_cbbNameColor, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_cbbPathColor, &CXButtonColorEdit::slotObjectColorChanged);
}

void CXPageWellVis::_Init()
{
	m_ui.m_cbbNameColor->AddButton("Object color", m_pViewInfo->GetColor());
	m_ui.m_cbbPathColor->AddButton("Object color", m_pViewInfo->GetColor());

	m_ui.m_cbNameVisible->setChecked(m_pViewInfo->GetWellNameVisible());
	m_ui.m_cbbNameColor->SetColor(m_pViewInfo->GetWellNameUseObjColor(), m_pViewInfo->GetWellNameColor());
	m_ui.m_cbPathVisible->setChecked(m_pViewInfo->GetWellPathVisible());
	m_ui.m_cbbPathColor->SetColor(m_pViewInfo->GetWellPathUseObjColor(), m_pViewInfo->GetWellPathColor());
	m_ui.m_cbbPathWidth->SetLineWidth(m_pViewInfo->GetWellPathRadius());
}