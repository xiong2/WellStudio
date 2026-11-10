#include "xbmprestackgatherbuilder.h"
#include <cmath>
#include <osg/Point>
#include <osg/PolygonMode>
#include "x3dbuilderfactory.h"
#include "xviewinfoprestackgather.h"
#include "xglobal.h"
#include "xprestackgather.h"
#include "x3dglobalcoordmap.h"
#include "x3dutility.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXBMPreStackGatherBuilder)
{ EXPrestackGather, e3DBaseMap }
END_REGISTER_BUILDER_TO_FACTORY(CXBMPreStackGatherBuilder)

CXBMPreStackGatherBuilder::CXBMPreStackGatherBuilder()
	: CX3DBuilderAbstract()
{

}

CXBMPreStackGatherBuilder::~CXBMPreStackGatherBuilder()
{

}

osg::ref_ptr<osg::Group> CXBMPreStackGatherBuilder::Build(QUuid objId)
{
	m_pPreStackGather = dynamic_cast<CXPreStackGather*>(::GetObjectByID(objId));
	m_pViewInfo = dynamic_cast<CXViewInfoPreStackGather*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pPreStackGather || !m_pViewInfo)
		return nullptr;

	m_sourceSize = m_pViewInfo->GetSourcePointSize();
	m_detectSize = m_pViewInfo->GetDetectPointSize();
	m_sourceShape = m_pViewInfo->GetSourcePointShape();
	m_detectShape = m_pViewInfo->GetDetectPointShape();

	m_pSwitch = new osg::Switch;

	m_pSwitch->addChild(_BuildWhole(), m_pViewInfo->GetIsViewAll());
	m_pSwitch->addChild(_BuildSingle(), !m_pViewInfo->GetIsViewAll());

	return m_pSwitch;
}

void CXBMPreStackGatherBuilder::UpdateNode(EEventType eType)
{
	if (eType == EInfoChanged)
	{
		NX3DUtility::SetSingleColor(m_pWholeSourcePointGeom, m_pViewInfo->GetSourcePointColor());
		NX3DUtility::SetSingleColor(m_pWholeDetectPointGeom, m_pViewInfo->GetDetectPointColor());
		NX3DUtility::SetSingleColor(m_pSingleSourcePointGeom, m_pViewInfo->GetSourcePointColor());
		NX3DUtility::SetSingleColor(m_pSingleDetectPointGeom, m_pViewInfo->GetDetectPointColor());

		if (m_sourceSize != m_pViewInfo->GetSourcePointSize() || m_sourceShape != m_pViewInfo->GetSourcePointShape())
		{
			m_sourceSize = m_pViewInfo->GetSourcePointSize();
			m_sourceShape = m_pViewInfo->GetSourcePointShape();

			m_pWholeGeode->removeChild(m_pWholeSourcePointGeom);
			m_pWholeGeode->addChild(_BuildWholeSourcePoints());
			m_pSingleGeode->removeChild(m_pSingleSourcePointGeom);
			m_pSingleGeode->addChild(_BuildSingleSourcePoints());
		}

		if (m_detectSize != m_pViewInfo->GetDetectPointSize() || m_detectShape != m_pViewInfo->GetDetectPointShape())
		{
			m_detectSize = m_pViewInfo->GetDetectPointSize();
			m_detectShape = m_pViewInfo->GetDetectPointShape();

			m_pWholeGeode->removeChild(m_pWholeDetectPointGeom);
			m_pWholeGeode->addChild(_BuildWholeDetectPoints());
			m_pSingleGeode->removeChild(m_pSingleDetectPointGeom);
			m_pSingleGeode->addChild(_BuildSingleDetectPoints());
		}
		
		m_pSwitch->setValue(0, m_pViewInfo->GetIsViewAll());
		m_pSwitch->setValue(1, !m_pViewInfo->GetIsViewAll());
	}
	else if (eType == EDataChanged)
	{
		m_pSingleGeode->removeChildren(0, m_pSingleGeode->getNumChildren());
		m_pSingleGeode->addDrawable(_BuildSingleSourcePoints());
		m_pSingleGeode->addDrawable(_BuildSingleDetectPoints());
	}
}

