#include "xdlganisotropyforwarding.h"
#include "xparameteranisotropyforwarding.h"
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


//BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgAnisotropyForwarding)
//EAnisotrpicForwarding
//END_REGISTER_PROCESS_DIALOG_TO_FACTORY(CXDlgAnisotropyForwarding)


CXDlgAnisotropyForwarding::CXDlgAnisotropyForwarding(CXBaseParameter* pPara, CXObject* pParentObj, QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Seismic Anisotropy Forwarding");

	m_pDV = nullptr;

	m_pPara = dynamic_cast<CXParameterAnisotropyForwarding*>(pPara);
	assert(m_pPara);

	connect(m_ui.m_pPushBtnUpdate, &QPushButton::clicked, this, &CXDlgAnisotropyForwarding::slotUpdate);
	connect(m_ui.m_pLineEdtEnterAzi, &QLineEdit::editingFinished, this, &CXDlgAnisotropyForwarding::slotFinishAzi);
	connect(m_ui.m_pLineEdtEnterIncidence, &QLineEdit::editingFinished, this, &CXDlgAnisotropyForwarding::slotFinishIncidence);

	connect(m_ui.m_pBtnSelectVp, &QToolButton::clicked, this, &CXDlgAnisotropyForwarding::slotSelectDV);
	connect(m_ui.m_pBtnSelectVs, &QToolButton::clicked, this, &CXDlgAnisotropyForwarding::slotSelectDV);
	connect(m_ui.m_pBtnSelectRho, &QToolButton::clicked, this, &CXDlgAnisotropyForwarding::slotSelectDV);
	connect(m_ui.m_pBtnSelectEpsilon, &QToolButton::clicked, this, &CXDlgAnisotropyForwarding::slotSelectDV);
	connect(m_ui.m_pBtnSelectDelta, &QToolButton::clicked, this, &CXDlgAnisotropyForwarding::slotSelectDV);
	connect(m_ui.m_pBtnSelectGamma, &QToolButton::clicked, this, &CXDlgAnisotropyForwarding::slotSelectDV);
	connect(m_ui.m_pBtnSelectAzimuth, &QToolButton::clicked, this, &CXDlgAnisotropyForwarding::slotSelectDV);

	m_ui.m_pLineEdtScalingFactor->setValidator(new QDoubleValidator(this));

	_Init();
}

CXDlgAnisotropyForwarding::~CXDlgAnisotropyForwarding()
{
}

void CXDlgAnisotropyForwarding::_Init()
{
	// name
	m_ui.m_pOutputName->setText(m_pPara->GetOutputDVName());
}

void CXDlgAnisotropyForwarding::slotSelectDV()
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


void CXDlgAnisotropyForwarding::slotUpdate()
{
	slotFinishAzi();
	slotFinishIncidence();

	std::vector<double> vecAzimuth = m_pPara->GetVecAzimuth();
	std::vector<double> vecIncidence = m_pPara->GetVecIncidence();
	if (vecAzimuth.empty() || vecIncidence.empty())
	{
		QMessageBox::warning(this, ::g_strProductName, "Both azimuth and incidence angles are required before selecting wavelets.");
		return;
	}

	m_ui.m_pTable->clear();
	m_ui.m_pTable->setRowCount(vecAzimuth.size() *vecIncidence.size());

	// all wavelets
	QList<CXObject*> listObj = ::GetProject()->GetChildren(EXWaveletFolder);
	QList<CXObject*> listWavelet;
	if (!listObj.isEmpty())
	{
		listWavelet = listObj[0]->GetChildren(EXWavelet, true);
	}

	for (int i = 0; i < m_ui.m_pTable->rowCount(); ++i)
	{
		int iAZi = i / vecIncidence.size();
		int iIncidence = i % vecIncidence.size();

		// Azimuth
		QTableWidgetItem* pAziItem = new QTableWidgetItem;
		pAziItem->setText(QString::number(vecAzimuth[iAZi], 'f', 1));
		pAziItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ui.m_pTable->setItem(i, 0, pAziItem);

		// incidence
		QTableWidgetItem* pOffItem = new QTableWidgetItem;
		pOffItem->setText(QString::number(vecIncidence[iIncidence], 'f', 1));
		pOffItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ui.m_pTable->setItem(i, 1, pOffItem);

		// wavelet
		QComboBox* pComb = new QComboBox;

		// all available wavelets
		for (int ii = 0; ii < listWavelet.size(); ++ii)
		{
			pComb->addItem(listWavelet[ii]->GetObjectName(), listWavelet[ii]->GetObjectID());
		}
		if (!listWavelet.isEmpty())
			pComb->setCurrentIndex(0);
		m_ui.m_pTable->setCellWidget(i, 2, pComb);
	}

}
void CXDlgAnisotropyForwarding::slotFinishAzi()
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
void CXDlgAnisotropyForwarding::slotFinishIncidence()
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

void CXDlgAnisotropyForwarding::accept()
{
	// check name
	QString strDVName = m_ui.m_pOutputName->text();
	if (strDVName == "")
	{
		QMessageBox::warning(this, ::g_strProductName, "Please enter a valid data volume name.");
		return;
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
		return;
	}

	// check wavelets
	if (m_ui.m_pTable->rowCount() == 0)
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select wavelets.");
		return;
	}

	std::vector<QUuid> vecWaveletID;
	for (int i = 0; i < m_ui.m_pTable->rowCount(); ++i)
	{
		QComboBox* pComb = dynamic_cast<QComboBox*>(m_ui.m_pTable->cellWidget(i, 2));
		assert(pComb);

		vecWaveletID.push_back(pComb->currentData().toString());
	}
	m_pPara->SetVecWaveletID(vecWaveletID);

	m_pPara->SetWaveletScalingFactor(m_ui.m_pLineEdtScalingFactor->text().toDouble());


	QDialog::accept();
}


