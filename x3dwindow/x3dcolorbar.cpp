#include "x3dcolorbar.h"
#include "xglobal.h"
#include "xwindow.h"
#include "xscene.h"
#include "xwindowinfo.h"
#include "xviewinfoobject.h"
#include "xcolormap.h"
#include "xautogrid.h"

CX3DColorbar::CX3DColorbar()
{
}

CX3DColorbar::~CX3DColorbar()
{
}

osg::ref_ptr<osg::Group> CX3DColorbar::GetColorbar()
{
	if (!m_pSwitch.valid())
	{
		m_pMT = new osg::MatrixTransform;
		m_pMT->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
		m_pMT->setMatrix(osg::Matrix::translate(_CalcRainbowTranslate()));

		m_pProjection = new osg::Projection;
		m_pProjection->setMatrix(osg::Matrix::ortho2D(0, m_pWin->width(), 0, m_pWin->height()));
		m_pProjection->addChild(m_pMT);

		m_pSwitch = new osg::Switch;
		m_pSwitch->addChild(m_pProjection, true);
	}

	return m_pSwitch;
}

void CX3DColorbar::SetWindow(CXWindow * pWin)
{
	m_pWin = pWin;
	m_pWinInfo = dynamic_cast<CXWindowInfo*>(pWin->GetWindowInfo());
}

void CX3DColorbar::PushObj(const QUuid & uuidGeomObj)
{
	CXObject* pGeomObj = ::GetObjectByID(uuidGeomObj);
	CXViewInfoObject* pViewInfo = m_pWin->GetObjectViewInfo(uuidGeomObj);

	if (!pGeomObj || !pGeomObj->HasHistogram() || !pViewInfo || !pViewInfo->GetNeedColormap())
		return;

	if (m_stackObjID.isEmpty())
	{
		_BuildHUD(uuidGeomObj);
	}
	else
	{
		_ObjectChanged(uuidGeomObj);
	}

	m_stackObjID.push(uuidGeomObj);
}

void CX3DColorbar::RemoveObj(const QUuid & uuidGeomObj)
{
	m_stackObjID.removeAll(uuidGeomObj);
	if (m_stackObjID.isEmpty())
	{
		m_pMT->removeChild(m_pGeode);
		return;
	}

	_ObjectChanged(m_stackObjID.top());
}

void CX3DColorbar::UpdateObj(const QUuid & uuidGeomObj)
{
	if (m_stackObjID.isEmpty() || m_stackObjID.top() != uuidGeomObj)
		return;

	_ObjectChanged(uuidGeomObj);
}

void CX3DColorbar::Clear()
{
	m_stackObjID.clear();
	m_pMT->removeChild(m_pGeode);
}

void CX3DColorbar::UpdateViewInfo()
{
	if (!m_pMT.valid() || !m_pGeode.valid() || m_stackObjID.isEmpty())
		return;

	m_pMT->setMatrix(osg::Matrix::translate(osg::Vec3(_CalcRainbowTranslate())));

	m_pGeode->removeDrawable(m_pTextObjName);
	m_pGeode->addDrawable(_BuildObjName(m_stackObjID.top()));

	m_pGeode->removeDrawable(m_pGeom);
	m_pGeode->addDrawable(_BuildRainbow(m_stackObjID.top()));

	for (auto pMark : m_listMarks)
	{
		m_pGeode->removeDrawable(pMark);
	}
	for (auto pMark : _BuildMarks(m_stackObjID.top()))
	{
		m_pGeode->addDrawable(pMark);
	}

	m_pGeode->removeDrawable(m_pGeomTicks);
	m_pGeode->addDrawable(_BuildTicks(m_listMarks.size()));
}

void CX3DColorbar::UpdatePosition()
{
	if (!m_pProjection.valid() || !m_pMT.valid())
		return;

	m_pProjection->setMatrix(osg::Matrix::ortho2D(0, m_pWin->width(), 0, m_pWin->height()));
	m_pMT->setMatrix(osg::Matrix::translate(osg::Vec3(_CalcRainbowTranslate())));
}

void CX3DColorbar::SetVisible(bool bVisible)
{
	if (!m_pSwitch.valid())
		return;

	m_pSwitch->setValue(0, bVisible);
}

