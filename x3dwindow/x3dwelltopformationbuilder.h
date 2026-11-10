#ifndef X3DWELLTOPSBUILDER_H
#define X3DWELLTOPSBUILDER_H

#include "x3dbuilder.h"
#include "xviewinfo3dwelltopformation.h"
#include <osg/LOD>

///@Brief	the builder for 3D well top formation.
///@Author	PEZY
///@Date	2014-06-04
///@Update	2014-08-29
///@See		CX3DBuilderAbstract

class CX3DWindow;
class CXWellTopFormation;

class CX3DWellTopFormationBuilder : public CX3DBuilderAbstract
{
public:
	CX3DWellTopFormationBuilder();
	virtual osg::ref_ptr<osg::Group> Build(QUuid objId);
	virtual void UpdateNode(EEventType eType);

private:
	CX3DWindow* m_pOSGWindow = nullptr;	///< Brief Pointer of 3d window
	CXWellTopFormation *m_pWellTopFormation = nullptr; ///< Brief Well top data
    CXViewInfo3DWellTopFormation *m_pViewInfo = nullptr; ///< Brief Well top view info

	osg::ref_ptr<osg::LOD> m_pLOD; ///< Brief LOD
	float m_fZScale; ///< Brief Current ZScale value

	CXViewInfo3DWellTopFormation::EDisplayMode m_curMode;
	osg::ref_ptr<osg::Vec3Array> m_pVecPosition;
};

#endif // RL3DWELLTOPSBUILDER_H
