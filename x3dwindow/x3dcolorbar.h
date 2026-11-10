#ifndef X3DCOLORBAR_H
#define X3DCOLORBAR_H

#include "x3dwindow_global.h"
#include <osg/MatrixTransform>
#include <osg/Projection>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Switch>
#include <osgText/Text>
#include <QUuid>
#include <QStack>
#include <qlist.h>

/*!
 * @class	CX3DColorbar in the file "ke3dcolorbar.h"
 * @brief	Build the colorbar on the 3D scene.
 *
 * @author	pezy
 * @date	2016-09-28
 * @see
 */

class CXWindow;
class CXWindowInfo;
class CXColormap;

class X3DWINDOW_EXPORT CX3DColorbar
{
public:
	CX3DColorbar();
	~CX3DColorbar();

	osg::ref_ptr<osg::Group> GetColorbar();
	void SetWindow(CXWindow* pWin);
	void PushObj(const QUuid& uuidGeomObj);
	void RemoveObj(const QUuid& uuidGeomObj);
	void UpdateObj(const QUuid& uuidGeomObj);
	void Clear();

	void UpdateViewInfo();
	void UpdatePosition();
	void SetVisible(bool bVisible);

private:
	void _BuildHUD(const QUuid& objID);
	osgText::Text* _BuildObjName(const QUuid& objID);
	osg::Geometry* _BuildRainbow(const QUuid& objID);
	const QList<osg::ref_ptr<osgText::Text>>& _BuildMarks(const QUuid& objID);
	osg::Geometry* _BuildTicks(int nScales);

	osg::Vec3 _CalcRainbowTranslate();
	osg::Vec3Array* _CalcRainbowVertex(CXColormap* pColormap);
	osg::Vec4Array* _CalcRainbowColors(CXColormap* pColormap);

	void _SetObjName(const QUuid& objID);
	void _ObjectChanged(const QUuid& objID);

private:
	const float m_fOffset = 20.f;
	const float m_fRainbowWidth = 30.f;
	const float m_fRainbowHeight = 180.f;

	CXWindow* m_pWin = nullptr;
	CXWindowInfo* m_pWinInfo = nullptr;

	osg::ref_ptr<osg::Switch> m_pSwitch;
	osg::ref_ptr<osg::Projection> m_pProjection;
	osg::ref_ptr<osg::MatrixTransform> m_pMT;
	osg::ref_ptr<osg::Geode> m_pGeode;
	osg::ref_ptr<osg::Geometry> m_pGeom;
	osg::ref_ptr<osg::Geometry> m_pGeomTicks;

	osg::ref_ptr<osgText::Text> m_pTextObjName;
	QList<osg::ref_ptr<osgText::Text>> m_listMarks;

	QStack<QUuid> m_stackObjID;
};

#endif // KE3DCOLORBAR_H