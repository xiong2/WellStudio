#pragma warning (push,0)
#include "xpagebuildlfmone.h"
#include "xparameterbuildlfm.h"
#include "xglobal.h"
#include "x3dhorizon.h"
//
#include <QMessageBox>
#include <QList>

#include "xproject.h"
#include "xtree.h"
#include "xobjecttype.h"
#include <cassert>

#pragma warning(pop)

CXPageBuildLFMOne::CXPageBuildLFMOne(CXParameterBuildLFM* pPara, QWidget *parent) 
	:m_pPara(pPara), QWizardPage(parent)
{
	m_ui.setupUi(this);

	assert(pPara);

	// two buttons
	QPixmap pixAdd, pixRemove;
	pixAdd.load(::GetIconPath() + "18804.png");
	pixRemove.load(::GetIconPath() + "Delete.png");
	m_ui.m_pBtnAdd->setIcon(QIcon(pixAdd));
	m_ui.m_pBtnRemove->setIcon(QIcon(pixRemove));

	//	Connections
	connect(m_ui.m_pBtnAdd, SIGNAL(clicked()), this, SLOT(slotAddHorizon()));
	connect(m_ui.m_pBtnRemove, SIGNAL(clicked()), this, SLOT(slotRemoveHorizon()));

	//	Add the current horizon
	slotAddHorizon();
}

CXPageBuildLFMOne::~CXPageBuildLFMOne()
{
}

void CXPageBuildLFMOne::_AddOneObject(CXObject* pObj)
{
	CX3DHorizon *pHorizon = dynamic_cast<CX3DHorizon*>(pObj);

	if (!pHorizon || pHorizon->GetObjectType() != EX3DHorizon)
	{
		QMessageBox::warning(this, ::g_strProductName, "The selected item is not a 3-D horizon!");
		return;
	}

	// Add the horizon
	if (!_AddOneHorizon(pHorizon))
		return;

	//	Update the list view
	m_ui.m_pListHorizon->clear();
	std::vector<QUuid> vecHorizonID = m_pPara->GetVecHorizonID();
	for (int i = 0; i < vecHorizonID.size(); ++i)
	{
		CXObject* pObj = ::GetObjectByID(vecHorizonID.at(i));
		assert(pObj);
		QString strName = pObj->GetObjectName();
		m_ui.m_pListHorizon->addItem(strName);

		if (strName == pHorizon->GetObjectName())
			m_ui.m_pListHorizon->setCurrentRow(i);
	}

	//	If name generated automatically, then change it.
	if (m_pPara->GetLFMName().startsWith("LFM-"))
		_GenerateName();
}

void CXPageBuildLFMOne::slotAddHorizon()
{
	CXObject* pCurrentOBj = ::GetCurrentObject();
	if (!pCurrentOBj)
		return;

	_AddOneObject(pCurrentOBj);
}

void CXPageBuildLFMOne::_GenerateName()
{
	QString strName = "LFM-";

	std::vector<QUuid> vecHorizonID = m_pPara->GetVecHorizonID();
	for (int i = 0; i < vecHorizonID.size(); ++i)
	{
		CXObject* pObj = ::GetObjectByID(vecHorizonID.at(i));
		assert(pObj);

		if (i == 0)
		{
			strName = strName + pObj->GetObjectName();
		}

		if (i == vecHorizonID.size() - 1)
		{
			strName = strName + "_" + pObj->GetObjectName();
		}
	}

	CXObject* pLFMFolder = ::GetRootObjectFolder(EXLFMFolder);
	assert(pLFMFolder);

	QString strLFMName = pLFMFolder->GetUnallocatedName(strName);
	m_pPara->SetLFMName(strLFMName);
	m_ui.m_pLineEdtLFMName->setText(strLFMName);
}

bool CXPageBuildLFMOne::_AddOneHorizon(CX3DHorizon* pHorizon)
{
	std::vector<QUuid> vecHorizonID = m_pPara->GetVecHorizonID();

	if (vecHorizonID.empty())
	{
		m_pPara->SetSurveyID(pHorizon->GetSurveyID());
		vecHorizonID.push_back(pHorizon->GetObjectID());
		m_pPara->SetVecHorizonID(vecHorizonID);
		return true;
	}
	// already contains some horizons
	else
	{
		// Tell if the horizon belong to the same survey
		if (pHorizon->GetSurveyID() != m_pPara->GetSurveyID())
		{
			QMessageBox::warning(this, ::g_strProductName, "The selected horizons must belong to the same survey.");
			return false;
		}

		// If the horizon has already be selected?
		for (int i = 0; i < vecHorizonID.size(); ++i)
		{
			if (pHorizon->GetObjectID() == vecHorizonID.at(i))
				return false;
		}

		// Insert the horizon to the horizon array
		double dZMax = pHorizon->GetZMax();

		// In case some horizons were deleted
		QList<CX3DHorizon*> listHorizon;
		for (int i = 0; i < vecHorizonID.size(); ++i)
		{
			CXObject* pObj = ::GetObjectByID(vecHorizonID.at(i));
			CX3DHorizon* p3DHorizon = dynamic_cast<CX3DHorizon*>(pObj);
			if (p3DHorizon)
				listHorizon.append(p3DHorizon);
		}
		bool bInsert = false;
		for (int i = 0; i < listHorizon.size(); ++i)
		{
			if (dZMax < listHorizon.at(i)->GetZMax())
			{
				listHorizon.insert(i, pHorizon);
				bInsert = true;
				break;
			}
		}
		if (!bInsert)
			listHorizon.append(pHorizon);

		// Get the horizon IDs
		vecHorizonID.clear();
		for (int i = 0; i < listHorizon.size(); ++i)
			vecHorizonID.push_back(listHorizon.at(i)->GetObjectID());

		m_pPara->SetVecHorizonID(vecHorizonID);
		return true;
	}
}

void CXPageBuildLFMOne::slotRemoveHorizon()
{
	//	Remove the selected horizon.
	int currentRow = m_ui.m_pListHorizon->currentRow();
	if (currentRow < 0 || currentRow >= m_ui.m_pListHorizon->count())
		return;

	std::vector<QUuid> vecHorizonID = m_pPara->GetVecHorizonID();
	QUuid iSelectedHorizonID = vecHorizonID.at(currentRow);
	CXObject* pTargetObj = ::GetObjectByID(iSelectedHorizonID);

	QListWidgetItem* pWidgetItem = m_ui.m_pListHorizon->takeItem(currentRow);
	delete pWidgetItem;

	// Remove the horizon ID
	vecHorizonID.erase(vecHorizonID.begin() + currentRow);
	m_pPara->SetVecHorizonID(vecHorizonID);

	//	If name generated automatically, then change it.
	if (m_pPara->GetLFMName().startsWith("LFM-"))
		_GenerateName();
}

bool CXPageBuildLFMOne::validatePage()
{
	QString strLFMName = m_ui.m_pLineEdtLFMName->text();
	if (strLFMName == "")
	{
		QMessageBox::warning(this, ::g_strProductName, "Please set a name for the low frequency model!");
		return false;
	}
	else
	{
		m_pPara->SetLFMName(strLFMName);
	}

	if (m_pPara->GetVecHorizonID().size() <= 0)
	{
		QMessageBox::warning(this, g_strProductName, "At least select one horizon to create a low frequency model!");
		return false;
	}

	return true;
}



