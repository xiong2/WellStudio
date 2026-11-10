#include "xbasemapcoordinate.h"
#include <queue>
#include "quuid.h"
#include <QtMath>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osgText/Text>
#include <osg/ComputeBoundsVisitor>
#include "x3dglobalcoordmap.h"
#include "xbasemapwindow.h"
#include "xautogrid.h"
#include "xglobal.h"

CXBasemapCoordinate::CXBasemapCoordinate()
{
	m_boundingBox.init();
}

CXBasemapCoordinate::~CXBasemapCoordinate()
{
}

void CXBasemapCoordinate::SetWinInfoAndCoordMap(CXWindowInfoBasemap* pWinInfo, CX3DGlobalCoordMap* pCoordMap)
{
	m_pWinInfo = pWinInfo;
	m_pCoordMap = pCoordMap;
}

void CXBasemapCoordinate::ExpandBy(const osg::BoundingBox& box)
{
	if (!box.valid())
		return;

	if (!m_boundingBox.valid())
	{
		m_boundingBox = box;
		_BuildCoordinateAxis();
	}
	else 
	{
		// Update
		osg::BoundingBox newBox = m_boundingBox;
		newBox.expandBy(box);

		if (m_boundingBox == newBox)
			return;

		m_boundingBox = newBox;
		_UpdateBoundingBox();
	}
}

void CXBasemapCoordinate::ResetBy(const osg::BoundingBox& box)
{
	if (!box.valid())
		return;

	if (m_boundingBox == box)
		return;

	m_boundingBox = box;
	_UpdateBoundingBox();
}

void CXBasemapCoordinate::_BuildCoordinateAxis()
{
	osg::Geometry *pCoordGeom = new osg::Geometry;

	// vertex
	osg::Vec3Array* m_pVertex = new osg::Vec3Array(4);
	osg::BoundingBox box = _ExpandBox(m_boundingBox);
	(*m_pVertex)[0] = osg::Vec3(box.xMin(), box.yMin(), box.zMax());
	(*m_pVertex)[1] = osg::Vec3(box.xMax(), box.yMin(), box.zMax());
	(*m_pVertex)[2] = osg::Vec3(box.xMax(), box.yMax(), box.zMax());
	(*m_pVertex)[3] = osg::Vec3(box.xMin(), box.yMax(), box.zMax());
	pCoordGeom->setVertexArray(m_pVertex);

	// color
	m_pCoordColor = new osg::Vec4Array(1);
	const QColor& color = m_pWinInfo->GetCoordColor();
	(*m_pCoordColor)[0] = osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	pCoordGeom->setColorArray(m_pCoordColor, osg::Array::BIND_OVERALL);

	pCoordGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, 4));

	// line

	osg::StateSet *pStateSet = pCoordGeom->getOrCreateStateSet();
	m_pBoundingBoxLineWidth = new osg::LineWidth;
	m_pBoundingBoxLineWidth->setWidth(m_pWinInfo->GetCoordLineWidth());
	pStateSet->setAttributeAndModes(m_pBoundingBoxLineWidth, osg::StateAttribute::ON);
	pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	m_pCoordGeode = new osg::Geode;
	m_pCoordGeode->addDrawable(pCoordGeom);

	m_pCoordSwitch = new osg::Switch;
	m_pCoordSwitch->addChild(m_pCoordGeode.get());
	m_pCoordSwitch->setValue(0, m_pWinInfo->GetCoordVisible());

	_CalcTickMarks();
}

void CXBasemapCoordinate::_UpdateBoundingBox()
{
	// Update bounding box vertex

	if (!m_pCoordGeode.valid())
		return;

	osg::Vec3Array* m_pVertex = new osg::Vec3Array(4);
	osg::BoundingBox box = _ExpandBox(m_boundingBox);
	(*m_pVertex)[0] = osg::Vec3(box.xMin(), box.yMin(), box.zMax());
	(*m_pVertex)[1] = osg::Vec3(box.xMax(), box.yMin(), box.zMax());
	(*m_pVertex)[2] = osg::Vec3(box.xMax(), box.yMax(), box.zMax());
	(*m_pVertex)[3] = osg::Vec3(box.xMin(), box.yMax(), box.zMax());

	dynamic_cast<osg::Geometry*>(m_pCoordGeode->getDrawable(0))->setVertexArray(m_pVertex);

	m_pCoordGeode->removeChildren(1, m_pCoordGeode->getNumChildren() - 1);

	_CalcTickMarks();
}

