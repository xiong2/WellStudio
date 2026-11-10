#include "xbmpickcallback.h"

#include <osg/NodeVisitor>
#include <osgGA/EventVisitor>
#include <osg/LineStipple>

#include "xosgwidget.h"
#include "xbmpickhandle.h"
#include "x3dpickablebuilder.h"
#include "xbmseismicsectionbuilder.h"
#include "xglobal.h"
#include "x3dutility.h"
#include "xbmrandomsectionbuilder.h"
#include "xbmpolygonbuilder.h"

CXBMPickCallback::CXBMPickCallback(CX3DPickableBuilderAbstract *pBuilder)
	: osg::NodeCallback(), m_pBuilder(pBuilder)
{

}

CXBMPickCallback::~CXBMPickCallback()
{

}

void CXBMPickCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	traverse(node, nv);
}

bool CXBMPickCallback::SetActive(bool bActive)
{
	return m_pBuilder->SetActive(bActive);
}

void CXBMPickCallback::SetSeismicSectionTrace(int iInline, int iXline)
{
	auto pSeismicSectionBuilder = dynamic_cast<CXBMSeismicSectionBuilder*>(m_pBuilder);
	if (!pSeismicSectionBuilder)
		return;

	pSeismicSectionBuilder->UpdateSeismicLinePosition(iInline, iXline);
}

int CXBMPickCallback::GetSeismicSectionTrace()
{
	auto pSeismicSectionBuilder = dynamic_cast<CXBMSeismicSectionBuilder*>(m_pBuilder);
	if (!pSeismicSectionBuilder)
		return -1;

	return pSeismicSectionBuilder->GetCurrentTraceNumber();
}

int CXBMPickCallback::GetPivotIndexFromPos(const osg::Vec3 & pos, float minDist)
{
	int iPivotIndex = _CheckPivot(pos, minDist);

	return iPivotIndex == -1 ? m_iCurrentPivot : iPivotIndex;
}

void CXBMPickCallback::DragPivot(int iPivotIndex, const osg::Vec3 & toPos)
{
	if (-1 == iPivotIndex)
		return;

	auto pRandomSectionBuilder = dynamic_cast<CXBMRandomSectionBuilder*>(m_pBuilder);
	if (pRandomSectionBuilder)
	{
		osg::Geode* pGeode = dynamic_cast<osg::Geode*>(pRandomSectionBuilder->GetBuilderNode().get());
		osg::ref_ptr<osg::Vec3Array> pVertex = pRandomSectionBuilder->GetVertex();

		if (!m_pGeometry.valid())
		{
			m_pGeometry = new osg::Geometry;
			m_pVertex = new osg::Vec3Array;
			if (iPivotIndex == 0)
			{
				m_pVertex->push_back(pVertex->at(iPivotIndex + 1));
				m_pVertex->push_back(toPos);
				m_pGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, m_pVertex->size()));
			}
			else if (iPivotIndex == pVertex->size() - 1)
			{
				m_pVertex->push_back(pVertex->at(iPivotIndex - 1));
				m_pVertex->push_back(toPos);
				m_pGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, m_pVertex->size()));
			}
			else
			{
				m_pVertex->push_back(pVertex->at(iPivotIndex - 1));
				m_pVertex->push_back(pVertex->at(iPivotIndex));
				m_pVertex->push_back(pVertex->at(iPivotIndex + 1));
				m_pVertex->push_back(toPos);
				m_pGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, m_pVertex->size()));
			}

			pGeode->addDrawable(m_pGeometry);
		}
		else
		{
			m_pVertex->back().set(toPos);
		}

		m_pGeometry->dirtyDisplayList();
		m_pGeometry->setVertexArray(m_pVertex);
		m_pGeometry->setColorArray(pRandomSectionBuilder->GetPickedColor(), osg::Array::BIND_OVERALL);
		m_pGeometry->getOrCreateStateSet()->setAttributeAndModes(new osg::LineStipple(1, 0x0f0f));
	}

	auto pPolygonBuilder = dynamic_cast<CXBMPolygonBuilder*>(m_pBuilder);
	if (pPolygonBuilder)
	{
		osg::Geode* pGeode = dynamic_cast<osg::Geode*>(pPolygonBuilder->GetBuilderNode().get());
		osg::ref_ptr<osg::Vec3Array> pVertex = pPolygonBuilder->GetVertex();

		if (!m_pGeometry.valid())
		{
			m_pGeometry = new osg::Geometry;
			m_pVertex = new osg::Vec3Array(4);

			int iPrev = [](int iPrev, int size) {
				if (iPrev < 0)
					iPrev += size;
				return iPrev;
			}(iPivotIndex - 1, pVertex->size());

			int iNext = [](int iNext, int size) {
				if (iNext > size - 1)
					iNext -= size;
				return iNext;
			}(iPivotIndex + 1, pVertex->size());

			(*m_pVertex)[0].set(pVertex->at(iPrev));
			(*m_pVertex)[1].set(pVertex->at(iPivotIndex));
			(*m_pVertex)[2].set(pVertex->at(iNext));
			(*m_pVertex)[3].set(toPos);

			pGeode->addDrawable(m_pGeometry);
		}
		else
		{
			(*m_pVertex)[3].set(toPos);
		}

		m_pGeometry->dirtyDisplayList();
		m_pGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, 4));
		m_pGeometry->setVertexArray(m_pVertex);
	}
}

void CXBMPickCallback::FixedPivot()
{
	auto pBuilder = dynamic_cast<CX3DPickableBuilderAbstract*>(m_pBuilder);
	if (pBuilder)
	{
		osg::Geode* pGeode = dynamic_cast<osg::Geode*>(pBuilder->GetBuilderNode().get());
		pGeode->removeDrawable(m_pGeometry);

		m_pVertex = nullptr;
		m_pGeometry = nullptr;
	}
}

bool CXBMPickCallback::IsPolygonSelfIntersection(int index, const osg::Vec3 & pos)
{
	auto pPolygonBuilder = dynamic_cast<CXBMPolygonBuilder*>(m_pBuilder);
	if (!pPolygonBuilder)
		return false;

	osg::ref_ptr<osg::Vec3Array> pVertex = pPolygonBuilder->GetVertex();
	osg::ref_ptr<osg::Vec3Array> pNewVertex = new osg::Vec3Array(*pVertex);
	pNewVertex->at(index) = pos;

	if (NX3DUtility::IsPolygonSelfIntersection(pNewVertex, index))
		return true;

	return false;
}

int CXBMPickCallback::_CheckPivot(const osg::Vec3 & pos, float minDist)
{
	auto pBuilder = dynamic_cast<CX3DPickableBuilderAbstract*>(m_pBuilder);
	if (!pBuilder)
		return -1;

	osg::ref_ptr<osg::Vec3Array> pVertex = pBuilder->GetVertex();
	if (!pVertex.valid())
		return -1;

	for (uint i = 0; i != pVertex->size(); ++i)
	{
		osg::Vec3 sameZPos(pos.x(), pos.y(), pVertex->at(i).z());
		osg::Vec3 distance = pVertex->at(i) - sameZPos;
		if (minDist > distance.length())
		{
			return i;
		}
	}

	return -1;
}
