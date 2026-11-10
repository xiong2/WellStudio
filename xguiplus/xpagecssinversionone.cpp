#pragma warning (push,0)
#include "xpagecssinversionone.h"
#include "xparametercssinversion.h";
#include "xglobal.h"
#include "xseismicdatavolume.h"
//
#include <QMessageBox>

#include "xproject.h"
#include "xtree.h"
#include "xobjecttype.h"
#include <cassert>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QFileDialog>
#include <QFileInfo>
#include <qsettings.h>
#include <qdir.h>

#pragma warning(pop)

CXPageCSSInversionOne::CXPageCSSInversionOne(CXParameterCSSInversion* pPara, QWidget *parent)
	:m_pPara(pPara), QWizardPage(parent)
{
	m_ui.setupUi(this);

	assert(pPara);

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

	//	Connections
	connect(m_ui.m_pBtnSelectDV, SIGNAL(clicked()), this, SLOT(slotAddDV()));
	connect(m_ui.m_pBtnSelectZp, SIGNAL(clicked()), this, SLOT(slotAddZp()));
	connect(m_ui.m_pCombDataSource, SIGNAL(currentIndexChanged(int)), this, SLOT(slotDataSourceChanged(int)));
	connect(m_ui.m_pBtnSelectWavelet, SIGNAL(clicked()), this, SLOT(slotAddWaveletObject()));
	connect(m_ui.m_pBtnBrowse, SIGNAL(clicked()), this, SLOT(slotAddWaveletDataFile()));
}

CXPageCSSInversionOne::~CXPageCSSInversionOne()
{
}

void CXPageCSSInversionOne::slotAddDV()
{
	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetCurrentObject());
	if (!pDV || pDV->IsPrestack())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select a poststack seismic data volume.");
		return;
	}

	if (pDV->GetObjectID() == m_pPara->GetDVID())
		return;

	m_pPara->SetDVID(pDV->GetObjectID());
	m_pPara->SetDVName(pDV->GetObjectName());
	m_pPara->SetSamplingRate(pDV->GetSampleInterval());

	// dv
	m_ui.m_pLineEdtDV->setText(pDV->GetObjectName());
}

void CXPageCSSInversionOne::slotAddZp()
{
	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetCurrentObject());
	if (!pDV || pDV->IsPrestack())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select a poststack seismic data volume.");
		return;
	}

	if (pDV->GetObjectID() == m_pPara->GetImpedanceID())
		return;

	m_pPara->SetImpedanceID(pDV->GetObjectID());
	m_pPara->SetImpedanceName(pDV->GetObjectName());

	// dv
	m_ui.m_pLineEdtZp->setText(pDV->GetObjectName());
}

void CXPageCSSInversionOne::slotDataSourceChanged(int index)
{
	bool bDataFile = (index == 0);
	m_ui.m_pBtnSelectWavelet->setEnabled(!bDataFile);
	m_ui.m_pBtnBrowse->setEnabled(bDataFile);

	m_ui.m_pLineEdtWavelet->clear();
}

void CXPageCSSInversionOne::slotAddWaveletObject()
{
	CXObject* pCurrentObj = ::GetCurrentObject();
	if (!pCurrentObj || EXWavelet != pCurrentObj->GetObjectType())
		return;

	m_ui.m_pLineEdtWavelet->setText(pCurrentObj->GetObjectName());
	m_pPara->SetWaveletID(pCurrentObj->GetObjectID());
	m_pPara->SetWaveletFileName("");

}

void CXPageCSSInversionOne::slotAddWaveletDataFile()
{
	QSettings settings("XStudio", "Wavelet");
	QString wvfilepath = settings.value("recentpath").toString();
	if (wvfilepath.isEmpty())
		wvfilepath = ::GetProjectPath();

	QString strFileName = QFileDialog::getOpenFileName(this, "Select Wavelet Data File", wvfilepath);
	if (strFileName.isEmpty())
		return;

	settings.setValue("recentpath", QDir(strFileName).absolutePath());

	m_ui.m_pLineEdtWavelet->setText(strFileName);

	m_pPara->SetWaveletID(QUuid());
	m_pPara->SetWaveletFileName(strFileName);
}


bool CXPageCSSInversionOne::validatePage()
{
	if (!::GetObjectByID(m_pPara->GetDVID()))
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select one seismic data.");
		return false;
	}	

	if (!::GetObjectByID(m_pPara->GetImpedanceID()))
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select one seismic data.");
		return false;
	}

	// wavelet
	if (!::GetObjectByID(m_pPara->GetWaveletID()) && !QFile::exists(m_pPara->GetWaveletFileName()))
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select wavelet data.");
		return false;
	}

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

	return true;
}



