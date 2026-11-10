#include "x3dautocubeaxes.h"

#include <sstream>
#include <array>

#include <osg/LineWidth>

#include "x3dwindow.h"
#include "x3dscene.h"
#include "xglobal.h"
#include "xautogrid.h"
#include "xwindowinfo3d.h"
#include "x3dutility.h"
#include "xobject.h"
#include "xcoordupdatecallback.h"
#include "xosgwidget.h"
#include "x3dutility.h"

osg::BoundingBox CX3DAutoCubeAxes::GetBoundingBox()
{
	return NX3DUtility::ExpandBox(m_box);
}

void CX3DAutoCubeAxes::UpdateWindowInfo()
{
	if (!m_pGroupAxis.valid())
		return;

	_CalcTickVertices();

	m_pGroupAxis->removeChildren(0, m_pGroupAxis->getNumChildren());

	m_pGroupAxis->addChild(_BuildFrame());
	m_pGroupAxis->addChild(_BuildGrids());
	m_pGroupAxis->addChild(_BuildTicks());
	m_pGroupAxis->addChild(_BuildMarks());
}

void CX3DAutoCubeAxes::ExpandBy(CXObject* pObj)
{
	osg::BoundingBoxd boxObj;
	if (!pObj || !pObj->GetDimension(boxObj.xMin(), boxObj.xMax(), boxObj.yMin(), boxObj.yMax(), boxObj.zMin(), boxObj.zMax()))
		return;

	osg::BoundingBox box;
	m_pCoordMap->MapWorldToLocal(boxObj, box);

	Q_ASSERT(box.valid());

	osg::BoundingBox newBox(m_box);
	newBox.expandBy(box);

	if (newBox == m_box) // boundingbox isn't changed.
		return;

	if (!m_box.valid())
	{
		// init
		m_pGroupAxis = new osg::Group;
		m_pGroupAxis->setName("AutoCubeAxes");
		m_pGroupAxis->setUpdateCallback(new CXCoordUpdateCallback(m_pWin->GetOSGViewWidget()->getCamera()));
		m_pGroupAxis->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	}

	m_box = newBox;

	_UpdateGeometry();
}

void CX3DAutoCubeAxes::UpdateBoundingBox()
{
	QList<QUuid> listObjID = dynamic_cast<CX3DWindow*>(m_pWin)->GetOSGScene()->GetAllDisplayObject();

	osg::BoundingBoxd boxWorld;
	for (QUuid uuidObj : listObjID)
	{
		CXObject* pObj = ::GetObjectByID(uuidObj);

		osg::BoundingBoxd boxObj;
		if (!pObj || !pObj->GetDimension(boxObj.xMin(), boxObj.xMax(), boxObj.yMin(), boxObj.yMax(), boxObj.zMin(), boxObj.zMax()))
			continue;

		boxWorld.expandBy(boxObj);
	}

	if (boxWorld.valid())
	{
		m_pCoordMap->MapWorldToLocal(boxWorld, m_box);
	}
	else
	{
		m_box.init();
	}

	_UpdateGeometry();
}

void CX3DAutoCubeAxes::SetVisible(bool bShow)
{
	m_pGroupAxis->removeChildren(0, m_pGroupAxis->getNumChildren());

	if (bShow)
		_UpdateGeometry();
}

void CX3DAutoCubeAxes::SetGridVisible(bool bShow)
{
	m_pGroupAxis->setChild(1, bShow ? _BuildGrids() : new osg::Switch);
}

void CX3DAutoCubeAxes::_UpdateGeometry()
{
	m_pGroupAxis->removeChildren(0, m_pGroupAxis->getNumChildren());

	if (!m_box.valid())
		return;
	
	_CalcGridVertices();
	_CalcTickVertices();

	m_pGroupAxis->addChild(_BuildFrame());
	m_pGroupAxis->addChild(_BuildGrids());
	m_pGroupAxis->addChild(_BuildTicks());
	m_pGroupAxis->addChild(_BuildMarks());
}

