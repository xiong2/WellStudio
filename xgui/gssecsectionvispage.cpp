#include "gssecsectionvispage.h"
#include "gssectionviewinfo.h"

GSSecSectionVisPage::GSSecSectionVisPage(CXViewInfoObject* pViewInfo, QWidget *parent)
	: CXBasePropertyPage(parent), m_pViewInfo(dynamic_cast<GSSectionViewInfo*>(pViewInfo))
{
	ui.setupUi(this);

	ui.radioButtonH->setChecked(!m_pViewInfo->GetFillByStress());
	ui.checkBoxLH->setChecked(m_pViewInfo->GetLeftHName());
	ui.checkBoxRH->setChecked(m_pViewInfo->GetRightHName());
	ui.checkBoxLP->setChecked(m_pViewInfo->GetLeftPName());
	ui.checkBoxRP->setChecked(m_pViewInfo->GetRightPName());
}

GSSecSectionVisPage::~GSSecSectionVisPage()
{

}

void GSSecSectionVisPage::Apply()
{
	m_pViewInfo->SetFillByStress(ui.radioButtonS->isChecked());
	m_pViewInfo->SetLeftHName(ui.checkBoxLH->isChecked());
	m_pViewInfo->SetRightHName(ui.checkBoxRH->isChecked());
	m_pViewInfo->SetLeftPName(ui.checkBoxLP->isChecked());
	m_pViewInfo->SetRightPName(ui.checkBoxRP->isChecked());
}
