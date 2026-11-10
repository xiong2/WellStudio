#include "xprocessfactory.h"

CXProcessFactory& CXProcessFactory::Instance()
{
	static CXProcessFactory object;
	return object;
}

void CXProcessFactory::RegisterProcess(EXObjectType eGeneralObjectType, CreateProcessPfunc pFunc)
{
	m_mapCreateProcess.insert(eGeneralObjectType, pFunc);
}

IKEProcess* CXProcessFactory::CreateProcess( EXObjectType eGeneralObjectType)
{
	CreateProcessPfunc pFunc = m_mapCreateProcess.value(eGeneralObjectType, NULL);
	if (pFunc)
		return (*pFunc)();
	else
		return NULL;
}

void CXProcessFactory::RegisterProcessDialog(EXObjectType eGeneralObjectType, CreateProcessDialogPfunc pFunc)
{
	m_mapCreateDialog.insert(eGeneralObjectType, pFunc);
}

void CXProcessFactory::RegisterProcessWidget(EXObjectType eGeneralObjectType, CreateProcessWidgetPfunc pFunc)
{
	m_mapCreateWidget.insert(eGeneralObjectType, pFunc);
}

QDialog* CXProcessFactory::CreateProcessDialog(EXObjectType eGeneralObjectType, CXBaseParameter* pPara, CXObject* pParentObj, QWidget* pParent)
{
	CreateProcessDialogPfunc pFunc = m_mapCreateDialog.value(eGeneralObjectType, NULL);
	if (pFunc)
		return (*pFunc)(pPara, pParentObj, pParent);
	else
		return NULL;
}

QWidget* CXProcessFactory::CreateProcessWidget(EXObjectType eGeneralObjectType, CXBaseParameter* pPara, CXObject* pParentObj, QWidget* pParent)
{
	CreateProcessWidgetPfunc pFunc = m_mapCreateWidget.value(eGeneralObjectType, NULL);
	if (pFunc)
		return (*pFunc)(pPara, pParentObj, pParent);
	else
		return NULL;
}
