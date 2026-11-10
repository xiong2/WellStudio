#include "stdafx.h"
#include <qpainter.h>
#include <qgraphicsscene.h>
#include "gsitemtrappoints.h"
#include "xglobalcoordtransform.h"
#include "gsutilities.h"

GSItemTrapPoints::GSItemTrapPoints(QVector<QVector<double>> vecvecPoints, CXGlobalCoordTransform *pCT, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
	m_bColorByGroup = true;
	m_vecvecPoints = vecvecPoints;
	m_pCoordTransform = pCT;
}

void GSItemTrapPoints::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	int i, j, iIDX = 0;
	setRect(scene()->sceneRect());

	painter->setPen(QPen(QColor("black")));

	for (i = 0; i < m_vecvecPoints.size(); i++)
	{
		if (m_bColorByGroup)
		{
			painter->setBrush(QBrush(GSUtil::GetKellyColor(iIDX)));
			iIDX++;
		}

		int iLen = m_vecvecPoints[i].size();
		for (j = 0; j < iLen; j += 3)
		{
			if (!m_bColorByGroup)
			{
				painter->setBrush(QBrush(GSUtil::GetKellyColor((int)m_vecvecPoints[i][j + 2])));
			}

			QPointF point = m_pCoordTransform->World2Local(QPointF(m_vecvecPoints[i][j], m_vecvecPoints[i][j + 1]));
			painter->drawEllipse(QRectF(point - QPointF(HALFSIZE, HALFSIZE), point + QPointF(HALFSIZE, HALFSIZE)));
		}
	}
}