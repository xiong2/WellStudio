#include "xdlgseismicfiltering.h"
#include "xparameterseismicfiltering.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include "xwell.h"
#include <QMessageBox>
#include "xprocessfactory.h"
#include <QButtonGroup>
#include <QDoubleValidator>


BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgSeismicFiltering)
ESeismicFiltering
END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgSeismicFiltering)

CXDlgSeismicFiltering::CXDlgSeismicFiltering(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
: QDialog(parent)
{
	m_ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Seismic Filtering");

	m_pPara = dynamic_cast<CXParameterSeismicFiltering*>(pPara);
	assert(m_pPara);

	m_ui.m_pLineEdtLowCut->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	m_ui.m_pLineEdtLowOverlap->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	m_ui.m_pLineEdtHighCut->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	m_ui.m_pLineEdtHighOverlap->setValidator(new QDoubleValidator(0, 10000, 0.1, this));


	m_PBottonGroup = new QButtonGroup(this);
	m_PBottonGroup->addButton(m_ui.m_pRadioLowCut, CXParameterSeismicFiltering::eLowCut);
	m_PBottonGroup->addButton(m_ui.m_pRadioHighCut, CXParameterSeismicFiltering::eHighCut);
	m_PBottonGroup->addButton(m_ui.m_pRadioBandPass, CXParameterSeismicFiltering::eBandPass);
	m_PBottonGroup->button(m_pPara->GetFilterType())->setChecked(true);

	connect(m_PBottonGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotFilteringMethod(int)));
}

CXDlgSeismicFiltering::~CXDlgSeismicFiltering()
{
}

void CXDlgSeismicFiltering::slotFilteringMethod(int id)
{
	m_pPara->SetFilterType(id);

	if (id == CXParameterSeismicFiltering::eLowCut)
	{
		_SetWidget(true, false);
	}
	else if (id == CXParameterSeismicFiltering::eHighCut)
	{
		_SetWidget(false, true);
	}
	else
	{
		_SetWidget(true, true);
	}

}

void CXDlgSeismicFiltering::_SetWidget(bool bShowLow, bool bShowHigh)
{
	m_ui.m_pLabelLow->setVisible(bShowLow);
	m_ui.m_pLineEdtLowCut->setVisible(bShowLow);
	m_ui.m_pLabelLowOver->setVisible(bShowLow);
	m_ui.m_pLineEdtLowOverlap->setVisible(bShowLow);


	m_ui.m_pLabeHigh->setVisible(bShowHigh);
	m_ui.m_pLineEdtHighCut->setVisible(bShowHigh);
	m_ui.m_pLabelHighOver->setVisible(bShowHigh);
	m_ui.m_pLineEdtHighOverlap->setVisible(bShowHigh);

}

void CXDlgSeismicFiltering::accept()
{
	int iType = m_pPara->GetFilterType();

	double dLowCut = m_ui.m_pLineEdtLowCut->text().toDouble();
	double dLowOver = m_ui.m_pLineEdtLowOverlap->text().toDouble();
	double dHighCut = m_ui.m_pLineEdtHighCut->text().toDouble();
	double dHighOver = m_ui.m_pLineEdtHighOverlap->text().toDouble();

	if (iType == CXParameterSeismicFiltering::eLowCut)
	{
		m_pPara->SetLowCutFreq(dLowCut);
		m_pPara->SetLowCutOverlapped(dLowOver);
		m_pPara->SetHighCutFreq(0);
		m_pPara->SetHighCutOverlapped(0);

		_SetWidget(true, false);
	}
	else if (iType == CXParameterSeismicFiltering::eHighCut)
	{
		m_pPara->SetLowCutFreq(0);
		m_pPara->SetLowCutOverlapped(0);
		m_pPara->SetHighCutFreq(dHighCut);
		m_pPara->SetHighCutOverlapped(dHighOver);
	}
	else
	{
		m_pPara->SetLowCutFreq(dLowCut);
		m_pPara->SetLowCutOverlapped(dLowOver);
		m_pPara->SetHighCutFreq(dHighCut);
		m_pPara->SetHighCutOverlapped(dHighOver);
	}
		
	m_pPara->SetTreatZeroInvalid(m_ui.m_pChkBoxInvalid->isChecked());

	QDialog::accept();
}

