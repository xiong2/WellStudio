#include "xprocesspartialstack.h"
#include "xpartialstackthread.h"
#include "xparameterspartialstack.h"
#include "xobjecttype.h"
#include "xprocessfactory.h"
#include "xdlgcalculatingprogress.h"
#include "xglobal.h"
#include <cassert>
#include "xbaseconsole.h"
#include <qwidget.h>

#include "xgeneralfolder.h"
#include "xparametermanager.h"
#include "xtree.h"
#include "xalgorithmutility.h"
#include "xpartialstackthread.h"
#include "xseismicdatavolume.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessPartialStack)
EPartialStack
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessPartialStack)


CXProcessPartialStack::CXProcessPartialStack()
{
}

CXProcessPartialStack::~CXProcessPartialStack()
{
}

void CXProcessPartialStack::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXParametersPartialStack* pStackPara = dynamic_cast<CXParametersPartialStack*>(pPara);
	assert(pStackPara);

	m_pThread = new CXPartialStackThread(pStackPara);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();

	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();
}

void CXProcessPartialStack::slotFinishedComputing()
{
	CXPartialStackThread* pThread = dynamic_cast<CXPartialStackThread*>(m_pThread);

	CXSeismicDataVolume *pDV = pThread->GetOuputDV();
	if(pDV)
		CXAlgorithmUtility::CalculateHistogram(pDV->GetTraceFileName(), pDV->GetSamplingQty(), pDV);

	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;
}