void CX3DAutoCubeAxes::_CalcGridVertices()
{
	Q_ASSERT(m_box.valid());

	double dXMin, dXMax, dYMin, dYMax, dZMin, dZMax;
	const osg::BoundingBox& box = NX3DUtility::ExpandBox(m_box);
	m_pCoordMap->MapLocalToWorld(box.xMin(), box.yMin(), box.zMin(), dXMin, dYMin, dZMax);
	m_pCoordMap->MapLocalToWorld(box.xMax(), box.yMax(), box.zMax(), dXMax, dYMax, dZMin);

	const int nNum = 10;

	m_vecGridX = CXAutoGrid::AutoGrid(dXMin, dXMax, nNum);
	m_vecGridY = CXAutoGrid::AutoGrid(dYMin, dYMax, nNum);
	m_vecGridZ = CXAutoGrid::AutoGrid(dZMin, dZMax, nNum);

	m_pVertexGridX = new osg::Vec3Array;

	for (double dX : m_vecGridX)
	{
		osg::Vec3 local;
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dYMin, dZMax), local); // x00
		m_pVertexGridX->push_back(local);

		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dYMin, dZMin), local); // x01
		m_pVertexGridX->push_back(local);

		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dYMax, dZMax), local); // x10
		m_pVertexGridX->push_back(local);

		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dYMax, dZMin), local); // x11
		m_pVertexGridX->push_back(local);
	}

	m_pVertexGridY = new osg::Vec3Array;

	for (double dY : m_vecGridY)
	{
		osg::Vec3 local;
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dXMin, dY, dZMax), local); // y00
		m_pVertexGridY->push_back(local);

		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dXMin, dY, dZMin), local); // y01
		m_pVertexGridY->push_back(local);

		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dXMax, dY, dZMax), local); // y10
		m_pVertexGridY->push_back(local);

		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dXMax, dY, dZMin), local); // y11
		m_pVertexGridY->push_back(local);
	}

	m_pVertexGridZ = new osg::Vec3Array;

	for (double dZ : m_vecGridZ)
	{
		osg::Vec3 local;
		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dXMin, dYMin, dZ), local); // z00
		m_pVertexGridZ->push_back(local);

		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dXMin, dYMax, dZ), local); // z01
		m_pVertexGridZ->push_back(local);

		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dXMax, dYMin, dZ), local); // z10
		m_pVertexGridZ->push_back(local);

		m_pCoordMap->MapWorldToLocal(osg::Vec3d(dXMax, dYMax, dZ), local); // z11
		m_pVertexGridZ->push_back(local);
	}
}

