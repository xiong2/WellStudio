#ifndef GSBMITEMBUILDERFACTORY_H
#define GSBMITEMBUILDERFACTORY_H

#include <unordered_map>
#include <functional>
#include "xobjecttype.h"

class QGraphicsItem;
class CXObject;

/**
@class  GSBMItemBuilderFactory provided in the file "gsbmitembuildfactory.h"
@brief  The class provides a build factory for QGraphicsItem.
@author pezy
@date   2018-04-18
@sa
*/
class GSBMItemBuilderFactory
{
public:
	using Build = std::function<QGraphicsItem*(CXObject* pObj)>;

	QGraphicsItem* Create(CXObject* pObj);
	void Registered(EXObjectType objType, const Build& build);
	void Registered(const std::initializer_list<EXObjectType>& listType, const Build& build);

private:
	std::unordered_map<EXObjectType, Build> m_tableBuilders;
};

#endif // GSBMITEMBUILDERFACTORY_H
