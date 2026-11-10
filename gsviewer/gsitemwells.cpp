#include "stdafx.h"
#include <qpainter.h>
#include <qgraphicsscene.h>
#include "stdafx.h"
#include "xglobalcoordtransform.h"
#include "gsutilities.h"
#include "gsitemwells.h"
#include "xwell.h"

GSItemWells::GSItemWells(QList<CXWell *> listStructures, CXGlobalCoordTransform *pCT, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
	m_listWells = listStructures;
	m_pCoordTransform = pCT;
}

void GSItemWells::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	int i, j, iIDX = 0;
	setRect(scene()->sceneRect());

	QPen pen(QColor("black"));
	pen.setWidth(30);
	painter->setPen(pen);
	painter->setRenderHint(QPainter::Antialiasing);
	QFont font = painter->font();
	font.setPixelSize(800);
	painter->setFont(font);

	for (i = 0; i < m_listWells.size(); i++)
	{
		double dX, dY;
		m_listWells[i]->GetWellPosition(dX, dY);
		QPointF	wellPoint = m_pCoordTransform->World2Local(QPointF(dX, dY));

		painter->drawEllipse(QRectF(wellPoint - QPointF(300, 300), wellPoint + QPointF(300, 300)));

		painter->drawText(wellPoint.x() - 1600, wellPoint.y() - 1600, 3200, 800, Qt::AlignCenter, m_listWells[i]->GetObjectName());
	}
}