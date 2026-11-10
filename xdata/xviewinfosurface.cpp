#include "xviewinfosurface.h"
#include "xglobal.h"
#include "xobject.h"

CXViewInfoSurface::CXViewInfoSurface()
{
	SetDisplayMode(1);
	SetColormapName("probability_smooth");
	SetPointColorType(2);
	SetPointSize(5);

	SetReverseColormap(false);
	SetMaxLevel(0.0);
	SetMinLevel(0.0);
	SetIncLevel(0.0);

	SetFillColorType(2);
	SetDiscreteFillColorName("probability_smooth");

	SetContourStart(0.0);
	SetContourEnd(0.0);
	SetContourInc(0.0);
	SetContourVisible(false);
	SetMajorColorType(1);
	SetMinorColorType(1);
	SetMajorLineWeight(4);
	SetMinorLineWeight(2);
	SetMajorLineStyle(1); // Qt::PenStyle::SolidLine
	SetMinorLineStyle(1); // Qt::PenStyle::SolidLine
	SetMajorLineInterval(5);
	SetMajorContourColor(Qt::red);
	SetMinorContourColor(Qt::yellow);

	SetFracAzimuth(QUuid());
	SetFracDensity(QUuid());
	SetFracDX(3);
	SetFracDY(3);
	SetFracScale(1.f);
	SetFracMinThreshold(0.02);
	SetFracMaxThreshold(0.98);
	SetFracColorType(1);
	SetFracColor(Qt::red);
	SetFracWidth(1);
	SetFracHeight(2);
	SetFracOffset(5);

	SetSectionLineUseObjColor(true);
	SetSectionLineWidth(2);
	SetSectionAnnotationUseObjColor(true);
	SetSectionAnnotationBackgroundColor(Qt::yellow);
	SetSectionAnnotationSize(3);
	SetSectionIntersectionPointSize(2);
	SetSectionAnnotationLeftVisible(true);
	SetSectionAnnotationRightVisible(false);
	SetSectionAnnotationBackgroundVisible(true);
}

CXViewInfoSurface::~CXViewInfoSurface()
{

}

void CXViewInfoSurface::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	CXObject* pObj = ::GetObjectByID(objID);

	SetPointColor(pObj->GetColor());
	SetFillColor(pObj->GetColor());
	SetSectionLineColor(pObj->GetColor());
	SetSectionAnnotationColor(pObj->GetColor());
}

void CXViewInfoSurface::AddDiscreteContourFillColor(float fMin, float fMax, const QColor& color)
{
	m_rangeColor.insert(keMakeRange(fMin, fMax), color);
}