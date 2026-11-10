#include "gsbm3dhorizonvispage.h"
#include "gs3dhorizonviewinfo.h"

GSBM3DHorizonVisPage::GSBM3DHorizonVisPage(CXViewInfoObject* pViewInfo, QWidget *parent)
	: CXBasePropertyPage(parent), m_pViewInfo(dynamic_cast<GS3DHorizonViewInfo*>(pViewInfo))
{
	Q_ASSERT(m_pViewInfo);
	ui.setupUi(this);

	ui.groupBox->setChecked(m_pViewInfo->GetIsolineDisplay());

	ui.lineEdit_LevelFirst->setText(QString::number(m_pViewInfo->GetIsolineLevelFirst()));
	ui.lineEdit_LevelLast->setText(QString::number(m_pViewInfo->GetIsolineLevelLast()));
	ui.lineEdit_LevelNum->setText(QString::number(m_pViewInfo->GetIsolineLevelNum()));

	ui.colorButton_CoarseLine->SetColor(m_pViewInfo->GetIsolineCoarseColor());
	ui.spinBox_CoarseWidth->setValue(m_pViewInfo->GetIsolineCoarseWidth());
	ui.spinBox_CoarseFreq->setValue(m_pViewInfo->GetIsolineCoarseFreq());
	
	ui.colorButton_NormalLine->SetColor(m_pViewInfo->GetIsolineNormalColor());
	ui.spinBox_NormalWidth->setValue(m_pViewInfo->GetIsolineNormalWidth());
	
	ui.colorButton_Annotation->SetColor(m_pViewInfo->GetIsolineAnnotationColor());
	ui.fontComboBox->setCurrentFont(QFont(m_pViewInfo->GetIsolineAnnotationFontName()));
	ui.spinBox_AnnotationFontSize->setValue(m_pViewInfo->GetIsolineAnnotationFontSize());
}

GSBM3DHorizonVisPage::~GSBM3DHorizonVisPage()
{

}

void GSBM3DHorizonVisPage::Apply()
{
	m_pViewInfo->SetIsolineDisplay(ui.groupBox->isChecked());
	
	double dLevelFirst = ui.lineEdit_LevelFirst->text().toDouble();
	double dLevelLast  = ui.lineEdit_LevelLast->text().toDouble();
	int nLevel = ui.lineEdit_LevelNum->text().toInt();

	if (dLevelFirst != m_pViewInfo->GetIsolineLevelFirst() || dLevelLast != m_pViewInfo->GetIsolineLevelLast() || nLevel != m_pViewInfo->GetIsolineLevelNum())
		m_pViewInfo->SetIsolineLevelChanged(true);

	m_pViewInfo->SetIsolineLevelFirst(dLevelFirst);
	m_pViewInfo->SetIsolineLevelLast(dLevelLast);
	m_pViewInfo->SetIsolineLevelNum(nLevel);

	m_pViewInfo->SetIsolineCoarseColor(ui.colorButton_CoarseLine->GetColor());
	m_pViewInfo->SetIsolineCoarseWidth(ui.spinBox_CoarseWidth->value());
	m_pViewInfo->SetIsolineCoarseFreq(ui.spinBox_CoarseFreq->value());

	m_pViewInfo->SetIsolineNormalColor(ui.colorButton_NormalLine->GetColor());
	m_pViewInfo->SetIsolineNormalWidth(ui.spinBox_NormalWidth->value());

	m_pViewInfo->SetIsolineAnnotationColor(ui.colorButton_Annotation->GetColor());
	m_pViewInfo->SetIsolineAnnotationFontName(ui.fontComboBox->font().family());
	m_pViewInfo->SetIsolineAnnotationFontSize(ui.spinBox_AnnotationFontSize->value());
}
