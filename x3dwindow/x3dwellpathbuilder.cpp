#include "x3dwellpathbuilder.h"

#include "xglobal.h"
#include "xwell.h"
#include "xwellpath.h"
#include <osg/ComputeBoundsVisitor>
#include <osg/AutoTransform>
#include <osg/PositionAttitudeTransform>
#include "x3dbuilderfactory.h"
#include "x3dutility.h"

#include "qcolor.h"
#include "x3dwindow.h"
#include "x3dglobalcoordmap.h"
#include "xviewinfowellpath.h"
#include "xgraphicsapi.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CX3DWellPathBuilder)
{ EXWell, e3DWindow }
END_REGISTER_BUILDER_TO_FACTORY(CX3DWellPathBuilder)


CX3DWellPathBuilder::CX3DWellPathBuilder()
    : CX3DBuilderAbstract()
    , m_pX(nullptr)
    , m_pY(nullptr)
    , m_pZ(nullptr)
{
    m_bScalable = false;
}

CX3DWellPathBuilder::~CX3DWellPathBuilder()
{
    if (m_pX) { delete m_pX; m_pX = nullptr; }
    if (m_pY) { delete m_pY; m_pY = nullptr; }
    if (m_pZ) { delete m_pZ; m_pZ = nullptr; }
}

osg::BoundingBox CX3DWellPathBuilder::GetBoundBox()
{
    return m_BoundBox;
}

osg::ref_ptr<osg::Group> CX3DWellPathBuilder::Build(QUuid objId)
{
	m_p3DWin = dynamic_cast<CX3DWindow*>(m_pCurWin);
	if (!m_p3DWin)
		return nullptr;
	
	m_pViewInfo = dynamic_cast<CXViewInfoWellPath*>(m_p3DWin->GetObjectViewInfo(objId));
    if (!m_pViewInfo)
        return nullptr;

    if (!_InitData(objId))
        return nullptr;

    m_pWellPathGeode = new osg::Geode();
    m_pWellPathGeode->addDrawable(_CalcWellPillarGeometry().get());
    m_pWellPathGeode->addDrawable(_CalcLegendText().get());
    m_pWellPathGeode->setUserValue("objID", objId.toString().toStdString());

    if (!m_pBuilderNode)
        m_pBuilderNode = new osg::Group;

    m_pBuilderNode->addChild(m_pWellPathGeode);
    m_pBuilderNode->addChild(_BuildLegendSymbol());

    osg::ComputeBoundsVisitor cbVisitor;
    m_pBuilderNode->accept(cbVisitor);
    m_BoundBox = cbVisitor.getBoundingBox();

    return m_pBuilderNode;
}

void CX3DWellPathBuilder::UpdateNode(EEventType eType)
{
    if (eType == EDataChanged || eType == EInfoChanged)
    {
        m_pWellPathGeode->removeDrawables(0, m_pWellPathGeode->getNumDrawables());

        m_pWellPathGeode->addDrawable(_CalcWellPillarGeometry());
        m_pWellPathGeode->addDrawable(_CalcLegendText());
        
        m_pBuilderNode->removeChild(1);
        m_pBuilderNode->addChild(_BuildLegendSymbol());
    }
}

osg::ref_ptr<osgText::Text> CX3DWellPathBuilder::_CalcLegendText()
{
    if (!m_pViewInfo->GetWellNameVisible())
        return nullptr;

    // from viewinfo.
    int nFontSize = m_pViewInfo->GetWellNameFontSize();
    QString fontName = m_pViewInfo->GetWellNameFontFamily();
    QColor fontColor = m_pViewInfo->GetWellNameColor();
    
    osg::ref_ptr<osgText::Text> pWellLegend = new osgText::Text;
    pWellLegend->setUseVertexBufferObjects(true);
    pWellLegend->setFont(osgText::readFontFile("fonts/" + fontName.toStdString() + ".ttf"));
    pWellLegend->setText(osgText::String(m_pWell->GetObjectName().toStdString()));
    pWellLegend->setColor(osg::Vec4(fontColor.redF(), fontColor.greenF(), fontColor.blueF(), fontColor.alphaF()));
    pWellLegend->setCharacterSize(20 * nFontSize);
    pWellLegend->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
    pWellLegend->setAutoRotateToScreen(false);
    pWellLegend->setPosition(_GetWellHeaderPosition() + osg::Vec3(0.f, 100.f, 0.f));
    pWellLegend->setAlignment(osgText::Text::CENTER_CENTER);
    pWellLegend->setAxisAlignment(osgText::Text::SCREEN);

    return pWellLegend;
}

