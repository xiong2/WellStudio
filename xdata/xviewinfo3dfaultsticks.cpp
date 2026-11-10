#include "xviewinfo3dfaultsticks.h"

CXViewInfo3DFaultSticks::CXViewInfo3DFaultSticks()
{
	SetDisplayPoint(false);
	SetDisplayLine(true);
	SetDisplayPlane(false);

	SetPointSize(8);
	SetLineWidth(3);
	SetLineColorMode(1);
	SetAnnColorType(1);
	SetAnnTop(true);
	SetOpacity(0.82f);
}

void CXViewInfo3DFaultSticks::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetPointColor(GetColor());
	SetLineColor(GetColor());
	SetPlaneColor(GetColor());
}

bool CXViewInfo3DFaultSticks::ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo)
{
	const CXViewInfo3DFaultSticks* pOther = dynamic_cast<const CXViewInfo3DFaultSticks*>(pViewInfo);
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

