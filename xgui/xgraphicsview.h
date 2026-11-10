#ifndef _CXGRAPHICSVIEW_H__
#define _CXGRAPHICSVIEW_H__

#include <qgraphicsview.h>
#include "xgui_global.h"
#include "xdef.h"

class XGUI_EXPORT CXGraphicsView : public QGraphicsView
{
public:
	CXGraphicsView(QGraphicsScene *scene, EXWindowType eWindowType, QWidget *parent = 0);

protected:
	virtual void resizeEvent(QResizeEvent *pEvent) override;
	EXWindowType m_eWindowType;
};

#endif