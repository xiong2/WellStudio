#include <qdebug.h>
#include "xseismicutmtool.h"
#include "xgeometry.h"
#include "gsstresscalculatemethods.h"
#include "x3dhorizon.h"
#include "gsanticline.h"
#include "gsgeometry.h"
#include "gsstructure.h"
#include "gsstressparameters.h"
#include "gs3dhorizonfaulttraces.h"

QList<GSAnticline *> GSStressCalculateMethods::Calculate(bool bAnti, double dRR, double dLength, double dHeight, double dRadius, unsigned char *pBuff, unsigned char *pMap)
{
	QVector<QVector<double> > vecvecPoints = SearchPoints(bAnti, dHeight, dRadius, pBuff, pMap);

	GSStressParameters para;

	if (bAnti)
		para.m_iAnti[0] = 1;
	else
		para.m_iAnti[0] = 2;
	para.m_dCThreshold[0] = dRR;
	para.m_dLThreshold[0] = dLength;
	para.m_bRemoveOverlap = false;

	return GenerateAnticlines(vecvecPoints, 0, &para);
}

QVector<QVector<double> >  GSStressCalculateMethods::SearchPoints(bool bAnti, double dHeight, double dRadius, unsigned char *pBuff, unsigned char *pMap)
{
	//	Height threshold and searching diameter.
	CXSeismicUTMTool utm = m_pHorizon->GetUTM();
	int i, j, k, nI = utm.GetNI(), nJ = utm.GetNJ();
	int iDataLen = nI * nJ;
	int nCell = dRadius / utm.GetIInterval();
	nCell = nCell < 3 ? 3 : nCell;

	memset(pBuff, 0, iDataLen);
	memset(pMap, 0, iDataLen);

	bool bOK1, bOK2;
	unsigned char ch;
	float *pData = m_pHorizon->GetData();
	float pVal;
	QVector<QVector<double> > 	vecvecPoints;
	QVector<double>vecPoints;

	//	Iterate the isopach to find the anticlines.
	for (i = 0; i < nI; i++)
	{
		for (j = 0; j < nJ; j++)
		{
			ch = 0;
			pVal = pData[i * nJ + j];

			//	Up & down.
			if (calculateOnePoint(i, j, 0, 1, nCell, dHeight, bAnti))
				ch = 1;

			//	Left & right.
			if (calculateOnePoint(i, j, 1, 0, nCell, dHeight, bAnti))
				ch |= 2;

			//	Bottom left & top right.
			if (calculateOnePoint(i, j, 1, 1, nCell, dHeight, bAnti))
				ch |= 4;

			//	Bottom right & top left.
			if (calculateOnePoint(i, j, 1, -1, nCell, dHeight, bAnti))
				ch |= 8;

			pBuff[i * nJ + j] = ch;
		}
	}

	// Flat expand.
	float fHTh = 0.05 * dHeight;
	for (i = 0; i < nI; i++)
	{
		for (j = 0; j < nJ; j++)
		{
			if (pBuff[i * nJ + j] == 0)
				continue;

			flatExpand(i, j, 0, -1, fHTh, pBuff);		//	Left.
			flatExpand(i, j, 0, +1, fHTh, pBuff);		//	Right.
			flatExpand(i, j, +1, 0, fHTh, pBuff);		//	Up.
			flatExpand(i, j, -1, 0, fHTh, pBuff);		//	Down.
			flatExpand(i, j, +1, -1, fHTh, pBuff);		//	Top left.
			flatExpand(i, j, +1, +1, fHTh, pBuff);		//	Top right.
			flatExpand(i, j, -1, -1, fHTh, pBuff);		//	Bottom left.
			flatExpand(i, j, -1, +1, fHTh, pBuff);		//	Bottom right.
		}
	}

	//	Find out the points represent the anticline.
	int iPCount = 0;
	while (true)
	{
		//	To find out the most thin point within the anticlines.
		int iMin = -1, jMin = -1;
		float fZMin = 999999.;
		if (!bAnti)
			fZMin = -99999;

		for (i = 0; i < nI; i++)
		{
			for (j = 0; j < nJ; j++)
			{
				//	Ignore points processed or not anticlines.
				if (pMap[i * nJ + j] || pBuff[i * nJ + j] <= 0)
					continue;

				if ((bAnti && pData[i * nJ + j] < fZMin) || (!bAnti && pData[i * nJ + j] > fZMin))
				{
					fZMin = pData[i * nJ + j];
					iMin = i;
					jMin = j;
				}
			}
		}

		//	No thin point found, finished!
		if (iMin == -1)
			break;

		vecPoints.clear();

		//	Use the thin point as seed, searching!
		findAnticlinePoints(pBuff, pMap, iMin, jMin, vecPoints);

		//	Ignore single point.
		if (vecPoints.size() <= 3)
			continue;

		//	To guarantee all the points has the same direction.
		anticlinePointsDirectionFilter(pMap, vecPoints, dRadius);

		//	Ignore single point.
		if (vecPoints.size() <= 3)
			continue;

		//	If most points closed to the boundary, ignore them.
		int iBoundaryCount = 0;
		for (int i = 0; i < vecPoints.size(); i += 3)
		{
			float fI, fJ;
			utm.XYToIJ(vecPoints[i], vecPoints[i + 1], fI, fJ);
			if (fI < 1 || fI > nI - 1 || fJ < 1 || fJ > nJ - 1)
				iBoundaryCount++;
		}

		if (iBoundaryCount > vecPoints.size() * 0.3)
			continue;

		vecvecPoints << vecPoints;
	}

	return vecvecPoints;
}

