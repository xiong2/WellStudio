#include "xsurfaceapi.h"
#include "x3dhorizon.h"
#include "xglobal.h"
#include <cmath>
#include "xmathmacro.h"
#include "xutility.h"
#include "xgraphicsapi.h"


CX3DHorizon* CXSurfaceAPI::InterpolateWithUTM(CX3DHorizon* p3DHorizon, CXSeismicUTMTool* pUTMTool)
{
	if (!p3DHorizon || !pUTMTool)
		return NULL;

	CXSeismicUTMTool& utm = p3DHorizon->GetUTM();
	if (!utm.IsIntersecting(pUTMTool))
		return NULL;

	CX3DHorizon* p3DNewHorizon = new CX3DHorizon(p3DHorizon->GetSurveyID(), *pUTMTool, "New");
	int nJNew = pUTMTool->GetNJ();
	int nI = utm.GetNI();
	int nJ = utm.GetNJ();
	float* pData = p3DHorizon->GetData();
	float* pNewData = p3DNewHorizon->GetData();
	if (!pData || !pNewData)
	{
		delete p3DNewHorizon;
		return NULL;
	}

	float fInvalid = (float)::g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);
	int iInline, iXline, iI, iJ;
	for (int i = 0; i < nI; ++i)
	{
		for (int j = 0; j < nJ; ++j)
		{
			if (qAbs(pData[i*nJ + j] - fInvalid) < fInvalidEPS)
				continue;

			utm.IJToLine(i, j, iInline, iXline);
			if (!pUTMTool->LineToIJ(iInline, iXline, iI, iJ))
				continue;

			pNewData[iI*nJNew + iJ] = pData[i*nJ + j];
		}
	}

	Interpolate(p3DNewHorizon);

	return p3DNewHorizon;
}

void CXSurfaceAPI::Interpolate(CX3DSurface* p3DSurface)
{
	if (!p3DSurface)
		return;

	int nJ = p3DSurface->GetUTM().GetNJ();
	int nI = p3DSurface->GetUTM().GetNI();
	float fInvalid = (float)::g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);
	float *pTargetData = p3DSurface->GetData();

	int i, j, iPlus, jPlus;
	float fData, fIPlusData, fJPlusData;
	bool bBreak = false;

	// find the first valid i and j
	int iValidIndex = -1, jValidIndex = -1;
	for (i = 0; i < nI; ++i)
	{
		if (bBreak)
			break;
		for (j = 0; j<nJ; ++j)
		{
			fData = pTargetData[i* nJ + j];
			if (qAbs(fData - fInvalid) > fInvalidEPS)
			{
				iValidIndex = i;
				jValidIndex = j;
				bBreak = true;
				break;
			}
			// j plus
			jPlus = j + 1;
			if (jPlus < nJ)
			{
				fJPlusData = pTargetData[i* nJ + jPlus];
				while (qAbs(fJPlusData - fInvalid) < fInvalidEPS)
				{
					if (++jPlus < nJ)
						fJPlusData = pTargetData[i* nJ + jPlus];
					else
						break;
				}
			}
			// i plus
			iPlus = i + 1;
			if (iPlus < nI)
			{
				fIPlusData = pTargetData[iPlus* nJ + j];
				while (qAbs(fIPlusData - fInvalid) < fInvalidEPS)
				{
					if (++iPlus < nI)
						fIPlusData = pTargetData[iPlus* nJ + j];
					else
						break;
				}
			}
			// break
			if (iPlus < nI && jPlus < nJ)
			{
				iValidIndex = i;
				jValidIndex = j;
				bBreak = true;
				break;
			}
		}
	}

	if (iValidIndex == -1 || jValidIndex == -1)
		return;

	// Interpolation
	_Interpolation(pTargetData, nI, nJ, true, iValidIndex, jValidIndex);

	// The rest
	_Interpolation(pTargetData, nI, nJ, false, iValidIndex, jValidIndex);

	p3DSurface->SetModifiedFlag();
}

