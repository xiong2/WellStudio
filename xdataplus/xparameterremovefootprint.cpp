#pragma warning (push, 0)
#include "xparameterremovefootprint.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"

#pragma warning pop

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterRemoveFootprint)
ERemoveFootprint
END_REGISTER_OBJECT_TO_FACTORY(CXParameterRemoveFootprint)

CXParameterRemoveFootprint::CXParameterRemoveFootprint()
{
	SetThreshold(1.f);
	SetWavelet("sym4");

	SetLevel(5);
	SetWindow(5);

	SetDirection("Both");
}