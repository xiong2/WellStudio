#include "xbiggeometry.h"

#include <cassert>
#include <algorithm>
#include <osgUtil/SmoothingVisitor>

CXBigGeometry::CXBigGeometry(Shape shape, const osg::Vec3Array &centers, float radius, unsigned fidelity /* = 2U */)
	:m_curRadius(radius), m_curFidelity(fidelity), m_curShape(shape)
{
	// Init colors
	m_curColors = new osg::Vec4Array(1);
	(*m_curColors)[0].set(0.f, 0.f, 0.f, 1.f);	// white default.

	m_pVecCenter = new osg::Vec3Array(centers);
	m_pVecCore = nullptr;
	_Create();
}

CXBigGeometry::~CXBigGeometry()
{

}

void CXBigGeometry::_CreateSpherePoints(const osg::Vec3Array& vecCenter, float radius, unsigned fidelity)
{
	osg::ref_ptr<osg::Vec3Array> pVertices = new osg::Vec3Array;
	{
		// Build regular icosahedron
		osg::ref_ptr<osg::Vec3Array> pCoreVertices = new osg::Vec3Array(12);

		// k is golden radio.
		const float k = (1.f + std::sqrt(5.f))/2.f;

		(*pCoreVertices)[0].set(-1,  k, 0);
		(*pCoreVertices)[1].set( 1,  k, 0);
		(*pCoreVertices)[2].set(-1, -k, 0);
		(*pCoreVertices)[3].set( 1, -k, 0);
		(*pCoreVertices)[4].set(0, -1,  k);
		(*pCoreVertices)[5].set(0,  1,  k);
		(*pCoreVertices)[6].set(0, -1, -k);
		(*pCoreVertices)[7].set(0,  1, -k);
		(*pCoreVertices)[8].set(  k, 0, -1);
		(*pCoreVertices)[9].set(  k, 0,  1);
		(*pCoreVertices)[10].set(-k, 0, -1);
		(*pCoreVertices)[11].set(-k, 0,  1);

		unsigned int basicArray[60] = {	0, 11,  5, 0,  5,  1,  0,  1,  7,  0,  7, 10, 0, 10, 11,	// around 0. clockwise
			1,  5,  9, 5, 11,  4, 11, 10,  2, 10,  7,  6, 7,  1,  8,	// more adjacent.
			3,  9,  4, 3,  4,  2,  3,  2,  6,  3,  6,  8, 3,  8,  9,	// around 3.
			4,  9,  5, 2,  4, 11,  6,  2, 10,  8,  6,  7, 9,  8,  1};	// more adjacent.
		osg::ref_ptr<osg::DrawElementsUInt> pCoreTriangle = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, basicArray, basicArray+60);

		for (unsigned i=0; i<fidelity; ++i)
		{
			std::map<long long, unsigned> uniqueVertexMap;
			osg::ref_ptr<osg::DrawElementsUInt> newCoreTriangle = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

			//   / \          /2\
			//  /   \  ==>   /---\    1 triangle subdivide to 4 triangle.
			// /_ _ _\      /1\4/3\

			for (auto iter = pCoreTriangle->begin(); iter != pCoreTriangle->end(); iter += 3)
			{
				unsigned u1 = _MiddlePointOnSphere(pCoreVertices, uniqueVertexMap, *iter, *(iter+1));
				unsigned u2 = _MiddlePointOnSphere(pCoreVertices, uniqueVertexMap, *(iter+1), *(iter+2));
				unsigned u3 = _MiddlePointOnSphere(pCoreVertices, uniqueVertexMap, *(iter+2), *iter);

				newCoreTriangle->push_back(*iter);		newCoreTriangle->push_back(u1); newCoreTriangle->push_back(u3);	// 1
				newCoreTriangle->push_back(*(iter+1));	newCoreTriangle->push_back(u2); newCoreTriangle->push_back(u1); // 2
				newCoreTriangle->push_back(*(iter+2));	newCoreTriangle->push_back(u3); newCoreTriangle->push_back(u2); // 3
				newCoreTriangle->push_back(u1);			newCoreTriangle->push_back(u2); newCoreTriangle->push_back(u3); // 4
			}

			pCoreTriangle = newCoreTriangle;
		}

		osg::ref_ptr<osg::DrawElementsUInt> points = new osg::DrawElementsUInt(osg::PrimitiveSet::POINTS, pCoreVertices->size());
		for (auto it = points->begin(); it != points->end(); ++it) *it = it - points->begin();

		for (auto centerIter = vecCenter.begin(); centerIter != vecCenter.end(); ++centerIter)
		{
			// add all the vertex.
			for (auto coreIter = pCoreVertices->begin(); coreIter != pCoreVertices->end(); ++coreIter)
			{
				coreIter->normalize();
				*coreIter *= radius;
				pVertices->push_back(*coreIter + *centerIter);
			}

			// calculate the factor which need to add to elements of pTriangle.
			auto factor = (centerIter - vecCenter.begin()) * pCoreVertices->size();

            osg::ref_ptr<osg::DrawElementsUInt> pTriangle = new osg::DrawElementsUInt(points->getMode(), points->begin(), points->end());

            if (factor != 0)
                std::for_each(pTriangle->begin(), pTriangle->end(), [&](unsigned &i){ i += factor; });

			m_geom->addPrimitiveSet(pTriangle.get());
		}
	}

	m_geom->setVertexArray(pVertices.get());
	m_geom->setColorArray(m_curColors.get());
	m_geom->setColorBinding(osg::Geometry::BIND_OVERALL);
}

