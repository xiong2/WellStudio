#include "xprocessmodelintersection.h"

#include <cassert>

#include "xobjecttype.h"
#include "xprocessfactory.h"
#include "xglobal.h"
#include "xgridmodel.h"
#include "xparametermodelintersecion.h"
#include "xdlgcalculatingprogress.h"
#include "xbaseconsole.h"
#include "xparametermanager.h"
#include "xtree.h"
#include "xintersectiongrid.h"
#include "xthreadmodelintersecion.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessModelIntersection)
EModelIncision
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessModelIntersection)

CXProcessModelIntersection::CXProcessModelIntersection(void)
{
}

CXProcessModelIntersection::~CXProcessModelIntersection()
{
}

void CXProcessModelIntersection::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (nullptr == pParentObj)
		return;

	m_pPara			= pPara;
	m_pParentObject = pParentObj;

	auto pIncisionPara	= dynamic_cast<CXParameterModelIntersection*>(pPara);
	auto pGridModel		= dynamic_cast<CXGridModel*>(pParentObj);

	assert(pIncisionPara && pGridModel);

	m_pThread = new CXThreadModelIntersection(pGridModel, pIncisionPara);

	auto pBaseConsole = reinterpret_cast<CXBaseConsole *>(::GetConsole());
	assert(pBaseConsole);

	QWidget* pParentWidget = pBaseConsole->GetMainWindowWidget();
	auto pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);
	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()) );

	pProgress->show();
	m_pThread->start();
	pProgress->exec();
}

void CXProcessModelIntersection::slotFinishedComputing()
{
	auto pThread = dynamic_cast<CXThreadModelIntersection*>(m_pThread);

	std::vector<CXIntersectionGrid*> vecOutput = pThread->GetOutputIntersection();

	// Add data and parameter
	for (size_t i = 0; i < vecOutput.size(); ++i) {
		QString strObjName = m_pParentObject->GetUnallocatedName(vecOutput[i]->GetObjectName());
		vecOutput[i]->SetObjectName(strObjName);
		m_pParentObject->AddChild(vecOutput[i]);

		CXParameterManager::Instance().AddParameter(vecOutput[i]->GetObjectID(), *m_pPara);
	}
	
	// Add node
	for (size_t i=0; i<vecOutput.size(); ++i) {
		::AddObjectEvent(vecOutput[i]);
	}	

	// Delete the thread
	delete m_pThread;
	m_pThread = nullptr;
}