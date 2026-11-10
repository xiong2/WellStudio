#pragma warning (push,0)
#include "xpagefractureavoone.h"
#include "xparameterfractureavo.h"
#include "xglobal.h"
#include "xseismicdatavolume.h"
//
#include <QMessageBox>

#include "xproject.h"
#include "xtree.h"
#include "xobjecttype.h"
#include <cassert>
#include <QDoubleValidator>
#include <QVector>
#include <QMenu>

#pragma warning(pop)

CXPageFractureAVOOne::CXPageFractureAVOOne(CXParameterFractureAVO* pPara, QWidget *parent)
	:m_pPara(pPara), QWizardPage(parent)
{
	m_ui.setupUi(this);

	assert(pPara);

	m_ui.m_pLineEdtAzi->setValidator(new QDoubleValidator(this));

	//	Connections
	connect(m_ui.m_pBtnSelectDV, SIGNAL(clicked()), this, SLOT(slotAddDV()));

	connect(m_ui.m_pBtnAdd, SIGNAL(clicked()), this, SLOT(slotAddOneAngle()));

	// delete one row of the table widget
	m_ui.m_pTable->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(m_ui.m_pTable, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(slotTableMenuRequest(const QPoint &)));
}

CXPageFractureAVOOne::~CXPageFractureAVOOne()
{
}

void CXPageFractureAVOOne::slotTableMenuRequest(const QPoint & point)
{
	QTableWidgetItem* pItem = m_ui.m_pTable->itemAt(point);
	if (!pItem)
		return;

	int iRow = m_ui.m_pTable->row(pItem);

	QMenu menu;
	QAction* pAction = menu.addAction("Delete the azimuth", this, SLOT(slotDeleteCurrentAngle()));
	pAction->setData(QVariant(iRow));

	menu.exec(QCursor::pos());
}

void CXPageFractureAVOOne::slotDeleteCurrentAngle()
{
	QAction* pAction = dynamic_cast<QAction*>(sender());
	if (!pAction)
		return;

	int iRow = pAction->data().toInt();
	if (iRow < 0)
		return;

	m_ui.m_pTable->removeRow(iRow);
}

void CXPageFractureAVOOne::slotAddDV()
{
	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetCurrentObject());
	if (!pDV->IsPrestack())
	{
		QMessageBox::warning(this, ::g_strProductName, "Please select a prestack seismic data volume.");
		return;
	}

	// dv
	m_ui.m_pLineEdtDV->setText(pDV->GetObjectName());
	m_ui.m_pLineEdtDV->setProperty("DVOBJID", pDV->GetObjectID().toString());
}

void CXPageFractureAVOOne::slotAddOneAngle()
{
	// selected
	QVector<float> vecAzimuth;
	QVector<QUuid> vecDVID;
	_GetAzimuthInfo(vecAzimuth, vecDVID);

	// current
	float fAzimuth = m_ui.m_pLineEdtAzi->text().toFloat();

	QUuid uuidDVID = m_ui.m_pLineEdtDV->property("DVOBJID").toString();
	if (!::GetObjectByID(uuidDVID))
	{
		QMessageBox::warning(this, ::g_strProductName, "The data for the selected azimuth has already removed.");
		return;
	}

	if (vecAzimuth.contains(fAzimuth))
	{
		QMessageBox::warning(this, ::g_strProductName, "Please enter a different azimuth.");
		return;
	}

	if (vecDVID.contains(uuidDVID))
	{
		QMessageBox::warning(this, ::g_strProductName, "The data for the selected azimuth has already existed.");
		return;
	}

	// add the angle
	int nRow = m_ui.m_pTable->rowCount();
	m_ui.m_pTable->setRowCount(nRow + 1);
		
	// angle value
	QTableWidgetItem* pAngleItem = new QTableWidgetItem;
	pAngleItem->setText(QString::number(fAzimuth, 'f', 1));
	pAngleItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	m_ui.m_pTable->setItem(nRow, 0, pAngleItem);

	// data volume
	QTableWidgetItem* pDVItem = new QTableWidgetItem;
	pDVItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	CXObject* pDVObj = ::GetObjectByID(uuidDVID);

	pDVItem->setText(pDVObj->GetObjectName());
	pDVItem->setData(Qt::UserRole, QVariant(uuidDVID));

	m_ui.m_pTable->setItem(nRow, 1, pDVItem);

}

void CXPageFractureAVOOne::_GetAzimuthInfo(QVector<float>& vecAzimuth, QVector<QUuid>& vecDVID)
{
	for (int i = 0; i < m_ui.m_pTable->rowCount(); ++i)
	{
		// angle
		float fAzimuth = m_ui.m_pTable->item(i, 0)->text().toFloat();
		vecAzimuth.append(fAzimuth);

		// ID
		QUuid uuid = m_ui.m_pTable->item(i, 1)->data(Qt::UserRole).toString();
		vecDVID.append(uuid);
	}

}

bool CXPageFractureAVOOne::validatePage()
{
	// add info
	QVector<float> vecAzimuth;
	QVector<QUuid> vecDVID;
	_GetAzimuthInfo(vecAzimuth, vecDVID);

	if (vecAzimuth.size() < 3)
	{
		QMessageBox::warning(this, ::g_strProductName, "Please add at least three azimuth dataset.");
		return false;
	}

	m_pPara->SetVecAzimuth(vecAzimuth.toStdVector());
	m_pPara->SetVecDVID(vecDVID.toStdVector());
	

	return true;
}




