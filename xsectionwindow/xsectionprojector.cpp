#include "xsectionprojector.h"
#include "xsectionscene.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "x2dseismicline.h"
#include "xseismicdatavolume.h"
#include "xseismicutmtool.h"
#include "xwell.h"
#include "xmath2d.h"

CXSectionProjector::CXSectionProjector(CXSectionScene *pScene)
{
	m_pScene = pScene;
	m_pSection = NULL;
}

CXSectionProjector::CXSectionProjector(CXObject *pSection)
{
	m_pScene = NULL;
	m_pSection = pSection;
}

//	Return -1 means beyond the projection threhold, otherwise return the plane index. 
int CXSectionProjector::WellShouldBeDrawn(CXWell *pWell, float fProjThrehold)
{
	int iIDX = -1;
	unsigned short iNumPlane = getPlaneNumber();
	double dWellX, dWellY;
	pWell->GetWellPosition(dWellX, dWellY);
	if (dWellX == g_dInvalidData || dWellY == g_dInvalidData)
		return iIDX;

	QPointF wellPos(dWellX, dWellY);
	double dLeftX, dLeftY, dRightX, dRightY;
	for (unsigned short i = 0; i < iNumPlane; i++)
	{
		if (!getPlaneEnds(i, dLeftX, dLeftY, dRightX, dRightY))
			continue;

		QPointF footPoint;
		QLineF segment(dLeftX, dLeftY, dRightX, dRightY);

		float fDis = NXMath2D::PointToSegment(wellPos, segment);
		if (fDis <= fProjThrehold)
		{
			iIDX = i;
			fProjThrehold = fDis;
		}
	}

	return iIDX;
}

//	Get the end's trace number of specified plane.
bool CXSectionProjector::GetEndTraceNumber(int iPlaneIDX, float& fLeftTrace, float& fRightTrace)
{
	CXObject *pObj = m_pSection;
	if (!pObj)
	{
		pObj= m_pScene->GetBackgroundSection();
	}
	if (!pObj)
		return false;

	if (iPlaneIDX >= getPlaneNumber())
		return false;

	//	So far random section and 2d line may contain multiple plane.
	if (pObj->GetObjectType() == EXRandomSection)
	{
		CXSeismicRandomSection *pRSection = (CXSeismicRandomSection *)pObj;
		fLeftTrace = pRSection->GetTPTraceIndex(iPlaneIDX);
		fRightTrace = pRSection->GetTPTraceIndex(iPlaneIDX + 1);
	}
	else if (pObj->GetObjectType() == EX2DSeismicLine)
	{
		CX2DSeismicLine *pLine = (CX2DSeismicLine *)pObj;
		QList<int>& listInf = pLine->GetInflexionIndices();
		fLeftTrace = listInf[iPlaneIDX];
		fRightTrace = listInf[iPlaneIDX + 1];
	}
	else if (pObj->GetObjectType() == EXSeismicSection)
	{
		CXSeismicSection *pSection = (CXSeismicSection *)pObj;
		CXSeismicDataVolume *pDV = NULL;
		if (m_pScene)
		{
			pDV = dynamic_cast<CXSeismicDataVolume *>(m_pScene->GetBackgroundSection(false));
		}
		if (!pDV)
			return false;
		CXSeismicUTMTool& utm = pDV->GetUTM();

		if (pSection->GetSectionType() == eInlineSection)
		{
			fLeftTrace = utm.GetFirstCrossline();
			fRightTrace = utm.GetLastCrossline();
		}
		else if (pSection->GetSectionType() == eCrosslineSection)
		{
			fLeftTrace = utm.GetFirstInline();
			fRightTrace = utm.GetLastInline();
		}
		else
		{
			return false;
		}
	}
	else
		return false;

	return true;
}

