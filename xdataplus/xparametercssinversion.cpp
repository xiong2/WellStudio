#pragma warning (push, 0)
#include "xparametercssinversion.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"

#pragma warning pop

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterCSSInversion)
ECSSInversion
END_REGISTER_OBJECT_TO_FACTORY(CXParameterCSSInversion)

CXParameterCSSInversion::CXParameterCSSInversion()
{
	SetAlpha(0.05f);
	SetMu(1.f);
	SetSigma(0.01f);
	SetMaxLoopNum(20);
	SetTolerance(0.0001);
}