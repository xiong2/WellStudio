#include "stdafx.h"
#include <qdebug.h>
#include <qevent.h>
#include "gspdgview.h"
#include "gspdgscene.h"

GSPDGView::GSPDGView(QWidget* parent)
	: QGraphicsView(parent)
{
	setMouseTracking(true);
}

GSPDGView::~GSPDGView()
{

}


void GSPDGView::mouseMoveEvent(QMouseEvent* pEvent)
{
	GSPDGScene *pScene = (GSPDGScene *)scene();
	pScene->HandleMouseEvent(pEvent, eGSMouseMove);
}
