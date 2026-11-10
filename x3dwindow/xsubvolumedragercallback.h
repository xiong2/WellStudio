#ifndef CRLSUBVOLUMEDRAGERCALLBACK_H_H
#define CRLSUBVOLUMEDRAGERCALLBACK_H_H

#include <osgManipulator/TabBoxDragger>
#include <osg/Geometry>
#include "x3dsubcubebuilder.h"
class CXSubvolumeDragerCallBack:public osgManipulator::DraggerTransformCallback
{
public:
	CXSubvolumeDragerCallBack(osg::MatrixTransform *transform);
	~CXSubvolumeDragerCallBack();

	virtual bool  receive (const osgManipulator::MotionCommand  &motionCmd);
	bool ComputeVolumeData(std::vector<osg::Vec3f> localVertexArray,osg::Matrix localMotionMatrix,bool ifFinished);
	void SetDragerCube(std::vector<osg::Vec3> dragerVertex,CX3DSubCubeBuilder *pBuilder,osg::MatrixTransform *drager);
	
private:
	bool m_IfMoveContinue;
	bool m_IfMoveDrager;
	osg::Geometry *m_pCube;
	CX3DSubCubeBuilder * m_pBuilder;
	osg::MatrixTransform *m_pDrager;

	osg::Matrix m_SubVolumeLocalMatrix;
	std::vector<osg::Vec3> m_localVertexArray;


};
#endif