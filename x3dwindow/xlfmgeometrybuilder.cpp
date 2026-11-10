#include "xlfmgeometrybuilder.h"

#include <qset.h>
#include <osg/LineWidth>
#include <osgUtil/SmoothingVisitor>

#include "x3dbuilderfactory.h"
#include "xlfmgeometry.h"
#include "xglobal.h"
#include "x3dglobalcoordmap.h"
#include "xviewinfolfmgeometry.h"
#include "xcolormap.h"
#include "xdbio.h"
#include "xlfmattribute.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXLFMGeometryBuilder)
{ EXLowFrequencyModel, e3DWindow }
END_REGISTER_BUILDER_TO_FACTORY(CXLFMGeometryBuilder)

CXLFMGeometryBuilder::CXLFMGeometryBuilder()
: CX3DBuilderAbstract()
{

}

CXLFMGeometryBuilder::~CXLFMGeometryBuilder()
{

}

osg::ref_ptr<osg::Group> CXLFMGeometryBuilder::Build(QUuid objId)
{
    if (!m_pBuilderNode)
    {
        m_pBuilderNode = new osg::Group;
    }

    m_pLFM = dynamic_cast<CXLFMGeometry*>(::GetObjectByID(objId));
    if (!m_pLFM)
		return nullptr;

    _InitData();

    m_pViewInfo = dynamic_cast<CXViewInfoLFMGeometry*>(m_pCurWin->GetObjectViewInfo(objId));
    if (!m_pViewInfo)
		return nullptr;

    _InitOrUpdateViewInfo();

	for (int i = 0; i != m_vecZoneDisplay.size(); ++i)
	{
		if (m_vecZoneDisplay.at(i))
		{
			m_pBuilderNode->addChild(_BuildLFMZone(i));
			m_pBuilderNode->dirtyBound();
		}
	}

    return m_pBuilderNode;
}

void CXLFMGeometryBuilder::UpdateNode(EEventType eType)
{
	if (eType == EInfoChanged)
	{
		_InitOrUpdateViewInfo();

		m_pBuilderNode->removeChildren(0, m_pBuilderNode->getNumChildren());

		for (size_t i = 0; i != m_vecZoneDisplay.size(); ++i)
		{
			if (m_vecZoneDisplay.at(i))
			{
				if (m_vecGeodeZone.at(i))
					m_pBuilderNode->addChild(m_vecGeodeZone.at(i));
				else
					m_pBuilderNode->addChild(_BuildLFMZone(i));

				_UpdateVerticesAndTexCoord(i);

				if (_HasAttribute())
				{
					_UpdateAttributeTexCoord(i);
				}

				_CalcIndices(i);
				_UpdateColors(i);
				_UpdateGridLine(i);
				
			}
		}
	}
	else if (eType == EColormapChanged)
	{
		for (size_t i = 0; i != m_vecZoneDisplay.size(); ++i)
		{
			if (m_vecZoneDisplay.at(i))
			{
				if (_HasAttribute())
				{
					_UpdateAttributeTexCoord(i);
				}
				else
				{
					_UpdateVerticesAndTexCoord(i);
				}

				_UpdateColors(i);
			}
		}
	}
}

void CXLFMGeometryBuilder::_InitData()
{
    m_utm = m_pLFM->GetUTM();
    m_nI = m_utm.GetNI();
    m_nJ = m_utm.GetNJ();
    
    m_pLFM->GetDataRange(m_dDataMin, m_dDataMax);
	m_listZoneName = m_pLFM->GetZoneNameList();
}

void CXLFMGeometryBuilder::_InitOrUpdateViewInfo()
{
	Q_ASSERT(m_pViewInfo);

    m_utm.LineToIJ(m_pViewInfo->GetMinInline(), m_pViewInfo->GetMinCrossline(), m_minNI, m_minNJ);
    m_utm.LineToIJ(m_pViewInfo->GetMaxInline(), m_pViewInfo->GetMaxCrossline(), m_maxNI, m_maxNJ);

	m_vecZoneDisplay = m_pViewInfo->GetVecZoneDisplay();
	m_vecZoneColor = m_pViewInfo->GetVecZoneColor();
	m_vecZoneMinSlice = m_pViewInfo->GetVecZoneMinSlice();
	m_vecZoneMaxSlice = m_pViewInfo->GetVecZoneMaxSlice();

	m_vecGeodeZone.resize(m_vecZoneDisplay.size());

	m_vecSurfaceTop.resize(m_vecZoneDisplay.size());
	m_vecSurfaceBottom.resize(m_vecZoneDisplay.size());
	m_vecSurfaceSide.resize(m_vecZoneDisplay.size());

	m_vecGridLineTop.resize(m_vecZoneDisplay.size());
	m_vecGridLineBottom.resize(m_vecZoneDisplay.size());
	m_vecGridLineHorizontalSlice.resize(m_vecZoneDisplay.size());
	m_vecGridLineVerticalSlice.resize(m_vecZoneDisplay.size());

	m_vecVerticesTop.resize(m_vecZoneDisplay.size());
	m_vecVerticesBottom.resize(m_vecZoneDisplay.size());
	m_vecVerticesSide.resize(m_vecZoneDisplay.size());

	m_vecTexCoordTop.resize(m_vecZoneDisplay.size());
	m_vecTexCoordBottom.resize(m_vecZoneDisplay.size());
	m_vecTexCoordSide.resize(m_vecZoneDisplay.size());

	m_vecStateSet.resize(m_vecZoneDisplay.size());
	m_vecGridIndex.resize(m_vecZoneDisplay.size());
}

