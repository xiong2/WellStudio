#include "xbmseismicsectionbuilder.h"

#include <osg/Depth>
#include <osg/LineWidth>
#include <osg/CullFace>
#include <osg/PolygonOffset>
#include <osg/BlendFunc>
#include <osg/ValueObject>
#include <osg/BlendFunc>
#include <QtMath>
#include <QMessageBox>

#include "xcolormap.h"
#include "xdbio.h"
#include "xbmpickcallback.h"
#include "xseismicsection.h"
#include "xglobal.h"
#include "x3dglobalcoordmap.h"
#include "xviewinfoseismicsection.h"
#include "x3dbuilderfactory.h"
#include "xseismicdatavolume.h"
#include "x3dutility.h"
#include "xprocessengine.h"
#include "xviewinfotimeslice.h"
#include "xviewinfoseismicdv.h"
#include "xbasemapwindow.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXBMSeismicSectionBuilder)
{ EXSeismicSection, e3DBaseMap }
END_REGISTER_BUILDER_TO_FACTORY(CXBMSeismicSectionBuilder)

CXBMSeismicSectionBuilder::CXBMSeismicSectionBuilder()
{

}

CXBMSeismicSectionBuilder::~CXBMSeismicSectionBuilder()
{

}

osg::ref_ptr<osg::Group> CXBMSeismicSectionBuilder::Build(QUuid objId)
{
	// data
	m_pSection = dynamic_cast<CXSeismicSection*>(::GetObjectByID(objId));
	m_pViewInfo = dynamic_cast<CXViewInfoSeismicSection*>(m_pCurWin->GetObjectViewInfo(objId));

	if (!m_pSection || !m_pViewInfo)
		return nullptr;

	SetObjectID(objId);

	m_utm = m_pSection->GetUTM();
	m_type = m_pSection->GetSectionType();
	_UpdateSectionData();

	m_pGeode = new osg::Geode;
	m_pGeode->setUserValue("objID", objId.toString().toStdString());

	if (m_type == eInlineSection || m_type == eCrosslineSection)
	{
		m_pGeode->addDrawable(_BuildSectionLine());
	}
	else if (m_type = eTimeSlice)
	{
		m_pGeode->addDrawable(_BuildSectionSlice());
		_CheckFractureDisplay();
	}

	m_pGeode->setEventCallback(new CXBMPickCallback(this));
	m_pGeode->setDataVariance(osg::Object::DYNAMIC);

	m_pBuilderNode = new osg::Group;
	m_pBuilderNode->addChild(m_pGeode);
	
	return m_pBuilderNode;
}

void CXBMSeismicSectionBuilder::UpdateNode(EEventType eType)
{
	if (eType == EDataChanged)
	{
		if (!m_pGeometry.valid())
			return;

		_UpdateSectionData();

		if (m_type == eInlineSection || m_type == eCrosslineSection)
		{
			m_pGeometry->setVertexArray(_CalcSectionLineVertex());
		}
		else if (m_type == eTimeSlice)
		{
			osg::StateSet* pStateSet = m_pGeometry->getOrCreateStateSet();
			pStateSet->setTextureAttributeAndModes(0, _BuildSectionSliceTexture(), osg::StateAttribute::ON);

			_CheckFractureDisplay();
		}
	}
	else if (eType == EInfoChanged)
	{
		_UpdateLineViewInfo(false);

		if (m_pGeometry && eTimeSlice == m_type)
		{
			m_pGeometry->getOrCreateStateSet()->removeUniform(m_pUniformColorTable);
			m_pGeometry->getOrCreateStateSet()->addUniform(_BuildSectionSliceColorTable());

			_CheckFractureDisplay();
		}
	}
	else if (eType == EColormapChanged)
	{
		_UpdateSectionData();

		osg::StateSet* pStateSet = m_pGeometry->getOrCreateStateSet();
		pStateSet->setTextureAttributeAndModes(0, _BuildSectionSliceTexture(), osg::StateAttribute::ON);
		pStateSet->removeUniform(m_pUniformColorTable);
		pStateSet->addUniform(_BuildSectionSliceColorTable());
	}
}

