#include "gsbmsectionvispage.h"
#include "gssectionviewinfo.h"

GSBMSectionVisPage::GSBMSectionVisPage(CXViewInfoObject* pViewInfo, QWidget *parent)
	: CXBasePropertyPage(parent), m_pViewInfo(dynamic_cast<GSSectionViewInfo*>(pViewInfo))
{
	ui.setupUi(this);

	ui.spinBox_Width->setValue(m_pViewInfo->GetWidth());
	ui.groupBox_TurningPoints->setChecked(m_pViewInfo->GetShowTurningPoint());
	ui.spinBox_Radius->setValue(m_pViewInfo->GetTurningPointRadius());
}

GSBMSectionVisPage::~GSBMSectionVisPage()
{

}

void GSBMSectionVisPage::Apply()
{
	m_pViewInfo->SetWidth(ui.spinBox_Width->value());
	m_pViewInfo->SetShowTurningPoint(ui.groupBox_TurningPoints->isChecked());
	m_pViewInfo->SetTurningPointRadius(ui.spinBox_Radius->value());
}
