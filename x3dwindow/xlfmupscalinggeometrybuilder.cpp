#include "xlfmupscalinggeometrybuilder.h"

#include <array>
#include <osg/Geometry>
#include <osgUtil/SmoothingVisitor>

#include "x3dbuilderfactory.h"
#include "xlfmupscalinggeometry.h"
#include "xglobal.h"
#include "x3dglobalcoordmap.h"
#include "xlfmupscalingattribute.h"
#include "xviewinfoobject.h"
#include "xcolormap.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXLFMUpscalingGeometryBuilder)
{ EXLFMUpscalingGeometry, e3DWindow }
END_REGISTER_BUILDER_TO_FACTORY(CXLFMUpscalingGeometryBuilder)

CXLFMUpscalingGeometryBuilder::CXLFMUpscalingGeometryBuilder()
    : CX3DBuilderAbstract()
{

}

CXLFMUpscalingGeometryBuilder::~CXLFMUpscalingGeometryBuilder()
{

}

osg::ref_ptr<osg::Group> CXLFMUpscalingGeometryBuilder::Build(QUuid objId)
{
    if (!m_pBuilderNode)
    {
        m_pBuilderNode = new osg::Group;
    }

    m_pUpscaling = dynamic_cast<CXLFMUpscalingGeometry*>(::GetObjectByID(objId));
    if (!m_pUpscaling)
    {
        return NULL;
    }

    m_pCellGeom = new osg::Geometry;
    m_pCellGeom->setName("LFM Upscaling cell geometry");
    m_pCellGeom->setUseVertexBufferObjects(true);
    m_pCellGeom->getOrCreateStateSet()->setMode(GL_PRIMITIVE_RESTART, osg::StateAttribute::ON);

    _BuildVertices();
    _BuildIndices();
    _BuildColor();
    _BuildNormal();

    osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
    pGeode->setName(m_pUpscaling->GetObjectName().toLatin1().data());
    pGeode->addDrawable(m_pCellGeom.get());
    m_pBuilderNode->addChild(pGeode.get());

    return m_pBuilderNode.get();
}

void CXLFMUpscalingGeometryBuilder::UpdateNode(EEventType eType)
{
	if (eType == EColormapChanged || eType == EInfoChanged)
	{
		_UpdateColor();
	}
}

void CXLFMUpscalingGeometryBuilder::_BuildVertices()
{
    m_pVertices = new osg::Vec3Array;
    m_pVertices->push_back(osg::Vec3(0.0, 0.0, 0.0)); // for restart mark.

    for (QUuid wellID : m_pUpscaling->GetAllWellID())
    {
        std::vector<qint64> vecIndex;
        std::vector<double> vecXYZ;
        std::vector<double> vecTemp;
        m_pUpscaling->GetOneWellInfo(wellID, vecIndex, vecXYZ, vecTemp, vecTemp);

        for (decltype(vecXYZ.size()) i = 0; i < vecXYZ.size(); i += 3)
        {
            double dX = vecXYZ.at(i);
            double dY = vecXYZ.at(i + 1);
            double dZ = vecXYZ.at(i + 2);

            osg::Vec3 vecLocal;
            m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dY, dZ), vecLocal);
            m_pVertices->push_back(vecLocal);
        }
    }

    m_pCellGeom->setVertexArray(m_pVertices.get());
}

void CXLFMUpscalingGeometryBuilder::_BuildIndices()
{
    osg::ref_ptr<osg::DrawElementsUInt> pCellPrimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, 0);

    std::array<uint, 14> triangleStrips = { 3, 2, 7, 6, 5, 2, 1, 3, 0, 7, 4, 5, 0, 1 };
    for (size_t i = 1; i < m_pVertices->size(); i += 8)
    {
        for (size_t j = 0; j != 14; ++j)
        {
            pCellPrimitive->push_back(triangleStrips[j] + i);
        }
        pCellPrimitive->push_back(0); // restart
    }
    m_pCellGeom->addPrimitiveSet(pCellPrimitive.get());
}

void CXLFMUpscalingGeometryBuilder::_BuildColor()
{
	if (!m_pUpscaling)
		return;

    QColor color = m_pUpscaling->GetColor();
    osg::ref_ptr<osg::Vec4Array> pColor = new osg::Vec4Array(1);
    (*pColor)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    m_pCellGeom->setColorArray(pColor.get());
    m_pCellGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
}

void CXLFMUpscalingGeometryBuilder::_BuildNormal()
{
    m_pCellGeom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
    osgUtil::SmoothingVisitor::smooth(*m_pCellGeom);
}

void CXLFMUpscalingGeometryBuilder::_UpdateColor()
{
	auto pViewInfo = dynamic_cast<CXViewInfoObject*>(m_pCurWin->GetObjectViewInfo(m_pUpscaling->GetObjectID()));
	auto pAttribute = dynamic_cast<CXLFMUpscalingAttribute*>(::GetObjectByID(pViewInfo->GetAttributeObjID()));
	
	if (!pViewInfo || !pAttribute)
	{
		_BuildColor();
		return;
	}
	
	CXColormap* pColormap = CXColormap::GetColormap(pViewInfo->GetColormapName());

	double dMin, dMax;
	pAttribute->GetDataRange(dMin, dMax);

	osg::ref_ptr<osg::Vec4Array> pColor = new osg::Vec4Array(m_pVertices->size());
	int idx = 0;
	(*pColor)[idx++].set(0.f, 0.f, 0.f, 1.f); // for matching restart mark.
	
	for (const QUuid& wellID : m_pUpscaling->GetAllWellID())
	{
		std::vector<double> vecData;
		pAttribute->GetOneWellInfo(wellID, vecData);

		for (double dValue : vecData)
		{
			const QColor& color = qFuzzyCompare(dValue, ::g_dInvalidData) ? pColormap->GetInvalidColor() :
				pColormap->ColorAt(qRound((dValue - dMin) / (dMax - dMin) * (pColormap->GetColorNum() - 1)));

			for (int i = 0; i != 8; ++i)
			{
				(*pColor )[idx++].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
			}
		}
	}

	Q_ASSERT(idx == m_pVertices->size());
	
	m_pCellGeom->setColorArray(pColor.get());
	m_pCellGeom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	m_pCellGeom->getOrCreateStateSet()->setMode(GL_ALPHA_TEST, osg::StateAttribute::ON);
	m_pCellGeom->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
}