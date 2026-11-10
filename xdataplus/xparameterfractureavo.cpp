#pragma warning (push, 0)
#include "xparameterfractureavo.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"
#include "xsysteminfo.h"

#pragma warning pop

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterFractureAVO)
EFractureAnalysisAVO
END_REGISTER_OBJECT_TO_FACTORY(CXParameterFractureAVO)

CXParameterFractureAVO::CXParameterFractureAVO()
{
	SetDx(3);
	SetDy(3);
	SetMinimumFold(3);

	SetIncidenceAngle(40);

	SetMethodType(eRuger);
}

