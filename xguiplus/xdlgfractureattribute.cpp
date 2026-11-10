#include "xdlgfractureattribute.h"
#include "xparameterfractureattribute.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include "xwell.h"
#include <QMessageBox>
#include "xprocessfactory.h"
#include <qset.h>
#include <qcombobox.h>
#include "xwavelet.h"
#include "xseismicdatavolume.h"
#include <qvalidator.h>
#include "xsysteminfo.h"


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgFractureAttribute)
EFractureAttribute
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgFractureAttribute)


CXDlgFractureAttribute::CXDlgFractureAttribute(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Calculate Fracture Attributes");

	m_pPara = dynamic_cast<CXParameterFractureAttribute*>(pPara);
	assert(m_pPara);

	m_pDV = nullptr;
	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(pParentObj);
	if (pDV)
	{
		_SetDV(pDV);
	}

	connect(m_ui.m_pBtnSelectDV, &QToolButton::clicked, this, &CXDlgFractureAttribute::slotSelectDV);

	//connect(m_ui.m_pBtnSelectVp, &QToolButton::clicked, this, &CXDlgFractureAttribute::slotSelectLFM);
	//connect(m_ui.m_pBtnSelectVs, &QToolButton::clicked, this, &CXDlgFractureAttribute::slotSelectLFM);
	//connect(m_ui.m_pBtnSelectEpsilon, &QToolButton::clicked, this, &CXDlgFractureAttribute::slotSelectLFM);
	//connect(m_ui.m_pBtnSelectDelta, &QToolButton::clicked, this, &CXDlgFractureAttribute::slotSelectLFM);
	//connect(m_ui.m_pBtnSelectGamma, &QToolButton::clicked, this, &CXDlgFractureAttribute::slotSelectLFM);
	//connect(m_ui.m_pBtnSelectAzimuth, &QToolButton::clicked, this, &CXDlgFractureAttribute::slotSelectLFM);

	//connect(m_ui.m_pGroupBoxFiltering, &QGroupBox::clicked, this, &CXDlgFractureAttribute::slotSelectFilter);

	m_ui.m_pLineEdtMinimumFold->setValidator(new QIntValidator(4, 1000));

	//m_ui.m_pLineEdtLowCut->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	//m_ui.m_pLineEdtLowOverlap->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	//m_ui.m_pLineEdtHighCut->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	//m_ui.m_pLineEdtHighOverlap->setValidator(new QDoubleValidator(0, 10000, 0.1, this));

	_Init();
}

CXDlgFractureAttribute::~CXDlgFractureAttribute()
{
	m_pDV->UnlockObject(QCoreApplication::instance()->thread());
}

void CXDlgFractureAttribute::_Init()
{
	// cpu number
	int nCPUNum = CXSystemInfo::GetCPUNum();
	for (int i = 1; i <= nCPUNum; ++i)
	{
		m_ui.m_pCmbCPUNumber->addItem(QString::number(i));
	}
	m_ui.m_pCmbCPUNumber->setCurrentIndex(nCPUNum - 1);
	m_pPara->SetCPUNumber(nCPUNum);

	//filtering
	//m_ui.m_pLineEdtLowCut->setText(QString::number(m_pPara->GetLowCut(), 'f', 1));
	//m_ui.m_pLineEdtLowOverlap->setText(QString::number(m_pPara->GetLowOverlap(), 'f', 1));
	//m_ui.m_pLineEdtHighCut->setText(QString::number(m_pPara->GetHighCut(), 'f', 1));
	//m_ui.m_pLineEdtHighOverlap->setText(QString::number(m_pPara->GetHighOverlap(), 'f', 1));
}

void CXDlgFractureAttribute::slotSelectFilter()
{
	//m_ui.m_pGroupBoxLFM->setChecked(m_ui.m_pGroupBoxFiltering->isChecked());
	//m_pPara->SetApplyFiltering(m_ui.m_pGroupBoxFiltering->isChecked());
}

void CXDlgFractureAttribute::slotSelectDV()
{
	CXSeismicDataVolume* pCurrentDV = dynamic_cast<CXSeismicDataVolume*>(::GetCurrentObject());
	if (!pCurrentDV->ContainsAzimuthOnly())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select a azimuthal seismic data volume.");
		return;
	}
	_SetDV(pCurrentDV);
}

