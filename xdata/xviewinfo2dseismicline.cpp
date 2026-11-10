#include "xviewinfo2dseismicline.h"

CXViewInfo2DSeismicLine::CXViewInfo2DSeismicLine()
{
	SetDisplayNameOnTop(true);
	SetDisplayNameOnBottom(false);
	SetNameSize(10);
	SetNameFont(QString::fromLatin1("Arial"));
	SetLineWidth(1);
	SetColormapName("rainbow");
}

void CXViewInfo2DSeismicLine::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetNameColor(GetColor());
	SetLineColor(GetColor());
}

bool CXViewInfo2DSeismicLine::ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo)
{
	auto pOther = dynamic_cast<const CXViewInfo2DSeismicLine*>(pViewInfo);
	if (!pOther) return false;

	SetDisplayNameOnTop(pOther->GetDisplayNameOnTop());
	SetDisplayNameOnBottom(pOther->GetDisplayNameOnBottom());
	SetNameSize(pOther->GetNameSize());
	SetNameFont(pOther->GetNameFont());
	SetLineWidth(pOther->GetLineWidth());

	return true;
}