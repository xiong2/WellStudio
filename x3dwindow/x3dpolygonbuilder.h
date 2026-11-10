#ifndef X3DPOLYGONBUILDER_H_H
#define X3DPOLYGONBUILDER_H_H
#include "x3dbuilder.h"

class CX3DPolygonBuilder:public CX3DBuilderAbstract
{
public:
	CX3DPolygonBuilder();
	~CX3DPolygonBuilder();
	osg::ref_ptr<osg::Group> Build(QUuid objId);
	
private:


};
#endif