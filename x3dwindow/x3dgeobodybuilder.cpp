#include "x3dgeobodybuilder.h"

#include <array>
#include <osg/Geometry>
#include <osgUtil/SmoothingVisitor>

#include "xgeobody.h"
#include "x3dbuilderfactory.h"
#include "x3dwindow.h"
#include "xglobal.h"
#include "xviewinfoobject.h"
#include "x3dglobalcoordmap.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DGeobodyBuilder)
{ EXGeobody, e3DWindow }
END_REGISTER_BUILDER_TO_FACTORY(CX3DGeobodyBuilder)

std::array<uint, 14> m_triangleStrips = { 3, 2, 7, 6, 5, 2, 1, 3, 0, 7, 4, 5, 0, 1 };

CX3DGeobodyBuilder::CX3DGeobodyBuilder()
	: CX3DBuilderAbstract()
{
}

CX3DGeobodyBuilder::~CX3DGeobodyBuilder()
{

}

osg::ref_ptr<osg::Group> CX3DGeobodyBuilder::Build(QUuid objId)
{
	if (!m_pBuilderNode)
	{
		m_pBuilderNode = new osg::Group;
	}

	m_pGeobody = dynamic_cast<CXGeobody*>(::GetObjectByID(objId));
	if (!m_pGeobody)
	{
		return nullptr;
	}

	m_pCellGeom = new osg::Geometry;
	m_pCellGeom->setName("Geobody cell geometry");
	m_pCellGeom->setUseVertexBufferObjects(true);
	m_pCellGeom->getOrCreateStateSet()->setMode(GL_PRIMITIVE_RESTART, osg::StateAttribute::ON);

	_CalcUTMDirection();
	_BuildVertices();
	_BuildIndices();
	_BuildColor();
	_BuildNormal();

	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
	pGeode->setName(m_pGeobody->GetObjectName().toLatin1().data());
	pGeode->addDrawable(m_pCellGeom.get());
	m_pBuilderNode->addChild(pGeode.get());

	return m_pBuilderNode;
}

void CX3DGeobodyBuilder::_BuildVertices()
{
	m_pVertices = new osg::Vec3Array;
	m_pVertices->push_back(osg::Vec3(0.0, 0.0, 0.0)); // for restart mark.
	
	unsigned int nCellNumber;
	qint64* pCell = m_pGeobody->GetAllCells(nCellNumber);
	
	for (qint64 i = 0; i != nCellNumber; ++i)
	{
		double dX, dY, dZ;
		m_pGeobody->GetCellCentralPosition(pCell[i], dX, dY, dZ);
		_PushCellVerticesToGeometryByCentral(dX, dY, dZ);
	}

	m_pCellGeom->setVertexArray(m_pVertices.get());
}

void CX3DGeobodyBuilder::_BuildIndices()
{
	osg::ref_ptr<osg::DrawElementsUInt> pCellPrimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0);

	for (size_t i = 1; i < m_pVertices->size(); i += 8)
	{
		for (size_t j = 0; j != 14; ++j)
		{
			pCellPrimitive->push_back(m_triangleStrips[j] + i);
		}
		pCellPrimitive->push_back(0); // restart
	}
	m_pCellGeom->addPrimitiveSet(pCellPrimitive.get());
}

void CX3DGeobodyBuilder::_BuildColor()
{
	if (!m_pGeobody)
	{
		return;
	}

	QColor color = m_pGeobody->GetColor();
	osg::ref_ptr<osg::Vec4Array> pColor = new osg::Vec4Array(1);
	(*pColor)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	m_pCellGeom->setColorArray(pColor.get());
	m_pCellGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
}

