#pragma warning (push, 0)
#include "xparameterseismicfiltering.h"
#include "xobjectfactory.h"
#include "xobjecttype.h"

#pragma warning pop

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXParameterSeismicFiltering)
ESeismicFiltering
END_REGISTER_OBJECT_TO_FACTORY(CXParameterSeismicFiltering)

CXParameterSeismicFiltering::CXParameterSeismicFiltering()
{
	SetFilterType(eBandPass);
}

QString CXParameterSeismicFiltering::GetFilteringName()
{
	int iType = GetFilterType();
	QString strName = "";
	switch (iType)
	{
	case eLowCut:
		strName = "lowcut";
		break;

	case eHighCut:
		strName = "highcut";
		break;

	case eBandPass:
		strName = "bandpass";
		break;

	default:
		break;
	}

	return strName;
}

