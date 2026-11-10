#pragma warning (push,0)
#include "xpagebuildlfmthree.h"
#include "xparameterbuildlfm.h"
#include "xglobal.h"

#include <QHeaderView>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
//
#include <QMessageBox>
#include <QList>

#include <cassert>

#pragma warning(pop)

CXPageBuildLFMThree::CXPageBuildLFMThree(CXParameterBuildLFM* pPara, QWidget *parent)
	: m_pPara(pPara), QWizardPage(parent)
{
	m_ui.setupUi(this);
	assert(m_pPara);

	m_ui.tableWidget->setColumnWidth(0, 240);
	m_ui.tableWidget->setColumnWidth(1, 150);
	m_ui.tableWidget->setColumnWidth(2, 100);
	m_ui.tableWidget->setColumnWidth(3, 100);
	m_ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
	m_ui.tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
}

CXPageBuildLFMThree::~CXPageBuildLFMThree()
{

}

void CXPageBuildLFMThree::initializePage()
{
	disconnect(m_ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(slotCellChanged()));

	// Initialize the blocks
	m_pPara->Initialize();

	// Block number and horizon number
	int nBlockNum = (int)m_pPara->GetVecContactType().size();
	int nHorizonNum = (int)m_pPara->GetVecHorizonID().size();

	// Init the widget
	m_ui.tableWidget->clearContents();
	m_ui.tableWidget->setRowCount(nBlockNum);

	QStringList strZoneNameList = m_pPara->GetZoneNameList();
	std::vector<int> vecContactType = m_pPara->GetVecContactType();
	std::vector<int> vecSliceNum = m_pPara->GetVecSliceNum();
	std::vector<float> vecThickness = m_pPara->GetVecThickness();

	for (int i = 0; i < nBlockNum; ++i)
	{
		QComboBox *pBox = new QComboBox(this);
		pBox->addItem(m_pPara->GetContactName(CXParameterBuildLFM::eProportional));
		pBox->setItemData(0, (int)CXParameterBuildLFM::eProportional);

		if (nHorizonNum > 1)
		{
			pBox->addItem(m_pPara->GetContactName(CXParameterBuildLFM::eTopConformable));
			pBox->addItem(m_pPara->GetContactName(CXParameterBuildLFM::eBottomConformable));
			pBox->setItemData(1, (int)CXParameterBuildLFM::eTopConformable);
			pBox->setItemData(2, (int)CXParameterBuildLFM::eBottomConformable);
		}
		connect(pBox, SIGNAL(activated(int)), this, SLOT(slotCellChanged(int)));

		QLineEdit *pLine1 = new QLineEdit(this);
		QLineEdit *pLine2 = new QLineEdit(this);

		if (vecContactType.at(i) == (int)CXParameterBuildLFM::eProportional)
		{
			pLine1->setText(QString::number(vecSliceNum.at(i)));
			pLine1->setReadOnly(false);

			pLine2->setText("N/A");
			pLine2->setReadOnly(true);
		}
		else
		{
			pLine1->setText("N/A");
			pLine1->setReadOnly(true);

			pLine2->setText(QString::number(vecThickness.at(i)));
			pLine2->setReadOnly(false);
		}

		// item
		QTableWidgetItem* pTableItem = new QTableWidgetItem;
		pTableItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
		pTableItem->setText(strZoneNameList.at(i));

		m_ui.tableWidget->setItem(i, 0, pTableItem); 
		m_ui.tableWidget->setCellWidget(i, 1, pBox);
		m_ui.tableWidget->setCellWidget(i, 2, pLine1);
		m_ui.tableWidget->setCellWidget(i, 3, pLine2);
	}

	// Top and bottom shift
	bool bTwoHorizon = (nHorizonNum == 1 ? false : true);
	float fTopShift = (bTwoHorizon ? 0.f : -100.f);
	float fBotShift = (bTwoHorizon ? 0.f : 100.f);

	m_pPara->SetTopShift(fTopShift);
	m_pPara->SetBottomShift(fBotShift);

	m_ui.m_pLineEdtTop->setText(QString::number(fTopShift, 'f', 1));
	m_ui.m_pLineEdtBottom->setText(QString::number(fBotShift, 'f', 1));

	connect(m_ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(slotCellChanged(int)));
}

