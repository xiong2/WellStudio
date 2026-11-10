#include "xprocessengine.h"

#include <qdialog.h>
#include <QDesktopWidget>
#include <cassert>

#include "xobject.h"
#include "xbaseparameter.h"
#include "xprocessfactory.h"
#include "xobjectfactory.h"
#include "xprocess.h"
#include "xglobal.h"
#include "xbaseconsole.h"

CXProcessEngine::CXProcessEngine(CXObject* pCurrentObj, EXObjectType eType)
{
	m_pCurrentObject = pCurrentObj;

	m_eGeneralObjectType = eType;
	
	m_pParameter = NULL;
}

CXProcessEngine::~CXProcessEngine()
{
}


void CXProcessEngine::Calculate(bool bModal)
{
	// Get parameter
	CXBaseParameter* pPara = dynamic_cast<CXBaseParameter*>(CXObjectFactory::Instance().CreateObject(m_eGeneralObjectType));
	if (!pPara)
		return;

	// Get the dialog to retrieve the array of parameters
	QWidget* pParentWidget = ((CXBaseConsole*)::GetConsole())->GetMainWindowWidget();
	QDialog* pGeneralDlg = CXProcessFactory::Instance().CreateProcessDialog (m_eGeneralObjectType, pPara, m_pCurrentObject, pParentWidget);
	assert(pGeneralDlg);

	_SetWidgetSize(pGeneralDlg);
	if (!bModal)
		pGeneralDlg->show();

	pGeneralDlg->setFocus();

	// First parameter
	if (pGeneralDlg->exec() == QDialog::Accepted)
	{
		IKEProcess* pProcess = CXProcessFactory::Instance().CreateProcess(m_eGeneralObjectType);
		if(pProcess==NULL)
			return;
		
		assert(pProcess);

		pProcess->Calculate(m_pCurrentObject, pPara);
		delete pProcess;
	}

	delete pPara;
}



void CXProcessEngine::_SetWidgetSize(QWidget* pWidget)
{
	QDesktopWidget widget;
	QRect rectScreen =  widget.screenGeometry();
	
	pWidget->setGeometry(rectScreen.center().x()/2,rectScreen.center().y()/2,pWidget->width(),pWidget->height());
}

void CXProcessEngine::CalculateOnly()
{
	if (!m_pCurrentObject)
		return;

	IKEProcess* pProcess = CXProcessFactory::Instance().CreateProcess(m_eGeneralObjectType);
	assert(pProcess);

	CXBaseParameter* pPara = dynamic_cast<CXBaseParameter*>(CXObjectFactory::Instance().CreateObject(m_eGeneralObjectType));

	pProcess->Calculate(m_pCurrentObject, pPara);
	delete pProcess;

	if (NULL != pPara)
		delete pPara;
}