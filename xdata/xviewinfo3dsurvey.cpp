#include "xviewinfo3dsurvey.h"

CXViewInfo3DSurvey::CXViewInfo3DSurvey()
{

	SetBoundaryLineUseObjColor(true);
	SetBoundaryLineWidth(2);

	SetSeismicLineVisible(false);
	SetSeismicLineUseObjColor(true);
	SetSeismicLineWidth(1);

	SetTracePointVisible(true);
	SetTracePointUseObjColor(true);
	SetTracePointSymbol(0);

	SetTickmarksVisible(true);
	SetTickmarksUseObjColor(false);
	SetTickmarksColor(Qt::white);
	SetTickmarksFont("arial");
	SetTickmarksFontSize(2);
	SetInlineAnnotationOnBegin(true);
	SetInlineAnnotationOnEnd(true);
	SetXlineAnnotationOnBegin(true);
	SetXlineAnnotationOnEnd(true);

	SetSurveyNameVisible(false);
	SetSurveyNameUseObjColor(true);
	SetSurveyNameFont("arial");
	SetSurveyNameFontSize(3);
}

CXViewInfo3DSurvey::~CXViewInfo3DSurvey()
{

}

void CXViewInfo3DSurvey::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetBoundaryLineColor(GetColor());
	SetSeismicLineColor(GetColor());
	SetTracePointColor(GetColor());
	SetSurveyNameColor(GetColor());
}