osg::ref_ptr<osg::Node> CX3DWellPathBuilder::_BuildLegendSymbol()
{
    if (!m_pViewInfo->GetWellSymbolVisible())
        return nullptr;

    // from viewinfo
    QColor color = m_pViewInfo->GetWellSymbolColor();
    int radius = m_pViewInfo->GetWellSymbolRadius();

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(67);
    (*vertices)[0].set(0.0f, 0.0f, 0.0f);
    for (unsigned int i = 1; i <= 65; ++i)
    {
        float angle = (float)(i - 1) * osg::PI / 32.0f;
        (*vertices)[i].set(radius * cosf(angle), radius * sinf(angle), 0.0f);
    }

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(1);
    (*normals)[0].set(0.0f, 0.0f, -1.0f);

    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(1);
    (*colors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray(vertices.get());
    geom->setNormalArray(normals.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geom->setColorArray(colors.get());
    geom->setColorBinding(osg::Geometry::BIND_OVERALL);
    geom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_FAN, 0, 67));

    osg::Geode* pGeode = new osg::Geode;
    pGeode->addDrawable(geom.get());

    osg::StateSet* pStateSet = pGeode->getOrCreateStateSet();
    pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    osg::ref_ptr<osg::AutoTransform> pAutoTransform = new osg::AutoTransform;

    pAutoTransform->setAutoScaleToScreen(true);
    pAutoTransform->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
    pAutoTransform->addChild(pGeode);
    pAutoTransform->setPosition(_GetWellHeaderPosition());

    return pAutoTransform;
}

std::vector<int> CX3DWellPathBuilder::_SegmentWellPillar(double *pX, double *pY, double *pZ, int nSampleNum, std::vector<std::pair<int, int> > &segment)
{
    std::vector<int> vecPoints;
    CXGraphicsAPI::SegmentSimplification(pX, pY, pZ, nSampleNum, vecPoints);

    std::pair<int, int> pa;
    for (int i = 0; i < vecPoints.size() - 1; ++i)
    {
        pa.first = vecPoints[i];
        pa.second = vecPoints[i + 1];
        segment.push_back(pa);
    }
    return vecPoints;
}

