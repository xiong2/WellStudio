#include "xfaultsticksvissec.h"
#include "xviewinfo3dfaultsticks.h"
#include <QMessageBox>

CXFaultSticksVisSec::CXFaultSticksVisSec(QWidget *parent, CXViewInfoObject* pViewInfo):CXBasePropertyPage(parent)
{
	m_Ui.setupUi(this);
	m_pViewInfo = dynamic_cast<CXViewInfo3DFaultSticks*>(pViewInfo);
	_initUI();
}


CXFaultSticksVisSec::~CXFaultSticksVisSec(void)
{
}
void CXFaultSticksVisSec::_initUI()
{
	m_Ui.m_pCmbStyleColor->AddButton("Object color", m_pViewInfo->GetColor());
	m_Ui.m_pCmbStyleColor->SetColor(m_pViewInfo->GetLineColor());
	m_Ui.m_pCmbSytleWidth->SetLineWidth(m_pViewInfo->GetLineWidth());
	m_Ui.m_pCmbStyleColor->SetColorType(m_pViewInfo->GetLineColorMode());
	m_Ui.m_pChkTop->setChecked(m_pViewInfo->GetAnnTop());
	m_Ui.m_pChkBottom->setChecked(m_pViewInfo->GetAnnBottom());
}

void CXFaultSticksVisSec::Apply()
{
	m_pViewInfo->SetLineColor(m_Ui.m_pCmbStyleColor->GetColor());
	m_pViewInfo->SetLineColorMode(m_Ui.m_pCmbStyleColor->ColorType());
	m_pViewInfo->SetLineWidth(m_Ui.m_pCmbSytleWidth->GetLineWidth());
	m_pViewInfo->SetAnnTop(m_Ui.m_pChkTop->isChecked());
	m_pViewInfo->SetAnnBottom(m_Ui.m_pChkBottom->isChecked());
}

void CXFaultSticksVisSec::SetObjectColorBuddyButton(CXButtonColorEdit* pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_Ui.m_pCmbStyleColor, &CXButtonColorEdit::slotObjectColorChanged);
}