#ifndef XOBJECTFACTORY_H
#define XOBJECTFACTORY_H

#include <QMap>
#include "xobjecttype.h"
#include "xdata_global.h"

class IKEIO;

/**
* @class CkeObjectFactory in the file "rlobjectfactory.h"
* @brief The class provides an object factory to create a general object
* 
*/
class XDATA_EXPORT CXObjectFactory
{
		typedef IKEIO* (*CreateObjectPfunc)(void);

public:
	///@brief Get the unique instance of this factory
	static CXObjectFactory& Instance();

	///@brief  Register a parameter. It can only be invoked by within the  macro REGISTER_TO_GENERAL_FACTORY
	void RegisterObject(EXObjectType eObjType, CreateObjectPfunc pFunc);
	
	///@brief Create a CGmSeismicParameter
	IKEIO* CreateObject(EXObjectType eObjType);

private:
	CXObjectFactory() {}
	QMap<EXObjectType, CreateObjectPfunc> m_mapObject;
};



///@brief Register one CXObject to the above factory
#define REGISTER_OBJECT_TO_FACTORY(eObjType, className)	\
namespace NXObject \
{\
	IRLIO* Create##className() { return new className();} \
	class CKe##className##Helper \
	{ \
	public: \
		CKe##className##Helper() \
		{ \
			CXObjectFactory::Instance().RegisterObject(eObjType, &Create##className);	\
		} \
	}; \
}; \
NXObject::CKe##className##Helper g_CKe##className##Helper;

///@brief Register one or multiple CXObjectS to the above factory
#define BEGIN_REGISTER_OBJECT_TO_FACTORY(className) \
namespace NXObject \
{ \
	EXObjectType g_##className[]= { \

#define END_REGISTER_OBJECT_TO_FACTORY(className) \
	,EXEnd }; \
	IKEIO* Create##className() { return new className();} \
	class CKe##className##Helper \
	{ \
	public: \
		CKe##className##Helper() \
		{ \
			for (int i=0; g_##className[i] != EXEnd; ++i) \
				CXObjectFactory::Instance().RegisterObject(g_##className[i], &Create##className); \
		} \
	}; \
}; \
NXObject::CKe##className##Helper g_CKe##className##Helper;


#endif // RLOBJECTFACTORY_H