//	From a seed point, find out points within one anticline by recursion function.
void GSStressCalculateMethods::findAnticlinePoints(unsigned char *pData, unsigned char *pMap, int i, int j, QVector<double>& vecPoints)
{
	CXSeismicUTMTool utm = m_pHorizon->GetUTM();
	int nI = utm.GetNI(), nJ = utm.GetNJ();

	if (i < 0 || i >= nI || j < 0 || j >= nJ)
		return;

	//	This point has been tracked, or not int anticline.
	if (pMap[i * nJ + j] || pData[i * nJ + j] <= 0)
		return;

	//	Set the point tracked.
	pMap[i * nJ + j] = 1;

	//	Add this point into vector.
	double x, y, z;
	utm.IJToXY(i, j, x, y);
	z = (double)pData[i * nJ + j];
	vecPoints << x << y << z;

	//	Recursion searching in 8 directions.
	findAnticlinePoints(pData, pMap, i + 1, j, vecPoints);				//	Up.
	findAnticlinePoints(pData, pMap, i - 1, j, vecPoints);				//	Down.
	findAnticlinePoints(pData, pMap, i, j - 1, vecPoints);				//	Left.
	findAnticlinePoints(pData, pMap, i, j + 1, vecPoints);				//	Right.
	findAnticlinePoints(pData, pMap, i + 1, j - 1, vecPoints);			//	Top left.
	findAnticlinePoints(pData, pMap, i + 1, j + 1, vecPoints);			//	Top right.
	findAnticlinePoints(pData, pMap, i - 1, j - 1, vecPoints);			//	Bottom left.
	findAnticlinePoints(pData, pMap, i - 1, j + 1, vecPoints);			//	Bottom right.
}

