#include "xpageseismicforwardingthree.h"
#include "xparameteranisotropyforwarding.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include <QMessageBox>
#include <qcombobox.h>
#include "xseismicdatavolume.h"

CXPageSeismicForwardingThree::CXPageSeismicForwardingThree(CXParameterAnisotropyForwarding* pPara, QWidget *parent)
	: QWizardPage(parent)
{
	m_ui.setupUi(this);

	m_pPara = pPara;

	// name
	m_ui.m_pOutputName->setText(m_pPara->GetOutputDVName());
}

CXPageSeismicForwardingThree::~CXPageSeismicForwardingThree()
{

}

void CXPageSeismicForwardingThree::initializePage()
{	
	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	double dSamplingStart, dSamplingEnd, dSamplingRate;

	CXSeismicDataVolume* pVpDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetVpDVID()));
	if (!pVpDV)
	{
		QMessageBox::warning(this, ::g_strProductName, "One of the selected data volume has been removed.");
		return;
	}

	pVpDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);
	pVpDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
	

	// set range
	m_ui.m_pInlineWidget->SetSliderName("Inline");
	m_ui.m_pInlineWidget->SetRangeAndPrecision(iInlineMin, iInlineMax, iInlineInc, 0);

	m_ui.m_pXlineWidget->SetSliderName("Crossline");
	m_ui.m_pXlineWidget->SetRangeAndPrecision(iXlineMin, iXlineMax, iXlineInc, 0);

	m_ui.m_pTimeWidget->SetSliderName("Time");
	m_ui.m_pTimeWidget->SetRangeAndPrecision(dSamplingStart, dSamplingEnd, dSamplingRate, 1);

	m_pPara->SetInlineInc(iInlineInc);
	m_pPara->SetXlineInc(iXlineInc);
	m_pPara->SetSamplingRate(dSamplingRate);
}



bool CXPageSeismicForwardingThree::validatePage()
{
	// check name
	QString strDVName = m_ui.m_pOutputName->text();
	if (strDVName == "")
	{
		QMessageBox::warning(this, ::g_strProductName, "Please enter a valid data volume name.");
		return false;
	}
	m_pPara->SetOutputDVName(strDVName);

	// range
	m_pPara->SetMinInlineNum(m_ui.m_pInlineWidget->GetMinValue());
	m_pPara->SetMaxInlineNum(m_ui.m_pInlineWidget->GetMaxValue());

	m_pPara->SetMinXlineNum(m_ui.m_pXlineWidget->GetMinValue());
	m_pPara->SetMaxXlineNum(m_ui.m_pXlineWidget->GetMaxValue());

	m_pPara->SetSamplingStart(m_ui.m_pTimeWidget->GetMinValue());
	m_pPara->SetSamplingEnd(m_ui.m_pTimeWidget->GetMaxValue());

	return true;
}


