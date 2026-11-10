#include "xpage3dwellcurvevis.h"
#include "xviewinfowellcurve.h"

CXPage3DWellCurveVis::CXPage3DWellCurveVis(QWidget *parent, CXViewInfoObject* pViewInfo)
	: CXBasePropertyPage(parent)
{
	m_ui.setupUi(this);
	m_pViewInfo = dynamic_cast<CXViewInfoWellCurve*>(pViewInfo);
	_InitUI();
}

CXPage3DWellCurveVis::~CXPage3DWellCurveVis()
{

}

void CXPage3DWellCurveVis::Apply()
{
	m_pViewInfo->SetDisplayMode3D(!m_ui.m_pRadioBtnCylinder->isChecked());
	m_pViewInfo->SetLineVisible(m_ui.m_pChkVisibleLine->isChecked());
	m_pViewInfo->SetLineWidth(m_ui.m_pEdtLineWidth->text().toInt());
	m_pViewInfo->SetLineColor(m_ui.m_pClrBtnLine->GetColor());
	m_pViewInfo->SetFillVisible(m_ui.m_pChkVisibleFill->isChecked());
	m_pViewInfo->SetFillWidth(m_ui.m_pEdtFillWidth->text().toInt());
	m_pViewInfo->SetFillColorMode(m_ui.m_pClrBtnFill->ColorType());
	m_pViewInfo->SetFillColor(m_ui.m_pClrBtnFill->GetColor());
}

void CXPage3DWellCurveVis::SetObjectColorBuddyButton(CXButtonColorEdit *pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_pClrBtnLine, &CXButtonColorEdit::slotObjectColorChanged);
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_pClrBtnFill, &CXButtonColorEdit::slotObjectColorChanged);
}

void CXPage3DWellCurveVis::_InitUI()
{
	if (!m_pViewInfo)
		return;

	m_ui.m_pClrBtnLine->AddObjectColorButton(m_pViewInfo->GetColor());
	m_ui.m_pClrBtnFill->AddObjectColorButton(m_pViewInfo->GetColor());
	m_ui.m_pClrBtnFill->AddColormapButton();

	m_ui.m_pRadioBtnCylinder->setChecked(!m_pViewInfo->GetDisplayMode3D());
	m_ui.m_pRadioBtnFlat->setChecked(m_pViewInfo->GetDisplayMode3D());

	m_ui.m_pChkVisibleLine->setChecked(m_pViewInfo->GetLineVisible());
	m_ui.m_pEdtLineWidth->setText(QString::number(m_pViewInfo->GetLineWidth()));
	m_ui.m_pClrBtnLine->SetColor(m_pViewInfo->GetLineColorMode(), m_pViewInfo->GetLineColor());
	m_ui.m_pChkVisibleFill->setChecked(m_pViewInfo->GetFillVisible());
	m_ui.m_pEdtFillWidth->setText(QString::number(m_pViewInfo->GetFillWidth()));
	m_ui.m_pClrBtnFill->SetColor(m_pViewInfo->GetFillColorMode(), m_pViewInfo->GetFillColor());
}