//	To guarantee all the points has the same direction.
void GSStressCalculateMethods::anticlinePointsDirectionFilter(unsigned char *pMap, QVector<double>& vecPoints, float fRadi)
{
	//	No more than 3 points abort!
	if (vecPoints.size() <= 9)
		return;

	int i, iMax = 0, iCount[16];
	memset(iCount, 0, 64);
	CXSeismicUTMTool utm = m_pHorizon->GetUTM();
	int nJ = utm.GetNJ();

	//	Which direction is the most significiant?
	for (i = 0; i < vecPoints.size(); i += 3)
	{
		iCount[(int)(vecPoints[i + 2])]++;
	}

	for (i = 1; i < 16; i++)
	{
		if (iCount[i] > iCount[iMax])
			iMax = i;
	}

	//	The maximum direction may not be one, should combine those greater than 70%.
	float fMax = 0.7 * iCount[iMax];
	for (i = 0; i < 16; i++)
	{
		if (i == iMax)
			continue;

		if (iCount[i] > fMax)
			iMax |= i;
	}

	int iDelCount = 0;
	for (i = vecPoints.size() - 3; i >= 0; i -= 3)
	{
		if (((int)vecPoints[i + 2] & iMax) == 0)
		{
			//	Unset the map to let this point be used by other anticline.
			int m, n;
			utm.XYToIJ(vecPoints[i], vecPoints[i + 1], m, n);
			pMap[m * nJ + n] = 0;

			vecPoints.remove(i, 3);
			iDelCount++;
		}
	}

	//	Check the width constraint.
	XRMA rma;
	double dDis, dMaxDis = -1.;
	while (true)
	{
		//	Construct the rma.
		iMax = -1;
		rma.Clean();
		for (i = 0; i < vecPoints.size(); i += 3)
			rma.Add(vecPoints[i], vecPoints[i + 1]);
		rma.Solve();

		//	Then find the farest point.
		for (i = 0; i < vecPoints.size(); i += 3)
		{
			dDis = qAbs(rma.PointDist(vecPoints[i], vecPoints[i + 1]));
			if (dDis > dMaxDis)
			{
				dMaxDis = dDis;
				iMax = i;
			}
		}

		//	Is the farest point beyond the tolerance?
		if (iMax >= 0 && dMaxDis > fRadi)
		{
			//	Delete the farest point.
			int m, n;
			utm.XYToIJ(vecPoints[iMax], vecPoints[iMax + 1], m, n);
			pMap[m * nJ + n] = 0;

			vecPoints.remove(iMax, 3);
			iDelCount++;
		}
		else
			break;
	}

	if (iDelCount <= 2)
		return;

	//	If more than 2 points be deleted, there's maybe a gap in the points, then we have to delete the small part.
	rma.Clean();
	for (i = 0; i < vecPoints.size(); i += 3)
		rma.Add(vecPoints[i], vecPoints[i + 1]);
	rma.Solve();

	//	Sort the points depend on their projection on rma line.
	std::vector<XVec3d> vecForSort;
	for (i = 0; i < vecPoints.size(); i += 3)
	{
		vecForSort.emplace_back(vecPoints[i], vecPoints[i + 1], vecPoints[i + 2]);
	}
	const XLine2d& rmaLine = rma.Line();
	std::sort(vecForSort.begin(), vecForSort.end(), [&rmaLine](const XVec3d& p1, const XVec3d& p2)
	{
		double t1 = rmaLine.TforXY(p1.x(), p1.y());
		double t2 = rmaLine.TforXY(p2.x(), p2.y());
		return t1 > t2;
	});
	vecPoints.clear();
	for (auto&& p : vecForSort)
	{
		vecPoints.push_back(p.x());
		vecPoints.push_back(p.y());
		vecPoints.push_back(p.z());
	}

	//	Find the largest gap.
	double t0, t1;
	dMaxDis = -1;
	for (i = 0; i < vecPoints.size() - 3; i += 3)
	{
		t0 = rmaLine.TforXY(vecPoints[i], vecPoints[i + 1]);
		t1 = rmaLine.TforXY(vecPoints[i + 3], vecPoints[i + 4]);

		if (qAbs(t1 - t0) > dMaxDis)
		{
			dMaxDis = qAbs(t1 - t0);
			iMax = i;
		}
	}

	//	Gap is big enough to be splited.
	if (dMaxDis > utm.GetIInterval() * 3)
	{
		//	Which parts holds fewer points should be deleted.
		if (i >= vecPoints.size() - i)
		{
			//	Delete later part.
			int j, m, n;
			for (j = i + 3; j < vecPoints.size(); j += 3)
			{
				utm.XYToIJ(vecPoints[j], vecPoints[j + 1], m, n);
				pMap[m * nJ + n] = 0;
			}

			vecPoints.remove(i + 3, vecPoints.size() - i - 3);
		}
		else
		{
			//	Delete former part.
			int j, m, n;
			for (j = 0; j < vecPoints.size(); j += 3)
			{
				utm.XYToIJ(vecPoints[j], vecPoints[j + 1], m, n);
				pMap[m * nJ + n] = 0;
			}
			vecPoints.remove(0, i + 3);
		}
	}
}

QList<GSAnticline *> GSStressCalculateMethods::GenerateAnticlines(QVector<QVector<double> > vecvecPoints, int iShape, GSStressParameters *pParas)
{
	int i;
	bool bAnti = pParas->m_iAnti[iShape] == 1;
	QList<GSAnticline *> listAnti;
	foreach(QVector<double> vecPoints, vecvecPoints)
	{
		//	Now create the anticline.
		XRMA rma;
		for (i = 0; i < vecPoints.size(); i += 3)
			rma.Add(vecPoints[i], vecPoints[i + 1]);
		rma.Solve();
		double t0, t1;
		rma.TRange(&t0, &t1);
		QPointF end0, end1;
		end0.setX(rma.Line().XforT(t0));
		end0.setY(rma.Line().YforT(t0));
		end1.setX(rma.Line().XforT(t1));
		end1.setY(rma.Line().YforT(t1));

		GSAnticline *pAnticline = new GSAnticline(end0, end1, rma.R(), qAbs(t1 - t0), bAnti);
		listAnti << pAnticline;
	}

	//	To remove the smaller anticline of the overlap ones.
	QList<GSAnticline *> listResAnti = listAnti;
	if(pParas->m_bRemoveOverlap)
		listResAnti = removeOverlapAnticlines(listAnti, pParas->m_dTWidth, pParas->m_dORatio);

	//	Wipe out un-qualified anticlines.
	for (i = listResAnti.size() - 1; i >= 0; i--)
	{
		GSAnticline *pAnti = listResAnti.at(i);

		if (pAnti->GetRmaR() < pParas->m_dCThreshold[iShape] || pAnti->GetLength() < pParas->m_dLThreshold[iShape])
		{
			listResAnti.removeAt(i);
			delete pAnti;
		}
	}

	return listResAnti;
}

