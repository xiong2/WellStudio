#include "x3drandomsectionbuilder.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Image>
#include <osg/Texture2D>
#include <osg/LineWidth>
#include <osg/PolygonOffset>
#include <osgDB/FileUtils>

#include "x3dglobalcoordmap.h"
#include "xcolormap.h"
#include "xviewinfoobject.h"
#include "xdbio.h"
#include "x3dbuilderfactory.h"
#include "xseismicdatavolume.h"
#include "xseismicrandomsection.h"
#include "xglobal.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DRandomSectionBuilder)
{EXRandomSection,e3DWindow}
END_REGISTER_BUILDER_TO_FACTORY(CX3DRandomSectionBuilder)

void CX3DRandomSectionBuilder::UpdateNode(EEventType eType)
{
	if (eType == EDataChanged || (eType == EInfoChanged) || eType == EColormapChanged)
	{
		osg::ref_ptr<osg::Switch> pSwitch = m_pBuilderNode->getChild(0)->asSwitch();
		if (!pSwitch) return;

		auto valueList = pSwitch->getValueList();
		pSwitch->removeChildren(0, pSwitch->getNumChildren());
		_BuildSectionGeom(pSwitch);
		pSwitch->setValueList(valueList);
	}
}

ref_ptr<Group> CX3DRandomSectionBuilder::Build(QUuid objId)
{
	if (!m_pBuilderNode) m_pBuilderNode = new osg::Group();

	SetObjectID(objId);

	osg::ref_ptr<osg::Switch> geodeSectionSwitch = new osg::Switch();
	_BuildSectionGeom(geodeSectionSwitch);
	m_pBuilderNode->addChild(geodeSectionSwitch.get());
	return m_pBuilderNode;
}

void CX3DRandomSectionBuilder::_BuildSectionGeom(osg::ref_ptr<osg::Switch> geodeSectionSwitch)
{
	CXSeismicRandomSection* pRandomSection = dynamic_cast<CXSeismicRandomSection*>(::GetObjectByID(m_objID));
	if (!pRandomSection)
		return;
	
	auto pDv = dynamic_cast<CXSeismicDataVolume*>(::GetAttributeFromGeometry(pRandomSection, m_pCurWin));
	Q_ASSERT(pDv);

	int alltraceNum = pRandomSection->GetTraceNum();
	int sampleNum = pDv->GetSamplingQty();
	double sampleStart, sampleEnd, sampleRate;
	pDv->GetSamplingRange(sampleStart, sampleEnd, sampleRate);
	vector<double> xValueVec, yValueVec;
	pRandomSection->GetXYofTuringPoint(xValueVec, yValueVec);

	osg::ref_ptr<osg::Geode> polygonGeode = new osg::Geode;
	osg::ref_ptr<osg::Geode> polygonGeodePicked = new osg::Geode;

	for (int i = 0; i < xValueVec.size() - 1; i++)
	{
		osg::Vec3f worldCoord, localCood;
		osg::ref_ptr<osg::Vec4Array> polyColor = new osg::Vec4Array;
		polyColor->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));
		osg::ref_ptr<osg::Vec3Array> vertexArray = new osg::Vec3Array;
		osg::ref_ptr<osg::Vec3Array> vertexArrayForSection = new osg::Vec3Array;
		osg::ref_ptr<osg::Vec2Array> texCordArray = new osg::Vec2Array;
		worldCoord.set(xValueVec[i], yValueVec[i], sampleStart);
		m_pCoordMap->MapWorldToLocal(worldCoord, localCood);
		vertexArray->push_back(localCood);
		vertexArrayForSection->push_back(localCood);
		int curIndex = pRandomSection->GetTPTraceIndex(i);
		texCordArray->push_back(osg::Vec2f((float)curIndex / (alltraceNum - 1), 0));

		worldCoord.set(xValueVec[i + 1], yValueVec[i + 1], sampleStart);
		m_pCoordMap->MapWorldToLocal(worldCoord, localCood);
		vertexArray->push_back(localCood);
		vertexArrayForSection->push_back(localCood);
		curIndex = pRandomSection->GetTPTraceIndex(i + 1);
		texCordArray->push_back(osg::Vec2f((float)curIndex / (alltraceNum - 1), 0));

		worldCoord.set(xValueVec[i + 1], yValueVec[i + 1], sampleEnd);
		m_pCoordMap->MapWorldToLocal(worldCoord, localCood);
		vertexArray->push_back(localCood);
		vertexArrayForSection->push_back(localCood);
		curIndex = pRandomSection->GetTPTraceIndex(i + 1);
		texCordArray->push_back(osg::Vec2f((float)curIndex / (alltraceNum - 1), 1));

		worldCoord.set(xValueVec[i], yValueVec[i], sampleEnd);
		m_pCoordMap->MapWorldToLocal(worldCoord, localCood);
		vertexArray->push_back(localCood);
		vertexArrayForSection->push_back(localCood);
		curIndex = pRandomSection->GetTPTraceIndex(i);
		texCordArray->push_back(osg::Vec2f((float)curIndex / (alltraceNum - 1), 1));

		osg::ref_ptr<osg::Geometry> polygonGeom = new osg::Geometry;
		polygonGeom->setVertexArray(vertexArray.get());
		polygonGeom->setTexCoordArray(0, texCordArray, osg::Array::BIND_PER_VERTEX);
		polygonGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertexArray->size()));
		polygonGeode->addDrawable(polygonGeom.get());

		osg::ref_ptr<osg::Geometry> polygonGeomPicked = new osg::Geometry;
		polygonGeomPicked->setVertexArray(vertexArrayForSection.get());
		polygonGeomPicked->setColorArray(polyColor.get(), osg::Array::BIND_OVERALL);
		polygonGeomPicked->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, vertexArrayForSection->size()));
		polygonGeodePicked->addDrawable(polygonGeomPicked.get());

		polygonGeode->setUserValue("objID", m_objID.toString().toStdString());
	}
	osg::ref_ptr<osg::StateSet> pSectionStatSet = new osg::StateSet;
	pSectionStatSet = _GenerateTextureState(pRandomSection, sampleNum, alltraceNum);

	if (pSectionStatSet != NULL)
	{
		polygonGeode->setStateSet(pSectionStatSet);
	}

	osg::StateSet* pPickSectionStatSet = polygonGeodePicked->getOrCreateStateSet();
	osg::PolygonOffset* poffset = new osg::PolygonOffset;
	poffset->setFactor(-1.0f);
	poffset->setUnits(1.0f);
	osg::LineWidth* pLineWidth = new osg::LineWidth;
	pLineWidth->setWidth(5);
	pPickSectionStatSet->setAttribute(poffset, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);
	pPickSectionStatSet->setAttribute(pLineWidth, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);

	geodeSectionSwitch->addChild(polygonGeode.get());
	geodeSectionSwitch->addChild(polygonGeodePicked.get(), false);
}

