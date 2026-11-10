#ifndef CRL3DSUBCUBEBUILDER_H_H
#define CRL3DSUBCUBEBUILDER_H_H
#include "x3dbuilder.h"

#include <osg/ref_ptr>
#include <osg/Group>
#include "xseismicsubvolume.h"
#include "xseismicdatavolume.h"

class CX3DSubCubeBuilder : public CX3DBuilderAbstract
{
public:
	CX3DSubCubeBuilder();
	~CX3DSubCubeBuilder();

	osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	void UpdateNode(EEventType eType) override;

	
	
	void BuildChairMode(CXSeismicDataVolume *dv, osg::ref_ptr<osg::Geometry> pSectionGeom, osg::ref_ptr<osg::Geometry> pSectionChairGeom, float curSection, float curChairSection, int startInline, int endInline, int startCrossline, int endCrossline, double timestart, double timeend, EXSectionType secType);
	
	bool UpdateDrager(vector<osg::Vec3f> DragerCube);
	
private:
	osg::Matrixd _InitDrager(std::vector<osg::Vec3> dragerVertex);
	CXSeismicDataVolume* _GetDV();
	osg::ref_ptr<osg::Switch> _BuildSubCube(CXSeismicSubVolume *pSubVolume);
	osg::ref_ptr<osg::Geode>  _BuildSubVolume(int inlineStart, int inlineEnd, int xlineStart, int xlineEnd, double timeStart, double timeEnd, float zScale = 1.0f);
	osg::ref_ptr<osg::Geometry> _BuildSectionGeom(double currentSection, int inLineStart, int inLineEnd, int xLineStart, int xLineEnd, double timeStart, double timeEnd, EXSectionType curSecType);
	std::vector<osg::Vec3> _BuildDragerCube(CXSeismicDataVolume *dv, int inLineStart, int inLineEnd, int xLineStart, int xLineEnd, double timeStart, double timeEnd);

	osg::ref_ptr<osg::StateSet> _GenerateTextureState(int currentSection, int inLineStart, int inLineEnd, int xLineStart, int xLineEnd, double timeStart, double timeEnd, EXSectionType curSecType, bool ifChairMode = false);
	void _GenerateTexture(float *sectionData, float dataMin, float dataMax, int traceNum, int sampleNum, float *texData);

private:
	CXSeismicSubVolume *m_pSubVolume = nullptr;
	
	std::vector<osg::Vec3f> m_DragerCube;

	osg::ref_ptr<osg::Geometry> m_pGeoInlineSectionStart = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeoInlineSectionEnd = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeoXlineSectionStart = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeoXlineSectionEnd = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeoTimeSliceStart = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeoTimeSliceEnd = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeoInlineSectionChairStart = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeoInlineSectionChairEnd = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeoXlineSectionChairStart = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeoXlineSectionChairEnd = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeoTimeSliceChairStart = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeoTimeSliceChairEnd = nullptr;
	osg::ref_ptr<osg::Geode> m_pChairGeode = nullptr;
	osg::ref_ptr<osg::Geode> m_pCubeGeode = nullptr;
	osg::ref_ptr<osg::Switch> m_pChairSwitch = nullptr;

	bool m_bChairMode = false; //normal or chair
};

#endif