bool GSStressCalculateMethods::calculateOnePoint(int iRow, int iCol, int iHStep, int iVStep, int iCell, float fHTh, bool bAnti)
{
	int i, j, k;
	bool bOK1 = false, bOK2 = false;
	float *pData = m_pHorizon->GetData();
	CXSeismicUTMTool utm = m_pHorizon->GetUTM();
	int nI = utm.GetNI(), nJ = utm.GetNJ();
	float fVal = pData[iRow * nJ + iCol];
	float fZTol;

	//	Search -
	float fMax = fVal;
	for (k = 1; k < iCell; k++)
	{
		i = iRow - k * iVStep;
		j = iCol - k * iHStep;

		if (i >= nI || j >= nJ)
			continue;

		if (i < 0 || j < 0)
		{
			if (k > 1 && (iHStep == 0 || iVStep == 0))
			{
				fZTol = (k - 1.) / iCell * fHTh;
				if ((bAnti && fMax >= fVal + fZTol) || (!bAnti && fMax <= fVal - fZTol))
				{
					bOK1 = true;
					break;
				}
			}

			continue;
		}

		if ((bAnti && pData[i * nJ + j] < fVal) || (!bAnti && pData[i * nJ + j] > fVal))
			return false;

		if (bAnti)
			fMax = qMax(pData[i * nJ + j], fMax);
		else
			fMax = qMin(pData[i * nJ + j], fMax);

		if ((bAnti && pData[i * nJ + j] > fVal + fHTh) || (!bAnti && pData[i * nJ + j] < fVal - fHTh))
		{
			bOK1 = true;
			break;
		}
	}

	//	Search +
	fMax = fVal;
	for (k = 1; k < iCell; k++)
	{
		i = iRow + k * iVStep;
		j = iCol + k * iHStep;

		if (i < 0 || j < 0)
			continue;

		if (i >= nI || j >= nJ)
		{
			if (k > 1 && (iHStep == 0 || iVStep == 0))
			{
				fZTol = (k - 1.) / iCell * fHTh;
				if ((bAnti && fMax >= fVal + fZTol) || (!bAnti && fMax <= fVal - fZTol))
				{
					bOK2 = true;
					break;
				}
			}

			continue;
		}

		if ((bAnti && pData[i * nJ + j] < fVal) || (!bAnti && pData[i * nJ + j] > fVal))
			return false;

		if (bAnti)
			fMax = qMax(pData[i * nJ + j], fMax);
		else
			fMax = qMin(pData[i * nJ + j], fMax);

		if ((bAnti && pData[i * nJ + j] > fVal + fHTh) || (!bAnti && pData[i * nJ + j] < fVal - fHTh))
		{
			bOK2 = true;
			break;
		}
	}

	return bOK1 && bOK2;
}

void GSStressCalculateMethods::flatExpand(int iRow, int iCol, int iVStep, int iHStep, float fHTh, unsigned char *pBuff)
{
	float *pData = m_pHorizon->GetData();
	CXSeismicUTMTool utm = m_pHorizon->GetUTM();
	int nI = utm.GetNI(), nJ = utm.GetNJ();
	int iFlag;

	int iNRow = iRow + iVStep, iNCol = iCol + iHStep;

	//	Out of range?
	if (iNRow < 0 || iNRow >= nI || iNCol < 0 || iNCol >= nJ)
		return;

	if (pBuff[iRow * nJ + iCol] == 0)
		return;

	if (iVStep == 0)
		iFlag = 2;			//	Left to right.
	else if (iVStep == 1)
	{
		if (iHStep == 0)
			iFlag = 1;		//	Up to down.
		else if (iHStep == 1)
			iFlag = 4;		//	Bottom left to top right.
		else
			iFlag = 8;		//	Bottom right to top left.
	}
	else
	{
		if (iHStep == 0)
			iFlag = 1;		//	Up to down.
		else if (iHStep == 1)
			iFlag = 8;		//	Bottom right to top left.
		else
			iFlag = 4;		//	Bottom left to top right.
	}

	//	Only process points in the same direction.
	if (iFlag & pBuff[iRow * nJ + iCol] == 0)
		return;

	if (qAbs(pData[iRow * nJ + iCol] - pData[iNRow * nJ + iNCol]) < fHTh
		&& pBuff[iNRow * nJ + iNCol] == 0)
	{
		pBuff[iNRow * nJ + iNCol] = pBuff[iRow * nJ + iCol];

		//	Reccur calling.
		flatExpand(iNRow, iNCol, 0, -1, fHTh, pBuff);		//	Left.
		flatExpand(iNRow, iNCol, 0, +1, fHTh, pBuff);		//	Right.
		flatExpand(iNRow, iNCol, +1, 0, fHTh, pBuff);		//	Up.
		flatExpand(iNRow, iNCol, -1, 0, fHTh, pBuff);		//	Down.
		flatExpand(iNRow, iNCol, +1, -1, fHTh, pBuff);		//	Top left.
		flatExpand(iNRow, iNCol, +1, +1, fHTh, pBuff);		//	Top right.
		flatExpand(iNRow, iNCol, -1, -1, fHTh, pBuff);		//	Bottom left.
		flatExpand(iNRow, iNCol, -1, +1, fHTh, pBuff);		//	Bottom right.
	}
}

