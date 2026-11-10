#include "xpagewelltopformation.h"

#include <cassert>

#include "xviewinfoobject.h"
#include "xviewinfo3dwelltopformation.h"

CXPageWellTopFormation::CXPageWellTopFormation(QWidget *parent, CXViewInfoObject *pViewInfo)
	: CXBasePropertyPage(parent)
{
	m_ui.setupUi(this);

	assert(pViewInfo);
    m_pViewInfo = dynamic_cast<CXViewInfo3DWellTopFormation*>(pViewInfo);
	_InitUI();

	connect(m_ui.m_btngroupMode, SIGNAL(buttonClicked(int)), this, SLOT(_ChangeLabelName(int)));
}

void CXPageWellTopFormation::_InitUI()
{
	m_ui.m_btngroupMode->setId(m_ui.m_rdbSphere, 0);
	m_ui.m_btngroupMode->setId(m_ui.m_rdbDisk, 1);
	m_ui.m_btngroupMode->setId(m_ui.m_rdbCube, 2);

	if (m_pViewInfo == nullptr)
	{
		m_ui.m_rdbSphere->setChecked(true);
		m_ui.m_dsbRadius->setValue(20);
		m_ui.m_cbbColor->SetColor(QColor(255,255,255));
	}
	else
	{
		int id = static_cast<int>(m_pViewInfo->GetDisplayMode());
		QRadioButton* rdb = dynamic_cast<QRadioButton*>(m_ui.m_btngroupMode->button(id));
		rdb->setChecked(true);
		m_ui.m_dsbRadius->setValue(static_cast<int>(m_pViewInfo->GetRadius()));
		m_ui.m_cbbColor->SetColor(m_pViewInfo->GetWellTopFormationColor());
	}
}

void CXPageWellTopFormation::Apply()
{
	if (m_pViewInfo == nullptr) return;
    m_pViewInfo->SetDisplayMode(static_cast<CXViewInfo3DWellTopFormation::EDisplayMode>(m_ui.m_btngroupMode->checkedId()));
	m_pViewInfo->SetRadius(static_cast<float>(m_ui.m_dsbRadius->value()));
	m_pViewInfo->SetWellTopFormationColor(m_ui.m_cbbColor->GetColor());
}

void CXPageWellTopFormation::_ChangeLabelName(int id)
{
	switch(id)
	{
	case 0:
	case 1:
		m_ui.m_labelName->setText("Radius");
		break;
	case 2:
		m_ui.m_labelName->setText("Length");
		break;
	default:
		assert(!"Error Button id");
	}
}