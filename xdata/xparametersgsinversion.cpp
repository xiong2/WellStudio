#include "xparametersgsinversion.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParametersGSInversion)
EGSInversion
END_REGISTER_OBJECT_TO_FACTORY(CXParametersGSInversion)

CXParametersGSInversion::CXParametersGSInversion() : CXBaseParameter()
{
	//	Initialize all ID to NULL.
	SetSMID(QUuid());

	SetStartInline(-999);
	SetEndInline(-999);
	SetStartXline(-999);
	SetEndXline(-999);
	SetQCSection(QUuid());
}