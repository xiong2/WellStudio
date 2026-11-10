#pragma once

#include <QGraphicsView>

class QOpenGLWidget;

class XViewPyramid : public QGraphicsView
{
	Q_OBJECT

public:
	XViewPyramid(QWidget* parent = Q_NULLPTR);
	~XViewPyramid() = default;

	QOpenGLWidget* GetGLWidget() const { return m_pGLWidget; }

protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;

private:
	void _InitGLWidget();

	QOpenGLWidget* m_pGLWidget;
};