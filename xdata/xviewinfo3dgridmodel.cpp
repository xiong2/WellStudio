#include "xviewinfo3dgridmodel.h"
#include "xgridmodel.h"
#include "xglobal.h"

CXViewInfo3DGridModel::CXViewInfo3DGridModel()
    : CXViewInfoObject()
{
	SetLineColor(Qt::gray);
	SetDisplayLine(true);
}

void CXViewInfo3DGridModel::SetViewObjectID(const QUuid& objID)
{
    CXViewInfoObject::SetViewObjectID(objID);

	CXGridModel* gridModel = dynamic_cast<CXGridModel*>(::GetObjectByID(objID));

	if (gridModel)
	{	
		unsigned nI, nJ, nK;
		gridModel->GetIJKDimentionInfo(nI, nJ, nK);

		SetMinI(1);
		SetMaxI(nI);
		SetMinJ(1);
		SetMaxJ(nJ);
		SetMinK(1);
		SetMaxK(nK);

		SetGeomColor(gridModel->GetColor());
	}
}
