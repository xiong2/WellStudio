#ifndef XBMSCALE_H
#define XBMSCALE_H

/*!
 *	@brief	display the scale of the base map.
 *	@author	pezy
 *	@date	2016-06-03
 *	@see
 */

#include <osg/ref_ptr>
#include <osg/Array>
#include <osgText/Text>
namespace osg { class Projection; class Geometry; class MatrixTransform; class Geode; };
class CXBaseMapWindow;

class CXBMScale
{
public:
	CXBMScale();
	~CXBMScale();

	void SetWindow(CXBaseMapWindow* pBMWin);
	osg::ref_ptr<osg::Projection> GetScaleNode();

	void UpdateScale(int iScale);
	void UpdateViewInfo();
	void UpdatePosition();
	void SetVisible(bool bVisible);

private:
	osg::Geometry* _BuildGeometry();
	osgText::Text* _BuildMark();
	void _UpdateMarkInfo();
	void _UpdateFrameInfo();
	osg::Vec3 _GetTranslatePos();

private:
	osg::ref_ptr<osg::Projection> m_pScaleProjection;
	osg::ref_ptr<osg::MatrixTransform> m_modelview;
	osg::ref_ptr<osg::Geode> m_pGeode;
	osg::ref_ptr<osgText::Text> m_pMark;
	osg::ref_ptr<osg::Geometry> m_pGeom;
	CXBaseMapWindow* m_pWin;
};

#endif // KEBMSCALE_H