QList<GSAnticline *> GSStressCalculateMethods::removeOverlapAnticlines(QList<GSAnticline *> listAnti, double dWidth, double dOverlapRatio)
{
	QPointF end0, end1;
	QList<GSAnticline *> listResAnti;
	while (!listAnti.isEmpty())
	{
		GSAnticline *pAnti0 = listAnti.takeLast();
		pAnti0->GetEndPoints(end0, end1);
		QPolygonF polygon0 = GSGeom::CreateCapsule(end0, end1, dWidth);

		for (int i = listAnti.size() - 1; i >= 0; i--)
		{
			GSAnticline *pAnti1 = listAnti.at(i);
			pAnti1->GetEndPoints(end0, end1);
			QPolygonF polygon1 = GSGeom::CreateCapsule(end0, end1, dWidth);
			QPolygonF polygonIntersec = polygon0.intersected(polygon1);

			//	Judge whether the overlap part greater than 30%.
			if (GSGeom::PolygonArea(polygonIntersec) / qMin(GSGeom::PolygonArea(polygon0), GSGeom::PolygonArea(polygon1)) > dOverlapRatio)
			{
				//	Remove the small one.
				if (pAnti0->GetVolume(m_pHorizon) > pAnti1->GetVolume(m_pHorizon))
				{
					listAnti.removeAt(i);
					delete pAnti1;
				}
				else
				{
					delete pAnti0;
					pAnti0 = NULL;
					break;
				}
			}
		}

		if (pAnti0)
			listResAnti << pAnti0;
	}

	return listResAnti;
}

QList<GSAnticline *> GSStressCalculateMethods::RemoveAnticlinesByFaults(QList<GSAnticline *> listAnti, QList<GSStructure *> listFaults, double dLength)
{
	QPointF end0, end1;
	foreach(GSStructure *pStr, listFaults)
	{
		if (pStr->GetFaultLength() < dLength)
			continue;

		for (int i = listAnti.size() - 1; i >= 0; i--)
		{
			GSAnticline *pAnti = listAnti.at(i);
			pAnti->GetEndPoints(end0, end1);
			QPolygonF polygon = GSGeom::CreateCapsule(end0, end1, 2000);
			QPolygonF polygonIntersec = pStr->GetBoundaryPolygon().intersected(polygon);

			if (!polygonIntersec.isEmpty())
			{
				delete pAnti;
				listAnti.removeAt(i);
			}
		}
	}

	return listAnti;
}

QList<GSStructure *> GSStressCalculateMethods::mergeOverlapCapsules(QList<GSStructure *> listCapsule, double dOverlap, double dAngle)
{
	QList<GSStructure *> listResult;
	while (!listCapsule.isEmpty())
	{
		GSStructure *pC1 = listCapsule.takeFirst();

		bool bMerged = true;
		while (bMerged)
		{
			bMerged = false;
			for (int i = listCapsule.size() - 1; i >= 0; i--)
			{
				GSStructure *pC2 = listCapsule[i];
				if (pC1->MergeWith(pC2, dOverlap, dAngle))
				{
					listCapsule.removeAt(i);
					delete pC2;
					bMerged = true;
					break;
				}
			}
		}

		listResult << pC1;
	}

	return listResult;
}


