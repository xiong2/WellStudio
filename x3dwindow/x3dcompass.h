#ifndef X3DNORTHARROWBUILDER_H
#define X3DNORTHARROWBUILDER_H

/*!
*	@brief	display the compass of the 3D scene.
*	@author	pezy
*	@date	2014-07-11
*	@see
*/

#include <osg/Camera>
#include <osg/MatrixTransform>

class CX3DWindow;

class CXHUDCamera : public osg::Camera
{
public:
	void traverse(osg::NodeVisitor& nv) override;
	void SetMainCameraAndTransform(osg::MatrixTransform* pMt, osg::Camera* pCamera);

private:
	osg::ref_ptr<osg::MatrixTransform> m_pTransform;
	osg::ref_ptr<osg::Camera> m_pMainCamera;
};

class CX3DCompass
{
public:
	CX3DCompass();
	~CX3DCompass();

	osg::ref_ptr<osg::Camera> GetCompassNode();

	void SetVisible(bool bVisible);
	void SetWindow(CX3DWindow* p3DWin);
	void UpdateViewInfo();
	void UpdateViewport();

private:
	osg::Geometry* _BuildGeometry();
	//osg::Vec3 _GetPosition();

private:
	const float m_ratio = 0.05f;

	CX3DWindow* m_pWin;

	osg::ref_ptr<CXHUDCamera> m_pCompassCamera;
	osg::ref_ptr<osg::Geode> m_pGeode;
	osg::ref_ptr<osg::Geometry> m_pGeom;
};

#endif // RL3DNORTHARROWBUILDER_H
