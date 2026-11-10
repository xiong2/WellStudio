#include "stdafx.h"
#include "gsbasemapview.h"
#include "gsbasemapwindow.h"
#include "xglobal.h"
#include "xobject.h"
#include "gsbm3dhorizonItem.h"
#include <QGLWidget>
#include <QGraphicsItem>
#include <QWheelEvent>
#include <QPushButton>

GSBasemapView::GSBasemapView(QWidget* parent)
    : QGraphicsView(parent)
{
    setMouseTracking(true);
	//setRenderHint(QPainter::Antialiasing);
	setBackgroundBrush(Qt::black);
	setCacheMode(CacheBackground);
}

GSBasemapView::~GSBasemapView()
{
}

void GSBasemapView::wheelEvent(QWheelEvent* pEvent)
{
    if (pEvent->modifiers() & Qt::ControlModifier)
    {
        qreal scaleFactor = pow((double)2, -pEvent->delta() / 240.0);
        qreal factor      = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
        if (factor < 0.002 || factor > 10)
            return;

        scale(scaleFactor, scaleFactor);
    }
    else
    {
        QGraphicsView::wheelEvent(pEvent);
    }
}

void GSBasemapView::mouseMoveEvent(QMouseEvent* pEvent)
{
	emit ShowPositionInfo(pEvent->pos(), itemAt(pEvent->pos()));
	QGraphicsView::mouseMoveEvent(pEvent);
}
