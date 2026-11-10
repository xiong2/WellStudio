#include "xdlgkriginginterpolation.h"
#include "xprocessfactory.h"

#include "xglobal.h"
#include "xparametermakerevinterpolation.h"

BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgKrigingInterpolation)
EMakePropertyModel
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgKrigingInterpolation)

CXDlgKrigingInterpolation::CXDlgKrigingInterpolation(CXBaseParameter *pPara,CXObject* pObj,QWidget *parent):CXBaseDialog(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
	m_ui.setupUi(this);
	m_pPara = dynamic_cast<CXParameterMakeRevInterpolation*>(pPara);
	InitDlg();
}
CXDlgKrigingInterpolation::~CXDlgKrigingInterpolation()
{


}
void CXDlgKrigingInterpolation::InitDlg()
{
	m_ui.m_gbIDP->setVisible(false);
	m_ui.m_cbKriging->addItem(GetTr("简单克里金插值法"));
	m_ui.m_cbKriging->addItem(GetTr("普通克里金插值法"));
	m_ui.m_cbKriging->addItem(GetTr("泛克里金插值法"));

	m_ui.m_cbbType->addItem("Spherical");
	m_ui.m_cbbType->addItem("Exponential");
	m_ui.m_cbbType->addItem("Gaussian");

	m_ui.m_leSill->setText("1.00");
	m_ui.m_leNugget->setText("0.0010");
	m_ui.m_leMajorRange->setText("11973.07");
	m_ui.m_leMinorRange->setText("11973.07");
	m_ui.m_leAzimuth->setText("0.00");
	m_ui.m_leKMaximumSampleNumber->setText("15");
	m_ui.m_lineEditAvalue->setText("1");
	m_ui.m_lineEditxValue->setText("0");
	m_ui.m_lineEditYvalue->setText("0");
	m_ui.m_lineEditzValue->setText("0");
	m_ui.m_gbTrendFunction->setVisible(false);

	connect(m_ui.m_cbKriging, SIGNAL(currentIndexChanged(int)), SLOT(slotShowParameter(int)));
}

void CXDlgKrigingInterpolation::slotShowParameter(int selectedIndex)
{
	m_ui.m_gbIDP->setVisible(false);
	m_ui.m_lFunction->setVisible(true);
	m_ui.m_cbbType->setVisible(true);
	m_ui.m_gbKriging->setVisible(true);
	if (selectedIndex == m_pPara->eGeneralKriging)
	{
		
		m_ui.m_gbTrendFunction->setVisible(true);
	}else
	{
		m_ui.m_gbTrendFunction->setVisible(false);
	}
}

void CXDlgKrigingInterpolation::OnOK()
{
	
	m_pPara->SetAlgorithmType(m_ui.m_cbKriging->currentIndex());
	m_pPara->SetVariogramType(m_ui.m_cbbType->currentIndex());
	m_pPara->SetSill(m_ui.m_leSill->text().toDouble());
	m_pPara->SetNugget(m_ui.m_leNugget->text().toDouble());
	m_pPara->SetMaxRange(m_ui.m_leMajorRange->text().toDouble());
	m_pPara->SetMinRange(m_ui.m_leMinorRange->text().toDouble());
	m_pPara->SetAzimuth(m_ui.m_leAzimuth->text().toDouble());
	m_pPara->SetMaxSampleNum(m_ui.m_leKMaximumSampleNumber->text().toDouble());
	m_pPara->SetA(m_ui.m_lineEditAvalue->text().toDouble());
	m_pPara->SetA(m_ui.m_lineEditxValue->text().toDouble());
	m_pPara->SetA(m_ui.m_lineEditYvalue->text().toDouble());
	m_pPara->SetA(m_ui.m_lineEditzValue->text().toDouble());


}