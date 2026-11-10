#include "stdafx.h"
#include "gsbmitembuilderfactory.h"
#include "xobject.h"

QGraphicsItem* GSBMItemBuilderFactory::Create(CXObject* pObj)
{
	auto found = m_tableBuilders.find(pObj->GetObjectType());
	if (found == m_tableBuilders.end())
		return nullptr;
    return found->second(pObj);
}

void GSBMItemBuilderFactory::Registered(EXObjectType objType, const Build& build)
{
	m_tableBuilders.emplace(objType, build);
}

void GSBMItemBuilderFactory::Registered(const std::initializer_list<EXObjectType>& listType, const Build& build)
{
	for (auto&& type : listType)
	{
		m_tableBuilders.emplace(type, build);
	}
}
