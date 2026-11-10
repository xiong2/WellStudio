#include "xprocessextracthorizonatt.h"
#include "xthreadextracthorizonatt.h"
#include "xparameterextracthorizonatt.h"
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
#include "x3dhorizon.h"

#include "xproject.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessExtractHorizonAtt)
EExtractHorizonAttribute
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessExtractHorizonAtt)


CXProcessExtractHorizonAtt::CXProcessExtractHorizonAtt()
{
}

CXProcessExtractHorizonAtt::~CXProcessExtractHorizonAtt()
{
}

void CXProcessExtractHorizonAtt::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXParameterExtractHorizonAtt* pAttPara = dynamic_cast<CXParameterExtractHorizonAtt*>(pPara);
	assert(pAttPara);


	m_pThread = new CXThreadExtractHorizonAtt(pAttPara);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();

}

void CXProcessExtractHorizonAtt::slotFinishedComputing()
{
	CXThreadExtractHorizonAtt* pThread = dynamic_cast<CXThreadExtractHorizonAtt*>(m_pThread);

	std::vector<CX3DHorizon*> vecAtt = pThread->GetOutput();


	CXParameterExtractHorizonAtt* pAttPara = dynamic_cast<CXParameterExtractHorizonAtt*>(m_pPara);
	assert(pAttPara);

	CX3DHorizon* pParentHor = dynamic_cast<CX3DHorizon*>(::GetObjectByID(pAttPara->GetHorizonID()));
	assert(pParentHor);

	CXObject* pFolderObj = NULL;
	QList<CXObject*> listObj = pParentHor->GetChildren(EXHorizonAttributeFolder, false);
	if (listObj.isEmpty())
	{
		pFolderObj = new CXGeneralFolder("Horizon Attributes", EXHorizonAttributeFolder, "Folder.png");
		pParentHor->AddChild(pFolderObj);
	}
	else
	{
		pFolderObj = listObj.front();
	}

	// add data
	for (int i = 0; i < vecAtt.size(); ++i)
	{
		vecAtt[i]->SetObjectName(pFolderObj->GetUnallocatedName(vecAtt[i]->GetObjectName()));
		pFolderObj->AddChild(vecAtt[i]);

		// add parameter
		CXParameterManager::Instance().AddParameter(vecAtt[i]->GetObjectID(), *m_pPara);
	}

	pFolderObj->AddEvent(EAdded);
	CXProcessEvent eventProcess;

	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;

}


