#ifndef X2DSECTIONCURVEITEM_H
#define X2DSECTIONCURVEITEM_H

#include "xabstractitem.h"

class CXWell;
class CXWellCurve;
class CXWellPath;
class CXViewInfoWellCurve;
class QLinearGradient;

class CX2DSectionCurveItem : public CXAbstractItem
{
public:
	CX2DSectionCurveItem(CX2DSectionWindow *pWindow, QGraphicsItem *parent = 0);
	~CX2DSectionCurveItem(void);

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	virtual QRectF	boundingRect() const;

	//	Calculate item from logical coords into scene coords.
	virtual void MapToScene();

protected:
	virtual void _UpdateData();
	QColor _mapColor(double dPercent);

	QPointF _findPostion(int& iSOffset, double dMD, QVector<double>& vecMD, QVector<QPointF>& vecPath);

	QVector<QColor>	m_vecColor;
	QVector<QPointF> m_vecDrawPoint;
	QVector<QPointF> m_vecBasePoint;
};

#endif // KE2DSECTIONCURVEITEM_H