void CXBigGeometry::_CreateSphere(const osg::Vec3Array& vecCenter, float radius, unsigned fidelity)
{
	osg::ref_ptr<osg::Vec3Array> pVertices = new osg::Vec3Array;
	{
		// Build regular icosahedron
		osg::ref_ptr<osg::Vec3Array> pCoreVertices = new osg::Vec3Array(12);

		// k is golden radio.
		const float k = (1.f + std::sqrt(5.f))/2.f;

		//@brief	the vertices of an icosahedron are the corners of three orthogonal rectangles. 
		//@see		https://en.wikipedia.org/wiki/Icosahedron#mediaviewer/File:Icosahedron-golden-rectangles.svg

		// XOY: 0|1
		//		-+-
		//		2|3 

		(*pCoreVertices)[0].set(-1,  k, 0);
		(*pCoreVertices)[1].set( 1,  k, 0);
		(*pCoreVertices)[2].set(-1, -k, 0);
		(*pCoreVertices)[3].set( 1, -k, 0);

		// YOZ: 4|5
		//		-+-
		//		6|7

		(*pCoreVertices)[4].set(0, -1,  k);
		(*pCoreVertices)[5].set(0,  1,  k);
		(*pCoreVertices)[6].set(0, -1, -k);
		(*pCoreVertices)[7].set(0,  1, -k);

		// ZOX:  8| 9
		//		--+--
		//		10|11

		(*pCoreVertices)[8].set(  k, 0, -1);
		(*pCoreVertices)[9].set(  k, 0,  1);
		(*pCoreVertices)[10].set(-k, 0, -1);
		(*pCoreVertices)[11].set(-k, 0,  1);

		unsigned int basicArray[60] = {	0, 11,  5, 0,  5,  1,  0,  1,  7,  0,  7, 10, 0, 10, 11,	// around 0. clockwise
			1,  5,  9, 5, 11,  4, 11, 10,  2, 10,  7,  6, 7,  1,  8,	// more adjacent.
			3,  9,  4, 3,  4,  2,  3,  2,  6,  3,  6,  8, 3,  8,  9,	// around 3.
			4,  9,  5, 2,  4, 11,  6,  2, 10,  8,  6,  7, 9,  8,  1};	// more adjacent.
		osg::ref_ptr<osg::DrawElementsUInt> pCoreTriangle = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, std::begin(basicArray), std::end(basicArray));

		// subdivide
		for (unsigned i=0; i<fidelity; ++i)
		{
			std::map<long long, unsigned> uniqueVertexMap;
			osg::ref_ptr<osg::DrawElementsUInt> newCoreTriangle = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

			//   / \          /2\
			//  /   \  ==>   /---\    1 triangle subdivide to 4 triangle.
			// /_ _ _\      /1\4/3\

			for (auto iter = pCoreTriangle->begin(); iter != pCoreTriangle->end(); iter += 3)
			{
				unsigned u1 = _MiddlePointOnSphere(pCoreVertices, uniqueVertexMap, *iter, *(iter+1));
				unsigned u2 = _MiddlePointOnSphere(pCoreVertices, uniqueVertexMap, *(iter+1), *(iter+2));
				unsigned u3 = _MiddlePointOnSphere(pCoreVertices, uniqueVertexMap, *(iter+2), *iter);

				newCoreTriangle->push_back(*iter);		newCoreTriangle->push_back(u1); newCoreTriangle->push_back(u3);	// 1
				newCoreTriangle->push_back(*(iter+1));	newCoreTriangle->push_back(u2); newCoreTriangle->push_back(u1); // 2
				newCoreTriangle->push_back(*(iter+2));	newCoreTriangle->push_back(u3); newCoreTriangle->push_back(u2); // 3
				newCoreTriangle->push_back(u1);			newCoreTriangle->push_back(u2); newCoreTriangle->push_back(u3); // 4
			}

			pCoreTriangle.swap(newCoreTriangle);
		}

		m_pVecCore = pCoreVertices;

		// set all the vertex
		for (auto centerIter = vecCenter.begin(); centerIter != vecCenter.end(); ++centerIter)
		{
			// add all the vertex.
			for (auto coreIter = pCoreVertices->begin(); coreIter != pCoreVertices->end(); ++coreIter)
			{
				coreIter->normalize();
				*coreIter *= radius;
				pVertices->push_back(*coreIter + *centerIter);
			}

			// calculate the factor which need to add to elements of pTriangle.
			auto factor = (centerIter - vecCenter.begin()) * pCoreVertices->size();

			osg::ref_ptr<osg::DrawElementsUInt> pTriangle = new osg::DrawElementsUInt(pCoreTriangle->getMode(), pCoreTriangle->begin(), pCoreTriangle->end());

			if (factor != 0)
				std::for_each(pTriangle->begin(), pTriangle->end(), [&](unsigned &i){ i += factor; });

			m_geom->addPrimitiveSet(pTriangle.get());
		}
	}

	m_geom->setVertexArray(pVertices.get());
	m_geom->setColorArray(m_curColors.get());
	m_geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	m_geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	osgUtil::SmoothingVisitor::smooth(*m_geom);
	m_geom->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
}

