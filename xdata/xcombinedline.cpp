#include <qpolygon.h>
#include <qfile.h>
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

CXCombinedLine::~CXCombinedLine()
{
	_freeMemory();
}

int CXCombinedLine::GetTraceNumber()
{
	int nTrace = 0;
	for (CXOneSection& section : m_vecSection)
		nTrace += section.m_vecI1.size();

	return nTrace;
}

void CXCombinedLine::_WriteData()
{
	if (!m_pDataInMem)
		return;

	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::WriteOnly))
		return;

	qFile.write((char*)m_pDataInMem, sizeof(float) * m_nSample * GetTraceNumber());
}

void CXCombinedLine::_ReadData()
{
	QString strFileName = GetDataFileName();
	QFile qFile(strFileName);
	if (!qFile.open(QIODevice::ReadOnly))
		return;

	_freeMemory();

	unsigned int nSize = m_nSample * GetTraceNumber();
	m_pDataInMem = new float[nSize];

	qFile.read((char*)m_pDataInMem, sizeof(float) * nSize);
}

void CXCombinedLine::_freeMemory()
{
	if (m_pDataInMem)
		delete[]m_pDataInMem;

	m_pDataInMem = nullptr;
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

CXCombinedLine* CXCombinedLine::CreateOneInstance(QVector<CXObject *> vecObj, QPolygonF polyline)
{
	if(vecObj.size() < polyline.size() || polyline.size() <= 1)
		return nullptr;

	QPolygon polyIndices;
	bool bLast3D = false;
	CX3DSurvey *pLastSurvey = dynamic_cast<CX3DSurvey *>(vecObj[0]);
	CX2DSeismicLine *pLastLine = nullptr;
	if (pLastSurvey)
	{
		bLast3D = true;
	}
	else
		pLastLine = dynamic_cast<CX2DSeismicLine *>(vecObj[0]);

	for (int i = 1; i < polyline.size(); i++)
	{
		CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey *>(vecObj[i]);
		CX2DSeismicLine *pLine = dynamic_cast<CX2DSeismicLine *>(vecObj[i]);
		if (pSurvey)
		{
			if (pLastSurvey)
			{
				//	3D ~ 3D.
				if (pLastSurvey != pSurvey)
				{
					//	Two points on 3D survey, the same?

				}
				else
				{
					// Still in the same 3D survey.
					polyIndices += createOneSegment(pSurvey, polyline[i - 1], polyline[i]);
				}
			}
			else
			{
				//	2D ~ 3D.
			}
		}
		else
		{
			if (pLastSurvey)
			{
				//	3D ~ 2D
			}
			else
			{
				//	2D ~2D
			}
		}
	}

	return nullptr;
}

QPolygon CXCombinedLine::createOneSegment(CX3DSurvey* pSurvey, QPointF p1, QPointF p2)
{
	int m, n, i1, j1, i2, j2;
	CXSeismicUTMTool& utm = pSurvey->GetUTM();
	utm.XYToIJ(p1.x(), p1.y(), i1, j1);
	utm.XYToIJ(p2.x(), p2.y(), i2, j2);

	QPolygon poly;
	if (qAbs(i2 - i1) >= qAbs(j2 - j1))
	{
		float fDelta = 1. * (j2 - j1) / (i2 - i1);
		float fSum = fDelta;
		int iInc = i2 > i1 ? 1 : -1;
		for(m = i1; m != i2; m += iInc)
		{
			n = (int)(j1 + fSum);
			poly << QPoint(m, n);
			
			fSum += fDelta;
		}
	}
	else
	{
		float fDelta = 1. * (i2 - i1) / (j2 - j1);
		float fSum = fDelta;
		int iInc = j2 > j1 ? 1 : -1;
		for (n = j1; n != j2; n += iInc)
		{
			m = (int)(i1 + fSum);
			poly << QPoint(m, n);

			fSum += fDelta;
		}
	}

	return poly;
}