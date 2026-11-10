#include "stdafx.h"
#include <qpainter.h>
#include <qgraphicsscene.h>
#include "gsitemstress.h"
#include "gsstressmap.h"
#include "xutmtool.h"
#include "xglobalcoordtransform.h"
#include "gsdef.h"

GSItemStress::GSItemStress(GSStressMap *pMap, CXGlobalCoordTransform *pCT, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
	m_pMap = pMap;
	m_pCoordTransform = pCT;
}

void GSItemStress::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	int i, j, iIDX = 0;
	setRect(scene()->sceneRect());

	QPen pen(QColor("blue"));
	pen.setWidth(20);
	painter->setPen(pen);

	CXSeismicUTMTool utm = m_pMap->GetUTM();
	int nI = utm.GetNI(), nJ = utm.GetNJ(), iStep = 8;
	int iSize = nI * nJ;
	float *pData = m_pMap->GetData();
	QPainterPath stressLines = QPainterPath();
	double dIInterval = utm.GetIInterval();
	double dMin, dMax, dSpan;
	m_pMap->GetDataRange(dMin, dMax);
	if (dMax == dMin)
		dMin = 0.;
	dSpan = 1 / (dMax - dMin);

	for (i = 0; i < nI; i += iStep)
	{
		for (j = 0; j < nJ; j += iStep)
		{
			float z = pData[iSize + i * nJ + j];
			float fMag = pData[i * nJ + j];
			//if (z == xGlobal.g_dInvalidData || fMag <= gStressMagRange[MAG_UPLIFT].m_fSHMagLower)
			//	continue;

			double x, y;
			utm.IJToXY(i, j, x, y);

			QPointF p(x, y);
			//QPointF p1(x - (fMag - dMin) * dSpan * dIInterval * iStep / 4, y);
			//QPointF p2(x + (fMag - dMin) * dSpan * dIInterval * iStep / 4, y);
			QPointF p1(x - dIInterval * iStep / 4, y);
			QPointF p2(x + dIInterval * iStep / 4, y);

			QLineF line1(p, p2);
			line1.setAngle(-z);
			QLineF line2(p, p1);
			line2.setAngle(180 - z);

			QPointF line1p2 = m_pCoordTransform->World2Local(line1.p2());
			QPointF line2p2 = m_pCoordTransform->World2Local(line2.p2());

			stressLines.moveTo(line1p2);
			stressLines.lineTo(line2p2);
		}
	}
		
	painter->drawPath(stressLines);
}