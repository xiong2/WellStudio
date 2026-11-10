#include "xsubvolumedragercallback.h"
#include <osgManipulator/Command>
#include "x3dwindow.h"

CXSubvolumeDragerCallBack::CXSubvolumeDragerCallBack( osg::MatrixTransform *transform):osgManipulator::DraggerTransformCallback(transform)
{
	m_pCube= NULL;
	m_SubVolumeLocalMatrix.makeIdentity();
	m_IfMoveContinue=true;
}
CXSubvolumeDragerCallBack::~CXSubvolumeDragerCallBack()
{
	m_pCube= NULL;
}

bool CXSubvolumeDragerCallBack::receive(const osgManipulator::MotionCommand &motionCmd)
{
	//osg::Matrix volumeMat;
	switch (motionCmd.getStage())
	{
		case osgManipulator::MotionCommand::START:
		{
			_startMotionMatrix = _transform->getMatrix();
			osg::NodePath nodePathToRoot;
			osgManipulator::computeNodePathToRoot(*_transform,nodePathToRoot);
			_localToWorld = osg::computeLocalToWorld(nodePathToRoot);
			_worldToLocal = osg::Matrix::inverse(_localToWorld);
			return true;
		}
		case osgManipulator::MotionCommand::MOVE:
		{	
			osg::Matrix motionMatrix=motionCmd.getMotionMatrix();
			osg::Matrix localtoworld=motionCmd.getLocalToWorld();
			osg::Matrix worldtolocal=motionCmd.getWorldToLocal();
				
			osg::Matrix localmotionMatrix=_localToWorld*worldtolocal*motionMatrix*localtoworld*_worldToLocal;
			osg::Matrix localObjMatrix=localmotionMatrix*_startMotionMatrix;
			bool m_IfMoveContinue=ComputeVolumeData(m_localVertexArray,localObjMatrix,false);
				
			if(m_IfMoveContinue)
			{
				_transform->setMatrix(localObjMatrix);
				m_SubVolumeLocalMatrix=m_pDrager->getMatrix();
			}
			else
			{		
				m_pDrager->setMatrix(m_SubVolumeLocalMatrix);
			}
			return true;
			
			
		}
		case osgManipulator::MotionCommand::FINISH:
		{
			return true;
		}

		case osgManipulator::MotionCommand::NONE:
		default:
			return false;
	}
	
}
void CXSubvolumeDragerCallBack::SetDragerCube(std::vector<osg::Vec3> dragerVertex,CX3DSubCubeBuilder *pBuilder,osg::MatrixTransform *drager)
{
	m_localVertexArray=dragerVertex;
	m_pBuilder=pBuilder;
	m_pDrager=drager;
}

bool CXSubvolumeDragerCallBack::ComputeVolumeData(std::vector<osg::Vec3f> localVertexArray,osg::Matrix localMotionMatrix,bool ifFinished)
{
	bool ifBeyondSurvery=false;
	if(m_pBuilder&&m_localVertexArray.size()!=0)
	{
		std::vector<osg::Vec3f> localVertexArray;
		{
			for(int i=0;i<m_localVertexArray.size();i++)
			{
				osg::Vec3f localVertex=localMotionMatrix.preMult(m_localVertexArray[i]);
				localVertexArray.push_back(localVertex);
			}
		}
		if(ifFinished)
		{
		     m_localVertexArray =localVertexArray;
		}
		ifBeyondSurvery=m_pBuilder->UpdateDrager(localVertexArray);
	}
	return ifBeyondSurvery;
}