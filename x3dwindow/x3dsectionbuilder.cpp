#include "x3dsectionbuilder.h"

#include <osg/Array>
#include <osg/Image>
#include <osg/TexEnv>
#include <osg/TexMat>
#include <osg/PolygonMode>
#include <osg/FrontFace>
#include <osg/LineWidth>
#include <osg/PolygonOffset>
#include <osg/Material>
#include <osg/CullFace>
#include <osg/ComputeBoundsVisitor>
#include <osgDB/ReadFile>
#include <osg/ValueObject>

#include <QMessageBox>
#include <QtMath>

#include "xprocessengine.h"
#include "xpickcallback.h"
#include "xviewinfoseismicsection.h"
#include "x3dbuilderfactory.h"
#include "xglobal.h"
#include "xseismicsection.h"
#include "xseismicdatavolume.h"
#include "xcolormap.h"
#include "xviewinfoobject.h"
#include "x3dwindow.h"
#include "x3dglobalcoordmap.h"
#include "qstring.h"
#include "xdbio.h"
#include "xviewinfoseismicdv.h"
#include "xviewinfotimeslice.h"
#include "xshaderutility.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DSectionBuilder)
{ EXSeismicSection, e3DWindow }
END_REGISTER_BUILDER_TO_FACTORY(CX3DSectionBuilder)

CX3DSectionBuilder::CX3DSectionBuilder()
{
}

CX3DSectionBuilder::~CX3DSectionBuilder()
{
}

osg::ref_ptr<osg::Group> CX3DSectionBuilder::Build(QUuid objId)
{
    m_pSection = dynamic_cast<CXSeismicSection*>(::GetObjectByID(objId));
	m_pViewInfo = dynamic_cast<CXViewInfoSeismicSection*>(m_pCurWin->GetObjectViewInfo(objId));

	if (!m_pSection || !m_pViewInfo)
		return nullptr;

	m_utm = m_pSection->GetUTM();
	m_type = m_pSection->GetSectionType();

	m_pGeode = new osg::Geode;
	m_pGeode->setUserValue("objID", objId.toString().toStdString());
	m_pGeode->setEventCallback(new CXPickCallback(this));
	m_pGeode->setDataVariance(osg::Object::DYNAMIC);
	m_pGeode->addDrawable(_BuildSection());

	_CheckFractureDisplay();

	return m_pGeode;
}

void CX3DSectionBuilder::UpdateNode(EEventType eType)
{
	if (EDataChanged == eType)
	{
		_UpdateSectionData();

		if (m_pGeom.valid())
		{
			m_pGeom->setVertexArray(_CalcVertex());
			m_pGeom->setStateSet(_BuildTextureState());

			_CheckFractureDisplay();
		}

		if (m_pFrameGeom.valid())
		{
			m_pFrameGeom->setVertexArray(_CalcVertex());
		}
	}
	else if (EInfoChanged == eType)
	{	
		if (m_pGeom.valid())
		{
			m_pGeom->setStateSet(_BuildTextureState());

			_CheckFractureDisplay();
		}
	}
	else if (EColormapChanged)
	{
		_UpdateSectionData();

		if (m_pGeom.valid())
		{
			m_pGeom->setStateSet(_BuildTextureState());
		}
	}
}

