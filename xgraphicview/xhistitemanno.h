#pragma once
#include <QGraphicsRectItem>
#include "xgraphicview_global.h"

class CXAxis;

class XGRAPHICVIEW_EXPORT CXHistItemAnno : public QGraphicsRectItem
{
public:
	CXHistItemAnno(QRectF, CXAxis *, CXAxis *, int iYZoom = 1, QGraphicsItem *parent = 0);

protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

	int		m_iYZoom;
	CXAxis	*m_pAxisX = NULL;
	CXAxis	*m_pAxisY = NULL;
};