QList<GSStructure *> GSStressCalculateMethods::removeOverlapPart(QList<GSStructure *> listCapsule)
{
	QList<GSStructure *> listResult;
	while (!listCapsule.isEmpty())
	{
		GSStructure *pC1 = listCapsule.takeFirst();

		for(int i = listCapsule.size() - 1; i >= 0; i--)
		{
			GSStructure *pC2 = listCapsule[i];
			pC2->SubtractBoundaryPolygon(pC1);

			//	Nothing remained!
			if(pC2->GetBoundaryPolygon().size() < 3)
				listCapsule.removeAt(i);
		}

		listResult << pC1;
	
		//	Sort the capsules by area first.
		std::sort(listCapsule.begin(), listCapsule.end(), [](GSStructure* pCap1, GSStructure* pCap2) { return pCap1->GreaterThan(pCap2); });
	}

	return listResult;
}

QList<GSStructure *> GSStressCalculateMethods::CreateStructuresByFaults(GSStressParameters *pParas)
{
	QList<GSStructure *> listStr;

	GSFaultTrace *pT1, *pT2, *pT;
	int i, j, iFoundCount;
	QList<CXObject *> listObj = m_pHorizon->GetChildren(EXGSFaultTraces);
	foreach(CXObject *pObj, listObj)
	{
		GS3DHorizonFaultTraces *pFT = (GS3DHorizonFaultTraces *)pObj;
		GS3DHorizonFaultTraces *pDupFT = new GS3DHorizonFaultTraces(*pFT);

		/* Delete ZERO throw segments at the start */
		while (pDupFT->TraceCount() >= 2)
		{
			pT1 = pDupFT->GetTrace(0);
			pT2 = pDupFT->GetTrace(1);
			if (fabs(pT1->m_p1.z() - pT1->m_p2.z()) < 2.5 &&
				fabs(pT2->m_p1.z() - pT2->m_p2.z()) < 2.5)
			{
				/* Set new first throw to zero. */
				pT2->m_p1[2] = pT2->m_p2[2] = (pT2->m_p1.z() + pT2->m_p2.z()) / 2;
				pDupFT->DelTrace(0);
			}
			else
			{
				break;
			}
		}

		/* Delete ZERO throw segments at the end */
		while (pDupFT->TraceCount() >= 2)
		{
			pT1 = pDupFT->GetTrace(pDupFT->TraceCount() - 1);
			pT2 = pDupFT->GetTrace(pDupFT->TraceCount() - 2);
			if (fabs(pT1->m_p1.z() - pT1->m_p2.z()) < 2.5 &&
				fabs(pT2->m_p1.z() - pT2->m_p2.z()) < 2.5)
			{
				/* Set new last throw to zero. */
				pT2->m_p1[2] = pT2->m_p2[2] =
					(pT2->m_p1.z() + pT2->m_p2.z()) / 2;
				pDupFT->DelTrace(pDupFT->TraceCount() - 1);
			}
			else
			{
				break;
			}
		}
		/* Must have at least 2 points. */
		if (pDupFT->TraceCount() < 2)
			continue;

		pDupFT->Reduce(pParas->m_dFLinearity, false);

		for (i = 1; i < pDupFT->TraceCount(); i++)
		{
			pT1 = pDupFT->GetTrace(i - 1);
			pT2 = pDupFT->GetTrace(i);

			/* Work out the segment maximum throw */

			int iCount = 0;
			double dSum = 0, dMaxThrow = -9999;
			iFoundCount = 0;

			for (j = 0; pT = pFT->GetTrace(j); j++)
			{

				/* Is this point one of the segment end points? */
				if ((pT->m_p1.x() == pT1->m_p1.x() && pT->m_p2.x() == pT1->m_p2.x() && pT->m_p1.y() == pT1->m_p1.y() && pT->m_p2.y() == pT1->m_p2.y())
					|| (pT->m_p1.x() == pT2->m_p1.x() && pT->m_p2.x() == pT2->m_p2.x() && pT->m_p1.y() == pT2->m_p1.y() && pT->m_p2.y() == pT2->m_p2.y()))
				{
					iFoundCount++;
				}

				if (iFoundCount < 1)
				{
					continue;
				}
				else
				{
					dSum += qAbs(pT->m_p1.z() - pT->m_p2.z());
					iCount++;
				}

				/* Have we found the second point? */
				if (iFoundCount == 2)
					break;
			}

			if (iFoundCount != 2)
			{
				continue;
			}

			dMaxThrow = dSum / iCount;
			int iType = pFT->ReversePercent() > 0 ? STRUCTURE_REVERSE_FAULT : STRUCTURE_NORMAL_FAULT;
			GSStructure *pCapsule = new GSStructure(iType, pT1->CentrePoint(), pT2->CentrePoint(), dMaxThrow, pFT->ReversePercent() / 100., pFT->Length());
			listStr << pCapsule;
		}
	}

	return listStr;
}

