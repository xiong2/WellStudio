#include "xbmpolygonbuilder.h"

#include <osg/LineWidth>
#include <osg/BlendFunc>
#include <osg/Point>
#include <osg/Depth>

#include "x3dbuilderfactory.h"
#include "x2dpolygon.h"
#include "xglobal.h"
#include "xviewinfo2dpolygon.h"
#include "xbmpickcallback.h"
#include "x3dglobalcoordmap.h"
#include "xbasemapwindow.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXBMPolygonBuilder)
{EX2DPolygon, e3DBaseMap},
{EXFaultPolygon, e3DBaseMap}
END_REGISTER_BUILDER_TO_FACTORY(CXBMPolygonBuilder)

CXBMPolygonBuilder::CXBMPolygonBuilder()
	: CX3DPickableBuilderAbstract()
{

}

CXBMPolygonBuilder::~CXBMPolygonBuilder()
{

}

osg::ref_ptr<osg::Group> CXBMPolygonBuilder::Build(QUuid objId)
{
	// data
	m_pPolygon = dynamic_cast<CX2DPolygon*>(::GetObjectByID(objId));
	m_pViewInfo = dynamic_cast<CXViewInfo2DPolygon*>(m_pCurWin->GetObjectViewInfo(objId));

	if (!m_pPolygon || !m_pViewInfo)
		return nullptr;

	m_pGeode = new osg::Geode;
	m_pGeode->setUserValue("objID", objId.toString().toStdString());
	m_pGeode->addDrawable(_BuildPolygon());
	m_pGeode->setEventCallback(new CXBMPickCallback(this));

	// transparent setting.
	osg::StateSet* pStateSet = m_pGeode->getOrCreateStateSet();
	pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	pStateSet->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	pStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	return m_pGeode;
}

void CXBMPolygonBuilder::UpdateNode(EEventType eType)
{
	if (EDataChanged == eType)
	{
		m_pGeom->setVertexArray(_BuildPolygonVertex());
	}
	else if (EInfoChanged == eType)
	{
		_UpdateViewInfo(false);
	}
}

bool CXBMPolygonBuilder::SetActive(bool bActive)
{
	auto pBMWin = dynamic_cast<CXBaseMapWindow*>(m_pCurWin);
	Q_ASSERT(pBMWin);

	if (!pBMWin->IsPolygonMode())
		return false;

	_UpdateViewInfo(bActive);

	// update delete action status.
	pBMWin->EnablePolygonDeleteAction(bActive);

	return true;
}

osg::Geometry * CXBMPolygonBuilder::_BuildPolygon()
{
	m_pGeom = new osg::Geometry;

	m_pGeom->setVertexArray(_BuildPolygonVertex());
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, m_pVertex->size()));
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, m_pVertex->size()));

	_UpdateViewInfo(false);

	return m_pGeom.get();
}

osg::Vec3Array * CXBMPolygonBuilder::_BuildPolygonVertex()
{
	uint nNum = 0;
	double* pData = m_pPolygon->GetData(nNum);

	Q_ASSERT(!(nNum & 0x1));
	uint nPoint = nNum / 2;

	m_pVertex = new osg::Vec3Array(nPoint);
	for (uint i = 0; i < nPoint; ++i)
	{
		m_pCoordMap->MapWorldToLocal(osg::Vec3(pData[i * 2], pData[i * 2 + 1], 0), (*m_pVertex)[i]);
		(*m_pVertex)[i].z() = 1;
	}

	return m_pVertex.get();
}

void CXBMPolygonBuilder::_UpdateViewInfo(bool bPicked)
{
	// view info
	const QColor& colorLine = bPicked ? m_pViewInfo->GetBMPickedColor() : m_pViewInfo->GetBMLineColor();
	const QColor& colorPivot = bPicked ? m_pViewInfo->GetBMPickedColor() : m_pViewInfo->GetBMPivotColor();
	const QColor& colorFill = m_pViewInfo->GetBMFillColor();
	int lineWidth = bPicked ? m_pViewInfo->GetBMPickedWidth() : m_pViewInfo->GetBMLineWidth();
	
	osg::Vec4Array* pColors = new osg::Vec4Array(3);
	(*pColors)[0].set(colorPivot.redF(), colorPivot.greenF(), colorPivot.blueF(), colorPivot.alphaF());
	(*pColors)[1].set(colorLine.redF(), colorLine.greenF(), colorLine.blueF(), colorLine.alphaF());
	(*pColors)[2].set(colorFill.redF(), colorFill.greenF(), colorFill.blueF(), colorFill.alphaF());
	m_pGeom->setColorArray(pColors, osg::Array::BIND_PER_PRIMITIVE_SET);

	osg::StateSet *pStateSet = m_pGeom->getOrCreateStateSet();
	pStateSet->setAttributeAndModes(new osg::LineWidth(lineWidth), osg::StateAttribute::ON);

	if (bPicked)
	{
		pStateSet->setAttribute(new osg::Point(m_pViewInfo->GetBMPivotSize()));
	}
	else
	{
		pStateSet->removeAttribute(osg::StateAttribute::POINT);
	}

	if (m_pViewInfo->GetBMIsFill())
	{
		m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_POLYGON, 0, m_pVertex->size()));
	}
	else
	{
		m_pGeom->removePrimitiveSet(2);
	}
}
