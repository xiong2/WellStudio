#include "xpageseismicforwardingone.h"
#include "xparameteranisotropyforwarding.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include <QMessageBox>
#include <qset.h>
#include <qcombobox.h>
#include "xseismicdatavolume.h"
#include "xparametermanager.h"

CXPageSeismicForwardingOne::CXPageSeismicForwardingOne(CXParameterAnisotropyForwarding* pPara, QWidget *parent)
	: QWizardPage(parent)
{
	m_ui.setupUi(this);
	
	m_pPara = pPara;
	m_pDV = nullptr;
	
	connect(m_ui.m_pLineEdtEnterAzi, &QLineEdit::editingFinished, this, &CXPageSeismicForwardingOne::slotFinishAzi);
	connect(m_ui.m_pLineEdtEnterIncidence, &QLineEdit::editingFinished, this, &CXPageSeismicForwardingOne::slotFinishIncidence);

	connect(m_ui.m_pBtnSelectVp, &QToolButton::clicked, this, &CXPageSeismicForwardingOne::slotSelectDV);
	connect(m_ui.m_pBtnSelectVs, &QToolButton::clicked, this, &CXPageSeismicForwardingOne::slotSelectDV);
	connect(m_ui.m_pBtnSelectRho, &QToolButton::clicked, this, &CXPageSeismicForwardingOne::slotSelectDV);
	connect(m_ui.m_pBtnSelectEpsilon, &QToolButton::clicked, this, &CXPageSeismicForwardingOne::slotSelectDV);
	connect(m_ui.m_pBtnSelectDelta, &QToolButton::clicked, this, &CXPageSeismicForwardingOne::slotSelectDV);
	connect(m_ui.m_pBtnSelectGamma, &QToolButton::clicked, this, &CXPageSeismicForwardingOne::slotSelectDV);
	connect(m_ui.m_pBtnSelectAzimuth, &QToolButton::clicked, this, &CXPageSeismicForwardingOne::slotSelectDV);	

	connect(m_ui.m_pPushBtnLoadPara, &QPushButton::clicked, this, &CXPageSeismicForwardingOne::slotLoadParameter);

}

CXPageSeismicForwardingOne::~CXPageSeismicForwardingOne()
{

}

void CXPageSeismicForwardingOne::initializePage()
{
	CXObject* pObj = ::GetObjectByID(m_pPara->GetVpDVID());
	if (pObj)
		m_ui.m_pLineEdtVp->setText(pObj->GetObjectName());

	pObj = ::GetObjectByID(m_pPara->GetVsDVID());
	if (pObj)
		m_ui.m_pLineEdtVs->setText(pObj->GetObjectName());

	pObj = ::GetObjectByID(m_pPara->GetRhoDVID());
	if (pObj)
		m_ui.m_pLineEdtRho->setText(pObj->GetObjectName());

	pObj = ::GetObjectByID(m_pPara->GetEpsilonDVID());
	if (pObj)
		m_ui.m_pLineEdtEpsilon->setText(pObj->GetObjectName());

	pObj = ::GetObjectByID(m_pPara->GetDeltaDVID());
	if (pObj)
		m_ui.m_pLineEdtDelta->setText(pObj->GetObjectName());

	pObj = ::GetObjectByID(m_pPara->GetGammaDVID());
	if (pObj)
		m_ui.m_pLineEdtGamma->setText(pObj->GetObjectName());

	pObj = ::GetObjectByID(m_pPara->GetAziSymDVID());
	if (pObj)
		m_ui.m_pLineEdtAzimuth->setText(pObj->GetObjectName());

	std::vector<double> vecAzi = m_pPara->GetVecAzimuth();
	if (!vecAzi.empty())
	{
		QString str;
		for (int i=0; i<vecAzi.size(); ++i)
		{	
			str += QString::number(vecAzi[i], 'f', 1);
			if (i != vecAzi.size() - 1)
			{
				str += ", ";
			}
		}
		m_ui.m_pLineEdtEnterAzi->setText(str);
	}

	std::vector<double> vecInc = m_pPara->GetVecIncidence();
	if (!vecInc.empty())
	{
		QString str;
		for (int i = 0; i<vecInc.size(); ++i)
		{
			str += QString::number(vecInc[i], 'f', 1);
			if (i != vecInc.size() - 1)
			{
				str += ", ";
			}
		}
		m_ui.m_pLineEdtEnterIncidence->setText(str);
	}

}

void CXPageSeismicForwardingOne::slotLoadParameter()
{
	CXObject* pObj = ::GetCurrentObject();
	if (!pObj)
		return;

	CXBaseParameter* pPara = CXParameterManager::Instance().GetParameterByID(pObj->GetObjectID());
	CXParameterAnisotropyForwarding* pOldPara = dynamic_cast<CXParameterAnisotropyForwarding*>(pPara);
	if (!pPara || pPara->GetObjectType() != m_pPara->GetObjectType())
	{
		QMessageBox::warning(this, ::g_strProductName, "The parameter of the selected item is not same type as the current one.");
		return;
	}

	CXBaseParameter* pNewPara = m_pPara;
	*pNewPara = *pPara;

	initializePage();
}