void CX3DColorbar::_BuildHUD(const QUuid& objID)
{
	m_pGeode = new osg::Geode;
	m_pGeode->addDrawable(_BuildObjName(objID));
	m_pGeode->addDrawable(_BuildRainbow(objID));
	for (auto pMark : _BuildMarks(objID))
	{
		m_pGeode->addDrawable(pMark);
	}
	m_pGeode->addDrawable(_BuildTicks(m_listMarks.size()));

	osg::StateSet *pStateSet = m_pGeode->getOrCreateStateSet();
	pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	pStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	pStateSet->setRenderBinDetails(11, "RenderBin");

	m_pMT->addChild(m_pGeode);
}

osgText::Text * CX3DColorbar::_BuildObjName(const QUuid& objID)
{
	if (!m_pWinInfo->GetColorbarTitleVisible())
		return nullptr;

	QString font = m_pWinInfo->GetColorbarTitleFont();
	const QColor& color = m_pWinInfo->GetColorbarTitleColor();
	int size = m_pWinInfo->GetColorbarTitleSize();

	m_pTextObjName = new osgText::Text;
	m_pTextObjName->setAxisAlignment(osgText::TextBase::XY_PLANE);
	m_pTextObjName->setAlignment(osgText::TextBase::LEFT_BOTTOM);
	m_pTextObjName->setPosition(osg::Vec3(-m_fRainbowWidth / 2, m_fRainbowHeight / 2 + 5.f, 0.f));
	m_pTextObjName->setFont(::GetOSGFontPath(font));
	m_pTextObjName->setColor(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
	m_pTextObjName->setCharacterSize(size * 8);

	_SetObjName(objID);

	return m_pTextObjName.get();
}

osg::Geometry * CX3DColorbar::_BuildRainbow(const QUuid& objID)
{
	CXViewInfoObject* pViewInfo = m_pWin->GetObjectViewInfo(objID);
	CXColormap* pColormap = CXColormap::GetColormap(pViewInfo->GetColormapName());

	m_pGeom = new osg::Geometry;
	m_pGeom->setVertexArray(_CalcRainbowVertex(pColormap));
	m_pGeom->setColorArray(_CalcRainbowColors(pColormap), osg::Array::BIND_PER_VERTEX);
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUAD_STRIP, 0, pColormap->GetColorNum() * 2));
	return m_pGeom.get();
}

const QList<osg::ref_ptr<osgText::Text>>& CX3DColorbar::_BuildMarks(const QUuid& objID)
{
	CXViewInfoObject* pViewInfo = m_pWin->GetObjectViewInfo(objID);
	double dMin = pViewInfo->GetDisplayDataMin();
	double dMax = pViewInfo->GetDisplayDataMax();
	Q_ASSERT(dMin <= dMax);

	const QColor& color = m_pWinInfo->GetColorbarMarkColor();
	int size = m_pWinInfo->GetColorbarMarkSize();
	const QString& font = m_pWinInfo->GetColorbarMarkFont();
	int len = m_pWinInfo->GetColorbarTickSize();

	int nScales = 10;
	double dUniStart = dMin, dUniStop = dMax, dStep = 0.0;

	if (dMin < dMax)
	{
		CXAutoGrid::AutoGrid(dMin, dMax, nScales, dUniStart, dUniStop, dStep);

		if (dUniStart != dUniStop)
		{
			nScales = (dUniStop - dUniStart) / dStep + 1;
		}
	}

	float fSpacing = m_fRainbowHeight / (nScales - 1);
	osg::Vec3 posLeftBottom{ -m_fRainbowWidth / 2, -m_fRainbowHeight / 2, 0.f };

	m_listMarks.clear();

	for (int i = 0; i != nScales; ++i)
	{
		osg::ref_ptr<osgText::Text> pMark = new osgText::Text;
		pMark->setFont(::GetOSGFontPath(font));
		pMark->setColor(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
		pMark->setCharacterSize(size);
		pMark->setAxisAlignment(osgText::TextBase::XY_PLANE);
		pMark->setAlignment(osgText::TextBase::LEFT_CENTER);
		pMark->setPosition(posLeftBottom + osg::Vec3(m_fRainbowWidth + 2 * len, i * fSpacing, 0.f));
		pMark->setText(CXAutoGrid::TrimToStdString(dUniStart + i * dStep));

		m_listMarks << pMark;
	}

	return m_listMarks;
}

osg::Geometry * CX3DColorbar::_BuildTicks(int nScales)
{
	const QColor& color = m_pWinInfo->GetColorbarTickColor();
	int len = m_pWinInfo->GetColorbarTickSize();

	m_pGeomTicks = new osg::Geometry;

	osg::Vec3Array* pVertex = new osg::Vec3Array(nScales * 2);
	float fSpacing = m_fRainbowHeight / (nScales - 1);
	osg::Vec3 posLeftBottom{ -m_fRainbowWidth / 2, -m_fRainbowHeight / 2, 0.f };
	for (int i = 0; i != nScales; ++i)
	{
		(*pVertex)[2 * i].set(posLeftBottom + osg::Vec3(m_fRainbowWidth, i * fSpacing, 0.f));
		(*pVertex)[2 * i + 1].set(posLeftBottom + osg::Vec3(m_fRainbowWidth + len, i * fSpacing, 0.f));
	}
	m_pGeomTicks->setVertexArray(pVertex);
	m_pGeomTicks->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, nScales * 2));

	osg::Vec4Array* pColors = new osg::Vec4Array(1);
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	m_pGeomTicks->setColorArray(pColors, osg::Array::BIND_OVERALL);

	return m_pGeomTicks.get();
}