unsigned CXBigGeometry::_MiddlePointOnSphere(osg::Vec3Array* pVertices, std::map<long long, unsigned>& uniqueMap, unsigned u1, unsigned u2)
{
	float len = pVertices->at(u1).length();
	// made the key for unique vertex (small one * 2^16 + big one)
	long long key = u1 < u2 ? (u1 << 16) + u2 : (u2 << 16) + u1;

	// check exist
	std::map<long long, unsigned>::const_iterator iter;
	if ((iter = uniqueMap.find(key)) != uniqueMap.end()) return iter->second;

	osg::Vec3 middlePoint = (pVertices->at(u1) + pVertices->at(u2))/2; 
	middlePoint.normalize(); 
	middlePoint *= len;
	pVertices->push_back(middlePoint);
	unsigned size = pVertices->size();

	uniqueMap.insert(std::pair<long long, unsigned>(key, size-1));

	return size-1;
}

void CXBigGeometry::_CreateBox(const osg::Vec3Array& vecCenter, float radius, unsigned fidelity)
{
	osg::ref_ptr<osg::Vec3Array> pVertices = new osg::Vec3Array;
	{
		osg::ref_ptr<osg::Vec3Array> pCoreVertices = new osg::Vec3Array(8);

		// XOZ (front): 4|5 (back): 7|6  
		//				-+-			-+-
		//				0|1			3|2

		(*pCoreVertices)[0].set(-1,-1,-1);
		(*pCoreVertices)[1].set( 1,-1,-1);
		(*pCoreVertices)[2].set( 1, 1,-1);
		(*pCoreVertices)[3].set(-1, 1,-1);
		(*pCoreVertices)[4].set(-1,-1, 1);
		(*pCoreVertices)[5].set( 1,-1, 1);
		(*pCoreVertices)[6].set( 1, 1, 1);
		(*pCoreVertices)[7].set(-1, 1, 1);

		//   /--- /
		//  /_1_ /|
		//  |   |2/ : 0(below) -> 1 -> 2 -> 3(left) -> 4(back) -> 5
		//  |_5_|/

		unsigned basicArray[24] = {0, 1, 2, 3, 4, 5, 6, 7,
			5, 1, 2, 6, 4, 0, 3, 7,
			6, 2, 3, 7, 5, 1, 0, 4};
		osg::ref_ptr<osg::DrawElementsUInt> pCoreBase = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, basicArray, basicArray+24);
		m_pVecCore = pCoreVertices;

		// set all the vertex
		for (auto centerIter = vecCenter.begin(); centerIter != vecCenter.end(); ++centerIter)
		{
			for (auto iter = pCoreVertices->begin(); iter != pCoreVertices->end(); ++iter)
			{
				iter->normalize();
				*iter *= radius;
				pVertices->push_back(*iter + *centerIter);
			}

			// calculate the factor which need to add to elements of pTriangle.
			auto factor = (centerIter - vecCenter.begin()) * pCoreVertices->size();
			
			osg::ref_ptr<osg::DrawElementsUInt> pyramid = new osg::DrawElementsUInt(pCoreBase->getMode(), pCoreBase->begin(), pCoreBase->end());

			if (factor != 0)
				std::for_each(pyramid->begin(), pyramid->end(), [&](unsigned &i){ i += factor; });

			m_geom->addPrimitiveSet(pyramid.get());
		}
	}

	m_geom->setVertexArray(pVertices.get());
	m_geom->setColorArray(m_curColors.get());
	m_geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	osgUtil::SmoothingVisitor::smooth(*m_geom.get());
}