osg::Geode* CXBMPreStackGatherBuilder::_BuildWhole()
{
	m_pWholeGeode = new osg::Geode;

	m_pWholeGeode->addDrawable(_BuildWholeSourcePoints());
	m_pWholeGeode->addDrawable(_BuildWholeDetectPoints());

	return m_pWholeGeode;
}

osg::Geode* CXBMPreStackGatherBuilder::_BuildSingle()
{
	m_pSingleGeode = new osg::Geode;

	m_pSingleGeode->addDrawable(_BuildSingleSourcePoints());
	m_pSingleGeode->addDrawable(_BuildSingleDetectPoints());

	return m_pSingleGeode;
}

osg::Geometry * CXBMPreStackGatherBuilder::_BuildWholeSourcePoints()
{
	m_pWholeSourcePointGeom = new osg::Geometry;
	osg::Vec3Array* pVertex = new osg::Vec3Array;

	for (int iShot = m_pViewInfo->GetMINShotID(); iShot < m_pViewInfo->GetMAXShotID(); iShot += m_pViewInfo->GetShotIDStep())
	{
		QList<qreal>* listShot = m_pPreStackGather->GetOneShotPoints(iShot);
		if (!listShot || listShot->isEmpty())
			continue;

		osg::Vec3 vecLocal;
		m_pCoordMap->MapWorldToLocal(osg::Vec3d((*listShot)[2], (*listShot)[3], 0), vecLocal);
		pVertex->push_back(vecLocal);
	}

	_BuildGeometry(m_pWholeSourcePointGeom, pVertex, m_sourceShape, m_sourceSize, m_pViewInfo->GetSourcePointColor());

	return m_pWholeSourcePointGeom;
}

osg::Geometry * CXBMPreStackGatherBuilder::_BuildWholeDetectPoints()
{
	m_pWholeDetectPointGeom = new osg::Geometry;
	osg::Vec3Array* pVertex = new osg::Vec3Array;

	for (int iShot = m_pViewInfo->GetMINShotID(); iShot < m_pViewInfo->GetMAXShotID(); iShot += m_pViewInfo->GetShotIDStep())
	{
		QList<qreal>* listShot = m_pPreStackGather->GetOneShotPoints(iShot);
		if (!listShot || listShot->size() < 9)
			continue;
		for (int i = 5; i < listShot->size(); i += 4)
		{
			osg::Vec3 vecLocal;
			m_pCoordMap->MapWorldToLocal(osg::Vec3d((*listShot)[i], (*listShot)[i + 1], 0), vecLocal);
			pVertex->push_back(vecLocal);
		}
	}

	_BuildGeometry(m_pWholeDetectPointGeom, pVertex, m_detectShape, m_detectSize, m_pViewInfo->GetDetectPointColor());

	return m_pWholeDetectPointGeom;
}

osg::Geometry * CXBMPreStackGatherBuilder::_BuildSingleSourcePoints()
{
	m_pSingleSourcePointGeom = new osg::Geometry;
	osg::Vec3Array* pVertex = new osg::Vec3Array;
	
	if (_UpdateSingleSourceShot(pVertex))
		_BuildGeometry(m_pSingleSourcePointGeom, pVertex, m_sourceShape, m_sourceSize, m_pViewInfo->GetSourcePointColor());

	return m_pSingleSourcePointGeom;
}

osg::Geometry * CXBMPreStackGatherBuilder::_BuildSingleDetectPoints()
{
	m_pSingleDetectPointGeom = new osg::Geometry;

	osg::Vec3Array* pVertex = new osg::Vec3Array;

	if (_UpdateSingleDetectShot(pVertex))
		_BuildGeometry(m_pSingleDetectPointGeom, pVertex, m_detectShape, m_detectSize, m_pViewInfo->GetDetectPointColor());

	return m_pSingleDetectPointGeom;
}

bool CXBMPreStackGatherBuilder::_UpdateSingleSourceShot(osg::Vec3Array *pVertex)
{
	QList<qreal>* listShot = m_pPreStackGather->GetOneShotPoints(m_pViewInfo->GetCURShotID());
	if (!listShot || listShot->isEmpty())
		return false;

	pVertex->resize(1);
	m_pCoordMap->MapWorldToLocal(osg::Vec3d((*listShot)[2], (*listShot)[3], 0), (*pVertex)[0]);

	return true;
}

