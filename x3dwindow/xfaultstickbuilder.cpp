#include "xfaultstickbuilder.h"

#include <osg/Point>
#include <osg/LineWidth>
#include <osg/BlendFunc>
#include <osgUtil/SmoothingVisitor>

#include "xviewinfo3dfaultsticks.h"
#include "xfaultsticks.h"
#include "xglobal.h"
#include "x3dbuilderfactory.h"
#include "x3dglobalcoordmap.h"
#include "x3dwindow.h"

BEGIN_REGISTER_BUILDER_TO_FACTORY(CXFaultStickBuilder)
{EXFaultSticks,e3DWindow},
{EXFaultSticks,e3DBaseMap}
END_REGISTER_BUILDER_TO_FACTORY(CXFaultStickBuilder)

osg::ref_ptr<osg::Group> CXFaultStickBuilder::Build(QUuid objId)
{
	if (!m_pBuilderNode) 
		m_pBuilderNode = new osg::Group;

	m_pSticks = dynamic_cast<CXFaultSticks*>(::GetObjectByID(objId));
	if (!m_pSticks) return nullptr;

	m_pViewInfo = dynamic_cast<CXViewInfo3DFaultSticks*>(m_pCurWin->GetObjectViewInfo(objId));
	if (!m_pViewInfo) return nullptr;

	_BuildNode();

	return m_pBuilderNode;
}

void CXFaultStickBuilder::_BuildNode()
{
	m_pGeoNode = new osg::Geode;

	m_pVertices = new osg::Vec3Array;
	_BuildVertices();

	m_pPlane = new osg::Geometry;
	_BuildPlane();

	m_pLine = new osg::Geometry;
	_BuildLines();

	m_pPoint = new osg::Geometry;
	_BuildPoints();	

	if (m_pViewInfo->GetDisplayPlane()) m_pGeoNode->addDrawable(m_pPlane.get());
	if (m_pViewInfo->GetDisplayLine())  m_pGeoNode->addDrawable(m_pLine.get());
	if (m_pViewInfo->GetDisplayPoint()) m_pGeoNode->addDrawable(m_pPoint.get());

	m_pGeoNode->setName("faultstick Geode");
	m_pGeoNode->setUserValue("objID", m_pSticks->GetObjectID().toString().toStdString());

	m_pBuilderNode->addChild(m_pGeoNode.get());
}


void CXFaultStickBuilder::UpdateNode(EEventType eType)
{
	if (!m_pGeoNode) return;

	if (eType == EInfoChanged)
	{
		_UpdatePoint();
		_UpdateLine();
		_UpdataPlane();
	}
	else if (eType == EDataChanged)
	{
		m_pBuilderNode->removeChild(m_pGeoNode.get());

		_BuildNode();

	}
}

void CXFaultStickBuilder::_UpdatePoint()
{
	// Color
	osg::ref_ptr<osg::Vec3Array> pColor = dynamic_cast<osg::Vec3Array*>(m_pPoint->getColorArray());
	QColor color = m_pViewInfo->GetPointColor();
	(*pColor)[0].set(color.redF(), color.greenF(), color.blueF());
	m_pPoint->setColorArray(pColor);

	// Size
	osg::ref_ptr<osg::Point> pPoint = dynamic_cast<osg::Point*>(m_pPoint->getStateSet()->getAttribute((osg::StateAttribute::POINT)));
	pPoint->setSize(m_pViewInfo->GetPointSize());

	if (m_pViewInfo->GetDisplayPoint())
	{
		if (!m_pGeoNode->containsDrawable(m_pPoint.get())) 
			m_pGeoNode->addDrawable(m_pPoint.get());
	}
	else
	{
		if (m_pGeoNode->containsDrawable(m_pPoint.get()))
			m_pGeoNode->removeDrawable(m_pPoint.get());
	}
}