void CX3DAutoCubeAxes::_CalcTickVertices()
{
	m_vecTicksVertex.clear();
	m_vecTicksVertex.resize(12);
	for (osg::Vec3Array* &pVertex : m_vecTicksVertex)
		pVertex = new osg::Vec3Array;

	float fTickLen = m_pWin->GetWindowInfo()->GetCoordTickLength() * 100;

	for (int i = 0; i < m_pVertexGridX->size(); i += 4)
	{
		float fOffset = (i / 4) % 2 == 0 ? 2 * fTickLen : fTickLen;
		float fZOffset = fOffset / m_pWin->GetWindowInfo()->GetZScale();

		m_vecTicksVertex[0]->push_back(m_pVertexGridX->at(i));
		m_vecTicksVertex[0]->push_back(m_pVertexGridX->at(i) - osg::Vec3(0, fOffset, 0)); // -y
		m_vecTicksVertex[0]->push_back(m_pVertexGridX->at(i) - osg::Vec3(0, 0, fZOffset)); // -z

		m_vecTicksVertex[1]->push_back(m_pVertexGridX->at(i + 1));
		m_vecTicksVertex[1]->push_back(m_pVertexGridX->at(i + 1) - osg::Vec3(0, fOffset, 0)); // -y
		m_vecTicksVertex[1]->push_back(m_pVertexGridX->at(i + 1) + osg::Vec3(0, 0, fZOffset)); // +z

		m_vecTicksVertex[2]->push_back(m_pVertexGridX->at(i + 2));
		m_vecTicksVertex[2]->push_back(m_pVertexGridX->at(i + 2) + osg::Vec3(0, fOffset, 0)); // +y
		m_vecTicksVertex[2]->push_back(m_pVertexGridX->at(i + 2) - osg::Vec3(0, 0, fZOffset)); // -z

		m_vecTicksVertex[3]->push_back(m_pVertexGridX->at(i + 3));
		m_vecTicksVertex[3]->push_back(m_pVertexGridX->at(i + 3) + osg::Vec3(0, fOffset, 0)); // +y
		m_vecTicksVertex[3]->push_back(m_pVertexGridX->at(i + 3) + osg::Vec3(0, 0, fZOffset)); // +z
	}

	for (int i = 0; i < m_pVertexGridY->size(); i += 4)
	{
		float fOffset = (i / 4) % 2 == 0 ? 2 * fTickLen : fTickLen;
		float fZOffset = fOffset / m_pWin->GetWindowInfo()->GetZScale();

		m_vecTicksVertex[4]->push_back(m_pVertexGridY->at(i));
		m_vecTicksVertex[4]->push_back(m_pVertexGridY->at(i) - osg::Vec3(fOffset, 0, 0)); // -x
		m_vecTicksVertex[4]->push_back(m_pVertexGridY->at(i) - osg::Vec3(0, 0, fZOffset)); // -z

		m_vecTicksVertex[5]->push_back(m_pVertexGridY->at(i + 1));
		m_vecTicksVertex[5]->push_back(m_pVertexGridY->at(i + 1) - osg::Vec3(fOffset, 0, 0)); // -x
		m_vecTicksVertex[5]->push_back(m_pVertexGridY->at(i + 1) + osg::Vec3(0, 0, fZOffset)); // +z

		m_vecTicksVertex[6]->push_back(m_pVertexGridY->at(i + 2));
		m_vecTicksVertex[6]->push_back(m_pVertexGridY->at(i + 2) + osg::Vec3(fOffset, 0, 0)); // +x
		m_vecTicksVertex[6]->push_back(m_pVertexGridY->at(i + 2) - osg::Vec3(0, 0, fZOffset)); // -z

		m_vecTicksVertex[7]->push_back(m_pVertexGridY->at(i + 3));
		m_vecTicksVertex[7]->push_back(m_pVertexGridY->at(i + 3) + osg::Vec3(fOffset, 0, 0)); // +x
		m_vecTicksVertex[7]->push_back(m_pVertexGridY->at(i + 3) + osg::Vec3(0, 0, fZOffset)); // +z
	}

	for (int i = 0; i < m_pVertexGridZ->size(); i += 4)
	{
		float fOffset = (i / 4) % 2 == 0 ? 2 * fTickLen : fTickLen;

		m_vecTicksVertex[8]->push_back(m_pVertexGridZ->at(i));
		m_vecTicksVertex[8]->push_back(m_pVertexGridZ->at(i) - osg::Vec3(fOffset, 0, 0)); // -x
		m_vecTicksVertex[8]->push_back(m_pVertexGridZ->at(i) - osg::Vec3(0, fOffset, 0)); // -y

		m_vecTicksVertex[9]->push_back(m_pVertexGridZ->at(i + 1));
		m_vecTicksVertex[9]->push_back(m_pVertexGridZ->at(i + 1) - osg::Vec3(fOffset, 0, 0)); // -x
		m_vecTicksVertex[9]->push_back(m_pVertexGridZ->at(i + 1) + osg::Vec3(0, fOffset, 0)); // +y

		m_vecTicksVertex[10]->push_back(m_pVertexGridZ->at(i + 2));
		m_vecTicksVertex[10]->push_back(m_pVertexGridZ->at(i + 2) + osg::Vec3(fOffset, 0, 0)); // +x
		m_vecTicksVertex[10]->push_back(m_pVertexGridZ->at(i + 2) - osg::Vec3(0, fOffset, 0)); // -y

		m_vecTicksVertex[11]->push_back(m_pVertexGridZ->at(i + 3));
		m_vecTicksVertex[11]->push_back(m_pVertexGridZ->at(i + 3) + osg::Vec3(fOffset, 0, 0)); // +x
		m_vecTicksVertex[11]->push_back(m_pVertexGridZ->at(i + 3) + osg::Vec3(0, fOffset, 0)); // +y
	}
}

