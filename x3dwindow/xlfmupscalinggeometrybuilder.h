#ifndef XLFMUPSCALINGGEOMETRYBUILDER_H
#define XLFMUPSCALINGGEOMETRYBUILDER_H

#include "x3dbuilder.h"

/*!
 *  @brief  The class is a node builder for LFM Upscale Geometry
 *  @author pezy
 *  @data   2015-12-21
 *  @see
 */

class CXLFMUpscalingGeometry;

class CXLFMUpscalingGeometryBuilder : public CX3DBuilderAbstract
{
public:
    CXLFMUpscalingGeometryBuilder();
    ~CXLFMUpscalingGeometryBuilder();

    virtual osg::ref_ptr<osg::Group> Build(QUuid objId) override;
    virtual void UpdateNode(EEventType eType) override;

private:
    void _BuildVertices();
    void _BuildIndices();
    void _BuildColor();
    void _BuildNormal();

	void _UpdateColor();

    CXLFMUpscalingGeometry* m_pUpscaling = nullptr;

    osg::ref_ptr<osg::Geometry> m_pCellGeom;
    osg::ref_ptr<osg::Geometry> m_pGridGeom;
    osg::ref_ptr<osg::Vec3Array> m_pVertices;
};

#endif // KELFMUPSCALINGGEOMETRYBUILDER_H
