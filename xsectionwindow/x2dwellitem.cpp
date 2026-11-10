#include <qdebug.h>
#include "x2dwellitem.h"

#include "xwell.h"
#include "xglobal.h"
#include "xviewinfowellpath.h"
#include "xwellpath.h"
#include "x2dsectionwindow.h"
#include "xbaseconsole.h"
#include "x2dsectionaxis.h"
#include "xwindowinfosection.h"
#include "xlinearitymap.h"

#include "xgraphicsapi.h"
#include "xsectionscene.h"
#include "xsectionprojector.h"
#include "xcoordtransformer.h"

CX2DWellItem::CX2DWellItem(CX2DSectionWindow *pWindow,QGraphicsItem *parent):CXAbstractItem(pWindow)
{
	m_pWell = NULL;
	this->setZValue(2);
}


CX2DWellItem::~CX2DWellItem(void)
{
	CX2DSectionWindow *pWindow =dynamic_cast<CX2DSectionWindow*>(((CXBaseConsole*)::GetConsole())->GetActiveWinow()) ;
	if (pWindow!= NULL)
	{	
		CX2DSectionAxis *pAxisWidget =pWindow->GetAxisWidget();
		pAxisWidget->RemoveWellName(m_pWell);
	}
}

void CX2DWellItem::_UpdateData()
{
	m_vecFullDataPoint.clear();
	m_vecFullMD.clear();
	m_vecMD.clear();
	m_vecDataPoint.clear();
	m_vecDrawPoint.clear();

	m_pWell = dynamic_cast<CXWell*>(GetItemObject());
	if (m_pWell == NULL)
	{
		return;
	}
	m_pAxis->RemoveWellName(m_pWell);

	CXSectionScene *pScene = (CXSectionScene *)scene();
	CXSectionProjector *pProjector = pScene->GetProjector();

	double dX, dY;
	m_pWell->GetWellPosition(dX, dY);
	int iPlaneIDX = pProjector->WellShouldBeDrawn(m_pWell, m_pSectionWindow->GetSecWindowViewInfo()->GetSearchingRadius());
	if (iPlaneIDX < 0)
	{
		//	Too faraway.
		return;
	}

	float XLeft, XRight;
	pProjector->GetEndTraceNumber(iPlaneIDX, XLeft, XRight);
	if (XRight < XLeft)
	{
		std::swap(XRight, XLeft);
	}
	m_clipRect = m_pSectionWindow->GetSceneRect();
	m_clipRect.setLeft(XLeft);
	m_clipRect.setRight(XRight);

	vector<double> vecX, vecY, vecTWT, vecMD;
	if (m_pWell->GetXYAndTWT(vecX, vecY, vecTWT, vecMD))
	{
		int iIdx;
		for (iIdx = 0; iIdx < vecX.size(); ++iIdx)
		{
			float fTrace = pProjector->GetSubPointTraceNumber(vecX[iIdx], vecY[iIdx], iPlaneIDX);
			m_vecFullDataPoint.push_back(QPointF(fTrace, vecTWT[iIdx]));
			m_vecFullMD.push_back(vecMD[iIdx]);
		}

		//	Well has time data, use simplified data.
		vector<int> vecInd;
		CXGraphicsAPI::SegmentSimplification(&vecX[0], &vecY[0], &vecTWT[0], vecX.size(), vecInd);

		for (iIdx = 0; iIdx < vecInd.size(); ++iIdx)
		{
			float fTrace = pProjector->GetSubPointTraceNumber(vecX[vecInd[iIdx]], vecY[vecInd[iIdx]], iPlaneIDX);
			m_vecDataPoint.push_back(QPointF(fTrace, vecTWT[vecInd[iIdx]]));
			m_vecMD.push_back(vecMD[vecInd[iIdx]]);
		}
	}
	else
	{
		//	Well does not has time data.
	}

	MapToScene();
}

void CX2DWellItem::MapToScene()
{
	CXSectionScene* pScene = (CXSectionScene*)scene();
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);
	double scenex, sceney;

	m_vecDrawPoint.clear();

	m_pWellPathViewInfo = dynamic_cast<CXViewInfoWellPath*>(m_pViewInfo);
	Q_ASSERT(m_pWellPathViewInfo);

	CXWindowInfoSection *pViewInfo = m_pSectionWindow->GetSecWindowViewInfo();
	int nNum = m_vecDataPoint.size();
	float fXMin = 99999., fXMax = 0., fYMax = 0.;

	for (int iIdx = 0 ; iIdx < nNum ; ++iIdx)
	{
		QPointF pos = m_vecDataPoint[iIdx];

		transformer.World2Scene(pos.x(), pos.y(), scenex, sceney);

		QPointF ScenPos(scenex, sceney);

		if (iIdx == 0)
		{
			if (m_pWellPathViewInfo->GetWellNameVisible())
			{
				m_pAxis->AddWellName(qMakePair(m_pWell, pos.x()));
			}
			else
			{
				m_pAxis->RemoveWellName(m_pWell);
			}
		}

		if (pos.isNull())
		{
			continue;
		}

		fXMin = fXMin > ScenPos.x() ? ScenPos.x() : fXMin;
		fXMax = fXMax < ScenPos.x() ? ScenPos.x() : fXMax;
		fYMax = fYMax < ScenPos.y() ? ScenPos.y() : fYMax;

		m_vecDrawPoint.push_back(ScenPos);
	}

	m_boundRect = QRectF(fXMin, 0., (fXMax - fXMin), fYMax);

	update();
}

void CX2DWellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (m_vecDrawPoint.isEmpty() || !m_pViewInfo || !m_pWellPathViewInfo->GetWellPathVisible())
		return;

	CXSectionScene* pScene = (CXSectionScene*)scene();
	if (!pScene)
		return;

	CXCoordTransformer transformer(pScene);
	double scenex, sceney;

	painter->save();

	transformer.World2Scene(m_clipRect.left(), 0, scenex, sceney);
	QPointF leftEdge(scenex, sceney);

	transformer.World2Scene(m_clipRect.right(), 0, scenex, sceney);
	QPointF rightEdge(scenex, sceney);

	QRectF sceneRect = m_pSectionWindow->GetSceneRect();
	painter->setClipRect(QRectF(leftEdge.x(), sceneRect.top(), rightEdge.x() - leftEdge.x(), sceneRect.height()));
	painter->setRenderHint(QPainter::HighQualityAntialiasing);
	QPen pen;
	pen.setColor(m_pWellPathViewInfo->GetWellPathColor());
	pen.setWidth(m_pWellPathViewInfo->GetWellPathRadius());
	painter->setPen(pen);
	painter->drawPolyline(m_vecDrawPoint.data(), m_vecDrawPoint.size());
	pen.setStyle(Qt::DotLine);
	painter->setPen(pen);
	painter->drawLine(QPointF(m_vecDrawPoint[0].x(), 0), m_vecDrawPoint[0]);
	painter->restore();
}

QRectF	CX2DWellItem::boundingRect() const
{
	return m_boundRect;
}