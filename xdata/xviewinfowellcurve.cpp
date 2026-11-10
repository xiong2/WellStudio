#include "xviewinfowellcurve.h"


CXViewInfoWellCurve::CXViewInfoWellCurve() : CXViewInfoObject()
{
	SetLineVisible(true);
	SetLineWidth(2);
	SetLineColorMode(1);

	SetFillVisible(false);
	SetFillWidth(40);
	SetFillColorMode(1);

	SetDisplayMode3D(1);
	SetDisplayModeSection(0);

	SetVIWidth(5);

	SetFilterLowFreq(60.0);
	SetFilterLowOverlap(10.0);
	SetFilterHighFreq(10.0);
	SetFilterHighOverlap(3.0);
}


CXViewInfoWellCurve::~CXViewInfoWellCurve(void)
{
}

void CXViewInfoWellCurve::SetViewObjectID(const QUuid & objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetLineColor(GetColor());
	SetFillColor(GetColor());
}


bool CXViewInfoWellCurve::ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo)
{
    const CXViewInfoWellCurve* pOther = dynamic_cast<const CXViewInfoWellCurve*>(pViewInfo);
	if (!pOther)
		return false;

	CXViewInfoObject::ApplyToCurrentViewInfo(pViewInfo);

	SetDisplayMode3D(pOther->GetDisplayMode3D());
	SetDisplayModeSection(pOther->GetDisplayModeSection());
	SetLineVisible(pOther->GetLineVisible());
	SetLineWidth(pOther->GetLineWidth());
	SetLineColorMode(pOther->GetLineColorMode());
	SetLineColor(pOther->GetLineColor());
	SetFillVisible(pOther->GetFillVisible());
	SetFillWidth(pOther->GetFillWidth());
	SetFillColorMode(pOther->GetFillColorMode());
	SetFillColor(pOther->GetFillColor());
	SetFilterType(pOther->GetFilterType());
	SetFilterLowFreq(pOther->GetFilterLowFreq());
	SetFilterLowOverlap(pOther->GetFilterLowOverlap());
	SetFilterHighFreq(pOther->GetFilterHighFreq());
	SetFilterHighOverlap(pOther->GetFilterHighOverlap());

	return true;
}