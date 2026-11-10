#ifndef CRLBUILDERFACTORY_H_H
#define CRLBUILDERFACTORY_H_H

#include <qmap.h>
#include "xobjecttype.h"
#include "x3dbuilder.h"

struct CXDrawStylePair
{
	int objType;
	int winType;
};
class X3DWINDOW_EXPORT CXBuilderFactory
{
	typedef CX3DBuilderAbstract* (*CreateBuilderPfunc)(void);

public:	
	CX3DBuilderAbstract* CreateBuilder(EXObjectType objType,EXWindowType winType)
	{
		QPair<int,int> curDrawStylePair;
		curDrawStylePair.first=(int)objType;
		curDrawStylePair.second=(int)winType;
		CreateBuilderPfunc pFunc = m_mapBuilder.value(curDrawStylePair, NULL);
		if (pFunc)
		{
			CX3DBuilderAbstract* pBuilder = (*pFunc)();
			return pBuilder;
		}
		else
			return NULL;
	}

	void RegisterBuilder(CXDrawStylePair objType, CreateBuilderPfunc pFunc)
	{
		QPair<int,int> curDrawStylePair;
		curDrawStylePair.first=(int)objType.objType;
		curDrawStylePair.second=(int)objType.winType;
		m_mapBuilder.insert(curDrawStylePair, pFunc);
	}

	static CXBuilderFactory& Instance()
	{
		static CXBuilderFactory builderFactory;

		return builderFactory;
	}

private:
    CXBuilderFactory() {}

	QMap<QPair<int,int>,CreateBuilderPfunc> m_mapBuilder;	
};


///@brief Register one or multiple node builders to the above factory
#define BEGIN_REGISTER_BUILDER_TO_FACTORY(className) \
namespace NXBuilder \
{ \
	CXDrawStylePair g_##className##DrawStylePair[]= { \

#define END_REGISTER_BUILDER_TO_FACTORY(className) \
	,{-1,-1} }; \
	CX3DBuilderAbstract* Create##className() { return new className();} \
	class CX##className##Helper \
	{ \
	public: \
		CX##className##Helper() \
		{ \
			for (int i=0; g_##className##DrawStylePair[i].objType!= -1&&g_##className##DrawStylePair[i].winType!= -1; ++i) \
				CXBuilderFactory::Instance().RegisterBuilder(g_##className##DrawStylePair[i], &Create##className); \
		} \
	}; \
}; \
NXBuilder::CX##className##Helper g_CX##className##Helper;


#endif