#include "xfile3dsurface.h"
#include "xpagefile3dsurface.h"
#include <cassert>
#include "ximport3dsurfacemanager.h"
#include "xglobal.h"
#include <qmessagebox.h>
#include "x3dsurvey.h"
#include "xproject.h"
#include "xseismicutmtool.h"
#include "xfaultsticksfile.h"
#include <QDebug>
#include <qfileinfo.h>
#include "x3dhorizon.h"

CXPageFile3DSurface::CXPageFile3DSurface(CXASCIIFile *pASCIIFile, QWidget *parent)
	: QWizardPage(parent)
{
	m_ui.setupUi(this);

	m_bImportingFault = true;
	m_pDataFile = pASCIIFile;
	if (dynamic_cast<CXFile3DSurface*>(pASCIIFile))
		m_bImportingFault = false;

	m_pSelectedUTM = NULL;
	_InitUTM();
	_InsertSurfaceGeometry(EX3DSurface);

	connect(m_ui.m_pLineEdtHorizoName, SIGNAL(editingFinished()), this, SLOT(slotSurfaceNameChange()));	
}

CXPageFile3DSurface::~CXPageFile3DSurface()
{
	if (m_pSelectedUTM)
	{
		delete m_pSelectedUTM;
		m_pSelectedUTM = NULL;
	}
}

void CXPageFile3DSurface::_InsertSurfaceGeometry(EXObjectType eObjType)
{
	QList<CXObject*> listObj = ::GetProject()->GetChildren(eObjType, true);

	m_ui.m_pComboParent->clear();
	m_ui.m_pComboParent->addItem("NULL", QVariant());
	
	for (int i = 0; i<listObj.size(); ++i)
	{
		if (eObjType == EX3DHorizon)
		{
			CX3DHorizon* pHorizon = dynamic_cast<CX3DHorizon*>(listObj[i]);
			if (pHorizon && pHorizon->GetSurveyID() == m_uuidSurvey)
			{ 
				m_ui.m_pComboParent->addItem(listObj[i]->GetObjectName(), QVariant(listObj[i]->GetObjectID()));
			}
		}
		else
		{
			//m_ui.m_pComboParent->addItem(listObj[i]->GetObjectName(), QVariant(listObj[i]->GetObjectID()));
		}
	}
}

