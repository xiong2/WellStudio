#pragma warning (push, 0)
#include "xparameter3terminversion.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"
#include "xsysteminfo.h"

#pragma warning pop

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameter3TermInversion)
EAVOInversion,
EAVOSSInversion,
EAnisotropyInversion
END_REGISTER_OBJECT_TO_FACTORY(CXParameter3TermInversion)

CXParameter3TermInversion::CXParameter3TermInversion()
{
	SetGamma(0.5f);
	SetMaxLoopNum(20);
	SetTolerance(0.00001);

	SetLambda(1.f);
	SetBeta(0.f);
	SetSigma(1.f);
	SetAlpha(0.05f);

	SetLowCut(7.f);
	SetLowOverlap(2.f);
	SetHighCut(60.f);
	SetHighOverlap(5.f);

	SetOutputType(eZpVpVsRho);

	SetOutputInversion(true);
	SetOutputPrior(false);
	SetAkiRichards(true);

	int nCPUNum = CXSystemInfo::GetCPUNum();
	SetCPUNumber(nCPUNum);

	SetUseHorizon(false);
}