#ifndef CRLBASEMAPCOORDINATE_H_H
#define CRLBASEMAPCOORDINATE_H_H

/*!
 *	@brief	display of point set in basemap
 *	@author	pezy
 *	@date	2016-05-03
 *	@see
 */

#include <osg/BoundingBox>
#include <osg/ref_ptr>
#include <osg/Array>
#include <string>

namespace osg { class LineWidth; class Group; class Switch; class Geode; class Geometry; };
class CXBaseMapWindow;
class CXWindowInfoBasemap;
class CX3DGlobalCoordMap;

class CXBasemapCoordinate
{
public:
	CXBasemapCoordinate();
	~CXBasemapCoordinate();

	void SetWinInfoAndCoordMap(CXWindowInfoBasemap* pWinInfo, CX3DGlobalCoordMap* pCoordMap);

	osg::ref_ptr<osg::Group> GetCoordinateAxis() { return m_pCoordSwitch; }
	const osg::BoundingBox& GetBoundBox() const { return m_boundingBox; }
	
	void ExpandBy(const osg::BoundingBox& boundingBox);
	void ResetBy(const osg::BoundingBox& boundingBox);
	void Clear() { m_boundingBox.init(); }
	void UpdateWindowInfo();

private:
	void _BuildCoordinateAxis();
	void _UpdateBoundingBox();
	void _CalcTickMarks();
	void _DrawXAxisLabel(const osg::BoundingBox& box, float fYMargin, float fHeightXMark);
	void _DrawYAxisLabel(const osg::BoundingBox& box, float fXMargin, float fWidthYMark);
	osg::BoundingBox _ExpandBox(const osg::BoundingBox& box);

	void _GetXMarkInfo(double dMaxX, const std::string& strFontName, float& fWidth, float& fHeight);
	void _GetYMarkInfo(double dMaxY, const std::string& strFontName, float& fWidth, float& fHeight);

	osg::Geometry* _CreateTickGeometry(osg::Vec3Array* pVertex);
	osg::Geometry* _CreateGridGeometry(osg::Vec3Array* pVertex);
	
private:
	CX3DGlobalCoordMap* m_pCoordMap = nullptr;
	CXWindowInfoBasemap* m_pWinInfo = nullptr;

	osg::BoundingBox m_boundingBox;
	osg::ref_ptr<osg::Geode> m_pCoordGeode;
	osg::ref_ptr<osg::Switch> m_pCoordSwitch;
	
	osg::ref_ptr<osg::Vec4Array> m_pCoordColor;
	osg::ref_ptr<osg::LineWidth> m_pBoundingBoxLineWidth;
};

#endif