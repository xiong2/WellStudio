#include "gsstressmapviewinfo.h"

GSStressMapViewInfo::GSStressMapViewInfo()
	: CXViewInfoObject()
{
	SetColormapName("stressmap");

	SetShowAsTrafficLight(false);
	SetShowStressStates(true);
	SetStressStatesOpacity(0.8);
	SetStresslinesColor(Qt::blue);
	SetStresslinesLength(3);
	SetStresslinesWidth(4);
	SetStresslinesStep(3);
	SetStresslineAll(true);

	SetShowFaultPolygon(true);
	SetFPLineWidth(5);
	SetFPLineColor(Qt::black);
	SetFPFillColor(Qt::white);

	SetShowCapsule(false);
	SetCapsuleOpacity(1.0);
	SetCapsuleLineColor(Qt::blue);

	SetShowAnticline(false);
	SetAnticlineColor(Qt::blue);
	SetAnticlineWidth(2);
	SetAnticlineMarkerLineColor(Qt::black);
	SetAnticlineMarkerSize(2);
	SetAnticlineStressArrowSize(2);
}

GSStressMapViewInfo::~GSStressMapViewInfo()
{

}
