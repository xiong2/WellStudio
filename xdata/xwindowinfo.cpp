#include "xwindowinfo.h"

CXWindowInfo::CXWindowInfo()
	: CXBaseParameter()
{
	SetBackgroundColor(QColor(45, 46, 40));

	SetColorbarVisible(true);
	SetColorbarTitleVisible(true);
	SetColorbarTitleColor(Qt::green);
	SetColorbarTitleSize(2);
	SetColorbarTitleFont("arial");
	SetColorbarTickColor(Qt::green);
	SetColorbarTickSize(5);
	SetColorbarMarkColor(Qt::green);
	SetColorbarMarkSize(11);
	SetColorbarMarkFont("arial");
	SetColorbarPosition(0);

	SetCoordVisible(true);
	SetCoordColor(Qt::white);
	SetCoordLineWidth(2);
	SetCoordTickLength(1);
	SetCoordMarkSize(3);
	SetCoordMarkFont("arial");
	SetCoordLabelVisible(true);
	SetCoordLabelSize(3);
	SetCoordLabelFont("arial");
	SetCoordLabelX("X");
	SetCoordLabelY("Y");
	SetCoordGridVisible(false);
	SetCoordGridColor(QColor(128, 128, 128, 255));
	SetCoordGridLineWidth(1);

	SetCompassVisible(true);
	SetCompassTopColor(Qt::green);
	SetCompassBottomColor(Qt::white);
	SetCompassFrameColor(Qt::black);
	SetCompassPosition(0); // right-bottom
}

CXWindowInfo::~CXWindowInfo()
{

}