void CXFaultStickBuilder::_UpdateLine()
{
	// color
	osg::ref_ptr<osg::Vec3Array> pColor = dynamic_cast<osg::Vec3Array*>(m_pLine->getColorArray());
	QColor color = m_pViewInfo->GetLineColor();
	(*pColor)[0].set(color.redF(), color.greenF(), color.blueF());
	m_pLine->setColorArray(pColor);

	// line width
	osg::ref_ptr<osg::LineWidth> pLineWidth = dynamic_cast<osg::LineWidth*>(m_pLine->getStateSet()->getAttribute((osg::StateAttribute::LINEWIDTH)));
	pLineWidth->setWidth(m_pViewInfo->GetLineWidth());

	if (m_pViewInfo->GetDisplayLine())
	{
		if (!m_pGeoNode->containsDrawable(m_pLine.get())) 
			m_pGeoNode->addDrawable(m_pLine.get());
	}
	else
	{
		if (m_pGeoNode->containsDrawable(m_pLine.get()))
			m_pGeoNode->removeDrawable(m_pLine.get());
	}
}

void CXFaultStickBuilder::_UpdataPlane()
{
	if (m_vecPointNum.size() < 2) return;

	// color
	osg::ref_ptr<osg::Vec4Array> pColor = dynamic_cast<osg::Vec4Array*>(m_pPlane->getColorArray());
	QColor color = m_pViewInfo->GetPlaneColor();
	(*pColor)[0].set(color.redF(), color.greenF(), color.blueF(), m_pViewInfo->GetOpacity());
	m_pPlane->setColorArray(pColor);

	if (m_pViewInfo->GetDisplayPlane())
	{
		if (!m_pGeoNode->containsDrawable(m_pPlane.get())) 
			m_pGeoNode->addDrawable(m_pPlane.get());
	}
	else
	{
		if (m_pGeoNode->containsDrawable(m_pPlane.get()))
			m_pGeoNode->removeDrawable(m_pPlane.get());
	}
}

void CXFaultStickBuilder::_BuildPlane()
{
	if (m_vecPointNum.size() < 2) return;

	// vertices
	m_pPlane->setVertexArray(m_pVertices.get());

	// colors
	osg::ref_ptr<osg::Vec4Array> pColor = new osg::Vec4Array;
	QColor color = m_pViewInfo->GetPlaneColor();
	pColor->push_back(osg::Vec4(color.redF(), color.greenF(), color.blueF(), m_pViewInfo->GetOpacity()));
	m_pPlane->setColorArray(pColor.get(), osg::Array::BIND_OVERALL);

	m_pPlane->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	m_pPlane->getOrCreateStateSet()->setAttributeAndModes(new osg::BlendFunc);

	// normal
	m_pPlane->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	osgUtil::SmoothingVisitor::smooth(*m_pPlane);

	// Add triangles
	osg::ref_ptr<osg::DrawElementsUInt> pIndices = new osg::DrawElementsUInt(GL_TRIANGLES);

	unsigned int iFirstIndex = 0;
	unsigned iSecondIndex = 0;
	for (int i = 0; i < m_vecPointNum.size() - 1; ++i)
	{
		iSecondIndex += m_vecPointNum[i];

		// even
		int nMinNum = qMin(m_vecPointNum[i], m_vecPointNum[i + 1]);
		for (int j = 0; j < nMinNum - 1; ++j)
		{
			// first triangle
			pIndices->push_back(iFirstIndex + j);
			pIndices->push_back(iSecondIndex + j);
			pIndices->push_back(iFirstIndex + j + 1);

			// second triangle
			pIndices->push_back(iFirstIndex + j + 1);
			pIndices->push_back(iSecondIndex + j);
			pIndices->push_back(iSecondIndex + j + 1);
		}
		if (m_vecPointNum[i] < m_vecPointNum[i + 1])
		{
			for (int j = m_vecPointNum[i] - 1; j < m_vecPointNum[i + 1] - 1; ++j)
			{
				pIndices->push_back(iFirstIndex + m_vecPointNum[i] - 1);
				pIndices->push_back(iSecondIndex + j);
				pIndices->push_back(iSecondIndex + j + 1);
			}
		}
		else
		{
			for (int j = m_vecPointNum[i + 1] - 1; j < m_vecPointNum[i] - 1; ++j)
			{
				pIndices->push_back(iFirstIndex + j);
				pIndices->push_back(iSecondIndex + m_vecPointNum[i + 1] - 1);
				pIndices->push_back(iFirstIndex + j + 1);
			}
		}

		iFirstIndex = iSecondIndex;
	}

	m_pPlane->addPrimitiveSet(pIndices.get());
}

