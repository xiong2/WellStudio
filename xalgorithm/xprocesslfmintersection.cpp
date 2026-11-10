#include "xprocesslfmintersection.h"
#include "xparameterlfmintersecton.h"
#include "xthreadintersectlfm.h"

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
#include "xlfmupscalinggeometry.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessLFMIntersection)
EIntersectLFMAndWell
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessLFMIntersection)


CXProcessLFMIntersection::CXProcessLFMIntersection()
{
}

CXProcessLFMIntersection::~CXProcessLFMIntersection()
{
}

void CXProcessLFMIntersection::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pParentObject = pParentObj;

	m_pPara = pPara;

	CXParameterLFMIntersecton* pLFMPara = dynamic_cast<CXParameterLFMIntersecton*>(pPara);
	assert(pLFMPara);


	m_pThread = new CXThreadIntersectLFM(pLFMPara, pParentObj);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();	
}

void CXProcessLFMIntersection::slotFinishedComputing()
{
	CXThreadIntersectLFM* pThread = dynamic_cast<CXThreadIntersectLFM*>(m_pThread);

	CXObject* pGeometry = pThread->GetOutputObj();
	if (!pGeometry)
		return;

	CXObject* pFolderObj = NULL;
	QList<CXObject*> listObj = m_pParentObject->GetChildren(EXLFMUpscalingResultFolder, false);
	if (listObj.isEmpty())
	{
		pFolderObj = new CXGeneralFolder("Upscaling Result", EXLFMUpscalingResultFolder, "Folder.png");
		m_pParentObject->AddChild(pFolderObj);
	}
	else
	{
		pFolderObj = listObj.front();
	}

	//  add data
	pGeometry->SetObjectName(pFolderObj->GetUnallocatedName(pGeometry->GetObjectName()));
	pFolderObj->AddChild(pGeometry);

	// add parameter
	CXParameterManager::Instance().AddParameter(pGeometry->GetObjectID(), *m_pPara);

	pFolderObj->AddEvent(EAdded);
	CXProcessEvent eventProcess;

	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;
}