void CX3DRandomSectionBuilder::_ResetTexture(float* pData, float fMin, float fMax, int nTrace, int nSampling, float* pTexData)
{
	for (auto iTrace = 0; iTrace < nTrace; ++iTrace)
		for (auto iSampling = 0; iSampling < nSampling; ++iSampling)
			pTexData[iSampling * nTrace + iTrace] = (pData[iTrace * nSampling + iSampling] - fMin) / (fMax - fMin);
}

ref_ptr<StateSet> CX3DRandomSectionBuilder::_GenerateTextureState(CXSeismicRandomSection* pSection, int nSampling, int nTrace)
{
	CXSeismicRandomSection* pRandomSection = dynamic_cast<CXSeismicRandomSection*>(::GetObjectByID(m_objID));
	if (!pRandomSection)
		return nullptr;

	auto pDv = dynamic_cast<CXSeismicDataVolume*>(::GetAttributeFromGeometry(pRandomSection, m_pCurWin));
	Q_ASSERT(pDv);
	
    CXViewInfoObject* pViewInfo = m_pCurWin->GetObjectViewInfo(pDv->GetObjectID());
    float fMin = pViewInfo->GetDisplayDataMin();
    float fMax = pViewInfo->GetDisplayDataMax();

	float* pSectionData = new float[nTrace * nSampling];

	osg::ref_ptr<osg::StateSet> pStatSet = new osg::StateSet;
	bool ifSuccess = pDv->ReadRandomSection(pSection, pSectionData);
	if (!ifSuccess)
	{
		delete [] pSectionData;
		pSectionData = NULL;
		return pStatSet.get();
	}

	osg::ref_ptr<osg::Image> texImage = new osg::Image;
	texImage->allocateImage(nTrace, nSampling, 1,GL_LUMINANCE,GL_FLOAT);
	texImage->setInternalTextureFormat(GL_RGBA32F_ARB);
	float* texData = (float*)(texImage->data());
	_ResetTexture(pSectionData, fMin, fMax, nTrace, nSampling, texData);

	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
	tex->setImage(texImage);
	tex->setUnRefImageDataAfterApply(true);
	tex->setResizeNonPowerOfTwoHint(false);
	tex->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	tex->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	tex->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
	tex->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);

	pStatSet->setTextureAttributeAndModes(0, tex, osg::StateAttribute::ON);

	CXViewInfoObject* pObjViewInfo = m_pCurWin->GetObjectViewInfo(pRandomSection->GetObjectID());
	if (pObjViewInfo == NULL) return pStatSet.get();
	CXColormap* pColormap = CXColormap::GetColormap(pObjViewInfo->GetColormapName());
	if (pColormap == NULL) return pStatSet.get();
	osg::Vec4 colormap[256];
	for (int i = 0; i < 256; i++)
	{
		QColor colorValue = pColormap->GetColorAt((unsigned char)i);
		float red = colorValue.redF();
		float green = colorValue.greenF();
		float blue = colorValue.blueF();
		float alpha = colorValue.alphaF();
		colormap[i] = (osg::Vec4(red, green, blue, alpha));
	}
	osg::Program* program = new osg::Program;

	std::string strVertex = QString(CXDBIO::GetShaderFilePath() + "section.vert").toStdString();
	std::string strFrag = QString(CXDBIO::GetShaderFilePath() + "section.frag").toStdString();

	program->addShader(osg::Shader::readShaderFile(osg::Shader::VERTEX, strVertex));
	program->addShader(osg::Shader::readShaderFile(osg::Shader::FRAGMENT, strFrag));
	pStatSet->setAttribute(program, osg::StateAttribute::ON);
	pStatSet->addUniform(new osg::Uniform("sectionTex", 0));
	osg::Uniform* ColorMap = new osg::Uniform(osg::Uniform::FLOAT_VEC4, "colorTable", 256);
	for (int i = 0; i < 256; i++)
	{
		ColorMap->setElement(i, colormap[i]);
	}
	pStatSet->addUniform(ColorMap);

	delete [] pSectionData;
	pSectionData = NULL;
	return pStatSet.get();
}