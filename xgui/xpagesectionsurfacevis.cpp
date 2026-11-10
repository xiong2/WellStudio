#include "xpagesectionsurfacevis.h"
#include "xviewinfosurface.h"
#include "x3dhorizon.h"
#include "x3dsurface.h"


CXPageSectionSurfaceVis::CXPageSectionSurfaceVis(QWidget *parent, CXViewInfoObject* pViewInfo) :CXBasePropertyPage(parent)
{
	m_ui.setupUi(this);
	m_pViewInfo = dynamic_cast<CXViewInfoSurface*>(pViewInfo);
	_InitUi();
}

CXPageSectionSurfaceVis::~CXPageSectionSurfaceVis(void)
{
}

void CXPageSectionSurfaceVis::slotEnabledAnn()
{
	bool bEnabled = m_ui.m_pChkRightAnnVis->isChecked() ||  m_ui.m_pChkLeftAnnVis->isChecked();
	m_ui.label_6->setEnabled(bEnabled);
	m_ui.m_pPtnAnnColor->setEnabled(bEnabled);
	m_ui.label_5->setEnabled(bEnabled);
	m_ui.m_EdtAnnSize->setEnabled(bEnabled);
}


void CXPageSectionSurfaceVis::_InitUi()
{
	QIntValidator *pInt = new QIntValidator(m_ui.m_EdtAnnSize);
	m_ui.m_EdtAnnSize->setValidator(pInt);

	m_ui.m_pPtnLineColor->AddButton("Object color", m_pViewInfo->GetColor());
	m_ui.m_pPtnLineColor->SetColor(m_pViewInfo->GetSectionLineUseObjColor(), m_pViewInfo->GetSectionLineColor());

	m_ui.m_pPtnAnnColor->AddButton("Object color", m_pViewInfo->GetColor());
	m_ui.m_pPtnAnnColor->SetColor(m_pViewInfo->GetSectionAnnotationUseObjColor(), m_pViewInfo->GetSectionAnnotationColor());

	m_ui.m_pCmbLineSize->SetLineWidth(m_pViewInfo->GetSectionLineWidth());
	m_ui.m_EdtAnnSize->setText(QString::number(m_pViewInfo->GetSectionAnnotationSize()));
	m_ui.m_pPtnAnnBgr->SetColor(m_pViewInfo->GetSectionAnnotationBackgroundColor());
	m_ui.m_pChkRightAnnVis->setChecked(m_pViewInfo->GetSectionAnnotationRightVisible());
	m_ui.m_pChkLeftAnnVis->setChecked(m_pViewInfo->GetSectionAnnotationLeftVisible());
	m_ui.m_ChkBgr->setChecked(m_pViewInfo->GetSectionAnnotationBackgroundVisible());

	m_ui.m_pCbbPointSize->setCurrentText(QString::number(m_pViewInfo->GetSectionIntersectionPointSize()));

	slotEnabledAnn();
	connect(m_ui.m_pChkRightAnnVis,SIGNAL(toggled(bool)),this,SLOT(slotEnabledAnn()));
	connect(m_ui.m_pChkLeftAnnVis,SIGNAL(toggled(bool)),this,SLOT(slotEnabledAnn()));

}

void CXPageSectionSurfaceVis::Apply()
{
	m_pViewInfo->SetSectionLineColor(m_ui.m_pPtnLineColor->GetColor());
	m_pViewInfo->SetSectionLineUseObjColor(m_ui.m_pPtnLineColor->ColorType() == 1);
	m_pViewInfo->SetSectionLineWidth(m_ui.m_pCmbLineSize->GetLineWidth());

	m_pViewInfo->SetSectionAnnotationLeftVisible(m_ui.m_pChkLeftAnnVis->isChecked());
	m_pViewInfo->SetSectionAnnotationRightVisible(m_ui.m_pChkRightAnnVis->isChecked());
	m_pViewInfo->SetSectionAnnotationBackgroundVisible(m_ui.m_ChkBgr->isChecked());
	m_pViewInfo->SetSectionAnnotationBackgroundColor(m_ui.m_pPtnAnnBgr->GetColor());
	m_pViewInfo->SetSectionAnnotationColor(m_ui.m_pPtnAnnColor->GetColor());
	m_pViewInfo->SetSectionAnnotationUseObjColor(m_ui.m_pPtnAnnColor->ColorType() == 1);
	m_pViewInfo->SetSectionAnnotationSize(m_ui.m_EdtAnnSize->text().toInt());

	m_pViewInfo->SetSectionIntersectionPointSize(m_ui.m_pCbbPointSize->currentText().toInt());
}

void CXPageSectionSurfaceVis::SetObjectColorBuddyButton(CXButtonColorEdit* pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_pPtnLineColor, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_pPtnAnnColor, &CXButtonColorEdit::slotObjectColorChanged);
}
