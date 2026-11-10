#include "xpagebm2dpolygon.h"
#include "ui_xpagebm2dpolygon.h"
#include "xviewinfo2dpolygon.h"

CXPageBM2DPolygon::CXPageBM2DPolygon(QWidget *parent, CXViewInfoObject* pViewInfo)
	: CXBasePropertyPage(parent)
{
	m_ui = new Ui::CXPageBM2DPolygon();
	m_ui->setupUi(this);

	m_pViewInfo = dynamic_cast<CXViewInfo2DPolygon*>(pViewInfo);
	Q_ASSERT(m_pViewInfo);

	_Init();
}

CXPageBM2DPolygon::~CXPageBM2DPolygon()
{
	delete m_ui;
}

void CXPageBM2DPolygon::Apply()
{
	m_pViewInfo->SetBMLineUseObjectColor(m_ui->m_colorBtnLine->IsObjectColor());
	m_pViewInfo->SetBMLineColor(m_ui->m_colorBtnLine->GetColor());
	m_pViewInfo->SetBMLineWidth(m_ui->m_spinBoxLineWidth->value());

	m_pViewInfo->SetBMPivotUseObjectColor(m_ui->m_colorBtnPivot->IsObjectColor());
	m_pViewInfo->SetBMPivotColor(m_ui->m_colorBtnPivot->GetColor());
	m_pViewInfo->SetBMPivotSize(m_ui->m_spinBoxPivotSize->value());

	m_pViewInfo->SetBMIsFill(m_ui->m_cbFill->isChecked());
	m_pViewInfo->SetBMFillUseObjectColor(m_ui->m_colorBtnFill->IsObjectColor());
	
	QColor colorFill = m_ui->m_colorBtnFill->GetColor();
	colorFill.setAlphaF(m_ui->m_widgetAlpha->GetValue());
	m_pViewInfo->SetBMFillColor(colorFill);
}

void CXPageBM2DPolygon::SetObjectColorBuddyButton(CXButtonColorEdit * pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui->m_colorBtnLine, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui->m_colorBtnPivot, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui->m_colorBtnFill, &CXButtonColorEdit::slotObjectColorChanged);
}

void CXPageBM2DPolygon::_Init()
{
	m_ui->m_colorBtnLine->AddObjectColorButton(m_pViewInfo->GetColor());
	m_ui->m_colorBtnLine->SetColor(m_pViewInfo->GetBMLineUseObjectColor(), m_pViewInfo->GetBMLineColor());
	m_ui->m_spinBoxLineWidth->setValue(m_pViewInfo->GetBMLineWidth());

	m_ui->m_colorBtnPivot->AddObjectColorButton(m_pViewInfo->GetColor());
	m_ui->m_colorBtnPivot->SetColor(m_pViewInfo->GetBMPivotUseObjectColor(), m_pViewInfo->GetBMPivotColor());
	m_ui->m_spinBoxPivotSize->setValue(m_pViewInfo->GetBMPivotSize());

	m_ui->m_cbFill->setChecked(m_pViewInfo->GetBMIsFill());
	m_ui->m_colorBtnFill->AddObjectColorButton(m_pViewInfo->GetColor());
	m_ui->m_colorBtnFill->SetColor(m_pViewInfo->GetBMFillUseObjectColor(), m_pViewInfo->GetBMFillColor());
	m_ui->m_widgetAlpha->SetLabelString("Transparent:");
	m_ui->m_widgetAlpha->InitWidget(0.0, 1.0, 0.1, 11, 1);
	m_ui->m_widgetAlpha->SetValue(m_pViewInfo->GetBMFillColor().alphaF());
}