osg::ref_ptr<osg::Geometry> CX3DWellPathBuilder::_CalcWellPillarGeometry()
{
    std::vector<osg::Vec3f> circleVertex;

    // Get well path data
    unsigned int nNumber;
    double *pData = m_pWellPath->GetData(nNumber);

    osg::ref_ptr<osg::Geometry> pWellPillarGeometry = new osg::Geometry;
    pWellPillarGeometry->setUseVertexBufferObjects(true);
    osg::ref_ptr<osg::Vec3Array> pAllSegPillarVertex = new osg::Vec3Array();

    osg::ref_ptr<osg::Vec3Array> pAllSegPillarVertexNormal = new osg::Vec3Array();
    osg::ref_ptr<osg::Vec4Array>  pAllSegPillarVertexcolors = new osg::Vec4Array();

    float wellradius = m_pViewInfo->GetWellPathRadius();
    QColor wellPathColor = m_pViewInfo->GetWellPathColor();

    for (int i = 0; i <= 360; i += 10)
    {
        float curradians = osg::DegreesToRadians((float)i);
        osg::Vec3f oneCircleVertex(wellradius*cosf(curradians), wellradius*sinf(curradians), 0.0f);
        circleVertex.push_back(oneCircleVertex);
    }
    circleVertex.push_back(circleVertex[0]);
    
	double fZscale = m_p3DWin->GetZScale();
    //
    std::vector<int> inflectionIndex;
    std::vector<osg::Vec3f> segDir;
    Vec3d beginD, endD;
    osg::Vec3f beginVertex, endVertex;
    for (unsigned int i = 0; i < m_vecSegment.size(); i++)
    {
        inflectionIndex.push_back(m_vecSegment[i].first);
        int beginIndex = m_vecSegment[i].first;
        int endIndex = m_vecSegment[i].second;
        beginD.set(pData[3 * beginIndex], pData[3 * beginIndex + 1], pData[3 * beginIndex + 2]);
        m_pCoordMap->MapWorldToLocal(beginD, beginVertex);

        endD.set(pData[3 * endIndex], pData[3 * endIndex + 1], pData[3 * endIndex + 2]);
        m_pCoordMap->MapWorldToLocal(endD, endVertex);

        beginVertex[2] *= fZscale;
        endVertex[2] *= fZscale;

        osg::Vec3f dirVec = beginVertex - endVertex;
        dirVec.normalize();
        segDir.push_back(dirVec);


        if (i == m_vecSegment.size() - 1)
        {
            inflectionIndex.push_back(m_vecSegment[i].second);
            segDir.push_back(dirVec);
        }
    }
    int circleNum = circleVertex.size();

    for (unsigned int i = 0; i < inflectionIndex.size(); i++)
    {
        int curIndex = inflectionIndex[i];

        endD.set(pData[3 * curIndex], pData[3 * curIndex + 1], pData[3 * curIndex + 2]);
        m_pCoordMap->MapWorldToLocal(endD, endVertex);
        endVertex[2] *= fZscale;

        osg::Matrixd matScale;
        osg::Matrixd matTransVertex;

        matTransVertex.makeRotate(osg::Vec3f(0.0, 0.0, 1.0), segDir[i]);
        matTransVertex.postMultTranslate(endVertex);
        for (int j = 0; j < circleNum; j++)
        {
            osg::Vec3f CircleEndVertex = matTransVertex.preMult(circleVertex[j]);
            pAllSegPillarVertex->push_back(CircleEndVertex);
            osg::Vec3f normalVector = CircleEndVertex - endVertex;
            normalVector.normalize();
            pAllSegPillarVertexNormal->push_back(normalVector);
        }

    }

    std::vector<vector<int> >allIndex;
    for (int i = 0; i < inflectionIndex.size() - 1; i++)
    {
        std::vector<int>OneTriTripIndex;
        for (int j = 0; j < circleNum; j++)
        {

            int curIndex = i*(circleNum)+j;
            int curIndexNext = (i + 1)*(circleNum)+j;
            OneTriTripIndex.push_back(curIndex);
            OneTriTripIndex.push_back(curIndexNext);

        }
        allIndex.push_back(OneTriTripIndex);
        pAllSegPillarVertexcolors->push_back(osg::Vec4f((float)wellPathColor.redF(), (float)wellPathColor.greenF(), (float)wellPathColor.blueF(), (float)wellPathColor.alphaF()));
    }

    pWellPillarGeometry->setVertexArray(pAllSegPillarVertex.get());
    pWellPillarGeometry->setNormalArray(pAllSegPillarVertexNormal.get(), osg::Array::BIND_PER_VERTEX);
    pWellPillarGeometry->setColorArray(pAllSegPillarVertexcolors.get(), osg::Array::BIND_PER_PRIMITIVE_SET);

    for (int i = 0; i < allIndex.size(); i++)
    {
        pWellPillarGeometry->addPrimitiveSet(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_STRIP, allIndex[i].begin(), allIndex[i].end()));
    }
    return pWellPillarGeometry;
}

bool CX3DWellPathBuilder::_InitData(QUuid objID)
{
    m_pWell = dynamic_cast<CXWell*>(::GetObjectByID(objID));
    if (!m_pWell)
        return false;

    m_pWellPath = m_pWell->GetWellPath();
    if (!m_pWellPath)
        return false;

    unsigned int nSize;
    double *pData = m_pWellPath->GetData(nSize);
    if (!pData || nSize == 0)
        return false;

    unsigned int nPoint = nSize / 3;
    if (nPoint < 2)
        return false;

    m_pX = new double[nPoint];
    m_pY = new double[nPoint];
    m_pZ = new double[nPoint];

    for (uint i = 0; i != nPoint; ++i)
    {
        m_pX[i] = pData[3 * i + 0];
        m_pY[i] = pData[3 * i + 1];
        m_pZ[i] = pData[3 * i + 2];
    }

    vector<int> vecIndex;
    vecIndex = _SegmentWellPillar(m_pX, m_pY, m_pZ, nPoint, m_vecSegment);

    return true;
}

osg::Vec3 CX3DWellPathBuilder::_GetWellHeaderPosition()
{
    float fZScale = 1.f;
    if (e3DWindow == m_pCurWin->GetWindowType())
    {
        CX3DWindow *p3DWindow = dynamic_cast<CX3DWindow*>(m_pCurWin);
        fZScale = p3DWindow->GetZScale();
    }

    double dX, dY;
    m_pWell->GetWellPosition(dX, dY);
    double dZ = m_pWell->GetZMin();

    osg::Vec3 vecWellPosition;
    m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dY, dZ), vecWellPosition);
    vecWellPosition.z() *= fZScale;

    return vecWellPosition;
}