#include "xpagesection3dhorizonvis.h"
#include "xviewinfo3dhorizon.h"

CXPageSection3DHorizonVis::CXPageSection3DHorizonVis(QWidget *parent, CXViewInfoObject *pViewInfo)
	: CXBasePropertyPage(parent)
{
	m_ui.setupUi(this);
	m_pViewInfo = dynamic_cast<CXViewInfo3DHorizon*>(pViewInfo);

	_Init();
}

CXPageSection3DHorizonVis::~CXPageSection3DHorizonVis()
{

}

void CXPageSection3DHorizonVis::Apply()
{
	m_pViewInfo->SetSectionLineColor(m_ui.m_colorLine->GetColor());
	m_pViewInfo->SetSectionLineUseObjColor(m_ui.m_colorAnn->ColorType() == 1);
	m_pViewInfo->SetSectionLineWidth(m_ui.m_cbbLineWidth->GetLineWidth());

	m_pViewInfo->SetSectionAnnotationLeftVisible(m_ui.m_cbAnnLeft->isChecked());
	m_pViewInfo->SetSectionAnnotationRightVisible(m_ui.m_cbAnnRight->isChecked());
	m_pViewInfo->SetSectionAnnotationBackgroundVisible(m_ui.m_cbAnnBkg->isChecked());
	m_pViewInfo->SetSectionAnnotationBackgroundColor(m_ui.m_colorAnnBkg->GetColor());
	m_pViewInfo->SetSectionAnnotationColor(m_ui.m_colorAnn->GetColor());
	m_pViewInfo->SetSectionAnnotationUseObjColor(m_ui.m_colorAnn->ColorType() == 1);
	m_pViewInfo->SetSectionAnnotationSize(m_ui.m_editAnnSize->text().toInt());

	m_pViewInfo->SetSectionIntersectionPointSize(m_ui.m_cbbPointSize->currentText().toInt());
}

void CXPageSection3DHorizonVis::_Init()
{
	m_ui.m_colorLine->AddButton("Object color", m_pViewInfo->GetColor());
	m_ui.m_colorLine->SetColor(m_pViewInfo->GetSectionLineUseObjColor(), m_pViewInfo->GetSectionLineColor());
	m_ui.m_cbbLineWidth->SetLineWidth(m_pViewInfo->GetSectionLineWidth());

	m_ui.m_cbAnnLeft->setChecked(m_pViewInfo->GetSectionAnnotationLeftVisible());
	m_ui.m_cbAnnRight->setChecked(m_pViewInfo->GetSectionAnnotationRightVisible());
	m_ui.m_cbAnnBkg->setChecked(m_pViewInfo->GetSectionAnnotationBackgroundVisible());
	m_ui.m_colorAnnBkg->SetColor(m_pViewInfo->GetSectionAnnotationBackgroundColor());
	m_ui.m_colorAnn->AddButton("Object color", m_pViewInfo->GetColor());
	m_ui.m_colorAnn->SetColor(m_pViewInfo->GetSectionAnnotationUseObjColor(), m_pViewInfo->GetSectionAnnotationColor());
	m_ui.m_editAnnSize->setText(QString::number(m_pViewInfo->GetSectionAnnotationSize()));

	m_ui.m_cbbPointSize->setCurrentText(QString::number(m_pViewInfo->GetSectionIntersectionPointSize()));
}

void CXPageSection3DHorizonVis::SetObjectColorBuddyButton(CXButtonColorEdit* pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_colorAnn, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_colorLine, &CXButtonColorEdit::slotObjectColorChanged);
}