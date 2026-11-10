#ifndef X3DWELLPATHBUILDER_H_H
#define X3DWELLPATHBUILDER_H_H

#include "x3dbuilder.h"
#include <osg/Node>
#include <osgText/Text>
#include <vector>
#include <osg/Geometry>
#include <osg/MatrixTransform>

class CXWell;
class CXWellPath;
class CXViewInfoWellPath;
class CX3DWindow;

class CX3DWellPathBuilder : public CX3DBuilderAbstract
{
public:
    CX3DWellPathBuilder();
    ~CX3DWellPathBuilder();

    virtual osg::ref_ptr<osg::Group> Build(QUuid objId);
    virtual void UpdateNode(EEventType eType);
    virtual osg::BoundingBox GetBoundBox();

    static std::vector<int> _SegmentWellPillar(double *pX, double *pY, double *pZ, int nSampleNum, std::vector<std::pair<int, int> > &segment);

private:
    bool _InitData(QUuid objID);
    osg::Vec3 _GetWellHeaderPosition();
    
    osg::ref_ptr<osg::Geometry> _CalcWellPillarGeometry();
    osg::ref_ptr<osgText::Text> _CalcLegendText();
    osg::ref_ptr<osg::Node> _BuildLegendSymbol();

private:
    CXWell *m_pWell = nullptr;
    CXWellPath* m_pWellPath = nullptr;
    CXViewInfoWellPath* m_pViewInfo = nullptr;
	CX3DWindow* m_p3DWin = nullptr;

    std::vector<std::pair<int, int> > m_vecSegment;

    double *m_pX;
    double *m_pY;
    double *m_pZ;

    osg::ref_ptr<osg::Geode> m_pWellPathGeode;
};
#endif