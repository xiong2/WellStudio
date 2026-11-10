#ifndef XCOORDUPDATECALLBACK_H
#define XCOORDUPDATECALLBACK_H

#include <osg/NodeCallback>
#include <osg/Camera>

///@brief	show or hide the coordinate grid.
///@author	PEZY
///@date	2014-07-21
///@see	

class CXCoordUpdateCallback : public osg::NodeCallback
{
public:
	CXCoordUpdateCallback(osg::Camera* camera):m_pMainCamera(camera){}

	void operator()(osg::Node* node, osg::NodeVisitor* nv);
	

private:
	osg::observer_ptr<osg::Camera> m_pMainCamera;
};

#endif // RLCOORDUPDATECALLBACK_H