osg::Vec3 CX3DColorbar::_CalcRainbowTranslate()
{
	osg::Vec3 vecTranslate;

	switch (m_pWinInfo->GetColorbarPosition())
	{
	case 0: // left top
		vecTranslate.set(m_fOffset + m_fRainbowWidth / 2, m_pWin->height() - 2 * m_fOffset - m_fRainbowHeight / 2, 0.f);
		break;
	case 1: // left bottom
		vecTranslate.set(m_fOffset + m_fRainbowWidth / 2, m_fOffset + m_fRainbowHeight / 2, 0.f);
		break;
	case 2: // right bottom
		vecTranslate.set(m_pWin->width() - 3 * m_fRainbowWidth, m_fOffset + m_fRainbowHeight / 2, 0.f);
		break;
	case 3: // right top
		vecTranslate.set(m_pWin->width() - 3 * m_fRainbowWidth, m_pWin->height() - 2 * m_fOffset - m_fRainbowHeight / 2, 0.f);
		break;
	default:
		throw std::logic_error("no this position type.");
	}

	return vecTranslate;
}

osg::Vec3Array * CX3DColorbar::_CalcRainbowVertex(CXColormap* pColormap)
{
	auto pVertex = new osg::Vec3Array(pColormap->GetColorNum() * 2);

	osg::Vec3 posLeftBottom{ -m_fRainbowWidth / 2, -m_fRainbowHeight / 2, 0.f };
	float fSpacing = m_fRainbowHeight / (pColormap->GetColorNum() - 1);
	for (int i = 0; i != pColormap->GetColorNum(); ++i)
	{
		(*pVertex)[2 * i] = posLeftBottom + osg::Vec3(0.f, i * fSpacing, 0.f);
		(*pVertex)[2 * i + 1] = posLeftBottom + osg::Vec3(m_fRainbowWidth, i * fSpacing, 0.f);
	}

	return pVertex;
}

osg::Vec4Array * CX3DColorbar::_CalcRainbowColors(CXColormap* pColormap)
{
	auto pColors = new osg::Vec4Array(pColormap->GetColorNum() * 2);

	for (int i = 0; i < pColormap->GetColorNum(); ++i)
	{
		const QColor& color = pColormap->ColorAt(i);
		(*pColors)[2 * i].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
		(*pColors)[2 * i + 1].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	}

	return pColors;
}

void CX3DColorbar::_SetObjName(const QUuid & objID)
{
	CXViewInfoObject* pViewInfo = m_pWin->GetObjectViewInfo(objID);
	CXObject* pAttribute = ::GetObjectByID(pViewInfo->GetAttributeObjID());

	if (pAttribute && m_pTextObjName.valid())
	{
		m_pTextObjName->setText(pAttribute->GetObjectName().toStdString());
	}
}

void CX3DColorbar::_ObjectChanged(const QUuid & objID)
{
	if (!m_pGeode.valid())
		return;

	_SetObjName(objID);

	m_pGeode->removeDrawable(m_pGeom);
	m_pGeode->addDrawable(_BuildRainbow(objID));

	for (auto pMark : m_listMarks)
	{
		m_pGeode->removeDrawable(pMark);
	}

	for (auto pMark : _BuildMarks(objID))
	{
		m_pGeode->addDrawable(pMark);
	}

	m_pGeode->removeDrawable(m_pGeomTicks);
	m_pGeode->addDrawable(_BuildTicks(m_listMarks.size()));
}
