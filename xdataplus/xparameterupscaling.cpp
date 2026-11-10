#pragma warning (push, 0)
#include "xparameterupscaling.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"

#pragma warning pop

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterUpscaling)
ECalculateUpscaling
END_REGISTER_OBJECT_TO_FACTORY(CXParameterUpscaling)

CXParameterUpscaling::CXParameterUpscaling()
{
	SetAverageMethod(eArithemtic);
}

