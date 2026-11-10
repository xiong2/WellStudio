#include "x2dseismiclinevispage.h"

CX2DSeismicLineVisPage::CX2DSeismicLineVisPage(QWidget *parent, CXViewInfoObject* pViewInfo)
	: CXBasePropertyPage(parent)
{
	m_ui.setupUi(this);

	m_pViewInfo = dynamic_cast<CXViewInfo2DSeismicLine*>(pViewInfo);
	Q_ASSERT(m_pViewInfo);

	_Init();
	_InitData();
}

CX2DSeismicLineVisPage::~CX2DSeismicLineVisPage()
{

}

void CX2DSeismicLineVisPage::Apply()
{
	m_pViewInfo->SetDisplayNameOnTop(m_ui.m_checkBoxTop->checkState() == Qt::Checked);
	m_pViewInfo->SetDisplayNameOnBottom(m_ui.m_checkBoxBottom->checkState() == Qt::Checked);
	m_pViewInfo->SetNameColor(m_ui.m_btnNameColor->GetColor());
	m_pViewInfo->SetNameSize(m_ui.m_cbbNameSize->currentText().toInt());
	m_pViewInfo->SetNameFont(m_ui.m_fontComboBox->currentText());
	m_pViewInfo->SetLineColor(m_ui.m_btnLineColor->GetColor());
	m_pViewInfo->SetLineWidth(m_ui.m_cbbLineWidth->GetLineWidth());
}

void CX2DSeismicLineVisPage::_Init()
{
	_InitNameFontSize();
}

void CX2DSeismicLineVisPage::_InitData()
{
	m_ui.m_checkBoxTop->setCheckState(m_pViewInfo->GetDisplayNameOnTop() ? Qt::Checked : Qt::Unchecked);
	m_ui.m_checkBoxBottom->setCheckState(m_pViewInfo->GetDisplayNameOnBottom() ? Qt::Checked : Qt::Unchecked);
	m_ui.m_btnNameColor->SetColor(m_pViewInfo->GetNameColor());
	m_ui.m_cbbNameSize->setCurrentIndex(m_pViewInfo->GetNameSize() - 1);
	m_ui.m_fontComboBox->setCurrentFont(QFont(m_pViewInfo->GetNameFont()));
	m_ui.m_btnLineColor->SetColor(m_pViewInfo->GetLineColor());
	m_ui.m_cbbLineWidth->SetLineWidth(m_pViewInfo->GetLineWidth());
}

void CX2DSeismicLineVisPage::_InitNameFontSize()
{
	QStringList sizeList;
	for (auto i = 0; i != 20; ++i)
		sizeList << QString::number(i + 1);
	m_ui.m_cbbNameSize->addItems(sizeList);
}