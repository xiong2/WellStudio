#pragma once

#include <qwidget.h>

class QGridLayout;
class XDlgGatherWin;
class XSceneGather;

class XAxesWidget : public QWidget
{
public:
	XAxesWidget(QWidget* parent);
	XAxesWidget();

	void SetView(QWidget* pView);

protected:
	virtual void paintEvent(QPaintEvent* event) override;

private:
	XDlgGatherWin*	m_pWindow;
	XSceneGather*	m_pScene = nullptr;
	QGridLayout*	m_pLayout;
};