#ifndef XBMMANIPULATOR_H
#define XBMMANIPULATOR_H

#include <osgGA/OrbitManipulator>

/*!
 *	@brief	manipulator for basemap.
 *	@author	pezy
 *	@date	2016-04-13
 */

class CXBaseMapWindow;

class CXBMManipulator : public osgGA::OrbitManipulator
{
public:
	CXBMManipulator();
	virtual ~CXBMManipulator();
	
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);

	float GetCurrentScale();
	void GetOffsetCenter(double& offsetX, double& offsetY);

private:
	void _UpdateHUDCamera();

private:
	osg::ref_ptr<osg::Camera> m_pCamera;
	CXBaseMapWindow* m_pWin;

	double m_l = 0.0; // left
	double m_r = 0.0; // right
	double m_b = 0.0; // bottom
	double m_t = 0.0; // top
	double m_n = 0.0; // near
	double m_f = 0.0; // far

	osg::Vec3d m_center;

	float m_originX = 0.f;
	float m_originY = 0.f;

	double m_offsetX = 0.0;
	double m_offsetY = 0.0;
};

#endif // KEBMMANIPULATOR_H
