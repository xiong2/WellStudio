#include "xwindowinfobasemap.h"

CXWindowInfoBasemap::CXWindowInfoBasemap()
{
	SetLastScale(0.f);
	SetLastCenterOffsetX(0.0);
	SetLastCenterOffsetY(0.0);

	SetScalebarVisible(true);
	SetScalebarPosition(0);
	SetScaleMarkColor(Qt::white);
	SetScaleMarkSize(2);
	SetScaleMarkFont("times");
	SetScaleFrameColor(Qt::white);
}

CXWindowInfoBasemap::~CXWindowInfoBasemap()
{

}