bool CXBMSeismicSectionBuilder::SetActive(bool bActive)
{
	if (!m_pGeometry.valid())
		return false;

	auto pBMWin = dynamic_cast<CXBaseMapWindow*>(m_pCurWin);
	Q_ASSERT(pBMWin);

	if (bActive && (pBMWin->IsRandomSectionMode() || pBMWin->IsPolygonMode()))
		return false;

	if (eTimeSlice == m_type) // time slice
	{
		_UpdateDisplayRange(bActive);
		pBMWin->SetVolumeToolbarVisible(m_pSection, bActive);
		if (bActive)
		{
			m_pGeode->addDrawable(_BuildSectionSliceFrame());
		}
		else
		{
			m_pGeode->removeDrawable(m_pFrameGeometry);
		}
	}
	else if (eInlineSection == m_type || eCrosslineSection == m_type)
	{
		_UpdateLineViewInfo(bActive);
	}

	pBMWin->SetVCRControlVisible(m_pSection, bActive);

	if (pBMWin->IsRandomSectionMode() || pBMWin->IsPolygonMode())
		return false;
	
	return true;
}

void CXBMSeismicSectionBuilder::UpdateSeismicLinePosition(int iInline, int iXline)
{
	if (!m_pGeometry.valid())
		return;

	if (eInlineSection == m_type)
	{
		m_nTrace = qBound(m_utm.GetFirstInline(), iInline, m_utm.GetLastInline());
	}
	else if (eCrosslineSection == m_type)
	{
		m_nTrace = qBound(m_utm.GetFirstCrossline(), iXline, m_utm.GetLastCrossline());
	}

	m_pGeometry->setVertexArray(_CalcSectionLineVertex());
}

int CXBMSeismicSectionBuilder::GetCurrentTraceNumber()
{
	return m_nTrace;
}

void CXBMSeismicSectionBuilder::_UpdateSectionData()
{
	m_nTrace = qRound(m_pSection->GetSectionNumber());
	m_pSection->GetSectionRange(m_iSTrace, m_iETrace);
}

void CXBMSeismicSectionBuilder::_UpdateDisplayRange(bool bDisplaySection)
{
	if (!bDisplaySection && m_pViewInfoDV && m_pViewInfoDV->HasFold())
	{
		const CXHistogram& histogram = m_pViewInfoDV->GetFoldHistogram();
		m_pViewInfoDV->SetDisplayDataMin(histogram.m_dDataMin);
		m_pViewInfoDV->SetDisplayDataMax(histogram.m_dDataMax);
	}
	else
	{
		CXObject* pObjDV = ::GetObjectByID(m_pViewInfo->GetAttributeObjID());
		if (!pObjDV)
			return;

		double dMin, dMax;
		pObjDV->GetDataRange(dMin, dMax);
		m_pViewInfo->SetDisplayDataMin(dMin);
		m_pViewInfo->SetDisplayDataMax(dMax);
	}
}

void CXBMSeismicSectionBuilder::_UpdateLineViewInfo(bool bPicked)
{
	if (!m_pGeometry.valid())
		return;

	const QColor& color = bPicked ? m_pViewInfo->GetBMPickedLineColor() : m_pViewInfo->GetBMLineColor();
	int width = bPicked ? m_pViewInfo->GetBMPickedLineWidth() : m_pViewInfo->GetBMLineWidth();

	osg::Vec3Array* pColors = new osg::Vec3Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF());
	m_pGeometry->setColorArray(pColors, osg::Array::BIND_OVERALL);
	m_pGeometry->getOrCreateStateSet()->setAttributeAndModes(new osg::LineWidth(width), osg::StateAttribute::ON);
}

void CXBMSeismicSectionBuilder::_CheckFractureDisplay()
{
	auto pViewInfo = dynamic_cast<CXViewInfoTimeSlice*>(m_pViewInfo);

	if (m_type != eTimeSlice || !pViewInfo || 0 == pViewInfo->GetDisplayMode())
		return;

	m_pGeode->removeDrawable(m_pGeometry);

	if (pViewInfo->GetSeismicDisplay())
	{
		m_pGeode->addDrawable(m_pGeometry);
	}

	m_pGeode->removeDrawable(m_pFracGeom);
	m_pGeode->addDrawable(_BuildFractureGeometry());
}

osg::Geometry* CXBMSeismicSectionBuilder::_BuildSectionLine()
{
	m_pGeometry = new osg::Geometry;

	m_pGeometry->setVertexArray(_CalcSectionLineVertex());
	m_pGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, 2));
	_UpdateLineViewInfo(false);

	osg::StateSet* pStateSet = m_pGeometry->getOrCreateStateSet();
	pStateSet->setRenderBinDetails(11, "RenderBin");

	return m_pGeometry.get();
}

