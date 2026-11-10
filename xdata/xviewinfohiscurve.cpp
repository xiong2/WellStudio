#include "xviewinfohiscurve.h"

CXViewInfoHisCurve::CXViewInfoHisCurve()
{
	SetLineWidth(1);
	SetCumLineWidth(1);
	SetCumLineStyle(1);		//	Solid line.
	SetSolid(false);
	SetCumLine(true);
	SetCumColor(QColor("Black"));
}