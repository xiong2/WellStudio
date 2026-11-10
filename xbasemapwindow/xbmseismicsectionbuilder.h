#ifndef XBMSEISMICSECTIONBUILDER_H
#define XBMSEISMICSECTIONBUILDER_H

/*!
 *	@brief	display of seismic section line or plane
 *	@author	pezy
 *	@date	2016-06-30
 *	@see
 */

#include "x3dpickablebuilder.h"
#include "xseismicutmtool.h"
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/Program>
#include <osg/Uniform>

class CXViewInfoSeismicSection;
class CXSeismicSection;
class CXViewInfoSeismicDV;

class CXBMSeismicSectionBuilder : public CX3DPickableBuilderAbstract
{
public:
	CXBMSeismicSectionBuilder();
	~CXBMSeismicSectionBuilder();

	osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	void UpdateNode(EEventType eType) override;
	bool SetActive(bool bActive) override;

	void UpdateSeismicLinePosition(int iInline, int iXline);
	int GetCurrentTraceNumber();

private:
	void _UpdateSectionData();
	void _UpdateDisplayRange(bool bDisplaySection);
	void _UpdateLineViewInfo(bool bPicked);
	void _CheckFractureDisplay();

	osg::Geometry* _BuildSectionLine();
	osg::Geometry* _BuildSectionSlice();
	osg::Geometry* _BuildSectionSliceFrame();
	osg::Geometry* _BuildFractureGeometry();
	osg::Texture2D* _BuildSectionSliceTexture();
	osg::Program* _BuildSectionSliceProgram();
	osg::Uniform* _BuildSectionSliceColorTable();

	osg::Vec3Array* _CalcSectionLineVertex();
	osg::Vec3Array* _CalcSectionSliceVertex();

	int _GetFirstInline();
	int _GetLastInline();
	int _GetFirstXline();
	int _GetLastXline();

private:
	CXSeismicSection* m_pSection = nullptr;
	CXViewInfoSeismicSection* m_pViewInfo = nullptr;
	CXViewInfoSeismicDV* m_pViewInfoDV = nullptr;

	osg::ref_ptr<osg::Geode> m_pGeode = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeometry = nullptr;
	osg::ref_ptr<osg::Geometry> m_pFrameGeometry = nullptr;
	osg::ref_ptr<osg::Geometry> m_pFracGeom = nullptr;
	osg::ref_ptr<osg::Vec3Array> m_pLineVertex = nullptr;
	osg::ref_ptr<osg::Uniform> m_pUniformColorTable = nullptr;

	CXSeismicUTMTool m_utm;
	EXSectionType m_type;
	int m_nTrace = -1;
	int m_iSTrace = -1;
	int m_iETrace = -1;
};

#endif // KEBMSEISMICSECTIONBUILDER_H
