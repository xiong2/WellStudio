#include "xwelltopformation.h"
#include "xobjectfactory.h"
#include "xwelltops.h"
#include "x3dpoints.h" 

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXWellTopFormation)
EXWellTopFormation
END_REGISTER_OBJECT_TO_FACTORY(CXWellTopFormation)

CXWellTopFormation::CXWellTopFormation(const QString& strName)
:CXObject(strName)
{
	SetIconName("Formation.png");
	SetObjectType(EXWellTopFormation);

	SetDeletableFlag(false);
}

CXWellTopFormation::~CXWellTopFormation()
{
}

CX3DPoints* CXWellTopFormation::GetAllPoints()
{
	CXWellTops* pWellTops = dynamic_cast<CXWellTops*>(this->GetParent());
	if (!pWellTops)
		return NULL;
	else
		return pWellTops->Get3DPointsFromFormation(this->GetObjectName());
}

double CXWellTopFormation::GetDepthOnWell(QString sWellName)
{
	CXWellTops* pWellTops = dynamic_cast<CXWellTops*>(this->GetParent());
	if (!pWellTops)
		return 0.;
	else
		return pWellTops->GetOneRecord(sWellName, this->GetObjectName());
}

void CXWellTopFormation::_SetSelfDimension()
{
	CX3DPoints* pPoints = GetAllPoints();
	if (!pPoints)
		return;

	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	pPoints->GetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);

	_SetDimension(dXMin, dXMax, dYMin, dYMax, dZMin, dZMax);
}

