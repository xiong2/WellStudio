#include "xprocesspcafiltering.h"
#include "xthreadpcafiltering.h"
#include "xparameterpcafiltering.h"
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
#include "xseismicdatavolume.h"
#include "xalgorithmutility.h"

#include "xproject.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessPCAFiltering)
ESeismicPCAFiltering
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessPCAFiltering)


CXProcessPCAFiltering::CXProcessPCAFiltering()
{
	m_pDV = NULL;
}

CXProcessPCAFiltering::~CXProcessPCAFiltering()
{
}

void CXProcessPCAFiltering::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pParentObject = pParentObj;

	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(pParentObj);
	if (!pDV)
		return;

	m_pPara = pPara;

	CXParameterPCAFiltering* pFilteringPara = dynamic_cast<CXParameterPCAFiltering*>(pPara);
	assert(pFilteringPara);


	m_pThread = new CXThreadPCAFiltering(pFilteringPara, pDV);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();

	if (m_pDV)
		CXAlgorithmUtility::CalculateHistogram(m_pDV->GetTraceFileName(), m_pDV->GetSamplingQty(), m_pDV);

}

void CXProcessPCAFiltering::slotFinishedComputing()
{
	CXThreadPCAFiltering* pThread = dynamic_cast<CXThreadPCAFiltering*>(m_pThread);

	m_pDV = pThread->GetOutput();
	if (!m_pDV)
		return;

	m_pDV->SetObjectName(m_pParentObject->GetUnallocatedName(m_pDV->GetObjectName()));
	m_pParentObject->AddChild(m_pDV);

	// add parameter
	CXParameterManager::Instance().AddParameter(m_pDV->GetObjectID(), *m_pPara);

	m_pDV->AddEvent(EAdded);
	CXProcessEvent eventProcess;

	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;

}