void CXLFMGeometryBuilder::_UpdateGridLine(int iZoneIndex)
{
    Q_ASSERT(m_pViewInfo);

    QColor lineColor = m_pViewInfo->GetLineColor();

    osg::ref_ptr<osg::Vec4Array> pColorArray = new osg::Vec4Array;
    pColorArray->push_back(osg::Vec4(lineColor.redF(), lineColor.greenF(), lineColor.blueF(), lineColor.alphaF()));

	osg::ref_ptr<osg::Geode>& pGeode = m_vecGeodeZone.at(iZoneIndex);
	osg::ref_ptr<osg::Geometry>& pTopGridLine = m_vecGridLineTop.at(iZoneIndex);
	osg::ref_ptr<osg::Geometry>& pBottomGridLine = m_vecGridLineBottom.at(iZoneIndex);
	osg::ref_ptr<osg::Geometry>& pSideHorizontalGridLine = m_vecGridLineHorizontalSlice.at(iZoneIndex);
	osg::ref_ptr<osg::Geometry>& pSideVerticalGridLine = m_vecGridLineVerticalSlice.at(iZoneIndex);

	pTopGridLine->setColorArray(pColorArray.get(), osg::Array::BIND_OVERALL);
	pBottomGridLine->setColorArray(pColorArray.get(), osg::Array::BIND_OVERALL);
	pSideHorizontalGridLine->setColorArray(pColorArray.get(), osg::Array::BIND_OVERALL);
	pSideVerticalGridLine->setColorArray(pColorArray.get(), osg::Array::BIND_OVERALL);

	pGeode->removeDrawable(pTopGridLine);
	pGeode->removeDrawable(pBottomGridLine);
	pGeode->removeDrawable(pSideHorizontalGridLine);
	pGeode->removeDrawable(pSideVerticalGridLine);

    if (m_pViewInfo->GetDisplayTopAndBottomLine())
    {
		pGeode->addDrawable(pTopGridLine);
		pGeode->addDrawable(pBottomGridLine);
    }

    if (m_pViewInfo->GetDisplayHorizontalSideLine())
    {
		pGeode->addDrawable(pSideHorizontalGridLine);
    }

    if (m_pViewInfo->GetDisplayVerticalSideLine())
    {
		pGeode->addDrawable(pSideVerticalGridLine);
    }

    osg::LineWidth* linewidth = new osg::LineWidth();
    linewidth->setWidth(m_pViewInfo->GetLineSize());

    pTopGridLine->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);
    pBottomGridLine->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);
    pSideHorizontalGridLine->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);
	pSideVerticalGridLine->getOrCreateStateSet()->setAttributeAndModes(linewidth, osg::StateAttribute::ON);
}

bool CXLFMGeometryBuilder::_CalcValidMap(float* pData)
{
    bool bHasValid = false;

    float fInvalid = ::g_dInvalidData;
    float fInvalidEPS = ::GetEPSofInvalidData(fInvalid);

    m_validDataBitMap.resize(m_nI * m_nJ);

    for (auto i = 0; i != m_validDataBitMap.size(); ++i)
    {
        bool bValid = !(qAbs(pData[i] - fInvalid) < fInvalidEPS);
        m_validDataBitMap.setBit(i, bValid);
        bHasValid |= bValid;
    }

    return bHasValid;
}

double CXLFMGeometryBuilder::_CalcVertexAttributeValue(int nI, int nJ, double dI, double dJ, float *pData)
{
	//    J --->
	//
    //    3     2 (trace)
    // I  +-----+
    // |  |     |
    // |  |  +--+---> vertex
    // V  |     |
    //    +-----+
    //    0     1 (trace)

	double dZSum = 0.0;
	int nCount = 0;

	auto _AccumulateTraceZValue = [&](double i, double j) -> double
	{
		int index = qRound(qBound(0., i, m_nI - 1.)) * m_nJ + qRound(qBound(0., j, m_nJ - 1.));
		if (m_validDataBitMap.testBit(index))
		{
			++nCount;
			return pData[index];
		}
		return 0.0;
	};

	dZSum += _AccumulateTraceZValue(dI - 0.5, dJ - 0.5); // 3
    dZSum += _AccumulateTraceZValue(dI - 0.5, dJ + 0.5); // 2
    dZSum += _AccumulateTraceZValue(dI + 0.5, dJ + 0.5); // 1
    dZSum += _AccumulateTraceZValue(dI + 0.5, dJ - 0.5); // 0

    return nCount != 0 ? dZSum / nCount : 0.;
}

