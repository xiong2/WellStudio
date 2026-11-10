#include "xviewinfo3dwelltopformation.h"

CXViewInfo3DWellTopFormation::CXViewInfo3DWellTopFormation()
{
	SetDisplayMode(WT_SPHERE);
	SetRadius(6.0f);
	SetHeight(4.0f);
	SetFormationAnnVisible(true);
	SetFormationAnnFont("Arial");
	SetFormationAnnSize(10);
	SetFormationBgrTrans(0);
	SetWellTopFormationUseObjColor(true);
	SetFormationAnnUseObjColor(true);
	SetFormationBgrUseObjColor(false);
	SetFormationBgrColor(Qt::white);
}

void CXViewInfo3DWellTopFormation::SetViewObjectID(const QUuid& objID)
{
    CXViewInfoObject::SetViewObjectID(objID);

	SetWellTopFormationColor(GetColor());
}

bool CXViewInfo3DWellTopFormation::ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo)
{
    auto pOther = dynamic_cast<const CXViewInfo3DWellTopFormation*>(pViewInfo);
	if (!pOther) return false;
	
	SetDisplayMode(pOther->GetDisplayMode());
	SetRadius(pOther->GetRadius());
	SetWellTopFormationUseObjColor(pOther->GetWellTopFormationUseObjColor());
	SetWellTopFormationColor(GetWellTopFormationUseObjColor() ? GetColor() : pOther->GetWellTopFormationColor());
	SetHeight(pOther->GetHeight());
	SetFormationAnnVisible(pOther->GetFormationAnnVisible());
	SetFormationAnnSize(pOther->GetFormationAnnSize());
	SetFormationAnnFont(pOther->GetFormationAnnFont());
	SetFormationAnnUseObjColor(pOther->GetFormationAnnUseObjColor());
	SetFormationAnnColor(GetFormationAnnUseObjColor() ? GetColor() : pOther->GetFormationAnnColor());
	SetFormationBgrUseObjColor(pOther->GetFormationBgrUseObjColor());
	SetFormationBgrColor(GetFormationBgrUseObjColor() ? GetColor() : pOther->GetFormationBgrColor());
	SetFormationBgrTrans(pOther->GetFormationBgrTrans());

	return true;
}