void CXSurfaceAPI::_Interpolation(float* pTargetData, int nI, int nJ, bool bWithValidIndex, int iValidIndex, int jValidIndex)
{
	float fInvalid = (float)g_dInvalidData;
	float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);
	int iPlus, iMinus, jPlus, jMinus, nIMinusLen, nIPlusLen, nJMinusLen, nJPlusLen;
	float fData, fTargetData, fIMinusData, fIPlusData, fJPlusData, fJMinusData, fILen, fJLen;
	bool bIMinus, bIPlus, bJMinus, bJPlus;

	int nII, nJJ;
	if (bWithValidIndex)
	{
		nII = nI;
		nJJ = nJ;
	}
	else
	{
		nII = iValidIndex;
		nJJ = jValidIndex;
	}

	for (int i = 0; i < nI; ++i)
	{
		for (int j = 0; j<nJ; ++j)
		{
			bIMinus = bIPlus = bJMinus = bJPlus = false;

			fData = pTargetData[i* nJ + j];
			if (qAbs(fData - fInvalid) > fInvalidEPS)
				continue;

			if (bWithValidIndex)
			{
				if (i < iValidIndex && j < jValidIndex)
					continue;
			}

			// J plus
			jPlus = j + 1;
			if (jPlus < nJ)
			{
				fJPlusData = pTargetData[i* nJ + jPlus];
				while (qAbs(fJPlusData - fInvalid) < fInvalidEPS)
				{
					if (++jPlus < nJ)
						fJPlusData = pTargetData[i* nJ + jPlus];
					else
						break;
				}
				if (jPlus < nJ)
				{
					nJPlusLen = jPlus - j;
					bJPlus = true;
				}
			}
			// J minus
			jMinus = j - 1;
			if (jMinus >= 0)
			{
				fJMinusData = pTargetData[i* nJ + jMinus];
				if (qAbs(fJMinusData - fInvalid) > fInvalidEPS)
				{
					nJMinusLen = 1;
					bJMinus = true;
				}
			}
			// I plus
			iPlus = i + 1;
			if (iPlus < nI)
			{
				fIPlusData = pTargetData[iPlus* nJ + j];
				while (qAbs(fIPlusData - fInvalid) < fInvalidEPS)
				{
					if (++iPlus < nI)
						fIPlusData = pTargetData[iPlus* nJ + j];
					else
						break;
				}
				if (iPlus < nI)
				{
					nIPlusLen = iPlus - i;
					bIPlus = true;
				}
			}
			// I minus
			iMinus = i - 1;
			if (iMinus >= 0)
			{
				fIMinusData = pTargetData[iMinus* nJ + j];
				if (qAbs(fIMinusData - fInvalid) > fInvalidEPS)
				{
					nIMinusLen = 1;
					bIMinus = true;
				}
			}

			// Linear interpolation
			fTargetData = 0.0f;
			fILen = static_cast<float>(nIMinusLen + nIPlusLen);
			if (bIMinus && bIPlus)
				fTargetData = (fIMinusData*nIPlusLen + fIPlusData*nIMinusLen) / fILen;
			else if (bIMinus)
				fTargetData = fIMinusData;
			else if (bIPlus)
				fTargetData = fIPlusData;

			fJLen = static_cast<float>(nJMinusLen + nJPlusLen);

			if (bJMinus && bJPlus)
				fTargetData += (fJMinusData*nJPlusLen + fJPlusData*nJMinusLen) / fJLen;
			else if (bJMinus)
				fTargetData += fJMinusData;
			else if (bJPlus)
				fTargetData += fJPlusData;

			if ((bIMinus || bIPlus) && (bJMinus || bJPlus))
				fTargetData /= 2.0f;

			pTargetData[i* nJ + j] = fTargetData;
		}
	}

}

bool CXSurfaceAPI::CalcWellHorizonIntersection(vector<double>& vecX, vector<double>& vecY, vector<double>& vecZ, CXUTMTool& utm, float* pData, vector<double>& vecXYZ)
{
	if (!pData || vecX.empty() || vecY.empty() || vecZ.empty())
		return false;

	int nI = utm.GetNI();
	int nJ = utm.GetNJ();
	int nSize = nI*nJ;
	int nLength = (int)vecX.size();

	// find horizon z range
	double dzminhor(M_FLT_MAX), dzmaxhor(M_FLT_NEGATIVEMAX);
	for (int i = 0; i < nSize; ++i)
	{
		dzminhor = qMin(dzminhor, (double)pData[i]);
		dzmaxhor = qMax(dzmaxhor, (double)pData[i]);
	}

	CXVector3D p1, p2, pInter;
	double x[4], y[4];
	CXVector3D v1, v2, v3, v4;

	float fI1, fJ1, fI2, fJ2;
	int iIMin, iIMax, iJMin, iJMax;
	for (int k = 0; k < nLength - 1; ++k)
	{
		p1.SetValue(vecX[k], vecY[k], vecZ[k]);
		p2.SetValue(vecX[k + 1], vecY[k + 1], vecZ[k + 1]);

		if (dzminhor < qMax(p1[2], p2[2]) || dzmaxhor < qMin(p1[2], p2[2]))
			continue;

		// range
		utm.XYToIJ(p1[0], p1[1], fI1, fJ1);
		utm.XYToIJ(p2[0], p2[1], fI2, fJ2);

		iIMin = (int)floor(qMin(fI1, fI2));
		iIMax = (int)ceil(qMax(fI1, fI2));
		iJMin = (int)floor(qMin(fJ1, fJ2));
		iJMax = (int)ceil(qMax(fJ1, fJ2));

		for (int i = iIMin; i < iIMax; ++i)
		{
			for (int j = iJMin; j < iJMax; ++j)
			{
				// (0, 0) -> (1, 0) -> (1, 1) -> (0, 1)
				utm.IJToXY(i, j, x[0], y[0]);
				utm.IJToXY(i + 1, j, x[1], y[1]);
				utm.IJToXY(i + 1, j + 1, x[2], y[3]);
				utm.IJToXY(i, j + 1, x[4], y[4]);

				v1.SetValue(x[0], y[0], pData[i*nJ + j]);
				v2.SetValue(x[1], y[1], pData[(i + 1)*nJ + j]);
				v3.SetValue(x[2], y[2], pData[(i + 1)*nJ + j + 1]);
				v4.SetValue(x[3], y[3], pData[i*nJ + j + 1]);

				if (CXGraphicsAPI::IntersectLineSegmentAndTriangle(v1, v2, v3, p1, p2, pInter) ||
					CXGraphicsAPI::IntersectLineSegmentAndTriangle(v1, v3, v4, p1, p2, pInter))
				{
					vecXYZ.push_back(pInter[0]);
					vecXYZ.push_back(pInter[1]);
					vecXYZ.push_back(pInter[2]);
					return true;
				}
			}
		}

	}

	return false;
}

