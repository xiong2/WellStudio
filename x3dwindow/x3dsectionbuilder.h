#ifndef X3DSECTIONBUILDER_H_H
#define X3DSECTIONBUILDER_H_H

#include "x3dpickablebuilder.h"
#include "xseismicutmtool.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osg/TextureRectangle>
#include <osg/Texture2D>
#include <osg/Program>
#include <osg/Uniform>

class CXViewInfoSeismicSection;
class CXSeismicSection;
class CXSeismicDataVolume;
class CXViewInfoSeismicDV;

class CX3DSectionBuilder : public CX3DPickableBuilderAbstract
{
public:
    CX3DSectionBuilder();
    virtual ~CX3DSectionBuilder();

    virtual osg::ref_ptr<osg::Group> Build(QUuid objId) override;
    virtual void UpdateNode(EEventType eType) override;
	// Inherited via CX3DPickableBuilderAbstract
	virtual bool SetActive(bool bActive) override;

private:
	osg::Vec3Array* _CalcVertex();
	void _UpdateSectionData();
	float* _ReadVolumeData(int& iS, int& iT);
	void _CheckFractureDisplay();

	osg::Geometry* _BuildSection();
	osg::Geometry* _BuildSectionFrame();
	osg::Geometry* _BuildFractureGeometry();
	osg::TextureRectangle* _BuildProfileTexture();
	osg::StateSet* _BuildTextureState();
    
private:
    CXSeismicSection *m_pSection = nullptr;
	CXViewInfoSeismicSection* m_pViewInfo = nullptr;
	CXViewInfoSeismicDV* m_pViewInfoDV = nullptr;
	CXSeismicUTMTool m_utm;
	EXSectionType m_type;
	
	int m_iNumSection = 0;
	CXSeismicDataVolume* m_pDV = nullptr;
	int m_nQtyInline = -1;
	int m_nQtyXline = -1;
	int m_nQtySampling = -1;
	double m_dStartZ = 0.0;
	double m_dStopZ = 0.0;
	double m_dStepZ = 0.0;

	osg::ref_ptr<osg::Geode> m_pGeode = nullptr;
	osg::ref_ptr<osg::Geometry> m_pGeom = nullptr;
	osg::ref_ptr<osg::Geometry> m_pFrameGeom = nullptr;
	osg::ref_ptr<osg::Geometry> m_pFracGeom = nullptr;
	osg::ref_ptr<osg::Uniform> m_pUniformColorTable = nullptr;
};
#endif