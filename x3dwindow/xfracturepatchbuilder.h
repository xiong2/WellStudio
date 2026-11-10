#pragma once

#include "x3dbuilder.h"
#include <vector>

class CXFracturePatch;
class CXViewInfo3DFracturePatches;

class CXFracturePatchBuilder : public CX3DBuilderAbstract
{
public:
	CXFracturePatchBuilder() {}
	~CXFracturePatchBuilder() {}

	virtual osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	virtual void UpdateNode(EEventType eType) override;

private:
	void _BuildVertices();
	void _BuildPoints();
	void _BuildLines();
	void _BuildPlane();

	void _UpdatePoint();
	void _UpdateLine();
	void _UpdataPlane();

	void _BuildNode();

private:
	osg::ref_ptr<osg::Geode> m_pGeoNode;

	osg::ref_ptr<osg::Geometry> m_pPlane;
	osg::ref_ptr<osg::Geometry> m_pLine;
	osg::ref_ptr<osg::Geometry> m_pPoint;

	osg::ref_ptr<osg::Vec3Array> m_pVertices;

private:
	CXFracturePatch* m_pFracPatches = nullptr;
	CXViewInfo3DFracturePatches* m_pViewInfo = nullptr;
};