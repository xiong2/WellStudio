#include "stdafx.h"
#include <qpainter.h>
#include <qgraphicsscene.h>
#include "xglobalcoordtransform.h"
#include "gsutilities.h"
#include "gsitemanticlines.h"
#include "gsanticline.h"

GSItemAnticlines::GSItemAnticlines(QList<GSAnticline *> listAnticlines, CXGlobalCoordTransform *pCT, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
	m_listAnticlines = listAnticlines;
	m_pCoordTransform = pCT;
}

void GSItemAnticlines::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	int i, j, iIDX = 0;
	//setRect(scene()->sceneRect());

	QPen pen(QColor("brown"));
	pen.setWidth(150);
	painter->setPen(pen);
	QPointF p1, p2;
	for (i = 0; i < m_listAnticlines.size(); i++)
	{
		m_listAnticlines[i]->GetEndPoints(p1, p2);

		QPointF sP1 = m_pCoordTransform->World2Local(p1);
		QPointF sP2 = m_pCoordTransform->World2Local(p2);
		painter->drawLine(sP1, sP2);
	}
}