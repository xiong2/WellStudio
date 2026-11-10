#pragma warning (push,0)
#include "xpage3termavoinversionthree.h"
#include "xparameter3terminversion.h"
#include "xglobal.h"
#include "xseismicdatavolume.h"
//
#include <QMessageBox>

#include "xproject.h"
#include <cassert>
#include "xsysteminfo.h"
#include "x3dhorizon.h"

#pragma warning(pop)

CXPage3TermAVOInversionThree::CXPage3TermAVOInversionThree(CXParameter3TermInversion* pPara, QWidget *parent)
	:m_pPara(pPara), QWizardPage(parent)
{
	m_ui.setupUi(this);

	assert(pPara);

	_Init();
}

CXPage3TermAVOInversionThree::~CXPage3TermAVOInversionThree()
{
}
void CXPage3TermAVOInversionThree::_Init()
{
	connect(m_ui.m_pBtnTop, &QPushButton::clicked, this, &CXPage3TermAVOInversionThree::slotAddTop);
	connect(m_ui.m_pBtnBot, &QPushButton::clicked, this, &CXPage3TermAVOInversionThree::slotAddBot);
	connect(m_ui.m_pCheckBoxHorizon, &QCheckBox::clicked, this, &CXPage3TermAVOInversionThree::slotHorizon);

	_SetEnableConstraint(false);

	// cpu number
	int nCPUNum = CXSystemInfo::GetCPUNum();
	for (int i = 1; i <= nCPUNum; ++i)
	{
		m_ui.m_pCmbCPUNumber->addItem(QString::number(i));
	}
	m_ui.m_pCmbCPUNumber->setCurrentIndex(nCPUNum - 1);

	// for fracture analysis
	if (m_pPara->GetObjectType() == EAnisotropyInversion)
	{
		m_ui.m_pGroupBoxInversion->setVisible(false);
		m_ui.m_pGroupBoxPrior->setVisible(false);
		m_pPara->SetOutputInversion(true);
		m_pPara->SetOutputType(CXParameter3TermInversion::eZpVpVsRho);
	}
}

void CXPage3TermAVOInversionThree::_SetEnableConstraint(bool bEnabled)
{
	m_ui.m_pLabelTop->setEnabled(bEnabled);
	m_ui.m_pBtnTop->setEnabled(bEnabled);
	m_ui.m_pLineEdtTopHorizon->setEnabled(bEnabled);
	m_ui.m_pLabelBot->setEnabled(bEnabled);
	m_ui.m_pBtnBot->setEnabled(bEnabled);
	m_ui.m_pLineEdtBotHorizon->setEnabled(bEnabled);
}

void CXPage3TermAVOInversionThree::_InitByPara()
{
	// output type
	m_ui.m_pGroupBoxInversion->setChecked(m_pPara->GetOutputInversion());
	if (m_pPara->GetOutputInversion())
	{

		CXParameter3TermInversion::EOutputType eType = static_cast<CXParameter3TermInversion::EOutputType>(m_pPara->GetOutputType());

		if (eType == CXParameter3TermInversion::eZpZsRho)
			m_ui.m_pRadioZpZsRho->setChecked(true);
		else if (eType == CXParameter3TermInversion::eZpVpVsRho)
			m_ui.m_pRadioZpVpVsRho->setChecked(true);
		else
			m_ui.m_pRadioVpVsRho->setChecked(true);

		// R 
		m_ui.m_pRadioReflectivity->setChecked(m_pPara->GetExportReflectivity());

		// seismic
		m_ui.m_pRadioSeismic->setChecked(m_pPara->GetExportSeismic());
	}

	// prior
	m_ui.m_pGroupBoxPrior->setChecked(m_pPara->GetOutputPrior());
	if (m_pPara->GetOutputPrior())
	{
		if (m_pPara->GetAkiRichards())
		{
			m_ui.m_pRadioAki->setChecked(true);
		}
		else
		{
			m_ui.m_pRadioZoeppritz->setChecked(true);
		}
	}

	// horizon
	if (m_pPara->GetUseHorizon())
	{
		m_ui.m_pTimeWidget->setEnabled(false);

		m_ui.m_pCheckBoxHorizon->setChecked(true);
		_SetEnableConstraint(true);

		CXObject* pTop = ::GetObjectByID(m_pPara->GetTopHorizonID());
		if (pTop)
			m_ui.m_pLineEdtTopHorizon->setText(pTop->GetObjectName());

		CXObject* pBot = ::GetObjectByID(m_pPara->GetBotHorizonID());
		if (pBot)
			m_ui.m_pLineEdtBotHorizon->setText(pBot->GetObjectName());
	}

	// number of cpus
	int index = qBound(1, m_pPara->GetCPUNumber(), m_ui.m_pCmbCPUNumber->count()) - 1;
	m_ui.m_pCmbCPUNumber->setCurrentIndex(index);	
}



