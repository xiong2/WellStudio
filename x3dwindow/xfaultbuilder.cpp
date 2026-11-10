#include "xfaultbuilder.h"
#include "xgmfault.h"
#include "x3dglobalcoordmap.h"
#include "xgmmethod.h"
#include "xglobal.h"
#include "x3dbuilderfactory.h"
#include "x3dwindow.h"
#include "x3dscene.h"
#include <osgUtil/SmoothingVisitor>
#include "xviewinfo3dfaultsticks.h"
#include <osg/Point>
#include <osg/LineWidth>
#include <osg/BlendFunc>

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXGMFaultBuilder)
{EXGMFault,e3DWindow}
END_REGISTER_BUILDER_TO_FACTORY(CXGMFaultBuilder)

CXGMFaultBuilder::CXGMFaultBuilder()
{
	m_pFault = NULL;

	m_pVertices = NULL;
	m_pPlane = NULL;
	m_pLine = NULL;
	m_pPoint = NULL;

	m_pGeoNode = NULL;
}

CXGMFaultBuilder::~CXGMFaultBuilder()
{

}

osg::ref_ptr<osg::Group> CXGMFaultBuilder::Build(QUuid objId)
{
	if(m_pBuilderNode==NULL)
		m_pBuilderNode=new osg::Group;


	m_pFault = dynamic_cast<CXGMFault*>(::GetObjectByID(objId));
	if (!m_pFault)
		return NULL;

	m_pViewInfo = dynamic_cast<CXViewInfo3DFaultSticks*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pViewInfo)
		return NULL;

	m_pVertices = new osg::Vec3Array;
	_BuildVertices();

	m_pPlane = new osg::Geometry;
	_BuildPlane();

	m_pLine = new osg::Geometry;
	_BuildLines();

	m_pPoint = new osg::Geometry;
	_BuildPoints();

	m_pGeoNode = new osg::Geode;

	if (m_pViewInfo->GetDisplayPlane())
		m_pGeoNode->addDrawable(m_pPlane.get());

	if (m_pViewInfo->GetDisplayLine())
		m_pGeoNode->addDrawable(m_pLine.get());

	if (m_pViewInfo->GetDisplayPoint())
		m_pGeoNode->addDrawable(m_pPoint.get());
	
	m_pGeoNode->setName("modeled fault Geode");
	m_pGeoNode->setUserValue("objID",m_pFault->GetObjectID().toString().toStdString());
	
	m_pBuilderNode->addChild(m_pGeoNode.get());

	return m_pBuilderNode;

}


void CXGMFaultBuilder::_BuildVertices()
{
	if (!m_pFault)
		return;

	std::vector<osg::Vec3d> vecVertices;
	vector<vector<int> > vecVecIndex;
	vector<int> vecCount;

	CXGMMethod::CalcVerticesAndIndex(m_pFault, vecVertices, m_vecPillarVerticeIndex, m_vecCount);

	if (vecVertices.empty())
		return;

	int nSize = (int) vecVertices.size();
	m_pVertices->resize(nSize);
	osg::Vec3 vecLocal;
	for (int i=0; i<nSize; ++i)
	{
		m_pCoordMap->MapWorldToLocal(vecVertices[i], vecLocal);
		(*m_pVertices)[i] = vecLocal;
	}
}

