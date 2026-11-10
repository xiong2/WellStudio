#include "xviewinfo3dpoints.h"

CXViewInfo3DPoints::CXViewInfo3DPoints()
	: CXViewInfoObject()
{
	SetPointSize(3);
	SetIsObjectColor(true);
}

CXViewInfo3DPoints::~CXViewInfo3DPoints()
{

}

void CXViewInfo3DPoints::SetViewObjectID(const QUuid& objID)
{
	CXViewInfoObject::SetViewObjectID(objID);

	SetPointColor(GetColor());
}