void CXPageFile3DSurface::_UpdateWidet()
{
	if (m_bImportingFault)
	{
		m_ui.m_pTable->setVisible(false);
		m_ui.label_6->setVisible(false);
		m_ui.line_2->setVisible(false);
		m_ui.label_8->setVisible(false);
		m_ui.m_pLineEdtHorizoName->setVisible(false);

		return;
	}

	CXFile3DSurface *pSurfaceFile = dynamic_cast<CXFile3DSurface*>(m_pDataFile);
	if (!pSurfaceFile)
		return;

	QStringList listHorizonName = pSurfaceFile->GetImSurManager()->GetHorizonListName();
	if (listHorizonName.isEmpty()) return;

	bool bInline, bXline, bX, bY, bI, bJ;
	pSurfaceFile->GetImSurManager()->GetDataFlag(bInline, bXline, bX, bY, bI, bJ);
	if (bInline && bXline && bX && bY)
	{
		//	That the data are enough to create new survey!
		m_ui.m_pComboUTM->addItem("Create New", QVariant());
	}

	// Horizon name
	m_ui.m_pLineEdtHorizoName->setText(listHorizonName.at(0));

	// Data dimension:
	m_ui.m_pTable->setRowCount(3);
	m_ui.m_pTable->setColumnCount(3);

	QStringList listHeader;
	listHeader<<"  X  "<<"  Y  "<<"  Z  ";
	m_ui.m_pTable->setVerticalHeaderLabels (listHeader);

	listHeader.clear();
	listHeader<<"Min"<<"Max"<<"Delta";
	m_ui.m_pTable->setHorizontalHeaderLabels (listHeader);

	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	pSurfaceFile->GetImSurManager()->GetXYZMinMax(0, dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
	QString strInvalid = "";
	if (dXMin == 0.0 && dXMax == 0.0 && dYMin ==0 && dYMax == 0)
		strInvalid = "N/A";
	QString strValue;

	// X
	m_ui.m_pTable->clearContents();
	strValue = (strInvalid == "" ? QString::number(dXMin, 'f', 2) : strInvalid);
	QTableWidgetItem *pTableItem = m_ui.m_pTable->item(0,0 ) ? m_ui.m_pTable->item(0,0 ) :  new QTableWidgetItem(strValue);
	pTableItem->setFlags(Qt::ItemIsEditable);
	m_ui.m_pTable->setItem(0,0,pTableItem);

	strValue = (strInvalid == "" ? QString::number(dXMax, 'f', 2) : strInvalid);
	pTableItem = m_ui.m_pTable->item(0,1 ) ? m_ui.m_pTable->item(0,1 ) : new QTableWidgetItem(strValue);
	pTableItem->setFlags(Qt::ItemIsEditable);
	m_ui.m_pTable->setItem(0,1,pTableItem);

	strValue = (strInvalid == "" ? QString::number(dXMax-dXMin, 'f', 2) : strInvalid);
	pTableItem = m_ui.m_pTable->item(0,2 ) ? m_ui.m_pTable->item(0,2 ) : new QTableWidgetItem(strValue);
	pTableItem->setFlags(Qt::ItemIsEditable);
	m_ui.m_pTable->setItem(0,2,pTableItem); 

	// Y
	strValue = (strInvalid == "" ? QString::number(dYMin, 'f', 2) : strInvalid);
	pTableItem = m_ui.m_pTable->item(1,0 ) ? m_ui.m_pTable->item(1,0 ) : new QTableWidgetItem(strValue);
	pTableItem->setFlags(Qt::ItemIsEditable);
	m_ui.m_pTable->setItem(1,0,pTableItem);  

	strValue = (strInvalid == "" ? QString::number(dYMax, 'f', 2) : strInvalid);
	pTableItem = m_ui.m_pTable->item(1,1 ) ? m_ui.m_pTable->item(1,1 ) : new QTableWidgetItem(strValue);
	pTableItem->setFlags(Qt::ItemIsEditable);
	m_ui.m_pTable->setItem(1,1,pTableItem);

	strValue = (strInvalid == "" ? QString::number(dYMax-dYMin, 'f', 2) : strInvalid);
	pTableItem = m_ui.m_pTable->item(1,2 ) ? m_ui.m_pTable->item(1,2 ) : new QTableWidgetItem(strValue);
	pTableItem->setFlags(Qt::ItemIsEditable);
	m_ui.m_pTable->setItem(1,2,pTableItem);		

	//Z		
	pTableItem = m_ui.m_pTable->item(2,0 ) ? m_ui.m_pTable->item(2,0 ) : new QTableWidgetItem(QString::number(dZMin, 'f', 4));
	pTableItem->setFlags(Qt::ItemIsEditable);
	m_ui.m_pTable->setItem(2,0,pTableItem);	

	pTableItem = m_ui.m_pTable->item(2,1 ) ? m_ui.m_pTable->item(2,1 ) : new QTableWidgetItem(QString::number(dZMax, 'f', 4));
	pTableItem->setFlags(Qt::ItemIsEditable);
	m_ui.m_pTable->setItem(2,1,pTableItem);

	pTableItem = m_ui.m_pTable->item(2,2 ) ? m_ui.m_pTable->item(2,2 ) : new QTableWidgetItem(QString::number(dZMax-dZMin, 'f', 4));
	pTableItem->setFlags(Qt::ItemIsEditable);
	m_ui.m_pTable->setItem(2,2,pTableItem);  	
}

void CXPageFile3DSurface::_InitUTM()
{	
	// UTM
	m_ui.m_pComboUTM->clear();

	if (!m_bImportingFault)
		m_ui.m_pComboUTM->addItem("NULL", QVariant());

	QList<CXObject*> listObj = ::GetProject()->GetChildren(EX3DSurvey, true);
	for (int i=0; i<listObj.size(); ++i)
	{
		CX3DSurvey* p3DSurvey = dynamic_cast<CX3DSurvey*>(listObj.at(i));
		if (!p3DSurvey)
			continue;

		m_ui.m_pComboUTM->addItem(p3DSurvey->GetObjectName(), QVariant(p3DSurvey->GetObjectID()));
	}

	slotUtmChanged(0);
	m_ui.m_pComboUTM->setCurrentIndex(0);
	connect(m_ui.m_pComboUTM, SIGNAL(currentIndexChanged(int)), this, SLOT(slotUtmChanged(int)));
}

void CXPageFile3DSurface::slotUtmChanged(int index)
{
	if (m_pSelectedUTM)
	{
		delete m_pSelectedUTM;
		m_pSelectedUTM = NULL;
	}

	if (m_ui.m_pComboUTM->currentText() == "Create New")
	{
		m_pSelectedUTM = new CXSeismicUTMTool;
		return;
	}

	QUuid uuidSurvey = m_ui.m_pComboUTM->itemData(index).toString();
	CX3DSurvey* p3DSurvey = dynamic_cast<CX3DSurvey*>(::GetObjectByID(uuidSurvey));
	if (p3DSurvey)
	{
		m_pSelectedUTM = new CXSeismicUTMTool(p3DSurvey->GetUTM());
		m_uuidSurvey = p3DSurvey->GetObjectID();

		_InsertSurfaceGeometry(EX3DHorizon);
	}
	else
	{
		_InsertSurfaceGeometry(EX3DSurface);
	}
}

void CXPageFile3DSurface::initializePage()
{
	// Set the file name
	QString strFileName = m_pDataFile->GetFileName();
	strFileName=strFileName.replace("\\\\","\\");
	strFileName=strFileName.replace("//","/");
	m_ui.m_pLineEditFileName->setText(strFileName);
	m_ui.m_pLineEditFileName->setEnabled(false);

	// Domain
	m_ui.m_pComboDomain->setCurrentIndex(1);

	// parse data
	if (!m_bImportingFault)
	{
		CXFile3DSurface *pSurfaceFile = dynamic_cast<CXFile3DSurface*>(m_pDataFile);
		if (pSurfaceFile)
			pSurfaceFile->ParseData();
	}

	_UpdateWidet();
}

bool CXPageFile3DSurface::validatePage()
{
	m_pDataFile->SetOjectName(m_ui.m_pLineEdtHorizoName->text());

	if (!m_bImportingFault)
	{
		CXFile3DSurface *pSurfaceFile = dynamic_cast<CXFile3DSurface*>(m_pDataFile);
		pSurfaceFile->SetNegateZ(m_ui.m_pCheckNegateZ->isChecked());
		pSurfaceFile->SetWithoutZone(m_ui.checkBoxZone->isChecked());

		pSurfaceFile->SetSurveyInfo(m_pSelectedUTM, m_uuidSurvey);

		pSurfaceFile->SetDomainType(static_cast<EDomainType>(m_ui.m_pComboDomain->currentIndex()));

		// geometry surface
		QUuid uuidSurfaceGeometry = m_ui.m_pComboParent->currentData().toString();
		CX3DSurface* p3DSurface = dynamic_cast<CX3DSurface*>(::GetObjectByID(uuidSurfaceGeometry));
		pSurfaceFile->SetGeometrySurface(p3DSurface);

		// tell if it is valid input
		bool bInline, bXline, bX, bY, bI, bJ;
		pSurfaceFile->GetImSurManager()->GetDataFlag(bInline, bXline, bX, bY, bI, bJ);
		if (!m_pSelectedUTM || m_pSelectedUTM->GetNI() == 0)
		{
			if ((bInline && bXline && bX && bY) ||
				(bI && bJ && bX && bY) ||
				(!bInline && !bXline && !bI && !bJ && !bX && !bY))
			{
				return true;
			}
			else if (bInline && bXline && !bX && !bY) // only have inline/xline
			{
				QMessageBox::warning(this, ::g_strProductName, "Please select one 3-D survey or select more column data!");
				return false;
			}
			else
			{
				QMessageBox::warning(this, g_strProductName, "Please select one 3-D survey or select more column data!");
				return false;
			}
		}
	}
	else
	{
		CXFaultSticksFile *pFaultFile = dynamic_cast<CXFaultSticksFile *>(m_pDataFile);
		if (!pFaultFile)
			return false;

		pFaultFile->SetDomainType(static_cast<EDomainType>(m_ui.m_pComboDomain->currentIndex()));
		pFaultFile->SetSurveyID(m_uuidSurvey);
	}

	return true;
}

void CXPageFile3DSurface::slotSurfaceNameChange()
{
	QString strSurfaceName = m_ui.m_pLineEdtHorizoName->text();

	if (!m_bImportingFault)
	{
		CXFile3DSurface *pSurfaceFile = dynamic_cast<CXFile3DSurface*>(m_pDataFile);
		if (strSurfaceName == "")
		{
			QMessageBox::warning(NULL, ::g_strProductName, "The 3-D surface cannot be empty.");
			m_ui.m_pLineEdtHorizoName->undo();
			m_ui.m_pLineEdtHorizoName->setFocus();
		}
		else
		{
			pSurfaceFile->GetImSurManager()->SetHorizonName(0, strSurfaceName);
		}
	}
}