osg::Geometry* CXBMSeismicSectionBuilder::_BuildSectionSlice()
{
	m_pGeometry = new osg::Geometry;

	m_pGeometry->setVertexArray(_CalcSectionSliceVertex());

	osg::Vec2Array* pTexCoord = new osg::Vec2Array(4);
	m_pGeometry->setTexCoordArray(0, pTexCoord);

	(*pTexCoord)[0].set(0, 0);
	(*pTexCoord)[1].set(0, 1);
	(*pTexCoord)[2].set(1, 1);
	(*pTexCoord)[3].set(1, 0);

	m_pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	osg::StateSet* pStateSet = m_pGeometry->getOrCreateStateSet();
	pStateSet->setTextureAttributeAndModes(0, _BuildSectionSliceTexture(), osg::StateAttribute::ON);
	pStateSet->setAttribute(_BuildSectionSliceProgram(), osg::StateAttribute::ON);
	pStateSet->setAttribute(new osg::CullFace(osg::CullFace::FRONT), osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
	pStateSet->addUniform(new osg::Uniform("sectionTex", 0));
	pStateSet->addUniform(_BuildSectionSliceColorTable());
	pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
	pStateSet->setAttributeAndModes(new osg::BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA), osg::StateAttribute::ON);

	return m_pGeometry.get();
}

osg::Geometry* CXBMSeismicSectionBuilder::_BuildSectionSliceFrame()
{
	m_pFrameGeometry = new osg::Geometry;

	m_pFrameGeometry->setVertexArray(_CalcSectionSliceVertex());
	m_pFrameGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, 4));

	const QColor& color = m_pViewInfo->GetBMPickedLineColor();
	osg::Vec3Array* pColors = new osg::Vec3Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF());
	m_pFrameGeometry->setColorArray(pColors, osg::Array::BIND_OVERALL);

	osg::StateSet* pStateSet = m_pFrameGeometry->getOrCreateStateSet();
	pStateSet->setAttributeAndModes(new osg::LineWidth(m_pViewInfo->GetBMPickedLineWidth()), osg::StateAttribute::ON);
	pStateSet->setAttributeAndModes(new osg::PolygonOffset(-1.f, 1.f), osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
	pStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	pStateSet->setRenderBinDetails(11, "RenderBin");

	return m_pFrameGeometry.get();
}

osg::Geometry * CXBMSeismicSectionBuilder::_BuildFractureGeometry()
{
	auto pViewInfo = dynamic_cast<CXViewInfoTimeSlice*>(m_pViewInfo);

	m_pFracGeom = new osg::Geometry;

	const QUuid& uuidAzimuth = pViewInfo->GetFracAzimuth();
	const QUuid& uuidDensity = pViewInfo->GetFracDensity();
	int ndX = pViewInfo->GetFracDX();
	int ndY = pViewInfo->GetFracDY();
	float fScale = pViewInfo->GetFracScale();
	float fMinThreshold = pViewInfo->GetFracMinThreshold();
	float fMaxThreshold = pViewInfo->GetFracMaxThreshold();

	std::vector<float> vecDensity, vecAzimuth, vecColor;
	CXSeismicDataVolume::GetFractureInfo(uuidDensity, uuidAzimuth, m_pSection->GetSectionNumber(), ndX, ndY, fMinThreshold, fMaxThreshold, vecDensity, vecAzimuth, vecColor);

	if (vecDensity.empty() && vecAzimuth.empty())
		return nullptr;

	int nDX = qMax(1, ndX);
	int nDY = qMax(1, ndY);

	int nFracNI = m_utm.GetNI() / nDY;
	int nFracNJ = m_utm.GetNJ() / nDX;

	osg::Vec3Array* pVertex = new osg::Vec3Array;
	for (int i = 0; i < nFracNI; ++i)
	{
		int iMin = i * nDY;
		int iMax = iMin + nDY - 1;
		for (int j = 0; j < nFracNJ; ++j)
		{
			int jMin = j * nDX;
			int jMax = jMin + nDX - 1;

			osg::Vec3d vecCenter;
			m_utm.IJToXY2((iMin + iMax) * 0.5, (jMin + jMax) * 0.5, vecCenter.x(), vecCenter.y());

			float fAzimuth = vecAzimuth.at(i * nFracNJ + j);
			float fDensity = vecDensity.at(i * nFracNJ + j);

			if (fAzimuth == ::g_dInvalidData && fDensity == ::g_dInvalidData)
				continue;

			if (fAzimuth < 0)
			{
				fAzimuth += 360;
			}

			osg::Vec3d vecUnitNormal{ qCos(fAzimuth), qSin(fAzimuth), 0.0 };
			osg::Vec3d vecNormal = vecUnitNormal * fDensity * fScale * 0.5;

			osg::Vec3 vecHead, vecEnd;
			m_pCoordMap->MapWorldToLocal(vecCenter - vecNormal, vecHead);
			m_pCoordMap->MapWorldToLocal(vecCenter + vecNormal, vecEnd);

			pVertex->push_back(vecHead);
			pVertex->push_back(vecEnd);
		}
	}
	m_pFracGeom->setVertexArray(pVertex);
	m_pFracGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, pVertex->size()));

	const QColor& color = pViewInfo->GetFracColor();
	osg::Vec4Array* pColors = new osg::Vec4Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	m_pFracGeom->setColorArray(pColors, osg::Array::BIND_OVERALL);
	
	int iWidth = pViewInfo->GetFracWidth();
	m_pFracGeom->getOrCreateStateSet()->setAttributeAndModes(new osg::LineWidth(iWidth), osg::StateAttribute::ON);

	return m_pFracGeom.get();
}

