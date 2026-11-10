#include "stdafx.h"
#include <qdebug.h>
#include <qevent.h>
#include "gssectionview.h"
#include "gssectionscene.h"

GSSectionView::GSSectionView(QWidget* parent)
	: QGraphicsView(parent)
{
	setMouseTracking(true);
}

GSSectionView::~GSSectionView()
{

}


void GSSectionView::mouseMoveEvent(QMouseEvent* pEvent)
{
	GSSectionScene *pScene = (GSSectionScene *)scene();
	//pScene->HandleMouseEvent(pEvent, eSecMouseMove);
}
