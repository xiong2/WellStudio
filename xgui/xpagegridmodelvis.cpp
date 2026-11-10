#include "xpagegridmodelvis.h"
#include "ui_xpagegridmodelvis.h"

#include <cassert>

#include "xviewinfo3dgridmodel.h"

CXPageGridModelVis::CXPageGridModelVis(QWidget *parent, CXViewInfoObject* pViewInfo)
	: CXBasePropertyPage(parent)
{
	m_pUi = new Ui::CXPageGridModelVis();
	m_pUi->setupUi(this);

    m_pViewInfo = dynamic_cast<CXViewInfo3DGridModel*>(pViewInfo);
	assert(m_pViewInfo);

	_InitData();
}

CXPageGridModelVis::~CXPageGridModelVis()
{
	delete m_pUi;
}

void CXPageGridModelVis::_InitData()
{
	// Geometry
	m_pUi->m_pColorEditGeom->SetColor(m_pViewInfo->GetColor());

	// Grid line
	m_pUi->m_pChkVisibleLine->setChecked(m_pViewInfo->GetDisplayLine());
	m_pUi->m_pColorEditLine->SetColor(m_pViewInfo->GetLineColor());
}

void CXPageGridModelVis::Apply()
{
	// Geometry
	m_pViewInfo->SetGeomColor(m_pUi->m_pColorEditGeom->GetColor());

	// Grid line
	m_pViewInfo->SetDisplayLine(m_pUi->m_pChkVisibleLine->isChecked());
	m_pViewInfo->SetLineColor(m_pUi->m_pColorEditLine->GetColor());
}