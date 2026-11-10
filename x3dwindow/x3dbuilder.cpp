#include "x3dbuilder.h"
#include "x3dwindow.h"

#include <osg/ComputeBoundsVisitor>

CX3DBuilderAbstract::~CX3DBuilderAbstract()
{
	m_pCurWin = NULL;
	m_pBuilderNode = NULL;
	m_bScalable = true;
}

osg::ref_ptr<osg::Group> CX3DBuilderAbstract::GetBuilderNode()
{
	return m_pBuilderNode;
}

osg::BoundingBox CX3DBuilderAbstract::GetBoundBox()
{
	osg::ComputeBoundsVisitor cbVisitor;
	m_pBuilderNode->accept(cbVisitor);
	return cbVisitor.getBoundingBox();
}

void CX3DBuilderAbstract::SetWindowAndCoordMap(CXWindow *pCurrentWindow, CX3DGlobalCoordMap* pCoordMap)
{
	m_pCurWin = pCurrentWindow;
	m_pCoordMap = pCoordMap;
}

void CX3DBuilderAbstract::SetBuilderNode(osg::ref_ptr<osg::Group> builderNode)
{
	m_pBuilderNode = builderNode;
}

void CX3DBuilderAbstract::SetObjectID(const QUuid& objID)
{
	m_objID = objID;
}

bool CX3DBuilderAbstract::IsScalable()
{
	return m_bScalable;
}

const QUuid& CX3DBuilderAbstract::GetObjectID() const
{
	return m_objID;
}

CXWindow * CX3DBuilderAbstract::GetCurWin()
{
	return m_pCurWin;
}

CX3DGlobalCoordMap* CX3DBuilderAbstract::GetCoordMap()
{
	return m_pCoordMap;
}