#ifndef X2DWELLITEM_H
#define X2DWELLITEM_H

#include "xabstractitem.h"

class CXWell;
class CXWellPath;
class CXViewInfoWellPath;

class CX2DWellItem : public CXAbstractItem
{
public:
    CX2DWellItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent = 0);
    ~CX2DWellItem(void);
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    virtual QRectF boundingRect() const;

	//	Calculate item from logical coords into scene coords.
	virtual void MapToScene();

	QVector<QPointF> GetPathData(bool bFull = true)
	{
		if (bFull)
			return m_vecFullDataPoint;
		else
			return m_vecDataPoint;
	}

	QVector<double> GetPathMD(bool bFull = true)
	{
		if (bFull)
			return m_vecFullMD;
		else
			return m_vecMD;
	}

protected:
    virtual void _UpdateData();

    CXWell* m_pWell;
    CXViewInfoWellPath* m_pWellPathViewInfo;

	QVector<QPointF>	m_vecFullDataPoint;			//	Well path in trace, twt coordinates.
	QVector<double>		m_vecFullMD;				//	Each MD coorespondingly.

	QVector<double>		m_vecMD;				//	Sparse MD.
	QVector<QPointF>	m_vecDataPoint;			//	Sparse well path in trace, twt coordinates.
    QVector<QPointF>	m_vecDrawPoint;

	QRectF	m_boundRect;
	QRectF	m_clipRect;		//	X coords In real world coords.
};

#endif // KE2DWELLITEM_H