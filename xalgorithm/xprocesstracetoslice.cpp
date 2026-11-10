#include "xprocesstracetoslice.h"
#include "xthreadtracetoslice.h"
#include "xobjecttype.h"
#include "xprocessfactory.h"
#include "xdlgcalculatingprogress.h"
#include "xglobal.h"
#include <cassert>
#include "xbaseconsole.h"
#include <qwidget.h>

#include "xseismicdatavolume.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessTraceToSlice)
ETraceToSlice
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessTraceToSlice)


CXProcessTraceToSlice::CXProcessTraceToSlice()
{	
}

CXProcessTraceToSlice::~CXProcessTraceToSlice()
{
}

void CXProcessTraceToSlice::Calculate( CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(pParentObj);
	if (!pDV)
        return;

	m_pThread = new CXThreadTraceToSlice(pDV);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();

	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()) );

	pProgress->show();
	m_pThread->start();
	pProgress->exec();
}

void CXProcessTraceToSlice::slotFinishedComputing()
{
	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;
}
