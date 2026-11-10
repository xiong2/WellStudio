#include "xprocessfractureinversion.h"
#include "xthreadfractureinversion.h"
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

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessFractureInversion)
EAnisotropyInversion
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessFractureInversion)


CXProcessFractureInversion::CXProcessFractureInversion()
{
	m_pDV = nullptr;
}

CXProcessFractureInversion::~CXProcessFractureInversion()
{
}

void CXProcessFractureInversion::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pPara = pPara;

	CXParameter3TermInversion* pInversionPara = dynamic_cast<CXParameter3TermInversion*>(pPara);
	assert(pInversionPara);


	m_pThread = new CXThreadFractureInversion(pInversionPara);

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

void CXProcessFractureInversion::slotFinishedComputing()
{
	CXThreadFractureInversion* pThread = dynamic_cast<CXThreadFractureInversion*>(m_pThread);

	m_pDV = pThread->GetOutput();


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
	QList<CXObject*> listObj = pSurvey->GetChildren(EXFractureInversionFolder, false);
	if (listObj.isEmpty())
	{
		pFolderObj = new CXGeneralFolder("Anisotropy Inversion", EXFractureInversionFolder, "Folder.png");
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