osg::Switch* CX3DAutoCubeAxes::_BuildFrame()
{
	auto _CalcFrameVertices = [&]()
	{
		osg::Vec3Array* pVertexFrame = new osg::Vec3Array(8);
		const osg::BoundingBox& box = NX3DUtility::ExpandBox(m_box);

		for (int i = 0; i != 8; ++i)
			(*pVertexFrame)[i].set(box.corner(i));

		return pVertexFrame;
	};

	auto _BuildFramePerFace = [&](const std::array<ushort, 4>& arrIndex)
	{
		osg::Geode* pGeode = new osg::Geode;
		std::ostringstream os;
		for (ushort us : arrIndex) os << us;
		pGeode->setName("Frame" + os.str());

		osg::Geometry* pGeom = new osg::Geometry;
		pGeom->setVertexArray(_CalcFrameVertices());
		pGeom->addPrimitiveSet(new osg::DrawElementsUShort(GL_LINE_LOOP, arrIndex.begin(), arrIndex.end()));
		NX3DUtility::SetSingleColor(pGeom, m_pWin->GetWindowInfo()->GetCoordColor());
		pGeom->getOrCreateStateSet()->setAttribute(new osg::LineWidth(m_pWin->GetWindowInfo()->GetCoordLineWidth()));
		pGeode->addDrawable(pGeom);

		return pGeode;
	};

	osg::Switch* pSwitchFrame = new osg::Switch;
	pSwitchFrame->setName("Coord_Frame");

	pSwitchFrame->addChild(_BuildFramePerFace({ 0, 2, 6, 4 }), true); // Left
	pSwitchFrame->addChild(_BuildFramePerFace({ 1, 3, 7, 5 }), true); // Right
	pSwitchFrame->addChild(_BuildFramePerFace({ 0, 1, 5, 4 }), true); // Near
	pSwitchFrame->addChild(_BuildFramePerFace({ 2, 3, 7, 6 }), true); // Far
	pSwitchFrame->addChild(_BuildFramePerFace({ 0, 1, 3, 2 }), true); // Bottom
	pSwitchFrame->addChild(_BuildFramePerFace({ 4, 5, 7, 6 }), true); // Top

	return pSwitchFrame;
}

