#include "x3ddvbuilder.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/LineWidth>

#include "x3dbuilderfactory.h"
#include "xglobal.h"
#include "x3dsurvey.h"
#include "x3dglobalcoordmap.h"
#include "xseismicdatavolume.h"
#include "xviewinfoseismicdv.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DDataVolumeBuilder)
{ EXSeismicDataVolume, e3DWindow }
END_REGISTER_BUILDER_TO_FACTORY(CX3DDataVolumeBuilder)

CX3DDataVolumeBuilder::CX3DDataVolumeBuilder()
{
}

CX3DDataVolumeBuilder::~CX3DDataVolumeBuilder()
{
}

osg::ref_ptr<osg::Group> CX3DDataVolumeBuilder::Build(QUuid objId)
{
	m_pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(objId));
	m_pViewInfo = dynamic_cast<CXViewInfoSeismicDV*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pDV || !m_pViewInfo)
		return nullptr;
	
	m_pBuilderNode = new osg::Group;

	osg::Geode* pGeode = new osg::Geode;
	pGeode->setUserValue("objID", objId.toString().toStdString());
	pGeode->addDrawable(_BuildGeometry());
	m_pBuilderNode->addChild(pGeode);

	osg::StateSet* pStateSet = m_pBuilderNode->getOrCreateStateSet();
	pStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
	pStateSet->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
	pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);

	return m_pBuilderNode.get();
}

void CX3DDataVolumeBuilder::UpdateNode(EEventType eType)
{
	if (eType == EInfoChanged)
	{
		_UpdateGeometry();
	}
}

osg::Geometry* CX3DDataVolumeBuilder::_BuildGeometry()
{
	m_pGeom = new osg::Geometry;

	// data
	double dZMin, dZMax, dZInterval;
	m_pDV->GetSamplingRange(dZMin, dZMax, dZInterval);

	const CXSeismicUTMTool& utm = m_pDV->GetUTM();
	int firstInline = utm.GetFirstInline();
	int lastInline = utm.GetLastInline();
	int firstXline = utm.GetFirstCrossline();
	int lastXline = utm.GetLastCrossline();

	osg::Vec3Array* pVertex = new osg::Vec3Array(8);
	(*pVertex)[0].set(_LineToLocal(firstInline, firstXline, dZMin));
	(*pVertex)[1].set(_LineToLocal(lastInline, firstXline, dZMin));
	(*pVertex)[2].set(_LineToLocal(lastInline, lastXline, dZMin));
	(*pVertex)[3].set(_LineToLocal(firstInline, lastXline, dZMin));
	(*pVertex)[4].set(_LineToLocal(firstInline, firstXline, dZMax));
	(*pVertex)[5].set(_LineToLocal(lastInline, firstXline, dZMax));
	(*pVertex)[6].set(_LineToLocal(lastInline, lastXline, dZMax));
	(*pVertex)[7].set(_LineToLocal(firstInline, lastXline, dZMax));
	m_pGeom->setVertexArray(pVertex);

	std::vector<uint> vecSide{ 0, 4, 1, 5, 2, 6, 3, 7 };
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, 4));
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 4, 4));
	m_pGeom->addPrimitiveSet(new osg::DrawElementsUInt(GL_LINES, vecSide.cbegin(), vecSide.cend()));

	_UpdateGeometry();

	return m_pGeom.get();
}

osg::Vec3 CX3DDataVolumeBuilder::_LineToLocal(int iInline, int iXline, double dZ)
{
	double dX, dY;

	const CXSeismicUTMTool& utm = m_pDV->GetUTM();
	utm.LineToXY(iInline, iXline, dX, dY);

	osg::Vec3 vecLocal;
	m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dY, dZ), vecLocal);

	return vecLocal;
}

void CX3DDataVolumeBuilder::_UpdateGeometry               ()
{
	const QColor& color = m_pViewInfo->GetBMFrameColor();
	int width = m_pViewInfo->GetBMFrameWidth();

	osg::Vec4Array* pColors = new osg::Vec4Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	m_pGeom->setColorArray(pColors, osg::Array::BIND_OVERALL);

	osg::StateSet *pStateSet = m_pGeom->getOrCreateStateSet();
	pStateSet->setAttributeAndModes(new osg::LineWidth(width), osg::StateAttribute::ON);
}