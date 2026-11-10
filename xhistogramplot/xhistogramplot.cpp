#include <qtoolbar.h>
#include "xhistogramplot.h"
#include "xhistscene.h"
#include "xviewinfohiscurve.h"
#include "xglobal.h"

CXHistogramPlot::CXHistogramPlot(QString sWindowName, QWidget *parent, Qt::WindowFlags f)
	:CXWindow(sWindowName, parent, f)
{
	setAttribute(Qt::WA_DeleteOnClose);
	m_eWindowType = eHistogramWindow;
	setMinimumSize(600, 400);
}

CXHistogramPlot::~CXHistogramPlot()
{
}

void CXHistogramPlot::InitWindow()
{
	CXWindow::InitWindow();
}

CXScene* CXHistogramPlot::GetScene()
{
	if(!m_pScene)
	{
		m_pScene = new CXHistScene(this);
	}
	return m_pScene;
}

void CXHistogramPlot::itemChanged(bool bAdd, QUuid objectID)
{
	//	Update the setting tab.
    CXViewInfoHisCurve *pViewInfo = (CXViewInfoHisCurve *)(GetObjectViewInfo(objectID));
}

void CXHistogramPlot::slotSetting()
{

}