void CXBasemapCoordinate::UpdateWindowInfo()
{
	// visible
	if (m_pCoordSwitch.valid())
	{
		m_pCoordSwitch->setValue(0, m_pWinInfo->GetCoordVisible());
	}

	// color
	const QColor& color = m_pWinInfo->GetCoordColor();
	
	if (m_pCoordColor.valid())
	{
		(*m_pCoordColor)[0] = osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF());
		
		// update all drawables.
		for (uint i = 0; i != m_pCoordGeode->getNumDrawables(); ++i)
		{
			osg::Geometry* pGeom = m_pCoordGeode->getDrawable(i)->asGeometry();
			if (pGeom)
			{
				pGeom->setColorArray(m_pCoordColor, osg::Array::BIND_OVERALL);
				continue;
			}

			osgText::Text* pText = dynamic_cast<osgText::Text*>(m_pCoordGeode->getDrawable(i));
			if (pText)
			{
				pText->setColor(m_pCoordColor->back());
			}
		}
	}
	
	// line width
	if (m_pBoundingBoxLineWidth.valid())
	{
		m_pBoundingBoxLineWidth->setWidth(m_pWinInfo->GetCoordLineWidth());
	}

	if (m_pCoordGeode.valid())
	{
		m_pCoordGeode->removeChildren(1, m_pCoordGeode->getNumChildren() - 1);
		_CalcTickMarks();
	}
}

