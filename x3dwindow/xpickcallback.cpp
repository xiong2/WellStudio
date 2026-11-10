#include "xpickcallback.h"
#include "x3dpickablebuilder.h"

CXPickCallback::CXPickCallback(CX3DPickableBuilderAbstract * pBuilder) 
	: osg::NodeCallback(), m_pBuilder(pBuilder)
{
}

CXPickCallback::~CXPickCallback()
{
}

void CXPickCallback::operator()(osg::Node * node, osg::NodeVisitor * nv)
{
	traverse(node, nv);
}

void CXPickCallback::SetActive(bool bActive)
{
	m_pBuilder->SetActive(bActive);
}
