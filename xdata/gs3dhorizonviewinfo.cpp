#include "gs3dhorizonviewinfo.h"
#include "xmathmacro.h"

GS3DHorizonViewInfo::GS3DHorizonViewInfo()
    : CXViewInfoObject()
{
	SetIsolineDisplay(false);
	SetIsolineLevelFirst(M_FINVALID);
	SetIsolineLevelLast(M_FINVALID);
	SetIsolineLevelNum(50);
	SetIsolineLevelChanged(false);
	SetIsolineCoarseColor(Qt::black);
	SetIsolineCoarseWidth(5);
	SetIsolineCoarseFreq(5);
	SetIsolineNormalColor(Qt::black);
	SetIsolineNormalWidth(1);
	SetIsolineAnnotationColor(Qt::black);
	SetIsolineAnnotationFontName("Arial");
	SetIsolineAnnotationFontSize(2);

	SetColormapName("probability_smooth");
}

GS3DHorizonViewInfo::~GS3DHorizonViewInfo()
{
}

void GS3DHorizonViewInfo::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetIsolineLevelFirst(GetDisplayDataMin());
	SetIsolineLevelLast(GetDisplayDataMax());
}
