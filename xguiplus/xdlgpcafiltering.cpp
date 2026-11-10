#include "xdlgpcafiltering.h"
#include "xparameterpcafiltering.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include "xwell.h"
#include <QMessageBox>
#include "xprocessfactory.h"
#include "xseismicdatavolume.h"


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgPCAFiltering)
ESeismicPCAFiltering
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgPCAFiltering)

CXDlgPCAFiltering::CXDlgPCAFiltering(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
: QDialog(parent)
{
	m_ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Seismic PCA Filtering");

	m_pPara = dynamic_cast<CXParameterPCAFiltering*>(pPara);
	m_pDV = dynamic_cast<CXSeismicDataVolume*>(pParentObj);
	assert(m_pPara && m_pDV);

	_Init();
}

CXDlgPCAFiltering::~CXDlgPCAFiltering()
{
}

void CXDlgPCAFiltering::_Init()
{
	// sliders
	int iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc;
	m_pDV->GetUTM().GetLineNumRange(iInlineMin, iInlineMax, iInlineInc, iXlineMin, iXlineMax, iXlineInc);

	m_ui.m_pInlineWidget->SetSliderName("Inline");
	m_ui.m_pInlineWidget->SetRangeAndPrecision(iInlineMin, iInlineMax, iInlineInc, 0);

	m_ui.m_pXlineWidget->SetSliderName("Crossline");
	m_ui.m_pXlineWidget->SetRangeAndPrecision(iXlineMin, iXlineMax, iXlineInc, 0);

	m_pPara->SetInlineInc(iInlineInc);
	m_pPara->SetXlineInc(iXlineInc);
	m_pPara->SetSamplingRate(m_pDV->GetSampleInterval());

	// dx and dy
	for (int i = 1; i <= 49; i += 2)
	{
		m_ui.m_pComboxDx->addItem(QString::number(i));
		m_ui.m_pComboxDy->addItem(QString::number(i));
	}

	m_ui.m_pComboxDx->setCurrentIndex(1);
	m_ui.m_pComboxDy->setCurrentIndex(1);

}

void CXDlgPCAFiltering::accept()
{
	m_pPara->SetMinInlineNum(m_ui.m_pInlineWidget->GetMinValue());
	m_pPara->SetMaxInlineNum(m_ui.m_pInlineWidget->GetMaxValue());

	m_pPara->SetMinXlineNum(m_ui.m_pXlineWidget->GetMinValue());
	m_pPara->SetMaxXlineNum(m_ui.m_pXlineWidget->GetMaxValue());

	m_pPara->SetWinNI(m_ui.m_pComboxDy->currentText().toInt());
	m_pPara->SetWinNJ(m_ui.m_pComboxDx->currentText().toInt());
	

	QDialog::accept();
}

