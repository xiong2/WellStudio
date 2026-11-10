#ifndef X3DSURFACEBUILDER_H
#define X3DSURFACEBUILDER_H


#include "x3dbuilder.h"
#include <osg/LineStipple>
#include "xutmtool.h"
class CX3DSurface;
class CXViewInfoSurface;

struct CXCell
{
	uint left = 0;
	uint ifLeft = 0;
	uint right = 0;
	uint ifRight = 0;
	uint top = 0;
	uint ifTop = 0;
	uint bottom = 0;
	uint ifBottom = 0;
	uint slice = 0;
	uint ifSlice = 0;
	bool ifTraced = false;
	uint traceCount = 0; //count==1 mean half cell has been traced ,count==2 mean whole cell is traced.
	uint ifLeftTop = 0;
	uint ifRightBottom = 0;
};

struct CRLContourInfo {
	QColor m_MajorColor;
	QColor m_MinorColor;
	Qt::PenStyle m_MajorStyle;
	Qt::PenStyle m_MinorStyle;
	int m_MajorWeight;
	int m_MinorWeight;
	int m_MajorInterval;
};

class CX3DSurfaceBuilder : public CX3DBuilderAbstract
{
public:
	CX3DSurfaceBuilder();
	~CX3DSurfaceBuilder();

	virtual osg::ref_ptr<osg::Group> Build(QUuid objId);
	virtual void UpdateNode(EEventType eType);

private:
	osg::Geometry* _BuildGeometry();
	osg::Geometry* _BuildFractureGeometry();
	osg::Geometry* _BuildPointsGeometry();
	bool _HasAttribute();
	bool _CheckDataValid();
	osg::Vec3d _IJToWorld(float* pData, double dI, double dJ);

	osg::Vec3Array* _CalcVertex();
	osg::Vec3Array* _CalcNormal();
	osg::FloatArray* _CalcTexcoord();
	osg::StateSet* _CalcStateSet();
	const std::vector<osg::ref_ptr<osg::DrawElementsUInt>>& _CalcIndices();

	osg::Uniform* _BuildColorTable();
	osg::Uniform* _BuildLighting();
	osg::Program* _BuildShaderProgram();

	void _CheckFractureDisplay();
	void _CheckPointsDisplay();
	void _UpdateColor();

	//ios trace
	osg::ref_ptr<osg::Geode> _CalIOSCurve(float plotValue);
	bool _TraceCell(osg::Vec3Array * vTrace, std::vector<int> &tracedCell, int cellIndex, int preCellIndex, float plotValue, int traceDir = 15);
	osg::Vec3f _ComputeTracePoint(osg::Vec3f startPoint, osg::Vec3f endPoint, float plotValue);
	osg::ref_ptr<osg::Switch> _BuildIOSCurve(float startValue, float endValue, float incValue, CRLContourInfo contourInfo);
	osg::LineStipple* SetLineStyle(Qt::PenStyle curStyle);
	void SegmentIOSCurve(osg::Vec3Array *tracePoint, std::vector<std::pair<int, int> > &annotationIndex, osg::Vec3 &beginVertex, osg::Vec3 &endVertex);
	//void TopologySurfaceAsTriSurface();
	//ios trace
private:
	CX3DSurface* m_pSurface = nullptr;
	CX3DSurface* m_pSurfaceAtt = nullptr;
	CXViewInfoSurface* m_pViewInfo = nullptr;
	CXUTMTool m_utm;
	int m_nI;
	int m_nJ;
	QList<bool> m_listValid;

	osg::ref_ptr<osg::Geode> m_pGeode;
	osg::ref_ptr<osg::Geometry> m_pGeom;
	osg::ref_ptr<osg::Vec3Array> m_pVertices;
	osg::ref_ptr<osg::Vec3Array> m_pNormals;
	std::vector<osg::ref_ptr<osg::DrawElementsUInt>> m_vecDrawElements;
	osg::ref_ptr<osg::FloatArray> m_pTexCoord;
	osg::ref_ptr<osg::StateSet> m_pStateSet;

	osg::ref_ptr<osg::Geometry> m_pFracGeom;
	osg::ref_ptr<osg::Geometry> m_pPointsGeom;

	osg::ref_ptr<osg::Switch> m_pIosSwitch;
	osg::ref_ptr<osg::Uniform> m_ulightState;
	osg::ref_ptr<osg::Uniform> m_uColorTable;
	//ios trace
	std::vector<CXCell> m_vCell;
};

#endif // RL3DSURFACEBUILDER_H
