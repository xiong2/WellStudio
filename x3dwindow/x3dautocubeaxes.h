#ifndef XAUTOCUBEAXES_H
#define XAUTOCUBEAXES_H

/*!
 *	@class	CX3DAutoCubeAxes in the file "keautocubeaxes.h"
 *	@brief	Build 3D coordinate axes with a cube on the 3D window.
 *	@note	pos specifies the cube corner as a number between 0 and 7. 
 *			Each bit selects an axis, X, Y, or Z from least- to most- significant.
 *			For instance: ZYX|000|001|010|011 -> the bottom of cube.
 *
 *	@author	pezy
 *	@date	2017-03-03
 *	@see
 */

#include <osg/Group>
#include <osg/Switch>
#include <osg/BoundingBox>
#include <osgText/Text>

class CX3DWindow;
class CX3DGlobalCoordMap;
class CXObject;

class CX3DAutoCubeAxes
{
public:
	CX3DAutoCubeAxes() = default;
	~CX3DAutoCubeAxes() = default;

	void SetWindowAndCoordMap(CX3DWindow* pWin, CX3DGlobalCoordMap* pCoordMap) { m_pWin = pWin; m_pCoordMap = pCoordMap; }
	osg::ref_ptr<osg::Group> GetCoordinateAxes() { return m_pGroupAxis; }
	osg::BoundingBox GetBoundingBox();

	void UpdateWindowInfo();
	
	void ExpandBy(CXObject* pObj);
	void UpdateBoundingBox();

	void SetVisible(bool bShow);
	void SetGridVisible(bool bShow);

private:
	void _UpdateGeometry();

	void _CalcGridVertices();
	void _CalcTickVertices();

	osg::Switch* _BuildFrame();
	osg::Switch* _BuildGrids();
	osg::Switch* _BuildTicks();
	osg::Switch* _BuildMarks();

	osg::Geode* _BuildDebugInfo();

	osgText::Text* _BuildMark(const osg::Vec3& vecPosition, double d);

private:
	CX3DWindow* m_pWin = nullptr;
	CX3DGlobalCoordMap* m_pCoordMap = nullptr;
	osg::BoundingBox m_box;
	
	osg::ref_ptr<osg::Group> m_pGroupAxis;

	osg::ref_ptr<osg::Vec3Array> m_pVertexGridX;
	osg::ref_ptr<osg::Vec3Array> m_pVertexGridY;
	osg::ref_ptr<osg::Vec3Array> m_pVertexGridZ;

	std::vector<osg::Vec3Array*> m_vecTicksVertex;

	std::vector<double> m_vecGridX;
	std::vector<double> m_vecGridY;
	std::vector<double> m_vecGridZ;
};

#endif // KEAUTOCUBEAXES_H