QList<GSStructure *> GSStressCalculateMethods::CreateStructuresByFaults(GSStressParameters *pParas, QList<GS3DHorizonFaultTraces *> listObj)
{
	QList<GSStructure *> listStr;

	GSFaultTrace *pT1, *pT2, *pT;
	int i, j, iFoundCount;
	foreach(GS3DHorizonFaultTraces *pFT, listObj)
	{
		GS3DHorizonFaultTraces *pDupFT = new GS3DHorizonFaultTraces(*pFT);

		/* Delete ZERO throw segments at the start */
		while (pDupFT->TraceCount() >= 2)
		{
			pT1 = pDupFT->GetTrace(0);
			pT2 = pDupFT->GetTrace(1);
			if (fabs(pT1->m_p1.z() - pT1->m_p2.z()) < pParas->m_fThrow &&
				fabs(pT2->m_p1.z() - pT2->m_p2.z()) < pParas->m_fThrow)
			{
				/* Set new first throw to zero. */
				pT2->m_p1[2] = pT2->m_p2[2] = (pT2->m_p1.z() + pT2->m_p2.z()) / 2;
				pDupFT->DelTrace(0);
			}
			else
			{
				break;
			}
		}

		/* Delete ZERO throw segments at the end */
		while (pDupFT->TraceCount() >= 2)
		{
			pT1 = pDupFT->GetTrace(pDupFT->TraceCount() - 1);
			pT2 = pDupFT->GetTrace(pDupFT->TraceCount() - 2);
			if (fabs(pT1->m_p1.z() - pT1->m_p2.z()) < pParas->m_fThrow &&
				fabs(pT2->m_p1.z() - pT2->m_p2.z()) < pParas->m_fThrow)
			{
				/* Set new last throw to zero. */
				pT2->m_p1[2] = pT2->m_p2[2] =
					(pT2->m_p1.z() + pT2->m_p2.z()) / 2;
				pDupFT->DelTrace(pDupFT->TraceCount() - 1);
			}
			else
			{
				break;
			}
		}
		/* Must have at least 2 points. */
		if (pDupFT->TraceCount() < 2)
			continue;

		pDupFT->Reduce(pParas->m_dFLinearity, false);

		for (i = 1; i < pDupFT->TraceCount(); i++)
		{
			pT1 = pDupFT->GetTrace(i - 1);
			pT2 = pDupFT->GetTrace(i);

			/* Work out the segment maximum throw */

			int iCount = 0;
			double dSum = 0, dMaxThrow = -9999;
			iFoundCount = 0;

			for (j = 0; pT = pFT->GetTrace(j); j++)
			{

				/* Is this point one of the segment end points? */
				if ((pT->m_p1.x() == pT1->m_p1.x() && pT->m_p2.x() == pT1->m_p2.x() && pT->m_p1.y() == pT1->m_p1.y() && pT->m_p2.y() == pT1->m_p2.y())
					|| (pT->m_p1.x() == pT2->m_p1.x() && pT->m_p2.x() == pT2->m_p2.x() && pT->m_p1.y() == pT2->m_p1.y() && pT->m_p2.y() == pT2->m_p2.y()))
				{
					iFoundCount++;
				}

				if (iFoundCount < 1)
				{
					continue;
				}
				else
				{
					dSum += qAbs(pT->m_p1.z() - pT->m_p2.z());
					iCount++;
				}

				/* Have we found the second point? */
				if (iFoundCount == 2)
					break;
			}

			if (iFoundCount != 2)
			{
				continue;
			}

			dMaxThrow = dSum / iCount;
			GSStructure *pCapsule = new GSStructure(2, pT1->CentrePoint(), pT2->CentrePoint(), dMaxThrow, pFT->ReversePercent() / 100., pFT->Length(), pParas->m_iLWRatio);
			int iFaultType = pFT->GetStatus();
			if (iFaultType == 4)
			{
				if(pFT->ReversePercent() > 0.6)
					iFaultType = 3;
				else if(pFT->ReversePercent() < 0.3)
					iFaultType = 0;
				else iFaultType = 1;
			}
			pCapsule->SetFaultType(iFaultType);

			listStr << pCapsule;
		}
	}

	return listStr;
}