void CXPage3TermAVOInversionThree::slotAddTop()
{
	CX3DHorizon* pTopHor = dynamic_cast<CX3DHorizon*>(::GetCurrentObject());
	if (pTopHor)
	{
		CX3DHorizon* pBotHor = dynamic_cast<CX3DHorizon*>(::GetObjectByID(m_pPara->GetBotHorizonID()));
		if (pBotHor && pTopHor->GetZMax() > pBotHor->GetZMax())
		{
			QMessageBox::warning(this, ::g_strProductName, "The top horizon must lie above the bottom one.");
			return;
		}

		m_ui.m_pLineEdtTopHorizon->setText(pTopHor->GetObjectName());
		m_pPara->SetTopHorizonID(pTopHor->GetObjectID());
	}
	else
	{
		QMessageBox::warning(this, ::g_strProductName, "The selected node has to be 3-D horizon.");
		return;
	}
}
void CXPage3TermAVOInversionThree::slotAddBot()
{
	CX3DHorizon* pBotHor = dynamic_cast<CX3DHorizon*>(::GetCurrentObject());
	if (pBotHor)
	{
		CX3DHorizon* pTopHor = dynamic_cast<CX3DHorizon*>(::GetObjectByID(m_pPara->GetTopHorizonID()));
		if (pTopHor && pTopHor->GetZMax() > pBotHor->GetZMax())
		{
			QMessageBox::warning(this, ::g_strProductName, "The bottom horizon must lie below the top one.");
			return;
		}

		m_ui.m_pLineEdtBotHorizon->setText(pBotHor->GetObjectName());
		m_pPara->SetBotHorizonID(pBotHor->GetObjectID());
	}
	else
	{
		QMessageBox::warning(this, ::g_strProductName, "The selected node has to be 3-D horizon.");
		return;
	}
}
void CXPage3TermAVOInversionThree::slotHorizon()
{
	bool bUseHorizon = m_ui.m_pCheckBoxHorizon->isChecked();
	m_pPara->SetUseHorizon(bUseHorizon);

	m_ui.m_pTimeWidget->setEnabled(!bUseHorizon);
	_SetEnableConstraint(bUseHorizon);
}