void CXBigGeometry::_CreateCylider(const osg::Vec3Array& vecCenter, float radius, unsigned fidelity, float halfHeight)
{
	osg::ref_ptr<osg::Vec3Array> pVertices = new osg::Vec3Array;
	{
		// Build cuboid
		osg::ref_ptr<osg::Vec3Array> pCoreVertices = new osg::Vec3Array(8);
		osg::DrawElementsUInt* topCoreBase = new osg::DrawElementsUInt(osg::PrimitiveSet::POLYGON);
		osg::DrawElementsUInt* belowCoreBase = new osg::DrawElementsUInt(osg::PrimitiveSet::POLYGON);
		osg::DrawElementsUInt* pyramidCoreBase = new osg::DrawElementsUInt(osg::PrimitiveSet::QUAD_STRIP);

		// XOZ (front): 1|3 (back): 7|5  
		//				-+-			-+-
		//				0|2			6|4

		(*pCoreVertices)[0].set(-1,-1,-halfHeight);
		(*pCoreVertices)[1].set(-1,-1, halfHeight);
		(*pCoreVertices)[2].set( 1,-1,-halfHeight);
		(*pCoreVertices)[3].set( 1,-1, halfHeight);
		(*pCoreVertices)[4].set( 1, 1,-halfHeight);
		(*pCoreVertices)[5].set( 1, 1, halfHeight);
		(*pCoreVertices)[6].set(-1, 1,-halfHeight);
		(*pCoreVertices)[7].set(-1, 1, halfHeight);

		// cuboid to cylinder
		for (unsigned i=0; i<fidelity; ++i)
		{
			osg::ref_ptr<osg::Vec3Array> newVertices = new osg::Vec3Array(8 << i);

			// Example: 1|3		 1|new	 new|3
			//			-+-  ==> -+--- + ---+-  (new is the middle line points)
			//			0|2		 0|new	 new|2

			for (auto iter = pCoreVertices->begin(); iter != pCoreVertices->end(); iter+=2)
			{
				osg::Vec3 newPoint0, newPoint1;
				if (iter+2 == pCoreVertices->end())	// connected end to head. 
				{
					newPoint0 = (*iter		+ *(pCoreVertices->begin()	))/2;	// middle of last point and first point (below)
					newPoint1 = (*(iter+1)	+ *(pCoreVertices->begin()+1))/2;	// middle of last point and first point (top)
				}
				else
				{
					newPoint0 = (*iter		+ *(iter+2))/2;	// middle of two below origin points.
					newPoint1 = (*(iter+1)	+ *(iter+3))/2;	// middle of two top   origin points.
				}

				osg::Vec2 xoyPoint(newPoint0.x(), newPoint0.y()); xoyPoint.normalize(); xoyPoint *= radius;
				newPoint0[0] = newPoint1[0] = xoyPoint[0]; newPoint0[1] = newPoint1[1] = xoyPoint[1]; // x and y coordinate are same

				newVertices->push_back(*iter);
				newVertices->push_back(*(iter+1));
				newVertices->push_back(newPoint0);
				newVertices->push_back(newPoint1);
			}

			pCoreVertices = newVertices;
		}

		m_pVecCore = pCoreVertices;

		//    _ _   
		//   /   \
		//  | TOP |      _ _ _ _ _ _ _ _ _ _
		//   \_ _/   +  |   |   |   |   |   |
		//   /   \      | 0 | 1 | 2 | 3 | 4 |......
		//  | BLW |      - - - - - - - - - -
		//   \_ _/

		for(int i=0; i<pCoreVertices->size(); ++i)
			if (i%2 == 0)	belowCoreBase->push_back(i);
			else			topCoreBase->push_back(i);
		for(int i=0; i<pCoreVertices->size(); ++i)
			pyramidCoreBase->push_back(i);
		pyramidCoreBase->push_back(0); pyramidCoreBase->push_back(1);	// connect end to end.

		// set all the vertex.
		for (auto iter = vecCenter.begin(); iter != vecCenter.end(); ++iter)
		{
			for (auto coreIter = pCoreVertices->begin(); coreIter != pCoreVertices->end(); ++coreIter)
				pVertices->push_back(*coreIter + *iter);

			auto factor = (iter - vecCenter.begin()) * pCoreVertices->size();

			osg::ref_ptr<osg::DrawElementsUInt> topBase = topCoreBase;
			osg::ref_ptr<osg::DrawElementsUInt> belowBase = belowCoreBase;
			osg::ref_ptr<osg::DrawElementsUInt> pyramidBase = pyramidCoreBase;

			if (factor != 0)
			{
				std::for_each(topBase->begin(), topBase->end(), [&](unsigned &i){ i += factor; });
				std::for_each(belowBase->begin(), belowBase->end(), [&](unsigned &i){ i += factor; });
				std::for_each(pyramidBase->begin(), pyramidBase->end(), [&](unsigned &i){ i += factor; });
			}

			m_geom->addPrimitiveSet(topBase.get());
			m_geom->addPrimitiveSet(belowBase.get());
			m_geom->addPrimitiveSet(pyramidBase.get());
		}
	}

	m_geom->setVertexArray(pVertices.get());
	m_geom->setColorArray(m_curColors.get());
	m_geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	osgUtil::SmoothingVisitor::smooth(*m_geom.get());
}

