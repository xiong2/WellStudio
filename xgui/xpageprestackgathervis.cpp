#include "xpageprestackgathervis.h"
#include "xviewinfoprestackgather.h"
#include "xeventconsole.h"
#include "xobject.h"

CXPagePreStackGatherVis::CXPagePreStackGatherVis(CXViewInfoObject *pViewInfo, CXObject *pObj, QWidget *parent)
	: CXBasePropertyPage(parent)
{
	ui.setupUi(this);

	m_pViewInfo = dynamic_cast<CXViewInfoPreStackGather*>(pViewInfo);
	Q_ASSERT(m_pViewInfo);

	_Init();
	connect(ui.widget_SliderSpin, &CXSliderSpinWidget::ValueChanged, [this, pObj](double) { 
		m_pViewInfo->SetCURShotID(ui.widget_SliderSpin->GetValue());
		CXProcessEvent processEvent;
		pObj->AddEvent(EDataChanged);
	});
	connect(ui.radioBtn_ViewAll, &QRadioButton::toggled, [this, pObj](bool) {
		m_pViewInfo->SetIsViewAll(ui.radioBtn_ViewAll->isChecked());
		CXProcessEvent processEvent;
		pObj->AddEvent(EInfoChanged);
	});
}

CXPagePreStackGatherVis::~CXPagePreStackGatherVis()
{

}

void CXPagePreStackGatherVis::Apply()
{
	// Range
	m_pViewInfo->SetIsViewAll(ui.radioBtn_ViewAll->isChecked());
	if (ui.radioBtn_Specified->isChecked())
		m_pViewInfo->SetCURShotID(ui.widget_SliderSpin->GetValue());
	// Source Point
	m_pViewInfo->SetSourcePointShape(ui.comboBox_SourceShape->currentIndex());
	m_pViewInfo->SetSourcePointSize(ui.spinBox_SourceSize->value());
	m_pViewInfo->SetSourcePointColor(ui.btn_SourceColor->GetColor());
	// Detect Point
	m_pViewInfo->SetDetectPointShape(ui.comboBox_DetectShape->currentIndex());
	m_pViewInfo->SetDetectPointSize(ui.spinBox_DetectSize->value());
	m_pViewInfo->SetDetectPointColor(ui.btn_DetectColor->GetColor());
}

void CXPagePreStackGatherVis::_Init()
{
	// Range
	(m_pViewInfo->GetIsViewAll() ? ui.radioBtn_ViewAll : ui.radioBtn_Specified)->setChecked(true);
	
	ui.widget_SliderSpin->InitWidget(m_pViewInfo->GetMINShotID(), m_pViewInfo->GetMAXShotID(), m_pViewInfo->GetShotIDStep(), m_pViewInfo->GetShotIDNum(), -1);
	ui.widget_SliderSpin->SetValue(m_pViewInfo->GetCURShotID());
	// Source Point
	ui.comboBox_SourceShape->setCurrentIndex(m_pViewInfo->GetSourcePointShape());
	ui.spinBox_SourceSize->setValue(m_pViewInfo->GetSourcePointSize());
	ui.btn_SourceColor->SetColor(m_pViewInfo->GetSourcePointColor());
	// Detect Point
	ui.comboBox_DetectShape->setCurrentIndex(m_pViewInfo->GetDetectPointShape());
	ui.spinBox_DetectSize->setValue(m_pViewInfo->GetDetectPointSize());
	ui.btn_DetectColor->SetColor(m_pViewInfo->GetDetectPointColor());
}
