#pragma once

class CX3DSurvey;
class QPolygonF;
class QPointF;
class GSSection;
class GSPDG;

namespace NGSTreeNodeCreator
{
	GSSection* CreateSection(CX3DSurvey* pSurvey, const QPolygonF& polyline);
	GSPDG* CreatePDG(CX3DSurvey* pSurvey, const QPointF& point);
}	