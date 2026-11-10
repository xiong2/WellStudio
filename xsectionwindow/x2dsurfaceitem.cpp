#include "x2dsurfaceitem.h"
#include "x3dsurface.h"
#include "xseismicsection.h"
#include "xseismicrandomsection.h"
#include "xseismicdatavolume.h"
#include "xwindowinfosection.h"
#include "xviewinfosurface.h"
#include "xautogrid.h"
#include "xglobal.h"
#include "xcoordtransformer.h"
#include "xsectionscene.h"

CX2DSurfaceItem::CX2DSurfaceItem(CX2DSectionWindow *pWindow,QGraphicsItem *parent):CXAbstractItem(pWindow,parent)
{
}

CX2DSurfaceItem::~CX2DSurfaceItem(void)
{
}

void CX2DSurfaceItem::_UpdateData()
{
	m_p3DSurface = dynamic_cast<CX3DSurface*>(GetItemObject());
	m_pSurfaceViewInfo = dynamic_cast<CXViewInfoSurface*>(m_pViewInfo);
	if (m_p3DSurface == NULL)
	{
		return ;
	}

	m_Path = QPainterPath();

	CXObject *pCurSection = m_pSectionWindow->GetCurrentGeometryObj();
	CXSeismicSection* pSeismicSection = dynamic_cast<CXSeismicSection*>(pCurSection);
	CXSeismicRandomSection* pRandomSection = dynamic_cast<CXSeismicRandomSection*>(pCurSection);

	if (pSeismicSection != NULL)
	{
		int i, iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc;
		CXSeismicUTMTool sUTM = pSeismicSection->GetUTM();
		sUTM.GetLineNumRange(iSInline, iEInline, iInlineInc, iSXline, iEXline, iXlineInc);
		if (pSeismicSection->GetSectionType() == eInlineSection)
		{
			m_iSTrace = iSXline;
			m_iTraceInc = iXlineInc;
		}
		else if (pSeismicSection->GetSectionType() == eCrosslineSection)
		{
			m_iSTrace = iSInline;
			m_iTraceInc = iInlineInc;
		}
		else
			return;
	}
	else if (NULL != pRandomSection)
	{
		m_iSTrace = 0;
		m_iTraceInc = 1;
	}
	else
		return;

	CX3DSurface::CalcIntersection(m_vecZ, m_p3DSurface, pCurSection);

	MapToScene();
}

void CX2DSurfaceItem::MapToScene()
{
	CXSectionScene* pScene = (CXSectionScene*)scene();
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);
	double scenex, sceney;

	m_Path = QPainterPath();
	bool bHasNew(false);
	int nSize = m_vecZ.size();

	for (int i = 0; i < nSize; ++i)
	{
		if (m_vecZ[i] == g_dInvalidData)
		{
			bHasNew = true;
			continue;
		}

		float fTrace = m_iSTrace + i * m_iTraceInc;

		transformer.World2Scene(fTrace, qAbs(m_vecZ[i]), scenex, sceney);
		QPointF fPos(scenex, sceney);

		if (m_Path.elementCount() == 0 || bHasNew)
		{
			m_Path.moveTo(fPos);
			bHasNew = false;
		}
		else
		{
			m_Path.lineTo(fPos);
		}
	}

	update();
}

void CX2DSurfaceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->save();
	painter->setRenderHint(QPainter::HighQualityAntialiasing);
	QPen pen;
	pen.setWidthF(m_pSurfaceViewInfo->GetSectionLineWidth());
	pen.setColor(m_pSurfaceViewInfo->GetSectionLineColor());

	if (m_Path.elementCount() == 1)
	{	
	}
	else
	{
		painter->setPen(pen);
		painter->drawPath(m_Path);
	}
	painter->restore();

	if (!m_Path.isEmpty())
	{
		QPainterPath::Element elemFirst = m_Path.elementAt(0);
		QPainterPath::Element elemLast = m_Path.elementAt(m_Path.elementCount()-1);
		
		if (m_pSurfaceViewInfo->GetSectionAnnotationBackgroundVisible())
		{
			painter->save();	
			QPen pen;	
			painter->setPen(pen);
			QRect rect = CXAutoGrid::TextRect(QFont(), GetItemObject()->GetObjectName());
			rect.moveBottomLeft(QPoint(elemFirst.x,elemFirst.y));
			painter->fillRect(rect,m_pSurfaceViewInfo->GetSectionAnnotationBackgroundColor());
			rect.moveBottomLeft(QPoint(elemLast.x,elemLast.y));
			painter->fillRect(rect,m_pSurfaceViewInfo->GetSectionAnnotationBackgroundColor());
			painter->restore();
		}

		painter->save();
		QPen pen;	
		pen.setWidth(m_pSurfaceViewInfo->GetSectionAnnotationSize());	
		pen.setColor(m_pSurfaceViewInfo->GetSectionAnnotationColor());
		painter->setPen(pen);	
		if (m_pSurfaceViewInfo->GetSectionAnnotationLeftVisible())
		{
			painter->drawText(elemFirst.x, elemFirst.y, GetItemObject()->GetObjectName());
		}
		if (m_pSurfaceViewInfo->GetSectionAnnotationRightVisible())
		{
			painter->drawText(elemLast.x, elemLast.y, GetItemObject()->GetObjectName());
		}
		painter->restore();
	}
}