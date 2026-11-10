#include "xparametermake2dgrid.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterMake2DGrid)
EMake2DGRid
END_REGISTER_OBJECT_TO_FACTORY(CXParameterMake2DGrid)


CXParameterMake2DGrid::CXParameterMake2DGrid()
{
	SetAlgorithmType(eInverseDistance);

	SetRadius(10000);
	SetPower(2.0);
	SetMaxSampleNum(15);


	SetVariogramType(Spherical);
	SetSill(1.0);
	SetNugget(0.001);
	SetAzimuth(0.);
}
