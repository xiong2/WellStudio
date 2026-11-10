#include <QOpenGLWidget>
#include "xviewgather.h"
#include "xscenegather.h"
#include "xdlggatherwin.h"

XViewGather::XViewGather(XSceneGather* pScene, QWidget* parent) : QGraphicsView(pScene, parent)
{
	_InitGLWidget();
	setAlignment(Qt::AlignLeft | Qt::AlignTop);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void XViewGather::_InitGLWidget()
{
	m_pGLWidget = new QOpenGLWidget;
	QSurfaceFormat format;
	format.setSamples(8);
	m_pGLWidget->setFormat(format);
	m_pGLWidget->setMouseTracking(true);
	setViewport(m_pGLWidget);
}

void XViewGather::resizeEvent(QResizeEvent *event)
{
	XDlgGatherWin *pWin = dynamic_cast<XDlgGatherWin *>(parent());
	if (pWin)
	{
		pWin->SetScrollbarPos();
	}
}
