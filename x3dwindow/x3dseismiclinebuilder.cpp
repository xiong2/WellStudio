#include "x3dseismiclinebuilder.h"

#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/CullFace>

#include "x3dbuilderfactory.h"
#include "xglobal.h"
#include "x2dseismicline.h"
#include "xviewinfo2dseismicline.h"
#include "xseismicdataline.h"
#include "x3dglobalcoordmap.h"
#include "x3dutility.h"
#include "xcolormap.h"
#include "xshaderutility.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DSeismicLineBuilder)
{ EX2DSeismicLine, e3DWindow }
END_REGISTER_BUILDER_TO_FACTORY(CX3DSeismicLineBuilder)

osg::ref_ptr<osg::Group> CX3DSeismicLineBuilder::Build(QUuid objID)
{
	m_pSeismicLine = dynamic_cast<CX2DSeismicLine*>(::GetObjectByID(objID));
	m_pViewInfo = dynamic_cast<CXViewInfo2DSeismicLine*>(m_pCurWin->GetObjectViewInfo(objID));
	
	if (!m_pSeismicLine || !m_pViewInfo) 
		return nullptr;

	m_pSection = m_pSeismicLine->GetDefaultSection(false);
	if (!m_pSection)
		return nullptr;

	_CalcVertexAndTexCoord();

	m_pSectionGeode = new osg::Geode;
	m_pSectionGeode->setName("2-D Seismic Line");
	m_pSectionGeode->addDrawable(_BuildSectionGeom());

	return m_pSectionGeode;
}

void CX3DSeismicLineBuilder::UpdateNode(EEventType eType)
{
	if (EDataChanged == eType)
	{
		_CalcVertexAndTexCoord();
		m_pSectionGeode->removeDrawable(m_pGeom);
		m_pSectionGeode->addDrawable(_BuildSectionGeom());
	}
	else if (EInfoChanged == eType || EColormapChanged == eType)
	{
		m_pGeom->setStateSet(_BuildTextureState());
	}
}

void CX3DSeismicLineBuilder::_CalcVertexAndTexCoord()
{
	double dStartZ, dStopZ, dStep;
	m_pSection->GetSamplingRange(dStartZ, dStopZ, dStep);
	m_nSampling = m_pSection->GetSamplingQty();

	m_nTrace = m_pSeismicLine->GetTraceNumber();
	const QList<int>& listInflexion = m_pSeismicLine->GetInflexionIndices();

	double *pX, *pY;
	m_pSeismicLine->GetCoordData(pX, pY);

	m_pVertices = new osg::Vec3Array(listInflexion.size() * 2);
	m_pTexCoord = new osg::Vec2Array(listInflexion.size() * 2);

	for (int i = 0; i != listInflexion.size(); ++i)
	{
		int iIndex = listInflexion.at(i);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(pX[iIndex], pY[iIndex], dStartZ), (*m_pVertices)[i * 2]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(pX[iIndex], pY[iIndex], dStopZ), (*m_pVertices)[i * 2 + 1]);

		(*m_pTexCoord)[i * 2].set(osg::Vec2((static_cast<float>(iIndex) / (m_nTrace - 1)), 0));
		(*m_pTexCoord)[i * 2 + 1].set(osg::Vec2((static_cast<float>(iIndex) / (m_nTrace - 1)), 1));
	}
}

osg::Geometry* CX3DSeismicLineBuilder::_BuildSectionGeom()
{
	m_pGeom = new osg::Geometry;
	m_pGeom->setName("2-D Line Section Geometry");

	m_pGeom->setUseVertexBufferObjects(true);
	m_pGeom->setVertexArray(m_pVertices.get());
	m_pGeom->setTexCoordArray(0, m_pTexCoord, osg::Array::BIND_PER_VERTEX);
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUAD_STRIP, 0, m_pVertices->size()));
	m_pGeom->setStateSet(_BuildTextureState());

	return m_pGeom;
}

osg::StateSet * CX3DSeismicLineBuilder::_BuildTextureState()
{
	float *pSectionData = m_pSection->GetData();
	if (!pSectionData)
		return nullptr;

	double dMin, dMax;
	m_pSection->GetDataRange(dMin, dMax);
	dMin = qMax(dMin, m_pViewInfo->GetDisplayDataMin());
	dMax = qMin(dMax, m_pViewInfo->GetDisplayDataMax());

	NXShaderUtility::DisplayInfo info{ m_pViewInfo->GetColormapName(), dMin, dMax, m_pViewInfo->GetBZeroIsInvalid() };

	return NXShaderUtility::BuildSectionTexture(pSectionData, m_nTrace, m_nSampling, info);
}