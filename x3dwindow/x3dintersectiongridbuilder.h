#ifndef X3DINTERSECTIONGRIDBUILDER_H
#define X3DINTERSECTIONGRIDBUILDER_H

#include "x3dbuilder.h"

/**
* @class CX3DIntersectionGridBuilder in the file "rl3dintersectiongridbuilder.h"
* @brief The class is a node builder for intersection grid.
* 
* @author PEZY
* @date Apr. 21 2015
* @see CXGridModel and EXGridModel
*/

class CXViewInfo3DGridModel;
class CXIntersectionGrid;
class CXGridCell;
class CX3DWindow;
class CXIntersectedGridCell;

class CX3DIntersectionGridBuilder : public CX3DBuilderAbstract
{
public:
	CX3DIntersectionGridBuilder();
	~CX3DIntersectionGridBuilder();

    osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	void UpdateNode(EEventType eType) override;

private:
	void _CalcCompleteVertices();
	void _CalcCompleteIndices(bool bInit = false);
	void _CalcCompleteNormal();

	void _CalcIntersectionVertices();
	void _CalcIntersectionIndices(bool bInit = false);
	void _CalcIntersectionNormal();

	void _CalcColor();
	void _CalcPropertyIndicesAndColor();

private:
	CXViewInfo3DGridModel* m_pViewInfo;
	CX3DWindow* m_pOSGWindow;
	CXIntersectionGrid* m_pGrid;

	osg::ref_ptr<osg::Vec3usArray> m_pVecCompleteIJK;
	osg::ref_ptr<osg::Geometry> m_pCompleteCellGeom;
	osg::ref_ptr<osg::Geometry> m_pCompleteGridGeom;
	osg::ref_ptr<osg::Vec3Array> m_pCompleteVertices;

	osg::ref_ptr<osg::Vec3usArray> m_pVecIntersectedIJK;
	osg::ref_ptr<osg::Vec3Array> m_pIntersectedVertices;
	osg::ref_ptr<osg::Geometry> m_pIntersectedCellGeom;
	osg::ref_ptr<osg::Geometry> m_pIntersectedGridGeom;
};

#endif // RL3DINTERSECTIONGRIDBUILDER_H
