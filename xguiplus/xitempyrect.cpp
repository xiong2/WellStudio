#include <qpainter.h>
#include <qgraphicsscene.h>
#include <qgraphicsview.h>
#include <qdebug.h>
#include "xitempyrect.h"
#include "xscenepyramid.h"

XItemPyRect::XItemPyRect(XScenePyramid *pScene, QGraphicsItem* parent) : QGraphicsItem(parent)
{
	m_pScene = pScene;
	setZValue(2);
}

void XItemPyRect::HandleMouseEvent(QMouseEvent *pEvent)
{
	if (pEvent->type() == QEvent::MouseButtonPress)
	{
		if (pEvent->button() == Qt::LeftButton)
		{
			m_eSta = eEditing;
			m_polygon << pEvent->pos();
		}
		else if (pEvent->button() == Qt::RightButton)
		{
			if (m_polygon.length() <= 2)
			{
				m_polygon.clear();
				m_eSta = ePreEdit;
			}
			else
			{
				m_polygon.removeAt(m_polygon.length() - 2);
			}
		}
	}
	else if (pEvent->type() == QEvent::MouseMove && m_eSta == eEditing)
	{
		if (m_polygon.length() == 1)
		{
			m_polygon << pEvent->pos();
		}
		else
		{
			m_polygon.last().setX(pEvent->pos().x());
			m_polygon.last().setY(pEvent->pos().y());
		}
	}
	else if (pEvent->type() == QEvent::MouseButtonDblClick && m_eSta == eEditing)
	{
		m_eSta = eEdited;
		m_polygon.pop_back();

		if (m_polygon.length() <= 2)
		{
			m_polygon.clear();
		}

		m_pScene->SetPolygon(m_polygon);
	}

	update();
}

QRectF XItemPyRect::boundingRect() const
{
	return m_pScene->sceneRect();
}

void XItemPyRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (m_polygon.isEmpty())
		return;

	painter->setPen(QPen(Qt::red, 2));
	painter->drawPolygon(m_polygon);
}