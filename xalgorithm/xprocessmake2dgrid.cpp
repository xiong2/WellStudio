#include "xprocessmake2dgrid.h"
#include "xthreadmake2dgrid.h"
#include "xobjecttype.h"
#include "xprocessfactory.h"
#include "xdlgcalculatingprogress.h"
#include "xparametermake2dgrid.h"
#include "xglobal.h"
#include "xwelltops.h"
#include <cassert>
#include "xbaseconsole.h"
#include <qwidget.h>

#include "x3dsurface.h"
#include "xgeneralfolder.h"
#include "xparametermanager.h"
#include "xtree.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessMake2DGrid)
EMake2DGRid
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessMake2DGrid)


CXProcessMake2DGrid::CXProcessMake2DGrid()
{	
}

CXProcessMake2DGrid::~CXProcessMake2DGrid()
{
}

void CXProcessMake2DGrid::Calculate( CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXParameterMake2DGrid* pMake2DParameter = dynamic_cast<CXParameterMake2DGrid*>(pPara);	
	assert(pMake2DParameter);


	m_pThread = new CXThreadMake2DGrid(pMake2DParameter, pParentObj);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();

	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()) );

	pProgress->show();
	m_pThread->start();
	pProgress->exec();
}

void CXProcessMake2DGrid::slotFinishedComputing()
{
	CXThreadMake2DGrid* pThread = dynamic_cast<CXThreadMake2DGrid*>(m_pThread);

	std::vector<CX3DSurface*> vecOutput = pThread->GetOutput3DSurface();

	// Add data to the project 
	CXGeneralFolder* pSurfaceFolder = dynamic_cast<CXGeneralFolder*>(::GetRootObjectFolder(EXSurfaceFolder));
	assert(pSurfaceFolder);

	// Add data and parameter
	for (int i=0; i<vecOutput.size(); ++i)
	{
		QString strObjName = pSurfaceFolder->GetUnallocatedName(vecOutput[i]->GetObjectName());
		vecOutput[i]->SetObjectName(strObjName);
		pSurfaceFolder->AddChild(vecOutput[i]);

		CXParameterManager::Instance().AddParameter(vecOutput[i]->GetObjectID(), *m_pPara);
	}

	// Add node
	for (int i=0; i<vecOutput.size(); ++i)
	{
		::AddObjectEvent(vecOutput[i]);
	}	

	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;
}