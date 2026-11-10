#pragma warning (push,0)
#include "xpagefractureinversion.h"
#include "xparameter3terminversion.h"
#include "xglobal.h"
#include "xproject.h"
#include "xseismicdatavolume.h"
#include "xseismicirregularreader.h"
#include "xparametermanager.h"
//
#include <QMessageBox>

#include "xproject.h"
#include "xtree.h"
#include "xobjecttype.h"
#include <cassert>
#include <QVector>
#include <QMenu>
#include <qcombobox.h>
#include <qset.h>
#include <qmap.h>

#pragma warning(pop)

CXPageFractureInversion::CXPageFractureInversion(CXParameter3TermInversion* pPara, QWidget *parent)
	:m_pPara(pPara), QWizardPage(parent)
{
	m_ui.setupUi(this);
	assert(pPara);

	m_pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(m_pPara->GetPrestackDVID()));
	assert(m_pDV);

	// prevent the dv from deleting
	m_pDV->LockObject(QCoreApplication::instance()->thread());
	

	slotReset();

	// delete one row of the table widget
	m_ui.m_pTable->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(m_ui.m_pTable, &QTableWidget::customContextMenuRequested, this, &CXPageFractureInversion::slotTableMenuRequest);
	connect(m_ui.m_pPushBtnLoadPara, &QPushButton::clicked, this, &CXPageFractureInversion::slotLoadParameter);

	connect(m_ui.m_pBtnSelectEpsilon, &QToolButton::clicked, this, &CXPageFractureInversion::slotAddEpsilon);
	connect(m_ui.m_pBtnSelectDelta, &QToolButton::clicked, this, &CXPageFractureInversion::slotAddDelta);
	connect(m_ui.m_pBtnSelectGamma, &QToolButton::clicked, this, &CXPageFractureInversion::slotAddGamma);
	connect(m_ui.m_pBtnSelectAzimuth, &QToolButton::clicked, this, &CXPageFractureInversion::slotAddSymAzi);
	
}

CXPageFractureInversion::~CXPageFractureInversion()
{
	m_pDV->UnlockObject(QCoreApplication::instance()->thread());
}

void CXPageFractureInversion::initializePage()
{
	// epsilon
	CXObject* pEpsilon = ::GetObjectByID(m_pPara->GetEpsilonID());
	if (pEpsilon)
		m_ui.m_pLineEdtEpsilon->setText(pEpsilon->GetObjectName());
	else
	{
		m_pPara->SetEpsilonID(QUuid());
		m_ui.m_pLineEdtEpsilon->setText("");
	}

	// delta
	CXObject* pDelta = ::GetObjectByID(m_pPara->GetDeltaID());
	if (pDelta)
		m_ui.m_pLineEdtDelta->setText(pDelta->GetObjectName());
	else
	{
		m_pPara->SetDeltaID(QUuid());
		m_ui.m_pLineEdtDelta->setText("");
	}

	// gamma
	CXObject* pGamma = ::GetObjectByID(m_pPara->GetGammaID());
	if (pGamma)
		m_ui.m_pLineEdtGamma->setText(pGamma->GetObjectName());
	else
	{
		m_pPara->SetGammaID(QUuid());
		m_ui.m_pLineEdtGamma->setText("");
	}

	// symmetry azimuth
	CXObject* pSymAzi = ::GetObjectByID(m_pPara->GetSymAziID());
	if (pSymAzi)
		m_ui.m_pLineEdtAzimuth->setText(pSymAzi->GetObjectName());
	else
	{
		m_pPara->SetSymAziID(QUuid());
		m_ui.m_pLineEdtAzimuth->setText("");
	}
}

CXObject* CXPageFractureInversion::_GetCurrentDV(const QString& strMng)
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
		QMessageBox::warning(this, ::g_strProductName, "The sampling rate of the selected data volume has to be same with that of the prestack seismic volume.");
		return NULL;
	}

	QUuid uuidSurveyID = pCurrentDV->GetSurveyID();

	if (uuidSurveyID != pDV->GetSurveyID())
	{
		QMessageBox::warning(this, ::g_strProductName, "The selected data volume does not lie in the same survey as the prestack seismic volume.");
		return NULL;
	}


	return pCurrentDV;
}

void CXPageFractureInversion::slotAddEpsilon()
{
	CXObject* pObj = _GetCurrentDV("Please select epsilon data volume.");

	if (!pObj)
		return;

	m_ui.m_pLineEdtEpsilon->setText(pObj->GetObjectName());

	m_pPara->SetEpsilonID(pObj->GetObjectID());
}

