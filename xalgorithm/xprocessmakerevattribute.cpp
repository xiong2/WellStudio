#include "xprocessmakerevattibute.h"
#include "xthreadmakerevattribute.h"
#include "xwellcells.h"
#include "xobjecttype.h"
#include "xprocessfactory.h"
#include "xdlgcalculatingprogress.h"
#include "xpropertymodel.h"
#include "xglobal.h"
#include <cassert>
#include "xbaseconsole.h"
#include <qwidget.h>
#include "xtree.h"
#include "xgeneralfolder.h"
#include "xreservoirmodel.h"
#include "xgridmodel.h"
#include "xgridcell.h"
#include "xthreadmodelintersecion.h"

BEGIN_REGISTER_PROCESS_TO_FACTORY(CXProcessMakeRevAttribute)
	EMakePropertyModel
END_REGISTER_RPOCESS_TO_FACTORY(CXProcessMakeRevAttribute)


CXProcessMakeRevAttribute::CXProcessMakeRevAttribute()
{

}
CXProcessMakeRevAttribute::~CXProcessMakeRevAttribute()
{

}
void CXProcessMakeRevAttribute::Calculate(CXObject* pParentObj, CXBaseParameter* pBasePara)
{
	if (NULL == pParentObj)
		return;	

	CXParameterMakeRevInterpolation *pPara = dynamic_cast<CXParameterMakeRevInterpolation*>(pBasePara);
	if(NULL== pPara)
		return;

	CXObject *pWellCondition=pParentObj->GetParent();

	// grid model
	m_pParentObject = pWellCondition->GetParent();
	
	if(pWellCondition->GetObjectType()!=EXWellCondition)
	{
		return;
	}
	
	m_pThread = new CRLThreadMakeRevAttribute(pPara,pParentObj);

	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();

	CXDlgCalculatingProgress* pProgress = new CXDlgCalculatingProgress(m_pThread, pParentWidget);

	connect(pProgress, SIGNAL(signalFinishedComputing()), this, SLOT(slotFinishedComputing()) );

	pProgress->show();
	m_pThread->start();
	pProgress->exec();
}

void CXProcessMakeRevAttribute::slotFinishedComputing()
{
	// Delete the thread
	CXReservoirModel *pRevObj=dynamic_cast<CXReservoirModel*>(m_pParentObject);
	CXGridModel *pGridMode=pRevObj->GetGridModel();
	
	QList<CXGridCell*> pAllGridCell=pGridMode->GetAllCells();
	CRLThreadMakeRevAttribute* pThread = dynamic_cast<CRLThreadMakeRevAttribute*>(m_pThread);

	//CXObject * pAttObject = pThread->GetAttrObject();
	double *pSrcData=pThread->GetAttData();
	//double *allData=pAttObject->GetData(pAllGridCell.size());
	double *pAllData=new double[pAllGridCell.size()];
	memcpy(pAllData,pSrcData,sizeof(double)*pAllGridCell.size());

	// Delete the thread
	delete m_pThread;
	m_pThread = NULL;

	CXPropertyModel *pPropObj=new CXPropertyModel("Rev PropertyModel");
	pPropObj->ResetData(pAllGridCell.size(),pAllData);
	QString strObjName = m_pParentObject->GetUnallocatedName(pPropObj->GetObjectName());
	pPropObj->SetObjectName(strObjName);
	// add data
	m_pParentObject->AddChild(pPropObj);
	::AddObjectEvent(pPropObj);
}