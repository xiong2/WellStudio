#ifndef X3DGLOBALCOORDMAP_H
#define X3DGLOBALCOORDMAP_H

#include "x3dwindow_global.h"
#include <osg/Vec3d>
#include <osg/Vec3>
#include <osg/BoundingBox>
#include <quuid.h>

using osg::Vec3d;
using osg::Vec3;
using osg::BoundingBoxd;
using osg::BoundingBoxf;

/**
* @class CX3DGlobalCoordMap in the file "rl3dglobalcoordmap.h"
* @brief The class provides global translation for 3-D object
* 
* @author Yong Shu 
* @date 6/4/2014
*/

class X3DWINDOW_EXPORT CX3DGlobalCoordMap
{
public:
    CX3DGlobalCoordMap();

	///@brief Tell if it is initailized
	bool IsInitialized();

	///@brief Initialization
	void Init(const QUuid& objID);

	///@brief Map world coordinates to local coordinates
	void MapWorldToLocal(double dXWorld, double dYWorld, double dZWorld, float& fXLocal, float& fYLocal, float& fZLocal);
	void MapWorldToLocal(const Vec3d& vecWorld, Vec3& vecLocal);
	void MapWorldToLocal(const BoundingBoxd& boxWorld, BoundingBoxf& boxLocal);

	///@breif Map local coordinates to world coordinates
	void MapLocalToWorld(float fXLocal, float fYLocal, float fZLocal, double& dXWorld, double& dYWorld, double& dZWorld);
	void MapLocalToWorld(const Vec3& vecLocal,Vec3d& vecWorld);
	void MapLocalToWorld(const BoundingBoxf& boxLocal, BoundingBoxd& boxWorld);

private:

	bool m_bInitialized;

	double m_dXOffset, m_dYOffset, m_dZOffset;
	
};

#endif // RL3DGLOBALCOORDMAP_H