osg::Vec3Array * CX3DSectionBuilder::_CalcVertex()
{
	osg::Vec3Array* pVertex = new osg::Vec3Array(4);

	int iInlineFirst = m_utm.GetFirstInline();
	int iInlineLast = m_utm.GetLastInline();
	int iXlineFirst = m_utm.GetFirstCrossline();
	int iXlineLast = m_utm.GetLastCrossline();
	double dSectionNum = m_pSection->GetSectionNumber();

	switch (m_type)
	{
	case eInlineSection:
	{
		osg::Vec2d vecFX, vecLX;
		m_utm.LineToXY(m_iNumSection, iXlineFirst, vecFX.x(), vecFX.y());
		m_utm.LineToXY(m_iNumSection, iXlineLast, vecLX.x(), vecLX.y());
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecFX, m_dStartZ), (*pVertex)[0]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecFX, m_dStopZ), (*pVertex)[1]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecLX, m_dStopZ), (*pVertex)[2]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecLX, m_dStartZ), (*pVertex)[3]);
		break;
	}
	case eCrosslineSection:
	{
		osg::Vec2d vecFI, vecLI;
		m_utm.LineToXY(iInlineFirst, m_iNumSection, vecFI.x(), vecFI.y());
		m_utm.LineToXY(iInlineLast,  m_iNumSection, vecLI.x(), vecLI.y());
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecFI, m_dStartZ), (*pVertex)[0]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecFI, m_dStopZ),  (*pVertex)[1]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecLI, m_dStopZ),  (*pVertex)[2]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecLI, m_dStartZ), (*pVertex)[3]);
		break;
	}
	case eTimeSlice:
	{
		osg::Vec2d vecFIFX, vecFILX, vecLILX, vecLIFX;
		m_utm.LineToXY(m_utm.GetFirstInline(), m_utm.GetFirstCrossline(), vecFIFX.x(), vecFIFX.y());
		m_utm.LineToXY(m_utm.GetFirstInline(), m_utm.GetLastCrossline(), vecFILX.x(), vecFILX.y());
		m_utm.LineToXY(m_utm.GetLastInline(), m_utm.GetLastCrossline(), vecLILX.x(), vecLILX.y());
		m_utm.LineToXY(m_utm.GetLastInline(), m_utm.GetFirstCrossline(), vecLIFX.x(), vecLIFX.y());
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecFIFX, dSectionNum), (*pVertex)[0]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecFILX, dSectionNum), (*pVertex)[1]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecLILX, dSectionNum), (*pVertex)[2]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecLIFX, dSectionNum), (*pVertex)[3]);
		break;
	}
	case eInlineProfile:
	{
		int iLineNum, iStartTrace, iEndTrace;
		double dStartTime, dEndTime;
		m_pSection->GetProfileGeometry(iLineNum, iStartTrace, iEndTrace, dStartTime, dEndTime);

		osg::Vec2d vecST, vecET;
		m_utm.LineToXY(iLineNum, iStartTrace, vecST.x(), vecST.y());
		m_utm.LineToXY(iLineNum, iEndTrace, vecET.x(), vecET.y());
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecST, iStartTrace), (*pVertex)[0]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecST, iEndTrace), (*pVertex)[1]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecET, iEndTrace), (*pVertex)[2]);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(vecET, iStartTrace), (*pVertex)[3]);
		break;
	}
	}

	return pVertex;
}

void CX3DSectionBuilder::_UpdateSectionData()
{
	m_iNumSection = qRound(m_pSection->GetSectionNumber());

	// read seismic data
	QUuid currentVolumeID = m_pViewInfo->GetAttributeObjID();
	if (currentVolumeID == m_pSection->GetObjectID())
	{
		m_pDV = nullptr;
		m_nQtyInline = -1;
		m_nQtyXline = -1;
		m_nQtySampling = -1;
		m_dStartZ = 0.0;
		m_dStopZ = 0.0;
		m_dStepZ = 0.0;
		return;
	}

	m_pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(currentVolumeID));
	Q_ASSERT(m_pDV);
	m_pViewInfoDV = dynamic_cast<CXViewInfoSeismicDV*>(m_pCurWin->GetObjectViewInfo(m_pDV->GetObjectID()));

	if (eTimeSlice == m_type && !m_pDV->HasSliceFile())
	{
		if (QMessageBox::Yes == QMessageBox::question(nullptr, "XStudio", "Viewing a time or depth slice requires a slice file. You do not have the slice file yet. Do you want to create one now?"))
		{
			CXProcessEngine process(m_pDV, ETraceToSlice);
			process.CalculateOnly();
		}
	}

	m_nQtyInline = m_pDV->GetInlineQty();
	m_nQtyXline = m_pDV->GetXlineQty();
	m_nQtySampling = m_pDV->GetSamplingQty();
	m_pDV->GetSamplingRange(m_dStartZ, m_dStopZ, m_dStepZ);
}

