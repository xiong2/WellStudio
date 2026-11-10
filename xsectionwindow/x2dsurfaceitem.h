#ifndef X2DSURFACEITEM_H
#define X2DSURFACEITEM_H

#include "xabstractitem.h"

class CX3DSurface;
class CXViewInfoSurface;

class CX2DSurfaceItem : public CXAbstractItem {
public:
    CX2DSurfaceItem(CX2DSectionWindow* pWindow, QGraphicsItem* parent = 0);
    ~CX2DSurfaceItem(void);
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
	virtual QRectF boundingRect() const
	{
		return scene()->sceneRect();
	}

	virtual void MapToScene();

protected:
    virtual void _UpdateData();
    QPainterPath m_Path;
	int m_iSTrace;
	int m_iTraceInc;
	std::vector<double> m_vecZ;

	CX3DSurface* m_p3DSurface;
	CXViewInfoSurface* m_pSurfaceViewInfo;
};

#endif // KE2DSURFACEITEM_H