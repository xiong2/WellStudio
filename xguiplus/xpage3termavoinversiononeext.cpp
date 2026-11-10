#pragma warning (push,0)
#include "xpage3termavoinversiononeext.h"
#include "xparameter3terminversion.h"
#include "xglobal.h"
#include "xseismicdatavolume.h"
//
#include <QMessageBox>

#include "xproject.h"
#include "xtree.h"
#include "xobjecttype.h"
#include <cassert>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QFileInfo>
#include <QVector>
#include <QMenu>
#include "xparametermanager.h"

#pragma warning(pop)

CXPage3TermAVOInversionOneExt::CXPage3TermAVOInversionOneExt(CXParameter3TermInversion* pPara, QWidget *parent)
	:m_pPara(pPara), QWizardPage(parent)
{
	m_ui.setupUi(this);

	assert(pPara);

	m_ui.m_pLineEdtAngle->setValidator(new QDoubleValidator(this));

	//	Connections
	connect(m_ui.m_pBtnSelectDV, SIGNAL(clicked()), this, SLOT(slotAddDV()));
	connect(m_ui.m_pCombDataSource, SIGNAL(currentIndexChanged(int)), this, SLOT(slotDataSourceChanged(int)));
	connect(m_ui.m_pBtnSelectWavelet, SIGNAL(clicked()), this, SLOT(slotAddWaveletObject()));
	connect(m_ui.m_pBtnBrowse, SIGNAL(clicked()), this, SLOT(slotAddWaveletDataFile()));

	connect(m_ui.m_pBtnAdd, SIGNAL(clicked()), this, SLOT(slotAddOneAngle()));

	connect(m_ui.m_pPushBtnLoadPara, SIGNAL(clicked()), this, SLOT(slotLoadParameter()));

	// delete one row of the table widget
	m_ui.m_pTable->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(m_ui.m_pTable, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(slotTableMenuRequest(const QPoint &)));
}

CXPage3TermAVOInversionOneExt::~CXPage3TermAVOInversionOneExt()
{
}

void CXPage3TermAVOInversionOneExt::slotTableMenuRequest(const QPoint & point)
{
	QTableWidgetItem* pItem = m_ui.m_pTable->itemAt(point);
	if (!pItem)
		return;

	int iRow = m_ui.m_pTable->row(pItem);

	QMenu menu;
	QAction* pAction = menu.addAction("Delete the angle", this, SLOT(slotDeleteCurrentAngle()));
	pAction->setData(QVariant(iRow));

	menu.exec(QCursor::pos());
}

void CXPage3TermAVOInversionOneExt::slotDeleteCurrentAngle()
{
	QAction* pAction = dynamic_cast<QAction*>(sender());
	if (!pAction)
		return;

	int iRow = pAction->data().toInt();
	if (iRow < 0)
		return;

	m_ui.m_pTable->removeRow(iRow);
}

void CXPage3TermAVOInversionOneExt::slotAddDV()
{
	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetCurrentObject());
	if (!pDV || pDV->IsPrestack())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select a poststack seismic data volume.");
		return;
	}

	// selected
	QVector<QUuid> vecDVID;
	QVector<float> vecAngle;
	QVector<QUuid> vecWaveletID;
	QStringList listFileName;
	_GetOneAngleInfo(vecDVID, vecAngle, vecWaveletID, listFileName);
	if (vecDVID.contains(pDV->GetObjectID()))
	{
		QMessageBox::warning(this, ::g_strProductName, "Please choose a different seismic data volume.");
		return;
	}

	if (!vecDVID.isEmpty())
	{
		CXSeismicDataVolume* pSelectedDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(vecDVID[0]));
		if (pSelectedDV && !pSelectedDV->IsSameSizeWith(pDV))
		{
			QMessageBox::warning(this, ::g_strProductName, "The size of the selected data volume has to be same with the previous one.");
			return;
		}
	}
	
	// dv
	m_ui.m_pLineEdtDV->setText(pDV->GetObjectName());
	m_uuidDVID = pDV->GetObjectID();

	// angle
	m_ui.m_pLineEdtAngle->setText(QString::number(0));	
}