void CXPageFractureInversion::slotAddDelta()
{
	CXObject* pObj = _GetCurrentDV("Please select delta data volume.");

	if (!pObj)
		return;

	m_ui.m_pLineEdtDelta->setText(pObj->GetObjectName());

	m_pPara->SetDeltaID(pObj->GetObjectID());
}


void CXPageFractureInversion::slotAddGamma()
{
	CXObject* pObj = _GetCurrentDV("Please select the gamma data volume.");

	if (!pObj)
		return;

	m_ui.m_pLineEdtGamma->setText(pObj->GetObjectName());

	m_pPara->SetGammaID(pObj->GetObjectID());
}

void CXPageFractureInversion::slotAddSymAzi()
{
	CXObject* pObj = _GetCurrentDV("Please select the symmetry axis data volume.");

	if (!pObj)
		return;

	m_ui.m_pLineEdtAzimuth->setText(pObj->GetObjectName());

	m_pPara->SetSymAziID(pObj->GetObjectID());
}

void CXPageFractureInversion::slotLoadParameter()
{
	CXObject* pObj = ::GetCurrentObject();
	if (!pObj)
		return;

	CXBaseParameter* pPara = CXParameterManager::Instance().GetParameterByID(pObj->GetObjectID());
	CXParameter3TermInversion* pOldPara = dynamic_cast<CXParameter3TermInversion*>(pPara);
	if (!pPara || pPara->GetObjectType() != m_pPara->GetObjectType())
	{
		QMessageBox::warning(this, ::g_strProductName, "The parameter of the selected item is not same type as the current one.");
		return;
	}

	//CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(pOldPara->GetPrestackDVID()));
	//if (!pDV)
	//{
	//	QMessageBox::warning(this, ::g_strProductName, "The old data volume has been deleted.");
	//	return;
	//}	

	//// first unlock the old DV
	//m_pDV->UnlockObject(QCoreApplication::instance()->thread());
	//m_pDV = pDV;
	//m_pDV->LockObject(QCoreApplication::instance()->thread());

	CXBaseParameter* pNewPara = m_pPara;
	*pNewPara = *pPara;

	m_pPara->SetPrestackDVID(m_pDV->GetObjectID());

	_SetWidgetFromPara();
}

void CXPageFractureInversion::slotTableMenuRequest(const QPoint & point)
{
	QList<QTableWidgetItem*> listItem = m_ui.m_pTable->selectedItems();
	if (listItem.isEmpty())
	{
		QMenu menu;

		QAction* pResetAction = menu.addAction("Reset", this, SLOT(slotReset()));

		menu.exec(QCursor::pos());
		
		return;
	}
	
	QList<int> listRow;
	for (auto item : listItem)
	{
		int iRow = m_ui.m_pTable->row(item);
		if (listRow.contains(iRow))
			continue;
		else
			listRow.append(iRow);
	}
	
	// convert to variant
	QList<QVariant> listV;
	for (auto iRow : listRow)
		listV.append(QVariant(iRow));

	QMenu menu;
	QAction* pAction = menu.addAction("Delete the selected rows", this, SLOT(slotDeleteSelected()));
	pAction->setData(QVariant(listV));	

	menu.exec(QCursor::pos());
}

void CXPageFractureInversion::slotDeleteSelected()
{
	auto pAction = dynamic_cast<QAction*>(sender());
	if (!pAction)
		return;

	auto listV = pAction->data().toList();
	if (listV.isEmpty())
		return;
	
	// convert to row index 
	QList<int> listRow;
	for (auto iV : listV)
	{
		listRow.append(iV.toInt());
	}
	std::sort(listRow.begin(), listRow.end(), [](int a, int b) {return a > b; });

	for (auto iRow : listRow)
	{
		m_ui.m_pTable->removeRow(iRow);
	}	
}

