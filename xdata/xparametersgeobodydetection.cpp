#include "xparametersgeobodydetection.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParametersGeobodyDetection)
EDetectGeobody
END_REGISTER_OBJECT_TO_FACTORY(CXParametersGeobodyDetection)

CXParametersGeobodyDetection::CXParametersGeobodyDetection() : CXBaseParameter()
{
	//	Initialize all ID to NULL.
	SetDVID(QUuid());

	SetBoundaryPolygonID(QUuid());
	SetStartInline(-999);
	SetEndInline(-999);
	SetStartXline(-999);
	SetEndXline(-999);

	SetIntervalID(QUuid());
	SetTopSurfaceID(QUuid());
	SetBottomSurfaceID(QUuid());
	SetStartZ(-999.25);
	SetEndZ(-999.25);

	SetLowThreshold(-999.25);
	SetHighThreshold(-999.25);

	SetMiniSize(100);
	SetFaceConnectivity(false);
}