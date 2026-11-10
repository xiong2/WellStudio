#include "xbmrandomsectionbuilder.h"

#include <osg/LineWidth>
#include <osg/Point>
#include <QDebug>

#include "xseismicrandomsection.h"
#include "xglobal.h"
#include "xviewinforandomsection.h"
#include "xbmpickcallback.h"
#include "x3dglobalcoordmap.h"
#include "xbmpickcallback.h"
#include "x3dbuilderfactory.h"
#include "xbasemapwindow.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXBMRandomSectionBuilder)
{EXRandomSection,e3DBaseMap}
END_REGISTER_BUILDER_TO_FACTORY(CXBMRandomSectionBuilder)

CXBMRandomSectionBuilder::CXBMRandomSectionBuilder()
	: CX3DPickableBuilderAbstract()
{

}

CXBMRandomSectionBuilder::~CXBMRandomSectionBuilder()
{

}

osg::ref_ptr<osg::Group> CXBMRandomSectionBuilder::Build(QUuid objId)
{
	// data
	m_pRandomSection = dynamic_cast<CXSeismicRandomSection*>(::GetObjectByID(objId));
	m_pViewInfo = dynamic_cast<CXViewInfoRandomSection*>(m_pCurWin->GetObjectViewInfo(objId));

	if (!m_pRandomSection || !m_pViewInfo)
		return nullptr;

	m_pGeode = new osg::Geode;
	m_pGeode->setUserValue("objID", objId.toString().toStdString());
	m_pGeode->setName("RandomSection:" + m_pRandomSection->GetObjectName().toStdString());
	m_pGeode->addDrawable(_BuildRandomSectionLine());
	m_pGeode->setEventCallback(new CXBMPickCallback(this));

	return m_pGeode;
}

void CXBMRandomSectionBuilder::UpdateNode(EEventType eType)
{
	if (EDataChanged == eType)
	{
		m_pGeom->setVertexArray(_BuildRandomSectionVertex());
	}
	else if (EInfoChanged == eType)
	{
		_UpdateViewInfo(true);
	}
}

bool CXBMRandomSectionBuilder::SetActive(bool bActive)
{
	auto pBMWin = dynamic_cast<CXBaseMapWindow*>(m_pCurWin);
	Q_ASSERT(pBMWin);

	if (!pBMWin->IsRandomSectionMode())
		return false;

	_UpdateViewInfo(bActive);

	// update delete action status.
	pBMWin->EnableRandomSectionDeleteAction(bActive);

	return true;
}

osg::ref_ptr<osg::Vec4Array> CXBMRandomSectionBuilder::GetPickedColor() const
{
	const QColor& colorPicked = m_pViewInfo->GetBMPickedLineColor();

	osg::ref_ptr<osg::Vec4Array> pColors = new osg::Vec4Array(1);
	(*pColors)[0].set(colorPicked.redF(), colorPicked.greenF(), colorPicked.blueF(), colorPicked.alphaF());

	return pColors;
}

osg::Geometry* CXBMRandomSectionBuilder::_BuildRandomSectionLine()
{
	m_pGeom = new osg::Geometry;

	m_pGeom->setVertexArray(_BuildRandomSectionVertex());
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, m_pVertex->size()));
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, 0, m_pVertex->size()));

	_UpdateViewInfo(false);

	return m_pGeom.get();
}

osg::Vec3Array* CXBMRandomSectionBuilder::_BuildRandomSectionVertex()
{
	std::vector<double> vecX, vecY;

	m_pRandomSection->GetXYofTuringPoint(vecX, vecY);

	m_pVertex = new osg::Vec3Array(vecX.size());
	for (decltype(vecX.size()) i = 0; i != vecX.size(); ++i)
	{
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecX.at(i), vecY.at(i), -1), (*m_pVertex)[i]);
	}

	return m_pVertex.get();
}

void CXBMRandomSectionBuilder::_UpdateViewInfo(bool bPicked)
{
	const QColor& color = bPicked ? m_pViewInfo->GetBMPickedLineColor() : m_pViewInfo->GetBMLineColor();
	int width = bPicked ? m_pViewInfo->GetBMPickedLineWidth() : m_pViewInfo->GetBMLineWidth();

	osg::Vec3Array* pColor = new osg::Vec3Array(1);
	(*pColor)[0].set(color.redF(), color.greenF(), color.blueF());
	m_pGeom->setColorArray(pColor, osg::Array::BIND_OVERALL);

	osg::StateSet* pStateSet = m_pGeom->getOrCreateStateSet();
	pStateSet->setAttributeAndModes(new osg::LineWidth(width), osg::StateAttribute::ON);
	
	if (bPicked)
	{
		pStateSet->setAttribute(new osg::Point(m_pViewInfo->GetBMPointSize()));
	}
	else
	{
		pStateSet->removeAttribute(osg::StateAttribute::POINT);
	}
}