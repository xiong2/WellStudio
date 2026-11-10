#include "xbmseismicdvbuilder.h"
#include <osg/BlendFunc>
#include <osg/LineWidth>
#include <osg/Hint>
#include "xseismicdatavolume.h"
#include "xviewinfoseismicdv.h"
#include "x3dbuilderfactory.h"
#include "xglobal.h"
#include "x3dglobalcoordmap.h"
#include "xcolormap.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXBMSeismicDVBuilder)
{ EXSeismicDataVolume, e3DBaseMap }
END_REGISTER_BUILDER_TO_FACTORY(CXBMSeismicDVBuilder)

CXBMSeismicDVBuilder::CXBMSeismicDVBuilder()
	: CX3DBuilderAbstract()
{

}

CXBMSeismicDVBuilder::~CXBMSeismicDVBuilder()
{

}

osg::ref_ptr<osg::Group> CXBMSeismicDVBuilder::Build(QUuid objId)
{
	m_pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(objId));
	m_pViewInfo = dynamic_cast<CXViewInfoSeismicDV*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pDV || !m_pViewInfo)
		return nullptr;

	_UpdateDVData();

	osg::ref_ptr<osg::Geode> pGeode = new osg::Geode;
	if (m_pDV->IsPrestack())
	{
		pGeode->addDrawable(_BuildFoldMapGeometry());
	}
	else
	{
		pGeode->addDrawable(_BuildFrameGeometry());
	}
	pGeode->setNodeMask(0x1);

	return pGeode;
}

void CXBMSeismicDVBuilder::UpdateNode(EEventType eType)
{
	if (EColormapChanged == eType)
	{
		_UpdateFoldMapColormap();
	}
}

osg::Vec3 CXBMSeismicDVBuilder::_IJToLocal(double dI, double dJ, double dZ)
{
	const CXSeismicUTMTool& utm = m_pDV->GetUTM();
	
	double dX, dY;
	utm.IJToXY2(dI, dJ, dX, dY);

	osg::Vec3 vecLocal;
	m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dY, dZ), vecLocal);

	return vecLocal;
}

osg::Geometry* CXBMSeismicDVBuilder::_BuildFoldMapGeometry()
{
	m_pGeomFoldMap = new osg::Geometry;

	// vertex
	osg::Vec3Array* pVertex = new osg::Vec3Array(4 * m_nI * m_nJ);

	for (int i = 0; i != m_nI; ++i)
	{
		for (int j = 0; j != m_nJ; ++j)
		{
			(*pVertex)[4 * (i * m_nJ + j)].set(_IJToLocal(i - 0.5, j - 0.5, m_dZMax));
			(*pVertex)[4 * (i * m_nJ + j) + 1].set(_IJToLocal(i + 0.5, j - 0.5, m_dZMax));
			(*pVertex)[4 * (i * m_nJ + j) + 2].set(_IJToLocal(i + 0.5, j + 0.5, m_dZMax));
			(*pVertex)[4 * (i * m_nJ + j) + 3].set(_IJToLocal(i - 0.5, j + 0.5, m_dZMax));
		}
	}

	m_pGeomFoldMap->setVertexArray(pVertex);
	m_pGeomFoldMap->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4 * m_nI * m_nJ));

	_UpdateFoldMapColormap();
	
	return m_pGeomFoldMap.get();
}

osg::Geometry * CXBMSeismicDVBuilder::_BuildFrameGeometry()
{
	m_pGeomFrame = new osg::Geometry;
	osg::Vec3Array* pVertex = new osg::Vec3Array(4);
	(*pVertex)[0].set(_IJToLocal(0, 0, m_dZMin));
	(*pVertex)[1].set(_IJToLocal(0, m_nJ - 1, m_dZMin));
	(*pVertex)[2].set(_IJToLocal(m_nI - 1, m_nJ - 1, m_dZMin));
	(*pVertex)[3].set(_IJToLocal(m_nI - 1, 0, m_dZMin));
	m_pGeomFrame->setVertexArray(pVertex);
	m_pGeomFrame->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, 4));

	_UpdateFrameInfo();

	return m_pGeomFrame;
}

void CXBMSeismicDVBuilder::_UpdateFrameInfo()
{
	if (!m_pGeomFrame.valid())
		return;

	const QColor& color = m_pViewInfo->GetBMFrameColor();
	int iWidth = m_pViewInfo->GetBMFrameWidth();

	osg::Vec4Array* pColors = new osg::Vec4Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	m_pGeomFrame->setColorArray(pColors, osg::Array::BIND_OVERALL);
	m_pGeomFrame->getOrCreateStateSet()->setAttributeAndModes(new osg::LineWidth(iWidth), osg::StateAttribute::ON);
}

void CXBMSeismicDVBuilder::_UpdateFoldMapColormap()
{
	if (!m_pGeomFoldMap.valid())
		return;

	CXColormap* pColormap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());

	const CXSeismicUTMTool& utm = m_pDV->GetUTM();
	int nI = utm.GetNI();
	int nJ = utm.GetNJ();

	unsigned short* pFoldMap = new unsigned short[nI * nJ];
	m_pDV->GetFoldMap(pFoldMap);
	unsigned short usMax = *std::max_element(pFoldMap, pFoldMap + nI * nJ);

	osg::Vec4Array* pColors = new osg::Vec4Array(4 * nI * nJ);

	for (int i = 0; i != 4 * nI * nJ; ++i)
	{
		int nFold = qRound(pFoldMap[i / 4]* 1.f * (pColormap->GetColorNum() - 1) / usMax);
		const QColor& color = pColormap->ColorAt(nFold);
		(*pColors)[i].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	}

	delete[] pFoldMap;

	m_pGeomFoldMap->setColorArray(pColors, osg::Array::BIND_PER_VERTEX);
}

void CXBMSeismicDVBuilder::_UpdateDVData()
{
	// data
	m_utm = m_pDV->GetUTM();
	m_nI = m_utm.GetNI();
	m_nJ = m_utm.GetNJ();
	m_pDV->GetSamplingRange(m_dZMin, m_dZMax, m_dZInterval);
}
