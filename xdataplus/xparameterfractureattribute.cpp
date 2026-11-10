#pragma warning (push, 0)
#include "xparameterfractureattribute.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"
#include "xsysteminfo.h"

#pragma warning pop

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterFractureAttribute)
EFractureAttribute
END_REGISTER_OBJECT_TO_FACTORY(CXParameterFractureAttribute)

CXParameterFractureAttribute::CXParameterFractureAttribute()
{
	SetMinimumFold(4);
}