void CXBigGeometry::SetColor(const osg::Vec4& color)
{
	if (color == m_curColors->at(0)) return;

	(*m_curColors)[0].set(color._v[0], color._v[1], color._v[2], color._v[3]);
	m_geom->setColorArray(m_curColors.get());
	m_geom->setColorBinding(osg::Geometry::BIND_OVERALL);
}

void CXBigGeometry::SetCenter(const osg::Vec3Array &centers)
{
	if (*m_pVecCenter.get() == centers) return;

	osg::ref_ptr<osg::Vec3Array> newVectices = new osg::Vec3Array;
	for (auto iter = centers.begin(); iter != centers.end(); ++iter)
	{
		for (auto coreIter = m_pVecCore->begin(); coreIter != m_pVecCore->end(); ++coreIter)
			newVectices->push_back(*coreIter + *iter);
	}

	m_geom->setVertexArray(newVectices);
}

void CXBigGeometry::SetRadius(float radius)
{
	if (radius == m_curRadius) return;

	osg::Vec3Array* vectices = dynamic_cast<osg::Vec3Array*>(m_geom->getVertexArray());
	for (unsigned i=0; i!=vectices->size(); ++i)
	{
		(*vectices)[i].normalize();
		(*vectices)[i] *= radius;
	}
}

void CXBigGeometry::SetShape(Shape shape)
{
	if (shape == m_curShape) return;

	m_geom = new osg::Geometry;
	_Create();
}

void CXBigGeometry::_Create()
{
	m_geom = new osg::Geometry;

	switch (m_curShape)
	{
	case SpherePoints:
		_CreateSpherePoints(*m_pVecCenter.get(), m_curRadius, m_curFidelity);
		break;
	case Sphere:
		_CreateSphere(*m_pVecCenter.get(), m_curRadius, m_curFidelity);
		break;
	case Box:
		_CreateBox(*m_pVecCenter.get(), m_curRadius, m_curFidelity);
		break;
	case Cylinder:
		_CreateCylider(*m_pVecCenter.get(), m_curRadius, m_curFidelity);
		break;
	default: assert(!"error shape.");
	}
}
