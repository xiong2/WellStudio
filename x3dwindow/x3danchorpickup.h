#ifndef X3DANCHORPICKUP_H
#define X3DANCHORPICKUP_H

#include <QVector>
#include <QPainterPath>
#include "x3dwindow_global.h"

class QPainter;
class QPointF;

class X3DWINDOW_EXPORT CX3DAnchorPickup 
{
public:
	CX3DAnchorPickup(void);
	~CX3DAnchorPickup(void);
	void DrawPolygon(QPainter &painter);
	void AddAnchor(QPointF &pos);
	void SetMouseTrackingPos(QPointF &pos);
	void SetPickUpEnd(bool bEnd = true);
	void ClearAllAnchor();
	QPolygonF GetFillPolygon();
private:
	QVector< QPointF > m_vecAnchor;
	QPointF m_TrackingPosF;
	bool m_bPickUpEnd;
	QPainterPath m_DrawPath;

};

#endif // KE3DANCHORPICKUP_H
