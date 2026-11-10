#include "xpage3dpoints.h"

CXPage3DPoints::CXPage3DPoints(CXViewInfoObject* pViewInfo, QWidget *parent)
	: CXBasePropertyPage(parent)
{
	ui.setupUi(this);

	m_pViewInfo = dynamic_cast<CXViewInfo3DPoints*>(pViewInfo);

	ui.spinBox->setValue(m_pViewInfo->GetPointSize());
	ui.pushButton->AddObjectColorButton(m_pViewInfo->GetColor());
	ui.pushButton->SetColor(m_pViewInfo->GetIsObjectColor(), m_pViewInfo->GetPointColor());
}

CXPage3DPoints::~CXPage3DPoints()
{

}

void CXPage3DPoints::Apply()
{
	m_pViewInfo->SetPointSize(ui.spinBox->value());
	m_pViewInfo->SetIsObjectColor(ui.pushButton->ColorType());
	m_pViewInfo->SetPointColor(ui.pushButton->GetColor());
}

void CXPage3DPoints::SetObjectColorBuddyButton(CXButtonColorEdit *pColorEdit)
{
	connect(pColorEdit, &CXButtonColorEdit::ColorSelected, ui.pushButton, &CXButtonColorEdit::slotObjectColorChanged);
}
