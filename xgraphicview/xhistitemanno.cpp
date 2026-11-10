#include <qgraphicsscene.h>
#include <qpainter.h>
#include "xhistitemanno.h"
#include "xaxis.h"
#include "xautogrid.h"

CXHistItemAnno::CXHistItemAnno(QRectF rect, CXAxis *pXAxis, CXAxis *pYAxis, int iYZoom, QGraphicsItem *parent) : QGraphicsRectItem(rect, parent)
{
	m_pAxisX = pXAxis;
	m_pAxisY = pYAxis;
	m_iYZoom = iYZoom;
}

void CXHistItemAnno::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	if (!m_pAxisX)
		return;

	painter->setPen(QPen(Qt::black, 1));

	QRectF rect = scene()->sceneRect();
	rect.adjust(70, 30, -30, -60);
	painter->drawRect(rect);

	if(m_iYZoom == 100)
		painter->drawText(rect.left() - 20, rect.top(), "%");

	//	X Axis.
	m_pAxisX->SetSceneRect(rect.toRect());
	m_pAxisX->calculatorGroundTickInterval();
	int nTickCount = m_pAxisX->GetTickCount();
	for (int i = 0; i <= nTickCount; ++i)
	{
		double dDepth = m_pAxisX->GetGroundGradValue(i);
		int  iScenePos = m_pAxisX->MapGroundToScene(dDepth);
		QString strTickValue = CXAutoGrid::TrimToString(dDepth);

		if (m_pAxisX->IsMainTick(dDepth))
		{
			painter->save();
			painter->setPen(QPen(Qt::lightGray, 1));
			painter->drawLine(iScenePos, rect.bottom() + 1, iScenePos, rect.top());
			painter->restore();
			QRect textRect = CXAutoGrid::TextRect(QFont(), strTickValue);
			painter->drawText(iScenePos - textRect.width() / 2, rect.bottom() + textRect.height() + 10, strTickValue);
		}
		else
		{
			painter->drawLine(iScenePos, rect.bottom() + 1, iScenePos, rect.bottom() + 3);
		}
	}

	//	Y Axis.
	m_pAxisY->SetSceneRect(rect.toRect());
	m_pAxisY->calculatorGroundTickInterval();
	nTickCount = m_pAxisY->GetTickCount();
	for (int i = nTickCount; i >= 0; i--)
	{
		double dDepth = m_pAxisY->GetGroundGradValue(i);
		int  iScenePos = m_pAxisY->MapGroundToScene(dDepth, true);
		QString strTickValue = CXAutoGrid::TrimToString(dDepth * m_iYZoom);

		if (m_pAxisY->IsMainTick(dDepth))
		{
			painter->save();
			painter->setPen(QPen(Qt::lightGray, 1));
			if(iScenePos < rect.bottom())
				painter->drawLine(rect.right(), iScenePos, rect.x() - 5, iScenePos);
			painter->restore();
			QRect textRect = CXAutoGrid::TextRect(QFont(), strTickValue);
			painter->drawText(rect.x() - 10 - textRect.width(), iScenePos + textRect.height() / 2, strTickValue);
		}
		else
		{
			painter->drawLine(rect.x(), iScenePos, rect.x() - 2, iScenePos);
		}
	}
}