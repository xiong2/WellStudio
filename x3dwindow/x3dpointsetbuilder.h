#ifndef X3DPOINTSETBUILDER_H_H
#define X3DPOINTSETBUILDER_H_H
#include "x3dbuilder.h"

class CXViewInfo3DPoints;
namespace osg {class Geometry;}

class CX3DPointsetBuilder : public CX3DBuilderAbstract
{
public:
	CX3DPointsetBuilder();
	~CX3DPointsetBuilder();

	virtual osg::BoundingBox GetBoundBox() override;
	virtual osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	void UpdateNode(EEventType eType) override;

private:
    //osg::ref_ptr<osg::Group> _RenderingByLOD(osg::ref_ptr<osg::Vec3Array> pVertices, osg::Vec4 color);
    osg::ref_ptr<osg::Group> _RenderingByPoints(osg::ref_ptr<osg::Vec3Array> pVertices);

	CXViewInfo3DPoints* m_pViewInfo = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeometry;
};
#endif
