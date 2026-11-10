#ifndef _CXAXISITEM_H__
#define _CXAXISITEM_H__

#include "xgraphicview_global.h"
#include <qgraphicsitem.h>

class XGRAPHICVIEW_EXPORT CXAxisItem: public QGraphicsItem
{
public:
	CXAxisItem(QString sName, QGraphicsItem *parent = 0);

	//void Populate(bool bHorizontal, bool bTopLeft, bool bFixScale, double dStart, double dStep, double dScaleOrEnd);
	void Populate(bool bHorizontal, bool bTopLeft, bool bFixScale, double dScaleOrEnd);

	QRectF boundingRect() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

	//	Whether cross the canvas (grid).	
	bool isCrossed();	

	QColor getGridLineColor();

	Qt::PenStyle getGridLineStyle();

	int getGridLineWidth();

	QString		m_sName;
	bool		m_bHorizontal;		//	Horizontal or vertical axis?
	bool		m_bTopLeft;			//	On the top (horizontal) or on the left (vertical) axis?

	bool		m_bFixScale;		//	While window resized, fix scale or fix range?
	double		m_dScale;			//	Fixed scale.
};

#endif