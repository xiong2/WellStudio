#include "xviewinfocombinedline.h"

CXViewInfoCombinedLine::CXViewInfoCombinedLine()
{
	SetLineWidth(4);
	SetNeedColormap(false);
	SetColormapName("red_white_dkblue");
}

void CXViewInfoCombinedLine::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetLineColor(GetColor());
}

bool CXViewInfoCombinedLine::ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo)
{
	auto pOther = dynamic_cast<const CXViewInfoCombinedLine*>(pViewInfo);
	if (!pOther) return false;

	SetLineWidth(pOther->GetLineWidth());

	return true;
}