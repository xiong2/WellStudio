#include "x3dcompass.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/Camera>
#include <osg/StateSet>
#include <osg/Switch>
#include <osg/Material>
#include <osgUtil/Tessellator>

#include "xwindowinfo3d.h"
#include "x3dwindow.h"
#include "xosgwidget.h"

void CXHUDCamera::traverse(osg::NodeVisitor & nv)
{
	if (m_pMainCamera.valid() && nv.getVisitorType() == osg::NodeVisitor::CULL_VISITOR)
	{
		osg::Matrix matrix = m_pMainCamera->getViewMatrix();
		matrix.setTrans(osg::Vec3());

		if (m_pTransform.valid())
			m_pTransform->setMatrix(matrix);
	}

	m_pTransform->accept(nv);
	osg::Camera::traverse(nv);
}

void CXHUDCamera::SetMainCameraAndTransform(osg::MatrixTransform * pMt, osg::Camera * pCamera)
{
	m_pTransform = pMt;
	m_pMainCamera = pCamera;
}

CX3DCompass::CX3DCompass()
{
}

CX3DCompass::~CX3DCompass()
{
}

osg::ref_ptr<osg::Camera> CX3DCompass::GetCompassNode()
{
	if (m_pCompassCamera.valid())
		return m_pCompassCamera;

	m_pCompassCamera = new CXHUDCamera;
	m_pCompassCamera->setProjectionMatrix(osg::Matrixd::ortho2D(-0.5, 0.5, -0.5, 0.5));
	m_pCompassCamera->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	m_pCompassCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
	m_pCompassCamera->setAllowEventFocus(false);
	m_pCompassCamera->setRenderOrder(osg::Camera::POST_RENDER);
	m_pCompassCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	m_pGeode = new osg::Geode;
	m_pGeode->addDrawable(_BuildGeometry());

	auto pMt = new osg::MatrixTransform;
	pMt->addChild(m_pGeode);
	m_pCompassCamera->SetMainCameraAndTransform(pMt, m_pWin->GetOSGViewWidget()->getCamera());

	return m_pCompassCamera;
}

void CX3DCompass::SetVisible(bool bVisible)
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

void CX3DCompass::SetWindow(CX3DWindow * p3DWin)
{
	m_pWin = p3DWin;
}

void CX3DCompass::UpdateViewInfo()
{
	if (!m_pGeom.valid())
		return;

	CXWindowInfo3D* pWindowInfo = m_pWin->GetWindowInfo();
	const QColor& colorBottom = pWindowInfo->GetCompassBottomColor();
	const QColor& colorTop = pWindowInfo->GetCompassTopColor();
	const QColor& colorFrame = pWindowInfo->GetCompassFrameColor();

	osg::Vec3Array* pColors = new osg::Vec3Array(7);
	(*pColors)[0].set(colorBottom.redF(), colorBottom.greenF(), colorBottom.blueF());
	(*pColors)[1].set(colorBottom.redF(), colorBottom.greenF(), colorBottom.blueF());
	(*pColors)[2].set(colorTop.redF(), colorTop.greenF(), colorTop.blueF());
	(*pColors)[3].set(colorTop.redF(), colorTop.greenF(), colorTop.blueF());
	(*pColors)[4].set(colorFrame.redF(), colorFrame.greenF(), colorFrame.blueF());
	(*pColors)[5].set(colorFrame.redF(), colorFrame.greenF(), colorFrame.blueF());
	(*pColors)[6].set(colorFrame.redF(), colorFrame.greenF(), colorFrame.blueF());

	m_pGeom->setColorArray(pColors, osg::Array::BIND_PER_PRIMITIVE_SET);

	UpdateViewport();
}

void CX3DCompass::UpdateViewport()
{
	if (!m_pCompassCamera.valid())
		return;

	int height = m_pWin->GetOSGViewWidget()->height();
	int width = m_pWin->GetOSGViewWidget()->width();
	constexpr int kSize = 100;
	constexpr int kMargin = 10;

	switch (m_pWin->GetWindowInfo()->GetCompassPosition())
	{
	case 0:
		m_pCompassCamera->setViewport(width - kSize, 0, kSize, kSize);
		break;
	case 1:
		m_pCompassCamera->setViewport(width - kSize, height - kSize - kMargin, kSize, kSize);
		break;
	case 2:
		m_pCompassCamera->setViewport(0, height - kSize - kMargin, kSize, kSize);
		break;
	case 3:
		m_pCompassCamera->setViewport(0, 0, kSize, kSize);
		break;
	default:
		Q_ASSERT(!"Error position");
	}
}

osg::Geometry * CX3DCompass::_BuildGeometry()
{
	m_pGeom = new osg::Geometry;

	osg::Vec3Array* pVertex = new osg::Vec3Array(24);

	auto _SetVertexWithZ = [&](uint iFirst, float fZ) {
		(*pVertex)[iFirst].set(0.f, 6.f * m_ratio, fZ * m_ratio);
		(*pVertex)[iFirst + 1].set(3.f * m_ratio, 0.f, fZ * m_ratio);
		(*pVertex)[iFirst + 2].set(1.f * m_ratio, 1.f * m_ratio, fZ * m_ratio);
		(*pVertex)[iFirst + 3].set(2.f * m_ratio, -6.f * m_ratio, fZ * m_ratio);
		(*pVertex)[iFirst + 4].set(0.f, -4.f * m_ratio, fZ * m_ratio);
		(*pVertex)[iFirst + 5].set(-2.f * m_ratio, -6.f * m_ratio, fZ * m_ratio);
		(*pVertex)[iFirst + 6].set(-1.f * m_ratio, 1.f * m_ratio, fZ * m_ratio);
		(*pVertex)[iFirst + 7].set(-3.f * m_ratio, 0.f, fZ * m_ratio);
	};

	_SetVertexWithZ(0, -1); // bottom
	_SetVertexWithZ(8, 0);  // frame
	_SetVertexWithZ(16, 2); // top

	m_pGeom->setVertexArray(pVertex);

	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_FAN, 0, 8));
	std::vector<uint> vecBottomSideIndex{ 0,8,1,9,2,10,3,11,4,12,5,13,6,14,7,15,0,8 };
	m_pGeom->addPrimitiveSet(new osg::DrawElementsUInt(GL_TRIANGLE_STRIP, vecBottomSideIndex.begin(), vecBottomSideIndex.end()));

	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_FAN, 16, 8));
	std::vector<uint> vecTopSideIndex{ 8,16,9,17,10,18,11,19,12,20,13,21,14,22,15,23,8,16 };
	m_pGeom->addPrimitiveSet(new osg::DrawElementsUInt(GL_TRIANGLE_STRIP, vecTopSideIndex.begin(), vecTopSideIndex.end()));

	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 0, 8));
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 8, 8));
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_LINE_LOOP, 16, 8));

	UpdateViewInfo();

	return m_pGeom.get();
}