bool CXBMPreStackGatherBuilder::_UpdateSingleDetectShot(osg::Vec3Array *pVertex)
{
	QList<qreal>* listShot = m_pPreStackGather->GetOneShotPoints(m_pViewInfo->GetCURShotID());
	if (!listShot || listShot->size() < 2)
		return false;

	pVertex->resize(listShot->size() - 1);
	for (int i = 5; i < listShot->size(); i += 4)
		m_pCoordMap->MapWorldToLocal(osg::Vec3d((*listShot)[i], (*listShot)[i + 1], 0), (*pVertex)[i - 1]);

	return true;
}

void CXBMPreStackGatherBuilder::_BuildGeometry(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array * pVertex, int type, int size, const QColor & color)
{
	switch (type)
	{
	case 0:
		_BuildPoint(pGeom, pVertex, size, color);
		break;
	case 1:
		_BuildCross(pGeom, pVertex, size, color);
		break;
	case 2:
		_BuildTriangle(pGeom, pVertex, size, color);
		break;
	case 3:
		_BuildDiamond(pGeom, pVertex, size, color);
		break;
	case 4:
		_BuildSquare(pGeom, pVertex, size, color);
		break;
	case 5:
		_BuildCircle(pGeom, pVertex, size, color);
		break;
	case 6:
		_BuildTriangle(pGeom, pVertex, size, color, true);
		break;
	case 7:
		_BuildDiamond(pGeom, pVertex, size, color, true);
		break;
	case 8:
		_BuildSquare(pGeom, pVertex, size, color, true);
		break;
	case 9:
		_BuildCircle(pGeom, pVertex, size, color, true);
		break;
	default:;
	}
}

void CXBMPreStackGatherBuilder::_BuildPoint(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array * pVertex, int size, const QColor & color)
{
	pGeom->setVertexArray(pVertex);
	pGeom->getOrCreateStateSet()->setAttribute(new osg::Point(size), osg::StateAttribute::ON);
	NX3DUtility::SetSingleColor(pGeom, color);
	pGeom->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, pVertex->size()));
}

void CXBMPreStackGatherBuilder::_BuildCross(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array * pVertex, int size, const QColor & color)
{
	osg::Vec3Array* pCrossVertex = new osg::Vec3Array(pVertex->size() * 4);
	for (size_t i = 0; i < pVertex->size(); ++i)
	{
		const osg::Vec3& center = pVertex->at(i);
		(*pCrossVertex)[i * 4 + 0].set(center.x() - size / 2.f, center.y(), center.z());
		(*pCrossVertex)[i * 4 + 1].set(center.x() + size / 2.f, center.y(), center.z());
		(*pCrossVertex)[i * 4 + 2].set(center.x(), center.y() + size / 2.f, center.z());
		(*pCrossVertex)[i * 4 + 3].set(center.x(), center.y() - size / 2.f, center.z());
	}
	pGeom->setVertexArray(pCrossVertex);
	NX3DUtility::SetSingleColor(pGeom, color);
	pGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, pCrossVertex->size()));
}

void CXBMPreStackGatherBuilder::_BuildTriangle(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array * pVertex, int size, const QColor & color, bool bFill)
{
	osg::Vec3Array* pCrossVertex = new osg::Vec3Array(pVertex->size() * 3);
	for (size_t i = 0; i < pVertex->size(); ++i)
	{
		const osg::Vec3& center = pVertex->at(i);
		(*pCrossVertex)[i * 3 + 0].set(center.x(), center.y() + size, center.z());
		(*pCrossVertex)[i * 3 + 1].set(center.x() - std::sqrt(3.f) * size / 2.f, center.y() - size / 2.f, center.z());
		(*pCrossVertex)[i * 3 + 2].set(center.x() + std::sqrt(3.f) * size / 2.f, center.y() - size / 2.f, center.z());
	}
	pGeom->setVertexArray(pCrossVertex);
	if (!bFill)
		pGeom->getOrCreateStateSet()->setAttribute(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE), osg::StateAttribute::ON);
	NX3DUtility::SetSingleColor(pGeom, color);
	pGeom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLES, 0, pCrossVertex->size()));
}

