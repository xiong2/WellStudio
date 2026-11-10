#ifndef XSHAPEGEOMETRY_H_
#define XSHAPEGEOMETRY_H_

//@brief:	Build million drawable shape in a geometry.
//@author:	PEZY
//@date:	Sept. 2014
//@see:		

#include <osg/Geometry>

class CXBigGeometry
{
public:
	enum Shape {SpherePoints, Sphere, Cylinder, Box};

	CXBigGeometry(Shape shape, const osg::Vec3Array &centers, float radius, unsigned fidelity = 2U);
	~CXBigGeometry();

	void SetColor	(const osg::Vec4& color);
	void SetCenter	(const osg::Vec3Array &centers);
	void SetRadius	(float radius);
	void SetShape	(Shape shape);
	osg::Geometry*	Geometry() { return m_geom.get(); }

private:
	void _Create();
	void _CreateSpherePoints(const osg::Vec3Array& vecCenter, float radius, unsigned fidelity);
	void _CreateSphere		(const osg::Vec3Array& vecCenter, float radius, unsigned fidelity);
	void _CreateBox			(const osg::Vec3Array& vecCenter, float radius, unsigned fidelity);
	void _CreateCylider		(const osg::Vec3Array& vecCenter, float radius, unsigned fidelity, float halfHeight = 1.f);

	unsigned _MiddlePointOnSphere(osg::Vec3Array* pVertices, std::map<long long, unsigned>& uniqueMap, unsigned u1, unsigned u2);

private:
	osg::ref_ptr<osg::Geometry> m_geom;

	osg::ref_ptr<osg::Vec4Array> m_curColors;
	float m_curRadius;
	unsigned m_curFidelity;
	Shape m_curShape;
	osg::ref_ptr<osg::Vec3Array> m_pVecCenter;
	osg::ref_ptr<osg::Vec3Array> m_pVecCore;
};


#endif //RLSHAPEGEOMETRY_H_