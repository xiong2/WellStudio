#include "xprocesslfmupscaling.h"
#include "xparameterupscaling.h"
#include "xthreadlfmupscaling.h"

#include "xobjecttype.h"
#include "xprocessfactory.h"
#include "xdlgcalculatingprogress.h"
#include "xglobal.h"
#include <cassert>
#include "xbaseconsole.h"
#include <qwidget.h>

#include "xparametermanager.h"
#include "xtree.h"
#include "xlfmupscalingattribute.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessLFMUpscaling)
ECalculateUpscaling
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessLFMUpscaling)


CXProcessLFMUpscaling::CXProcessLFMUpscaling()
{
}

CXProcessLFMUpscaling::~CXProcessLFMUpscaling()
{
}

void CXProcessLFMUpscaling::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pParentObject = pParentObj;

	m_pPara = pPara;

	CXParameterUpscaling* pUpscalingPara = dynamic_cast<CXParameterUpscaling*>(pPara);
	assert(pUpscalingPara);


	m_pThread = new CXThreadLFMUpscaling(pUpscalingPara, pParentObj);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();
}

void CXProcessLFMUpscaling::slotFinishedComputing()
{
	CXThreadLFMUpscaling* pThread = dynamic_cast<CXThreadLFMUpscaling*>(m_pThread);

	QList<CXLFMUpscalingAttribute*> listAtt = pThread->GetOutput();
	if (listAtt.isEmpty())
		return;

	for (int i = 0; i < listAtt.size(); ++i)
	{
		// add data
		listAtt[i]->SetObjectName(m_pParentObject->GetUnallocatedName(listAtt[i]->GetObjectName()));
		m_pParentObject->AddChild(listAtt[i]);

		// add parameter
		CXParameterManager::Instance().AddParameter(listAtt[i]->GetObjectID(), *m_pPara);

		listAtt[i]->AddEvent(EAdded);
		CXProcessEvent eventProcess;	
	}


	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;
}

