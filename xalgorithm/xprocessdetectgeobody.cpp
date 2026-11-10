#include "xprocessdetectgeobody.h"
#include "xgeobodydetectionthread.h"
#include "xparametersgeobodydetection.h"
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
#include "xgeobody.h"
#include "xgeobodycollection.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessDetectGeobody)
EDetectGeobody
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessDetectGeobody)


CXProcessDetectGeobody::CXProcessDetectGeobody()
{
}

CXProcessDetectGeobody::~CXProcessDetectGeobody()
{
}

void CXProcessDetectGeobody::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXParametersGeobodyDetection* pGeobodyPara = dynamic_cast<CXParametersGeobodyDetection*>(pPara);
	assert(pGeobodyPara);


	m_pThread = new CXGeobodyDetectionThread(pGeobodyPara);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();

	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();
}

void CXProcessDetectGeobody::slotFinishedComputing()
{
	CXGeobodyDetectionThread* pThread = dynamic_cast<CXGeobodyDetectionThread*>(m_pThread);

	std::vector<CXGeobody*> vecOutput = pThread->GetOutput();
	if (vecOutput.empty())
		return;

	CXObject *pGFolder = ::GetRootObjectFolder(EXGeobodyFolder);
	assert(pGFolder);

	//	
	QString strGeobodyName = pGFolder->GetUnallocatedName(vecOutput[0]->GetObjectName());
	CXGeobodyCollection *pGeobodyCollection = new CXGeobodyCollection(strGeobodyName);
	CXParameterManager::Instance().AddParameter(pGeobodyCollection->GetObjectID(), *m_pPara);
	pGFolder->AddChild(pGeobodyCollection);

	// First geobody may be merged geobody
	int i = 0;
	if (vecOutput[i]->IsMerged())
	{
		vecOutput[i]->SetObjectName(strGeobodyName + " All");
		pGeobodyCollection->AddChild(vecOutput[i]);
		i++;
	}

	// rest of geobodies
	for (; i < vecOutput.size(); ++i)
	{
		CXGeobody *pNewBody = vecOutput[i];
		pNewBody->SetObjectName(strGeobodyName + " " + QString::number(i));
		pGeobodyCollection->AddChild(pNewBody);
	}

	pGFolder->AddEvent(EAdded);
	CXProcessEvent eventProcess;

	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;
}
