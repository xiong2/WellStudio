#include "x3dpolygonbuilder.h"

#include "x3dbuilderfactory.h"
#include "xglobal.h"
#include "x2dpolygon.h"
#include "x3dglobalcoordmap.h"
#include <osg/Geode>
#include <osg/Geometry>

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DPolygonBuilder)
{EX2DPolygon,e3DWindow},
{EXFaultPolygon,e3DWindow}
END_REGISTER_BUILDER_TO_FACTORY(CX3DPolygonBuilder)

CX3DPolygonBuilder::CX3DPolygonBuilder()
{

}
CX3DPolygonBuilder::~CX3DPolygonBuilder()
{



}


osg::ref_ptr<osg::Group> CX3DPolygonBuilder::Build(QUuid objId)
{
	m_pBuilderNode=new osg::Group();
	CX2DPolygon *pPolygonObj = dynamic_cast<CX2DPolygon*>(::GetObjectByID(objId));
	QColor objColor=pPolygonObj->GetColor();
	unsigned int dataNum=0;
	double *pData=pPolygonObj->GetData(dataNum);
	osg::Vec3Array *pVertexArray=new osg::Vec3Array;
	osg::Vec4Array *pColorArray=new osg::Vec4Array;
	for(int i=0;i<dataNum/2;i++)
	{
		osg::Vec3d vecWorld((pData)[i*2],(pData)[i*2+1],0);
		osg::Vec3 vecLocal;
		m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
		pVertexArray->push_back(vecLocal);
		pColorArray->push_back(osg::Vec4(objColor.redF(),objColor.greenF(),objColor.blueF(),objColor.alphaF()));
	}
	osg::Geode *pGeode=new osg::Geode;
	osg::Geometry *pGeometry=new osg::Geometry;
	pGeometry->setVertexArray(pVertexArray);
	pGeometry->setColorArray(pColorArray,osg::Array::BIND_PER_VERTEX);
	pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP,0,pVertexArray->size()));

	pGeode->addDrawable(pGeometry);
	m_pBuilderNode->addChild(pGeode);
	return m_pBuilderNode;

}