void CXBasemapCoordinate::_CalcTickMarks()
{
	if (!m_pCoordMap || !m_pWinInfo)
		return;

	// data
	osg::Vec3d leftBottom, rightBottom, leftTop;
	osg::BoundingBox box = _ExpandBox(m_boundingBox);
	m_pCoordMap->MapLocalToWorld(box.corner(4), leftBottom);  // 100
	m_pCoordMap->MapLocalToWorld(box.corner(5), rightBottom); // 101
	m_pCoordMap->MapLocalToWorld(box.corner(6), leftTop);	  // 110

	// Tick Geometry
	osg::Vec3Array* pVecTickVertex = new osg::Vec3Array;
	osg::Geometry* pTickGeom = _CreateTickGeometry(pVecTickVertex);
	m_pCoordGeode->addDrawable(pTickGeom);

	// Grid Geometry
	osg::Vec3Array* pVecGridVertex = new osg::Vec3Array;
	osg::Geometry* pGridGeom = _CreateGridGeometry(pVecGridVertex);

	if (m_pWinInfo->GetCoordGridVisible())
	{
		m_pCoordGeode->addDrawable(pGridGeom);
	}

	// Auto calculate tick and mark number.

	float fWidthXMark, fHeightXMark, fWidthYMark, fHeightYMark;

	float fXMargin = (box.xMax() - box.xMin()) * m_pWinInfo->GetCoordTickLength() / 100.f;
	_GetXMarkInfo(rightBottom.x(), ::GetOSGFontPath(m_pWinInfo->GetCoordMarkFont()), fWidthXMark, fHeightXMark);
	int nXNum = qFloor((box.xMax() - box.xMin()) / (fWidthXMark + fXMargin));

	float fYMargin = (box.yMax() - box.yMin()) * m_pWinInfo->GetCoordTickLength() / 100.f;
	_GetYMarkInfo(leftTop.y(), ::GetOSGFontPath(m_pWinInfo->GetCoordMarkFont()), fWidthYMark, fHeightYMark);
	int nYNum = qFloor((box.yMax() - box.yMin()) / (fHeightYMark + fYMargin));

	if (nXNum == 0 || nYNum == 0)
		return;

	// X

	_DrawXAxisLabel(box, fYMargin, fHeightXMark);
	_DrawYAxisLabel(box, fXMargin, fWidthYMark);

	double dXStart, dXStop, dXStep;
	CXAutoGrid::AutoGrid(leftBottom.x(), rightBottom.x(), nXNum, dXStart, dXStop, dXStep);
	double dX = dXStart > leftBottom.x() ? dXStart : dXStart + dXStep;

	bool bXOdd = true;
	while (dX < dXStop)
	{
		QString markX = QString("%1").arg(dX, 0, 'f', 0);

		osg::Vec3 posBottom, posTop;
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, leftBottom.y(), leftBottom.z()), posBottom);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, leftTop.y(), leftBottom.z()), posTop);

		// Mark
		if (bXOdd)
		{
			osgText::Text* pXBottomMark = new osgText::Text;
			pXBottomMark->setFont(::GetOSGFontPath(m_pWinInfo->GetCoordMarkFont()));
			pXBottomMark->setCharacterSize(m_pWinInfo->GetCoordMarkSize() * 100);
			pXBottomMark->setAxisAlignment(osgText::Text::XY_PLANE);
			pXBottomMark->setAlignment(osgText::Text::CENTER_BOTTOM);
			pXBottomMark->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
			pXBottomMark->setText(markX.toStdString());
			pXBottomMark->setColor(m_pCoordColor->back());
			pXBottomMark->setPosition(posBottom - osg::Vec3(0, fYMargin * 1.2, 0));

			m_pCoordGeode->addDrawable(pXBottomMark);

			osgText::Text* pXTopMark = new osgText::Text(*pXBottomMark, osg::CopyOp::DEEP_COPY_ALL);
			pXBottomMark->setAlignment(osgText::Text::CENTER_TOP);
			pXTopMark->setPosition(posTop + osg::Vec3(0, fYMargin * 1.2, 0));

			m_pCoordGeode->addDrawable(pXTopMark);
		}

		// Tick
		pVecTickVertex->push_back(posBottom);
		pVecTickVertex->push_back(posBottom - osg::Vec3(0, bXOdd ? fYMargin : fYMargin / 2, 0));
		pVecTickVertex->push_back(posTop);
		pVecTickVertex->push_back(posTop + osg::Vec3(0, bXOdd ? fYMargin : fYMargin / 2, 0));
		
		// Grid
		if (bXOdd)
		{
			pVecGridVertex->push_back(posBottom);
			pVecGridVertex->push_back(posTop);
		}

		dX += dXStep;
		bXOdd = !bXOdd;
	}

	// Y

	double dYStart, dYStop, dYStep;
	CXAutoGrid::AutoGrid(leftBottom.y(), leftTop.y(), nYNum, dYStart, dYStop, dYStep);
	double dY = dYStart > leftBottom.y() ? dYStart : dYStart + dYStep;

	bool bYOdd = true;
	while (dY < dYStop)
	{
		QString markY = QString("%1").arg(dY, 0, 'f', 0);

		osg::Vec3 posLeft, posRight;
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(leftBottom.x(), dY, leftBottom.z()), posLeft);
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(rightBottom.x(), dY, leftBottom.z()), posRight);

		// Mark
		if (bYOdd)
		{
			osgText::Text* pYLeftMark = new osgText::Text;
			pYLeftMark->setFont(::GetOSGFontPath(m_pWinInfo->GetCoordMarkFont()));
			pYLeftMark->setCharacterSize(m_pWinInfo->GetCoordMarkSize() * 100);
			pYLeftMark->setAxisAlignment(osgText::Text::XY_PLANE);
			pYLeftMark->setAlignment(osgText::Text::RIGHT_CENTER);
			pYLeftMark->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
			pYLeftMark->setText(markY.toStdString());
			pYLeftMark->setColor(m_pCoordColor->back());
			pYLeftMark->setPosition(posLeft - osg::Vec3(fXMargin * 1.2, 0, 0));

			m_pCoordGeode->addDrawable(pYLeftMark);

			osgText::Text* pYRightMark = new osgText::Text(*pYLeftMark, osg::CopyOp::DEEP_COPY_ALL);
			pYRightMark->setAlignment(osgText::Text::LEFT_CENTER);
			pYRightMark->setPosition(posRight + osg::Vec3(fXMargin * 1.2, 0, 0));

			m_pCoordGeode->addDrawable(pYRightMark);
		}

		// Tick
		pVecTickVertex->push_back(posLeft);
		pVecTickVertex->push_back(posLeft - osg::Vec3(bYOdd ? fXMargin : fXMargin / 2, 0, 0));
		pVecTickVertex->push_back(posRight);
		pVecTickVertex->push_back(posRight + osg::Vec3(bYOdd ? fXMargin : fXMargin / 2, 0, 0));

		// Grid
		if (bYOdd)
		{
			pVecGridVertex->push_back(posLeft);
			pVecGridVertex->push_back(posRight);
		}

		dY += dYStep;
		bYOdd = !bYOdd;
	}

	pTickGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, pVecTickVertex->size()));
	pGridGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, pVecGridVertex->size()));
}

