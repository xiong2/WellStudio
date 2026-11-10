#pragma  warning(push,0)
#include "x3danchorpickup.h"
#include <QPainterPath>
#include <QPainter>
#pragma  warning(pop)
CX3DAnchorPickup::CX3DAnchorPickup(void)
{
	m_bPickUpEnd = false;
}


CX3DAnchorPickup::~CX3DAnchorPickup(void)
{
	m_vecAnchor.clear();
	m_DrawPath = QPainterPath();
}

QVector<QPointF>  Intersect(const QPainterPath &path1, const QPainterPath &path2)  
{  
	QVector<QPointF > vecIntersectPointF;
	qreal len = path2.length();  
	QPointF p = path2.pointAtPercent(0);  
	for(int k = 1; k <= len; ++k)  
	{  
		if(path1.contains(p))  
		{  
			vecIntersectPointF.push_back(p);
		}  
		qreal per = path2.percentAtLength(k);  
		p = path2.pointAtPercent(per);  
	}  
	return vecIntersectPointF;
}

void CX3DAnchorPickup::AddAnchor(QPointF &pos)
{
	if (m_bPickUpEnd)
	{
		return;
	}
	if (!m_vecAnchor.isEmpty())
	{
		QPointF beginPosF = m_vecAnchor.first();
		QPointF EndPosF = m_vecAnchor.last();
		QPainterPath path;
		path.moveTo(beginPosF);
		path.lineTo(pos);

		QPainterPath path2 ;
		path2.moveTo(EndPosF);
		path2.lineTo(pos);
		QVector<QPointF > vecIntersectPointF = Intersect(m_DrawPath,path);
		QVector<QPointF > vecIntersectPointF2 = Intersect(m_DrawPath,path2);
		if (vecIntersectPointF.size() >1 || vecIntersectPointF2.size() >1)
		{
			return;
		}
	}
	m_vecAnchor.push_back(pos);
}

void CX3DAnchorPickup::DrawPolygon(QPainter &painter)
{		
	m_DrawPath = QPainterPath();

	painter.save();
	QPen pen;
	pen.setWidth(2);
	pen.setColor(Qt::yellow);
	painter.setPen(pen);
	if (!m_vecAnchor.isEmpty())
	{
		foreach(QPointF posF,m_vecAnchor)
		{
			if (m_DrawPath.elementCount() == 0)
			{
				m_DrawPath.moveTo(posF);
			}
			else
			{
				m_DrawPath.lineTo(posF);
			}
		}
		painter.drawPath(m_DrawPath);
		//draw tracking path pen style changed to dot line
		QPointF beginPosF = m_vecAnchor.first();
		QPointF EndPosF = m_vecAnchor.last();
		if (!m_bPickUpEnd)
		{
			if (!m_TrackingPosF.isNull())
			{
				pen.setStyle(Qt::DotLine);
				painter.setPen(pen);
				painter.drawLine(beginPosF,m_TrackingPosF);
				painter.drawLine(m_TrackingPosF,EndPosF);
			}
		}
		else
		{
			painter.drawLine(beginPosF,EndPosF);
		}
	}
	painter.restore();
}

void CX3DAnchorPickup::SetMouseTrackingPos(QPointF &pos)
{
	m_TrackingPosF = pos;
}

void CX3DAnchorPickup::SetPickUpEnd(bool bEnd)
{
	m_bPickUpEnd = bEnd;
}

void CX3DAnchorPickup::ClearAllAnchor()
{
	m_vecAnchor.clear();
	m_TrackingPosF = QPointF();
}


QPolygonF CX3DAnchorPickup::GetFillPolygon()
{
	return m_DrawPath.toFillPolygon();
}
