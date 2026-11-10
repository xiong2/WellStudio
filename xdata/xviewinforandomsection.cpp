#include "xviewinforandomsection.h"

CXViewInfoRandomSection::CXViewInfoRandomSection()
	: CXViewInfoObject()
{
	SetBMLineUseObjectColor(true);
	SetBMLineWidth(1);
	SetBMPointSize(10);
	SetBMPickedLineColor(Qt::yellow);
	SetBMPickedLineWidth(2);
	SetNeedColormap(false);
}

CXViewInfoRandomSection::~CXViewInfoRandomSection()
{

}

void CXViewInfoRandomSection::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetBMLineColor(GetColor());
}