void CXFaultStickBuilder::_BuildLines()
{
	// vertices
	m_pLine->setVertexArray(m_pVertices.get());

	// colors
	osg::ref_ptr<osg::Vec3Array> pColor = new osg::Vec3Array;
	QColor color = m_pViewInfo->GetLineColor();
	pColor->push_back(osg::Vec3f(color.redF(), color.greenF(), color.blueF()));
	m_pLine->setColorArray(pColor.get(), osg::Array::BIND_OVERALL);

	// normal
	m_pLine->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	osgUtil::SmoothingVisitor::smooth(*m_pLine);

	// line width
	osg::ref_ptr<osg::LineWidth> pLineWidth = new osg::LineWidth;
	pLineWidth->setWidth(m_pViewInfo->GetLineWidth());
	osg::ref_ptr<osg::StateSet> state = m_pLine->getOrCreateStateSet();
	state->setAttribute(pLineWidth);

	// Add lines
	int nSum = 0;
	for (int i = 0; i < m_vecPointNum.size(); ++i)
	{
		m_pLine->addPrimitiveSet(new osg::DrawArrays(GL_LINE_STRIP, nSum, m_vecPointNum[i]));
		nSum += m_vecPointNum[i];
	}
}

void CXFaultStickBuilder::_BuildPoints()
{
	// vertices
	m_pPoint->setVertexArray(m_pVertices.get());

	// color
	osg::ref_ptr<osg::Vec3Array> pColor = new osg::Vec3Array;
	QColor color = m_pViewInfo->GetPointColor();
	pColor->push_back(osg::Vec3f(color.redF(), color.greenF(), color.blueF()));
	m_pPoint->setColorArray(pColor.get(), osg::Array::BIND_OVERALL);

	// normal
	m_pPoint->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	osgUtil::SmoothingVisitor::smooth(*m_pPoint);

	// point size
	osg::ref_ptr<osg::Point> pPoint = new osg::Point;
	pPoint->setSize(m_pViewInfo->GetPointSize());
	osg::ref_ptr<osg::StateSet> state = m_pPoint->getOrCreateStateSet();
	state->setAttribute(pPoint);

	// add points
	m_pPoint->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, m_pVertices->size()));
}

void CXFaultStickBuilder::_BuildVertices()
{
	if (!m_pSticks) return;

	m_vecPointNum.clear();
	m_pVertices->clear();

	QList<CXFaultStick *> listStick = m_pSticks->GetAllSticks();
	for (int i = 0; i < listStick.size(); ++i)
	{
		unsigned int nPointNum;
		double* pData = listStick.at(i)->GetXYZData(nPointNum);

		std::vector<osg::Vec3f> vecPoint(nPointNum);

		Vec3d vecWorld;
		osg::Vec3f vecLocal;
		for (int j = 0; j < nPointNum; ++j)
		{
			vecWorld.set(pData[3 * j], pData[3 * j + 1], pData[3 * j + 2]);
			m_pCoordMap->MapWorldToLocal(vecWorld, vecLocal);
			vecPoint[j] = vecLocal;
		}
		if (vecPoint.size() < 2) continue;


		if (m_vecPointNum.empty())
		{
			for (int j = 0; j < nPointNum; ++j)
			{
				m_pVertices->push_back(vecPoint[j]);
			}
		}
		else // tell if need reserse the array
		{
			osg::Vec3f a1 = (*m_pVertices)[0];
			osg::Vec3f a2 = (*m_pVertices)[m_vecPointNum[0] - 1];
			osg::Vec3f b1 = vecPoint[0];
			osg::Vec3f b2 = vecPoint[nPointNum - 1];

			if ((a1 - a2) * (b1 - b2) >= 0)
			{
				for (int j = 0; j < nPointNum; ++j)
				{
					m_pVertices->push_back(vecPoint[j]);
				}
			}
			else
			{
				for (int j = nPointNum - 1; j >= 0; --j)
				{
					m_pVertices->push_back(vecPoint[j]);
				}
			}
		}

		m_vecPointNum.push_back(nPointNum);
	}
}
