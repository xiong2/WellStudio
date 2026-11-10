#ifndef X3DBUILDER_H_H
#define X3DBUILDER_H_H

#include <quuid.h>
#include <osg/Group>
#include <osg/ref_ptr>
#include <osg/Geode>
#include <osg/Switch>
#include "x3dwindow_global.h"
#include "xdef.h"
#include "xwindow.h"

class CXObject;
class CX3DGlobalCoordMap;

class X3DWINDOW_EXPORT CX3DBuilderAbstract
{
public:
	CX3DBuilderAbstract() {}
    virtual ~CX3DBuilderAbstract();

    virtual osg::ref_ptr<osg::Group> Build(QUuid objId) = 0;

	virtual void UpdateNode(EEventType eType) {}
	virtual void UpdateBuilderNode(QUuid objID) {}

	virtual osg::ref_ptr<osg::Group> GetBuilderNode();
	virtual osg::BoundingBox GetBoundBox();

    ///@brief set the current window and the coordinate map
    void SetWindowAndCoordMap(CXWindow* pCurrentWindow, CX3DGlobalCoordMap* pCoordMap);
	void SetBuilderNode(osg::ref_ptr<osg::Group> builderNode);
	void SetObjectID(const QUuid& objID);

	///@brief Tell if the global transform can apply with distortion
	bool IsScalable();

	const QUuid& GetObjectID() const;
    CXWindow* GetCurWin();
	CX3DGlobalCoordMap* GetCoordMap();

protected:
    bool m_bScalable = true;
    osg::ref_ptr<osg::Group> m_pBuilderNode = nullptr;

	CX3DGlobalCoordMap* m_pCoordMap = nullptr;
    CXWindow* m_pCurWin = nullptr;

	osg::BoundingBox m_BoundBox;
	QUuid m_objID;
};

#endif