void CXPageBuildLFMThree::slotCellChanged(int)
{
	//	So far do not know which changed so refresh all zones.
	std::vector<int> vecContactType = m_pPara->GetVecContactType();
	std::vector<int> vecSliceNum = m_pPara->GetVecSliceNum();
	std::vector<float> vecThickness = m_pPara->GetVecThickness();

	for (int i = 0; i < vecContactType.size(); ++i)
	{
		QComboBox* pCombox = (QComboBox*)(m_ui.tableWidget->cellWidget(i, 1));
		int nType = pCombox->itemData(pCombox->currentIndex()).toInt();

		if (vecContactType.at(i) != nType)
		{
			vecContactType.at(i) = nType;

			QLineEdit *pLine1 = (QLineEdit*)(m_ui.tableWidget->cellWidget(i, 2));
			QLineEdit *pLine2 = (QLineEdit*)(m_ui.tableWidget->cellWidget(i, 3));

			if (nType == (int)CXParameterBuildLFM::eProportional)
			{
				pLine1->setText(QString::number(vecSliceNum.at(i)));
				pLine1->setReadOnly(false);

				pLine2->setText("N/A");
				pLine2->setReadOnly(true);
			}
			else
			{
				pLine1->setText("N/A");
				pLine1->setReadOnly(true);

				pLine2->setText(QString::number(vecThickness.at(i)));
				pLine2->setReadOnly(false);
			}
		}
	}

	// Set contact type
	m_pPara->SetVecContactType(vecContactType);
}

bool CXPageBuildLFMThree::validatePage()
{
	//	Check top shift.
	float fMaxTopShiftDefault = -1000.f;
	float fMaxBottomShiftDefault = 1000.f;

	QString strMin = QString::number(fMaxTopShiftDefault, 'f', 2);
	QString strMax = QString::number(fMaxBottomShiftDefault, 'f', 2);
	QString strMsg = QString("The shift value must be between ") + strMin + " and" + strMax + ".";

	bool b;
	// check top shift
	float fTopShift = m_ui.m_pLineEdtTop->text().toFloat(&b);
	if (!b || fTopShift > fMaxBottomShiftDefault || fTopShift < fMaxTopShiftDefault)
	{
		QMessageBox::warning(this, ::g_strProductName, strMsg);
		return false;
	}

	//	Check bottom shift.
	float fBottomShift = m_ui.m_pLineEdtBottom->text().toFloat(&b);
	if (!b || fBottomShift > fMaxBottomShiftDefault || fBottomShift < fMaxTopShiftDefault)
	{
		QMessageBox::warning(this, g_strProductName, strMsg);
		return false;
	}

	//	If one horizon is selected,  the top and bottom shift must be different
	if (m_pPara->GetVecHorizonID().size() == 1 && fTopShift == fBottomShift)
	{
		QString strMsg = "The top and bottom shift values must be different \n"
			             "if only one horizon is selected!";
		QMessageBox::warning(this, g_strProductName, strMsg);
		return false;
	}
	else
	{
		m_pPara->SetTopShift(fTopShift);
		m_pPara->SetBottomShift(fBottomShift);
	}

	//	Check each zone.
	std::vector<int> vecContactType = m_pPara->GetVecContactType();
	std::vector<int> vecSliceNum = m_pPara->GetVecSliceNum();
	std::vector<float> vecThickness = m_pPara->GetVecThickness();

	for (int i = 0; i < vecContactType.size(); ++i)
	{
		if (vecContactType.at(i) == (int)CXParameterBuildLFM::eProportional)
		{
			QLineEdit *pLine = (QLineEdit *)(m_ui.tableWidget->cellWidget(i, 2));
			int nSliceNum = pLine->text().toInt();
			if (nSliceNum < 2 || nSliceNum > 1000)
			{
				QMessageBox::warning(this, g_strProductName, "The slice number must be between 2 and 1000!");
				return false;
			}
			else
				vecSliceNum.at(i) = nSliceNum;
		}
		else
		{
			QLineEdit *pLine = (QLineEdit *)(m_ui.tableWidget->cellWidget(i, 3));
			float fThickness = pLine->text().toFloat();
			if (fThickness < 1.0f || fThickness > 500.0f)
			{
				QMessageBox::warning(this, g_strProductName, "Thickness value must be between 1 and 500!");
				return false;
			}
			else
				vecThickness.at(i) = fThickness;
		}
	}
	// Set the block parameter
	m_pPara->SetVecSliceNum(vecSliceNum);
	m_pPara->SetVecThickness(vecThickness);

	// check zone names
	QStringList strListName;
	for (int i = 0; i < m_ui.tableWidget->rowCount(); ++i)
	{
		QString strZoneName = m_ui.tableWidget->item(i, 0)->text();
		if (strZoneName == "")
		{
			QMessageBox::warning(this, g_strProductName, "Please provide the valid zone names!");
			return false;
		}
		strListName.append(strZoneName);
	}

	m_pPara->SetZoneNameList(strListName);


	return true;
}
