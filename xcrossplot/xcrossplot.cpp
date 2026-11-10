#include <qdebug.h>
#include <QDockWidget>
#include <QStatusBar>
#include <qtoolbar.h>
#include "xcrossplot.h"
#include "xcrossplotscene.h"
#include "xviewinfoobject.h"
#include "xgraphicsview.h"
#include "xglobal.h"
#include "xdlgcpsetting.h"
#include "xcolormap.h"
#include "xcolormapwidget.h"

CXCrossPlot::CXCrossPlot(QString sWindowName, QWidget *parent, Qt::WindowFlags f)
	:CXWindow(sWindowName, parent, f)
{
	setAttribute(Qt::WA_DeleteOnClose);
	m_eWindowType = eCrossplotWindow;
	setMinimumSize(700, 600);
}

CXCrossPlot::~CXCrossPlot()
{
}

void CXCrossPlot::closeEvent(QCloseEvent* event)
{
	if (m_pScene)
	{
		CXCrossPlotScene *pScene = (CXCrossPlotScene *)m_pScene;
		//pScene->ClearBroadcastPoints();
	}

	CXWindow::closeEvent(event);
}

void CXCrossPlot::InitWindow()
{
	CXWindow::InitWindow();
	setStatusBar(new QStatusBar(this));

	QToolBar *pTBar = new QToolBar();
	addToolBar(pTBar);
	pTBar->addAction(QIcon(::GetIconPath() + "Setting"), "Setting...", this, SLOT(slotSetting()));

	m_pColormapDock = new QDockWidget("Colormap");
	addDockWidget(Qt::RightDockWidgetArea, m_pColormapDock);
}

CXScene* CXCrossPlot::GetScene()
{
	if(!m_pScene)
	{
		m_pScene = new CXCrossPlotScene(this);
	}

	return m_pScene;
}

void CXCrossPlot::UpdateColormap(int iIDX, QString sName, double dMin, double dMax)
{
	CXColormap *pColormap = CXColormap::GetColormap(iIDX);
	
	if (!m_pColormapWidget)
	{
		m_pColormapWidget = new CXColormapWidget(pColormap->GetName());
		m_pColormapDock->setWidget(m_pColormapWidget);
		connect(m_pColormapWidget, SIGNAL(OpenColormapEditingDialog()), this, SLOT(slotOpenColormapEditor()));
	}

	m_pColormapDock->setWindowTitle(sName);
	m_pColormapWidget->SetColormapName(pColormap->GetName());
	m_pColormapWidget->SetDisplayRange(dMin, dMax);
}

void CXCrossPlot::ShowStatus(QString str)
{
	statusBar()->showMessage(str);
}

void CXCrossPlot::slotSetting()
{
	if (!m_pDlgSetting)
	{
		m_pDlgSetting = new XDlgCPSetting((CXCrossPlotScene *)GetScene(), this);
	}

	m_pDlgSetting->show();
}