void CXLFMGeometryBuilder::_CalcTopVerticesAndTexCoord(int iZoneIndex, float* pData)
{
	osg::ref_ptr<osg::Vec3Array>& pVerticesTop = m_vecVerticesTop.at(iZoneIndex);
	pVerticesTop = new osg::Vec3Array((m_nI + 1) * (m_nJ + 1));

    m_vecSurfaceTop.at(iZoneIndex)->setVertexAttribArray(0, pVerticesTop.get(), osg::Array::BIND_PER_VERTEX);
    m_vecGridLineTop.at(iZoneIndex)->setVertexArray(pVerticesTop.get());

	osg::ref_ptr<osg::FloatArray>& pTexCoordTop = m_vecTexCoordTop.at(iZoneIndex);
	pTexCoordTop = new osg::FloatArray((m_nI + 1) * (m_nJ + 1));

	m_vecSurfaceTop.at(iZoneIndex)->setVertexAttribArray(2, pTexCoordTop.get(), osg::Array::BIND_PER_VERTEX);

    for (auto i = 0; i <= m_nI; ++i)
    {
        for (auto j = 0; j <= m_nJ; ++j)
        {
            int index = i * (m_nJ + 1) + j;

            if (!m_validBitMap.testBit(index)) continue;
            
            osg::Vec3d vecWorld;
            vecWorld[2] = _CalcVertexAttributeValue(m_nI, m_nJ, i - 0.5, j - 0.5, pData);
            m_utm.IJToXY2(i - 0.5, j - 0.5, vecWorld[0], vecWorld[1]);

            osg::Vec3 vecLocal;
            m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);

            (*pVerticesTop)[index].set(vecLocal);
            (*pTexCoordTop)[index] = (qBound(m_dDataMin, vecWorld[2], m_dDataMax) - m_dDataMin) / (m_dDataMax - m_dDataMin);
        }
    }
}

void CXLFMGeometryBuilder::_CalcBottomVerticesAndTexCoord(int iZoneIndex, float* pData)
{
	osg::ref_ptr<osg::Vec3Array>& pVerticesBottom = m_vecVerticesBottom.at(iZoneIndex);
    pVerticesBottom = new osg::Vec3Array((m_nI + 1) * (m_nJ + 1));

	m_vecSurfaceBottom.at(iZoneIndex)->setVertexAttribArray(0, pVerticesBottom.get(), osg::Array::BIND_PER_VERTEX);
	m_vecGridLineBottom.at(iZoneIndex)->setVertexArray(pVerticesBottom.get());
	
	osg::ref_ptr<osg::FloatArray>& pTexCoordBottom = m_vecTexCoordBottom.at(iZoneIndex);
	pTexCoordBottom = new osg::FloatArray((m_nI + 1) * (m_nJ + 1));

	m_vecSurfaceBottom.at(iZoneIndex)->setVertexAttribArray(2, pTexCoordBottom.get(), osg::Array::BIND_PER_VERTEX);

    for (auto i = 0; i <= m_nI; ++i)
    {
        for (auto j = 0; j <= m_nJ; ++j)
        {
            int index = i * (m_nJ + 1) + j;

            if (!m_validBitMap.testBit(index)) continue;
            
            osg::Vec3d vecWorld;
            m_utm.IJToXY2(i - 0.5, j - 0.5, vecWorld[0], vecWorld[1]);
			vecWorld[2] = _CalcVertexAttributeValue(m_nI, m_nJ, i - 0.5, j - 0.5, pData);

            osg::Vec3 vecLocal;
            m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);

            (*pVerticesBottom)[index].set(vecLocal);
            (*pTexCoordBottom)[index] = (qBound(m_dDataMin, vecWorld[2], m_dDataMax) - m_dDataMin) / (m_dDataMax - m_dDataMin);
        }
    }
}

void CXLFMGeometryBuilder::_CalcSideVerticesAndTexCoord(int iZoneIndex, float* pData, int k)
{
    for (decltype(m_vecEdgeIndex.size()) idx = 0; idx != m_vecEdgeIndex.size(); ++idx)
    {
        int i = m_vecEdgeIndex.at(idx) / (m_nJ + 1);
        int j = m_vecEdgeIndex.at(idx) % (m_nJ + 1);

        osg::Vec3d vecWorld;
        m_utm.IJToXY2(i - 0.5, j - 0.5, vecWorld[0], vecWorld[1]);
		vecWorld[2] = _CalcVertexAttributeValue(m_nI, m_nJ, i - 0.5, j - 0.5, pData);

        osg::Vec3 vecLocal;
        m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);

        (*m_vecVerticesSide.at(iZoneIndex))[k * m_vecEdgeIndex.size() + idx].set(vecLocal);
		(*m_vecTexCoordSide.at(iZoneIndex))[k * m_vecEdgeIndex.size() + idx] = (qBound(m_dDataMin, vecWorld[2], m_dDataMax) - m_dDataMin) / (m_dDataMax - m_dDataMin);
	}
}

void CXLFMGeometryBuilder::_UpdateTopTexCoord(int iZoneIndex, float *pAttributeData)
{
	osg::ref_ptr<osg::FloatArray>& pTexCoordTop = m_vecTexCoordTop.at(iZoneIndex);
    Q_ASSERT(pTexCoordTop);

    for (auto i = 0; i <= m_nI; ++i)
    {
        for (auto j = 0; j <= m_nJ; ++j)
        {
            int index = i * (m_nJ + 1) + j;

            if (!m_validBitMap.testBit(index)) continue;
            double dAttributeValue = _CalcVertexAttributeValue(m_nI, m_nJ, i - 0.5, j - 0.5, pAttributeData);
            dAttributeValue = qBound(m_dAttributeDataMin, dAttributeValue, m_dAttributeDataMax);
            (*pTexCoordTop)[index] = (dAttributeValue - m_dAttributeDataMin) / (m_dAttributeDataMax - m_dAttributeDataMin);
        }
    }
}

