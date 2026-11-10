#include "x3dpointsetbuilder.h"

#include <osg/Group>
#include <osg/Vec3d>
#include <osg/Node>
#include <osg/Geode>
#include <osg/LOD>
#include <osg/ComputeBoundsVisitor>
#include <osgUtil/SmoothingVisitor>
#include <osg/Point>

#include "x3dbuilder.h"
#include "xglobal.h"
#include "x3dbuilderfactory.h"
#include "xobject.h"
#include "x3dglobalcoordmap.h"
#include "x3dwindow.h"
#include "xbiggeometry.h"
#include "xviewinfo3dpoints.h"
#include "x3dutility.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DPointsetBuilder)
{EX3DPoints,e3DWindow}
END_REGISTER_BUILDER_TO_FACTORY(CX3DPointsetBuilder)

using namespace osg;

CX3DPointsetBuilder::CX3DPointsetBuilder():CX3DBuilderAbstract()
{
	m_bScalable = false;
}

CX3DPointsetBuilder::~CX3DPointsetBuilder()
{

}

osg::BoundingBox CX3DPointsetBuilder::GetBoundBox()
{
	return m_BoundBox;
}

ref_ptr<Group> CX3DPointsetBuilder::Build(QUuid objId)
{
    ///> Brief Get ZScale's value
    auto fZScale = static_cast<float>(dynamic_cast<CX3DWindow*>(m_pCurWin)->GetZScale());

    auto pObject = dynamic_cast<CXObject *>(GetObjectByID(objId));
    unsigned int iNumber;
    auto pData = pObject->GetData(iNumber);

	m_pViewInfo = dynamic_cast<CXViewInfo3DPoints*>(m_pCurWin->GetObjectViewInfo(objId));
	Q_ASSERT(m_pViewInfo);

    ref_ptr<Vec3Array> pVertex = new Vec3Array;
    for (auto i = 0; i < iNumber / 3; i++)
    {
        Vec3d vecWorld;
        Vec3f vecLocal;
        vecWorld.set(pData[i * 3], pData[i * 3 + 1], pData[i * 3 + 2]);
        m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
        vecLocal.z() *= fZScale;
        pVertex->push_back(vecLocal);
    }

    return _RenderingByPoints(pVertex);
}

void CX3DPointsetBuilder::UpdateNode(EEventType eType)
{
	if (eType != EInfoChanged)
		return;

	if (!m_pGeometry)
		return;

	auto objColor = m_pViewInfo->GetIsObjectColor() ? m_pViewInfo->GetColor() : m_pViewInfo->GetPointColor();
	NX3DUtility::SetSingleColor(m_pGeometry, objColor);
	m_pGeometry->getOrCreateStateSet()->setAttribute(new osg::Point(m_pViewInfo->GetPointSize()), osg::StateAttribute::ON);
}

//ref_ptr<Group> CX3DPointsetBuilder::_RenderingByLOD(ref_ptr<Vec3Array> pVertices, Vec4 color)
//{
//    CXBigGeometry* spheres1 = new CXBigGeometry(CXBigGeometry::Sphere, *pVertices.get(), 10);
//    CXBigGeometry* spheres2 = new CXBigGeometry(CXBigGeometry::Sphere, *pVertices.get(), 10, 1);
//    CXBigGeometry* spheres3 = new CXBigGeometry(CXBigGeometry::SpherePoints, *pVertices.get(), 10, 1);
//
//    spheres1->SetColor(color);
//    spheres2->SetColor(color);
//    spheres3->SetColor(color);
//
//    ref_ptr<LOD> pLod = new LOD;
//    pLod->setRangeMode(LOD::DISTANCE_FROM_EYE_POINT);
//
//    ref_ptr<Geode> pGeode1 = new Geode;
//    ref_ptr<Geode> pGeode2 = new Geode;
//    ref_ptr<Geode> pGeode3 = new Geode;
//
//    pGeode1->addDrawable(spheres1->Geometry());
//    pGeode2->addDrawable(spheres2->Geometry());
//    pGeode3->addDrawable(spheres3->Geometry());
//
//	spheres1->Geometry()->getOrCreateStateSet()->setAttribute(new osg::Point(m_pViewInfo->GetPointSize()), osg::StateAttribute::ON);
//	spheres2->Geometry()->getOrCreateStateSet()->setAttribute(new osg::Point(m_pViewInfo->GetPointSize()), osg::StateAttribute::ON);
//	spheres3->Geometry()->getOrCreateStateSet()->setAttribute(new osg::Point(m_pViewInfo->GetPointSize()), osg::StateAttribute::ON);
//
//    pLod->addChild(pGeode1.get(), 0, 1000);
//    pLod->addChild(pGeode2.get(), 1000, 3000);
//    pLod->addChild(pGeode3.get(), 3000, FLT_MAX);
//
//    ComputeBoundsVisitor cbVisitor;
//    pLod->accept(cbVisitor);
//    m_BoundBox = cbVisitor.getBoundingBox();
//
//    return pLod;
//}

ref_ptr<Group> CX3DPointsetBuilder::_RenderingByPoints(ref_ptr<Vec3Array> pVertices)
{
    if (!m_pBuilderNode) m_pBuilderNode = new Group;

    m_pGeometry = new Geometry;
    m_pGeometry->setVertexArray(pVertices.get());
    
	auto objColor = m_pViewInfo->GetIsObjectColor() ? m_pViewInfo->GetColor() : m_pViewInfo->GetPointColor();
	NX3DUtility::SetSingleColor(m_pGeometry, objColor);

    m_pGeometry->setNormalBinding(Geometry::BIND_PER_VERTEX);
    osgUtil::SmoothingVisitor::smooth(*m_pGeometry);

    m_pGeometry->addPrimitiveSet(new DrawArrays(GL_POINTS, 0, pVertices->size()));
	m_pGeometry->getOrCreateStateSet()->setAttribute(new osg::Point(m_pViewInfo->GetPointSize()), osg::StateAttribute::ON);

    ref_ptr<Geode> pGeode = new Geode;
    pGeode->addDrawable(m_pGeometry);
    m_pBuilderNode->addChild(pGeode);

    return m_pBuilderNode;
}