#include "xpageseismicforwardingtwo.h"
#include "xparameteranisotropyforwarding.h"
#include <cassert>
#include "xglobal.h"
#include "xproject.h"
#include <QMessageBox>
#include <qset.h>
#include <qcombobox.h>
#include "xwavelet.h"
#include "xseismicdatavolume.h"

CXPageSeismicForwardingTwo::CXPageSeismicForwardingTwo(CXParameterAnisotropyForwarding* pPara, QWidget *parent)
	: QWizardPage(parent)
{
	m_ui.setupUi(this);

	m_pPara = pPara;

	m_ui.m_pLineEdtScalingFactor->setValidator(new QDoubleValidator(this));

}

CXPageSeismicForwardingTwo::~CXPageSeismicForwardingTwo()
{

}

void CXPageSeismicForwardingTwo::initializePage()
{
	std::vector<double> vecAzimuth = m_pPara->GetVecAzimuth();
	std::vector<double> vecIncidence = m_pPara->GetVecIncidence();
	if (vecAzimuth.empty() || vecIncidence.empty())
	{
		QMessageBox::warning(this, ::g_strProductName, "Both azimuth and incidence angles are required before selecting wavelets.");
		return;
	}
	
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



bool CXPageSeismicForwardingTwo::validatePage()
{
	// check wavelets
	if (m_ui.m_pTable->rowCount() == 0)
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select wavelets.");
		return false;
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

	return true;
}

