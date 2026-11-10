#include "gssectionviewinfo.h"

GSSectionViewInfo::GSSectionViewInfo()
	: CXViewInfoObject()
{
	SetWidth(3);
	SetShowTurningPoint(true);
	SetTurningPointRadius(3);
	SetFillByStress(false);
	SetLeftHName(false);
	SetRightHName(false);
	SetLeftPName(false);
	SetRightPName(false);
}

GSSectionViewInfo::~GSSectionViewInfo()
{

}
