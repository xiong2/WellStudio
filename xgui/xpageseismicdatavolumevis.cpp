#include "xpageseismicdatavolumevis.h"
#include "xviewinfoseismicdv.h"

CXPageSeismicDataVolumeVis::CXPageSeismicDataVolumeVis(QWidget *parent, CXViewInfoObject* pViewInfo)
	: CXBasePropertyPage(parent)
{
	m_ui.setupUi(this);
	m_pViewInfo = dynamic_cast<CXViewInfoSeismicDV*>(pViewInfo);
	Q_ASSERT(m_pViewInfo);

	_Init();
}

CXPageSeismicDataVolumeVis::~CXPageSeismicDataVolumeVis()
{

}

void CXPageSeismicDataVolumeVis::Apply()
{
	m_pViewInfo->SetBMUseObjectColor(m_ui.m_color->ColorType() == 1);
	m_pViewInfo->SetBMFrameColor(m_ui.m_color->GetColor());
	m_pViewInfo->SetBMFrameWidth(m_ui.m_cbbWidth->GetLineWidth());
}

void CXPageSeismicDataVolumeVis::SetObjectColorBuddyButton(CXButtonColorEdit* pButton)
{
	connect(pButton, &CXButtonColorEdit::ColorSelected, m_ui.m_color, &CXButtonColorEdit::slotObjectColorChanged);
}

void CXPageSeismicDataVolumeVis::_Init()
{
	m_ui.m_color->AddButton("Object color", m_pViewInfo->GetBMFrameColor());
	m_ui.m_color->SetColor(m_pViewInfo->GetBMUseObjectColor(), m_pViewInfo->GetBMFrameColor());
	m_ui.m_cbbWidth->SetLineWidth(m_pViewInfo->GetBMFrameWidth());
}