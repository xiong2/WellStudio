#ifndef XCROSSPLOT_H
#define XCROSSPLOT_H

#include "xcrossplot_global.h"
#include "xwindow.h"

class XDlgCPSetting;
class CXColormapWidget;

class XCROSSPLOT_EXPORT CXCrossPlot: public CXWindow
{
	Q_OBJECT

public:
	CXCrossPlot(QString sWindowName, QWidget *parent = 0, Qt::WindowFlags f = Qt::Window);
	~CXCrossPlot();

	//	Really initialize the window, should be called after contstructor.
	virtual void InitWindow() override;

	virtual CXScene* GetScene() override;

	void UpdateColormap(int iIDX, QString sName, double dMin, double dMax);

	void ShowStatus(QString);

private slots:
	void slotSetting();

protected:
	virtual void closeEvent(QCloseEvent *event) override;

	XDlgCPSetting*	m_pDlgSetting = NULL;

	QDockWidget*		m_pColormapDock;
	CXColormapWidget*	m_pColormapWidget = nullptr;
};

#endif // RLCROSSPLOT_H
