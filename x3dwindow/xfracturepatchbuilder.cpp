#include "xfracturepatchbuilder.h"

#include <osg/Point>
#include <osg/LineWidth>
#include <osg/BlendFunc>
#include <osgUtil/SmoothingVisitor>

#include "xviewinfo3dfracturepatches.h"
#include "xfracturepatch.h"
#include "xglobal.h"
#include "x3dbuilderfactory.h"
#include "x3dwindow.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXFracturePatchBuilder)
{EXFracturePatch, e3DWindow},
{EXFracturePatch,e3DBaseMap }
END_REGISTER_BUILDER_TO_FACTORY(CXFracturePatchBuilder)

osg::ref_ptr<osg::Group> CXFracturePatchBuilder::Build(QUuid objId)
{
	if (!m_pBuilderNode)
		m_pBuilderNode = new osg::Group;

	m_pFracPatches = dynamic_cast<CXFracturePatch*>(::GetObjectByID(objId));
	if (!m_pFracPatches) return nullptr;

	m_pViewInfo = dynamic_cast<CXViewInfo3DFracturePatches*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pViewInfo) return nullptr;

	_BuildNode();

	return m_pBuilderNode;
}

void CXFracturePatchBuilder::_BuildNode()
{
	m_pGeoNode = new osg::Geode;

	m_pVertices = new osg::Vec3Array;
	_BuildVertices();

	m_pPlane = new osg::Geometry;
	_BuildPlane();

	m_pLine = new osg::Geometry;
	_BuildLines();

	m_pPoint = new osg::Geometry;
	_BuildPoints();

	if (m_pViewInfo->GetDisplayPlane()) m_pGeoNode->addDrawable(m_pPlane.get());
	if (m_pViewInfo->GetDisplayLine())  m_pGeoNode->addDrawable(m_pLine.get());
	if (m_pViewInfo->GetDisplayPoint()) m_pGeoNode->addDrawable(m_pPoint.get());

	m_pGeoNode->setName("fracturepatch Geode");
	m_pGeoNode->setUserValue("objID", m_pFracPatches->GetObjectID().toString().toStdString());

	m_pBuilderNode->addChild(m_pGeoNode.get());
}

void CXFracturePatchBuilder::UpdateNode(EEventType eType)
{
	if (!m_pGeoNode) return;

	if (eType == EInfoChanged)
	{
		_UpdatePoint();
		_UpdateLine();
		_UpdataPlane();
	}
	else if (eType == EDataChanged)
	{
		m_pBuilderNode->removeChild(m_pGeoNode.get());

		_BuildNode();

	}
}

void CXFracturePatchBuilder::_UpdatePoint()
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
			m_pGeoNode->removeDrawable(m_pPoint.get());
	}
}

void CXFracturePatchBuilder::_UpdateLine()
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
			m_pGeoNode->removeDrawable(m_pLine.get());
	}
}

void CXFracturePatchBuilder::_UpdataPlane()
{
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
			m_pGeoNode->removeDrawable(m_pPlane.get());
	}
}

void CXFracturePatchBuilder::_BuildPlane()
{
	// vertices
	m_pPlane->setVertexArray(m_pVertices.get());

	// colors
	osg::ref_ptr<osg::Vec4Array> pColor = new osg::Vec4Array;
	QColor color = m_pViewInfo->GetPlaneColor();
	pColor->push_back(osg::Vec4(color.redF(), color.greenF(), color.blueF(), m_pViewInfo->GetOpacity()));
	m_pPlane->setColorArray(pColor.get(), osg::Array::BIND_OVERALL);

	m_pPlane->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	m_pPlane->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc);

	// normal
	m_pPlane->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	osgUtil::SmoothingVisitor::smooth(*m_pPlane);

	// Add quads
	//osg::ref_ptr<osg::DrawElementsUInt> pIndices = new osg::DrawElementsUInt(GL_QUADS, 0, m_pVertices->size());
	//m_pPlane->addPrimitiveSet(pIndices.get());
	m_pPlane->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, m_pVertices->size()));
}

void CXFracturePatchBuilder::_BuildLines()
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
	osgUtil::SmoothingVisitor::smooth(*m_pLine);

	// line width
	osg::ref_ptr<osg::LineWidth> pLineWidth = new osg::LineWidth;
	pLineWidth->setWidth(m_pViewInfo->GetLineWidth());
	osg::ref_ptr<osg::StateSet> state = m_pLine->getOrCreateStateSet();
	state->setAttribute(pLineWidth);

	// Add lines
	int nPatches = m_pVertices->size() / 4;
	for (int i = 0; i < nPatches; ++i)
	{
		m_pLine->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, i * 4, 4));
	}
}

void CXFracturePatchBuilder::_BuildPoints()
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
	osgUtil::SmoothingVisitor::smooth(*m_pPoint);

	// point size
	osg::ref_ptr<osg::Point> pPoint = new osg::Point;
	pPoint->setSize(m_pViewInfo->GetPointSize());
	osg::ref_ptr<osg::StateSet> state = m_pPoint->getOrCreateStateSet();
	state->setAttribute(pPoint);

	// add points
	m_pPoint->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, m_pVertices->size()));
}

void CXFracturePatchBuilder::_BuildVertices()
{
	if (!m_pFracPatches) return;
	m_pVertices->clear();

	int i, j, nPatches;
	int nProp = m_pFracPatches->GetProperties().size();
	unsigned int iNum;
	double *pData = m_pFracPatches->GetData(iNum);
	nPatches = iNum / (12 + nProp);
	if (nPatches < 1)
		return;

	for (i = 0; i < nPatches; i++)
	{
		Vec3d vecWorld;
		osg::Vec3f vecLocal;

		int iOffset = i * (12 + nProp) + nProp;
		for (j = 0; j < 4; j++)
		{
			vecWorld.set(pData[iOffset + 3 * j], pData[iOffset + 3 * j + 1], pData[iOffset + 3 * j + 2]);
			m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
			m_pVertices->push_back(vecLocal);
		}
	}
}