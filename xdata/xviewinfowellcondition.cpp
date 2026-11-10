#include "xviewinfowellcondition.h"
#include "xwellcondition.h"
#include "xglobal.h"
#include "xwell.h"

CXViewInfoWellCondition::CXViewInfoWellCondition()
	: CXViewInfoObject()
{
	SetLineColor(Qt::gray);
	SetDisplayLine(true);
}

void CXViewInfoWellCondition::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	CXWellCondition *pWellCondition = dynamic_cast<CXWellCondition*>(::GetObjectByID(objID));

	if (pWellCondition)
	{	
		const QList<CXWell*> &listWell = pWellCondition->GetCalculatedWells();
		std::vector<QUuid> vecWellId;
		std::vector<int> vecVisible;
		for (CXWell *pWell : listWell)
		{
			vecWellId.push_back(pWell->GetObjectID());
			vecVisible.push_back(1);
		}
		SetWellList(vecWellId);
		SetWellVisibleList(vecVisible);
		SetGeomColor(pWellCondition->GetColor());
	}
}