QList<GSStructure *> GSStressCalculateMethods::StructuresAdjust(QList<GSStructure *>& listStr, GSStressParameters *pParas)
{
	int i;
	//	Sort the capsules by area first.
	std::sort(listStr.begin(), listStr.end(), [](GSStructure* pCap1, GSStructure* pCap2) { return pCap1->GreaterThan(pCap2); });

	//	Delete too short fault structures.
	for (i = listStr.size() - 1; i >= 0; i--)
	{
		GSStructure *pStr = listStr[i];
		if (pStr->GetFaultLength() > 0. && pStr->GetLength() < pParas->m_dMinFLength)
		{
			listStr.removeAt(i);
			delete pStr;
		}
	}

	if(listStr.isEmpty())
		return listStr;

	if (pParas->m_bMerge)
	{
		listStr = mergeOverlapCapsules(listStr, pParas->m_dMergeRatio, pParas->m_iMergeAngle);
	}

	//	Sort the capsules by area first.
	std::sort(listStr.begin(), listStr.end(), [](GSStructure* pCap1, GSStructure* pCap2) { return pCap1->GreaterThan(pCap2); });

	//	Remove overlap part of the capsules.
	listStr = removeOverlapPart(listStr);

	//	Adjust the type.
	foreach(GSStructure *pStr, listStr)
	{
		int iFType = pStr->GetFaultType();
		int iType = pStr->GetType();

		if (iFType != 4)
		{
			//	Manually specified!
			if (iFType == 0)
			{
				pStr->SetMagState(MAG_NORMAL);
				pStr->SetAdjMagState(MAG_NORMAL);
			}
			else if (iFType == 3)
			{
				pStr->SetMagState(MAG_REVERSE);
				pStr->SetAdjMagState(MAG_REVERSE);
			}
			else
			{
				pStr->SetMagState(MAG_SS);
				pStr->SetAdjMagState(MAG_SS);
			}
		}
		else if (iType == STRUCTURE_REVERSE_FAULT)
		{
			if (pStr->GetLength() > 5000.)
			{
				pStr->SetMagState(MAG_REVERSE);
				pStr->SetAdjMagState(MAG_REVERSE);
			}
			else
			{
				pStr->SetMagState(MAG_CSS);
				pStr->SetAdjMagState(MAG_CSS);
			}

			double dReverseFrac = pStr->GetRevFraction();
			if (pParas->m_bAdjReverse && dReverseFrac > 0.)
			{
				if (dReverseFrac < pParas->m_dNormF)
					pStr->SetAdjMagState(MAG_NORMAL);
				else if (dReverseFrac < pParas->m_dESSF)
					pStr->SetAdjMagState(MAG_ESS);
				else if (dReverseFrac < pParas->m_dSSF)
					pStr->SetAdjMagState(MAG_SS);
				else if (dReverseFrac < pParas->m_dCSSF)
					pStr->SetAdjMagState(MAG_CSS);
			}
		}
		else if (iType == STRUCTURE_NORMAL_FAULT)
		{
			pStr->SetMagState(MAG_NORMAL);
			pStr->SetAdjMagState(MAG_NORMAL);
		}
		else if (iType == STRUCTURE_SYNCLINE || iType == STRUCTURE_ANTICLINE)
		{
			if (pStr->HasNabour(listStr, 5000.))
			{
				pStr->SetMagState(MAG_SS);
				pStr->SetAdjMagState(MAG_SS);
			}
			else
			{
				pStr->SetMagState(MAG_UPLIFT);
				pStr->SetAdjMagState(MAG_UPLIFT);
			}
		}
		else if(iType != STRUCTURE_SPE_FAULT)
		{
			qDebug() << "Someting error about the magnitude state!";
		}

		if(pStr->GetMagState() < pParas->m_iLowestStatus)
			pStr->SetMagState(pParas->m_iLowestStatus);
		if(pStr->GetAdjMagState() < pParas->m_iLowestStatus)
			pStr->SetAdjMagState(pParas->m_iLowestStatus);
	}

	//	Sort again.
	std::sort(listStr.begin(), listStr.end(), [](GSStructure* pCap1, GSStructure* pCap2) { return pCap1->GreaterThan(pCap2); });

	//	Group them.
	QList<GSStructure *> listDup = listStr;
	GSStructure *pStr = listDup.takeFirst();
	while (!listDup.isEmpty())
	{
		pStr->Grouping(listDup);

		if(!listDup.isEmpty())
			pStr = listDup.takeFirst();
	}

	for (i = 0; i < listStr.size(); i++)
	{
		GSStructure *pStr = listStr[i];

		if (pStr->GetType() == STRUCTURE_ANTICLINE || pStr->GetType() == STRUCTURE_SYNCLINE)
		{
			if (pStr->GetMagState() == MAG_UPLIFT)
			{
				GSStructure *pHStr = pStr->FindHigherStructure(listStr, pParas->m_iMergeAngle);
				if (pHStr)
					pStr->SetMagState(pHStr->GetMagState());
			}
		}
	}

	return listStr;
}