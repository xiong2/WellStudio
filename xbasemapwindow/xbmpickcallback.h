#ifndef XBMSEISMICSECTIONCALLBACK_H
#define XBMSEISMICSECTIONCALLBACK_H

/*!
 *	@brief	process cull callback on base map.
 *	@author	pezy
 *	@date	2016-06-30
 *	@see
 */

#include <osg/NodeCallback>
#include <osg/NodeVisitor>
#include <osg/Node>
class CX3DPickableBuilderAbstract;

class CXBMPickCallback : public osg::NodeCallback
{
public:
	CXBMPickCallback(CX3DPickableBuilderAbstract *pBuilder);
	~CXBMPickCallback();

	void operator()(osg::Node* node, osg::NodeVisitor* nv) override;

	bool SetActive(bool bActive);
	void SetSeismicSectionTrace(int iInline, int iXline);
	int GetSeismicSectionTrace();

	int GetPivotIndexFromPos(const osg::Vec3& pos, float minDist);
	void DragPivot(int iPivotIndex, const osg::Vec3& toPos);
	void FixedPivot();
	void SetLastPivotIndex(int iPivotIndex) { m_iCurrentPivot = iPivotIndex; }

	bool IsPolygonSelfIntersection(int index, const osg::Vec3& pos);

private:
	int _CheckPivot(const osg::Vec3& pos, float minDist);

private:
	CX3DPickableBuilderAbstract* m_pBuilder;

	osg::ref_ptr<osg::Geometry> m_pGeometry;
	osg::ref_ptr<osg::Vec3Array> m_pVertex;

	int m_iCurrentPivot = -1;
};

#endif // KEBMSEISMICSECTIONCALLBACK_H
