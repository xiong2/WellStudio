#ifndef X3DGEOBODYBUILDER_H
#define X3DGEOBODYBUILDER_H

#include "x3dbuilder.h"

/*!
 *	@brief	The class is a node builder for Geobody
 *	@author	pezy
 *	@data	2015-11-23
 *	@see
 */

class CXGeobody;
class CXViewInfoObject;
class CX3DGeobodyBuilder : public CX3DBuilderAbstract
{
public:
	CX3DGeobodyBuilder();
	~CX3DGeobodyBuilder();

	virtual osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	virtual void UpdateNode(EEventType eType) override;

private:
	void _BuildVertices();
	void _BuildIndices();
	void _BuildColor();
	void _BuildNormal();

	void _CalcUTMDirection();
	void _PushCellVerticesToGeometryByCentral(double dX, double dY, double dZ);

	osg::ref_ptr<osg::Vec3Array> m_pVertices;
	osg::ref_ptr<osg::Geometry> m_pCellGeom;
	const int nCubeIndex = 8;

	CXGeobody* m_pGeobody = nullptr;
	
	//		   3--------2           
	//		  /|       /|          
	//		 / |      / |         
	//		0--+-----1  |        
	//		|  |     |  |       ^   ^
	//		|  7-----+--6       |  /
	//		| /      | /        Z Crossline
	//		|/       |/         |/
	//		4--------5          0---Inline---->

	osg::Vec3 m_pVector02;
	osg::Vec3 m_pVector13;

	double m_offsetK = 0.0;
};

#endif // KE3DGEOBODYBUILDER_H
