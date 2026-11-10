#include "xpageselectrock.h"

#include <cassert>

#include "xtypecombo.h"
#include "xparameterwellhorzionintersect.h"

CXPageSelectRock::CXPageSelectRock(CXParameterWellHorzionIntersect* pPara, QWidget *parent)
	: QWizardPage(parent)
{
	m_ui.setupUi(this);

	assert(pPara);
	m_pPara = pPara;
	
    m_ui.tableWidget->horizontalHeader()->setSectionsClickable(QHeaderView::Stretch);
	m_ui.tableWidget->verticalHeader()->setVisible(false);
	m_ui.tableWidget->verticalHeader()->setDefaultSectionSize(40);
}

void CXPageSelectRock::initializePage()
{
	m_ui.tableWidget->clear();
	m_vecRock.clear();

	QStringList listHorizonName = m_pPara->GetHorizonNameList();

	m_ui.tableWidget->setColumnCount(2);
	m_ui.tableWidget->setRowCount(listHorizonName.size()-1);

	m_ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "Horizon Name" << "Rock Type");

	for(int i=0; i<listHorizonName.size()-1; ++i)
	{
		CXTypeCombo *lithology_combo = new CXTypeCombo(ePatternType);
		lithology_combo->SetSelectedType(3);	// default is ÖÐÉ°ÑÒ
		m_ui.tableWidget->setItem(i, 0, new QTableWidgetItem(listHorizonName.at(i)+" ~ "+listHorizonName.at(i+1)));
		m_ui.tableWidget->setCellWidget(i, 1, lithology_combo);
		m_vecRock.push_back(lithology_combo);
	}
}

bool CXPageSelectRock::validatePage()
{
	assert(!m_vecRock.isEmpty());

	QStringList selectedRockNameList;
	for (auto rock = m_vecRock.begin(); rock != m_vecRock.end(); ++rock)
	{
		selectedRockNameList << (*rock)->currentText();
	}
	assert(!selectedRockNameList.isEmpty());

	m_pPara->SetRockNameList(selectedRockNameList);

	return true;
}