float * CX3DSectionBuilder::_ReadVolumeData(int& iS, int& iT)
{
	float *pData;
	bool bResult;

	switch (m_type)
	{
	case eInlineSection:
		iS = m_nQtyXline;
		iT = m_nQtySampling;
		pData = new float[iS * iT];
		bResult = m_pDV->ReadInline(m_iNumSection, pData);
		break;
	case eCrosslineSection:
		iS = m_nQtyInline;
		iT = m_nQtySampling;
		pData = new float[iS * iT];
		bResult = m_pDV->ReadXline(m_iNumSection, pData);
		break;
	case eTimeSlice:
		iS = m_nQtyInline;
		iT = m_nQtyXline;
		pData = new float[iS * iT];
		bResult = m_pDV->ReadSlice(m_pSection->GetSectionNumber(), pData);
		break;
	default:
		Q_ASSERT(!"error section type.");
	}

	if (!bResult)
		return nullptr;

	return pData;
}

void CX3DSectionBuilder::_CheckFractureDisplay()
{
	if (eTimeSlice != m_type)
		return;

	auto pViewInfoTimeSlice = dynamic_cast<CXViewInfoTimeSlice*>(m_pViewInfo);
	if (!pViewInfoTimeSlice || 0 == pViewInfoTimeSlice->GetDisplayMode())
		return;

	m_pGeode->removeDrawable(m_pGeom);
	if (pViewInfoTimeSlice->GetSeismicDisplay())
	{
		m_pGeode->addDrawable(m_pGeom);
	}

	m_pGeode->removeDrawable(m_pFracGeom);
	m_pGeode->addDrawable(_BuildFractureGeometry());
}

osg::TextureRectangle * CX3DSectionBuilder::_BuildProfileTexture()
{
	osg::Image* pImage = osgDB::readImageFile(m_pSection->GetPictureFile().toStdString());
	if (!pImage)
		return nullptr;

	osg::TextureRectangle* pTex = new osg::TextureRectangle;
	pTex->setImage(pImage);
	pTex->setUnRefImageDataAfterApply(true);
	pTex->setResizeNonPowerOfTwoHint(true);
	pTex->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_NEAREST);
	pTex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR_MIPMAP_NEAREST);
	pTex->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP);
	pTex->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP);

	return pTex;
}

osg::StateSet* CX3DSectionBuilder::_BuildTextureState()
{
	int nS = -1, nT = -1;
	float* pData = _ReadVolumeData(nS, nT);
	if (!pData)
		return nullptr;

	double dMin, dMax;
	m_pDV->GetDataRange(dMin, dMax);
	dMin = qMax(dMin, m_pViewInfoDV->GetDisplayDataMin());
	dMax = qMin(dMax, m_pViewInfoDV->GetDisplayDataMax());

	NXShaderUtility::DisplayInfo info{ m_pViewInfoDV->GetColormapName(), dMin, dMax, m_pViewInfoDV->GetBZeroIsInvalid() };

	return NXShaderUtility::BuildSectionTexture(pData, nS, nT, info);
}

bool CX3DSectionBuilder::SetActive(bool bActive)
{
	if (bActive)
	{
		m_pGeode->addDrawable(_BuildSectionFrame());
	}
	else
	{
		m_pGeode->removeDrawable(m_pFrameGeom);
	}

	return true;
}

