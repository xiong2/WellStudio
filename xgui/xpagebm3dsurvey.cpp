#include "xpagebm3dsurvey.h"
#include "xviewinfo3dsurvey.h"

CXPageBM3DSurvey::CXPageBM3DSurvey(QWidget *parent, CXViewInfoObject* pViewInfo)
	: CXBasePropertyPage(parent)
{
	m_ui.setupUi(this);

	m_pViewInfo = dynamic_cast<CXViewInfo3DSurvey*>(pViewInfo);
	Q_ASSERT(m_pViewInfo);

	_Init();
}

CXPageBM3DSurvey::~CXPageBM3DSurvey()
{

}

void CXPageBM3DSurvey::Apply()
{
	m_pViewInfo->SetBoundaryLineUseObjColor(m_ui.m_colorBtnBoundaryLine->ColorType() == 1);
	m_pViewInfo->SetBoundaryLineColor(m_ui.m_colorBtnBoundaryLine->GetColor());
	m_pViewInfo->SetBoundaryLineWidth(m_ui.m_spinBoxBoundaryLineWidth->value());

	m_pViewInfo->SetSeismicLineVisible(m_ui.m_cbSeismicLineVisible->isChecked());
	m_pViewInfo->SetSeismicLineUseObjColor(m_ui.m_colorBtnSeismicLine->ColorType() == 1);
	m_pViewInfo->SetSeismicLineColor(m_ui.m_colorBtnSeismicLine->GetColor());
	m_pViewInfo->SetSeismicLineWidth(m_ui.m_spinBoxSeismicLineWidth->value());

	m_pViewInfo->SetTracePointVisible(m_ui.m_cbTracePointVisible->isChecked());
	m_pViewInfo->SetTracePointUseObjColor(m_ui.m_colorBtnTracePoint->ColorType() == 1);
	m_pViewInfo->SetTracePointColor(m_ui.m_colorBtnTracePoint->GetColor());
	m_pViewInfo->SetTracePointSymbol(m_ui.m_cbbTracePointSymbol->currentIndex());

	m_pViewInfo->SetTickmarksVisible(m_ui.m_cbTickMarksVisible->isChecked());
	m_pViewInfo->SetTickmarksUseObjColor(m_ui.m_colorBtnTickMarks->ColorType() == 1);
	m_pViewInfo->SetTickmarksColor(m_ui.m_colorBtnTickMarks->GetColor());
	m_pViewInfo->SetTickmarksFont(m_ui.m_cbbFontTickMarks->currentText());
	m_pViewInfo->SetTickmarksFontSize(m_ui.m_spinBoxFontSizeTickMarks->value());
	m_pViewInfo->SetInlineAnnotationOnBegin(m_ui.m_cbInlineOnBegin->isChecked());
	m_pViewInfo->SetInlineAnnotationOnEnd(m_ui.m_cbInlineOnEnd->isChecked());
	m_pViewInfo->SetXlineAnnotationOnBegin(m_ui.m_cbXlineOnBegin->isChecked());
	m_pViewInfo->SetXlineAnnotationOnEnd(m_ui.m_cbXlineOnEnd->isChecked());

	m_pViewInfo->SetSurveyNameVisible(m_ui.m_cbSurveyNameVisible->isChecked());
	m_pViewInfo->SetSurveyNameUseObjColor(m_ui.m_colorBtnSurveyName->ColorType() == 1);
	m_pViewInfo->SetSurveyNameColor(m_ui.m_colorBtnSurveyName->GetColor());
	m_pViewInfo->SetSurveyNameFont(m_ui.m_cbbFontSurveyName->currentText());
	m_pViewInfo->SetSurveyNameFontSize(m_ui.m_spinBoxSurveyName->value());
}

void CXPageBM3DSurvey::SetObjectColorBuddyButton(CXButtonColorEdit* pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_colorBtnBoundaryLine, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_colorBtnSeismicLine, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_colorBtnTracePoint, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_colorBtnTickMarks, &CXButtonColorEdit::slotObjectColorChanged);
}

void CXPageBM3DSurvey::_Init()
{
	m_ui.m_colorBtnBoundaryLine->AddButton("Object color", m_pViewInfo->GetColor());
	m_ui.m_colorBtnSeismicLine->AddButton("Object color", m_pViewInfo->GetColor());
	m_ui.m_colorBtnTracePoint->AddButton("Object color", m_pViewInfo->GetColor());
	m_ui.m_colorBtnTickMarks->AddButton("Object color", m_pViewInfo->GetColor());
	m_ui.m_colorBtnSurveyName->AddButton("Object color", m_pViewInfo->GetColor());

	m_ui.m_colorBtnBoundaryLine->SetColor(m_pViewInfo->GetBoundaryLineUseObjColor(), m_pViewInfo->GetBoundaryLineColor());
	m_ui.m_spinBoxBoundaryLineWidth->setValue(m_pViewInfo->GetBoundaryLineWidth());

	m_ui.m_cbSeismicLineVisible->setChecked(m_pViewInfo->GetSeismicLineVisible());
	m_ui.m_colorBtnSeismicLine->SetColor(m_pViewInfo->GetSeismicLineUseObjColor(), m_pViewInfo->GetSeismicLineColor());
	m_ui.m_spinBoxSeismicLineWidth->setValue(m_pViewInfo->GetSeismicLineWidth());

	m_ui.m_cbTracePointVisible->setChecked(m_pViewInfo->GetTracePointVisible());
	m_ui.m_colorBtnTracePoint->SetColor(m_pViewInfo->GetTracePointUseObjColor(), m_pViewInfo->GetTracePointColor());
	m_ui.m_cbbTracePointSymbol->setCurrentIndex(m_pViewInfo->GetTracePointSymbol());

	m_ui.m_cbTickMarksVisible->setChecked(m_pViewInfo->GetTickmarksVisible());
	m_ui.m_colorBtnTickMarks->SetColor(m_pViewInfo->GetTickmarksUseObjColor(), m_pViewInfo->GetTickmarksColor());
	m_ui.m_cbbFontTickMarks->setCurrentText(m_pViewInfo->GetTickmarksFont());
	m_ui.m_spinBoxFontSizeTickMarks->setValue(m_pViewInfo->GetTickmarksFontSize());
	m_ui.m_cbInlineOnBegin->setChecked(m_pViewInfo->GetInlineAnnotationOnBegin());
	m_ui.m_cbInlineOnEnd->setChecked(m_pViewInfo->GetInlineAnnotationOnEnd());
	m_ui.m_cbXlineOnBegin->setChecked(m_pViewInfo->GetXlineAnnotationOnBegin());
	m_ui.m_cbXlineOnEnd->setChecked(m_pViewInfo->GetXlineAnnotationOnEnd());

	m_ui.m_cbSurveyNameVisible->setChecked(m_pViewInfo->GetSurveyNameVisible());
	m_ui.m_colorBtnSurveyName->SetColor(m_pViewInfo->GetSurveyNameUseObjColor(), m_pViewInfo->GetSurveyNameColor());
	m_ui.m_cbbFontSurveyName->setCurrentText(m_pViewInfo->GetSurveyNameFont());
	m_ui.m_spinBoxSurveyName->setValue(m_pViewInfo->GetSurveyNameFontSize());
}
