#include "xshaderutility.h"

#include <algorithm>
#include <osg/Shader>
#include <osg/Image>
#include <osg/Texture2D>
#include <QImage>

#include "xdbio.h"
#include "xcolormap.h"
#include "xglobal.h"

osg::Program * NXShaderUtility::GetSectionProgram()
{
	osg::Program* pProgram = new osg::Program;

	std::string strVert = CXDBIO::GetShaderFilePath().toStdString() + "section.vert";
	std::string strFrag = CXDBIO::GetShaderFilePath().toStdString() + "section.frag";

	pProgram->addShader(osg::Shader::readShaderFile(osg::Shader::VERTEX, strVert));
	pProgram->addShader(osg::Shader::readShaderFile(osg::Shader::FRAGMENT, strFrag));

	return pProgram;
}

osg::Uniform* NXShaderUtility::GetColorTable(const QString& strColormapName)
{
	CXColormap* pColormap = CXColormap::GetColormap(strColormapName);
	Q_ASSERT(pColormap);

	osg::Uniform* pUniformColorTable = new osg::Uniform(osg::Uniform::FLOAT_VEC4, "colorTable", 256);

	for (int i = 0; i < 255; ++i)
	{
		int index = qRound(i / 254.0 * (pColormap->GetColorNum() - 1));
		const QColor& color = pColormap->ColorAt(index);
		pUniformColorTable->setElement(i, osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	}

	const QColor& invalidColor = pColormap->GetInvalidColor();
	pUniformColorTable->setElement(255, osg::Vec4(invalidColor.redF(), invalidColor.greenF(), invalidColor.blueF(), invalidColor.alphaF()));

	return pUniformColorTable;
}

osg::StateSet * NXShaderUtility::BuildSectionTexture(float * pData, int nS, int nT, const DisplayInfo& info)
{
	CXColormap* pColormap = CXColormap::GetColormap(info.strColormapName);
	Q_ASSERT(pColormap);

	auto _GetImageData = [&]()
	{
		auto pImageData = new unsigned int[nS * nT];
		memset(pImageData, 0, nS * nT);

		if (qFuzzyCompare(info.dMin, info.dMax))
		{
			std::fill_n(pImageData, nS * nT, QColor(0, 0, 0).rgba());
			return pImageData;
		}

		int n = pColormap->GetColorNum();

		for (int s = 0; s < nS; ++s)
		{
			for (int t = 0; t < nT; ++t)
			{
				double d = pData[s * nT + t];
				if (qFuzzyCompare(d, ::g_dInvalidData) || (info.bZeroIsInvalid && d == 0.0))
				{
					pImageData[t * nS + s] = pColormap->GetInvalidColor().rgba();
				}
				else
				{
					int index = qBound(0, static_cast<int>((d - info.dMin) / (info.dMax - info.dMin) * n), n);
					pImageData[t * nS + s] = QColor(index, index, index).rgba();
				}
			}
		}

		return pImageData;
	};

	osg::Image* pImage = new osg::Image;
	pImage->setImage(nS, nT, 1, GL_RGBA32F_ARB, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)_GetImageData(), osg::Image::NO_DELETE);
	
	/*QImage image((unsigned char*)_GetImageData(), nS, nT, QImage::Format_RGB32);
	image = image.mirrored(true, true);
	image.save("texture", "png");*/

	osg::Texture2D* pTexture = new osg::Texture2D;
	pTexture->setImage(pImage);
	pTexture->setUnRefImageDataAfterApply(true);
	pTexture->setResizeNonPowerOfTwoHint(false);
	pTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	pTexture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	pTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
	pTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);

	osg::StateSet* pStateSet = new osg::StateSet;
	pStateSet->setTextureAttributeAndModes(0, pTexture, osg::StateAttribute::ON);
	pStateSet->setAttribute(NXShaderUtility::GetSectionProgram(), osg::StateAttribute::ON);
	pStateSet->addUniform(new osg::Uniform("sectionTex", 0));
	pStateSet->addUniform(GetColorTable(info.strColormapName));

	return pStateSet;
}
