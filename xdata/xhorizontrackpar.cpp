#include "xhorizontrackpar.h"

CXHorizonTrackPar::CXHorizonTrackPar()
{
    //track Mode
    SetTrackMode(0);
	SetTechnique(0);
    SetSnapType(0);
    SetMethod(0);

	//Search window
    SetSearchTop(8);
    SetSearchBottom(8);
    SetSearchDelta(8);

	//Parameter
    SetWindowTop(16);
    SetWindowBottom(16);
    SetQualityFactory(0.7);

	SetOverWrite(true);
}

CXHorizonTrackPar::~CXHorizonTrackPar()
{
}