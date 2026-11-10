#include <QStatusBar>
#include <qtoolbar.h>
#include "xlogview.h"
#include "xlvscene.h"
#include "xdlglvsetting.h"
#include "xglobal.h"

CXLogView::CXLogView(QString sWindowName, QWidget *parent, Qt::WindowFlags f)
	:CXWindow(sWindowName, parent, f)
{
	setAttribute(Qt::WA_DeleteOnClose);
	m_eWindowType = eLogViewWindow;
}

CXScene* CXLogView::GetScene()
{
	if (!m_pScene)
	{
		m_pScene = new CXLVScene(this);
		m_pScene->setSceneRect(QRectF(0, 0, 1000, 1500));
	}

	return (CXScene *)m_pScene;
}

void CXLogView::InitWindow()
{
	CXWindow::InitWindow();
	setStatusBar(new QStatusBar(this));

	QToolBar *pTBar = new QToolBar();
	addToolBar(pTBar);
	pTBar->addAction(QIcon(::GetIconPath() + "Setting"), "Setting...", this, SLOT(slotSetting()));
}

void CXLogView::slotSetting()
{
	XDlgLVSetting dlg((CXLVScene *)GetScene(), this);
	dlg.exec();
}

void CXLogView::ShowStatus(QString str)
{
	statusBar()->showMessage(str);
}