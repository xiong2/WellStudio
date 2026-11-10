#include "xpageattributes.h"

#include <qcombobox.h>
#include <qtablewidget.h>
#include <QGridLayout>

#include "xdatatype.h"
#include "xunit.h"
#include "xasciifile.h"
#include "xglobal.h"
#include "xfile3dsurface.h"

CXPageAttributes::CXPageAttributes(CXASCIIFile *pASCIIFile, QWidget *parent): QWizardPage(parent)
{
	QGridLayout *pMainLayout = new QGridLayout(this);
	this->setLayout(pMainLayout);
	m_pTable		= new QTableWidget(this);
	m_pASCIIFile	= pASCIIFile;
	pMainLayout->addWidget(m_pTable,0,1,1,1);
	QSpacerItem *pVerticalSpacer = new QSpacerItem(20, 275, QSizePolicy::Minimum, QSizePolicy::Expanding);
	pMainLayout->addItem(pVerticalSpacer,1,0,1,1);
	QStringList sListHeader;
	sListHeader << tr("Attribute") << tr("Data Type") << tr("Unit Type") << tr("Input Unit") << tr("Project Unit");
	m_pTable->setColumnCount(5);
	m_pTable->setHorizontalHeaderLabels(sListHeader);
}

void CXPageAttributes::initializePage()
{
	QStringList& sListAttributes = m_pASCIIFile->GetAttributes();
	QList<int> iListDataType, iListUnit;
	guessDataType(sListAttributes, iListDataType, iListUnit);

	int index = sListAttributes.indexOf("Z");
	if (index != -1)
	{
		switch (m_pASCIIFile->GetDomainType())
		{
		case eNull:
			iListUnit[index] = eVoid;
			break;
		case eTimeDomain:
			iListUnit[index] = eTime;
			break;
		case eDepthDomain:
		default:;
		}
	}

	m_pTable->setRowCount(sListAttributes.size());

	for(int i = 0; i < sListAttributes.size(); i++)
	{
		m_pTable->setItem(i, 0, new QTableWidgetItem(sListAttributes[i]));

		QComboBox *pCBDataType = new QComboBox;
		pCBDataType->addItems(CXDataType::GetAllDataTypeNames());
		pCBDataType->setCurrentIndex(iListDataType[i]);
		pCBDataType->setEnabled(false);
		m_pTable->setCellWidget(i, 1, pCBDataType);
		connect(pCBDataType, SIGNAL(currentIndexChanged(int)), this, SLOT(slotDataTypeChanged(int)));

		QComboBox *pCBDataUnit = new QComboBox;
		pCBDataUnit->addItems(CXUnit::GetAllUnitType());
		pCBDataUnit->setCurrentIndex(iListUnit[i]);
		pCBDataUnit->setEnabled(iListDataType[i] < 3 && iListUnit[i] != 0);
		m_pTable->setCellWidget(i, 2, pCBDataUnit);
		connect(pCBDataUnit, SIGNAL(currentIndexChanged(int)), this, SLOT(slotUnitTypeChanged(int)));

		if(iListUnit[i] != 0)
		{
			QComboBox *pCBInputUnit = new QComboBox;
			pCBInputUnit->addItems(CXUnit::GetAllUnits(static_cast<EXUnitType>(iListUnit[i])));
			pCBInputUnit->setCurrentIndex(0);
			m_pTable->setCellWidget(i, 3, pCBInputUnit);
			
			QComboBox *pCBPrjUnit = new QComboBox;
			pCBPrjUnit->addItems(CXUnit::GetAllUnits(static_cast<EXUnitType>(iListUnit[i])));
			pCBPrjUnit->setCurrentIndex(0);
			pCBPrjUnit->setEnabled(false);
			m_pTable->setCellWidget(i, 4, pCBPrjUnit);	
		}
	}
}

bool CXPageAttributes::validatePage()
{
	QStringList& sListAttributes	= m_pASCIIFile->GetAttributes();
	QList<int>& iListDataType		= m_pASCIIFile->GetAttributeDataType();
	QList<float>& fListUnitRatio	= m_pASCIIFile->GetAttributeUnitRatio();
	iListDataType.clear();
	fListUnitRatio.clear();

	for(int i = 0; i < sListAttributes.size(); i++)
	{
		//	Data type.
		QComboBox *pCBDataType = dynamic_cast<QComboBox *>(m_pTable->cellWidget(i, 1));
		if(!pCBDataType)
			continue;
		iListDataType<<pCBDataType->currentIndex();

		//	Unit ratio.
		float fRatio = 1.;
		QComboBox *pCBUnitType = dynamic_cast<QComboBox *>(m_pTable->cellWidget(i, 2));
		if(pCBUnitType->currentIndex() != 0)
		{
			QComboBox *pCBInputUnit		= dynamic_cast<QComboBox *>(m_pTable->cellWidget(i, 3));
			QComboBox *pCBPrjUnit		= dynamic_cast<QComboBox *>(m_pTable->cellWidget(i, 4));
			if(pCBInputUnit && pCBPrjUnit)
			{
				fRatio = CXUnit::GetConvertRatio(pCBInputUnit->currentText(), pCBPrjUnit->currentText());
			}
		}
		fListUnitRatio<<fRatio;
	}

	return true;
}

