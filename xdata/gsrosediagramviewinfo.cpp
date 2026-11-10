#include "gsrosediagramviewinfo.h"

GSRoseDiagramViewInfo::GSRoseDiagramViewInfo()
{
	SetSize(2);
	SetNumPetal(16);

	SetRoseOpacity(160);
	SetRangeOpacity(80);
    SetPetalColor(QColor("light blue"));
    SetLineColor(QColor("black"));
    SetBGColor(QColor("white"));
    SetRangeColor(QColor("yellow"));

	SetRosePos(8);
	SetShowRange(false);
}

GSRoseDiagramViewInfo::~GSRoseDiagramViewInfo()
{

}