void CXGMFaultBuilder::_BuildPlane()
{
	if (m_vecPillarVerticeIndex.size() < 2)
		return;

	// vertices
	m_pPlane->setVertexArray(m_pVertices.get());

	// colors
	osg::ref_ptr<osg::Vec4Array> pColor = new osg::Vec4Array;
	QColor color = m_pViewInfo->GetPlaneColor();
	pColor->push_back(osg::Vec4(color.redF(), color.greenF(), color.blueF(),  m_pViewInfo->GetOpacity()));
	m_pPlane->setColorArray(pColor.get(), osg::Array::BIND_OVERALL);

	m_pPlane->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	m_pPlane->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc);

	// normal
	m_pPlane->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	osgUtil::SmoothingVisitor::smooth( *m_pPlane );

	// Add quads
	osg::ref_ptr<osg::DrawElementsUInt> pIndices = new osg::DrawElementsUInt(GL_QUADS);

	unsigned int nK = m_vecCount.size() - 1;
	unsigned int nSize = m_vecPillarVerticeIndex.size();
	for (unsigned int k=0; k<nK-1; ++k)
	{
		for (unsigned int i=0; i<nSize-1; ++i)
		{
			pIndices->push_back(k*nSize + i);
			pIndices->push_back(k*nSize + i+1);
			pIndices->push_back((k+1)*nSize + i+1);
			pIndices->push_back((k+1)*nSize + i);
		}
	}
	
	m_pPlane->addPrimitiveSet(pIndices.get());

}

void CXGMFaultBuilder::_BuildLines()
{
	// vertices
	m_pLine->setVertexArray(m_pVertices.get());

	// colors
	osg::ref_ptr<osg::Vec3Array> pColor = new osg::Vec3Array;
	QColor color = m_pViewInfo->GetLineColor();
	pColor->push_back(osg::Vec3f(color.redF(), color.greenF(), color.blueF()));
	m_pLine->setColorArray(pColor.get(), osg::Array::BIND_OVERALL);

	// normal
	m_pLine->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	osgUtil::SmoothingVisitor::smooth( *m_pLine );

	// line width
	osg::ref_ptr<osg::LineWidth> pLineWidth = new osg::LineWidth;
	pLineWidth->setWidth(m_pViewInfo->GetLineWidth());
	osg::ref_ptr<osg::StateSet>  state = m_pLine->getOrCreateStateSet();
	state->setAttribute(pLineWidth);

	// horizon lines
	unsigned int nK = m_vecCount.size() - 1;	
	int nSum = 0;
	for (int k=0; k<nK; ++k)
	{
		m_pLine->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, nSum, m_vecCount[k+1]-m_vecCount[k]));
		nSum = m_vecCount[k+1];
	}

	// size line + pillars

	// head
	osg::ref_ptr<osg::DrawElementsUInt> pHeadIndices = new osg::DrawElementsUInt(GL_LINE_STRIP);
	for (int i=0; i<m_vecCount.size()-1; ++i)
	{
		pHeadIndices->push_back(m_vecCount[i]);
	}
	m_pLine->addPrimitiveSet(pHeadIndices.get());

	// Tail
	osg::ref_ptr<osg::DrawElementsUInt> pTailIndices = new osg::DrawElementsUInt(GL_LINE_STRIP);
	for (int i=1; i<m_vecCount.size(); ++i)
	{
		pTailIndices->push_back(m_vecCount[i]-1);
	}
	m_pLine->addPrimitiveSet(pTailIndices.get());

	// Pillar
	int nSize = m_vecPillarVerticeIndex.size();	
	for (int i=0; i<nSize; ++i)
	{
		osg::ref_ptr<osg::DrawElementsUInt> pPillarIndices = new osg::DrawElementsUInt(GL_LINE_STRIP);
		for (int k=0; k<nK; ++k)
		{
			pPillarIndices->push_back(m_vecPillarVerticeIndex.at(i).at(k));
		}
		m_pLine->addPrimitiveSet(pPillarIndices.get());
	}

}

