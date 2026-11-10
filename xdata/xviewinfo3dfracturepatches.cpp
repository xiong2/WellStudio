#include "xviewinfo3dfracturepatches.h"

CXViewInfo3DFracturePatches::CXViewInfo3DFracturePatches()
{
	SetDisplayPoint(false);
	SetDisplayLine(true);
	SetDisplayPlane(true);

	SetPointSize(8);
	SetLineWidth(1);
	SetLineColorMode(1);
	SetOpacity(0.82f);
}

void CXViewInfo3DFracturePatches::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetPointColor(GetColor());
	SetLineColor(GetColor());
	SetPlaneColor(GetColor());
}

bool CXViewInfo3DFracturePatches::ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo)
{
	const CXViewInfo3DFracturePatches* pOther = dynamic_cast<const CXViewInfo3DFracturePatches*>(pViewInfo);
	if (!pOther)
		return false;

	SetPointSize(pOther->GetPointSize());
	SetLineWidth(pOther->GetLineWidth());

	SetOpacity(pOther->GetOpacity());

	SetDisplayPoint(pOther->GetDisplayPoint());
	SetDisplayLine(pOther->GetDisplayLine());
	SetDisplayPlane(pOther->GetDisplayPlane());

	return true;
}