osg::Switch * CX3DAutoCubeAxes::_BuildGrids()
{
	int nGridX = m_pVertexGridX->size();
	int nGridY = m_pVertexGridY->size();
	int nGridZ = m_pVertexGridZ->size();

	osg::Vec3Array* pVertexGrids = new osg::Vec3Array;
	pVertexGrids->reserve(nGridX + nGridY + nGridZ);
	pVertexGrids->insert(pVertexGrids->end(), m_pVertexGridX->begin(), m_pVertexGridX->end());
	pVertexGrids->insert(pVertexGrids->end(), m_pVertexGridY->begin(), m_pVertexGridY->end());
	pVertexGrids->insert(pVertexGrids->end(), m_pVertexGridZ->begin(), m_pVertexGridZ->end());

	int iXBeg = 0, iXEnd = nGridX;
	int iYBeg = nGridX, iYEnd = nGridX + nGridY;
	int iZBeg = nGridX + nGridY, iZEnd = nGridX + nGridY + nGridZ;

	auto _BuildGridsPerFace = [&](int iBeg0, int iEnd0, int i00, int i01, int iBeg1, int iEnd1, int i10, int i11)
	{
		osg::Geode* pGeode = new osg::Geode;

		std::ostringstream os;
		os << (iBeg0 == iXBeg ? "x" : iBeg0 == iYBeg ? "y" : "z") << i00 << i01 << "_"
			<< (iBeg1 == iXBeg ? "x" : iBeg0 == iYBeg ? "y" : "z") << i10 << i11;
		pGeode->setName(os.str());

		osg::Geometry* pGeom = new osg::Geometry;
		pGeom->setVertexArray(pVertexGrids);

		osg::DrawElementsUInt* pPrimitives = new osg::DrawElementsUInt(GL_LINES);

		for (int i = iBeg0; i < iEnd0; i += 4)
		{
			pPrimitives->push_back(i + i00);
			pPrimitives->push_back(i + i01);
		}

		for (int i = iBeg1; i < iEnd1; i += 4)
		{
			pPrimitives->push_back(i + i10);
			pPrimitives->push_back(i + i11);
		}

		pGeom->addPrimitiveSet(pPrimitives);
		NX3DUtility::SetSingleColor(pGeom, m_pWin->GetWindowInfo()->GetCoordGridColor());
		pGeom->getOrCreateStateSet()->setAttribute(new osg::LineWidth(m_pWin->GetWindowInfo()->GetCoordGridLineWidth()));
		pGeode->addDrawable(pGeom);

		return pGeode;
	};

	osg::Switch* pSwitchGrids = new osg::Switch;
	pSwitchGrids->setName("Coord_Grids");

	pSwitchGrids->addChild(_BuildGridsPerFace(iYBeg, iYEnd, 0, 1, iZBeg, iZEnd, 0, 1), true); // left   -- YZ
	pSwitchGrids->addChild(_BuildGridsPerFace(iYBeg, iYEnd, 2, 3, iZBeg, iZEnd, 2, 3), true); // right  -/
	pSwitchGrids->addChild(_BuildGridsPerFace(iXBeg, iXEnd, 0, 1, iZBeg, iZEnd, 0, 2), true); // Near   -- XZ
	pSwitchGrids->addChild(_BuildGridsPerFace(iXBeg, iXEnd, 2, 3, iZBeg, iZEnd, 1, 3), true); // Far    -/
	pSwitchGrids->addChild(_BuildGridsPerFace(iXBeg, iXEnd, 0, 2, iYBeg, iYEnd, 0, 2), true); // bottom -- XY
	pSwitchGrids->addChild(_BuildGridsPerFace(iXBeg, iXEnd, 1, 3, iYBeg, iYEnd, 1, 3), true); // top    -/

	return pSwitchGrids;
}

osg::Switch * CX3DAutoCubeAxes::_BuildTicks()
{
	std::vector<std::vector<unsigned>> vecTicksIndex;
	for (osg::Vec3Array* pVertex : m_vecTicksVertex)
	{
		std::vector<unsigned> vecIndex0, vecIndex1;

		for (size_t i = 0; i < pVertex->size(); i += 3)
		{
			vecIndex0.push_back(i);
			vecIndex0.push_back(i + 1);

			vecIndex1.push_back(i);
			vecIndex1.push_back(i + 2);
		}

		vecTicksIndex.push_back(vecIndex0);
		vecTicksIndex.push_back(vecIndex1);
	}

	osg::Switch* pSwitchTicks = new osg::Switch;
	pSwitchTicks->setName("Coord_Ticks");

	for (int i = 0; i < 24; ++i)
	{
		osg::Geode* pGeode = new osg::Geode;
		pGeode->setName("Frame" + std::to_string(i / 2));

		osg::Geometry* pGeom = new osg::Geometry;
		pGeom->setVertexArray(m_vecTicksVertex.at(i / 2));
		pGeom->addPrimitiveSet(new osg::DrawElementsUInt(GL_LINES, vecTicksIndex[i].begin(), vecTicksIndex[i].end()));
		NX3DUtility::SetSingleColor(pGeom, m_pWin->GetWindowInfo()->GetCoordColor());
		pGeode->addDrawable(pGeom);

		pSwitchTicks->addChild(pGeode, true);
	}

	return pSwitchTicks;
}

