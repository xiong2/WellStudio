#include "xviewinfogather.h"

CXViewInfoGather::CXViewInfoGather()
{
	SetShowWiggle(true);
	SetShowVA(true);
	SetShowVI(false);

	SetHScale(3.0);
	SetVScale(1);
	SetExcusion(4);

	SetFBColor(QColor("green"));
}