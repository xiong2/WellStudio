#include "xprocess3termavoinversion.h"
#include "xthreadavossinversion.h"
#include "xparameter3terminversion.h"
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

#include "x2dsurvey.h"
#include "x2dseismicline.h"
#include "xproject.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcess3TermAVOInversion)
EAVOInversion,
EAVOSSInversion
END_REGISTER_RPOCESS_TO_FACTORY(CXProcess3TermAVOInversion)


CXProcess3TermAVOInversion::CXProcess3TermAVOInversion()
{
}

CXProcess3TermAVOInversion::~CXProcess3TermAVOInversion()
{
}

void CXProcess3TermAVOInversion::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXParameter3TermInversion* pInversionPara = dynamic_cast<CXParameter3TermInversion*>(pPara);
	assert(pInversionPara);


	m_pThread = new CXThreadAVOSSInversion(pInversionPara);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();

	for (int i = 0; i < m_vecDV.size();++i)
	{
		CXAlgorithmUtility::CalculateHistogram(m_vecDV[i]->GetTraceFileName(), 
			m_vecDV[i]->GetSamplingQty(), m_vecDV[i]);
	}
}

void CXProcess3TermAVOInversion::slotFinishedComputing()
{
	CXThreadAVOSSInversion* pThread = dynamic_cast<CXThreadAVOSSInversion*>(m_pThread);

	m_vecDV = pThread->GetOutput();


	CXParameter3TermInversion* pInversionPara = dynamic_cast<CXParameter3TermInversion*>(m_pPara);
	assert(pInversionPara);

	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(pInversionPara->GetPrestackDVID()));
	if (!pDV)
	{
		vector<QUuid> vecDVID = pInversionPara->GetVecDVID();
		assert(!vecDVID.empty());

		pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(vecDVID[0]));
	}

	CXObject* pSurvey = ::GetObjectByID(pDV->GetSurveyID());
	assert(pSurvey);

	CXObject* pFolderObj = NULL;
	QList<CXObject*> listObj = pSurvey->GetChildren(EX3TermAVOInversionFolder, false);
	if (listObj.isEmpty())
	{
		pFolderObj = new CXGeneralFolder("Inversion Results", EX3TermAVOInversionFolder, "Folder.png");
		pSurvey->AddChild(pFolderObj);
	}
	else
	{
		pFolderObj = listObj.front();
	}

	// add data
	for (int i = 0; i < m_vecDV.size(); ++i)
	{
		m_vecDV[i]->SetObjectName(pFolderObj->GetUnallocatedName(m_vecDV[i]->GetObjectName()));
		pFolderObj->AddChild(m_vecDV[i]);

		// add parameter
		CXParameterManager::Instance().AddParameter(m_vecDV[i]->GetObjectID(), *m_pPara);
	}

	pFolderObj->AddEvent(EAdded);
	CXProcessEvent eventProcess;

	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;
	
}