void CXPageFractureInversion::slotReset()
{
	if (!m_pDV->GetIrregularReader()->IsAzimuthVolume())
		return;

	short* pBuff = (short*)m_pDV->GetIrregularReader()->GetBuffer();

	int nTraceNum = pBuff[4];
	QMultiMap<short, short> mapAzi2Off;	
	for (int i = 0; i < nTraceNum; ++i)
	{
		mapAzi2Off.insert(pBuff[5 + 2 * i + 1], pBuff[5 + 2 * i]);
	}

	// get one wavelet ID
	QList<CXObject*> listObj = ::GetProject()->GetChildren(EXWaveletFolder);
	QUuid uuidWavelet;
	if (!listObj.isEmpty())
	{
		QList<CXObject*> listWavelet = listObj[0]->GetChildren(EXWavelet, true);
		if (!listWavelet.isEmpty())
			uuidWavelet = listWavelet[0]->GetObjectID();
	}

	// short and azimuth
	std::vector<float> vecOffset, vecAzimuth;
	std::vector<QUuid> vecWaveletID;
	QList<short> listAzi = mapAzi2Off.uniqueKeys();
	for (int i = 0; i < listAzi.size(); ++i)
	{
		QList<short> listOff = mapAzi2Off.values(listAzi[i]);
		std::sort(listOff.begin(), listOff.end());
		for (int j = 0; j < listOff.size(); ++j)
		{
			vecAzimuth.push_back(listAzi[i]);
			vecOffset.push_back(listOff[j]);
			vecWaveletID.push_back(uuidWavelet);
		}
	}


	// Set parameters
	m_pPara->SetVecAzimuth(vecAzimuth);
	m_pPara->SetVecAngleValue(vecOffset);
	m_pPara->SetVecWaveletID(vecWaveletID);

	_SetWidgetFromPara();
}

void CXPageFractureInversion::_SetWidgetFromPara()
{
	// load dvs
	initializePage();

	// load wavelets
	vector<float> vecAzimuth = m_pPara->GetVecAzimuth();
	vector<float> vecOffset = m_pPara->GetVecAngleValue();
	vector<QUuid> vecWaveletID = m_pPara->GetVecWaveletID();

	assert(vecAzimuth.size() == vecOffset.size());
	assert(vecAzimuth.size() == vecWaveletID.size());

	// all wavelets
	QList<CXObject*> listObj = ::GetProject()->GetChildren(EXWaveletFolder);
	QList<CXObject*> listWavelet;
	if (!listObj.isEmpty())
	{
		listWavelet = listObj[0]->GetChildren(EXWavelet, true);
	}

	// clear the table
	//m_ui.m_pTable->setRowCount(0);

	m_ui.m_pTable->setRowCount(vecAzimuth.size());
	for (int i = 0; i < vecAzimuth.size(); ++i)
	{
		// Azimuth
		QTableWidgetItem* pAziItem = new QTableWidgetItem;
		pAziItem->setText(QString::number(vecAzimuth[i]));
		pAziItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ui.m_pTable->setItem(i, 0, pAziItem);

		// Offset
		QTableWidgetItem* pOffItem = new QTableWidgetItem;
		pOffItem->setText(QString::number(vecOffset[i]));
		pOffItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ui.m_pTable->setItem(i, 1, pOffItem);

		// wavelet
		QComboBox* pComb = new QComboBox;

		// all available wavelets
		for (int ii = 0; ii < listWavelet.size(); ++ii)
		{
			pComb->addItem(listWavelet[ii]->GetObjectName(), listWavelet[ii]->GetObjectID());
		}

		// wavelet form parameter
		CXObject* pWavelet = ::GetObjectByID(vecWaveletID[i]);
		if (pWavelet)
		{
			int index = listWavelet.indexOf(pWavelet);
			if (index >= 0)
				pComb->setCurrentIndex(index);
		}
		m_ui.m_pTable->setCellWidget(i, 2, pComb);		
	}

}


bool CXPageFractureInversion::validatePage()
{
	vector<float> vecAzimuth, vecOffset;
	vector<QUuid> vecWaveletID;
	for (int i = 0; i < m_ui.m_pTable->rowCount(); ++i)
	{
		// azimuth
		short azimuth = m_ui.m_pTable->item(i, 0)->text().toShort();
		vecAzimuth.push_back(azimuth);

		// offset
		short offset = m_ui.m_pTable->item(i, 1)->text().toShort();
		vecOffset.push_back(offset);

		// wavelet
		QComboBox* pComb = dynamic_cast<QComboBox*>(m_ui.m_pTable->cellWidget(i, 2));
		assert(pComb);
		QUuid uuidWavelet = pComb->currentData().toString();
		vecWaveletID.push_back(uuidWavelet);
	}

	QSet<float> setAzi = QSet<float>::fromList(QList<float>::fromVector(QVector<float>::fromStdVector(vecAzimuth)));
	if (setAzi.size() < 4)
	{
		QMessageBox::warning(this, ::g_strProductName, "It requires more azimuth data.");
		return false;
	}

	m_pPara->SetVecAzimuth(vecAzimuth);
	m_pPara->SetVecAngleValue(vecOffset);
	m_pPara->SetVecWaveletID(vecWaveletID);


	return true;
}



