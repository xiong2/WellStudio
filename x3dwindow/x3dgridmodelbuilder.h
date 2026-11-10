#ifndef X3DGRIDMODELBUILDER_H
#define X3DGRIDMODELBUILDER_H

#include "x3dbuilder.h"

/**
* @class CX3DGridModelBuilder in the file "rl3dgridmodelbuilder.h"
* @brief The class is a node builder for Grid model.
* 
* @author PEZY
* @date Nov. 24, 2014
* @see CXGridModel and EXGridModel
*/

class CXViewInfo3DGridModel;
class CX3DWindow;
class CXGridCell;

class CX3DGridModelBuilder : public CX3DBuilderAbstract
{
public:
	CX3DGridModelBuilder();
	~CX3DGridModelBuilder();

	///@brief Reimplement the function
	virtual osg::ref_ptr<osg::Group> Build(QUuid objId);

	virtual void UpdateNode(EEventType eType);

private:
	void _CalcVertices(const QList<CXGridCell*> &listCells);
	void _CalcIndices(bool bInit = false);
	void _CalcColor();
	void _CalcNormal();
	void _CalcPropertyIndicesAndColor();

private:
	CXViewInfo3DGridModel *m_pViewInfo;
	CX3DWindow *m_pOSGWindow;

	osg::ref_ptr<osg::Vec3usArray> m_pVecIJK;
	osg::ref_ptr<osg::Geometry> m_pCellGeom;
	osg::ref_ptr<osg::Geometry> m_pGridGeom;
	osg::ref_ptr<osg::Vec3Array> m_pVertices;

public:
	static unsigned m_arrayIndex[24];
	static unsigned m_arrayLines[24];
};

#endif // RL3DGRIDMODELBUILDER_H
