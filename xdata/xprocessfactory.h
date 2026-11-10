#ifndef XPROCESSFACTORY_H
#define XPROCESSFACTORY_H

#include "xdata_global.h"
#include <qmap.h>
#include "xobjecttype.h"

class IKEProcess;
class CXBaseParameter;
class CXObject;
class QDialog;
class QWidget;

/**
* @class CXProcessFactory in the file "keprocessfactory.h"
* @brief The class provides an object factory to hold all different processes
* 
* @author Yong Shu 
* @date 5/16/2014
* @see 
*/
class XDATA_EXPORT CXProcessFactory
{
	typedef IKEProcess* (*CreateProcessPfunc)(void);	
	typedef QDialog* (*CreateProcessDialogPfunc)(CXBaseParameter* pPara, CXObject* pParentObj, QWidget*);
	typedef QWidget* (*CreateProcessWidgetPfunc)(CXBaseParameter* pPara, CXObject* pParentObj, QWidget*);

public:
	///@brief Get the unique instance of this factory
	static CXProcessFactory& Instance();

	///@brief  Add one attribute method
	void RegisterProcess(EXObjectType eGeneralObjectType, CreateProcessPfunc pFunc);

	///@brief  Register a dialog to retrieve the parameter. It can only be invoked by within the  maco REGISTER_TO_GENERAL_FACTORY
	void RegisterProcessDialog(EXObjectType eGeneralObjectType, CreateProcessDialogPfunc pFunc);

	///@brief  Register a property widget to display the parameter. It can only be invoked by within the  maco REGISTER_TO_GENERAL_FACTORY
	void RegisterProcessWidget(EXObjectType eGeneralObjectType, CreateProcessWidgetPfunc pFunc);
	
	///@brief Retrieve one attribute method according to the attribute type
	IKEProcess* CreateProcess( EXObjectType eGeneralObjectType);

	///@brief Create a parameter dialog
	QDialog* CreateProcessDialog(EXObjectType eGeneralObjectType, CXBaseParameter* pPara, CXObject* pParentObj, QWidget* pParent=NULL);

	///@brief Create a parameter dialog
	QWidget* CreateProcessWidget(EXObjectType eGeneralObjectType, CXBaseParameter* pPara, CXObject* pParentObj, QWidget* pParent=NULL);

private:
	CXProcessFactory() {}
	QMap<EXObjectType, CreateProcessPfunc> m_mapCreateProcess;	
	QMap<EXObjectType, CreateProcessDialogPfunc> m_mapCreateDialog;
	QMap<EXObjectType, CreateProcessWidgetPfunc> m_mapCreateWidget;
};

///@brief Register one or multiple attribute methods to the above factory
#define BEGIN_REGISTER_PROCESS_TO_FACTORY(className) \
namespace NXObject \
{ \
	EXObjectType g_##className[]= { \

#define END_REGISTER_RPOCESS_TO_FACTORY(className) \
    ,EXEnd }; \
    IKEProcess* Create##className() { return new className();} \
   	class CX##className##Helper \
	{ \
	public: \
		CX##className##Helper() \
		{ \
		    for (int i=0; g_##className[i] != EXEnd; ++i) \
			     CXProcessFactory::Instance().RegisterProcess(g_##className[i], &Create##className);	\
		} \
	}; \
}; \
NXObject::CX##className##Helper g_CX##className##Helper;

///@brief Register one and multiple dialog to the above factory
#define BEGIN_REGISTER_PROCESS_DIALOG_TO_FACTORY(className) \
namespace NXObject \
{ \
	EXObjectType g_##className[]= { \

#define END_REGISTER_PROCESS_DIALOG_TO_FACTORY(className) \
	,EXEnd }; \
	QDialog* Create##className(CXBaseParameter* pPara, CXObject* pParentObj, QWidget* pParent) { return new className(pPara, pParentObj, pParent);} \
	class CX##className##Helper \
	{ \
	public: \
		CX##className##Helper() \
		{ \
			for (int i=0; g_##className[i] != EXEnd; ++i) \
				CXProcessFactory::Instance().RegisterProcessDialog(g_##className[i], &Create##className); \
		} \
	}; \
}; \
NXObject::CX##className##Helper g_CX##className##Helper;

///@brief Register one and multiple widget to the above factory
#define BEGIN_REGISTER_PROCESS_WIDGET_TO_FACTORY(className) \
namespace NXObject \
{ \
	EXObjectType g_##className[]= { \

#define END_REGISTER_RPOCESS_WIDGET_TO_FACTORY(className) \
	,EXEnd }; \
	QWidget* Create##className(CXBaseParameter* pPara, CXObject* pParentObj, QWidget* pParent) { return new className(pPara, pParentObj, pParent);} \
	class CX##className##Helper \
	{ \
	public: \
		CX##className##Helper() \
		{ \
			for (int i=0; g_##className[i] != EXEnd; ++i) \
				CXProcessFactory::Instance().RegisterProcessWidget(g_##className[i], &Create##className); \
		} \
	}; \
}; \
NXObject::CX##className##Helper g_CX##className##Helper;



#endif // KEPROCESSFACTORY_H
