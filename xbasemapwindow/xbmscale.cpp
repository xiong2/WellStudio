#include "xbmscale.h"

#include <osg/Projection>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgText/Text>
#include <osg/MatrixTransform>

#include "x3dutility.h"
#include "xutility.h"
#include "xbasemapwindow.h"
#include "xwindowinfobasemap.h"
#include "xbmmanipulator.h"
#include "xglobal.h"

CXBMScale::CXBMScale()
{

}

CXBMScale::~CXBMScale()
{

}

void CXBMScale::SetWindow(CXBaseMapWindow* pBMWin)
{
	m_pWin = pBMWin;
}

osg::ref_ptr<osg::Projection> CXBMScale::GetScaleNode()
{
	if (m_pScaleProjection.valid())
		return m_pScaleProjection;

	m_pGeode = new osg::Geode;
	m_pGeode->addDrawable(_BuildGeometry());
	m_pGeode->addDrawable(_BuildMark());

	osg::StateSet* pStateset = m_pGeode->getOrCreateStateSet();
	pStateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	pStateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	pStateset->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
	pStateset->setRenderBinDetails(11, "RenderBin");

	// create the hud.
	m_modelview = new osg::MatrixTransform;
	m_modelview->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	m_modelview->setMatrix(osg::Matrix::translate(_GetTranslatePos()));
	m_modelview->addChild(m_pGeode);

	int height = m_pWin->GetOSGViewWidget()->height();
	int width = m_pWin->GetOSGViewWidget()->width();

	m_pScaleProjection = new osg::Projection;
	m_pScaleProjection->setMatrix(osg::Matrix::ortho2D(0, width, 0, height));
	m_pScaleProjection->addChild(m_modelview);
	
	return m_pScaleProjection;
}

void CXBMScale::UpdateScale(int iScale)
{
	if (!m_pMark.valid())
		return;

	m_pMark->setText(std::to_string(iScale) + "(m)");
}

void CXBMScale::UpdateViewInfo()
{
	_UpdateMarkInfo();
	_UpdateFrameInfo();

	if (!m_modelview.valid())
		return;

	m_modelview->setMatrix(osg::Matrix::translate(_GetTranslatePos()));
}

void CXBMScale::UpdatePosition()
{
	if (!m_pScaleProjection.valid() || !m_modelview.valid())
		return;
	
	int height = m_pWin->GetOSGViewWidget()->height();
	int width = m_pWin->GetOSGViewWidget()->width();

	m_pScaleProjection->setMatrix(osg::Matrix::ortho2D(0, width, 0, height));
	m_modelview->setMatrix(osg::Matrix::translate(_GetTranslatePos()));
}

void CXBMScale::SetVisible(bool bVisible)
{
	if (!m_pGeode.valid())
		return;

	if (!bVisible)
	{
		m_pGeode->removeDrawables(0, m_pGeode->getNumDrawables());
	}
	else
	{
		m_pGeode->addDrawable(_BuildGeometry());
		m_pGeode->addDrawable(_BuildMark());
	}
}

osg::Geometry* CXBMScale::_BuildGeometry()
{
	m_pGeom = new osg::Geometry;

	float disDPIX, disDPIY;
	NXUtility::GetMMPerDPI(disDPIX, disDPIY);
	float fDPIPerCM = 1. / disDPIX * 10.;

	osg::Vec3Array* pVertex = new osg::Vec3Array(10);
	for (int i = 0; i != 5; ++i)
	{
		(*pVertex)[2 * i].set((i - 2) * fDPIPerCM, 0.1*fDPIPerCM, 0.f);
		(*pVertex)[2 * i + 1].set((i - 2) * fDPIPerCM, -0.1*fDPIPerCM, 0.f);
	}
	m_pGeom->setVertexArray(pVertex);

	std::vector<uint> vecBound{0, 1, 3, 5, 7, 9, 8, 6, 4, 2};
	m_pGeom->addPrimitiveSet(new osg::DrawElementsUInt(GL_LINE_LOOP, vecBound.cbegin(), vecBound.cend()));
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_STRIP, 0, 4));
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_STRIP, 2, 4));
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_STRIP, 4, 4));
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_STRIP, 6, 4));

	osg::Vec4Array* pColors = new osg::Vec4Array(5);
	(*pColors)[0].set(1.f, 1.f, 1.f, 1.f);
	(*pColors)[1].set(0.f, 0.f, 0.f, 1.f);
	(*pColors)[2].set(1.f, 1.f, 1.f, 1.f);
	(*pColors)[3].set(0.f, 0.f, 0.f, 1.f);
	(*pColors)[4].set(1.f, 1.f, 1.f, 1.f);
	m_pGeom->setColorArray(pColors, osg::Array::BIND_PER_PRIMITIVE_SET);

	_UpdateFrameInfo();

	return m_pGeom;
}

osgText::Text* CXBMScale::_BuildMark()
{
	m_pMark = new osgText::Text;
	m_pMark->setAlignment(osgText::Text::LEFT_CENTER);

	float disDPIX, disDPIY;
	NXUtility::GetMMPerDPI(disDPIX, disDPIY);
	float fDPIPerCM = 1. / disDPIX * 10.;

	m_pMark->setPosition(osg::Vec3(2.2 * fDPIPerCM, 0.f, 0.f));

	_UpdateMarkInfo();

	return m_pMark;
}

void CXBMScale::_UpdateMarkInfo()
{
	if (!m_pMark.valid())
		return;

	// window info
	CXWindowInfoBasemap* pWindowInfo = m_pWin->GetWindowInfo();
	const QColor& color = pWindowInfo->GetScaleMarkColor();
	int size = pWindowInfo->GetScaleMarkSize();
	QString font = pWindowInfo->GetScaleMarkFont();

	m_pMark->setCharacterSize(size * 5);
	m_pMark->setFont(::GetOSGFontPath(font));
	m_pMark->setColor(osg::Vec4(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
}

void CXBMScale::_UpdateFrameInfo()
{
	if (!m_pGeom.valid())
		return;

	CXWindowInfoBasemap* pWindowInfo = m_pWin->GetWindowInfo();
	const QColor& color = pWindowInfo->GetScaleFrameColor();

	auto pColors = dynamic_cast<osg::Vec4Array*>(m_pGeom->getColorArray());
	(*pColors)[0].set(color.redF(), color.greenF(), color.blueF(), color.alphaF());
	m_pGeom->setColorArray(pColors);
}

osg::Vec3 CXBMScale::_GetTranslatePos()
{
	CXWindowInfoBasemap* pWindowInfo = m_pWin->GetWindowInfo();

	int width = m_pWin->GetOSGViewWidget()->width();
	int height = m_pWin->GetOSGViewWidget()->height();

	float disDPIX, disDPIY;
	NXUtility::GetMMPerDPI(disDPIX, disDPIY);
	float fDPIPerCM = 1. / disDPIX * 10.;

	switch (pWindowInfo->GetScalebarPosition())
	{
	case 0:
		return osg::Vec3(3 * fDPIPerCM, 1.1 * fDPIPerCM, 0.f);
	case 1:
		return osg::Vec3(width - 4 * fDPIPerCM, 1.1 * fDPIPerCM, 0.f);
	case 2:
		return osg::Vec3(width - 4 * fDPIPerCM, height - 1.1 * fDPIPerCM, 0.f);
	case 3:
		return osg::Vec3(3 * fDPIPerCM, height - 1.1 * fDPIPerCM, 0.f);
	default:
		throw std::logic_error("no such position.");
	}

	return osg::Vec3{};
}