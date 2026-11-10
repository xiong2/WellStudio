#include "xwellvisualizationpage.h"
#include "xviewinfowellpath.h"
#include "xcolorbutton.h"

CXPageWellVis3D::CXPageWellVis3D(QWidget *parent, CXViewInfoObject * pWellViewInfo)
    :CXBasePropertyPage(parent)
{
    m_page.setupUi(this);

    m_pViewInfo = dynamic_cast<CXViewInfoWellPath*>(pWellViewInfo);
    Q_ASSERT(m_pViewInfo);

	_InitUIState();
}

CXPageWellVis3D::~CXPageWellVis3D()
{

}

void CXPageWellVis3D::_InitUIState()
{
	m_page.m_cbNameVisible->setChecked(m_pViewInfo->GetWellNameVisible());
	m_page.m_cbbNameColor->AddButton("Object color", m_pViewInfo->GetColor());
	m_page.m_cbbNameColor->SetColor(m_pViewInfo->GetWellNameUseObjColor(), m_pViewInfo->GetWellNameColor());
	m_page.m_cbbNameSize->setCurrentIndex(m_page.m_cbbNameSize->findText(QString::number(m_pViewInfo->GetWellNameFontSize())));
	m_page.m_cbbNameFont->setCurrentText(m_pViewInfo->GetWellNameFontFamily());
	m_page.m_cbbNamePosition->setCurrentIndex(m_pViewInfo->GetWellNamePosition());

	m_page.m_cbPathVisible->setChecked(m_pViewInfo->GetWellPathVisible());
	m_page.m_cbbPathColor->AddButton("Object color", m_pViewInfo->GetColor());
	m_page.m_cbbPathColor->SetColor(m_pViewInfo->GetWellPathUseObjColor(), m_pViewInfo->GetWellPathColor());
	m_page.m_cbbPathSize->SetLineWidth(m_pViewInfo->GetWellPathRadius());

	m_page.m_cbSymbolVisible->setChecked(m_pViewInfo->GetWellSymbolVisible());
	m_page.m_cbbSymbolColor->AddButton("Object color", m_pViewInfo->GetColor());
	m_page.m_cbbSymbolColor->SetColor(m_pViewInfo->GetWellSymbolUseObjColor(), m_pViewInfo->GetWellSymbolColor());
	m_page.m_cbbSymbolRadius->setCurrentText(QString::number(m_pViewInfo->GetWellSymbolRadius()));
}

void CXPageWellVis3D::Apply()
{
    m_pViewInfo->SetWellNameVisible(m_page.m_cbNameVisible->isChecked());
    m_pViewInfo->SetWellNameColor(m_page.m_cbbNameColor->GetColor());
	m_pViewInfo->SetWellNameUseObjColor(m_page.m_cbbNameColor->ColorType() == 1);
	m_pViewInfo->SetWellNameFontFamily(m_page.m_cbbNameFont->currentText());
	m_pViewInfo->SetWellNameFontSize(m_page.m_cbbNameSize->currentText().toInt());
	m_pViewInfo->SetWellNamePosition(m_page.m_cbbNamePosition->currentIndex());

	m_pViewInfo->SetWellPathVisible(m_page.m_cbPathVisible->isChecked());
    m_pViewInfo->SetWellPathColor(m_page.m_cbbPathColor->GetColor());
	m_pViewInfo->SetWellPathUseObjColor(m_page.m_cbbPathColor->ColorType() == 1);
    m_pViewInfo->SetWellPathRadius(m_page.m_cbbPathSize->GetLineWidth());
    
    m_pViewInfo->SetWellSymbolVisible(m_page.m_cbSymbolVisible->isChecked());
    m_pViewInfo->SetWellSymbolColor(m_page.m_cbbSymbolColor->GetColor());
	m_pViewInfo->SetWellSymbolUseObjColor(m_page.m_cbbSymbolColor->ColorType() == 1);
    m_pViewInfo->SetWellSymbolRadius(m_page.m_cbbSymbolRadius->currentText().toInt());
}

void CXPageWellVis3D::SetObjectColorBuddyButton(CXButtonColorEdit* pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_page.m_cbbNameColor, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_page.m_cbbPathColor, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_page.m_cbbSymbolColor, &CXButtonColorEdit::slotObjectColorChanged);
}