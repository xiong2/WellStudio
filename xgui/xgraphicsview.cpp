#include "xgraphicsview.h"
#include "xscene.h"

CXGraphicsView::CXGraphicsView(QGraphicsScene *pScene, EXWindowType eWindowType, QWidget *parent) 
	: QGraphicsView(pScene, parent), m_eWindowType(eWindowType)
{
	setMouseTracking(true);
}

void CXGraphicsView::resizeEvent(QResizeEvent *pEvent)
{
	QGraphicsView::resizeEvent(pEvent);

	if(m_eWindowType == eLogViewWindow) return;

	QGraphicsScene *pScene = dynamic_cast<QGraphicsScene *>(scene());
	//CXScene *pScene = dynamic_cast<CXScene *>(scene());
	pScene->setSceneRect(0, 0, width() - 20, height() - 20);
}