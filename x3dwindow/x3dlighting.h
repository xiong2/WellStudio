#ifndef CX3DLIGHTING_H
#define CX3DLIGHTING_H

#include <QBitArray>
#include <QVector>
#include <osg/LightSource>
#include <osg/Group>
#include <osg/Geode>

class CXWindowInfo3D;

class CX3DLighting
{
public:
	CX3DLighting();
	~CX3DLighting();

	osg::ref_ptr<osg::Group> GetLightingNode();
	void SetWindowInfoAndRootStateSet(CXWindowInfo3D* pWinInfo, osg::StateSet* pRootStateSet);
	void UpdatePosition(const osg::BoundingBox& box);
	void SetSphereVisible(bool bVisible);
	void UpdateViewInfo(int id);

private:
	osg::LightSource* _BuildLightSource(int id);
	osg::Geode* _BuildLightSphere(int id);
	osg::Light* _BuildLight(int id);

private:
	constexpr static int LIGHT_NUM = 4;
	constexpr static int SPHERE_RADIUS = 100;
	
	osg::ref_ptr<osg::Group> m_pLightGroup;
	QVector<osg::ref_ptr<osg::LightSource>> m_vecLightSource;
	QVector<osg::ref_ptr<osg::Geode>> m_vecLightSphere;
	QVector<osg::ref_ptr<osg::Light>> m_vecLight;

	osg::StateSet* m_pRootStateSet = nullptr;
	CXWindowInfo3D* m_pWinInfo = nullptr;
};

#endif // CX3DLIGHTING_H