void CXPage3TermAVOInversionThree::initializePage()
{
	// prestack
	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	double dSamplingStart, dSamplingEnd, dSamplingRate;
	CXSeismicDataVolume* pPreDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetPrestackDVID()));
	if (!pPreDV)
	{
		vector<QUuid> vecDVID = m_pPara->GetVecDVID();
		if (vecDVID.empty())
			return;

		CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(vecDVID[0]));
		if (pDV)
		{
			pDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);
			pDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
		}
	}
	else
	{
		pPreDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);
		pPreDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);
	}

	// Zp
	double dSamplingStart1, dSamplingEnd1, dSamplingRate1;
	CXSeismicDataVolume* pZpDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetZpID()));
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
	pZpDV->GetSamplingRange(dSamplingStart1, dSamplingEnd1, dSamplingRate1);
	if (dSamplingRate != dSamplingRate1)
	{
		QMessageBox::warning(this, ::g_strProductName, "The sampling rate of each selected data volume must be same.");
		return;
	}

	dSamplingStart = qMax(dSamplingStart, dSamplingStart1);
	dSamplingEnd = qMin(dSamplingEnd, dSamplingEnd1);

	// zs
	CXSeismicDataVolume* pZsDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetZsID()));
	if (!pZsDV)
		return;
		
	pZsDV->GetUTM().GetLineNumRange(iInlineMin1, iInlineMax1, iInlineInc1, iXlineMin1, iXlineMax1, iXlineInc1);
	iInlineMin = qMax(iInlineMin, iInlineMin1);
	iInlineMax = qMin(iInlineMax, iInlineMax1);
	iInlineInc = qMax(iInlineInc, iInlineInc1);

	iXlineMin = qMax(iXlineMin, iXlineMin1);
	iXlineMax = qMin(iXlineMax, iXlineMax1);
	iXlineInc = qMax(iXlineInc, iXlineInc1);

	pZsDV->GetSamplingRange(dSamplingStart1, dSamplingEnd1, dSamplingRate1);
	if (dSamplingRate != dSamplingRate1)
	{
		QMessageBox::warning(this, ::g_strProductName, "The sampling rate of each selected data volume must be same.");
		return;
	}

	dSamplingStart = qMax(dSamplingStart, dSamplingStart1);
	dSamplingEnd = qMin(dSamplingEnd, dSamplingEnd1);

	// rho
	CXSeismicDataVolume* pRhoDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetRhoID()));
	if (!pRhoDV)
		return;

	pRhoDV->GetUTM().GetLineNumRange(iInlineMin1, iInlineMax1, iInlineInc1, iXlineMin1, iXlineMax1, iXlineInc1);
	iInlineMin = qMax(iInlineMin, iInlineMin1);
	iInlineMax = qMin(iInlineMax, iInlineMax1);
	iInlineInc = qMax(iInlineInc, iInlineInc1);

	iXlineMin = qMax(iXlineMin, iXlineMin1);
	iXlineMax = qMin(iXlineMax, iXlineMax1);
	iXlineInc = qMax(iXlineInc, iXlineInc1);

	pRhoDV->GetSamplingRange(dSamplingStart1, dSamplingEnd1, dSamplingRate1);
	if (dSamplingRate != dSamplingRate1)
	{
		QMessageBox::warning(this, ::g_strProductName, "The sampling rate of each selected data volume must be same.");
		return;
	}

	dSamplingStart = qMax(dSamplingStart, dSamplingStart1);
	dSamplingEnd = qMin(dSamplingEnd, dSamplingEnd1);

	if (iInlineMin > iInlineMax || iXlineMin > iXlineMax || dSamplingStart > dSamplingEnd)
	{
		QMessageBox::warning(this, ::g_strProductName, "Cannot find the valid region among the input data volumes.");
		return;
	}

	// set range
	iInlineMax = (iInlineMax - iInlineMin) / iInlineInc*iInlineInc + iInlineMin;
	iXlineMax = (iXlineMax - iXlineMin) / iXlineInc*iXlineInc + iXlineMin;
	dSamplingEnd = static_cast<int>((dSamplingEnd - dSamplingStart) / dSamplingRate)*dSamplingRate + dSamplingStart;

	m_ui.m_pInlineWidget->SetSliderName("Inline");
	m_ui.m_pInlineWidget->SetRangeAndPrecision(iInlineMin, iInlineMax, iInlineInc, 0);

	m_ui.m_pXlineWidget->SetSliderName("Crossline");
	m_ui.m_pXlineWidget->SetRangeAndPrecision(iXlineMin, iXlineMax, iXlineInc, 0);

	m_ui.m_pTimeWidget->SetSliderName("Time");
	m_ui.m_pTimeWidget->SetRangeAndPrecision(dSamplingStart, dSamplingEnd, dSamplingRate, 1);

	m_pPara->SetInlineInc(iInlineInc);
	m_pPara->SetXlineInc(iXlineInc);
	m_pPara->SetSamplingRate(dSamplingRate);

	if (!m_pPara->GetUseHorizon())
	{
		m_ui.m_pTimeWidget->setEnabled(true);
		_SetEnableConstraint(false);
		m_ui.m_pCheckBoxHorizon->setChecked(false);

	}

	_InitByPara();

}

