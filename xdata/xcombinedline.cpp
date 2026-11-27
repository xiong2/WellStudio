#include <qpolygon.h>
#include <qfile.h>
#include "xcombinedline.h"
#include "xobjectfactory.h"
#include "xglobal.h"
#include "xgraphicsapi.h"
#include "x3dsurvey.h"
#include "x2dseismicline.h"
#include "xregulardatareader.h"
#include "xseismicdatavolume.h"
#include "xseismicdataline.h"
#include "xregulardatareader.h"

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

bool CXCombinedLine::SerializeData(CXArchive& ar)
{
	if (ar.IsSaving())
	{
		ar << m_nSample;
		ar << m_dZStart;
		ar << m_dZStep;
		ar << m_vecSection.size();
		for (const CXOneSection& section : m_vecSection)
		{
			ar << section.m_refID;
			ar << section.m_iOffset;
			ar << section.m_vecInd;
			ar << section.m_coords;
		}
	}
	else
	{
		ar >> m_nSample;
		ar >> m_dZStart;
		ar >> m_dZStep;

		int iSize;
		ar >> iSize;
		m_vecSection.clear();
		for (int i = 0; i < iSize; i++)
		{
			CXOneSection section;
			ar >> section.m_refID;
			ar >> section.m_iOffset;
			ar >> section.m_vecInd;
			ar >> section.m_coords;

			m_vecSection.append(section);
		}
	}

	return true;
}

QStringList CXCombinedLine::GetDescription()
{
	QStringList sList;
	sList << u8"起始时间" << QString::number(m_dZStart, 'f', 0);
	sList << u8"终止时间" << QString::number(m_dZStart + (m_nSample - 1) * m_dZStep, 'f', 0);
	sList << u8"采样间隔" << QString::number(m_dZStep, 'f', 0);
	sList << u8"样点数目" << QString::number(m_nSample);
	sList << u8"剖面数目" << QString::number(m_vecSection.size());

	int nTrace = 0;
	for (CXOneSection section : m_vecSection)
		nTrace += section.m_vecInd.size();

	sList << u8"总道数" << QString::number(nTrace);

	return sList;
}

int CXCombinedLine::GetTraceNumber()
{
	int nTrace = 0;
	for (CXOneSection& section : m_vecSection)
		nTrace += section.m_vecInd.size();

	return nTrace;
}

QPolygonF CXCombinedLine::GetTurnPoints()
{
	QPolygonF polyline;
	if (!m_vecSection.isEmpty())
	{
		polyline << m_vecSection[0].m_coords.first();
		for (CXOneSection& section : m_vecSection)
			polyline << section.m_coords.last();
	}

	return polyline;
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
		return IsLineIntersectSurvey(pLine2, pSurvey1);
	else
		return IsLineIntersectSurvey(pLine1, pSurvey2);

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

bool CXCombinedLine::IsLineIntersectSurvey(CX2DSeismicLine* pLine, CX3DSurvey* pSurvey, QVector<QPointF>* pVecIntersects)
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

	// Only boundary crossings count: a polyline lying entirely inside the
	// rectangle produces no crossing and is therefore not intersecting.
	QVector<QPointF> vecPoints;
	double dX, dY;
	for (unsigned int i = 0; i < numTraces - 1; ++i)
	{
		for (int k = 0; k < 4; ++k)
		{
			int kNext = (k + 1) % 4;

			if (CXGraphicsAPI::IntersectionOfTwoLines(
				pLineX[i], pLineY[i], pLineX[i + 1], pLineY[i + 1],
				dCornerX[k], dCornerY[k], dCornerX[kNext], dCornerY[kNext],
				dX, dY))
			{
				// A vertex sitting on an edge is hit by its two adjacent segments,
				// and a crossing at a corner by the two edges meeting there.
				bool bDuplicate = false;
				for (const QPointF& qExisting : vecPoints)
				{
					if (qAbs(qExisting.x() - dX) < 1.0E-6 && qAbs(qExisting.y() - dY) < 1.0E-6)
					{
						bDuplicate = true;
						break;
					}
				}

				if (!bDuplicate)
					vecPoints << QPointF(dX, dY);
			}
		}
	}

	if (vecPoints.isEmpty())
		return false;

	if (pVecIntersects)
		*pVecIntersects = vecPoints;

	return true;
}

