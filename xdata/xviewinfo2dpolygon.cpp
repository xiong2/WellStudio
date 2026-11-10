#include "xviewinfo2dpolygon.h"

CXViewInfo2DPolygon::CXViewInfo2DPolygon()
	: CXViewInfoObject()
{
	SetBMPickedColor(Qt::yellow);
	SetBMPickedWidth(2);

	SetBMLineUseObjectColor(true);
	SetBMLineWidth(1);

	SetBMPivotUseObjectColor(true);
	SetBMPivotSize(10);

	SetBMIsFill(false);
	SetBMFillUseObjectColor(true);
}

CXViewInfo2DPolygon::~CXViewInfo2DPolygon()
{

}

bool CXViewInfo2DPolygon::ApplyToCurrentViewInfo(const CXViewInfoObject * pViewInfo)
{
	auto pOther = dynamic_cast<const CXViewInfo2DPolygon* const>(pViewInfo);
	if (!pOther)
		return false;

	SetBMLineUseObjectColor(pOther->GetBMLineUseObjectColor());
	SetBMLineColor(GetBMLineUseObjectColor() ? GetColor() : pOther->GetBMLineColor());
	SetBMLineWidth(pOther->GetBMLineWidth());

	SetBMPivotUseObjectColor(pOther->GetBMPivotUseObjectColor());
	SetBMPivotColor(GetBMPivotUseObjectColor() ? GetColor() : pOther->GetBMPivotColor());
	SetBMPivotSize(pOther->GetBMPivotSize());

	SetBMIsFill(pOther->GetBMIsFill());
	SetBMFillUseObjectColor(pOther->GetBMFillUseObjectColor());

	QColor colorObj = GetColor();
	colorObj.setAlphaF(pOther->GetBMFillColor().alphaF());
	SetBMFillColor(GetBMFillUseObjectColor() ? colorObj : pOther->GetBMFillColor());

	return true;
}

void CXViewInfo2DPolygon::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);
	SetBMLineColor(GetColor());
	SetBMPivotColor(GetColor());

	// Fill Color
	QColor alphaFillColor = GetColor();
	alphaFillColor.setAlphaF(0.5);
	SetBMFillColor(alphaFillColor);
}