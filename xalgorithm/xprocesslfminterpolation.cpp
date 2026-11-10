#include "xprocesslfminterpolation.h"

#include "xparameterlfminterpolation.h"
#include "xthreadlfminterpolation.h"

#include "xobjecttype.h"
#include "xprocessfactory.h"
#include "xdlgcalculatingprogress.h"
#include "xglobal.h"
#include <cassert>
#include "xbaseconsole.h"
#include <qwidget.h>

#include "xparametermanager.h"
#include "xtree.h"
#include "xlfmupscalingattribute.h"
#include "xlfmupscalinggeometry.h"
#include "xlfmgeometry.h"
#include "xlfmattribute.h"
#include "xgeneralfolder.h"
#include "xalgorithmutility.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessLFMInterpolation)
ELFMInterpolation
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessLFMInterpolation)


CXProcessLFMInterpolation::CXProcessLFMInterpolation()
{
	m_pAttribute = NULL;
}

CXProcessLFMInterpolation::~CXProcessLFMInterpolation()
{
}

void CXProcessLFMInterpolation::Calculate(CXObject* pParentObj, CXBaseParameter* pPara)
{
	if (NULL == pParentObj)
		return;

	m_pParentObject = pParentObj;

	m_pPara = pPara;

	CXParameterLFMInterpolation* pIntPara = dynamic_cast<CXParameterLFMInterpolation*>(pPara);
	assert(pIntPara);

	CXLFMUpscalingAttribute* pAtt = dynamic_cast<CXLFMUpscalingAttribute*>(m_pParentObject);
	assert(pAtt);

	m_pThread = new CXThreadLFMInterpolation(pIntPara, pAtt);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()));

	pProgress->show();
	m_pThread->start();
	pProgress->exec();

	// calculate histogram
	if (m_pAttribute)
	{
		CXAlgorithmUtility::CalculateHistogram(m_pAttribute->GetDataFileName(), m_pAttribute->GetNI()*m_pAttribute->GetNJ(), m_pAttribute);
	}
}

void CXProcessLFMInterpolation::slotFinishedComputing()
{
	CXThreadLFMInterpolation* pThread = dynamic_cast<CXThreadLFMInterpolation*>(m_pThread);
	m_pAttribute = pThread->GetOutput();
	if (!m_pAttribute)
		return;

	CXLFMGeometry* pGeometry = m_pAttribute->GetLFM();
	assert(pGeometry);


	CXObject* pFolderObj = NULL;
	QList<CXObject*> listObj = pGeometry->GetChildren(EXLFMAttributeFolder, false);
	if (listObj.isEmpty())
	{
		pFolderObj = new CXGeneralFolder("Attributes", EXLFMAttributeFolder, "Folder.png");
		pGeometry->AddChild(pFolderObj);
	}
	else
	{
		pFolderObj = listObj.front();
	}

	// add data
	m_pAttribute->SetObjectName(pFolderObj->GetUnallocatedName(m_pAttribute->GetObjectName()));
	pFolderObj->AddChild(m_pAttribute);

	// add parameter
	CXParameterManager::Instance().AddParameter(m_pAttribute->GetObjectID(), *m_pPara);

	pFolderObj->AddEvent(EAdded);
	CXProcessEvent eventProcess;

	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;
}