//	Get a point's projection trace number on a plane.
float CXSectionProjector::GetSubPointTraceNumber(double dX, double dY, int iPlaneIDX)
{
	double dLeftX, dLeftY, dRightX, dRightY;
	getPlaneEnds(iPlaneIDX, dLeftX, dLeftY, dRightX, dRightY);

	QLineF line(dLeftX, dLeftY, dRightX, dRightY);
	float fRatio = NXMath2D::PointProjectionOnSegment(QPointF(dX, dY), line);

	float fLeftTrace, fRightTrace;
	GetEndTraceNumber(iPlaneIDX, fLeftTrace, fRightTrace);

	return fLeftTrace + (fRightTrace - fLeftTrace) * fRatio;
}

unsigned short CXSectionProjector::getPlaneNumber()
{
	CXObject *pObj = m_pSection;
	if (!pObj)
	{
		pObj = m_pScene->GetBackgroundSection();
	}
	if (!pObj)
		return 0;

	//	So far random section and 2d line may contain multiple plane.
	if (pObj->GetObjectType() == EXRandomSection)
	{
		CXSeismicRandomSection *pRSection = (CXSeismicRandomSection *)pObj;
		vector<double> vecX, vecY;
		pRSection->GetXYofTuringPoint(vecX, vecY);
		return vecX.size() - 1;
	}
	else if (pObj->GetObjectType() == EX2DSeismicLine)
	{
		CX2DSeismicLine *pLine = (CX2DSeismicLine *)pObj;
		return pLine->GetInflexionIndices().size() - 1;
	}
	else
		return 1;
}

//	Get the end's coordinates of the given plane.
bool CXSectionProjector::getPlaneEnds(int iIDX, double& dLeftX, double& dLeftY, double& dRightX, double& dRightY)
{
	CXObject *pObj = m_pSection;
	if (!pObj)
	{
		pObj = m_pScene->GetBackgroundSection();
	}
	if (!pObj)
		return false;

	//	So far random section and 2d line may contain multiple plane.
	if (pObj->GetObjectType() == EXRandomSection)
	{
		CXSeismicRandomSection *pRSection = (CXSeismicRandomSection *)pObj;
		vector<double> vecX, vecY;
		pRSection->GetXYofTuringPoint(vecX, vecY);

		if (iIDX >= vecX.size() - 1)
			return false;
		
		dLeftX = vecX[iIDX];
		dLeftY = vecY[iIDX];
		dRightX = vecX[iIDX + 1];
		dRightY = vecY[iIDX + 1];
	}
	else if (pObj->GetObjectType() == EX2DSeismicLine)
	{
		double *pX, *pY;
		CX2DSeismicLine *pLine = (CX2DSeismicLine *)pObj;
		QList<int>& listInf = pLine->GetInflexionIndices();
		pLine->GetCoordData(pX, pY);

		if (iIDX >= listInf.size() - 1)
			return false;

		dLeftX = pX[iIDX];
		dLeftY = pY[iIDX];
		dRightX = pX[iIDX + 1];
		dRightY = pY[iIDX + 1];
	}
	else if (pObj->GetObjectType() == EXSeismicSection)
	{
		CXSeismicSection *pSection = (CXSeismicSection *)pObj;
		CXSeismicDataVolume *pDV = dynamic_cast<CXSeismicDataVolume *>(m_pScene->GetBackgroundSection(false));
		if (!pDV)
			return false;
		CXSeismicUTMTool& utm = pDV->GetUTM();

		double dSectionNum = pSection->GetSectionNumber();
		int iLNum, iRNum;
		if (pSection->GetSectionType() == eInlineSection)
		{
			iLNum = utm.GetFirstCrossline();
			iRNum = utm.GetLastCrossline();

			utm.LineToXY((int)dSectionNum, iLNum, dLeftX, dLeftY);
			utm.LineToXY((int)dSectionNum, iRNum, dRightX, dRightY);
		}
		else if (pSection->GetSectionType() == eCrosslineSection)
		{
			iLNum = utm.GetFirstInline();
			iRNum = utm.GetLastInline();

			utm.LineToXY(iLNum, (int)dSectionNum, dLeftX, dLeftY);
			utm.LineToXY(iRNum, (int)dSectionNum, dRightX, dRightY);
		}
		else
			return false;
	}
	else
		return false;

	return true;
}