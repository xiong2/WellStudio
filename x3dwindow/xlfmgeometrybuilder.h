#ifndef XLFMGEOMETRYBUILDER_H
#define XLFMGEOMETRYBUILDER_H

#include "x3dbuilder.h"
#include "xseismicutmtool.h"
#include <osg/Geometry>
#include <vector>
#include <unordered_set>
#include <QBitArray>

/*!
*	@brief	The class is a node builder for LFM Geometry
*	@author	pezy
*	@data	2015-12-01
*	@see
*/

class CXLFMGeometry;
class CXLFMAttribute;
class CXSeismicUTMTool;
class CXViewInfoLFMGeometry;

class CXLFMGeometryBuilder : public CX3DBuilderAbstract
{
public:
	CXLFMGeometryBuilder();
	~CXLFMGeometryBuilder();

	virtual osg::ref_ptr<osg::Group> Build(QUuid objId) override;
	virtual void UpdateNode(EEventType eType) override;

private:
    void _InitData();
    void _InitOrUpdateViewInfo();
    void _UpdateGridLine(int iZoneIndex);

    void _CalcTopVerticesAndTexCoord(int iZoneIndex, float* pData);
    void _CalcBottomVerticesAndTexCoord(int iZoneIndex, float* pData);
    void _CalcSideVerticesAndTexCoord(int iZoneIndex, float* pData, int k);
    void _UpdateVerticesAndTexCoord(int iZoneIndex);
    void _UpdateAttributeTexCoord(int iZoneIndex);

    void _UpdateTopTexCoord(int iZoneIndex, float *pAttributeData);
    void _UpdateBottomTexCoord(int iZoneIndex, float *pAttributeData);
    void _UpdateSideTexCoord(int iZoneIndex, float *pAttributeData, int k);

	void _CalcIndices(int iZoneIndex);
    void _CalcSurfaceIndices(osg::ref_ptr<osg::Geometry>& pSurfaceGeom);
    void _CalcSideIndices(osg::ref_ptr<osg::Geometry>& pSurfaceSideGeom, int minK, int maxK);

    void _CalcSurfaceGridlineIndices(int iZoneIndex);
    void _CalcSideGridlineIndices(int iZoneIndex);

    void _CalcSurfaceNormal(int iZoneIndex, bool bTop);
    void _CalcSideNormal(int iZoneIndex);

    void _UpdateColors(int iZoneIndex);

	bool _CalcValidMap(float* pData);
    void _CalcEdgeIndex();
    double _CalcVertexAttributeValue(int nI, int nJ, double dI, double dJ, float *pData);

    bool _HasAttribute();

	osg::ref_ptr<osg::Geode> _BuildLFMZone(int iZoneIndex);

private:
	std::vector<osg::ref_ptr<osg::Geode>> m_vecGeodeZone;

	std::vector<osg::ref_ptr<osg::Geometry>> m_vecSurfaceTop;
	std::vector<osg::ref_ptr<osg::Geometry>> m_vecSurfaceBottom;
	std::vector<osg::ref_ptr<osg::Geometry>> m_vecSurfaceSide;

	std::vector<osg::ref_ptr<osg::Geometry>> m_vecGridLineTop;
	std::vector<osg::ref_ptr<osg::Geometry>> m_vecGridLineBottom;
	std::vector<osg::ref_ptr<osg::Geometry>> m_vecGridLineHorizontalSlice;
	std::vector<osg::ref_ptr<osg::Geometry>> m_vecGridLineVerticalSlice;

	std::vector<osg::ref_ptr<osg::Vec3Array>> m_vecVerticesTop;
	std::vector<osg::ref_ptr<osg::Vec3Array>> m_vecVerticesBottom;
	std::vector<osg::ref_ptr<osg::Vec3Array>> m_vecVerticesSide;

	std::vector<osg::ref_ptr<osg::FloatArray>> m_vecTexCoordTop;
	std::vector<osg::ref_ptr<osg::FloatArray>> m_vecTexCoordBottom;
	std::vector<osg::ref_ptr<osg::FloatArray>> m_vecTexCoordSide;

	std::vector<osg::ref_ptr<osg::StateSet>> m_vecStateSet;

	CXLFMGeometry* m_pLFM = nullptr;
    CXLFMAttribute* m_pLFMAttribute = nullptr;
	CXViewInfoLFMGeometry* m_pViewInfo = nullptr;
	
    QBitArray m_validBitMap;
    QBitArray m_validDataBitMap;

    std::vector<int> m_vecEdgeIndex;
    std::vector<std::unordered_set<int>> m_vecGridIndex;

    CXSeismicUTMTool m_utm;
    int m_nI = 0;
    int m_nJ = 0;

    int m_minNI = 0;
    int m_maxNI = 1;
    int m_minNJ = 0;
    int m_maxNJ = 1;

    double m_dDataMin = 0.0;
    double m_dDataMax = 0.0;

    double m_dAttributeDataMin = 0.0;
    double m_dAttributeDataMax = 0.0;

	std::vector<bool> m_vecZoneDisplay;
	std::vector<QRgb> m_vecZoneColor;
	std::vector<int> m_vecZoneMinSlice;
	std::vector<int> m_vecZoneMaxSlice;

	QStringList m_listZoneName;
};

#endif // KELFMGEOMETRYBUILDER_H
