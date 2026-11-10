#include "xpageinterpolation.h"

#include <cassert>

#include "xwelltops.h"
#include "xparametermake2dgrid.h"
#include "xglobal.h"

CXPageInterpolation::CXPageInterpolation(CXParameterMake2DGrid *pPara, CXObject *pObj, QWidget *parent)
	: QWizardPage(parent)
{
	m_ui.setupUi(this);

	assert(pPara && pObj);

	m_pPara = pPara;

	m_ui.m_cbbMethod->addItem(GetTr("Inverse distance"));
	m_ui.m_cbbMethod->addItem(GetTr("Simple Kriging"));

	m_ui.m_cbbType->addItem("Spherical");
	m_ui.m_cbbType->addItem("Exponential");
	m_ui.m_cbbType->addItem("Gaussian");

	connect(m_ui.m_cbbMethod, SIGNAL(currentIndexChanged(int)), SLOT(slotShowParameter(int)));
}

CXPageInterpolation::~CXPageInterpolation()
{

}

void CXPageInterpolation::initializePage()
{
	m_ui.m_lFunction->setVisible(false);
	m_ui.m_cbbType->setVisible(false);
	m_ui.m_gbKriging->setVisible(false);
	m_ui.m_gbIDP->setVisible(true);

	m_ui.m_leSearchRadius->setText("11973.07");
	m_ui.m_lePower->setText("2.000");
	m_ui.m_leIDPMaximumSampleNumber->setText("15");

	m_ui.m_leSill->setText("1.00");
	m_ui.m_leNugget->setText("0.0010");
	m_ui.m_leMajorRange->setText("11973.07");
	m_ui.m_leMinorRange->setText("11973.07");
	m_ui.m_leAzimuth->setText("0.00");
	m_ui.m_leKMaximumSampleNumber->setText("15");
}

bool CXPageInterpolation::validatePage()
{
	if (m_ui.m_cbbMethod->currentIndex() == m_pPara->eInverseDistance)
	{
		m_pPara->SetAlgorithmType(m_pPara->eInverseDistance);
		m_pPara->SetRadius(m_ui.m_leSearchRadius->text().toDouble());
		m_pPara->SetPower(m_ui.m_lePower->text().toDouble());
		m_pPara->SetMaxSampleNum(m_ui.m_leIDPMaximumSampleNumber->text().toDouble());
	}
	else if (m_ui.m_cbbMethod->currentIndex() == m_pPara->eKriging)
	{
		m_pPara->SetAlgorithmType(m_pPara->eKriging);
		m_pPara->SetVariogramType(m_ui.m_cbbType->currentIndex());
		m_pPara->SetSill(m_ui.m_leSill->text().toDouble());
		m_pPara->SetNugget(m_ui.m_leNugget->text().toDouble());
		m_pPara->SetMaxRange(m_ui.m_leMajorRange->text().toDouble());
		m_pPara->SetMinRange(m_ui.m_leMinorRange->text().toDouble());
		m_pPara->SetAzimuth(m_ui.m_leAzimuth->text().toDouble());
		m_pPara->SetMaxSampleNum(m_ui.m_leKMaximumSampleNumber->text().toDouble());
	}

	return true;
}

void CXPageInterpolation::slotShowParameter(int selectedIndex)
{
	if (selectedIndex == m_pPara->eInverseDistance)
	{
		m_ui.m_gbIDP->setVisible(true);
		m_ui.m_lFunction->setVisible(false);
		m_ui.m_cbbType->setVisible(false);
		m_ui.m_gbKriging->setVisible(false);
	}
	else if (selectedIndex == m_pPara->eKriging)
	{
		m_ui.m_gbIDP->setVisible(false);
		m_ui.m_lFunction->setVisible(true);
		m_ui.m_cbbType->setVisible(true);
		m_ui.m_gbKriging->setVisible(true);
	}
}