void CXPage3TermAVOInversionOneExt::slotDataSourceChanged(int index)
{
	bool bDataFile = (index == 0);
	m_ui.m_pBtnSelectWavelet->setEnabled(!bDataFile);
	m_ui.m_pBtnBrowse->setEnabled(bDataFile);

	m_ui.m_pLineEdtWavelet->clear();
}

void CXPage3TermAVOInversionOneExt::slotAddWaveletObject()
{
	CXObject* pCurrentObj = ::GetCurrentObject();
	if (!pCurrentObj || EXWavelet != pCurrentObj->GetObjectType())
		return;

	m_ui.m_pLineEdtWavelet->setText(pCurrentObj->GetObjectName());
	m_uuidWaveletID = pCurrentObj->GetObjectID();
}

void CXPage3TermAVOInversionOneExt::slotAddWaveletDataFile()
{
	QString strFileName = QFileDialog::getOpenFileName(this, "Select Wavelet Data File", ::GetProjectPath());
	if (strFileName.isEmpty())
		return;

	m_ui.m_pLineEdtWavelet->setText(strFileName);

	m_uuidWaveletID = QUuid();

}

void CXPage3TermAVOInversionOneExt::initializePage()
{

	std::vector<QUuid> vecDVID = m_pPara->GetVecDVID();
	std::vector<float> vecAngle = m_pPara->GetVecAngleValue();
	QStringList listFileName = m_pPara->GetListWaveletFileName();
	std::vector<QUuid> vecWaveletObjID = m_pPara->GetVecWaveletID();

	QList<CXObject*> listDV;
	QList<float> listAngle;
	QStringList listWaveletFileName;
	for (int i = 0; i < vecDVID.size(); ++i)
	{
		CXObject* pObj = ::GetObjectByID(vecDVID[i]);
		if (!pObj)
			continue;

		listDV.append(pObj);
		listAngle.append(vecAngle[i]);
		listWaveletFileName.append(listFileName[i]);
	}


	// clear table
	m_ui.m_pTable->clearContents();
	m_ui.m_pTable->setRowCount(listDV.size());

	for (int i = 0; i < listDV.size(); ++i)
	{
		QTableWidgetItem* pPosItem = new QTableWidgetItem;
		pPosItem->setText(listDV[i]->GetObjectName());
		pPosItem->setData(Qt::UserRole, QVariant(listDV[i]->GetObjectID()));
		pPosItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ui.m_pTable->setItem(i, 0, pPosItem);

		// angle value
		QTableWidgetItem* pAngleItem = new QTableWidgetItem;
		pAngleItem->setText(QString::number(listAngle[i], 'f', 2));
		pAngleItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ui.m_pTable->setItem(i, 1, pAngleItem);

		// wavelet
		QTableWidgetItem* pWaveletItem = new QTableWidgetItem;
		pWaveletItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		CXObject* pObj = ::GetObjectByID(vecWaveletObjID[i]);
		if (pObj)
		{
			pWaveletItem->setText(pObj->GetObjectName());
			pWaveletItem->setData(Qt::UserRole, QVariant(vecWaveletObjID[i]));
		}
		else
		{
			pWaveletItem->setText(listWaveletFileName[i]);
		}
		
		m_ui.m_pTable->setItem(i, 2, pWaveletItem);

	}
}

void CXPage3TermAVOInversionOneExt::slotLoadParameter()
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


	CXBaseParameter* pNewPara = m_pPara;
	*pNewPara = *pPara;

	initializePage();
}


