#include "xcombinedlinebuilder.h"
#include <osg/Geometry>
#include <osg/LineWidth>
#include "x3dbuilderfactory.h"
#include "xcombinedline.h"
#include "xglobal.h"
#include "xviewinfocombinedline.h"
#include "x3dglobalcoordmap.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXCombinedLineBuilder)
{
	EXCombinedLine, e3DBaseMap
}
END_REGISTER_BUILDER_TO_FACTORY(CXCombinedLineBuilder)

osg::ref_ptr<osg::Group> CXCombinedLineBuilder::Build(QUuid objId)
{
	if (!m_pBuilderNode) m_pBuilderNode = new osg::Group;

	m_pSeismicLine = dynamic_cast<CXCombinedLine*>(::GetObjectByID(objId));
	if (!m_pSeismicLine) return nullptr;

	m_pViewInfo = dynamic_cast<CXViewInfoCombinedLine*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pViewInfo) return nullptr;

	m_pVertices = new osg::Vec3Array;
	_BuildVertices();

	m_pLineGeom = new osg::Geometry;
	_BuildPolyLine();

	m_pGeoNode = new osg::Geode;
	m_pGeoNode->addDrawable(m_pLineGeom.get());
	m_pGeoNode->setName("combined line geode");

	m_pBuilderNode->addChild(m_pGeoNode.get());

	return m_pBuilderNode;
}

void CXCombinedLineBuilder::UpdateNode(EEventType eType)
{
	if (!m_pGeoNode) return;

	if (eType == EInfoChanged)
	{
		_UpdatePolyLine();
	}
}

void CXCombinedLineBuilder::_BuildVertices() const
{
	if (!m_pSeismicLine) return;

	m_pVertices->clear();

	QPolygonF polyline = m_pSeismicLine->GetTurnPoints();

	osg::Vec3f vecLocal;
	for (QPointF point: polyline)
	{
		osg::Vec3d vecWorld{ point.x(), point.y(), 0 };
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		m_pVertices->push_back(vecLocal);
	}
}

void CXCombinedLineBuilder::_BuildPolyLine() const
{
	m_pLineGeom->setVertexArray(m_pVertices.get());

	osg::ref_ptr<osg::Vec3Array> pColorArray = new osg::Vec3Array;
	const auto& lineColor = m_pViewInfo->GetLineColor();
	pColorArray->push_back(osg::Vec3f(lineColor.redF(), lineColor.greenF(), lineColor.blueF()));
	m_pLineGeom->setColorArray(pColorArray, osg::Array::BIND_OVERALL);

	osg::ref_ptr<osg::LineWidth> pLineWidth = new osg::LineWidth;
	pLineWidth->setWidth(m_pViewInfo->GetLineWidth());
	m_pLineGeom->getOrCreateStateSet()->setAttribute(pLineWidth);

	m_pLineGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, m_pVertices->size()));
}

void CXCombinedLineBuilder::_UpdatePolyLine() const
{
	osg::ref_ptr<osg::Vec3Array> pColorArray = dynamic_cast<osg::Vec3Array*>(m_pLineGeom->getColorArray());
	const auto& lineColor = m_pViewInfo->GetLineColor();
	(*pColorArray)[0].set(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
	m_pLineGeom->setColorArray(pColorArray.get());

	osg::ref_ptr<osg::LineWidth> pLineWidth = dynamic_cast<osg::LineWidth*>(m_pLineGeom->getStateSet()->getAttribute((osg::StateAttribute::LINEWIDTH)));
	pLineWidth->setWidth(m_pViewInfo->GetLineWidth());

	if (!m_pGeoNode->containsDrawable(m_pLineGeom.get()))
		m_pGeoNode->addDrawable(m_pLineGeom.get());
}