osg::Geometry * CX3DSectionBuilder::_BuildSection()
{
	_UpdateSectionData();

	m_pGeom = new osg::Geometry;
	m_pGeom->setName("Section");
	m_pGeom->setUseVertexBufferObjects(true);
	m_pGeom->setVertexArray(_CalcVertex());

	osg::Vec2Array* pTexCoord = new osg::Vec2Array(4);
	m_pGeom->setTexCoordArray(0, pTexCoord);

	(*pTexCoord)[0].set(0, 0);
	(*pTexCoord)[1].set(0, 1);
	(*pTexCoord)[2].set(1, 1);
	(*pTexCoord)[3].set(1, 0);

	m_pGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	osg::StateSet* pStateSet = m_pGeom->getOrCreateStateSet();

	if (m_type == eInlineProfile)
	{
		pStateSet->setTextureAttribute(0, new osg::TexEnv(osg::TexEnv::REPLACE));
		osg::TexMat* pTexMat = new osg::TexMat;
		pTexMat->setScaleByTextureRectangleSize(true);
		pStateSet->setTextureAttribute(0, pTexMat, osg::StateAttribute::ON);
		pStateSet->setTextureAttributeAndModes(0, _BuildProfileTexture(), osg::StateAttribute::ON);
	}
	else
	{
		m_pGeom->setStateSet(_BuildTextureState());
	}

	return m_pGeom.get();
}

osg::Geometry * CX3DSectionBuilder::_BuildSectionFrame()
{
	m_pFrameGeom = new osg::Geometry;
	m_pFrameGeom->setName("section_frame");
	m_pFrameGeom->setVertexArray(_CalcVertex());
	m_pFrameGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, 4));

	const QColor& color = m_pViewInfo->Get3DPickedFrameColor();
	osg::Vec3Array* pColors = new osg::Vec3Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF());
	m_pFrameGeom->setColorArray(pColors, osg::Array::BIND_OVERALL);

	osg::StateSet* pStateSet = m_pFrameGeom->getOrCreateStateSet();
	pStateSet->setAttributeAndModes(new osg::LineWidth(m_pViewInfo->Get3DPickedFrameWidth()), osg::StateAttribute::ON);
	pStateSet->setAttributeAndModes(new osg::PolygonOffset(-1.f, 1.f), osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
	pStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	pStateSet->setRenderBinDetails(11, "RenderBin");

	return m_pFrameGeom.get();
}

osg::Geometry * CX3DSectionBuilder::_BuildFractureGeometry()
{
	auto pViewInfo = dynamic_cast<CXViewInfoTimeSlice*>(m_pViewInfo);

	m_pFracGeom = new osg::Geometry;
	m_pFracGeom->setName("fracture_section");

	const QUuid& uuidAzimuth = pViewInfo->GetFracAzimuth();
	const QUuid& uuidDensity = pViewInfo->GetFracDensity();
	int ndX = pViewInfo->GetFracDX();
	int ndY = pViewInfo->GetFracDY();
	float fScale = pViewInfo->GetFracScale();
	float fMinThreshold = pViewInfo->GetFracMinThreshold();
	float fMaxThreshold = pViewInfo->GetFracMaxThreshold();
	int iWidth = pViewInfo->GetFracWidth();
	int iHeight = pViewInfo->GetFracHeight();

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
			vecCenter.z() = m_pSection->GetSectionNumber();

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

			pVertex->push_back(vecHead - osg::Vec3(0, 0, iHeight / 2.f));
			pVertex->push_back(vecHead + osg::Vec3(0, 0, iHeight / 2.f));
			pVertex->push_back(vecEnd  + osg::Vec3(0, 0, iHeight / 2.f));
			pVertex->push_back(vecEnd  - osg::Vec3(0, 0, iHeight / 2.f));
		}
	}
	m_pFracGeom->setVertexArray(pVertex);
	m_pFracGeom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, pVertex->size()));

	const QColor& color = pViewInfo->GetFracColor();
	osg::Vec4Array* pColors = new osg::Vec4Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	m_pFracGeom->setColorArray(pColors, osg::Array::BIND_OVERALL);

	m_pFracGeom->getOrCreateStateSet()->setAttributeAndModes(new osg::LineWidth(iWidth), osg::StateAttribute::ON);

	return m_pFracGeom.get();
}
