#include "xbmpointsetbuilder.h"

#include <osg/Geometry>
#include <osg/Point>

#include "xglobal.h"
#include "x3dglobalcoordmap.h"
#include "x3dbuilderfactory.h"
#include "xviewinfo3dpoints.h"
#include "x3dutility.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXBMPointSetBuilder)
{ EX3DPoints, e3DBaseMap }
END_REGISTER_BUILDER_TO_FACTORY(CXBMPointSetBuilder)

CXBMPointSetBuilder::CXBMPointSetBuilder()
	: CX3DBuilderAbstract()
{

}

CXBMPointSetBuilder::~CXBMPointSetBuilder()
{

}

osg::ref_ptr<osg::Group> CXBMPointSetBuilder::Build(QUuid objId)
{
	auto pObj = dynamic_cast<CXObject*>(::GetObjectByID(objId));
	uint nNum;
	double *pData = pObj->GetData(nNum);

	m_pViewInfo = dynamic_cast<CXViewInfo3DPoints*>(m_pCurWin->GetObjectViewInfo(objId));
	Q_ASSERT(m_pViewInfo);

	m_pGeometry = new osg::Geometry;

	osg::Vec3Array* pVertex = new osg::Vec3Array(nNum / 3);
	for (uint i = 0; i < nNum; i += 3)
	{
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(pData[i], pData[i + 1], pData[i + 2]), (*pVertex)[i / 3]);
	}
	m_pGeometry->setVertexArray(pVertex);

	const QColor& color = m_pViewInfo->GetIsObjectColor() ? m_pViewInfo->GetColor() : m_pViewInfo->GetPointColor();
	NX3DUtility::SetSingleColor(m_pGeometry, color);

	m_pGeometry->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, pVertex->size()));
	m_pGeometry->getOrCreateStateSet()->setAttribute(new osg::Point(m_pViewInfo->GetPointSize()), osg::StateAttribute::ON);

	osg::Geode* pGeode = new osg::Geode;
	pGeode->addDrawable(m_pGeometry);

	m_pBuilderNode = new osg::Group;
	m_pBuilderNode->addChild(pGeode);

	return m_pBuilderNode.get();
}

void CXBMPointSetBuilder::UpdateNode(EEventType eType)
{
	if (eType != EInfoChanged)
		return;

	if (!m_pGeometry)
		return;

	const QColor& color = m_pViewInfo->GetIsObjectColor() ? m_pViewInfo->GetColor() : m_pViewInfo->GetPointColor();
	NX3DUtility::SetSingleColor(m_pGeometry, color);
	m_pGeometry->getOrCreateStateSet()->setAttribute(new osg::Point(m_pViewInfo->GetPointSize()), osg::StateAttribute::ON);
}
