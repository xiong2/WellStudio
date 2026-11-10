#pragma warning (push,0)
#include "xpagebuildlfmtwo.h"
#include "xparameterbuildlfm.h"
#include "xglobal.h"
//
#include "x2dpolygon.h"
#include <QMessageBox>
#include <QList>

#include "x3dsurvey.h"
#include <cassert>

#pragma warning(pop)

CXPageBuildLFMTwo::CXPageBuildLFMTwo(CXParameterBuildLFM* pPara, QWidget *parent)
	: m_pPara(pPara), QWizardPage(parent)
{
	m_ui.setupUi(this);
	assert(m_pPara);

	// two buttons
	QPixmap pixAdd, pixRemove;
	pixAdd.load(::GetIconPath() + "18804.png");
	pixRemove.load(::GetIconPath() + "Delete.png");
	m_ui.m_BtnAddPolygon->setIcon(QIcon(pixAdd));
	m_ui.m_pBtnRemovePolygon->setIcon(QIcon(pixRemove));

	//	Connections
	connect(m_ui.m_BtnAddPolygon, SIGNAL(clicked()), this, SLOT(slotAddPolygon()));
	connect(m_ui.m_pBtnRemovePolygon, SIGNAL(clicked()), this, SLOT(slotRemovePolygon()));

	m_ui.m_pInlineWidget->SetSliderName("Inline");
	m_ui.m_pXlineWidget->SetSliderName("Crossline");
}

CXPageBuildLFMTwo::~CXPageBuildLFMTwo()
{

}

void CXPageBuildLFMTwo::initializePage()
{
	QUuid uuidSurvey = m_pPara->GetSurveyID();
	CX3DSurvey* pSurvey = dynamic_cast<CX3DSurvey*>(::GetObjectByID(uuidSurvey));
	if (!pSurvey)
		return;

	// Inline
	int iInlineStart, iInlineEnd, iInlineStep, iXlineStart, iXlineEnd, iXlineStep;
	pSurvey->GetUTM().GetLineNumRange(iInlineStart, iInlineEnd, iInlineStep, iXlineStart, iXlineEnd, iXlineStep);

	m_ui.m_pInlineWidget->SetRangeAndPrecision(iInlineStart, iInlineEnd, iInlineStep, 0);
	m_ui.m_pXlineWidget->SetRangeAndPrecision(iXlineStart, iXlineEnd, iXlineStep, 0);
}

void CXPageBuildLFMTwo::slotAddPolygon()
{
	CXObject* pCurrentObj = ::GetCurrentObject();
	CX2DPolygon* pPolygon = dynamic_cast<CX2DPolygon*>(pCurrentObj);
	if (!pPolygon)
	{
		QMessageBox::warning(this, ::g_strProductName, "The selected item must be a polygon.");
		return;
	}

	m_pPara->SetPolygonID(pPolygon->GetObjectID());
	m_ui.m_pLinePolygon->setText(pPolygon->GetObjectName());
}

void CXPageBuildLFMTwo::slotRemovePolygon()
{
	m_pPara->SetPolygonID(QUuid());
	m_ui.m_pLinePolygon->setText("");
}

bool CXPageBuildLFMTwo::validatePage()
{
	m_pPara->SetMinInlineNum((int)m_ui.m_pInlineWidget->GetMinValue());
	m_pPara->SetMaxInlineNum((int)m_ui.m_pInlineWidget->GetMaxValue());
	m_pPara->SetMinXlineNum((int)m_ui.m_pXlineWidget->GetMinValue());
	m_pPara->SetMaxXlineNum((int)m_ui.m_pXlineWidget->GetMaxValue());

	return true;
}
