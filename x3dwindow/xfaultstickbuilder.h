#ifndef XFAULTSTICKBUILDER_H
#define XFAULTSTICKBUILDER_H

#include "x3dbuilder.h"
#include <vector>

class CXFaultSticks;
class CXViewInfo3DFaultSticks;

/**
* @class CXFaultStickBuilder in the file "rlfaultstickbuilder.h"
* @brief The class is a node builder for fault sticks
* 
* @author Yong Shu 
* @date 6/6/2014
* @see 
*/
class CXFaultStickBuilder : public CX3DBuilderAbstract
{
public:
	CXFaultStickBuilder() {}
	~CXFaultStickBuilder() {}

	///@brief Reimplement the function
	virtual osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	virtual void UpdateNode(EEventType eType) override;

private:
	void _BuildVertices();
	void _BuildPoints();
	void _BuildLines();
	void _BuildPlane();

	void _UpdatePoint();
	void _UpdateLine();
	void _UpdataPlane();

	void _BuildNode();

private:
	osg::ref_ptr<osg::Geode> m_pGeoNode;

	osg::ref_ptr<osg::Geometry> m_pPlane;
	osg::ref_ptr<osg::Geometry> m_pLine;
	osg::ref_ptr<osg::Geometry> m_pPoint;

	osg::ref_ptr<osg::Vec3Array> m_pVertices;
	
private:
	CXFaultSticks* m_pSticks = nullptr;
	CXViewInfo3DFaultSticks* m_pViewInfo = nullptr;
	std::vector<unsigned int> m_vecPointNum;
};

#endif // RLFAULTSTICKBUILDER_H
