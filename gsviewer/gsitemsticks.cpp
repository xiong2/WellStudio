#include "stdafx.h"
#include <qpainter.h>
#include <qgraphicsscene.h>
#include "gsitemsticks.h"
#include "x3dhorizon.h"
#include "xutmtool.h"
#include "xglobalcoordtransform.h"
#include "gsdef.h"
#include "xglobal.h"

GSItemSticks::GSItemSticks(CX3DHorizon *pMap, CXGlobalCoordTransform *pCT, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
	m_pMap = pMap;
	m_pCoordTransform = pCT;
}

void GSItemSticks::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	int i, j, iIDX = 0;
	setRect(scene()->sceneRect());

	QPen pen(QColor("blue"));
	pen.setWidth(20);
	painter->setPen(pen);

	CXSeismicUTMTool utm = m_pMap->GetUTM();
	int nI = utm.GetNI(), nJ = utm.GetNJ();
	int iSize = nI * nJ;
	float *pData = m_pMap->GetData();
	QPainterPath stressLines = QPainterPath();
	double dIInterval = utm.GetIInterval();

	for (i = 0; i < nI; i++)
	{
		for (j = 0; j < nJ; j++)
		{
			float z = pData[i * nJ + j];
			if (z == g_dInvalidData || qAbs(z - 0.055) < 0.001)
				continue;

			double x, y;
			utm.IJToXY(i, j, x, y);
			y += 0.5 * dIInterval;

			QPointF p(x, y);
			QPointF p1(x - 1.5 * dIInterval, y);
			QPointF p2(x + 2.5 * dIInterval, y);

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