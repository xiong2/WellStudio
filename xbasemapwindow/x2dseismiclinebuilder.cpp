#include "x2dseismiclinebuilder.h"

#include <osg/Geometry>

#include "x3dbuilderfactory.h"
#include "x2dseismicline.h"
#include "xglobal.h"
#include "xviewinfo2dseismicline.h"
#include "x3dglobalcoordmap.h"
#include <osg/LineWidth>
#include <osgText/Text>
#include <osgText/Font>

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX2DSeismicLineBuilder)
{ EX2DSeismicLine, e3DBaseMap }
END_REGISTER_BUILDER_TO_FACTORY(CX2DSeismicLineBuilder)

osg::ref_ptr<osg::Group> CX2DSeismicLineBuilder::Build(QUuid objId)
{
	if (!m_pBuilderNode) m_pBuilderNode = new osg::Group;

	m_pSeismicLine = dynamic_cast<CX2DSeismicLine*>(::GetObjectByID(objId));
	if (!m_pSeismicLine) return nullptr;

	m_pViewInfo = dynamic_cast<CXViewInfo2DSeismicLine*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pViewInfo) return nullptr;

	m_pVertices = new osg::Vec3Array;
	_BuildVertices();

	m_pLineGeom = new osg::Geometry;
	_BuildPolyLine();

	m_pMarkSwich = new osg::Switch;
	osg::ref_ptr<osgText::Text> pMarkTextTop = new osgText::Text;
	osg::ref_ptr<osgText::Text> pMarkTextBottom = new osgText::Text;
	m_pMarkSwich->addChild(pMarkTextTop.get());
	m_pMarkSwich->addChild(pMarkTextBottom.get());
	_BuildOrUpdateNameMark();

	m_pGeoNode = new osg::Geode;
	m_pGeoNode->addDrawable(m_pLineGeom.get());
	m_pGeoNode->setName("2D seismic line geode");

	m_pBuilderNode->addChild(m_pGeoNode.get());
	m_pBuilderNode->addChild(m_pMarkSwich.get());

	return m_pBuilderNode;
}

void CX2DSeismicLineBuilder::UpdateNode(EEventType eType)
{
	if (!m_pGeoNode) return;

	if (eType == EInfoChanged)
	{
		_UpdatePolyLine();
		_BuildOrUpdateNameMark();
	}
}

void CX2DSeismicLineBuilder::_BuildVertices() const
{
	if (!m_pSeismicLine) return;

	m_pVertices->clear();

	unsigned nTrace = m_pSeismicLine->GetTraceNumber();
	double *pX, *pY;
	m_pSeismicLine->GetCoordData(pX, pY);
	auto dOffset = m_pSeismicLine->GetOffset();

	osg::Vec3f vecLocal;
	for (unsigned i = 0; i != nTrace; ++i)
	{
		osg::Vec3d vecWorld{ pX[i] + dOffset.first, pY[i] + dOffset.second, 0 };
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		m_pVertices->push_back(vecLocal);
	}
}

void CX2DSeismicLineBuilder::_BuildPolyLine() const
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

void CX2DSeismicLineBuilder::_BuildOrUpdateNameMark() const
{
	osg::ref_ptr<osgText::Font> pFont = osgText::readFontFile(m_pViewInfo->GetNameFont().toStdString() + ".ttf");
	if (!pFont) pFont = osgText::readFontFile("arial.ttf");
	QColor nameColor = m_pViewInfo->GetNameColor();

	for (auto i = 0; i != m_pMarkSwich->getNumChildren(); ++i)
	{
		osgText::Text* pText = dynamic_cast<osgText::Text*>(m_pMarkSwich->getChild(i));
		if (!pText) continue;

		pText->setFont(pFont.get());
		pText->setText(osgText::String(m_pSeismicLine->GetObjectName().toStdString()));
		pText->setCharacterSize(m_pViewInfo->GetNameSize() * 50);
		pText->setColor(osg::Vec4(nameColor.redF(), nameColor.greenF(), nameColor.blueF(), nameColor.alphaF()));
		pText->setAlignment(0 == i ? osgText::Text::LEFT_CENTER : osgText::Text::RIGHT_CENTER);
		pText->setPosition(0 == i ? m_pVertices->front() : m_pVertices->back());
	}

	m_pMarkSwich->setValue(0, m_pViewInfo->GetDisplayNameOnTop());
	m_pMarkSwich->setValue(1, m_pViewInfo->GetDisplayNameOnBottom());
}

void CX2DSeismicLineBuilder::_UpdatePolyLine() const
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