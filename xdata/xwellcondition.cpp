#include "xwellcondition.h"
#include "xwell.h"
#include "xobjectfactory.h"
#include "xwellcells.h"
#include "xreservoirmodel.h"
#include "xgridmodel.h" 

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellCondition)
EXWellCondition
END_REGISTER_OBJECT_TO_FACTORY(CXWellCondition)

CXWellCondition::CXWellCondition()
{
}

CXWellCondition::CXWellCondition(QList<CXWell *> listWells)
{
	SetObjectType(EXWellCondition);
	SetObjectName("Well Condition");
	SetIconName("WellCondition");

	foreach(CXWell *pWell, listWells)
	{
		CalculateOneWell(pWell);
	}
}

CXWellCondition::~CXWellCondition()
{
}

QList<CXWell *> CXWellCondition::GetCalculatedWells()
{
	QList<CXWell *> listWells;
	QList<CXObject *> listWellCells = GetChildren(EXWellCells);
	for(int i = 0; i < listWellCells.size(); i++)
	{
		CXWellCells *pWellCells = (CXWellCells *)listWellCells[i];
		listWells << dynamic_cast<CXWell*>(::GetObjectByID(pWellCells->GetWellID()));
	}

	return listWells;
}

void CXWellCondition::CalculateOneWell(CXWell *pWell)
{
	//	First find whether this well's data already exist, if so, delete it.
	QList<CXObject *> listWellCells = GetChildren(EXWellCells);
	for(int i = 0; i < listWellCells.size(); i++)
	{
		CXWellCells *pWellCells = (CXWellCells *)listWellCells[i];
		if(pWellCells->GetWellID() == pWell->GetObjectID())
		{
			RemoveOneChild(pWellCells);
			delete pWellCells;
			break;
		}
	}

	//	Calculate the well's cells.
	CXReservoirModel *pResModel = dynamic_cast<CXReservoirModel*>(GetParent());
	CXGridModel *pGridModel = dynamic_cast<CXGridModel*>(pResModel->GetGeometryObject());
	CXWellCells *pWellCells = CXWellCells::CreateWellCells(pGridModel, pWell);

	if(pWellCells)
	{
		pWellCells->SetNodeFlag(false);
		AddChild(pWellCells);

		//	If curve cells exist, calculate the well curve cells.
	}
}


