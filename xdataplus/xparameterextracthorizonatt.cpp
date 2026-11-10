#pragma warning (push, 0)
#include "xparameterextracthorizonatt.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"
#include "xglobal.h"
#include "xobject.h"
#include "xproject.h"

#pragma warning pop

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterExtractHorizonAtt)
EExtractHorizonAttribute
END_REGISTER_OBJECT_TO_FACTORY(CXParameterExtractHorizonAtt)

CXParameterExtractHorizonAtt::CXParameterExtractHorizonAtt()
{
	SetMethodType(0);
	SetTopShift(-10);
	SetBottomShift(10);
}

QString CXParameterExtractHorizonAtt::GetPrefix()
{
	if (GetMethodType() == 0)
	{
		return "ins_";
	}
	else if (GetMethodType() == 1)
	{
		return "ari_";
	}
	else
	{
		return "";
	}
}
