#include "xviewinfoseismicsection.h"

CXViewInfoSeismicSection::CXViewInfoSeismicSection()
	: CXViewInfoObject()
{
	SetBMLineUseObjectColor(true);
	SetBMLineWidth(1);
	SetBMPickedLineColor(Qt::red);
	SetBMPickedLineWidth(3);

	Set3DPickedFrameColor(Qt::red);
	Set3DPickedFrameWidth(3);
	SetNeedColormap(false);
}

CXViewInfoSeismicSection::~CXViewInfoSeismicSection()
{

}

void CXViewInfoSeismicSection::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetBMLineColor(GetColor());
}