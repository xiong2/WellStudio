#pragma warning (push,0)
#include "xpage3termavoinversiontwo.h"
#include "xparameter3terminversion.h"
#include "xglobal.h"
#include "xseismicdatavolume.h"
//
#include <QMessageBox>

#include "xproject.h"
#include "xtree.h"
#include <cassert>
#include <QDoubleValidator>
#include <QIntValidator>
#include "xdlgavocssiadvanced.h"

#pragma warning(pop)

CXPage3TermAVOInversionTwo::CXPage3TermAVOInversionTwo(CXParameter3TermInversion* pPara, QWidget *parent)
	:m_pPara(pPara), QWizardPage(parent)
{
	m_ui.setupUi(this);

	assert(pPara);
	
	m_ui.m_pLineEdtTol->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtMaxLoopNum->setValidator(new QIntValidator(1, 1000, this));
	m_ui.m_pLineEdtGamma->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtLamda->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtBeta->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtSigma->setValidator(new QDoubleValidator(this));
	m_ui.m_pLineEdtAlpha->setValidator(new QDoubleValidator(this));

	m_ui.m_pLineEdtLowCut->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	m_ui.m_pLineEdtLowOverlap->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	m_ui.m_pLineEdtHighCut->setValidator(new QDoubleValidator(0, 10000, 0.1, this));
	m_ui.m_pLineEdtHighOverlap->setValidator(new QDoubleValidator(0, 10000, 0.1, this));

	if (m_pPara->GetObjectType() == EAVOInversion)
	{
		m_ui.m_pLabelRDistri->setHidden(true);
		m_ui.m_pLineEdtSigma->setHidden(true);
		m_ui.m_pLabelRWeight->setHidden(true);
		m_ui.m_pLineEdtAlpha->setHidden(true);
		m_ui.m_pBtnAdvanced->setEnabled(false);
	}


	//	Connections
	connect(m_ui.m_pBtnSelectZp, SIGNAL(clicked()), this, SLOT(slotAddZp()));
	connect(m_ui.m_pBtnSelectZs, SIGNAL(clicked()), this, SLOT(slotAddZs()));
	connect(m_ui.m_pBtnSelectRho, SIGNAL(clicked()), this, SLOT(slotAddRho()));

	connect(m_ui.m_pBtnAdvanced, SIGNAL(clicked()), this, SLOT(slotAdvanced()));
}

CXPage3TermAVOInversionTwo::~CXPage3TermAVOInversionTwo()
{
}
void CXPage3TermAVOInversionTwo::initializePage()
{
	// p impednace
	CXObject* pZp = ::GetObjectByID(m_pPara->GetZpID());
	if (pZp)
		m_ui.m_pLineEdtZp->setText(pZp->GetObjectName());
	else
	{
		m_pPara->SetZpID(QUuid()); 
		m_ui.m_pLineEdtZp->setText("");
	}

	// s impedance
	CXObject* pZs = ::GetObjectByID(m_pPara->GetZsID());
	if (pZp)
		m_ui.m_pLineEdtZs->setText(pZs->GetObjectName());
	else
	{
		m_pPara->SetZsID(QUuid());
		m_ui.m_pLineEdtZs->setText("");
	}

	// density
	CXObject* pRho = ::GetObjectByID(m_pPara->GetRhoID());
	if (pZp)
		m_ui.m_pLineEdtRho->setText(pRho->GetObjectName());
	else
	{
		m_pPara->SetRhoID(QUuid());
		m_ui.m_pLineEdtRho->setText("");
	}

	// inversion para
	m_ui.m_pLineEdtTol->setText(QString::number(m_pPara->GetTolerance(), 'g', 6));
	m_ui.m_pLineEdtMaxLoopNum->setText(QString::number(m_pPara->GetMaxLoopNum()));
	m_ui.m_pLineEdtGamma->setText(QString::number(m_pPara->GetGamma(), 'f', 2));

	m_ui.m_pLineEdtLamda->setText(QString::number(m_pPara->GetLambda(), 'g', 2));
	m_ui.m_pLineEdtBeta->setText(QString::number(m_pPara->GetBeta(), 'g', 2));
	m_ui.m_pLineEdtSigma->setText(QString::number(m_pPara->GetSigma(), 'g', 2));
	m_ui.m_pLineEdtAlpha->setText(QString::number(m_pPara->GetAlpha(), 'g', 2));

	//filtering
	m_ui.m_pLineEdtLowCut->setText(QString::number(m_pPara->GetLowCut(), 'f', 1));
	m_ui.m_pLineEdtLowOverlap->setText(QString::number(m_pPara->GetLowOverlap(), 'f', 1));
	m_ui.m_pLineEdtHighCut->setText(QString::number(m_pPara->GetHighCut(), 'f', 1));
	m_ui.m_pLineEdtHighOverlap->setText(QString::number(m_pPara->GetHighOverlap(), 'f', 1));
}

