#include "xviewinfotimeslice.h"

CXViewInfoTimeSlice::CXViewInfoTimeSlice(void)
{
	SetLineColor(Qt::black);
	SetLineSize(2);
	SetLineStyle(Qt::SolidLine);

	SetDisplayMode(0);
	SetSeismicDisplay(true);
	SetFracColor(Qt::red);
	SetFracDX(3);
	SetFracDY(3);
	SetFracScale(1.f);
	SetFracMinThreshold(0.02);
	SetFracMaxThreshold(0.98);
	SetFracWidth(1);
	SetFracHeight(2);
}

CXViewInfoTimeSlice::~CXViewInfoTimeSlice(void)
{
}