osg::Switch * CX3DAutoCubeAxes::_BuildMarks()
{
	std::vector<osg::Geode*> vecGeodeMarksPerEdge(24);
	for (osg::Geode* &pGeode : vecGeodeMarksPerEdge)
		pGeode = new osg::Geode;

	for (size_t i = 0; i != 12; ++i)
	{
		const std::vector<double>& vec = i / 4 == 0 ? m_vecGridX : i / 4 == 1 ? m_vecGridY : m_vecGridZ;

		for (size_t j = 0; j < m_vecTicksVertex[i]->size(); j += 6)
		{
			vecGeodeMarksPerEdge[i * 2]->addDrawable(_BuildMark(m_vecTicksVertex[i]->at(j + 1), vec.at(j / 6)));
			vecGeodeMarksPerEdge[i * 2 + 1]->addDrawable(_BuildMark(m_vecTicksVertex[i]->at(j + 2), vec.at(j / 6)));
		}
	}

	osg::Switch* pSwitchMarks = new osg::Switch;
	pSwitchMarks->setName("Coord_Marks");

	for (osg::Geode* pGeode : vecGeodeMarksPerEdge)
		pSwitchMarks->addChild(pGeode, true);

	return pSwitchMarks;
}

osg::Geode * CX3DAutoCubeAxes::_BuildDebugInfo()
{
	osg::Geode* pGeode = new osg::Geode;
	pGeode->setName("DebugInfo");

	const osg::BoundingBox& box = NX3DUtility::ExpandBox(m_box);
	for (int i = 0; i != 8; ++i)
	{
		osgText::Text* pCoordIndex = _BuildMark(box.corner(i), i);
		pCoordIndex->setCharacterSize(m_pWin->GetWindowInfo()->GetCoordMarkSize() * 300);
		pGeode->addDrawable(pCoordIndex);
	}

	return pGeode;
}

osgText::Text * CX3DAutoCubeAxes::_BuildMark(const osg::Vec3 & vecPosition, double d)
{
	auto _OffsetPos = [this](const osg::Vec3& vecPosition, float fWidth)
	{
		osg::Vec3f vecOffset = vecPosition;
		const osg::BoundingBox& box = NX3DUtility::ExpandBox(m_box);

		if (vecOffset.x() > box.xMax()) vecOffset.x() += fWidth * 2;
		if (vecOffset.x() < box.xMin()) vecOffset.x() -= fWidth * 2;
		if (vecOffset.y() > box.yMax()) vecOffset.y() += fWidth * 2;
		if (vecOffset.y() < box.yMin()) vecOffset.y() -= fWidth * 2;
		if (vecOffset.z() > box.zMax()) vecOffset.z() += fWidth / 2;
		if (vecOffset.z() < box.zMin()) vecOffset.z() -= fWidth / 2;

		return vecOffset;
	};

	QString mark = QString("%1").arg(d, 0, 'f', 0);

	osgText::Text* pText = new osgText::Text;
	pText->setFont(::GetOSGFontPath(m_pWin->GetWindowInfo()->GetCoordMarkFont()));
	pText->setCharacterSize(m_pWin->GetWindowInfo()->GetCoordMarkSize() * 100);
	pText->setAxisAlignment(osgText::Text::SCREEN);
	pText->setCharacterSizeMode(osgText::TextBase::OBJECT_COORDS_WITH_MAXIMUM_SCREEN_SIZE_CAPPED_BY_FONT_HEIGHT);
	pText->setColor(NX3DUtility::Color2Vec(m_pWin->GetWindowInfo()->GetCoordColor()));
	pText->setAlignment(osgText::Text::CENTER_CENTER);
	pText->setText(mark.toStdString());
	pText->setPosition(_OffsetPos(vecPosition, pText->getFontWidth() * std::to_string(d).size()));

	return pText;
}