CXObject* CXPage3TermAVOInversionTwo::_GetCurrentDV(const QString& strMng)
{
	CXSeismicDataVolume* pCurrentDV = dynamic_cast<CXSeismicDataVolume*>(::GetCurrentObject());
	if (!pCurrentDV || pCurrentDV->IsPrestack())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select a poststack seismic data volume.");
		return NULL;
	}

	// prestack volume
	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetPrestackDVID()));
	if (!pDV)
	{
		vector<QUuid> vecDVID = m_pPara->GetVecDVID();
		if (vecDVID.empty())
			return NULL;

		pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(vecDVID[0]));
		if (!pDV)
			return NULL;
	}

	if (qAbs(pCurrentDV->GetSampleInterval() - pDV->GetSampleInterval()) > 0.001f)
	{
		QMessageBox::warning(this, ::g_strProductName, "The sampling rate of the selected data volume has to be same with that of the seismic volume.");
		return NULL;
	}

	QUuid uuidSurveyID = pCurrentDV->GetSurveyID();

	if (uuidSurveyID != pDV->GetSurveyID())
	{
		QMessageBox::warning(this, ::g_strProductName, "The selected data volume does not lie in the same survey as the seismic volume.");
		return NULL;
	}

	double dMin, dMax;
	pCurrentDV->GetDataRange(dMin, dMax);
	if (dMin < 0.)
	{
		QMessageBox::warning(this, ::g_strProductName, strMng);
		return NULL;
	}

	return pCurrentDV;
}

void CXPage3TermAVOInversionTwo::slotAddZp()
{
	CXObject* pObj = _GetCurrentDV("Please select P-Impedance data volume.");

	if (!pObj)
		return;

	m_ui.m_pLineEdtZp->setText(pObj->GetObjectName());

	m_pPara->SetZpID(pObj->GetObjectID());
}

void CXPage3TermAVOInversionTwo::slotAddZs()
{
	CXObject* pObj = _GetCurrentDV("Please select S-Impedance data volume.");

	if (!pObj)
		return;

	m_ui.m_pLineEdtZs->setText(pObj->GetObjectName());

	m_pPara->SetZsID(pObj->GetObjectID());
}


void CXPage3TermAVOInversionTwo::slotAddRho()
{
	CXObject* pObj = _GetCurrentDV("Please select the density data volume.");

	if (!pObj)
		return;

	m_ui.m_pLineEdtRho->setText(pObj->GetObjectName());

	m_pPara->SetRhoID(pObj->GetObjectID());
}



bool CXPage3TermAVOInversionTwo::validatePage()
{
	CXSeismicDataVolume* pZpDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetZpID()));
	CXSeismicDataVolume* pZsDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetZsID()));
	CXSeismicDataVolume* pRhoDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetRhoID()));

	if (!pZpDV)
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select P-Impedance data volume.");
		return false;
	}

	if (!pZsDV)
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select S-Impedance data volume.");
		return false;
	}

	if (!pRhoDV)
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select the density data volume.");
		return false;
	}

	if (!pZpDV->IsSameSizeWith(pZsDV) || !pZpDV->IsSameSizeWith(pRhoDV))
	{
		QMessageBox::warning(this, ::g_strProductName, "Three data volumes must have the same dimension.");
		return false;
	}
	
	m_pPara->SetTolerance(m_ui.m_pLineEdtTol->text().toFloat());
	m_pPara->SetMaxLoopNum(m_ui.m_pLineEdtMaxLoopNum->text().toInt());
	m_pPara->SetGamma(m_ui.m_pLineEdtGamma->text().toFloat());
	m_pPara->SetSamplingRate(pZpDV->GetSampleInterval());

	m_pPara->SetLambda(m_ui.m_pLineEdtLamda->text().toFloat());
	m_pPara->SetBeta(m_ui.m_pLineEdtBeta->text().toFloat());
	m_pPara->SetSigma(m_ui.m_pLineEdtSigma->text().toFloat());
	m_pPara->SetAlpha(m_ui.m_pLineEdtAlpha->text().toFloat());

	//filtering
//	m_pPara->SetApplyFiltering(m_ui.m_pGroupBoxFiltering->isChecked());

	m_pPara->SetLowCut(m_ui.m_pLineEdtLowCut->text().toDouble());
	m_pPara->SetLowOverlap(m_ui.m_pLineEdtLowOverlap->text().toDouble());
	m_pPara->SetHighCut(m_ui.m_pLineEdtHighCut->text().toDouble());
	m_pPara->SetHighOverlap(m_ui.m_pLineEdtHighOverlap->text().toDouble());


	return true;
}

void CXPage3TermAVOInversionTwo::slotAdvanced()
{
	CXDlgAVOCSSIAdvanced* pDlg = new CXDlgAVOCSSIAdvanced(m_pPara, NULL, this);
	pDlg->show();
}