void CXLFMGeometryBuilder::_UpdateBottomTexCoord(int iZoneIndex, float *pAttributeData)
{
	osg::ref_ptr<osg::FloatArray>& pTexCoordBottom = m_vecTexCoordTop.at(iZoneIndex);
    Q_ASSERT(pTexCoordBottom);

    for (auto i = 0; i <= m_nI; ++i)
    {
        for (auto j = 0; j <= m_nJ; ++j)
        {
            int index = i * (m_nJ + 1) + j;

            if (!m_validBitMap.testBit(index)) continue;
            double dAttributeValue = _CalcVertexAttributeValue(m_nI, m_nJ, i - 0.5, j - 0.5, pAttributeData);
            dAttributeValue = qBound(m_dAttributeDataMin, dAttributeValue, m_dAttributeDataMax);
            (*pTexCoordBottom)[index] = (dAttributeValue - m_dAttributeDataMin) / (m_dAttributeDataMax - m_dAttributeDataMin);
        }
    }
}

void CXLFMGeometryBuilder::_UpdateSideTexCoord(int iZoneIndex, float *pAttributeData, int k)
{
    for (decltype(m_vecEdgeIndex.size()) idx = 0; idx != m_vecEdgeIndex.size(); ++idx)
    {
        int i = m_vecEdgeIndex.at(idx) / (m_nJ + 1);
        int j = m_vecEdgeIndex.at(idx) % (m_nJ + 1);

        double dAttributeValue = _CalcVertexAttributeValue(m_nI, m_nJ, i - 0.5, j - 0.5, pAttributeData);
        dAttributeValue = qBound(m_dAttributeDataMin, dAttributeValue, m_dAttributeDataMax);
        (*m_vecTexCoordSide.at(iZoneIndex))[k * m_vecEdgeIndex.size() + idx] = (dAttributeValue - m_dAttributeDataMin) / (m_dAttributeDataMax - m_dAttributeDataMin);
    }
}

bool CXLFMGeometryBuilder::_HasAttribute()
{
    m_pLFMAttribute = dynamic_cast<CXLFMAttribute*>(::GetObjectByID(m_pViewInfo->GetAttributeObjID()));

    if (m_pLFMAttribute)
    {
        m_pLFMAttribute->GetDataRange(m_dAttributeDataMin, m_dAttributeDataMax);

        return true;
    }
    else
    {
        return false;
    }
}

osg::ref_ptr<osg::Geode> CXLFMGeometryBuilder::_BuildLFMZone(int iZoneIndex)
{
	m_vecSurfaceTop.at(iZoneIndex) = new osg::Geometry;
	m_vecSurfaceBottom.at(iZoneIndex) = new osg::Geometry;
	m_vecSurfaceSide.at(iZoneIndex) = new osg::Geometry;

	m_vecGridLineTop.at(iZoneIndex) = new osg::Geometry;
	m_vecGridLineBottom.at(iZoneIndex) = new osg::Geometry;
	m_vecGridLineHorizontalSlice.at(iZoneIndex) = new osg::Geometry;
	m_vecGridLineVerticalSlice.at(iZoneIndex) = new osg::Geometry;

	osg::ref_ptr<osg::Geode>& pGeode = m_vecGeodeZone.at(iZoneIndex);
	pGeode = new osg::Geode;
	pGeode->setName(m_listZoneName.at(iZoneIndex).toStdString());
	pGeode->addDrawable(m_vecSurfaceTop.at(iZoneIndex));
	pGeode->addDrawable(m_vecSurfaceBottom.at(iZoneIndex));
	pGeode->addDrawable(m_vecSurfaceSide.at(iZoneIndex));

	_UpdateVerticesAndTexCoord(iZoneIndex);
	_CalcIndices(iZoneIndex);
	_CalcSurfaceNormal(iZoneIndex, true);
	_CalcSurfaceNormal(iZoneIndex, false);
	_CalcSideNormal(iZoneIndex);

	_UpdateColors(iZoneIndex);
	_UpdateGridLine(iZoneIndex);

	return pGeode;
}

