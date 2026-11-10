#ifndef CX3DRANDOMSECTIONBUILDER_H
#define CX3DRANDOMSECTIONBUILDER_H

#include "x3dbuilder.h"
#include <osg/Group>

class CXSeismicRandomSection;

using osg::ref_ptr;
using osg::Group;
using osg::Switch;
using osg::StateSet;

class CX3DRandomSectionBuilder: public CX3DBuilderAbstract
{
public:
	CX3DRandomSectionBuilder() : CX3DBuilderAbstract(){}
	virtual ~CX3DRandomSectionBuilder(){}

	ref_ptr<Group> Build(QUuid objId) override;
	virtual void UpdateNode(EEventType eType) override;

private:
	void _BuildSectionGeom(ref_ptr<Switch> pSwitch);
	void _ResetTexture(float* pData, float fMin, float fMax, int nTrace, int nSampling, float* pTexData);
	ref_ptr<StateSet> _GenerateTextureState(CXSeismicRandomSection* secObj, int nSampling, int nTrace);
};

#endif