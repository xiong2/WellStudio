#include "xbmcompass.h"
#include <osg/Projection>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/Hint>
#include <osg/BlendFunc>
#include "xbasemapwindow.h"
#include "xwindowinfobasemap.h"

CXBMCompass::CXBMCompass()
{

}

CXBMCompass::~CXBMCompass()
{

}

osg::ref_ptr<osg::Projection> CXBMCompass::GetCompassNode()
{
	if (m_pCompassProjection.valid())
		return m_pCompassProjection;

	m_pGeode = new osg::Geode;
	m_pGeode->addDrawable(_BuildGeometry());

	osg::StateSet* pStateset = m_pGeode->getOrCreateStateSet();
	pStateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	pStateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	pStateset->setRenderBinDetails(11, "RenderBin");

	// create the hud.
	m_modelView = new osg::MatrixTransform;
	m_modelView->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	m_modelView->setMatrix(osg::Matrix::translate(_GetPosition()));
	m_modelView->addChild(m_pGeode);

	int height = m_pWin->GetOSGViewWidget()->height();
	int width = m_pWin->GetOSGViewWidget()->width();

	m_pCompassProjection = new osg::Projection;
	m_pCompassProjection->setMatrix(osg::Matrix::ortho2D(0, width, 0, height));
	m_pCompassProjection->addChild(m_modelView);

	return m_pCompassProjection;
}

void CXBMCompass::SetVisible(bool bVisible)
{
	if (!m_pGeode.valid())
		return;

	if (!bVisible)
	{
		m_pGeode->removeDrawable(m_pGeom);
	}
	else
	{
		m_pGeode->addDrawable(_BuildGeometry());
	}
}

void CXBMCompass::SetWindow(CXBaseMapWindow* pBMWin)
{
	m_pWin = pBMWin;
}

void CXBMCompass::UpdateViewInfo()
{
	if (!m_pGeom.valid())
		return;
	
	CXWindowInfoBasemap* pWindowInfo = m_pWin->GetWindowInfo();
	const QColor& colorTop = pWindowInfo->GetCompassTopColor();
	
	osg::Vec3Array* pColors = new osg::Vec3Array(1);
	(*pColors)[0].set(colorTop.redF(), colorTop.greenF(), colorTop.blueF());
	m_pGeom->setColorArray(pColors, osg::Array::BIND_OVERALL);

	if (!m_modelView.valid())
		return;

	m_modelView->setMatrix(osg::Matrix::translate(_GetPosition()));
}

void CXBMCompass::UpdatePosition()
{
	if (!m_pCompassProjection.valid() || !m_modelView.valid())
		return;

	int height = m_pWin->GetOSGViewWidget()->height();
	int width = m_pWin->GetOSGViewWidget()->width();

	m_pCompassProjection->setMatrix(osg::Matrix::ortho2D(0, width, 0, height));
	m_modelView->setMatrix(osg::Matrix::translate(_GetPosition()));
}

osg::Geometry* CXBMCompass::_BuildGeometry()
{
	m_pGeom = new osg::Geometry;

	osg::Vec3Array* pVertex = new osg::Vec3Array(8);
	(*pVertex)[0].set(0.f, 6.f * m_ratio, 0.f);
	(*pVertex)[1].set(3.f * m_ratio, 0.f, 0.f);
	(*pVertex)[2].set(1.f * m_ratio, 1.f * m_ratio, 0.f);
	(*pVertex)[3].set(2.f * m_ratio, -6.f * m_ratio, 0.f);
	(*pVertex)[4].set(0.f, -4.f * m_ratio, 0.f);
	(*pVertex)[5].set(-2.f * m_ratio, -6.f * m_ratio, 0.f);
	(*pVertex)[6].set(-1.f * m_ratio, 1.f * m_ratio, 0.f);
	(*pVertex)[7].set(-3.f * m_ratio, 0.f, 0.f);
	m_pGeom->setVertexArray(pVertex);

	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_FAN, 0, 8));

	UpdateViewInfo();

	return m_pGeom.get();
}

osg::Vec3 CXBMCompass::_GetPosition()
{
	CXWindowInfoBasemap* pWindowInfo = m_pWin->GetWindowInfo();

	int width = m_pWin->GetOSGViewWidget()->width();
	int height = m_pWin->GetOSGViewWidget()->height();

	const int margin = 3 * m_ratio;

	switch (pWindowInfo->GetCompassPosition())
	{
	case 0:
		return osg::Vec3(width - 3.f * m_ratio - margin, 6.f * m_ratio + margin, 0.f);
	case 1:
		return osg::Vec3(width - 3.f * m_ratio - margin, height - 6.f * m_ratio - margin, 0.f);
	case 2:
		return osg::Vec3(3.f * m_ratio + margin, height - 6.f * m_ratio - margin, 0.f);
	case 3:
		return osg::Vec3(3.f * m_ratio + margin, 6.f * m_ratio + margin, 0.f);
	default:
		throw std::logic_error("No such position!");
	}

	return osg::Vec3{};
}