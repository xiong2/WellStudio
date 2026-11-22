#include <qpolygon.h>
#include "xcombinedline.h"
#include "xobjectfactory.h"
#include "xglobal.h"
#include "xgraphicsapi.h"
#include "x3dsurvey.h"
#include "x2dseismicline.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXCombinedLine)
EXCombinedLine
END_REGISTER_OBJECT_TO_FACTORY(CXCombinedLine)

CXCombinedLine::CXCombinedLine(QString sLineName) : CXObject(sLineName)
{
	SetObjectType(EXCombinedLine);
	SetIconName("CombinedLine.png");
}

bool CXCombinedLine::IsTwoObjectIntersect(CXObject* pObj1, CXObject* pObj2)
{
	CX3DSurvey* pSurvey1 = dynamic_cast<CX3DSurvey *>(pObj1);
	CX2DSeismicLine* pLine1 = dynamic_cast<CX2DSeismicLine *>(pObj1);
	if (!pSurvey1 && !pLine1)
		return false;

	CX3DSurvey* pSurvey2 = dynamic_cast<CX3DSurvey *>(pObj2);
	CX2DSeismicLine* pLine2 = dynamic_cast<CX2DSeismicLine *>(pObj2);
	if (!pSurvey2 && !pLine2)
		return false;

	if (pSurvey1 && pSurvey2)
		return isTwoSurveyIntersect(pSurvey1, pSurvey2);
	else if (pLine1 && pLine2)
		return pLine1->IsIntersected(pLine2);
	else if (pSurvey1)
		return isLineIntersectSurvey(pLine2, pSurvey1);
	else
		return isLineIntersectSurvey(pLine1, pSurvey2);

	return false;
}

bool CXCombinedLine::isTwoSurveyIntersect(CX3DSurvey* pSurvey1, CX3DSurvey* pSurvey2)
{

	int iFI, iLI, iFX, iLX;
	double x1, y1, x2, y2, x3, y3, x4, y4;
	QPolygonF polygon1, polygon2;

	CXSeismicUTMTool& utm = pSurvey1->GetUTM();
	iFI = utm.GetFirstInline();
	iLI = utm.GetLastInline();
	iFX = utm.GetFirstCrossline();
	iLX = utm.GetLastCrossline();
	utm.LineToXY(iFI, iFX, x1, y1);
	utm.LineToXY(iFI, iLX, x2, y2);
	utm.LineToXY(iLI, iLX, x3, y3);
	utm.LineToXY(iLI, iFX, x4, y4);
	polygon1 << QPointF(x1, y1) << QPointF(x2, y2) << QPointF(x3, y3) << QPointF(x4, y4);

	CXSeismicUTMTool& utm2 = pSurvey2->GetUTM();
	iFI = utm2.GetFirstInline();
	iLI = utm2.GetLastInline();
	iFX = utm2.GetFirstCrossline();
	iLX = utm2.GetLastCrossline();
	utm2.LineToXY(iFI, iFX, x1, y1);
	utm2.LineToXY(iFI, iLX, x2, y2);
	utm2.LineToXY(iLI, iLX, x3, y3);
	utm2.LineToXY(iLI, iFX, x4, y4);
	polygon2 << QPointF(x1, y1) << QPointF(x2, y2) << QPointF(x3, y3) << QPointF(x4, y4);

	return polygon1.intersects(polygon2);
}

bool CXCombinedLine::isLineIntersectSurvey(CX2DSeismicLine* pLine, CX3DSurvey* pSurvey)
{
	if (pLine == NULL || pSurvey == NULL)
		return false;

	unsigned int numTraces = pLine->GetTraceNumber();
	if (numTraces == 0)
		return false;

	double* pLineX = NULL;
	double* pLineY = NULL;
	pLine->GetCoordData(pLineX, pLineY);

	// The survey is represented by a rotated rectangle on the plane
	CXSeismicUTMTool& utm = pSurvey->GetUTM();

	int iFI = utm.GetFirstInline();
	int iLI = utm.GetLastInline();
	int iFX = utm.GetFirstCrossline();
	int iLX = utm.GetLastCrossline();

	double dCornerX[4], dCornerY[4];
	utm.LineToXY(iFI, iFX, dCornerX[0], dCornerY[0]);
	utm.LineToXY(iFI, iLX, dCornerX[1], dCornerY[1]);
	utm.LineToXY(iLI, iLX, dCornerX[2], dCornerY[2]);
	utm.LineToXY(iLI, iFX, dCornerX[3], dCornerY[3]);

	// Early rejection with the bounding boxes
	double dSurveyMinX = qMin(qMin(dCornerX[0], dCornerX[1]), qMin(dCornerX[2], dCornerX[3]));
	double dSurveyMaxX = qMax(qMax(dCornerX[0], dCornerX[1]), qMax(dCornerX[2], dCornerX[3]));
	double dSurveyMinY = qMin(qMin(dCornerY[0], dCornerY[1]), qMin(dCornerY[2], dCornerY[3]));
	double dSurveyMaxY = qMax(qMax(dCornerY[0], dCornerY[1]), qMax(dCornerY[2], dCornerY[3]));

	double dLineMinX, dLineMaxX, dLineMinY, dLineMaxY, dZMin, dZMax;
	pLine->GetDimension(dLineMinX, dLineMaxX, dLineMinY, dLineMaxY, dZMin, dZMax);

	if (dLineMaxX < dSurveyMinX || dSurveyMaxX < dLineMinX
		|| dLineMaxY < dSurveyMinY || dSurveyMaxY < dLineMinY)
		return false;

	QPolygonF polygon;
	polygon << QPointF(dCornerX[0], dCornerY[0]) << QPointF(dCornerX[1], dCornerY[1])
		<< QPointF(dCornerX[2], dCornerY[2]) << QPointF(dCornerX[3], dCornerY[3]);

	// The line intersects the survey if one of its vertices lies inside the rectangle
	for (unsigned int i = 0; i < numTraces; ++i)
	{
		if (polygon.containsPoint(QPointF(pLineX[i], pLineY[i]), Qt::OddEvenFill))
			return true;
	}

	// ... or if one of its segments crosses an edge of the rectangle
	for (unsigned int i = 0; i < numTraces - 1; ++i)
	{
		for (int k = 0; k < 4; ++k)
		{
			int kNext = (k + 1) % 4;

			if (CXGraphicsAPI::AreTwoLineSegmentsIntersecting(
				pLineX[i], pLineY[i], pLineX[i + 1], pLineY[i + 1],
				dCornerX[k], dCornerY[k], dCornerX[kNext], dCornerY[kNext]))
				return true;
		}
	}

	return false;
}