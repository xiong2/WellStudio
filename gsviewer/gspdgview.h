#ifndef _GSPDGVIEW_H__
#define _GSPDGVIEW_H__

#include "stdafx.h"
#include <QGraphicsView>
#include "gsviewer_global.h"

class GSVIEWER_EXPORT GSPDGView : public QGraphicsView
{
	Q_OBJECT
public:
	GSPDGView(QWidget *parent = Q_NULLPTR);
	~GSPDGView();

protected:
	void mouseMoveEvent(QMouseEvent *) override;
};

#endif