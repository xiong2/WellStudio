#pragma once

#include <QGraphicsView>

class QOpenGLWidget;
class XSceneGather;

class XViewGather : public QGraphicsView
{
	Q_OBJECT

public:
	XViewGather(XSceneGather *pScene, QWidget* parent = Q_NULLPTR);
	~XViewGather() = default;

	QOpenGLWidget* GetGLWidget() const { return m_pGLWidget; }

protected:
	virtual void resizeEvent(QResizeEvent *event) override;

private:
	void _InitGLWidget();

	QOpenGLWidget* m_pGLWidget;

	XSceneGather*	m_pScene;
};