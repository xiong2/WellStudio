#include <qdebug.h>

#include <qdatastream.h>
#include "xgeobody.h"
#include "xgeobodycollection.h"
#include "xobjectfactory.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXGeobodyCollection)
EXGeobodyCollection
END_REGISTER_OBJECT_TO_FACTORY(CXGeobodyCollection)

CXGeobodyCollection::CXGeobodyCollection(QString sName) : CXObject(sName)
{
	SetObjectType(EXGeobodyCollection);
	SetIconName("GeobodyCollection.png");
}

CXGeobodyCollection::~CXGeobodyCollection()
{
}