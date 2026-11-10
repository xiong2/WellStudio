#include "xprocessbuildlfm.h"
#include "xthreadbuildlfm.h"
#include "xparameterbuildlfm.h"
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
#include "xlfmgeometry.h"
#include "xalgorithmutility.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessBuildLFM)
EBuildLowFreuqencyModel
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessBuildLFM)


CXProcessBuildLFM::CXProcessBuildLFM()
{
	m_pLFM = NULL;
}

CXProcessBuildLFM::~CXProcessBuildLFM()
{
}

void CXProcessBuildLFM::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXParameterBuildLFM* pLFMPara = dynamic_cast<CXParameterBuildLFM*>(pPara);
	assert(pLFMPara);


	m_pThread = new CXThreadBuildLFM(pLFMPara);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();	

	// calculate histogram
	if (m_pLFM)
	{
		CXAlgorithmUtility::CalculateHistogram(m_pLFM->GetDataFileName(), m_pLFM->GetUTM().GetNI()*m_pLFM->GetUTM().GetNJ(), m_pLFM);
	}
}

void CXProcessBuildLFM::slotFinishedComputing()
{
	CXThreadBuildLFM* pThread = dynamic_cast<CXThreadBuildLFM*>(m_pThread);

	m_pLFM = pThread->GetLFM();
	if (!m_pLFM)
		return;

	CXObject *pLFMFolder = ::GetRootObjectFolder(EXLFMFolder);
	assert(pLFMFolder);

	// add LFM
	QString strLFMName = pLFMFolder->GetUnallocatedName(m_pLFM->GetObjectName());
	m_pLFM->SetObjectName(strLFMName);
	pLFMFolder->AddChild(m_pLFM);

	// add parameter
	CXParameterManager::Instance().AddParameter(m_pLFM->GetObjectID(), *m_pPara);

	m_pLFM->AddEvent(EAdded);
	CXProcessEvent eventProcess;

	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;
}