void CXLFMGeometryBuilder::_UpdateAttributeTexCoord(int iZoneIndex)
{
    Q_ASSERT(m_pLFMAttribute);

	int minK = m_vecZoneMinSlice.at(iZoneIndex);
	int maxK = m_vecZoneMaxSlice.at(iZoneIndex);

	osg::ref_ptr<osg::Geometry> pSurfaceTop = m_vecSurfaceTop.at(iZoneIndex);
	osg::ref_ptr<osg::Geometry> pSurfaceBottom = m_vecSurfaceBottom.at(iZoneIndex);
	osg::ref_ptr<osg::Geometry> pSurfaceSide = m_vecSurfaceSide.at(iZoneIndex);

	osg::ref_ptr<osg::FloatArray> pTexCoordTop = m_vecTexCoordTop.at(iZoneIndex);
	osg::ref_ptr<osg::FloatArray> pTexCoordBottom = m_vecTexCoordBottom.at(iZoneIndex);
	osg::ref_ptr<osg::FloatArray> pTexCoordSide = m_vecTexCoordSide.at(iZoneIndex);

    int nNewK = maxK - minK + 1;
    Q_ASSERT(nNewK > 1);

    for (int k = minK; k != maxK; ++k)
    {
        float *pAttributeData = new float[m_nI * m_nJ];
        bool bRet = m_pLFMAttribute->ReadOneSlice(k, pAttributeData);
        Q_ASSERT(bRet);

        if (minK == k)
        {
            _UpdateTopTexCoord(iZoneIndex, pAttributeData);
            pSurfaceTop->setVertexAttribArray(2, pTexCoordTop.get(), osg::Array::BIND_PER_VERTEX);
        }
        else if (maxK - 1 == k)
        {
            _UpdateBottomTexCoord(iZoneIndex, pAttributeData);
            pSurfaceBottom->setVertexAttribArray(2, pTexCoordBottom.get(), osg::Array::BIND_PER_VERTEX);
        }

        _UpdateSideTexCoord(iZoneIndex, pAttributeData, k - minK);

        delete[] pAttributeData;
    }

    pSurfaceSide->setVertexAttribArray(2, pTexCoordSide.get(), osg::Array::BIND_PER_VERTEX);
}

void CXLFMGeometryBuilder::_UpdateVerticesAndTexCoord(int iZoneIndex)
{
	int minK = m_vecZoneMinSlice.at(iZoneIndex);
	int maxK = m_vecZoneMaxSlice.at(iZoneIndex);

    int nNewK = maxK - minK + 1;
    Q_ASSERT(nNewK > 1);

    for (int k = minK; k <= maxK; ++k)
    {
        float *pData = new float[m_nI * m_nJ];
        bool bRet = m_pLFM->ReadOneSlice(k, pData);
        Q_ASSERT(bRet);

        if (minK == k)
        {
            if (!_CalcValidMap(pData)) return;
            _CalcEdgeIndex();

			m_vecVerticesSide.at(iZoneIndex) = new osg::Vec3Array(nNewK * m_vecEdgeIndex.size());
			m_vecTexCoordSide.at(iZoneIndex) = new osg::FloatArray(nNewK * m_vecEdgeIndex.size());
            _CalcTopVerticesAndTexCoord(iZoneIndex, pData);
        }
        else if (maxK == k)
        {
            _CalcBottomVerticesAndTexCoord(iZoneIndex, pData);
        }

        _CalcSideVerticesAndTexCoord(iZoneIndex, pData, k - minK);

        delete[] pData;
    }

    m_vecSurfaceSide.at(iZoneIndex)->setVertexAttribArray(0, m_vecVerticesSide.at(iZoneIndex), osg::Array::BIND_PER_VERTEX);
	m_vecSurfaceSide.at(iZoneIndex)->setVertexAttribArray(2, m_vecTexCoordSide.at(iZoneIndex), osg::Array::BIND_PER_VERTEX);

	m_vecGridLineHorizontalSlice.at(iZoneIndex)->setVertexArray(m_vecVerticesSide.at(iZoneIndex));
	m_vecGridLineVerticalSlice.at(iZoneIndex)->setVertexArray(m_vecVerticesSide.at(iZoneIndex));
}

void CXLFMGeometryBuilder::_CalcSideIndices(osg::ref_ptr<osg::Geometry>& pSurfaceSideGeom, int minK, int maxK)
{
	pSurfaceSideGeom->getPrimitiveSetList().clear();

    for (int k = minK; k < maxK; ++k)
    {
        osg::ref_ptr<osg::DrawElementsUInt> pIndices = new osg::DrawElementsUInt(GL_TRIANGLE_STRIP, m_vecEdgeIndex.size() * 2);

        int iK = k - minK;

        for (decltype(pIndices->size()) i = 0; i < pIndices->size(); i += 2)
        {
            (*pIndices)[i] = iK * m_vecEdgeIndex.size() + i / 2;
            (*pIndices)[i + 1] = (iK + 1) * m_vecEdgeIndex.size() + i / 2;
        }

        pIndices->push_back(iK * m_vecEdgeIndex.size());
        pIndices->push_back((iK + 1) * m_vecEdgeIndex.size());

		pSurfaceSideGeom->addPrimitiveSet(pIndices.get());
    }
}