void CXBMPreStackGatherBuilder::_BuildDiamond(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array * pVertex, int size, const QColor & color, bool bFill)
{
	osg::Vec3Array* pCrossVertex = new osg::Vec3Array(pVertex->size() * 4);
	for (size_t i = 0; i < pVertex->size(); ++i)
	{
		const osg::Vec3& center = pVertex->at(i);
		(*pCrossVertex)[i * 4 + 0].set(center.x() - size / 2.f, center.y(), center.z());
		(*pCrossVertex)[i * 4 + 1].set(center.x(), center.y() + size / 2.f, center.z());
		(*pCrossVertex)[i * 4 + 2].set(center.x() + size / 2.f, center.y(), center.z());
		(*pCrossVertex)[i * 4 + 3].set(center.x(), center.y() - size / 2.f, center.z());
	}
	pGeom->setVertexArray(pCrossVertex);
	if (!bFill)
		pGeom->getOrCreateStateSet()->setAttribute(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE), osg::StateAttribute::ON);
	NX3DUtility::SetSingleColor(pGeom, color);
	pGeom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, pCrossVertex->size()));
}

void CXBMPreStackGatherBuilder::_BuildSquare(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array * pVertex, int size, const QColor & color, bool bFill)
{
	osg::Vec3Array* pCrossVertex = new osg::Vec3Array(pVertex->size() * 4);
	for (size_t i = 0; i < pVertex->size(); ++i)
	{
		const osg::Vec3& center = pVertex->at(i);
		(*pCrossVertex)[i * 4 + 0].set(center.x() - size / 2.f, center.y() + size / 2.f, center.z());
		(*pCrossVertex)[i * 4 + 1].set(center.x() + size / 2.f, center.y() + size / 2.f, center.z());
		(*pCrossVertex)[i * 4 + 2].set(center.x() + size / 2.f, center.y() - size / 2.f, center.z());
		(*pCrossVertex)[i * 4 + 3].set(center.x() - size / 2.f, center.y() - size / 2.f, center.z());
	}
	pGeom->setVertexArray(pCrossVertex);
	if (!bFill)
		pGeom->getOrCreateStateSet()->setAttribute(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE), osg::StateAttribute::ON);
	NX3DUtility::SetSingleColor(pGeom, color);
	pGeom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, pCrossVertex->size()));
}

void CXBMPreStackGatherBuilder::_BuildCircle(osg::ref_ptr<osg::Geometry>& pGeom, osg::Vec3Array * pVertex, int size, const QColor & color, bool bFill)
{
	auto _GetCircleVertexFromCenter = [](float cx, float cy, float cz, float r, int n, osg::Vec3Array::iterator iterBegin, bool bIncludeCenter)
	{
		float theta = 2 * osg::PI / float(n);
		float c = cosf(theta);
		float s = sinf(theta);

		if (bIncludeCenter)
		{
			iterBegin->set(cx, cy, cz);
			++iterBegin;
		}

		float x = r, y = 0, t;
		for (int i = 0; i != n; ++i, ++iterBegin)
		{
			iterBegin->set(x + cx, y + cy, cz);
			t = x;
			x = c * x - s * y;
			y = s * t + c * y;
		}
	};

	const int nSegment = 10;
	const int nSize = nSegment + (bFill ? 1 : 0);
	osg::Vec3Array *pCircleVertex = new osg::Vec3Array(nSize * pVertex->size());
	for (size_t i = 0; i < pVertex->size(); ++i)
	{
		const osg::Vec3& center = pVertex->at(i);
		_GetCircleVertexFromCenter(center.x(), center.y(), center.z(), size / 2.f, nSegment, pCircleVertex->begin() + i * nSize, bFill);
		if (bFill)
		{
			auto pCircleElements = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLE_FAN, nSize + 1);
			std::iota(pCircleElements->begin(), pCircleElements->end(), i * nSize);
			pCircleElements->back() = pCircleElements->at(1);
			pGeom->addPrimitiveSet(pCircleElements);
		}
		else
		{
			auto pCircleElements = new osg::DrawElementsUInt(osg::PrimitiveSet::LINE_LOOP, nSize);
			std::iota(pCircleElements->begin(), pCircleElements->end(), i * nSize);
			pGeom->addPrimitiveSet(pCircleElements);
		}
	}
	pGeom->setVertexArray(pCircleVertex);
	NX3DUtility::SetSingleColor(pGeom, color);
}
