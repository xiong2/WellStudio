#include "xparameterspartialstack.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParametersPartialStack)
EPartialStack
END_REGISTER_OBJECT_TO_FACTORY(CXParametersPartialStack)

CXParametersPartialStack::CXParametersPartialStack() : CXBaseParameter()
{
	SetOutputDVName("");

	///	ID of original data volume.
	SetInputDVID(QUuid());

	///	Parameters of dimension.
	SetStartInline(-999);
	SetEndInline(-999);
	SetStartXline(-999);
	SetEndXline(-999);

	///	Parameters of Z dimension.
	SetStartZ(-999);
	SetEndZ(-999);
	SetZInterval(-999);

	///	Rolling window size.
	SetRollingInlines(1);
	SetRollingXlines(1);
}