void CXBasemapCoordinate::_DrawXAxisLabel(const osg::BoundingBox& box, float fYMargin, float fHeightXMark)
{
	if (!m_pWinInfo->GetCoordLabelVisible())
		return;

	osgText::Text* pBottomLabelX = new osgText::Text;
	pBottomLabelX->setFont(::GetOSGFontPath(m_pWinInfo->GetCoordLabelFont()));
	pBottomLabelX->setCharacterSize(m_pWinInfo->GetCoordLabelSize() * 100);
	pBottomLabelX->setAxisAlignment(osgText::Text::XY_PLANE);
	pBottomLabelX->setAlignment(osgText::Text::CENTER_TOP);
	pBottomLabelX->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
	pBottomLabelX->setText(m_pWinInfo->GetCoordLabelX().toStdString() + (::UsingMetricUnit() ? "(m)" : "(ft)"));
	pBottomLabelX->setColor(m_pCoordColor->back());
	pBottomLabelX->setPosition(osg::Vec3((box.xMax() + box.xMin()) / 2, box.yMin() - fHeightXMark - fYMargin * 1.2, 0));

	m_pCoordGeode->addDrawable(pBottomLabelX);

	osgText::Text* pTopLabelX = new osgText::Text(*pBottomLabelX, osg::CopyOp::DEEP_COPY_ALL);
	pTopLabelX->setAlignment(osgText::Text::CENTER_BOTTOM);
	pTopLabelX->setPosition(osg::Vec3((box.xMax() + box.xMin()) / 2, box.yMax() + fHeightXMark + fYMargin * 1.2, 0));

	m_pCoordGeode->addDrawable(pTopLabelX);
}

void CXBasemapCoordinate::_DrawYAxisLabel(const osg::BoundingBox& box, float fXMargin, float fWidthYMark)
{
	if (!m_pWinInfo->GetCoordLabelVisible())
		return;
	
	osgText::Text* pLeftLabelY = new osgText::Text;
	pLeftLabelY->setFont(::GetOSGFontPath(m_pWinInfo->GetCoordLabelFont()));
	pLeftLabelY->setCharacterSize(m_pWinInfo->GetCoordLabelSize() * 100);
	pLeftLabelY->setAxisAlignment(osgText::Text::XY_PLANE);
	pLeftLabelY->setAlignment(osgText::Text::CENTER_BOTTOM);
	pLeftLabelY->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
	pLeftLabelY->setText(m_pWinInfo->GetCoordLabelY().toStdString() + (::UsingMetricUnit() ? "(m)" : "(ft)"));
	pLeftLabelY->setColor(m_pCoordColor->back());
	pLeftLabelY->setPosition(osg::Vec3(box.xMin() - fWidthYMark - fXMargin * 1.2, (box.yMax() + box.yMin()) / 2, 0));
	pLeftLabelY->setRotation(osg::Quat(osg::inDegrees(90.f), osg::Vec3(0, 0, 1)));

	m_pCoordGeode->addDrawable(pLeftLabelY);

	osgText::Text* pRightLabelX = new osgText::Text(*pLeftLabelY, osg::CopyOp::DEEP_COPY_ALL);
	pRightLabelX->setAlignment(osgText::Text::CENTER_TOP);
	pRightLabelX->setPosition(osg::Vec3(box.xMax() + fWidthYMark + fXMargin * 1.2, (box.yMax() + box.yMin()) / 2, 0));

	m_pCoordGeode->addDrawable(pRightLabelX);
}

