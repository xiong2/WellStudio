#include "xprocessanisotropyforwarding.h"
#include "xthreadanisotropyforwarding.h"
#include "xparameteranisotropyforwarding.h"
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

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessAnisotropyForwarding)
EAnisotrpicForwarding
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessAnisotropyForwarding)


CXProcessAnisotropyForwarding::CXProcessAnisotropyForwarding()
{
	m_pDV = nullptr;
}

CXProcessAnisotropyForwarding::~CXProcessAnisotropyForwarding()
{
}

void CXProcessAnisotropyForwarding::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXParameterAnisotropyForwarding* pForwardingPara = dynamic_cast<CXParameterAnisotropyForwarding*>(pPara);
	assert(pForwardingPara);


	m_pThread = new CXThreadAnisotropyForwarding(pForwardingPara);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();

	if (m_pDV)
	{
		CXAlgorithmUtility::CalculateHistogram(m_pDV->GetTraceFileName(),
			m_pDV->GetSamplingQty(), m_pDV);
	}
}

void CXProcessAnisotropyForwarding::slotFinishedComputing()
{
	CXThreadAnisotropyForwarding* pThread = dynamic_cast<CXThreadAnisotropyForwarding*>(m_pThread);

	m_pDV = pThread->GetOutput();


	CXParameterAnisotropyForwarding* pForwardingPara = dynamic_cast<CXParameterAnisotropyForwarding*>(m_pPara);
	assert(pForwardingPara);

	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(pForwardingPara->GetVpDVID()));
	assert(pDV);

	CXObject* pSurvey = ::GetObjectByID(pDV->GetSurveyID());
	assert(pSurvey);

	CXObject* pFolderObj = NULL;
	QList<CXObject*> listObj = pSurvey->GetChildren(EXAnisotropyForwardingFolder, false);
	if (listObj.isEmpty())
	{
		pFolderObj = new CXGeneralFolder("Anisotropy Forwarding", EXAnisotropyForwardingFolder, "Folder.png");
		pSurvey->AddChild(pFolderObj);
	}
	else
	{
		pFolderObj = listObj.front();
	}

	// add data
	m_pDV->SetObjectName(pFolderObj->GetUnallocatedName(m_pDV->GetObjectName()));
	pFolderObj->AddChild(m_pDV);

	// add parameter
	CXParameterManager::Instance().AddParameter(m_pDV->GetObjectID(), *m_pPara);


	pFolderObj->AddEvent(EAdded);
	CXProcessEvent eventProcess;

	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;

}