void CXPageAttributes::guessDataType(QStringList& sListAttributes, QList<int>& iListType, QList<int>& iListUnit)
{
	int i, iSize = sListAttributes.size();

	for(i = 0; i < iSize; i++)
	{
		if(sListAttributes[i].compare("Well", Qt::CaseInsensitive) == 0)
		{
			iListType<<4;	//	String.
			iListUnit<<eVoid;
		}
		else if(sListAttributes[i].compare("Tops", Qt::CaseInsensitive) == 0)
		{
			iListType<<4;	//	String.
			iListUnit<<eVoid;
		}
		else if(sListAttributes[i].compare("Depth", Qt::CaseInsensitive) == 0
			|| sListAttributes[i].compare("Z", Qt::CaseInsensitive) == 0)
		{
			iListType<<1;	//	Double.
			iListUnit<<eLength;
		}
		else if(sListAttributes[i].compare("X Coordinate", Qt::CaseInsensitive) == 0
			|| sListAttributes[i].compare("X", Qt::CaseInsensitive) == 0)
		{
			iListType<<1;	//	Double.
			iListUnit<<eLength;
		}
		else if(sListAttributes[i].compare("Y Coordinate", Qt::CaseInsensitive) == 0
			|| sListAttributes[i].compare("Y", Qt::CaseInsensitive) == 0)
		{
			iListType<<1;	//	Double.
			iListUnit<<eLength;
		}
		else if(sListAttributes[i].compare("KB", Qt::CaseInsensitive) == 0)
		{
			iListType<<1;	//	Double.
			iListUnit<<eLength;
		}
		else if(sListAttributes[i].contains("TVD", Qt::CaseInsensitive))
		{
			iListType<<1;	//	Double.
			iListUnit<<eLength;
		}
		else if(sListAttributes[i].contains("TWT", Qt::CaseInsensitive))
		{
			iListType<<1;	//	Double.
			iListUnit<<eTime;
		}
		else
		{
			iListType<<4;	//	Default use String.
			iListUnit<<eVoid;
		}
	}
}

void CXPageAttributes::slotDataTypeChanged(int)
{
	//	First we should know which row's template changed.
	QComboBox *pCBDataType = dynamic_cast<QComboBox *>(sender());
	if(!pCBDataType)
		return;

	for(int i = 0; i < m_pTable->rowCount(); i++)
	{
		if(pCBDataType == m_pTable->cellWidget(i, 1))
		{
			if(pCBDataType->currentIndex() < 3)
			{
				//	Check the unit, if disabled, then enable them.
				QComboBox *pCBUnitType = (QComboBox *)m_pTable->cellWidget(i, 2);
				if(!pCBUnitType->isEnabled())
				{
					pCBUnitType->setEnabled(true);
				}
			}
			else
			{
				//	Check the unit, if enabled, then disable them.
				QComboBox *pCBUnitType = (QComboBox *)m_pTable->cellWidget(i, 2);
				if(pCBUnitType->isEnabled())
				{
					pCBUnitType->setCurrentIndex(0);
					pCBUnitType->setEnabled(false);
				}
			}

			return;
		}
	}
}

void CXPageAttributes::slotUnitTypeChanged(int)
{
	//	First we should know which row's template changed.
	QComboBox *pCBUnitType = dynamic_cast<QComboBox *>(sender());
	if(!pCBUnitType)
		return;

	for(int i = 0; i < m_pTable->rowCount(); i++)
	{
		if(pCBUnitType == m_pTable->cellWidget(i, 2))
		{
			if(pCBUnitType->currentIndex()== 0)
			{
				//	No unit, delete input and project unit combo box if exist.
				QComboBox *pCBInputUnit = (QComboBox *)m_pTable->cellWidget(i, 3);
				if(pCBInputUnit)
					delete pCBInputUnit;
				QComboBox *pCBPrjUnit = (QComboBox *)m_pTable->cellWidget(i, 4);
				if(pCBPrjUnit)
					delete pCBPrjUnit;
			}
			else
			{
				//	Create input and project unit combo box if not exist, and reset their candidates.
				QComboBox *pCBInputUnit = (QComboBox *)m_pTable->cellWidget(i, 3);
				if(!pCBInputUnit)
				{
					pCBInputUnit = new QComboBox;
					m_pTable->setCellWidget(i, 3, pCBInputUnit);
				}
				pCBInputUnit->clear();
				pCBInputUnit->addItems(CXUnit::GetAllUnits((EXUnitType)pCBUnitType->currentIndex()));
				pCBInputUnit->setCurrentIndex(0);

				QComboBox *pCBPrjUnit = (QComboBox *)m_pTable->cellWidget(i, 4);
				if(!pCBPrjUnit)
				{
					pCBPrjUnit = new QComboBox;
					m_pTable->setCellWidget(i, 4, pCBPrjUnit);
				}
				pCBPrjUnit->clear();
				pCBPrjUnit->addItems(CXUnit::GetAllUnits((EXUnitType)pCBUnitType->currentIndex()));
				pCBPrjUnit->setCurrentIndex(0);
			}
			return;
		}
	}
}