CXCombinedLine* CXCombinedLine::CreateOneInstance(QVector<CXObject *> vecObj, QPolygonF polyline)
{
	if(vecObj.size() < polyline.size() || polyline.size() <= 1)
		return nullptr;

	QVector<CXOneSection> vecSection;
	QVector<float*>	vecBuff;
	CXCombinedLine *pCL = new CXCombinedLine();
	
	QPointF prePoint;
	bool bLast3D = false;
	CX3DSurvey *pLastSurvey = dynamic_cast<CX3DSurvey *>(vecObj[0]);
	CX2DSeismicLine *pLastLine = nullptr;
	double dVal;
	if (pLastSurvey)
	{
		bLast3D = true;
		CXSeismicDataVolume *pDV = pLastSurvey->GetDefaultDV();
		pCL->m_nSample = pDV->GetSamplingQty();
		pDV->GetSamplingRange(pCL->m_dZStart, dVal, pCL->m_dZStep);
	}
	else
	{
		pLastLine = dynamic_cast<CX2DSeismicLine *>(vecObj[0]);
		CXSeismicDataLine *pDLine = pLastLine->GetDefaultSection();
		pCL->m_nSample = pDLine->GetSamplingQty();
		pDLine->GetSamplingRange(pCL->m_dZStart, dVal, pCL->m_dZStep);
	}

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
					//	Two points on different 3D.

				}
				else
				{
					// Still in the same 3D survey.
					QPolygon poly = createOneSegment(pSurvey, polyline[i - 1], polyline[i]);
					CXOneSection section;
					section.m_refID = pLastSurvey->GetObjectID();
					section.m_vecInd = poly;
					float* pData = populateOneSection(section);

					vecSection << section;
					vecBuff << pData;
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
				QVector<QPointF> vecInts;
				if (!IsLineIntersectSurvey(pLine, pLastSurvey, &vecInts))
				{
					qDebug() << "Something error!";
					return nullptr;
				}

				prePoint = vecInts[0];
				QPolygon poly = createOneSegment(pLastSurvey, polyline[i - 1], prePoint);

				CXOneSection section;
				section.m_refID = pLastSurvey->GetObjectID();
				section.m_vecInd = poly;
				float* pData = populateOneSection(section);

				vecSection << section;
				vecBuff << pData;

				pLastSurvey = nullptr;
				pLastLine = pLine;
			}
			else
			{
				//	2D ~2D
			}
		}
	}

	// To finish it.
	if (pLastSurvey)
	{
		//	End in 3D
	}
	else
	{
		//	End on 2D.
		int iIDX1 = pLastLine->PointOnLine(prePoint);
		int iIDX2 = pLastLine->PointOnLine(polyline.last());
		CXOneSection section;
		section.m_refID = pLastLine->GetObjectID();
		float* pData = populateOneSection(section, iIDX1, iIDX2);
		vecSection << section;
		vecBuff << pData;
	}

	int nTotalTrace = 0;
	for (CXOneSection& section : vecSection)
	{
		section.m_iOffset = nTotalTrace * pCL->m_nSample;
		nTotalTrace += section.m_vecInd.size();
	}

	float *pBuff = new float[pCL->m_nSample * nTotalTrace];
	for (int i = 0; i < vecSection.size(); i++)
	{
		memcpy(pBuff + vecSection[i].m_iOffset, vecBuff[i], pCL->m_nSample * vecSection[i].m_vecInd.size() * 4);
		delete[]vecBuff[i];
	}

	pCL->m_vecSection = vecSection;
	pCL->m_pDataInMem = pBuff;
	pCL->_WriteData();

	return pCL;
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

float* CXCombinedLine::populateOneSection(CXOneSection& section, int iIDX1, int iIDX2)
{
	qreal x, y;
	CX3DSurvey *pSurvey = dynamic_cast<CX3DSurvey *>(::GetObjectByID(section.m_refID));
	if (pSurvey)
	{
		CXSeismicDataVolume *pDV = pSurvey->GetDefaultDV();
		CXSeismicUTMTool& utm = pDV->GetUTM();
		for (QPoint p : section.m_vecInd)
		{
			utm.IJToXY(p.x(), p.y(), x, y);
			section.m_coords << QPointF(x, y);
		}

		int nTrace = section.m_vecInd.size();
		int nSample = pDV->GetSamplingQty();
		CXRegularDataReader<float> *pReader = new CXRegularDataReader<float>(pDV->GetTraceFileName(), 
			utm.GetNI(), utm.GetNJ(), nSample);

		float *pData = new float[nTrace * nSample];
		float *pPointer = pData;
		for (int i = 0; i < nTrace; i++)
		{
			pReader->ReadUVTrace(section.m_vecInd[i].x(), section.m_vecInd[i].y(), pPointer);
			pPointer += nSample;
		}

		delete pReader;
		return pData;
	}
	else
	{
		CX2DSeismicLine *pLine = dynamic_cast<CX2DSeismicLine *>(::GetObjectByID(section.m_refID));
		CXSeismicDataLine *pDLine = pLine->GetDefaultSection();

		int nSample = pDLine->GetSamplingQty();
		int nTrace = qAbs(iIDX1 - iIDX2) + 1;
		float *pBuff = new float[nTrace * nSample];

		unsigned int *pCDP = pLine->GetCDPData();
		double *pX, *pY;
		pLine->GetCoordData(pX, pY);
		float *pData = pDLine->GetData();

		if (iIDX1 > iIDX2)
			for (int i = iIDX1, n = 0; i >= iIDX2; i--, n++)
			{
				section.m_vecInd << QPoint(pCDP[i], 0);
				section.m_coords << QPointF(pX[i], pY[i]);
				memcpy(pBuff + n * nSample, pData + i * nSample, nSample * 4);
			}
		else
			for (int i = iIDX1, n = 0; i <= iIDX2; i++, n++)
			{
				section.m_vecInd << QPoint(pCDP[i], 0);
				section.m_coords << QPointF(pX[i], pY[i]);
				memcpy(pBuff + n * nSample, pData + i * nSample, nSample * 4);
			}

		return pBuff;
	}

	return nullptr;
}