void CXLFMGeometryBuilder::_CalcSideGridlineIndices(int iZoneIndex)
{
	osg::ref_ptr<osg::Geometry>& pHorizontalGridLineSlice = m_vecGridLineHorizontalSlice.at(iZoneIndex);
	osg::ref_ptr<osg::Geometry>& pVerticalGridLineSlice = m_vecGridLineVerticalSlice.at(iZoneIndex);

	pHorizontalGridLineSlice->getPrimitiveSetList().clear();
    pVerticalGridLineSlice->getPrimitiveSetList().clear();

	int minK = m_vecZoneMinSlice.at(iZoneIndex);
	int maxK = m_vecZoneMaxSlice.at(iZoneIndex);

    for (int k = minK; k < maxK; ++k)
    {
        osg::ref_ptr<osg::DrawElementsUInt> pVerticalLine = new osg::DrawElementsUInt(GL_LINES, 0);
        osg::ref_ptr<osg::DrawElementsUInt> pHorizontalLine = new osg::DrawElementsUInt(GL_LINE_LOOP, m_vecEdgeIndex.size());

        int iK = k - minK;

        for (decltype(m_vecEdgeIndex.size()) i = 0; i < m_vecEdgeIndex.size(); ++i)
        {
            int iI = m_vecEdgeIndex.at(i) / (m_nJ + 1);
            int iJ = m_vecEdgeIndex.at(i) % (m_nJ + 1);

            if (m_vecGridIndex.at(iZoneIndex).find(m_vecEdgeIndex.at(i)) == m_vecGridIndex.at(iZoneIndex).end()) continue;

            pVerticalLine->push_back(iK * m_vecEdgeIndex.size() + i);
            pVerticalLine->push_back((iK + 1) * m_vecEdgeIndex.size() + i);
        }

        for (decltype(pHorizontalLine->size()) i = 0; i < pHorizontalLine->size(); ++i)
        {
            (*pHorizontalLine)[i] = iK * m_vecEdgeIndex.size() + i;
        }

		pHorizontalGridLineSlice->addPrimitiveSet(pHorizontalLine.get());
		pVerticalGridLineSlice->addPrimitiveSet(pVerticalLine.get());
    }
}

void CXLFMGeometryBuilder::_CalcIndices(int iZoneIndex)
{
    _CalcSurfaceIndices(m_vecSurfaceTop.at(iZoneIndex));
    _CalcSurfaceIndices(m_vecSurfaceBottom.at(iZoneIndex));
    _CalcSideIndices(m_vecSurfaceSide.at(iZoneIndex), m_vecZoneMinSlice.at(iZoneIndex), m_vecZoneMaxSlice.at(iZoneIndex));

    _CalcSurfaceGridlineIndices(iZoneIndex);
    _CalcSideGridlineIndices(iZoneIndex);
}

void CXLFMGeometryBuilder::_CalcSurfaceIndices(osg::ref_ptr<osg::Geometry>& pSurfaceGeom)
{
    std::vector<GLuint> indices;

	pSurfaceGeom->getPrimitiveSetList().clear();

    for (int i = 0; i < m_nI; ++i)
    {
        indices.clear();

        if (i < m_minNI || m_maxNI < i) continue;

        for (int j = 0; j <= m_nJ; ++j)
        {
            if (j < m_minNJ || m_maxNJ < j) continue;

            if (m_validBitMap.testBit(i * (m_nJ + 1) + j) && m_validBitMap.testBit((i + 1) * (m_nJ + 1) + j))
            {
                indices.push_back( i      * (m_nJ + 1) + j);
                indices.push_back((i + 1) * (m_nJ + 1) + j);
            }
        }

        if (indices.size() < 3) 
			continue;
        else
        {
            osg::ref_ptr<osg::DrawElementsUInt> pIndicesOneLine = new osg::DrawElementsUInt(GL_TRIANGLE_STRIP, indices.cbegin(), indices.cend());
			pSurfaceGeom->addPrimitiveSet(pIndicesOneLine.get());
        }
    }
}

void CXLFMGeometryBuilder::_CalcSurfaceGridlineIndices(int iZoneIndex)
{
	int nVerticalLineSpacing = m_pViewInfo->GetVerticalLineSpacing();

	osg::ref_ptr<osg::Geometry>& pGridLineTop = m_vecGridLineTop.at(iZoneIndex);
	osg::ref_ptr<osg::Geometry>& pGridLineBottom = m_vecGridLineBottom.at(iZoneIndex);

    pGridLineTop->getPrimitiveSetList().clear();
    pGridLineBottom->getPrimitiveSetList().clear();
	m_vecGridIndex.at(iZoneIndex).clear();

    osg::ref_ptr<osg::DrawElementsUInt> pHorizontalIndices = new osg::DrawElementsUInt(GL_LINES, 0);

    int firstI = -1, lastI = 0;
    for (int i = 0; i < m_nI; ++i)
    {
		for (int j = 0; j <= m_nJ; j += nVerticalLineSpacing)
        {
            if (m_validBitMap.testBit(i * (m_nJ + 1) + j) && m_validBitMap.testBit((i + 1) * (m_nJ + 1) + j))
            {
                pHorizontalIndices->push_back( i      * (m_nJ + 1) + j);
                pHorizontalIndices->push_back((i + 1) * (m_nJ + 1) + j);

                if (firstI == -1)
                {
                    firstI = i;
                }
                lastI = i + 1;
            }
        }
    }

	for (int j = 0; j <= m_nJ; j += nVerticalLineSpacing)
    {
		m_vecGridIndex.at(iZoneIndex).insert(firstI * (m_nJ + 1) + j);
		m_vecGridIndex.at(iZoneIndex).insert(lastI * (m_nJ + 1) + j);
    }

    pGridLineTop->addPrimitiveSet(pHorizontalIndices.get());
    pGridLineBottom->addPrimitiveSet(pHorizontalIndices.get());

	for (int i = 0; i <= m_nI; i += nVerticalLineSpacing)
    {
        osg::ref_ptr<osg::DrawElementsUInt> pVerticalIndices = new osg::DrawElementsUInt(GL_LINE_STRIP, 0);

        int firstJ = -1, lastJ = 0;

        for (int j = 0; j <= m_nJ; ++j)
        {
            int index = i * (m_nJ + 1) + j;
            if (m_validBitMap.testBit(index))
            {
                pVerticalIndices->push_back(index);

                if (firstJ == -1)
                {
                    firstJ = j;
                }
                lastJ = j;
            }
        }

        if (pVerticalIndices->size() < 3) continue;

		m_vecGridIndex.at(iZoneIndex).insert(i * (m_nJ + 1) + firstJ);
		m_vecGridIndex.at(iZoneIndex).insert(i * (m_nJ + 1) + lastJ);

        pGridLineTop->addPrimitiveSet(pVerticalIndices.get());
        pGridLineBottom->addPrimitiveSet(pVerticalIndices.get());
    }
}