bool CXPage3TermAVOInversionThree::validatePage()
{
	m_pPara->SetMinInlineNum(m_ui.m_pInlineWidget->GetMinValue());
	m_pPara->SetMaxInlineNum(m_ui.m_pInlineWidget->GetMaxValue());

	m_pPara->SetMinXlineNum(m_ui.m_pXlineWidget->GetMinValue());
	m_pPara->SetMaxXlineNum(m_ui.m_pXlineWidget->GetMaxValue());

	if (!m_pPara->GetUseHorizon())
	{
		m_pPara->SetSamplingStart(m_ui.m_pTimeWidget->GetMinValue());
		m_pPara->SetSamplingEnd(m_ui.m_pTimeWidget->GetMaxValue());
	}
	else
	{
		CXSeismicDataVolume* pZpDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetZpID()));
		if (!pZpDV)
		{
			QMessageBox::warning(this, ::g_strProductName, "One of slected data volumes has been removed.");
			return false;
		}

		CX3DHorizon* pTop = dynamic_cast<CX3DHorizon*>(::GetObjectByID(m_pPara->GetTopHorizonID()));
		if (!pTop)
		{
			QMessageBox::warning(this, ::g_strProductName, "Please select the top horizon.");
			return false;
		}
		CX3DHorizon* pBot = dynamic_cast<CX3DHorizon*>(::GetObjectByID(m_pPara->GetBotHorizonID()));
		if (!pBot)
		{
			QMessageBox::warning(this, ::g_strProductName, "Please select the bottom horizon.");
			return false;
		}

		if (pZpDV->GetSurveyID() != pTop->GetSurveyID() || pZpDV->GetSurveyID() != pBot->GetSurveyID())
		{
			QMessageBox::warning(this, ::g_strProductName, "At least one of selected horizons does not lie in the same 3-D survey as seismic volumes.");
			return false;
		}			
	}

	// output option
	m_pPara->SetOutputInversion(m_ui.m_pGroupBoxInversion->isChecked());
	if (m_pPara->GetOutputInversion())
	{

		if (m_ui.m_pRadioZpZsRho->isChecked())
			m_pPara->SetOutputType(CXParameter3TermInversion::eZpZsRho);
		else if (m_ui.m_pRadioZpVpVsRho->isChecked())
			m_pPara->SetOutputType(CXParameter3TermInversion::eZpVpVsRho);
		else
			m_pPara->SetOutputType(CXParameter3TermInversion::eVpVsRho);

		m_pPara->SetExportReflectivity(m_ui.m_pRadioReflectivity->isChecked());
		m_pPara->SetExportSeismic(m_ui.m_pRadioSeismic->isChecked());
	}

	// prior
	m_pPara->SetOutputPrior(m_ui.m_pGroupBoxPrior->isChecked());
	if (m_pPara->GetOutputPrior())
	{
		m_pPara->SetAkiRichards(m_ui.m_pRadioAki->isChecked());
	}

	if (!m_pPara->GetOutputInversion() && !m_pPara->GetOutputPrior())
	{
		QMessageBox::warning(this, ::g_strProductName, "At least one output has to be selected.");
		return false;
	}

	// CPU
	m_pPara->SetCPUNumber(m_ui.m_pCmbCPUNumber->currentText().toInt());

	return true;
}



