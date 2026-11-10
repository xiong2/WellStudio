#pragma warning (push,0)
#include "xpage3termavoinversionone.h"
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

#pragma warning(pop)

CXPage3TermAVOInversionOne::CXPage3TermAVOInversionOne(CXParameter3TermInversion* pPara, QWidget *parent)
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

	// delete one row of the table widget
	m_ui.m_pTable->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(m_ui.m_pTable, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(slotTableMenuRequest(const QPoint &)));

	//	Add the current horizon
	slotAddDV();
}

CXPage3TermAVOInversionOne::~CXPage3TermAVOInversionOne()
{
}

void CXPage3TermAVOInversionOne::slotTableMenuRequest(const QPoint & point)
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

void CXPage3TermAVOInversionOne::slotDeleteCurrentAngle()
{
	QAction* pAction = dynamic_cast<QAction*>(sender());
	if (!pAction)
		return;

	int iRow = pAction->data().toInt();
	if (iRow < 0)
		return;

	m_ui.m_pTable->removeRow(iRow);
}

void CXPage3TermAVOInversionOne::slotAddDV()
{
	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetCurrentObject());
	if (!pDV || !pDV->IsPrestack())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select a prestack seismic data volume.");
		return;
	}	
	
	if (pDV->GetObjectID() == m_pPara->GetPrestackDVID())
		return;

	// set new DV
	m_nOffset = pDV->GetMaxFold();

	m_pPara->SetPrestackDVID(pDV->GetObjectID());
	m_pPara->SetPrestackDVName(pDV->GetObjectName());
	
	// dv
	m_ui.m_pLineEdtDV->setText(pDV->GetObjectName());

	// wavelet
	m_ui.m_pCmbPosition->clear();
	for (int i = 1; i <= m_nOffset; ++i)
		m_ui.m_pCmbPosition->addItem(QString::number(i));
	m_ui.m_pCmbPosition->setCurrentIndex(0);

	m_ui.m_pLineEdtAngle->setText(QString::number(0));

	m_ui.m_pCombDataSource->setCurrentIndex(0);
	m_ui.m_pBtnSelectWavelet->setEnabled(false);
	m_ui.m_pLineEdtWavelet->clear();

	// table
	m_ui.m_pTable->clear();
}

void CXPage3TermAVOInversionOne::slotDataSourceChanged(int index)
{
	bool bDataFile = (index == 0);
	m_ui.m_pBtnSelectWavelet->setEnabled(!bDataFile);
	m_ui.m_pBtnBrowse->setEnabled(bDataFile);

	m_ui.m_pLineEdtWavelet->clear();
}

void CXPage3TermAVOInversionOne::slotAddWaveletObject()
{
	CXObject* pCurrentObj = ::GetCurrentObject();
	if (!pCurrentObj || EXWavelet != pCurrentObj->GetObjectType())
		return;

	m_ui.m_pLineEdtWavelet->setText(pCurrentObj->GetObjectName());
	m_uuidWaveletID = pCurrentObj->GetObjectID();
}

void CXPage3TermAVOInversionOne::slotAddWaveletDataFile()
{
	QString strFileName = QFileDialog::getOpenFileName(this, "Select Wavelet Data File", ::GetProjectPath());
	if (strFileName.isEmpty())
		return;

	m_ui.m_pLineEdtWavelet->setText(strFileName);

	m_uuidWaveletID = QUuid();

}

void CXPage3TermAVOInversionOne::slotAddOneAngle()
{
	// selected
	QVector<int> vecPos;
	QVector<float> vecAngle;
	QVector<QUuid> vecWaveletID;
	QStringList listFileName;
	_GetOneAngleInfo(vecPos, vecAngle, vecWaveletID, listFileName);

	// current
	int iPos = m_ui.m_pCmbPosition->currentText().toInt();
	float fAngle = m_ui.m_pLineEdtAngle->text().toFloat();

	QUuid uuidWaveletID;
	if (::GetObjectByID(m_uuidWaveletID))
		uuidWaveletID = m_uuidWaveletID;
	else
		uuidWaveletID = QUuid();

	QString strFileName = m_ui.m_pLineEdtWavelet->text();
	QFileInfo fileInfo(strFileName);
	if (!fileInfo.isFile())
		strFileName = QString();

	if (vecPos.contains(iPos - 1))
	{
		QMessageBox::warning(this, ::g_strProductName, "The data for the selected angle has already existed.");
		return;
	}

	if (vecAngle.contains(fAngle))
	{
		QMessageBox::warning(this, ::g_strProductName, "Please enter a different angle value.");
		return;
	}

	if (uuidWaveletID.isNull() && strFileName.isEmpty())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please specify the wavelet data.");
		return;
	}

	// add the angle
	int nRow = m_ui.m_pTable->rowCount();
	m_ui.m_pTable->setRowCount(nRow + 1);

	// position
	QTableWidgetItem* pPosItem = new QTableWidgetItem;
	pPosItem->setText(QString::number(iPos));
	pPosItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	m_ui.m_pTable->setItem(nRow, 0, pPosItem);

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

void CXPage3TermAVOInversionOne::_GetOneAngleInfo(QVector<int>& vecPos, QVector<float>& vecAngle, QVector<QUuid>& vecWaveletID, QStringList& listFileName)
{
	for (int i = 0; i < m_ui.m_pTable->rowCount(); ++i)
	{
		// position
		int iPos = m_ui.m_pTable->item(i, 0)->text().toInt();
		vecPos.append(iPos - 1);

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

bool CXPage3TermAVOInversionOne::validatePage()
{
	if (!::GetObjectByID(m_pPara->GetPrestackDVID()))
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select one seismic data.");
		return false;
	}

	if (m_ui.m_pTable->rowCount() < 1)
	{
		QMessageBox::warning(this, ::g_strProductName, "Please add at least one angle dataset.");
		return false;
	}

	// add info
	QVector<int> vecPos;
	QVector<float> vecAngle;
	QVector<QUuid> vecWaveletID;
	QStringList listFileName;
	_GetOneAngleInfo(vecPos, vecAngle, vecWaveletID, listFileName);

	if (vecPos.size() < 3)
	{
		QMessageBox::warning(this, ::g_strProductName, "Please add at least three angle dataset.");
		return false;
	}

	m_pPara->SetVecAngleIndex(vecPos.toStdVector());
	m_pPara->SetVecAngleValue(vecAngle.toStdVector());
	m_pPara->SetVecWaveletID(vecWaveletID.toStdVector());

	m_pPara->SetListWaveletFileName(listFileName);
	

	return true;
}