void CXPageSeismicForwardingOne::slotSelectDV()
{
	CXSeismicDataVolume* pCurrentDV = dynamic_cast<CXSeismicDataVolume*>(::GetCurrentObject());
	if (!pCurrentDV || pCurrentDV->IsPrestack())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select a poststack seismic data volume.");
		return;
	}
	if (m_pDV == nullptr)
		m_pDV = pCurrentDV;
	else
	{
		if (!pCurrentDV->IsSameSizeWith(m_pDV))
		{
			QMessageBox::warning(this, ::g_strProductName, "The selected data volumes must have the same dimension.");
			return;
		}
	}

	QToolButton* pToolBtn = dynamic_cast<QToolButton*>(sender());
	if (pToolBtn == m_ui.m_pBtnSelectVp)
	{
		m_ui.m_pLineEdtVp->setText(pCurrentDV->GetObjectName());
		m_pPara->SetVpDVID(pCurrentDV->GetObjectID());
	}
	else if (pToolBtn == m_ui.m_pBtnSelectVs)
	{
		m_ui.m_pLineEdtVs->setText(pCurrentDV->GetObjectName());
		m_pPara->SetVsDVID(pCurrentDV->GetObjectID());
	}
	else if (pToolBtn == m_ui.m_pBtnSelectRho)
	{
		m_ui.m_pLineEdtRho->setText(pCurrentDV->GetObjectName());
		m_pPara->SetRhoDVID(pCurrentDV->GetObjectID());
	}
	else if (pToolBtn == m_ui.m_pBtnSelectEpsilon)
	{
		m_ui.m_pLineEdtEpsilon->setText(pCurrentDV->GetObjectName());
		m_pPara->SetEpsilonDVID(pCurrentDV->GetObjectID());
	}
	else if (pToolBtn == m_ui.m_pBtnSelectDelta)
	{
		m_ui.m_pLineEdtDelta->setText(pCurrentDV->GetObjectName());
		m_pPara->SetDeltaDVID(pCurrentDV->GetObjectID());
	}
	else if (pToolBtn == m_ui.m_pBtnSelectGamma)
	{
		m_ui.m_pLineEdtGamma->setText(pCurrentDV->GetObjectName());
		m_pPara->SetGammaDVID(pCurrentDV->GetObjectID());
	}
	else if (pToolBtn == m_ui.m_pBtnSelectAzimuth)
	{
		m_ui.m_pLineEdtAzimuth->setText(pCurrentDV->GetObjectName());
		m_pPara->SetAziSymDVID(pCurrentDV->GetObjectID());
	}
}

void CXPageSeismicForwardingOne::slotFinishAzi()
{
	std::vector<double> vecValue;
	QStringList strList = m_ui.m_pLineEdtEnterAzi->text().split(',', QString::SkipEmptyParts, Qt::CaseInsensitive);
	if (strList.isEmpty())
	{
		QMessageBox::warning(this, ::g_strProductName, "There is at least one azimuth value entered.");
		m_ui.m_pLineEdtEnterAzi->undo();
		m_ui.m_pLineEdtEnterAzi->setFocus();
		return;
	}
	for (auto str : strList)
	{
		bool b;
		double num = str.toDouble(&b);
		if (!b || num < 0. || num > 360.)
		{
			QMessageBox::warning(this, ::g_strProductName, "The input azimuth values should be within the range of 0 and 360.");
			m_ui.m_pLineEdtEnterAzi->undo();
			m_ui.m_pLineEdtEnterAzi->setFocus();
			return;
		}
		vecValue.push_back(num);
	}

	m_pPara->SetVecAzimuth(vecValue);
}
void CXPageSeismicForwardingOne::slotFinishIncidence()
{
	std::vector<double> vecValue;
	QStringList strList = m_ui.m_pLineEdtEnterIncidence->text().split(',', QString::SkipEmptyParts, Qt::CaseInsensitive);
	if (strList.isEmpty())
	{
		QMessageBox::warning(this, ::g_strProductName, "There is at least one incidence angle entered.");
		m_ui.m_pLineEdtEnterIncidence->undo();
		m_ui.m_pLineEdtEnterIncidence->setFocus();
		return;
	}
	for (auto str : strList)
	{
		bool b;
		double num = str.toDouble(&b);
		if (!b || num < 0. || num > 90.)
		{
			QMessageBox::warning(this, ::g_strProductName, "The input incidence angles should be within the range of 0 and 90.");
			m_ui.m_pLineEdtEnterIncidence->undo();
			m_ui.m_pLineEdtEnterIncidence->setFocus();
			return;
		}
		vecValue.push_back(num);
	}

	m_pPara->SetVecIncidence(vecValue);

}

bool CXPageSeismicForwardingOne::validatePage()
{
	if (m_pPara->GetVecAzimuth().empty())
		slotFinishAzi();

	if (m_pPara->GetVecIncidence().empty())
		slotFinishIncidence();

	if (m_pPara->GetVecAzimuth().empty())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please enter azimuth angles.");
		return false;
	}

	if (m_pPara->GetVecIncidence().empty())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please enter incidence angles.");
		return false;
	}

	// check dv
	if (m_pPara->GetVpDVID().isNull() ||
		m_pPara->GetVsDVID().isNull() ||
		m_pPara->GetRhoDVID().isNull() ||
		m_pPara->GetEpsilonDVID().isNull() ||
		m_pPara->GetDeltaDVID().isNull() ||
		m_pPara->GetGammaDVID().isNull() ||
		m_pPara->GetAziSymDVID().isNull())
	{
		QMessageBox::warning(this, ::g_strProductName, "Each of all seven data volume has to be selected.");
		return false;
	}

	return true;
}
