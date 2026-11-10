#include "gsbmrosediagramvispage.h"
#include "gsrosediagramviewinfo.h"

GSBMRoseDiagramVisPage::GSBMRoseDiagramVisPage(CXViewInfoObject *pViewInfo, QWidget * parent)
	: CXBasePropertyPage(parent), m_pViewInfo(dynamic_cast<GSRoseDiagramViewInfo*>(pViewInfo))
{
	ui.setupUi(this);

	ui.spinBoxSize->setValue(m_pViewInfo->GetSize());
	ui.comboBox->setCurrentIndex(m_pViewInfo->GetRosePos());
	ui.spinBoxPNumber->setValue(m_pViewInfo->GetNumPetal() * 2);
	ui.horizontalSliderPO->setValue(m_pViewInfo->GetRoseOpacity());
	ui.pushButtonLColor->SetColor(m_pViewInfo->GetLineColor());
	ui.pushButtonPColor->SetColor(m_pViewInfo->GetPetalColor());
	ui.groupBoxRange->setChecked(m_pViewInfo->GetShowRange());
	ui.pushButtonRColor->SetColor(QColor("yellow"));
	ui.horizontalSliderRO->setValue(m_pViewInfo->GetRangeOpacity());
}

GSBMRoseDiagramVisPage::~GSBMRoseDiagramVisPage() {
	
}

void GSBMRoseDiagramVisPage::Apply()
{
	m_pViewInfo->SetSize(ui.spinBoxSize->value());
	m_pViewInfo->SetRosePos(ui.comboBox->currentIndex());
	m_pViewInfo->SetNumPetal(ui.spinBoxPNumber->value() / 2);
	m_pViewInfo->SetRoseOpacity(ui.horizontalSliderPO->value());
	m_pViewInfo->SetLineColor(ui.pushButtonLColor->GetColor());
	m_pViewInfo->SetPetalColor(ui.pushButtonPColor->GetColor());
	m_pViewInfo->SetShowRange(ui.groupBoxRange->isChecked());
	m_pViewInfo->SetRangeColor(ui.pushButtonRColor->GetColor());
	m_pViewInfo->SetRangeOpacity(ui.horizontalSliderRO->value());
	m_pViewInfo->SetRosePos(ui.comboBox->currentIndex());
}