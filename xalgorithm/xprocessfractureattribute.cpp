#include "xprocessfractureattribute.h"
#include "xthreadfractureattribute.h"
#include "xparameterfractureattribute.h"
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

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessFractureAttribute)
EFractureAttribute
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessFractureAttribute)


CXProcessFractureAttribute::CXProcessFractureAttribute()
{
}

CXProcessFractureAttribute::~CXProcessFractureAttribute()
{
}

void CXProcessFractureAttribute::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXParameterFractureAttribute* pAVOPara = dynamic_cast<CXParameterFractureAttribute*>(pPara);
	assert(pAVOPara);


	m_pThread = new CXThreadFractureAttribute(pAVOPara);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();

	for (int i = 0; i < m_vecDV.size(); ++i)
	{
		CXAlgorithmUtility::CalculateHistogram(m_vecDV[i]->GetTraceFileName(),
			m_vecDV[i]->GetSamplingQty(), m_vecDV[i]);
	}
}

void CXProcessFractureAttribute::slotFinishedComputing()
{
	CXThreadFractureAttribute* pThread = dynamic_cast<CXThreadFractureAttribute*>(m_pThread);

	m_vecDV = pThread->GetOutput();


	CXParameterFractureAttribute* pAVOPara = dynamic_cast<CXParameterFractureAttribute*>(m_pPara);
	assert(pAVOPara);

	CXSeismicDataVolume* pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(pAVOPara->GetAzimuthDVID()));
	assert(pDV);

	CXObject* pSurvey = ::GetObjectByID(pDV->GetSurveyID());
	assert(pSurvey);

	CXObject* pFolderObj = NULL;
	QList<CXObject*> listObj = pSurvey->GetChildren(EXFractureAnalysisAVO, false);
	if (listObj.isEmpty())
	{
		pFolderObj = new CXGeneralFolder("AVAz Results", EXFractureAnalysisAVO, "Folder.png");
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



