#ifndef CX3DCURSOR_H
#define CX3DCURSOR_H

#include "x3dwindow_global.h"
#include <osg/Geometry>
#include <osg/AutoTransform>

/*!
 * @class	CXCursor in the file "kecursor.h"
 * @brief	The class is a node builder for the cursor
 * 
 * @author	pezy
 * @date	2016-10-10
 * @see 
 */

class CXWindow;
class CX3DGlobalCoordMap;

class X3DWINDOW_EXPORT CX3DCursor
{
public:
	CX3DCursor();
	~CX3DCursor();

	osg::ref_ptr<osg::Group> GetCursor();
	void SetWindowAndCoordMap(CXWindow* pWin, CX3DGlobalCoordMap* pCoordMap);
	void SetVisible(bool bVisible);
	void UpdatePosition();

private:
	osg::Geometry* _BuildGeometry();
	osg::Vec3Array* _GetVertex();
	osg::Geode* _BuildGeode();
	osg::Vec3 _GetPosition();
	osg::AutoTransform* _BuildTransform();

private:
	osg::ref_ptr<osg::Geometry> m_pGeometry;
	osg::ref_ptr<osg::AutoTransform> m_pAutoTrans;
	osg::ref_ptr<osg::Camera> m_pCamera;

	CXWindow* m_pWin = nullptr;
	CX3DGlobalCoordMap* m_pCoordMap = nullptr;
};

#endif // CX3DCURSOR_H