void CXLFMGeometryBuilder::_UpdateColors(int iZoneIndex)
{
	osg::ref_ptr<osg::StateSet>& m_pStateSet = m_vecStateSet.at(iZoneIndex);

    if (!m_pStateSet)
    {
        m_pStateSet = new osg::StateSet;
        m_vecSurfaceTop.at(iZoneIndex)->setStateSet(m_pStateSet.get());
        m_vecSurfaceBottom.at(iZoneIndex)->setStateSet(m_pStateSet.get());
        m_vecSurfaceSide.at(iZoneIndex)->setStateSet(m_pStateSet.get());
    }
    else
    {
        m_pStateSet->clear();
    }

    osg::ref_ptr<osg::Uniform> pColormapUniform = new osg::Uniform(osg::Uniform::FLOAT_VEC4, "colorTable", 256);

	if (_HasAttribute())
	{
		CXColormap *pColormap = CXColormap::GetColormap(m_pViewInfo->GetColormapName());
		if (!pColormap) return;

		for (uint i = 0; i < 256; ++i)
		{
			QColor color = pColormap->GetColorAt(static_cast<uchar>(i));
			pColormapUniform->setElement(i, osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
		}
	}
	else
	{
		QColor c = m_vecZoneColor.at(iZoneIndex);
		for (uint i = 0; i < 256; ++i)
		{
			pColormapUniform->setElement(i, osg::Vec4(c.redF(), c.greenF(), c.blueF(), c.alphaF()));
		}
	}

    osg::ref_ptr<osg::Program> pProgram = new osg::Program;

    pProgram->addShader(osg::Shader::readShaderFile(osg::Shader::VERTEX, (CXDBIO::GetShaderFilePath() + "surface.vert").toStdString()));
    pProgram->addShader(osg::Shader::readShaderFile(osg::Shader::FRAGMENT, (CXDBIO::GetShaderFilePath() + "surface.frag").toStdString()));
    pProgram->addBindAttribLocation("myVertex", 0);
    pProgram->addBindAttribLocation("myNormal", 1);
    pProgram->addBindAttribLocation("myAttr", 2);

    osg::ref_ptr<osg::Uniform> pLightUniform = new osg::Uniform(osg::Uniform::INT, "lightState", 4);

    pLightUniform->setElement(0, 1);
    pLightUniform->setElement(1, 1);
    pLightUniform->setElement(2, 0);
    pLightUniform->setElement(3, 0);

    m_pStateSet->setAttribute(pProgram, osg::StateAttribute::ON);
    m_pStateSet->addUniform(pColormapUniform.get());
    m_pStateSet->addUniform(pLightUniform.get());
}

void CXLFMGeometryBuilder::_CalcSurfaceNormal(int iZoneIndex, bool bTop)
{
    int NI = m_nI + 1;
    int NJ = m_nJ + 1;

	osg::ref_ptr<osg::Vec3Array>& pVertex = bTop ? m_vecVerticesTop.at(iZoneIndex) : m_vecVerticesBottom.at(iZoneIndex);
	osg::ref_ptr<osg::Geometry>& pSurface = bTop ? m_vecSurfaceTop.at(iZoneIndex) : m_vecSurfaceBottom.at(iZoneIndex);

    osg::Vec3Array* pNormal = new osg::Vec3Array(NI * NJ);

    for (int i = 0; i < m_nI; ++i)
    {
        for (int j = 0; j < m_nJ; ++j)
        {
            osg::Vec3 vec1 = pVertex->at( i      * NJ + j);
            osg::Vec3 vec2 = pVertex->at( i      * NJ + j);
            osg::Vec3 vec3 = pVertex->at((i + 1) * NJ + j);

            osg::Vec3 normal = bTop ? (vec3 - vec1) ^ (vec2 - vec1) : (vec2 - vec1) ^ (vec3 - vec1);
            normal.normalize();

            (*pNormal)[i * NJ + j].set(normal);

            if (i == m_nI - 1)
            {
                (*pNormal)[m_nI * NJ + j].set(normal);
            }
        }

        (*pNormal)[i * NJ + m_nJ].set(pNormal->at(i * NJ + m_nJ - 1));
    }

    (*pNormal)[m_nI * NJ + m_nJ].set(pNormal->at((m_nI - 1)* NJ + m_nJ - 1));

	pSurface->setVertexAttribArray(1, pNormal, osg::Array::BIND_PER_VERTEX);
}

void CXLFMGeometryBuilder::_CalcSideNormal(int iZoneIndex)
{
	int minK = m_vecZoneMinSlice.at(iZoneIndex);
	int maxK = m_vecZoneMaxSlice.at(iZoneIndex);

	osg::ref_ptr<osg::Vec3Array>& pVerticesSide = m_vecVerticesSide.at(iZoneIndex);
	osg::ref_ptr<osg::Geometry>& pSurfaceSide = m_vecSurfaceSide.at(iZoneIndex);

    int nNewNK = maxK - minK + 1;

    osg::Vec3Array* pNormal = new osg::Vec3Array(nNewNK * m_vecEdgeIndex.size());

    for (int iK = minK; iK < maxK - 1; ++iK)
    {
        int k = iK - minK;

        for (decltype(m_vecEdgeIndex.size()) index = 0; index != m_vecEdgeIndex.size(); ++index)
        {
            bool bLastIndex = index == m_vecEdgeIndex.size() - 1;

            osg::Vec3 vec1 = pVerticesSide->at( k      * m_vecEdgeIndex.size() + index);
            osg::Vec3 vec2 = pVerticesSide->at( k      * m_vecEdgeIndex.size() + bLastIndex ? 0 : index + 1);
            osg::Vec3 vec3 = pVerticesSide->at((k + 1) * m_vecEdgeIndex.size() + index);

            osg::Vec3 normal = (vec3 - vec1) ^ (vec2 - vec1);
            normal.normalize();

            (*pNormal)[k * m_vecEdgeIndex.size() + index].set(normal);

            if (k == nNewNK - 2)
            {
                (*pNormal)[(nNewNK - 1) * m_vecEdgeIndex.size() + index].set(normal);
            }
        }
    }

    pSurfaceSide->setVertexAttribArray(1, pNormal, osg::Array::BIND_PER_VERTEX);
}

void CXLFMGeometryBuilder::_CalcEdgeIndex()
{
    int NI = m_nI + 1;
    int NJ = m_nJ + 1;

    m_validBitMap.clear();
    m_validBitMap.resize(NI * NJ);

    bool bFirst = true;
    int firstIndex = 0;

    for (int i = 0; i < m_nI; ++i)
    {
        if (i < m_minNI || m_maxNI - 1 < i) continue;

        for (int j = 0; j < m_nJ; ++j)
        {
            if (!m_validDataBitMap.testBit(i * m_nJ + j)) continue;

            if (j < m_minNJ || m_maxNJ - 1 < j) continue;

            m_validBitMap.setBit(i * NJ + j, true); // top left
            m_validBitMap.setBit((i + 1) * NJ + j, true); // bottom left
            m_validBitMap.setBit(i * NJ + j + 1,  true); // top right
            m_validBitMap.setBit((i + 1) * NJ + j + 1,  true); // bottom right

            if (bFirst)
            {
                firstIndex = i * NJ + j;
                bFirst = false;
            }
        }
    }

    int nextIndex = firstIndex + 1;

    m_vecEdgeIndex.reserve(NI * NJ);
    m_vecEdgeIndex.assign({ firstIndex, nextIndex });

    enum Direction{ Up, Forward, Down, Back };
    Direction direction{ Forward };

    auto canUp = [NJ, this](int index) -> bool
    {
        if (index - NJ < 0)
        {
            return false;
        }
        else
        {
            return m_validBitMap.testBit(index - NJ);
        }
    };

    auto canDown = [NI, NJ, this](int index) -> bool
    {
        if (index + NJ >= NI * NJ)
        {
            return false;
        }
        else
        {
            return m_validBitMap.testBit(index + NJ);
        }
    };

    auto canForward = [NJ, this](int index) -> bool
    {
        if ((index + 1) % NJ == 0)
        {
            return false;
        }
        else
        {
            return m_validBitMap.testBit(index + 1);
        }
    };

    auto canBack = [NJ, this](int index) -> bool
    {
        if (index % NJ == 0)
        {
            return false;
        }
        else
        {
            return m_validBitMap.testBit(index - 1);
        }
    };

    while (nextIndex != firstIndex)
    {
        switch (direction)
        {
        case Forward:
            if (canUp(nextIndex))
            {
                nextIndex -= NJ;
                direction = Up;
            }
            else if (canForward(nextIndex))
            {
                nextIndex += 1;
                direction = Forward;
            }
            else if (canDown(nextIndex))
            {
                nextIndex += NJ;
                direction = Down;
            }
            break;
        case Down:
            if (canForward(nextIndex))
            {
                nextIndex += 1;
                direction = Forward;
            }
            else if (canDown(nextIndex))
            {
                nextIndex += NJ;
                direction = Down;
            }
            else if (canBack(nextIndex))
            {
                nextIndex -= 1;
                direction = Back;
            }
            break;
        case Back:
            if (canDown(nextIndex))
            {
                nextIndex += NJ;
                direction = Down;
            }
            else if (canBack(nextIndex))
            {
                nextIndex -= 1;
                direction = Back;
            }
            else if (canUp(nextIndex))
            {
                nextIndex -= NJ;
                direction = Up;
            }
            break;
        case Up:
            if (canBack(nextIndex))
            {
                nextIndex -= 1;
                direction = Back;
            }
            else if (canUp(nextIndex))
            {
                nextIndex -= NJ;
                direction = Up;
            }
            else if (canForward(nextIndex))
            {
                nextIndex += 1;
                direction = Forward;
            }
            break;
        default:
            Q_ASSERT(!"error direction");
        }

        m_vecEdgeIndex.push_back(nextIndex);
    }
}