void CX3DGeobodyBuilder::_BuildNormal()
{
	osg::ref_ptr<osg::Vec3Array> pNormalize = new osg::Vec3Array;

	for (decltype(m_pVertices->size()) i = 0; i < m_pVertices->size() - 1; i += 8)
	{
		osg::Vec3 normal_blw = ((*m_pVertices)[i + 7] - (*m_pVertices)[i + 4]) ^ ((*m_pVertices)[i + 5] - (*m_pVertices)[i + 4]);
		osg::Vec3 normal_fnt = ((*m_pVertices)[i + 1] - (*m_pVertices)[i + 5]) ^ ((*m_pVertices)[i + 4] - (*m_pVertices)[i + 5]);
		osg::Vec3 normal_rgt = ((*m_pVertices)[i + 1] - (*m_pVertices)[i + 2]) ^ ((*m_pVertices)[i + 6] - (*m_pVertices)[i + 2]);
		osg::Vec3 normal_bak = ((*m_pVertices)[i + 7] - (*m_pVertices)[i + 6]) ^ ((*m_pVertices)[i + 2] - (*m_pVertices)[i + 6]);
		osg::Vec3 normal_lft = ((*m_pVertices)[i + 4] - (*m_pVertices)[i + 7]) ^ ((*m_pVertices)[i + 3] - (*m_pVertices)[i + 7]);
		osg::Vec3 normal_top = ((*m_pVertices)[i + 3] - (*m_pVertices)[i + 2]) ^ ((*m_pVertices)[i + 1] - (*m_pVertices)[i + 2]);

		osg::Vec3 normal_0 = normal_lft + normal_fnt + normal_top;
		osg::Vec3 normal_1 = normal_rgt + normal_fnt + normal_top;
		osg::Vec3 normal_2 = normal_rgt + normal_bak + normal_top;
		osg::Vec3 normal_3 = normal_lft + normal_bak + normal_top;
		osg::Vec3 normal_4 = normal_lft + normal_fnt + normal_blw;
		osg::Vec3 normal_5 = normal_rgt + normal_fnt + normal_blw;
		osg::Vec3 normal_6 = normal_rgt + normal_bak + normal_blw;
		osg::Vec3 normal_7 = normal_lft + normal_bak + normal_blw;

		normal_blw.normalize();
		normal_fnt.normalize();
		normal_rgt.normalize();
		normal_bak.normalize();
		normal_lft.normalize();
		normal_top.normalize();
		normal_0.normalize();
		normal_1.normalize();
		normal_2.normalize();
		normal_3.normalize();
		normal_4.normalize();
		normal_5.normalize();
		normal_6.normalize();
		normal_7.normalize();

		pNormalize->push_back(normal_lft);
		pNormalize->push_back(normal_rgt);
		pNormalize->push_back(normal_rgt);
		pNormalize->push_back(normal_lft);
		pNormalize->push_back(normal_lft);
		pNormalize->push_back(normal_5);
		pNormalize->push_back(normal_6);
		pNormalize->push_back(normal_7);
	}

	m_pCellGeom->setNormalArray(pNormalize.get(), osg::Array::BIND_PER_VERTEX);
}

void CX3DGeobodyBuilder::UpdateNode(EEventType eType)
{
	if (eType == EColormapChanged)
	{
		_BuildColor();
	}
}

void CX3DGeobodyBuilder::_CalcUTMDirection()
{
	const CXSeismicUTMTool& utmTool = m_pGeobody->GetUTM();
	
	double dX0, dX1, dX2, dX3, dY0, dY1, dY2, dY3;
	utmTool.LineToXY(utmTool.GetFirstInline(),		utmTool.GetFirstCrossline(),		dX0, dY0);
	utmTool.LineToXY(utmTool.GetFirstInline() + 1,	utmTool.GetFirstCrossline() + 1,	dX2, dY2);
	utmTool.LineToXY(utmTool.GetFirstInline(),		utmTool.GetFirstCrossline() + 1,	dX1, dY1);
	utmTool.LineToXY(utmTool.GetFirstInline() + 1,	utmTool.GetFirstCrossline(),		dX3, dY3);

	double dZTemp = 0.0;
	osg::Vec3 vecLocal0, vecLocal1, vecLocal2, vecLocal3;
	m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX0, dY0, dZTemp), vecLocal0);
	m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX1, dY1, dZTemp), vecLocal1);
	m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX2, dY2, dZTemp), vecLocal2);
	m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX3, dY3, dZTemp), vecLocal3);

	m_pVector02.set(vecLocal2 - vecLocal0);
	m_pVector13.set(vecLocal3 - vecLocal1);

	m_pVector02.normalize();
	m_pVector13.normalize();

	double dOffsetI = utmTool.GetInlineInterval() / 2;
	double dOffsetJ = utmTool.GetCrosslineInterval() / 2;

	double dLength = sqrt(dOffsetI * dOffsetI + dOffsetJ * dOffsetJ);
	m_offsetK = m_pGeobody->GetZInc() / 2;

	m_pVector02 *= dLength;
	m_pVector13 *= dLength;
}

void CX3DGeobodyBuilder::_PushCellVerticesToGeometryByCentral(double dX, double dY, double dZ)
{
	osg::Vec3 localCentral;
	m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dY, dZ), localCentral);

	osg::Vec3 vec0(localCentral - m_pVector02);
	osg::Vec3 vec1(localCentral - m_pVector13);
	osg::Vec3 vec2(localCentral + m_pVector02);
	osg::Vec3 vec3(localCentral + m_pVector13);

	m_pVertices->push_back(vec0 + osg::Vec3(0.0, 0.0, m_offsetK));
	m_pVertices->push_back(vec1 + osg::Vec3(0.0, 0.0, m_offsetK));
	m_pVertices->push_back(vec2 + osg::Vec3(0.0, 0.0, m_offsetK));
	m_pVertices->push_back(vec3 + osg::Vec3(0.0, 0.0, m_offsetK));
	m_pVertices->push_back(vec0 - osg::Vec3(0.0, 0.0, m_offsetK));
	m_pVertices->push_back(vec1 - osg::Vec3(0.0, 0.0, m_offsetK));
	m_pVertices->push_back(vec2 - osg::Vec3(0.0, 0.0, m_offsetK));
	m_pVertices->push_back(vec3 - osg::Vec3(0.0, 0.0, m_offsetK));
}