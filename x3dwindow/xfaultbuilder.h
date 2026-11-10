#ifndef XGMFAULTBUILDER_H
#define XGMFAULTBUILDER_H

#include "x3dwindow_global.h"
#include "x3dbuilder.h"
#include <vector>

using std::vector;

class CXGMFault;
class CXViewInfo3DFaultSticks* m_pViewInfo;

/**
* @class CXGMFaultBuilder in the file "rfgmfaultbuilder.h"
* @brief The class is a node builder for modeled fault sticks
* 
* @author Yong Shu 
* @date 2/15/2015
* @see 
*/
class X3DWINDOW_EXPORT CXGMFaultBuilder : public CX3DBuilderAbstract
{
public:
	CXGMFaultBuilder();
	~CXGMFaultBuilder();
	
	///@brief Reimplement the function
	virtual osg::ref_ptr<osg::Group> Build(QUuid objId);

	virtual void UpdateNode(EEventType eType);

private:
	void _BuildVertices();
	void _BuildPoints();
	void _BuildLines();
	void _BuildPlane();

	void _UpdatePoint();
	void _UpdateLine();
	void _UpdataPlane();


private:
	osg::ref_ptr<osg::Geode> m_pGeoNode;

	osg::ref_ptr<osg::Geometry> m_pPlane;
	osg::ref_ptr<osg::Geometry> m_pLine;
	osg::ref_ptr<osg::Geometry> m_pPoint;

	osg::ref_ptr<osg::Vec3Array> m_pVertices;

private:
	CXGMFault* m_pFault;

	CXViewInfo3DFaultSticks* m_pViewInfo;

	vector<vector<int> > m_vecPillarVerticeIndex;

	vector<int> m_vecCount;	




	
};

#endif // RFGMFAULTBUILDER_H
