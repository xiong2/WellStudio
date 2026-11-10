#include "xdlgcssinversion.h"
#include "xparametercssinversion.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include "xwell.h"
#include <QMessageBox>
#include "xprocessfactory.h"
#include <QDoubleValidator>
#include "xcssinversion.h"
#include "xwaitcursor.h"


CXDlgCSSInversion::CXDlgCSSInversion(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
	setWindowTitle("Post-stack Constrained Sparse Spike Inversion");

	m_pPara = new CXParameterCSSInversion;

	m_ui.m_pLineEdtAlpha->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtMu->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtSigma->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtTol->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtBeta->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtWaveletFactor->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtMaxLoopNum->setValidator(new QIntValidator(1, 1000, this));

	m_ui.m_pLineEdtLowCut->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	m_ui.m_pLineEdtLowOverlap->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	m_ui.m_pLineEdtHighCut->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	m_ui.m_pLineEdtHighOverlap->setValidator(new QDoubleValidator(0, 10000, 0.1, this));

	m_nZ = 0;
}

CXDlgCSSInversion::~CXDlgCSSInversion()
{
	delete m_pPara;
}

void CXDlgCSSInversion::SetData(vector<float>& vecWavelet, vector<float> & vec2DSeismic, vector<float>& vecImp, double rate)
{
	m_nZ = vecImp.size();

	m_vecWavelet.resize(vecWavelet.size());
	m_vec2DSeismic.resize(vec2DSeismic.size());
	m_vecImpedance.resize(vecImp.size());

	m_pPara->SetSamplingRate(rate);

	std::copy(vecWavelet.begin(), vecWavelet.end(), m_vecWavelet.begin());
	std::copy(vec2DSeismic.begin(), vec2DSeismic.end(), m_vec2DSeismic.begin());
	std::copy(vecImp.begin(), vecImp.end(), m_vecImpedance.begin());
}



void CXDlgCSSInversion::_GetPara()
{
	m_pPara->SetAlpha(m_ui.m_pLineEdtAlpha->text().toFloat());
	m_pPara->SetBeta(m_ui.m_pLineEdtBeta->text().toFloat());
	m_pPara->SetMu(m_ui.m_pLineEdtMu->text().toFloat());
	m_pPara->SetSigma(m_ui.m_pLineEdtSigma->text().toFloat());
	m_pPara->SetWaveletFactor(m_ui.m_pLineEdtWaveletFactor->text().toFloat());
	m_pPara->SetTolerance(m_ui.m_pLineEdtTol->text().toFloat());
	m_pPara->SetMaxLoopNum(m_ui.m_pLineEdtMaxLoopNum->text().toInt());

	//	m_pPara->SetApplyFiltering(m_ui.m_pGroupBoxFiltering->isChecked());

	m_pPara->SetLowCut(m_ui.m_pLineEdtLowCut->text().toDouble());
	m_pPara->SetLowOverlap(m_ui.m_pLineEdtLowOverlap->text().toDouble());
	m_pPara->SetHighCut(m_ui.m_pLineEdtHighCut->text().toDouble());
	m_pPara->SetHighOverlap(m_ui.m_pLineEdtHighOverlap->text().toDouble());
}

void CXDlgCSSInversion::_Calc()
{
	CXWaitCursor waitcursor;

	if (m_vecWavelet.empty() || m_vec2DSeismic.empty() || m_vecImpedance.empty())
		return;

	int nJ = m_vec2DSeismic.size() / m_nZ;


	CXCSSInversion* pCalculation = new CXCSSInversion;
	pCalculation->InitInversionPara(m_pPara);	
	pCalculation->InitWaveletPara(m_vecWavelet.size(), m_vecWavelet);
	pCalculation->CreateBuffers(m_nZ, false, false);

	// in case there is invalid impedance values
	int zmin, zmax;
	_CalcMinMax(zmin, zmax);

	m_vecOutImped.clear();
	m_vecOutBP.clear();
	m_vecOutMerged.clear();
	for (int j = 0; j < nJ; ++j)
	{
		pCalculation->SetDataBuffer(zmin, zmax, &m_vecImpedance[0], &m_vec2DSeismic[0] + j*m_nZ);
		pCalculation->Calculate();

		float* pImped = pCalculation->GetImpedance();
		float* pBp = pCalculation->GetImpedanceBP();
		float* pMerged = pCalculation->GetImpedanceMerged();

		m_vecOutImped.insert(m_vecOutImped.end(), pImped, pImped + m_nZ);
		m_vecOutBP.insert(m_vecOutBP.end(), pBp, pBp + m_nZ);
		m_vecOutMerged.insert(m_vecOutMerged.end(), pMerged, pMerged + m_nZ);
	}

}

void CXDlgCSSInversion::_CalcMinMax(int& zMin, int& zMax)
{
	float fInvalid = g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);
	zMin = 0;
	zMax = m_nZ - 1;

	for (int k = 0; k < m_nZ; ++k)
	{
		if (qAbs(m_vecImpedance[k] - fInvalid) < fInvalidEPS || m_vecImpedance[k] <= 0.f)
		{
			continue;
		}
		else
		{
			zMin = k;
			break;
		}
	}

	for (int k = m_nZ - 1; k >= 0; --k)
	{
		if (qAbs(m_vecImpedance[k] - fInvalid) < fInvalidEPS || m_vecImpedance[k] <= 0.f)
		{
			continue;
		}
		else
		{
			zMax = k;
			break;
		}
	}
}

void CXDlgCSSInversion::accept()
{
	_GetPara();

	_Calc();

	QDialog::accept();
}

void CXDlgCSSInversion::GetImpedance(vector<float>& vec)
{

	vec.resize(m_vecOutImped.size());
	std::copy(m_vecOutImped.begin(), m_vecOutImped.end(), vec.begin());
}
void CXDlgCSSInversion::GetImpedanceBP(vector<float>& vec)
{
	vec.resize(m_vecOutBP.size());
	std::copy(m_vecOutBP.begin(), m_vecOutBP.end(), vec.begin());
}
void CXDlgCSSInversion::GetImpedanceMerged(vector<float>& vec)
{
	vec.resize(m_vecOutMerged.size());
	std::copy(m_vecOutMerged.begin(), m_vecOutMerged.end(), vec.begin());
}



