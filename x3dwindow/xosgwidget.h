#ifndef XOSGWIDGET_H
#define XOSGWIDGET_H

#include "x3dwindow_global.h"
#include <unordered_map>
#include <osgViewer/Viewer>
#include <QOpenGLWidget>
#include <QInputEvent>

class CXPickhandle;

/*!
 * @class	CXOSGWidget in the file "keosgwidget.h"
 * @brief	Embed the OSG Viewer in QOpenGLWidget.
 *
 * @author	pezy
 * @date	2017-02-21
 * @see
 */

class X3DWINDOW_EXPORT CXOSGWidget : public QOpenGLWidget, public osgViewer::Viewer
{
public:
	explicit CXOSGWidget(QWidget* parent = nullptr, bool bBasemap = false);
	~CXOSGWidget();

	CXPickhandle* GetPickhandle();
	
protected:
	//! reimplement from QOpenGLWidget
	void paintGL() override;
	void resizeGL(int w, int h) override;

	//! reimplement from QWidget for mouse and key event.
	void keyPressEvent(QKeyEvent* event) override;
	void keyReleaseEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

private:
	void _SetKeyboardModifiers(QInputEvent* event) const;

private:
	osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> m_pGraphWin;
	static std::unordered_map<int, int> m_mapKeys;
	qreal m_dDevicePixelRatio = 0.0;
};

#endif // KEOSGWIDGET_H
