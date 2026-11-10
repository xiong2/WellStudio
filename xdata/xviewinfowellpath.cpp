#include "xviewinfowellpath.h"

CXViewInfoWellPath::CXViewInfoWellPath()
{	
	SetWellNameVisible(true);
	SetWellNameUseObjColor(true);
	SetWellNameFontSize(15);
	SetWellNameFontFamily("times");
	SetWellNamePosition(1);

	SetWellPathVisible(true);
	SetWellPathUseObjColor(true);
	SetWellPathRadius(1);
    
	SetWellSymbolVisible(true);
	SetWellSymbolUseObjColor(true);
	SetWellSymbolRadius(5);
}
CXViewInfoWellPath::~CXViewInfoWellPath()
{

}

void CXViewInfoWellPath::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetWellNameColor(GetColor());
	SetWellPathColor(GetColor());
    SetWellSymbolColor(GetColor());
}

bool CXViewInfoWellPath::ApplyToCurrentViewInfo(const CXViewInfoObject* pViewInfo)
{
	const CXViewInfoWellPath* pOther = dynamic_cast<const CXViewInfoWellPath*>(pViewInfo);
	if (!pOther)
		return false;

	SetWellNameVisible(pOther->GetWellNameVisible());
	SetWellNameUseObjColor(pOther->GetWellNameUseObjColor());
	SetWellNameColor(GetWellNameUseObjColor() ? GetColor() : pOther->GetWellNameColor());
	SetWellNameFontSize(pOther->GetWellNameFontSize());
    SetWellNameFontFamily(pOther->GetWellNameFontFamily());
	SetWellNamePosition(pOther->GetWellNamePosition());

	SetWellPathVisible(pOther->GetWellPathVisible());
	SetWellPathColor(GetWellPathUseObjColor() ? GetColor() : pOther->GetWellPathColor());
	SetWellPathUseObjColor(pOther->GetWellPathUseObjColor());
	SetWellPathRadius(pOther->GetWellPathRadius());

    SetWellSymbolVisible(pOther->GetWellSymbolVisible());
	SetWellSymbolColor(GetWellSymbolUseObjColor() ? GetColor() : pOther->GetWellSymbolColor());
	SetWellSymbolUseObjColor(pOther->GetWellSymbolUseObjColor());
	SetWellSymbolRadius(pOther->GetWellSymbolRadius());

	return true;
}
