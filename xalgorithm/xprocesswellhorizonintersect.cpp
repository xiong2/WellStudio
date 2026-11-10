#include "xprocesswellhorizonintersect.h"
#include "xthreadwellhorizonintersect.h"
#include "xobjecttype.h"
#include "xprocessfactory.h"
#include "xdlgcalculatingprogress.h"
#include "xparameterwellhorzionintersect.h"
#include "xglobal.h"
#include "xwelltops.h"
#include <cassert>
#include "xbaseconsole.h"
#include <qwidget.h>

#include "xwell.h"


BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessWellHorizonIntersect)
EWellHorizonIntersect
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessWellHorizonIntersect)


CXProcessWellHorizonIntersect::CXProcessWellHorizonIntersect()
{	
}

CXProcessWellHorizonIntersect::~CXProcessWellHorizonIntersect()
{
}

void CXProcessWellHorizonIntersect::Calculate( CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXParameterWellHorzionIntersect* pIntersectPara = dynamic_cast<CXParameterWellHorzionIntersect*>(pPara);
	CXWell* pWell = dynamic_cast<CXWell*>(pParentObj);
	assert(pIntersectPara && pParentObj);


	m_pThread = new CXThreadWellHorizonIntersect(pWell, pIntersectPara);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();

	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()) );

	pProgress->show();
	m_pThread->start();
	pProgress->exec();
}

void CXProcessWellHorizonIntersect::slotFinishedComputing()
{
	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;
}
