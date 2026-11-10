#include "xgm.h"
#include "xobjectfactory.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXGM)
EXGM
END_REGISTER_OBJECT_TO_FACTORY(CXGM)

CXGM::CXGM(const QString& strName)
:CXObject(strName)
{
	SetIconName("ReservoirModel.png");
	SetObjectType(EXGM);
}

CXGM::~CXGM()
{
}

bool CXGM::SerializeData(CXArchive& ar)
{

	return true;
}