osg::Texture2D* CXBMSeismicSectionBuilder::_BuildSectionSliceTexture()
{
	// read seismic data
	QUuid currentVolumeID = m_pViewInfo->GetAttributeObjID();
	if (currentVolumeID == m_pSection->GetObjectID())
		return nullptr;

	auto pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(currentVolumeID));
	Q_ASSERT(pDV);
	m_pViewInfoDV = dynamic_cast<CXViewInfoSeismicDV*>(m_pCurWin->GetObjectViewInfo(pDV->GetObjectID()));

	if (!pDV->HasSliceFile())
	{
		if (QMessageBox::Yes == QMessageBox::question(nullptr, "XStudio", "Viewing a time or depth slice requires a slice file. You do not have the slice file yet. Do you want to create one now?"))
		{
			CXProcessEngine process(pDV, ETraceToSlice);
			process.CalculateOnly();
		}
	}

	int nInlineQty = pDV->GetInlineQty();
	int nXlineQty = pDV->GetXlineQty();	

	float* pData = new float[nInlineQty * nXlineQty];
	if (!pDV->ReadSlice(m_nTrace, pData))
		return nullptr;

	double dMin, dMax;
	pDV->GetDataRange(dMin, dMax);
	dMin = qMax(dMin, m_pViewInfoDV->GetDisplayDataMin());
	dMax = qMin(dMax, m_pViewInfoDV->GetDisplayDataMax());

	CXColormap *pColormap = CXColormap::GetColormap(m_pViewInfoDV->GetColormapName());
	if (pColormap == NULL)
		return nullptr;

	auto pTexImageData = new unsigned int[nInlineQty * nXlineQty];

	for (int i = 0; i < nInlineQty; ++i) // inline
	{
		for (int x = 0; x < nXlineQty; ++x) // xline
		{
			double dCurrValue = pData[i * nXlineQty + x];
			int index;
			if (qFuzzyCompare(dMin, dMax))
			{
				index = 0;
			}
			else if (qFuzzyCompare(dCurrValue, ::g_dInvalidData) || (m_pViewInfoDV->GetBZeroIsInvalid() && dCurrValue == 0.f))
			{
				pTexImageData[x * nInlineQty + i] = pColormap->GetInvalidColor().rgba();
				continue;
			}
			else
			{
				index = static_cast<int>((dCurrValue - dMin) / (dMax - dMin) * pColormap->GetColorNum());
				index = qBound(0, index, pColormap->GetColorNum());
			}

			pTexImageData[x * nInlineQty + i] = QColor(index, index, index).rgba();
		}
	}

	osg::Image* pTexImage = new osg::Image;
	pTexImage->setImage(nInlineQty, nXlineQty, 1, GL_RGBA32F_ARB, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)pTexImageData, osg::Image::NO_DELETE);

	// texture setting
	osg::Texture2D* pTexture = new osg::Texture2D;
	pTexture->setImage(pTexImage);
	pTexture->setUnRefImageDataAfterApply(true);
	pTexture->setResizeNonPowerOfTwoHint(false);
	pTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	pTexture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	pTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
	pTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);

	delete[] pData;

	return pTexture;
}

osg::Program* CXBMSeismicSectionBuilder::_BuildSectionSliceProgram()
{
	osg::Program* pProgram = new osg::Program;

	std::string strVert = CXDBIO::GetShaderFilePath().toStdString() + "section.vert";
	std::string strFrag = CXDBIO::GetShaderFilePath().toStdString() + "section.frag";

	pProgram->addShader(osg::Shader::readShaderFile(osg::Shader::VERTEX, strVert));
	pProgram->addShader(osg::Shader::readShaderFile(osg::Shader::FRAGMENT, strFrag));

	return pProgram;
}

