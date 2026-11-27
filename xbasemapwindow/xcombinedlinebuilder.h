#pragma once
#include "x3dbuilder.h"
#include <osg/Group>

class CXCombinedLine;
class CXViewInfoCombinedLine;

class CXCombinedLineBuilder : public CX3DBuilderAbstract
{
public:
	CXCombinedLineBuilder() : CX3DBuilderAbstract() {}
	~CXCombinedLineBuilder() {}

	virtual osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	virtual void UpdateNode(EEventType eType) override;

private:
	void _BuildVertices() const;
	void _BuildPolyLine() const;
	void _UpdatePolyLine() const;

	osg::ref_ptr<osg::Geode> m_pGeoNode;
	osg::ref_ptr<osg::Geometry> m_pLineGeom;
	osg::ref_ptr<osg::Vec3Array> m_pVertices;

	CXCombinedLine* m_pSeismicLine = nullptr;
	CXViewInfoCombinedLine* m_pViewInfo = nullptr;
};
