#include "xsechorizonitem.h"
#include "x3dhorizon.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xseismicdatavolume.h"
#include "xviewinfo3dhorizon.h"
#include "xsectionscene.h"
#include "xautogrid.h"
#include "xglobal.h"
#include "xcoordtransformer.h"

CXSecHorizonItem::CXSecHorizonItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent):CXAbstractItem(pWindow)
{
    setZValue(2);
}

CXSecHorizonItem::~CXSecHorizonItem(void)
{
}

void CXSecHorizonItem::_UpdateData()
{
	m_vecZ.clear();
	CX3DHorizon *p3DHorizon = dynamic_cast<CX3DHorizon*>(GetItemObject());
	if (p3DHorizon == NULL)
	{
		return;
	}

	CXSeismicUTMTool& hUTM = p3DHorizon->GetUTM();
	float *pHorizonData = p3DHorizon->GetData();
	int i, j, nJ = hUTM.GetNJ();

	CXObject* pCurSection = m_pSectionWindow->GetCurrentGeometryObj();
	CXSeismicSection* pSeismicSection = dynamic_cast<CXSeismicSection*>(pCurSection);
	CXSeismicRandomSection* pRandomSection = dynamic_cast<CXSeismicRandomSection*>(pCurSection);	

	CXSectionScene *pScene = (CXSectionScene *)scene();
	CXSeismicObject *pSObj = dynamic_cast<CXSeismicObject *>(pScene->GetBackgroundSection(false));
	m_bPreStackSection = pSObj->IsPrestack();

	if (pSeismicSection != NULL)
	{
		int i, iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc;
		CXSeismicUTMTool sUTM = pSeismicSection->GetUTM();
		sUTM.GetLineNumRange(iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc);
		int iSectionNumber = (int)pSeismicSection->GetSectionNumber();
		if (pSeismicSection->GetSectionType() == eInlineSection)
		{
			m_iSTrace = iSXline;
			m_iTraceInc = iXlineInc;

			for (int m = iSXline; m <= iEXline; m += iXlineInc)
			{
				hUTM.LineToIJ(iSectionNumber, m, i, j);
				m_vecZ.push_back(pHorizonData[i * nJ + j]);
			}
		}
		else if (pSeismicSection->GetSectionType() == eCrosslineSection)
		{
			m_iSTrace = iSInline;
			m_iTraceInc = iInlineInc;

			for (int m = iSInline; m <= iEInline; m += iInlineInc)
			{
				hUTM.LineToIJ(m, iSectionNumber, i, j);
				m_vecZ.push_back(pHorizonData[i * nJ + j]);
			}
		}
	}
	else if (NULL != pRandomSection)
	{
		m_iSTrace = 0;
		m_iTraceInc = 1;

		std::vector<int> vecInlineNum, vecXlineNum;
		pRandomSection->GetLineNumbers(vecInlineNum, vecXlineNum);
		int iSize = vecInlineNum.size();
		for (int m = 0; m < iSize; ++m)
		{
			hUTM.LineToIJ(vecInlineNum[m], vecXlineNum[m], i, j);
			m_vecZ.push_back(pHorizonData[i * nJ + j]);
		}
	}

	MapToScene();
}

void CXSecHorizonItem::MapToScene()
{
	CXSectionScene* pScene = (CXSectionScene*)scene();
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);
	double scenex, sceney;

	m_Path = QPainterPath();
	m_vecIntPoints.clear();
	bool bHasNew(false);
    int nSize = m_vecZ.size();

    for ( int i = 0; i < nSize; ++i ) 
	{
		if (m_vecZ[i] == g_dInvalidData)
		{
            bHasNew = true;
            continue;
        }

		float fTrace = m_iSTrace + i * m_iTraceInc;

		transformer.World2Scene(fTrace, qAbs(m_vecZ[i]), scenex, sceney);
		QPointF fPos(scenex, sceney);

        if ( m_Path.elementCount() == 0 || bHasNew ) 
		{
            m_Path.moveTo(fPos);
            bHasNew = false;

			if (!m_bPreStackSection && i < nSize - 1 && m_vecZ[i + 1] == g_dInvalidData)
				m_vecIntPoints << fPos;

			if (m_bPreStackSection)
			{
				transformer.World2Scene(fTrace + m_iTraceInc, qAbs(m_vecZ[i]), scenex, sceney);
				fPos = QPointF(scenex, sceney);
				m_Path.lineTo(fPos);
			}
		}
		else 
		{
            m_Path.lineTo(fPos);

			if (m_bPreStackSection)
			{
				transformer.World2Scene(fTrace + m_iTraceInc, qAbs(m_vecZ[i]), scenex, sceney);
				fPos = QPointF(scenex, sceney);
				m_Path.lineTo(fPos);
			}
		}
    }

	update();
}

void CXSecHorizonItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	CX3DHorizon *p3DHorizon = dynamic_cast<CX3DHorizon*>(GetItemObject());
	CXViewInfo3DHorizon *pHorizonViewInfo = dynamic_cast<CXViewInfo3DHorizon*>(m_pViewInfo);

	QPen pen;
    painter->setRenderHint(QPainter::HighQualityAntialiasing);
	int iWidth = pHorizonViewInfo->GetSectionLineWidth();
	pen.setWidthF(iWidth);
	pen.setColor(pHorizonViewInfo->GetSectionLineColor());	
	painter->setPen(pen);

    painter->drawPath(m_Path);

	pen.setWidthF(4 * iWidth);
	painter->setPen(pen);
	painter->drawPoints(m_vecIntPoints.data(), m_vecIntPoints.size());

    if ( !m_Path.isEmpty() ) 
	{
        QPainterPath::Element elemFirst = m_Path.elementAt(0);
        QPainterPath::Element elemLast = m_Path.elementAt(m_Path.elementCount() - 1);
        
		bool bAnnBgr = pHorizonViewInfo->GetSectionAnnotationBackgroundVisible();
        if ( bAnnBgr ) 
		{
            painter->save();
            QPen pen;
            painter->setPen(pen);
			QRect rect = CXAutoGrid::TextRect(QFont(), GetItemObject()->GetObjectName());
            rect.moveBottomLeft(QPoint(elemFirst.x, elemFirst.y));
			painter->fillRect(rect, pHorizonViewInfo->GetSectionAnnotationBackgroundColor());
            rect.moveBottomLeft(QPoint(elemLast.x, elemLast.y));
			painter->fillRect(rect, pHorizonViewInfo->GetSectionAnnotationBackgroundColor());
            painter->restore();
        }

		pen.setWidth(pHorizonViewInfo->GetSectionAnnotationSize());
		pen.setColor(pHorizonViewInfo->GetSectionAnnotationColor());
        painter->setPen(pen);
		if (pHorizonViewInfo->GetSectionAnnotationLeftVisible())
		{
			painter->drawText(elemFirst.x, elemFirst.y, GetItemObject()->GetObjectName());
        }
		if (pHorizonViewInfo->GetSectionAnnotationRightVisible())
		{			
			painter->drawText(elemLast.x, elemLast.y, GetItemObject()->GetObjectName());
        }
    }
}