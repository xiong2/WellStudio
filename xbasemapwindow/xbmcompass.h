#ifndef XBMCOMPASS_H
#define XBMCOMPASS_H

/*!
 *	@brief	display the compass of the base map.
 *	@author	pezy
 *	@date	2016-06-27
 *	@see
 */

#include <osg/ref_ptr>
#include <osg/Vec3>

namespace osg{ class Projection; class Geometry; class Geode; class MatrixTransform; };
class CXBaseMapWindow;

class CXBMCompass
{
public:
	CXBMCompass();
	~CXBMCompass();

	osg::ref_ptr<osg::Projection> GetCompassNode();

	void SetVisible(bool bVisible);
	void SetWindow(CXBaseMapWindow* pBMWin);
	void UpdateViewInfo();
	void UpdatePosition();

private:
	osg::Geometry* _BuildGeometry();
	osg::Vec3 _GetPosition();

private:
	const float m_ratio = 5.f;

	CXBaseMapWindow* m_pWin;

	osg::ref_ptr<osg::Geode> m_pGeode;
	osg::ref_ptr<osg::Projection> m_pCompassProjection;
	osg::ref_ptr<osg::Geometry> m_pGeom;
	osg::ref_ptr<osg::MatrixTransform> m_modelView;
};

#endif // KEBMCOMPASS_H
