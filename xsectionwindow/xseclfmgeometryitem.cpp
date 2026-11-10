#include "xseclfmgeometryitem.h"
#include "xlfmgeometry.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xglobal.h"
#include "xviewinfolfmgeometry.h"
#include "xcoordtransformer.h"

CXSecLFMGeometryItem::CXSecLFMGeometryItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent) :CXAbstractItem(pWindow)
{
	setZValue(2);
}

CXSecLFMGeometryItem::~CXSecLFMGeometryItem(void)
{
}

void CXSecLFMGeometryItem::_UpdateData()
{
	m_vecDataLines.clear();
	m_vecDrawLines.clear();

	CXLFMGeometry *pLFMGeometry = dynamic_cast<CXLFMGeometry *>(GetItemObject());
	if (pLFMGeometry == NULL)
	{
		return;
	}

	CXSeismicUTMTool& lfmUTM = pLFMGeometry->GetUTM();
	int nK = pLFMGeometry->GetNK();
	int nI = lfmUTM.GetNI();
	int nJ = lfmUTM.GetNJ();
	int i, j, k, iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc;

	CXObject* pCurSection = m_pSectionWindow->GetCurrentGeometryObj();
	CXSeismicSection* pSeismicSection = dynamic_cast<CXSeismicSection*>(pCurSection);
	CXSeismicRandomSection* pRandomSection = dynamic_cast<CXSeismicRandomSection*>(pCurSection);

	if (pSeismicSection != NULL)
	{
		CXSeismicUTMTool sUTM = pSeismicSection->GetUTM();
		sUTM.GetLineNumRange(iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc);
		int iSectionNumber = (int)pSeismicSection->GetSectionNumber();
		if (pSeismicSection->GetSectionType() == eInlineSection)
		{
			float *pBuffer = new float[nK * nJ];
			lfmUTM.LineToIJ(iSectionNumber, 1, i, j);

			if (!pLFMGeometry->ReadOneSection(i, pBuffer))
			{
				delete[]pBuffer;
				return;
			}

			for (k = 0; k < nK; k++)
			{
				QPolygonF polygonF;
				for (int iXline = iSXline; iXline <= iEXline; iXline += iXlineInc)
				{
					if (!lfmUTM.LineToIJ(iSectionNumber, iXline, i, j))
						continue;

					if (pBuffer[k * nJ + j] == g_dInvalidData)
					{
						if (polygonF.isEmpty())
							continue;
						else
							break;
					}

					polygonF << QPointF(iXline, pBuffer[k * nJ + j]);
				}

				if (!polygonF.isEmpty())
					m_vecDataLines << polygonF;
			}

			delete[]pBuffer;
		}
		else if (pSeismicSection->GetSectionType() == eCrosslineSection)
		{
			lfmUTM.LineToIJ(1, iSectionNumber, i, j);
			if (j < 0 || j >= nJ)
				return;

			float *pBuffer = new float[nI * nJ];
			for (k = 0; k < nK; k++)
			{
				pLFMGeometry->ReadOneSlice(k, pBuffer);

				QPolygonF polygonF;
				for (int iInline = iSInline; iInline <= iEInline; iInline += iInlineInc)
				{
					if (!lfmUTM.LineToIJ(iInline, iSectionNumber, i, j))
						continue;

					if (pBuffer[i * nJ + j] == g_dInvalidData)
					{
						if (polygonF.isEmpty())
							continue;
						else
							break;
					}

					polygonF << QPointF(iInline, pBuffer[i * nJ + j]);
				}

				if (!polygonF.isEmpty())
					m_vecDataLines << polygonF;
			}

			delete []pBuffer;
		}
	}
	else if (pRandomSection != NULL)
	{
		std::vector<int> vecInlineNum, vecXlineNum;
		pRandomSection->GetLineNumbers(vecInlineNum, vecXlineNum);
		int iSize = vecInlineNum.size();
		float *pBuffer = new float[nI * nJ];

		for (k = 0; k < nK; k++)
		{
			pLFMGeometry->ReadOneSlice(k, pBuffer);

			QPolygonF polygonF;
			for (int m = 0; m < iSize; ++m)
			{
				if (!lfmUTM.LineToIJ(vecInlineNum[m], vecXlineNum[m], i, j))
					continue;

				if (pBuffer[i * nJ + j] == g_dInvalidData)
				{
					if (polygonF.isEmpty())
						continue;
					else
						break;
				}

				polygonF << QPointF(m, pBuffer[i * nJ + j]);
			}

			if (!polygonF.isEmpty())
				m_vecDataLines << polygonF;
		}

		delete[]pBuffer;
	}

	MapToScene();
}

void CXSecLFMGeometryItem::MapToScene()
{
	CXSectionScene* pScene = (CXSectionScene*)scene();
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);
	double scenex, sceney;

	m_vecDrawLines.clear();
	m_vecColors.clear();
	if (m_vecDataLines.isEmpty())
		return;

	CXViewInfoLFMGeometry *pViewInfo = dynamic_cast<CXViewInfoLFMGeometry *>(m_pViewInfo);
	if (!pViewInfo)
		return;

	std::vector<bool> vecZoneDisplay = pViewInfo->GetVecZoneDisplay();
	std::vector<QRgb> vecZoneColor = pViewInfo->GetVecZoneColor();
	std::vector<int> vecZoneMinSlice = pViewInfo->GetVecZoneMinSlice();
	std::vector<int> vecZoneMaxSlice = pViewInfo->GetVecZoneMaxSlice();

	int m, n, iNumZone = vecZoneDisplay.size();
	for (m = 0; m < iNumZone; m++)
	{
		if (!vecZoneDisplay[m])
			continue;

		for (n = vecZoneMinSlice[m]; n <= vecZoneMaxSlice[m]; n++)
		{
			QPolygonF polygonData = m_vecDataLines[n];
			QPolygonF polygonDraw;
			for (int j = 0; j < m_vecDataLines[n].size(); j++)
			{
				transformer.World2Scene(polygonData[j].x(), qAbs(polygonData[j].y()), scenex, sceney);
				polygonDraw << QPointF(scenex, sceney);
			}

			m_vecDrawLines << polygonDraw;
			m_vecColors << QColor(vecZoneColor[m]);
		}
	}

	update();
}

void CXSecLFMGeometryItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	CXViewInfoLFMGeometry *pViewInfo = dynamic_cast<CXViewInfoLFMGeometry *>(m_pViewInfo);
	if (!pViewInfo)
		return;

	QPen pen;
	painter->save();
	pen.setWidthF(pViewInfo->GetLineSize());
	painter->setPen(pen);

	int nK = m_vecDrawLines.size();
	for (int k = 0; k < nK; k++)
	{
		painter->setPen(m_vecColors[k]);
		painter->drawPolyline(m_vecDrawLines[k]);
	}

	painter->restore();
}