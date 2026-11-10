#include "xprocessgsinversion.h"
//#include "xgeobodydetectionthread.h"
#include "xparametersgsinversion.h"
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

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessGSInversion)
EGSInversion
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessGSInversion)

CXProcessGSInversion::CXProcessGSInversion()
{
}

CXProcessGSInversion::~CXProcessGSInversion()
{
}

void CXProcessGSInversion::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	//CXParametersGeobodyDetection* pGeobodyPara = dynamic_cast<CXParametersGeobodyDetection*>(pPara);
	//assert(pGeobodyPara);


	//m_pThread = new CXGeobodyDetectionThread(pGeobodyPara);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();

	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	//m_pThread->start();
	pProgress->exec();
}

void CXProcessGSInversion::slotFinishedComputing()
{
}