osg::BoundingBox CXBasemapCoordinate::_ExpandBox(const osg::BoundingBox& box)
{
	float expandSize = box.radius() * 0.05;
	return osg::BoundingBox(box.xMin() - expandSize, box.yMin() - expandSize, box.zMin() - expandSize,
		box.xMax() + expandSize, box.yMax() + expandSize, box.zMax() + expandSize);
}

void CXBasemapCoordinate::_GetXMarkInfo(double dMaxX, const std::string& strFontName, float& fWidth, float& fHeight)
{
	QString markMaxX = QString("%1").arg(dMaxX, 0, 'f', 0);

	osg::ref_ptr<osgText::Text> pXMark = new osgText::Text;
	pXMark->setFont(strFontName);
	pXMark->setCharacterSize(m_pWinInfo->GetCoordMarkSize() * 100);
	pXMark->setAxisAlignment(osgText::Text::XY_PLANE);
	pXMark->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
	pXMark->setText(markMaxX.toStdString());
	pXMark->setColor(m_pCoordColor->back());

	const osg::BoundingBox& markBox = pXMark->getBoundingBox();
	fWidth = markBox.xMax() - markBox.xMin();
	fHeight = markBox.yMax() - markBox.yMin();
}

void CXBasemapCoordinate::_GetYMarkInfo(double dMaxY, const std::string& strFontName, float& fWidth, float& fHeight)
{
	QString markY = QString("%1").arg(dMaxY, 0, 'f', 0);

	osgText::Text* pYMark = new osgText::Text;
	pYMark->setFont(strFontName);
	pYMark->setCharacterSize(m_pWinInfo->GetCoordMarkSize() * 100);
	pYMark->setAxisAlignment(osgText::Text::XY_PLANE);
	pYMark->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
	pYMark->setText(markY.toStdString());
	pYMark->setColor(m_pCoordColor->back());

	const osg::BoundingBox& markBox = pYMark->getBoundingBox();
	fWidth = markBox.xMax() - markBox.xMin();
	fHeight = markBox.yMax() - markBox.yMin();
}

osg::Geometry* CXBasemapCoordinate::_CreateTickGeometry(osg::Vec3Array* pVertex)
{
	osg::Geometry* pTickGeom = new osg::Geometry;

	pTickGeom->setVertexArray(pVertex);
	pTickGeom->setColorArray(m_pCoordColor, osg::Array::BIND_OVERALL);

	osg::StateSet *pStateSet = pTickGeom->getOrCreateStateSet();
	osg::LineWidth *pLineWidth = new osg::LineWidth;
	pLineWidth->setWidth(1);
	pStateSet->setAttributeAndModes(pLineWidth, osg::StateAttribute::ON);
	pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	return pTickGeom;
}

osg::Geometry* CXBasemapCoordinate::_CreateGridGeometry(osg::Vec3Array* pVertex)
{
	osg::Geometry* pGridGeom = new osg::Geometry;

	pGridGeom->setVertexArray(pVertex);
	osg::Vec4Array* pGridColor = new osg::Vec4Array(1);
	const QColor& color = m_pWinInfo->GetCoordGridColor();
	(*pGridColor)[0] = osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	pGridGeom->setColorArray(pGridColor, osg::Array::BIND_OVERALL);

	osg::StateSet *pStateSet = pGridGeom->getOrCreateStateSet();
	osg::LineWidth *pLineWidth = new osg::LineWidth;
	pLineWidth->setWidth(m_pWinInfo->GetCoordGridLineWidth());
	pStateSet->setAttributeAndModes(pLineWidth, osg::StateAttribute::ON);
	pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	return pGridGeom;
}