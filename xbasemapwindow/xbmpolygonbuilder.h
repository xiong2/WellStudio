#ifndef XBMPOLYGONBUILDER_H
#define XBMPOLYGONBUILDER_H

/*!
 *	@brief	display of 2D Polygon
 *	@author	pezy
 *	@date	2016-08-19
 *	@see
 */

#include "x3dpickablebuilder.h"
#include <osg/Geode>
#include <osg/Geometry>

class CX2DPolygon;
class CXViewInfo2DPolygon;

class CXBMPolygonBuilder : public CX3DPickableBuilderAbstract
{
public:
	CXBMPolygonBuilder();
	~CXBMPolygonBuilder();

	osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	void UpdateNode(EEventType eType) override;
	bool SetActive(bool bActive) override;

	osg::ref_ptr<osg::Vec3Array> GetVertex() const override { return m_pVertex; }

private:
	osg::Geometry* _BuildPolygon();
	osg::Vec3Array* _BuildPolygonVertex();
	void _UpdateViewInfo(bool bPicked);

private:
	CX2DPolygon* m_pPolygon;
	CXViewInfo2DPolygon* m_pViewInfo;

	osg::ref_ptr<osg::Geode> m_pGeode;
	osg::ref_ptr<osg::Geometry> m_pGeom;
	osg::ref_ptr<osg::Vec3Array> m_pVertex;
};

#endif // KEBMPOLYGONBUILDER_H
