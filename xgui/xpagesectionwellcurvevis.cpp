#include "xpagesectionwellcurvevis.h"
#include "xviewinfowellcurve.h"

CXPageSectionWellCurveVis::CXPageSectionWellCurveVis(QWidget *parent, CXViewInfoObject* pViewInfo)
	: CXBasePropertyPage(parent)
{
	m_ui.setupUi(this);
	m_pViewInfo = dynamic_cast<CXViewInfoWellCurve*>(pViewInfo);
	_InitUI();
}

CXPageSectionWellCurveVis::~CXPageSectionWellCurveVis()
{

}

void CXPageSectionWellCurveVis::Apply()
{
	m_pViewInfo->SetDisplayModeSection(!m_ui.m_pRadioBtnCurve->isChecked());
	
	m_pViewInfo->SetLineVisible(m_ui.m_pChkVisibleLine->isChecked());
	m_pViewInfo->SetLineWidth(m_ui.m_pEdtLineWidth->text().toInt());
	m_pViewInfo->SetLineColorMode(m_ui.m_pClrBtnLine->ColorType());
	m_pViewInfo->SetLineColor(m_ui.m_pClrBtnLine->GetColor());

	m_pViewInfo->SetFillVisible(m_ui.m_pChkVisibleFill->isChecked());
	m_pViewInfo->SetFillWidth(m_ui.m_pEdtFillWidth->text().toInt());
	m_pViewInfo->SetFillColorMode(m_ui.m_pClrBtnFill->ColorType());
	m_pViewInfo->SetFillColor(m_ui.m_pClrBtnFill->GetColor());

	m_pViewInfo->SetVIWidth(m_ui.m_pEdtVIWidth->text().toInt());

	m_pViewInfo->SetFilterType(m_ui.m_pCbbFilterType->currentIndex());
	m_pViewInfo->SetFilterLowFreq(m_ui.m_pDsbxLowFreq->value());
	m_pViewInfo->SetFilterLowOverlap(m_ui.m_pDsbxLowOverlap->value());
	m_pViewInfo->SetFilterHighFreq(m_ui.m_pDsbxHighFreq->value());
	m_pViewInfo->SetFilterHighOverlap(m_ui.m_pDsbxHighOverlap->value());
}

void CXPageSectionWellCurveVis::SetObjectColorBuddyButton(CXButtonColorEdit *pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_pClrBtnLine, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_pClrBtnFill, &CXButtonColorEdit::slotObjectColorChanged);
}

void CXPageSectionWellCurveVis::_InitUI()
{
	if (!m_pViewInfo)
		return;

	m_ui.m_pClrBtnLine->AddObjectColorButton(m_pViewInfo->GetColor());
	m_ui.m_pClrBtnFill->AddObjectColorButton(m_pViewInfo->GetColor());
	m_ui.m_pClrBtnFill->AddColormapButton();

	m_ui.m_pRadioBtnCurve->setChecked(!m_pViewInfo->GetDisplayModeSection());
	m_ui.m_pRadioBtnVI->setChecked(m_pViewInfo->GetDisplayModeSection());

	m_ui.m_pChkVisibleLine->setChecked(m_pViewInfo->GetLineVisible());
	m_ui.m_pEdtLineWidth->setText(QString::number(m_pViewInfo->GetLineWidth()));
	m_ui.m_pClrBtnLine->SetColor(m_pViewInfo->GetLineColorMode(), m_pViewInfo->GetLineColor());
	m_ui.m_pChkVisibleFill->setChecked(m_pViewInfo->GetFillVisible());
	m_ui.m_pEdtFillWidth->setText(QString::number(m_pViewInfo->GetFillWidth()));
	m_ui.m_pClrBtnFill->SetColor(m_pViewInfo->GetFillColorMode(), m_pViewInfo->GetFillColor());

	m_ui.m_pEdtVIWidth->setText(QString::number(m_pViewInfo->GetVIWidth()));

	m_ui.m_pCbbFilterType->setCurrentIndex(m_pViewInfo->GetFilterType());
	m_ui.m_pDsbxLowFreq->setValue(m_pViewInfo->GetFilterLowFreq());
	m_ui.m_pDsbxLowOverlap->setValue(m_pViewInfo->GetFilterLowOverlap());
	m_ui.m_pDsbxHighFreq->setValue(m_pViewInfo->GetFilterHighFreq());
	m_ui.m_pDsbxHighOverlap->setValue(m_pViewInfo->GetFilterHighOverlap());

	m_ui.m_pGbxVI->setVisible(m_pViewInfo->GetDisplayModeSection());

	connect(m_ui.m_pCbbFilterType, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &CXPageSectionWellCurveVis::slotFilterTypeChanged);
	slotFilterTypeChanged(m_pViewInfo->GetFilterType());
}

void CXPageSectionWellCurveVis::slotFilterTypeChanged(int type)
{
	switch (type)
	{
	case 0: // no filter
		m_ui.m_pGbxLowValues->setEnabled(false);
		m_ui.m_pGbxHighValues->setEnabled(false);
		break;
	case 1: // low pass
		m_ui.m_pGbxLowValues->setEnabled(true);
		m_ui.m_pGbxHighValues->setEnabled(false);
		break;
	case 2: // band pass
		m_ui.m_pGbxLowValues->setEnabled(true);
		m_ui.m_pGbxHighValues->setEnabled(true);
		break;
	case 3: // high pass
		m_ui.m_pGbxLowValues->setEnabled(false);
		m_ui.m_pGbxHighValues->setEnabled(true);
		break;
	default:
		break;
	}
}