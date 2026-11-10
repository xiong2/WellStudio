#pragma warning( push ,0 )
#include "xparameterlfminterpolation.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"
#pragma warning( pop )

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterLFMInterpolation)
ELFMInterpolation
END_REGISTER_OBJECT_TO_FACTORY(CXParameterLFMInterpolation)

CXParameterLFMInterpolation::CXParameterLFMInterpolation()
{
	SetAlgorithmType(eInverseDistance);

	SetPower(2.0);
	SetMaxSampleNum(15);


	SetVariogramType(Exponential);
	SetSill(1.0);
	SetNugget(0.001);
	SetAzimuth(0.);

}