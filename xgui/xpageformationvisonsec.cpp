#include "xpageformationvisonsec.h"
#include "xviewinfo3dwelltopformation.h"

CXPageFormationVisOnSec::CXPageFormationVisOnSec(QWidget *parent, CXViewInfoObject* pViewInfo) :CXBasePropertyPage(parent)
{
	m_UI.setupUi(this);
    m_pViewInfo = dynamic_cast<CXViewInfo3DWellTopFormation*>(pViewInfo);
	connect(m_UI.m_pSldTrans,SIGNAL(valueChanged(int)),this,SLOT(slotTransChanged(int)));
	_InitUi();
}


CXPageFormationVisOnSec::~CXPageFormationVisOnSec(void)
{
}
void CXPageFormationVisOnSec::slotTransChanged(int nValue)
{
	m_UI.m_pLblTransValue->setText(QString::number(nValue));
}
void CXPageFormationVisOnSec::_InitUi()
{
	if (m_pViewInfo == NULL)
	{
		return;
	}
	m_UI.m_pPtnSymbolColor->AddButton("Object color", m_pViewInfo->GetColor());
	m_UI.m_pPtnFontColor->AddButton("Object color", m_pViewInfo->GetColor());
	m_UI.m_pPtnBackColor->AddButton("Object color", m_pViewInfo->GetColor());

	m_UI.m_pPtnSymbolColor->SetColor(m_pViewInfo->GetWellTopFormationUseObjColor(), m_pViewInfo->GetWellTopFormationColor());
	m_UI.m_editSymbolHeight->setText(QString::number(m_pViewInfo->GetHeight()));
	m_UI.m_editSymbolWidth->setText(QString::number(m_pViewInfo->GetRadius()));
	m_UI.m_cbbAnnVisible->setChecked(m_pViewInfo->GetFormationAnnVisible());
	m_UI.m_pPtnFontColor->SetColor(m_pViewInfo->GetFormationAnnUseObjColor(), m_pViewInfo->GetFormationAnnColor());
	m_UI.m_pEdtFontSize->setText(QString::number(m_pViewInfo->GetFormationAnnSize()));
	m_UI.m_pFontName->setCurrentFont(QFont(m_pViewInfo->GetFormationAnnFont()));
	m_UI.m_pPtnBackColor->SetColor(m_pViewInfo->GetFormationBgrUseObjColor(), m_pViewInfo->GetFormationBgrColor());
	m_UI.m_pSldTrans->setValue(m_pViewInfo->GetFormationBgrTrans());
	m_UI.m_pLblTransValue->setText(QString::number(m_pViewInfo->GetFormationBgrTrans()));

}
void CXPageFormationVisOnSec::Apply()
{
	if (m_pViewInfo == NULL)
	{
		return;
	}

	m_pViewInfo->SetWellTopFormationUseObjColor(m_UI.m_pPtnSymbolColor->ColorType() == 1);
	m_pViewInfo->SetWellTopFormationColor(m_UI.m_pPtnSymbolColor->GetColor());
	m_pViewInfo->SetHeight(m_UI.m_editSymbolHeight->text().toFloat());
	m_pViewInfo->SetRadius(m_UI.m_editSymbolWidth->text().toFloat());
	m_pViewInfo->SetFormationAnnVisible(m_UI.m_cbbAnnVisible->isChecked());
	m_pViewInfo->SetFormationAnnUseObjColor(m_UI.m_pPtnFontColor->ColorType() == 1);
	m_pViewInfo->SetFormationAnnColor(m_UI.m_pPtnFontColor->GetColor());
	m_pViewInfo->SetFormationAnnSize(m_UI.m_pEdtFontSize->text().toInt());
	m_pViewInfo->SetFormationAnnFont(m_UI.m_pFontName->currentText());
	m_pViewInfo->SetFormationBgrUseObjColor(m_UI.m_pPtnBackColor->ColorType() == 1);
	m_pViewInfo->SetFormationBgrColor(m_UI.m_pPtnBackColor->GetColor());
	m_pViewInfo->SetFormationBgrTrans(m_UI.m_pSldTrans->value());
}

void CXPageFormationVisOnSec::SetObjectColorBuddyButton(CXButtonColorEdit* pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_UI.m_pPtnSymbolColor, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_UI.m_pPtnFontColor, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_UI.m_pPtnBackColor, &CXButtonColorEdit::slotObjectColorChanged);
}