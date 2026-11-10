#ifndef XBMPRESTACKGATHERBUILDER_H
#define XBMPRESTACKGATHERBUILDER_H

#include "x3dbuilder.h"
#include <osg/Geometry>

class CXViewInfoPreStackGather;
class CXPreStackGather;

/**
@class CXBMPreStackGatherBuilder provided in the file "xbmprestackgatherbuilder.h"
@brief The class provides the display of CXPreStackGather
@author pezy
@date 2017-10-09
@sa CXPreStackGather
*/
class CXBMPreStackGatherBuilder : public CX3DBuilderAbstract
{
public:
	CXBMPreStackGatherBuilder();
	~CXBMPreStackGatherBuilder();

	osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	void UpdateNode(EEventType eType) override;

private:
	osg::Geode* _BuildWhole();
	osg::Geode* _BuildSingle();
	osg::Geometry* _BuildWholeSourcePoints();
	osg::Geometry* _BuildWholeDetectPoints();
	osg::Geometry* _BuildSingleSourcePoints();
	osg::Geometry* _BuildSingleDetectPoints();
	bool _UpdateSingleSourceShot(osg::Vec3Array* pVertex);
	bool _UpdateSingleDetectShot(osg::Vec3Array* pVertex);

	static void _BuildGeometry(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array *pVertex, int type, int size, const QColor& color);
	static void _BuildPoint(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array *pVertex, int size, const QColor& color);
	static void _BuildCross(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array *pVertex, int size, const QColor& color);
	static void _BuildTriangle(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array *pVertex, int size, const QColor& color, bool bFill = false);
	static void _BuildDiamond(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array *pVertex, int size, const QColor& color, bool bFill = false);
	static void _BuildSquare(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array *pVertex, int size, const QColor& color, bool bFill = false);
	static void _BuildCircle(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array *pVertex, int size, const QColor& color, bool bFill = false);

	CXPreStackGather *m_pPreStackGather = nullptr;
	CXViewInfoPreStackGather *m_pViewInfo = nullptr;

	int m_sourceSize = 0;
	int m_detectSize = 0;
	int m_sourceShape = 0;
	int m_detectShape = 0;

	osg::ref_ptr<osg::Switch> m_pSwitch;
	osg::ref_ptr<osg::Geode> m_pWholeGeode;
	osg::ref_ptr<osg::Geode> m_pSingleGeode;
	osg::ref_ptr<osg::Geometry> m_pWholeSourcePointGeom;
	osg::ref_ptr<osg::Geometry> m_pWholeDetectPointGeom;
	osg::ref_ptr<osg::Geometry> m_pSingleSourcePointGeom;
	osg::ref_ptr<osg::Geometry> m_pSingleDetectPointGeom;
};

#endif // XBMPRESTACKGATHERBUILDER_H
