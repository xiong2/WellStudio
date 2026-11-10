#pragma once

/*!
 * @brief	draw 2d seismic section on 3-D window
 * @author	pezy
 * @date	2017-03-09
 * @see
 */

#include "x3dbuilder.h"

class CX2DSeismicLine;
class CXViewInfo2DSeismicLine;
class CXSeismicDataLine;

class CX3DSeismicLineBuilder : public CX3DBuilderAbstract
{
public:
	CX3DSeismicLineBuilder() : CX3DBuilderAbstract() {}
	~CX3DSeismicLineBuilder() {}

	osg::ref_ptr<osg::Group> Build(QUuid objID) override;
	void UpdateNode(EEventType eType) override;

private:
	void _CalcVertexAndTexCoord();
	osg::Geometry* _BuildSectionGeom();
	osg::StateSet* _BuildTextureState();

private:
	CX2DSeismicLine* m_pSeismicLine = nullptr;
	CXViewInfo2DSeismicLine* m_pViewInfo = nullptr;
	CXSeismicDataLine* m_pSection = nullptr;

	unsigned int m_nTrace = 0;
	int m_nSampling = 0;

	osg::ref_ptr<osg::Vec3Array> m_pVertices;
	osg::ref_ptr<osg::Vec2Array> m_pTexCoord;
	osg::ref_ptr<osg::Geode> m_pSectionGeode;
	osg::ref_ptr<osg::Geometry> m_pGeom;
};
