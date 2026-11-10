#include "xviewinfoprestackgather.h"
#include "xglobal.h"
#include "xprestackgather.h"

CXViewInfoPreStackGather::CXViewInfoPreStackGather()
	: CXViewInfoObject()
{
	SetIsViewAll(true);
	SetSourcePointShape(0);
	SetSourcePointSize(5);
	SetDetectPointShape(0);
	SetDetectPointSize(1);
	SetSourcePointColor(Qt::red);
}

CXViewInfoPreStackGather::~CXViewInfoPreStackGather()
{

}

bool CXViewInfoPreStackGather::ApplyToCurrentViewInfo(const CXViewInfoObject * pViewInfo)
{
	auto pOtherViewInfo = dynamic_cast<const CXViewInfoPreStackGather*>(pViewInfo);
	if (!pOtherViewInfo)
		return false;

	SetSourcePointSize(pOtherViewInfo->GetSourcePointSize());
	SetSourcePointShape(pOtherViewInfo->GetSourcePointShape());
	SetDetectPointSize(pOtherViewInfo->GetDetectPointSize());
	SetDetectPointShape(pOtherViewInfo->GetDetectPointShape());

	return true;
}

void CXViewInfoPreStackGather::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	auto pPreStackGather = dynamic_cast<CXPreStackGather*>(::GetObjectByID(objID));
	Q_ASSERT(pPreStackGather);

	int iStart, iLast, iNumber;
	pPreStackGather->GetShotIDRange(iStart, iLast, iNumber);

	SetMINShotID(iStart);
	SetMAXShotID(iLast);
	SetShotIDNum(iLast - iStart + 1);
	//SetShotIDStep((iLast - iStart) / iNumber);
	SetShotIDStep(1);
	SetCURShotID(iStart);

	SetDetectPointColor(pPreStackGather->GetColor());
}