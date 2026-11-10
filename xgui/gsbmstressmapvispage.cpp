#include "gsbmstressmapvispage.h"
#include "gsstressmapviewinfo.h"

GSBMStressMapVisPage::GSBMStressMapVisPage(CXViewInfoObject* pViewInfo, QWidget *parent)
	: CXBasePropertyPage(parent), m_pViewInfo(dynamic_cast<GSStressMapViewInfo*>(pViewInfo))
{
	Q_ASSERT(m_pViewInfo);
	ui.setupUi(this);

	ui.groupBoxStressStates->setChecked(m_pViewInfo->GetShowStressStates());
	ui.checkBoxTL->setChecked(m_pViewInfo->GetShowAsTrafficLight());
	ui.horizontalSlider_StatesOpacity->setValue(m_pViewInfo->GetStressStatesOpacity() * 10);

	ui.colorButton_StressLine->SetColor(m_pViewInfo->GetStresslinesColor());
	ui.spinBox_StressLineWidth->setValue(m_pViewInfo->GetStresslinesWidth());
	ui.spinBox_StressLineStep->setValue(m_pViewInfo->GetStresslinesStep());

	ui.groupBoxFaultPolygon->setChecked(m_pViewInfo->GetShowFaultPolygon());
	ui.colorButtonFPL->SetColor(m_pViewInfo->GetFPLineColor());
	ui.spinBoxFPLineWidth->setValue(m_pViewInfo->GetFPLineWidth());
	ui.colorButtonFPF->SetColor(m_pViewInfo->GetFPFillColor());

	ui.groupBoxStructure->setChecked(m_pViewInfo->GetShowCapsule());
	ui.colorButton_CapsuleLineColor->SetColor(m_pViewInfo->GetCapsuleLineColor());
	ui.horizontalSlider_Opacity->setValue(m_pViewInfo->GetCapsuleOpacity() * 10);

	ui.groupBoxAnticline->setChecked(m_pViewInfo->GetShowAnticline());
	ui.colorButton_AnticlineColor->SetColor(m_pViewInfo->GetAnticlineColor());
	ui.spinBox_AnticlineWidth->setValue(m_pViewInfo->GetAnticlineWidth());
	ui.spinBox_AnticlineMarkerSize->setValue(m_pViewInfo->GetAnticlineMarkerSize());
	ui.spinBox_AnticlineArrowSize->setValue(m_pViewInfo->GetAnticlineStressArrowSize());
}

GSBMStressMapVisPage::~GSBMStressMapVisPage()
{

}

void GSBMStressMapVisPage::Apply()
{
	m_pViewInfo->SetShowStressStates(ui.groupBoxStressStates->isChecked());
	m_pViewInfo->SetShowAsTrafficLight(ui.checkBoxTL->isChecked());
	m_pViewInfo->SetStressStatesOpacity(ui.horizontalSlider_StatesOpacity->value() / 10.0);

	m_pViewInfo->SetStresslinesColor(ui.colorButton_StressLine->GetColor());
	m_pViewInfo->SetStresslinesLength(ui.spinBoxLength->value());
	m_pViewInfo->SetStresslinesWidth(ui.spinBox_StressLineWidth->value());
	m_pViewInfo->SetStresslinesStep(ui.spinBox_StressLineStep->value());

	m_pViewInfo->SetShowFaultPolygon(ui.groupBoxFaultPolygon->isChecked());
	m_pViewInfo->SetFPLineColor(ui.colorButtonFPL->GetColor());
	m_pViewInfo->SetFPLineWidth(ui.spinBoxFPLineWidth->value());
	m_pViewInfo->SetFPFillColor(ui.colorButtonFPF->GetColor());

	m_pViewInfo->SetShowCapsule(ui.groupBoxStructure->isChecked());
	m_pViewInfo->SetCapsuleLineColor(ui.colorButton_CapsuleLineColor->GetColor());
	m_pViewInfo->SetCapsuleOpacity(ui.horizontalSlider_Opacity->value() / 10.0);

	m_pViewInfo->SetShowAnticline(ui.groupBoxAnticline->isChecked());
	m_pViewInfo->SetAnticlineColor(ui.colorButton_AnticlineColor->GetColor());
	m_pViewInfo->SetAnticlineWidth(ui.spinBox_AnticlineWidth->value());
	m_pViewInfo->SetAnticlineMarkerSize(ui.spinBox_AnticlineMarkerSize->value());
	m_pViewInfo->SetAnticlineStressArrowSize(ui.spinBox_AnticlineArrowSize->value());
}
