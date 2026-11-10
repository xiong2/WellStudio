#pragma warning (push,0)
#include "xpagecssinversiontwo.h"
#include "xparametercssinversion.h"
#include "xglobal.h"
#include "xseismicdatavolume.h"
//
#include <QMessageBox>

#include "xproject.h"
#include <cassert>
#include "xsysteminfo.h"

#pragma warning(pop)

CXPageCSSInversionTwo::CXPageCSSInversionTwo(CXParameterCSSInversion* pPara, QWidget *parent)
	:m_pPara(pPara), QWizardPage(parent)
{
	m_ui.setupUi(this);

	assert(pPara);

	_Init();
}

CXPageCSSInversionTwo::~CXPageCSSInversionTwo()
{
}

void CXPageCSSInversionTwo::_Init()
{
	// cpu number
	int nCPUNum = CXSystemInfo::GetCPUNum();
	for (int i = 1; i <= nCPUNum; ++i)
	{
		m_ui.m_pCmbCPUNumber->addItem(QString::number(i));
	}
	m_ui.m_pCmbCPUNumber->setCurrentIndex(nCPUNum - 1);
}

void CXPageCSSInversionTwo::initializePage()
{
	// prestack
	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetDVID()));
	if (!pDV)
		return;
	pDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);

	// Zp
	CXSeismicDataVolume* pZpDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetImpedanceID()));
	if (!pZpDV)
		return;

	int iInlineMin1, iInlineMax1, iInlineInc1, iXlineMin1, iXlineMax1, iXlineInc1;
	pZpDV->GetUTM().GetLineNumRange(iInlineMin1, iInlineMax1, iInlineInc1, iXlineMin1, iXlineMax1, iXlineInc1);

	iInlineMin = qMax(iInlineMin, iInlineMin1);
	iInlineMax = qMin(iInlineMax, iInlineMax1);
	iInlineInc = qMax(iInlineInc, iInlineInc1);

	iXlineMin = qMax(iXlineMin, iXlineMin1);
	iXlineMax = qMin(iXlineMax, iXlineMax1);
	iXlineInc = qMax(iXlineInc, iXlineInc1);
	

	if (iInlineMin > iInlineMax || iXlineMin > iXlineMax)
	{
		QMessageBox::warning(this, ::g_strProductName, "Cannot find the valid region between the seismic data and the impedance data.");
		return;
	}

	// set range
	iInlineMax = (iInlineMax - iInlineMin) / iInlineInc*iInlineInc + iInlineMin;
	iXlineMax = (iXlineMax - iXlineMin) / iXlineInc*iXlineInc + iXlineMin;

	m_ui.m_pInlineWidget->SetSliderName("Inline");
	m_ui.m_pInlineWidget->SetRangeAndPrecision(iInlineMin, iInlineMax, iInlineInc, 0);

	m_ui.m_pXlineWidget->SetSliderName("Crossline");
	m_ui.m_pXlineWidget->SetRangeAndPrecision(iXlineMin, iXlineMax, iXlineInc, 0);

	m_pPara->SetInlineInc(iInlineInc);
	m_pPara->SetXlineInc(iXlineInc);

}

bool CXPageCSSInversionTwo::validatePage()
{
	m_pPara->SetMinInlineNum(m_ui.m_pInlineWidget->GetMinValue());
	m_pPara->SetMaxInlineNum(m_ui.m_pInlineWidget->GetMaxValue());

	m_pPara->SetMinXlineNum(m_ui.m_pXlineWidget->GetMinValue());
	m_pPara->SetMaxXlineNum(m_ui.m_pXlineWidget->GetMaxValue());

	m_pPara->SetExportReflectivity(m_ui.m_pRadioReflectivity->isChecked());
	m_pPara->SetExportSeismic(m_ui.m_pRadioSeismic->isChecked());

	// CPU
	m_pPara->SetCPUNumber(m_ui.m_pCmbCPUNumber->currentText().toInt());

	return true;
}



