#pragma warning( push ,0)  
#include "x3dglobalcoordmap.h"
#include "xobject.h"
#include "xglobal.h"
#pragma warning( pop ) 


CX3DGlobalCoordMap::CX3DGlobalCoordMap()
{
	m_bInitialized = false;
}

bool CX3DGlobalCoordMap::IsInitialized()
{
	return m_bInitialized;
}

void CX3DGlobalCoordMap::Init(const QUuid& objID)
{
	CXObject* pObj = ::GetObjectByID(objID);
	if (!pObj)
		return;

	double xmin, xmax, ymin, ymax, zmin, zmax;
	pObj->GetDimension(xmin, xmax, ymin, ymax, zmin, zmax);

	if (xmin == ::g_dInvalidData ||
		ymin == ::g_dInvalidData ||
		zmin == ::g_dInvalidData)
		return;

	m_dXOffset = (xmin + xmax)/2.;
	m_dYOffset = (ymin + ymax)/2.;
	m_dZOffset = (zmin + zmax)/2.;

	m_dZOffset *= ::g_f3DZFactor;

	m_dZOffset = 0;

	m_bInitialized = true;
	return;
}

void CX3DGlobalCoordMap::MapWorldToLocal(double dXWorld, double dYWorld, double dZWorld, float& fXLocal, float& fYLocal, float& fZLocal)
{
	fXLocal = static_cast<float>(dXWorld - m_dXOffset);
	fYLocal = static_cast<float>(dYWorld - m_dYOffset);
	fZLocal = static_cast<float>(dZWorld*g_f3DZFactor - m_dZOffset);
}

void CX3DGlobalCoordMap::MapWorldToLocal(const Vec3d& vecWorld, Vec3& vecLocal)
{
	vecLocal[0] =  static_cast<float>(vecWorld[0] - m_dXOffset);
	vecLocal[1] =  static_cast<float>(vecWorld[1] - m_dYOffset);
	vecLocal[2] =  static_cast<float>(vecWorld[2]*g_f3DZFactor - m_dZOffset);
}

void CX3DGlobalCoordMap::MapWorldToLocal(const BoundingBoxd& boxWorld, BoundingBoxf& boxLocal)
{
	// MapWorldToLocal would change the Z direction. so, origin zMin is zMax, and vice versa.
	MapWorldToLocal(boxWorld.xMin(), boxWorld.yMin(), boxWorld.zMin(), boxLocal.xMin(), boxLocal.yMin(), boxLocal.zMax());
	MapWorldToLocal(boxWorld.xMax(), boxWorld.yMax(), boxWorld.zMax(), boxLocal.xMax(), boxLocal.yMax(), boxLocal.zMin());
}

void CX3DGlobalCoordMap::MapLocalToWorld(float fXLocal, float fYLocal, float fZLocal, double& dXWorld, double& dYWorld, double& dZWorld)
{
	dXWorld = fXLocal + m_dXOffset;
	dYWorld = fYLocal + m_dYOffset;
	dZWorld = (fZLocal + m_dZOffset)*g_f3DZFactor;

}

void CX3DGlobalCoordMap::MapLocalToWorld(const Vec3& vecLocal,Vec3d& vecWorld)
{
	vecWorld[0] = vecLocal[0] + m_dXOffset;
	vecWorld[1] = vecLocal[1] + m_dYOffset;
	vecWorld[2] = (vecLocal[2] + m_dZOffset)*g_f3DZFactor;
}

void CX3DGlobalCoordMap::MapLocalToWorld(const BoundingBoxf& boxLocal, BoundingBoxd& boxWorld)
{
	// MapWorldToLocal would change the Z direction. so, origin zMin is zMax, and vice versa.
	MapLocalToWorld(boxLocal.xMin(), boxLocal.yMin(), boxLocal.zMin(), boxWorld.xMin(), boxWorld.yMin(), boxWorld.zMax());
	MapLocalToWorld(boxLocal.xMax(), boxLocal.yMax(), boxLocal.zMax(), boxWorld.xMax(), boxWorld.yMax(), boxWorld.zMin());
}
