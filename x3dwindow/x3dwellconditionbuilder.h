#ifndef X3DWELLCONDITION_H
#define X3DWELLCONDITION_H

#include "x3dbuilder.h"

//! @class	CRL3DWellCondition
//!
//! @brief	The class is a node builder for Well Condition Cells.
//!
//! @author	Pezy
//! @date	2015/1/15
//! 		

class CX3DWindow;
class CXWellCondition;
class CXViewInfoWellCondition;

class CX3DWellConditionBuilder : public CX3DBuilderAbstract
{
public:
	CX3DWellConditionBuilder();
	~CX3DWellConditionBuilder();

	//! @brief Reimplement the function
	virtual osg::ref_ptr<osg::Group> Build(QUuid objId);
	virtual void UpdateNode(EEventType eType);

private:
	void _CalcVertices();
	void _CalcIndices(bool bInit = false);
	void _CalcColor();
	void _CalcNormal();
	void _CalcPropertyColor();

private:
	CX3DWindow *m_pOSGWin;
	CXWellCondition *m_pWellCondition;
	CXViewInfoWellCondition *m_pViewInfo;
	QList<unsigned int> m_listWellCellIndexes;

	osg::ref_ptr<osg::Geometry> m_pCellGeom;
	osg::ref_ptr<osg::Geometry> m_pGridGeom;
	osg::ref_ptr<osg::Vec3Array> m_pVertices;

	static unsigned m_arrayIndex[24];
	static unsigned m_arrayLines[24];
};

#endif // RL3DWELLCONDITION_H
