#include "xparametermakerevinterpolation.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterMakeRevInterpolation)
EMakePropertyModel
END_REGISTER_OBJECT_TO_FACTORY(CXParameterMakeRevInterpolation)

CXParameterMakeRevInterpolation::CXParameterMakeRevInterpolation():CXBaseParameter()
{
	SetAlgorithmType(eOrdinaryKriging);

	SetRadius(10000);
	SetPower(2.0);
	SetMaxSampleNum(15);


	SetVariogramType(Spherical);
	SetSill(1.0);
	SetNugget(0.001);
	SetAzimuth(0.);
	;
}
CXParameterMakeRevInterpolation::~CXParameterMakeRevInterpolation()
{
	;
}