void CXPage3TermAVOInversionOneExt::slotAddOneAngle()
{
	// selected
	QVector<QUuid> vecDVID;
	QVector<float> vecAngle;
	QVector<QUuid> vecWaveletID;
	QStringList listFileName;
	_GetOneAngleInfo(vecDVID, vecAngle, vecWaveletID, listFileName);

	// dv
	if (vecDVID.contains(m_uuidDVID))
	{
		QMessageBox::warning(this, ::g_strProductName, "The seismic data volume has already been selected.");
		return;
	}	

	// angle
	float fAngle = m_ui.m_pLineEdtAngle->text().toFloat();
	if (vecAngle.contains(fAngle))
	{
		QMessageBox::warning(this, ::g_strProductName, "Please enter a different angle value.");
		return;
	}

	QUuid uuidWaveletID;
	if (::GetObjectByID(m_uuidWaveletID))
		uuidWaveletID = m_uuidWaveletID;
	else
		uuidWaveletID = QUuid();

	QString strFileName = m_ui.m_pLineEdtWavelet->text();
	QFileInfo fileInfo(strFileName);
	if (!fileInfo.isFile())
		strFileName = QString();


	if (uuidWaveletID.isNull() && strFileName.isEmpty())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please specify the wavelet data.");
		return;
	}

	// add the angle
	int nRow = m_ui.m_pTable->rowCount();
	m_ui.m_pTable->setRowCount(nRow + 1);

	// DV
	CXObject* pDV = ::GetObjectByID(m_uuidDVID);
	if (pDV)
	{
		QTableWidgetItem* pPosItem = new QTableWidgetItem;
		pPosItem->setText(pDV->GetObjectName());
		pPosItem->setData(Qt::UserRole, QVariant(m_uuidDVID));
		pPosItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_ui.m_pTable->setItem(nRow, 0, pPosItem);
	}

	// angle value
	QTableWidgetItem* pAngleItem = new QTableWidgetItem;
	pAngleItem->setText(QString::number(fAngle, 'f', 2));
	pAngleItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	m_ui.m_pTable->setItem(nRow, 1, pAngleItem);

	// wavelet
	QTableWidgetItem* pWaveletItem = new QTableWidgetItem;
	pWaveletItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	CXObject* pObj = ::GetObjectByID(uuidWaveletID);
	if (pObj)
	{
		pWaveletItem->setText(pObj->GetObjectName());
		pWaveletItem->setData(Qt::UserRole, QVariant(uuidWaveletID));
	}
	else
	{
		pWaveletItem->setText(strFileName);
	}
	m_ui.m_pTable->setItem(nRow, 2, pWaveletItem);

}

void CXPage3TermAVOInversionOneExt::_GetOneAngleInfo(QVector<QUuid>& vecDVID, QVector<float>& vecAngle, QVector<QUuid>& vecWaveletID, QStringList& listFileName)
{
	for (int i = 0; i < m_ui.m_pTable->rowCount(); ++i)
	{
		// DV ID
		QUuid uuidDV = m_ui.m_pTable->item(i, 0)->data(Qt::UserRole).toString();
		vecDVID.append(uuidDV);

		// angle
		float fAngle = m_ui.m_pTable->item(i, 1)->text().toFloat();
		vecAngle.append(fAngle);

		// ID
		QUuid uuid = m_ui.m_pTable->item(i, 2)->data(Qt::UserRole).toString();
		if (::GetObjectByID(uuid))
			vecWaveletID.append(uuid);
		else
			vecWaveletID.append(QUuid());

		// data file
		QString strDataFileName = m_ui.m_pTable->item(i, 2)->text();
		QFileInfo fileInfo(strDataFileName);
		if (fileInfo.isFile())
			listFileName.append(strDataFileName);
		else
			listFileName.append(QString());
	}

}

bool CXPage3TermAVOInversionOneExt::validatePage()
{
	if (m_ui.m_pTable->rowCount() < 1)
	{
		QMessageBox::warning(this, ::g_strProductName, "Please add at least one angle dataset.");
		return false;
	}

	// add info
	QVector<QUuid> vecDVID;
	QVector<float> vecAngle;
	QVector<QUuid> vecWaveletID;
	QStringList listFileName;
	_GetOneAngleInfo(vecDVID, vecAngle, vecWaveletID, listFileName);

	if (vecDVID.size() < 3)
	{
		QMessageBox::warning(this, ::g_strProductName, "Please add at least three angle dataset.");
		return false;
	}

	m_pPara->SetVecDVID(vecDVID.toStdVector());
	m_pPara->SetVecAngleValue(vecAngle.toStdVector());
	m_pPara->SetVecWaveletID(vecWaveletID.toStdVector());

	m_pPara->SetListWaveletFileName(listFileName);


	return true;
}



