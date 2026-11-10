#include "xwindowinfosection.h"

CXWindowInfoSection::CXWindowInfoSection(void)
{
	SetExcursion(3.f);
	SetCliping(3.f);
	SetTraceStep(1.f);

	
	//SetTraceScale(1.4173f);		//	As 20 trace/cm.
	//SetVerScale(0.35433f);		//	As 80 ms/cm

	SetTraceScale(20);		//	As 20 trace/cm.
	SetVerScale(80);		//	As 80 ms/cm

	SetForeColormapName("colormap");
	SetVariableIntensity(true);
	SetWiggleVariableArea(false);
	SetWiggle(false);
	SetForeVariableIntensity(true);
	SetForeWiggleVariableArea(false);
	SetForeWiggle(false);
	SetForeAlpha(0.3f);
	QStringList list;
	list << "Section Name" << "CDP" << "Line";
	SetShowContents(list);
	SetHorAnnColor(Qt::black);
	SetHorAnnSize(9);
	SetHorAnnFont("Arial");
	SetHorAuto(true);
	SetHorIncTraces(50);
	SetHorIncofMinor(10);
	SetHorAxisMargin(80);

	SetShowMajorLine(false);
	SetVerAnnColor(Qt::black);
	SetVerAnnSize(9);
	SetVerAnnFont("Arial");
	SetVerAuto(true);
	SetVerIncTraces(50);
	SetVerIncofMinor(10);
	SetVerAxisMargin(80);
	SetSearchingRadius(200.f);
}
