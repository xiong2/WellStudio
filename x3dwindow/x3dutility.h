#ifndef X3DUTILITY_H
#define X3DUTILITY_H

#include "x3dwindow_global.h"
#include <osg/Vec3>
#include <osg/Array>
#include <osg/Geometry>
#include <osg/BoundingBox>
#include <QColor>

namespace osg { class Camera; };
namespace NX3DUtility
{
	osg::Vec3 X3DWINDOW_EXPORT MapToLocal(osg::Camera *pCamera, const osg::Vec3& vecScene);
	osg::Vec3 X3DWINDOW_EXPORT MapToScene(osg::Camera *pCamera, const osg::Vec3& vecLocal);
	float X3DWINDOW_EXPORT DistPerMM(osg::Camera *pCamera);
	///@brief	(fX, fY) is the new point of polygon, pVertex is polygon's old vertex.
	bool X3DWINDOW_EXPORT IsPolygonSelfIntersection(osg::Vec3Array* pVertex, float fX, float fY);
	///@brief	index is the polygon's vertex index, when it's position changed, check it whether intersection with itself.
	bool X3DWINDOW_EXPORT IsPolygonSelfIntersection(osg::Vec3Array* pVertex, int index);

	QString X3DWINDOW_EXPORT OutputVec(const osg::Vec3& vec);
	void X3DWINDOW_EXPORT SetSingleColor(osg::Geometry* pGeom, const QColor& color);
	osg::Vec4 X3DWINDOW_EXPORT Color2Vec(const QColor& color);
	osg::BoundingBox X3DWINDOW_EXPORT ExpandBox(const osg::BoundingBox& box);
};

#endif // KE3DUTILITY_H