osg::Uniform* CXBMSeismicSectionBuilder::_BuildSectionSliceColorTable()
{
	if (!m_pViewInfoDV)
		return nullptr;

 	CXColormap* pColormap = CXColormap::GetColormap(m_pViewInfoDV->GetColormapName());
	Q_ASSERT(pColormap);

	m_pUniformColorTable = new osg::Uniform(osg::Uniform::FLOAT_VEC4, "colorTable", 256);

	for (int i = 0; i < 255; ++i)
	{
		int index = qRound(i / 254.0 * (pColormap->GetColorNum() - 1));
		const QColor& color = pColormap->ColorAt(index);
		m_pUniformColorTable->setElement(i, osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	}

	const QColor& invalidColor = pColormap->GetInvalidColor();
	m_pUniformColorTable->setElement(255, osg::Vec4(invalidColor.redF(), invalidColor.greenF(), invalidColor.blueF(), invalidColor.alphaF()));

	return m_pUniformColorTable.get();
}

osg::Vec3Array* CXBMSeismicSectionBuilder::_CalcSectionLineVertex()
{
	// data
	osg::Vec3d vecStart, vecEnd;

	switch (m_pSection->GetSectionType())
	{
	case eInlineSection:
	{
		m_utm.LineToXY(m_nTrace, _GetFirstXline(), vecStart.x(), vecStart.y());
		m_utm.LineToXY(m_nTrace, _GetLastXline(), vecEnd.x(), vecEnd.y());
		break;
	}
	case eCrosslineSection:
	{
		m_utm.LineToXY(_GetFirstInline(), m_nTrace, vecStart.x(), vecStart.y());
		m_utm.LineToXY(_GetLastInline(), m_nTrace, vecEnd.x(), vecEnd.y());
		break;
	}
	default:
		throw std::logic_error("only inline or crossline can display as line in basemap.");
	}

	vecStart.z() = -1;
	vecEnd.z() = -1;

	// vertex
	m_pLineVertex = new osg::Vec3Array(2);

	m_pCoordMap->MapWorldToLocal(vecStart, (*m_pLineVertex)[0]);
	m_pCoordMap->MapWorldToLocal(vecEnd, (*m_pLineVertex)[1]);
	
	return m_pLineVertex.get();
}

osg::Vec3Array* CXBMSeismicSectionBuilder::_CalcSectionSliceVertex()
{
	osg::Vec3d vecFIFX, vecFILX, vecLILX, vecLIFX;

	m_utm.LineToXY(m_utm.GetFirstInline(), m_utm.GetFirstCrossline(), vecFIFX.x(), vecFIFX.y());
	m_utm.LineToXY(m_utm.GetFirstInline(), m_utm.GetLastCrossline(), vecFILX.x(), vecFILX.y());
	m_utm.LineToXY(m_utm.GetLastInline(), m_utm.GetLastCrossline(), vecLILX.x(), vecLILX.y());
	m_utm.LineToXY(m_utm.GetLastInline(), m_utm.GetFirstCrossline(), vecLIFX.x(), vecLIFX.y());

	vecFIFX.z() = m_nTrace;
	vecFILX.z() = m_nTrace;
	vecLILX.z() = m_nTrace;
	vecLIFX.z() = m_nTrace;

	osg::Vec3Array* pVertex = new osg::Vec3Array(4);
	m_pGeometry->setVertexArray(pVertex);

	m_pCoordMap->MapWorldToLocal(vecFIFX, (*pVertex)[0]);
	m_pCoordMap->MapWorldToLocal(vecFILX, (*pVertex)[1]);
	m_pCoordMap->MapWorldToLocal(vecLILX, (*pVertex)[2]);
	m_pCoordMap->MapWorldToLocal(vecLIFX, (*pVertex)[3]);

	return pVertex;
}

int CXBMSeismicSectionBuilder::_GetFirstInline()
{
	return (m_iSTrace == -1) ? m_utm.GetFirstInline() : m_iSTrace;
}

int CXBMSeismicSectionBuilder::_GetLastInline()
{
	return (m_iETrace == -1) ? m_utm.GetLastInline() : m_iETrace;
}

int CXBMSeismicSectionBuilder::_GetFirstXline()
{
	return (m_iSTrace == -1) ? m_utm.GetFirstCrossline() : m_iSTrace;
}

int CXBMSeismicSectionBuilder::_GetLastXline()
{
	return (m_iETrace == -1) ? m_utm.GetLastCrossline() : m_iETrace;
}