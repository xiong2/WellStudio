#include <QOpenGLWidget>
#include "xviewpyramid.h"
#include "xscenepyramid.h"

XViewPyramid::XViewPyramid(QWidget* parent) : QGraphicsView(parent)
{
	_InitGLWidget();
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void XViewPyramid::_InitGLWidget()
{
	m_pGLWidget = new QOpenGLWidget;
	QSurfaceFormat format;
	format.setSamples(8);
	m_pGLWidget->setFormat(format);
	m_pGLWidget->setMouseTracking(true);
	setViewport(m_pGLWidget);
}

void XViewPyramid::resizeEvent(QResizeEvent *)
{
	XScenePyramid *pScene = dynamic_cast<XScenePyramid *>(scene());
	if (pScene)
	{
		QRect rect = this->rect();
		pScene->setSceneRect(rect);
	}
}

void XViewPyramid::mousePressEvent(QMouseEvent* event)
{
	XScenePyramid *pScene = dynamic_cast<XScenePyramid *>(scene());
	if (pScene)
		pScene->HandleMouseEvent(event);
}

void XViewPyramid::mouseDoubleClickEvent(QMouseEvent* event)
{
	XScenePyramid *pScene = dynamic_cast<XScenePyramid *>(scene());
	if (pScene)
		pScene->HandleMouseEvent(event);
}

void XViewPyramid::mouseMoveEvent(QMouseEvent* event)
{
	XScenePyramid *pScene = dynamic_cast<XScenePyramid *>(scene());
	if (pScene)
		pScene->HandleMouseEvent(event);
}

void XViewPyramid::mouseReleaseEvent(QMouseEvent* event)
{
	XScenePyramid *pScene = dynamic_cast<XScenePyramid *>(scene());
	if (pScene)
		pScene->HandleMouseEvent(event);
}