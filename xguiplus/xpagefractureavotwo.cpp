#pragma warning (push,0)
#include "xpagefractureavotwo.h"
#include "xparameterfractureavo.h"
#include "xglobal.h"
#include "xseismicdatavolume.h"
//
#include <QMessageBox>
#include <QIntValidator>

#include "xproject.h"
#include <cassert>
#include "xsysteminfo.h"
#include "xseismicdatavolume.h"
#include <cassert>
#include <algorithm>

#pragma warning(pop)

CXPageFractureAVOTwo::CXPageFractureAVOTwo(CXParameterFractureAVO* pPara, QWidget *parent)
	:m_pPara(pPara), QWizardPage(parent)
{
	m_ui.setupUi(this);

	assert(pPara);

	m_pPara->SetCPUNumber(CXSystemInfo::GetCPUNum());

	_Init();		

	connect(m_ui.m_pCombMethod, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &CXPageFractureAVOTwo::slotMethodChanged);
}

CXPageFractureAVOTwo::~CXPageFractureAVOTwo()
{
}

void CXPageFractureAVOTwo::slotMethodChanged(int index)
{
	if (index == 0)
	{
		m_ui.m_pLabelIncidence->setEnabled(false);
		m_ui.m_pCombBoxIncidence->setEnabled(false);
	}
	else
	{
		m_ui.m_pLabelIncidence->setEnabled(true);
		m_ui.m_pCombBoxIncidence->setEnabled(true);

		if (m_ui.m_pCombBoxIncidence->count() == 0)
		{
			CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetAzimuthDVID()));
			if (pDV)
			{
				CXSeismicUTMTool utm = pDV->GetUTM();
				int iInline, iXline;
				utm.IJToLine(utm.GetNI() / 2, utm.GetNJ() / 2, iInline, iXline);
				std::vector<int> vecAngle;
				pDV->GetOffset(iInline, iXline, vecAngle);
				if (vecAngle.empty())
					return;

				// remove repeated elements
				std::sort(vecAngle.begin(), vecAngle.end());
				auto last = std::unique(vecAngle.begin(), vecAngle.end());
				vecAngle.erase(last, vecAngle.end());

				for (int i = 0; i < vecAngle.size(); ++i)
					m_ui.m_pCombBoxIncidence->addItem(QString::number(vecAngle[i]));
				
				m_ui.m_pCombBoxIncidence->setCurrentText(QString::number(vecAngle.back()));		
				m_ui.m_pCombBoxIncidence->setCurrentText(QString::number(m_pPara->GetIncidenceAngle()));
			}

		}
	}
}

void CXPageFractureAVOTwo::_InitByPara()
{
	// output type
	int iMethod = m_pPara->GetMethodType();
	m_ui.m_pCombMethod->setCurrentIndex(iMethod);

	// dx and dy
	m_ui.m_pLineEdtDx->setText(QString::number(m_pPara->GetDx()));
	m_ui.m_pLineEdtDy->setText(QString::number(m_pPara->GetDy()));

	// minimum fold
	m_ui.m_pLineEdtMinimumFold->setText(QString::number(m_pPara->GetMinimumFold()));	

	// number of cpus
	int index = qBound(1, m_pPara->GetCPUNumber(), m_ui.m_pCmbCPUNumber->count()) - 1;
	m_ui.m_pCmbCPUNumber->setCurrentIndex(index);
}

void CXPageFractureAVOTwo::_Init()
{
	// validators
	m_ui.m_pLineEdtDx->setValidator(new QIntValidator(this));
	m_ui.m_pLineEdtDy->setValidator(new QIntValidator(this));
	m_ui.m_pLineEdtMinimumFold->setValidator(new QIntValidator(this));

	// cpu number
	int nCPUNum = CXSystemInfo::GetCPUNum();
	for (int i = 1; i <= nCPUNum; ++i)
	{
		m_ui.m_pCmbCPUNumber->addItem(QString::number(i));
	}
	m_ui.m_pCmbCPUNumber->setCurrentIndex(nCPUNum - 1);
}

void CXPageFractureAVOTwo::initializePage()
{
	// prestack
	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	double dSamplingStart, dSamplingEnd, dSamplingRate;
	vector<QUuid> vecDVID = m_pPara->GetVecDVID();
	if (!vecDVID.empty())
	{
		CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(vecDVID[0]));
		if (!pDV)
			return;

		pDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);
		pDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

		// valid range
		for (int i = 1; i < vecDVID.size(); ++i)
		{
			CXSeismicDataVolume* pObj = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(vecDVID[i]));

			int iInlineMin1, iInlineMax1, iInlineInc1, iXlineMin1, iXlineMax1, iXlineInc1;
			double dSamplingStart1, dSamplingEnd1, dSamplingRate1;
			pObj->GetUTM().GetLineNumRange(iInlineMin1, iInlineMax1, iInlineInc1, iXlineMin1, iXlineMax1, iXlineInc1);
			pDV->GetSamplingRange(dSamplingStart1, dSamplingEnd1, dSamplingRate1);

			iInlineMin = qMax(iInlineMin, iInlineMin1);
			iInlineMax = qMin(iInlineMax, iInlineMax1);
			iInlineInc = qMax(iInlineInc, iInlineInc1);

			iXlineMin = qMax(iXlineMin, iXlineMin1);
			iXlineMax = qMin(iXlineMax, iXlineMax1);
			iXlineInc = qMax(iXlineInc, iXlineInc1);

			if (dSamplingRate != dSamplingRate1)
			{
				QMessageBox::warning(this, ::g_strProductName, "The sampling rate of each selected data volume must be same.");
				return;
			}

			dSamplingStart = qMax(dSamplingStart, dSamplingStart1);
			dSamplingEnd = qMin(dSamplingEnd, dSamplingEnd1);
		}
	}
	else
	{
		CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetAzimuthDVID()));
		if (!pDV)
			return;
		
		pDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);
		pDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

	}


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

	_InitByPara();

	slotMethodChanged(0);

}

bool CXPageFractureAVOTwo::validatePage()
{
	m_pPara->SetMinInlineNum(m_ui.m_pInlineWidget->GetMinValue());
	m_pPara->SetMaxInlineNum(m_ui.m_pInlineWidget->GetMaxValue());

	m_pPara->SetMinXlineNum(m_ui.m_pXlineWidget->GetMinValue());
	m_pPara->SetMaxXlineNum(m_ui.m_pXlineWidget->GetMaxValue());

	m_pPara->SetSamplingStart(m_ui.m_pTimeWidget->GetMinValue());
	m_pPara->SetSamplingEnd(m_ui.m_pTimeWidget->GetMaxValue());

	// method
	m_pPara->SetMethodType(m_ui.m_pCombMethod->currentIndex());
	
	// dx and dy 
	m_pPara->SetDx(m_ui.m_pLineEdtDx->text().toInt());
	m_pPara->SetDy(m_ui.m_pLineEdtDy->text().toInt());

	// minimum fold
	m_pPara->SetMinimumFold(m_ui.m_pLineEdtMinimumFold->text().toInt());
	

	// CPU
	m_pPara->SetCPUNumber(m_ui.m_pCmbCPUNumber->currentText().toInt());

	// incidence
	if (m_ui.m_pCombMethod->currentIndex() == 1)
	{
		m_pPara->SetIncidenceAngle(m_ui.m_pCombBoxIncidence->currentText().toInt());
	}

	return true;
}



