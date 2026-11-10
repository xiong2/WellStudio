#ifndef XSHADERUTILITY_H
#define XSHADERUTILITY_H

/*!
 * @brief	utility function for OSG shader.
 * @author	pezy
 * @date	2017-03-20
 * @see
 */

#include <osg/Program>
#include <osg/Uniform>
#include <osg/StateSet>
#include <QString>

namespace NXShaderUtility
{
	struct DisplayInfo
	{
		QString strColormapName;
		double dMin;
		double dMax;
		bool bZeroIsInvalid;
	};

	osg::Program* GetSectionProgram();
	osg::Uniform* GetColorTable(const QString& strColormapName);
	osg::StateSet* BuildSectionTexture(float* pData, int nS, int nT, const DisplayInfo& info);
};

#endif // KESHADERUTILITY_H
