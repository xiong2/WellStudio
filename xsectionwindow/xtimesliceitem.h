#ifndef XTIMESLICEITEM_H
#define XTIMESLICEITEM_H

#include "xabstractitem.h"

class CXSeismicSection;


class CXTimeSliceItem : public CXAbstractItem
{
public:
	CXTimeSliceItem(CX2DSectionWindow *pWindow,QGraphicsItem *parent = 0);
	~CXTimeSliceItem(void);
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget  = 0 );
	virtual QRectF boundingRect() const;
	virtual QPainterPath  shape() const ;
	void SynSectionNumber(QPointF pos);

protected:
	virtual void _UpdateData();	

private:
	QPen m_Pen;
	QPainterPath m_Path;
	double m_dZRatio;
};

#endif // KETIMESLICEITEM_H