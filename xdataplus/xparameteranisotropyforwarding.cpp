#pragma warning (push, 0)
#include "xparameteranisotropyforwarding.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"
#include "xglobal.h"
#include "xobject.h"

#pragma warning pop

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterAnisotropyForwarding)
EAnisotrpicForwarding
END_REGISTER_OBJECT_TO_FACTORY(CXParameterAnisotropyForwarding)

CXParameterAnisotropyForwarding::CXParameterAnisotropyForwarding()
{
	SetOutputDVName("seismic");

}