void CXGMFaultBuilder::_BuildPoints()
{
	// vertices
	m_pPoint->setVertexArray(m_pVertices.get());

	// color
	osg::ref_ptr<osg::Vec3Array> pColor = new osg::Vec3Array;
	QColor color = m_pViewInfo->GetPointColor();
	pColor->push_back(osg::Vec3f(color.redF(), color.greenF(), color.blueF()));
	m_pPoint->setColorArray(pColor.get(), osg::Array::BIND_OVERALL);
	
	// normal
	m_pPoint->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	osgUtil::SmoothingVisitor::smooth( *m_pPoint );

	// point size
	osg::ref_ptr<osg::Point> pPoint = new osg::Point;
	pPoint->setSize(m_pViewInfo->GetPointSize());
	osg::ref_ptr<osg::StateSet>  state = m_pPoint->getOrCreateStateSet();
	state->setAttribute(pPoint);	

	// add points
	m_pPoint->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, m_pVertices->size()));
}

void CXGMFaultBuilder::UpdateNode(EEventType eType)
{
	if (m_pGeoNode == NULL)
		return;

	if (eType == EInfoChanged)
	{
		_UpdatePoint();
		_UpdateLine();
		_UpdataPlane();
	}
}

void CXGMFaultBuilder::_UpdatePoint()
{
	// Color
	osg::ref_ptr<osg::Vec3Array> pColor = dynamic_cast<osg::Vec3Array*>(m_pPoint->getColorArray());
	QColor color = m_pViewInfo->GetPointColor();
	(*pColor)[0].set(color.redF(), color.greenF(), color.blueF());
	m_pPoint->setColorArray(pColor);

	// Size
	osg::ref_ptr<osg::Point> pPoint = dynamic_cast<osg::Point*>(m_pPoint->getStateSet()->getAttribute((osg::StateAttribute::POINT)));
	pPoint->setSize(m_pViewInfo->GetPointSize());

	if (m_pViewInfo->GetDisplayPoint())
	{
		if (!m_pGeoNode->containsDrawable(m_pPoint.get()))
			m_pGeoNode->addDrawable(m_pPoint.get());
	}
	else
	{
		if (m_pGeoNode->containsDrawable(m_pPoint.get()))
		{
			m_pGeoNode->removeDrawable(m_pPoint.get());
		}
	}

}

void CXGMFaultBuilder::_UpdateLine()
{
	// color
	osg::ref_ptr<osg::Vec3Array> pColor = dynamic_cast<osg::Vec3Array*>(m_pLine->getColorArray());
	QColor color = m_pViewInfo->GetLineColor();
	(*pColor)[0].set(color.redF(), color.greenF(), color.blueF());
	m_pLine->setColorArray(pColor);

	// line width
	osg::ref_ptr<osg::LineWidth> pLineWidth = dynamic_cast<osg::LineWidth*>(m_pLine->getStateSet()->getAttribute((osg::StateAttribute::LINEWIDTH)));
	pLineWidth->setWidth(m_pViewInfo->GetLineWidth());

	if (m_pViewInfo->GetDisplayLine())
	{
		if (!m_pGeoNode->containsDrawable(m_pLine.get()))
			m_pGeoNode->addDrawable(m_pLine.get());
	}
	else
	{
		if (m_pGeoNode->containsDrawable(m_pLine.get()))
		{
			m_pGeoNode->removeDrawable(m_pLine.get());
		}
	}
}

void CXGMFaultBuilder::_UpdataPlane()
{
	if (m_vecPillarVerticeIndex.size() < 2)
		return;

	// color
	osg::ref_ptr<osg::Vec4Array> pColor = dynamic_cast<osg::Vec4Array*>(m_pPlane->getColorArray());
	QColor color = m_pViewInfo->GetPlaneColor();
	(*pColor)[0].set(color.redF(), color.greenF(), color.blueF(), m_pViewInfo->GetOpacity());
	m_pPlane->setColorArray(pColor);

	if (m_pViewInfo->GetDisplayPlane())
	{
		if (!m_pGeoNode->containsDrawable(m_pPlane.get()))
			m_pGeoNode->addDrawable(m_pPlane.get());
	}
	else
	{
		if (m_pGeoNode->containsDrawable(m_pPlane.get()))
		{
			m_pGeoNode->removeDrawable(m_pPlane.get());
		}
	}
}
