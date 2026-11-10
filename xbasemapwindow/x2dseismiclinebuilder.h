#ifndef X2DSECTIONLINEBUILDER_H
#define X2DSECTIONLINEBUILDER_H

/*!
 * @brief	draw 2d seismic section on base map.
 * @author	pezy
 * @date	2015-09-22
 * @see
 */

#include "x3dbuilder.h"
#include <osg/Group>

class CX2DSeismicLine;
class CXViewInfo2DSeismicLine;

class CX2DSeismicLineBuilder : public CX3DBuilderAbstract
{
public:
	CX2DSeismicLineBuilder() : CX3DBuilderAbstract(){}
	~CX2DSeismicLineBuilder(){}

	virtual osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	virtual void UpdateNode(EEventType eType) override;

private:
	void _BuildVertices() const;
	void _BuildPolyLine() const;
	void _BuildOrUpdateNameMark() const;
	void _UpdatePolyLine() const;

	osg::ref_ptr<osg::Geode> m_pGeoNode;
	osg::ref_ptr<osg::Geometry> m_pLineGeom;
	osg::ref_ptr<osg::Switch> m_pMarkSwich;
	osg::ref_ptr<osg::Vec3Array> m_pVertices;

	CX2DSeismicLine* m_pSeismicLine = nullptr;
	CXViewInfo2DSeismicLine* m_pViewInfo = nullptr;
};

#endif // KE2DSECTIONLINEBUILDER_H
