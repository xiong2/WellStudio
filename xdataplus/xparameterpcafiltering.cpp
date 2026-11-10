#pragma warning (push, 0)
#include "xparameterpcafiltering.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"

#pragma warning pop

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterPCAFiltering)
ESeismicPCAFiltering
END_REGISTER_OBJECT_TO_FACTORY(CXParameterPCAFiltering)

CXParameterPCAFiltering::CXParameterPCAFiltering()
{
	SetWinNI(3);
	SetWinNJ(3);
	SetWinNK(5);
}



