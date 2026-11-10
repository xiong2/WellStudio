#include "xviewinfolfmgeometry.h"
#include "xlfmgeometry.h"
#include "xglobal.h"
#include "xseismicutmtool.h"

CXViewInfoLFMGeometry::CXViewInfoLFMGeometry()
	: CXViewInfoObject()
{
	SetLineColor(Qt::gray);
    SetDisplayTopAndBottomLine(false);
    SetDisplayHorizontalSideLine(false);
    SetDisplayVerticalSideLine(false);
    SetLineSize(1);
	SetVerticalLineSpacing(20);
	SetNeedColormap(false);
}

CXViewInfoLFMGeometry::~CXViewInfoLFMGeometry()
{

}

void CXViewInfoLFMGeometry::SetViewObjectID(const QUuid& objID)
{
	auto pLFM = dynamic_cast<CXLFMGeometry*>(::GetObjectByID(objID));

	CXSeismicUTMTool& utm = pLFM->GetUTM();
	SetMinInline(utm.GetFirstInline());
	SetMaxInline(utm.GetLastInline());
	SetMinCrossline(utm.GetFirstCrossline());
	SetMaxCrossline(utm.GetLastCrossline());
	
	std::vector<int> vecHorizonIndex = pLFM->GetHorizonIndex();
	int nZone = vecHorizonIndex.size() - 1;

	std::vector<bool> vecDisplay(nZone, true);
	SetVecZoneDisplay(vecDisplay);

	std::vector<int> vecMinSlice, vecMaxSlice;
	std::vector<QRgb> vecColor;
	for (int i = 0; i < nZone; ++i)
	{
		vecMinSlice.push_back(vecHorizonIndex.at(i));
		vecMaxSlice.push_back(vecHorizonIndex.at(i + 1));
		vecColor.push_back(::GetCurveColor(i).rgb());
	}
	SetVecZoneMinSlice(vecMinSlice);
	SetVecZoneMaxSlice(vecMaxSlice);
	SetVecZoneColor(vecColor);
}