void CXDlgFractureAttribute::slotSelectLFM()
{
	//if (!m_pDV)
	//{
	//	QMessageBox::warning(this, ::g_strProductName, "Please select a azimuthal seismic data volume first.");
	//	return;
	//}

	//CXSeismicDataVolume* pCurrentDV = dynamic_cast<CXSeismicDataVolume*>(::GetCurrentObject());
	//if (!pCurrentDV || pCurrentDV->IsPrestack())
	//{
	//	QMessageBox::warning(this, ::g_strProductName, "Please select a poststack seismic data volume.");
	//	return;
	//}

	//double dZStart, dZEnd, dZRate;
	//pCurrentDV->GetSamplingRange(dZStart, dZEnd, dZRate);

	//double dZStart1, dZEnd1, dZRate1;
	//m_pDV->GetSamplingRange(dZStart1, dZEnd1, dZRate1);

	//if (qAbs(dZStart1 - dZStart) > GetEPSofInvalidData(qMax(dZStart1, dZStart)) ||
	//	qAbs(dZEnd1 - dZEnd) > GetEPSofInvalidData(qMax(dZEnd1, dZEnd)) ||
	//	qAbs(dZRate1 - dZRate) > GetEPSofInvalidData(qMax(dZRate1, dZRate)))
	//{
	//	QMessageBox::warning(this, ::g_strProductName, "The selected data volumes must have the same dimension.");
	//	return;
	//}

	//CXSeismicUTMTool utmOld = m_pDV->GetUTM();
	//CXSeismicUTMTool utm = pCurrentDV->GetUTM();

	//if (!utm.Contains(&utmOld))
	//{
	//	QMessageBox::warning(this, ::g_strProductName, "The selected data volumes must have the same dimension.");
	//	return;
	//}
	//

	//QToolButton* pToolBtn = dynamic_cast<QToolButton*>(sender());

	//if (pToolBtn == m_ui.m_pBtnSelectVp)
	//{
	//	m_ui.m_pLineEdtVp->setText(pCurrentDV->GetObjectName());
	//	m_pPara->SetVpDVID(pCurrentDV->GetObjectID());
	//}
	//else if (pToolBtn == m_ui.m_pBtnSelectVs)
	//{
	//	m_ui.m_pLineEdtVs->setText(pCurrentDV->GetObjectName());
	//	m_pPara->SetVsDVID(pCurrentDV->GetObjectID());
	//}
	//else if (pToolBtn == m_ui.m_pBtnSelectEpsilon)
	//{
	//	m_ui.m_pLineEdtEpsilon->setText(pCurrentDV->GetObjectName());
	//	m_pPara->SetEpsilonDVID(pCurrentDV->GetObjectID());
	//}
	//else if (pToolBtn == m_ui.m_pBtnSelectDelta)
	//{
	//	m_ui.m_pLineEdtDelta->setText(pCurrentDV->GetObjectName());
	//	m_pPara->SetDeltaDVID(pCurrentDV->GetObjectID());
	//}
	//else if (pToolBtn == m_ui.m_pBtnSelectGamma)
	//{
	//	m_ui.m_pLineEdtGamma->setText(pCurrentDV->GetObjectName());
	//	m_pPara->SetGammaDVID(pCurrentDV->GetObjectID());
	//}
	//else if (pToolBtn == m_ui.m_pBtnSelectAzimuth)
	//{
	//	m_ui.m_pLineEdtAzimuth->setText(pCurrentDV->GetObjectName());
	//	m_pPara->SetAziSymDVID(pCurrentDV->GetObjectID());
	//}
}

void CXDlgFractureAttribute::_SetDV(CXSeismicDataVolume* pDV)
{
	if (m_pDV)
	{
		m_pDV->UnlockObject(QCoreApplication::instance()->thread());
	}
	m_pDV = pDV;
	m_pDV->LockObject(QCoreApplication::instance()->thread());

	m_ui.m_pLineEdtDV->setText(m_pDV->GetObjectName());
	m_pPara->SetAzimuthDVID(m_pDV->GetObjectID());
	m_pPara->SetAzimuthDVName(m_pDV->GetObjectName());

	_SetRange();
}

void CXDlgFractureAttribute::_SetRange()
{
	// prestack
	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	double dSamplingStart, dSamplingEnd, dSamplingRate;

	m_pDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);
	m_pDV->GetSamplingRange(dSamplingStart, dSamplingEnd, dSamplingRate);

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


void CXDlgFractureAttribute::accept()
{
	// range
	m_pPara->SetMinInlineNum(m_ui.m_pInlineWidget->GetMinValue());
	m_pPara->SetMaxInlineNum(m_ui.m_pInlineWidget->GetMaxValue());

	m_pPara->SetMinXlineNum(m_ui.m_pXlineWidget->GetMinValue());
	m_pPara->SetMaxXlineNum(m_ui.m_pXlineWidget->GetMaxValue());

	m_pPara->SetSamplingStart(m_ui.m_pTimeWidget->GetMinValue());
	m_pPara->SetSamplingEnd(m_ui.m_pTimeWidget->GetMaxValue());

	// minimum fold
	m_pPara->SetMinimumFold(m_ui.m_pLineEdtMinimumFold->text().toInt());

	// cpu number
	m_pPara->SetCPUNumber(m_ui.m_pCmbCPUNumber->currentText().toInt());

	if (m_pDV->GetMaxFold() < m_pPara->GetMinimumFold())
	{
		QMessageBox::warning(this, ::g_strProductName, "The maximum fold of the selected data volume should not be less than the input minimum fold.");
		return;
	}

	// filter
	//if (m_ui.m_pGroupBoxFiltering->isChecked())
	//{
	//	m_pPara->SetApplyFiltering(true);

	//	m_pPara->SetLowCut(m_ui.m_pLineEdtLowCut->text().toDouble());
	//	m_pPara->SetLowOverlap(m_ui.m_pLineEdtLowOverlap->text().toDouble());
	//	m_pPara->SetHighCut(m_ui.m_pLineEdtHighCut->text().toDouble());
	//	m_pPara->SetHighOverlap(m_ui.m_pLineEdtHighOverlap->text().toDouble());

	//	if (m_pPara->GetVpDVID().isNull() ||
	//		m_pPara->GetVsDVID().isNull() ||
	//		m_pPara->GetEpsilonDVID().isNull() ||
	//		m_pPara->GetDeltaDVID().isNull() ||
	//		m_pPara->GetGammaDVID().isNull() ||
	//		m_pPara->GetAziSymDVID().isNull())
	//	{
	//		QMessageBox::warning(this, ::g_strProductName, "Each of all seven data volume has to be selected.");
	//		return;
	//	}
	//}


	QDialog::accept();
}



