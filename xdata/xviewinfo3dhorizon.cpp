#include "xviewinfo3dhorizon.h"

CXViewInfo3DHorizon::CXViewInfo3DHorizon()
{
	SetSectionLineUseObjColor(true);
	SetSectionLineWidth(2);

	SetSectionAnnotationUseObjColor(true);
	SetSectionAnnotationBackgroundColor(Qt::white);
	SetSectionAnnotationSize(8);

	SetSectionIntersectionPointSize(4);

	SetSectionAnnotationBackgroundVisible(false);
	SetSectionAnnotationLeftVisible(true);
	SetSectionAnnotationRightVisible(false);
}

CXViewInfo3DHorizon::~CXViewInfo3DHorizon()
{

}

void CXViewInfo3DHorizon::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetSectionLineColor(GetColor());
	SetSectionAnnotationColor(GetColor());
}

bool CXViewInfo3DHorizon::ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo)
{
	const CXViewInfo3DHorizon* pOther = dynamic_cast<const CXViewInfo3DHorizon*>(pViewInfo);
	if (!pOther)
		return false;

	SetSectionLineUseObjColor(pOther->GetSectionLineUseObjColor());
	SetSectionLineColor(GetSectionLineUseObjColor() ? GetColor() : pOther->GetSectionLineColor());
	SetSectionLineWidth(pOther->GetSectionLineWidth());

	SetSectionAnnotationUseObjColor(pOther->GetSectionAnnotationUseObjColor());
	SetSectionAnnotationColor(GetSectionAnnotationUseObjColor() ? GetColor() : pOther->GetSectionAnnotationColor());
	SetSectionAnnotationBackgroundColor(pOther->GetSectionAnnotationBackgroundColor());
	SetSectionAnnotationSize(pOther->GetSectionAnnotationSize());

	SetSectionIntersectionPointSize(pOther->GetSectionIntersectionPointSize());

	SetSectionAnnotationBackgroundVisible(pOther->GetSectionAnnotationBackgroundVisible());
	SetSectionAnnotationLeftVisible(pOther->GetSectionAnnotationLeftVisible());
	SetSectionAnnotationRightVisible(pOther->GetSectionAnnotationRightVisible());

	return true;
}