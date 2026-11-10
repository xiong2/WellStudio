#include "x3dcursor.h"

#include <QColor>
#include <osg/LineWidth>
#include <osg/Billboard>

#include "xwindow.h"
#include "xcursor.h"
#include "xscene.h"
#include "x3dglobalcoordmap.h"
#include "x3dwindow.h"

CX3DCursor::CX3DCursor()
{
}

CX3DCursor::~CX3DCursor()
{
}

osg::ref_ptr<osg::Group> CX3DCursor::GetCursor()
{
	if (!m_pCamera.valid())
	{
		m_pCamera = new osg::Camera;
		m_pCamera->setProjectionResizePolicy(osg::Camera::FIXED);
		m_pCamera->setRenderOrder(osg::Camera::POST_RENDER);
		m_pCamera->setClearMask(GL_DEPTH_BUFFER_BIT);
		m_pCamera->setAllowEventFocus(false);
		m_pCamera->addChild(_BuildTransform());
	}

	return m_pCamera;
}

void CX3DCursor::SetWindowAndCoordMap(CXWindow * pWin, CX3DGlobalCoordMap* pCoordMap)
{
	m_pWin = pWin;
	m_pCoordMap = pCoordMap;
}

void CX3DCursor::SetVisible(bool bVisible)
{
	if (!m_pCamera.valid())
		return;

	if (!bVisible)
	{
		m_pCamera->removeChild(m_pAutoTrans);
	}
	else
	{
		m_pCamera->addChild(_BuildTransform());
	}
}

void CX3DCursor::UpdatePosition()
{
	if (m_pAutoTrans.valid())
	{
		m_pAutoTrans->setPosition(_GetPosition());
	}
}

osg::Geometry * CX3DCursor::_BuildGeometry()
{
	m_pGeometry = new osg::Geometry;
	m_pGeometry->setVertexArray(_GetVertex());

	osg::ref_ptr<osg::Vec3Array> pColor = new osg::Vec3Array(1);
	QColor color = QColor(Qt::yellow);
	(*pColor)[0].set(color.redF(), color.greenF(), color.blueF());
	m_pGeometry->setColorArray(pColor.get(), osg::Array::BIND_OVERALL);

	m_pGeometry->getOrCreateStateSet()->setAttribute(new osg::LineWidth(2));
	m_pGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, 10));

	return m_pGeometry;
}

osg::Vec3Array * CX3DCursor::_GetVertex()
{
	osg::Vec3Array* pVertex = new osg::Vec3Array(10);
	(*pVertex)[0].set(-12.f, 0.f, 0.f);
	(*pVertex)[1].set(-4.f, 0.f, 0.f);
	(*pVertex)[2].set(4.f, 0.f, 0.f);
	(*pVertex)[3].set(12.f, 0.f, 0.f);

	EXWindowType type = m_pWin->GetWindowType();
	if (e3DWindow == type)
	{
		(*pVertex)[4].set(0.f, 0.f, -12.f);
		(*pVertex)[5].set(0.f, 0.f, -4.f);
		(*pVertex)[6].set(0.f, 0.f, -2.f);
		(*pVertex)[7].set(0.f, 0.f, 2.f);
		(*pVertex)[8].set(0.f, 0.f, 4.f);
		(*pVertex)[9].set(0.f, 0.f, 12.f);
	}
	else if (e3DBaseMap == type)
	{
		(*pVertex)[4].set(0.f, -12.f, 0.f);
		(*pVertex)[5].set(0.f, -4.f, 0.f);
		(*pVertex)[6].set(0.f, -2.f, 0.f);
		(*pVertex)[7].set(0.f, 2.f, 0.f);
		(*pVertex)[8].set(0.f, 4.f, 0.f);
		(*pVertex)[9].set(0.f, 12.f, 0.f);
	}

	return pVertex;
}

osg::Geode * CX3DCursor::_BuildGeode()
{
	EXWindowType type = m_pWin->GetWindowType();
	if (e3DWindow == type)
	{
		osg::Billboard* pBillboard = new osg::Billboard;
		pBillboard->setMode(osg::Billboard::POINT_ROT_EYE);
		pBillboard->addDrawable(_BuildGeometry());

		return pBillboard;
	}
	else if (e3DBaseMap == type)
	{
		osg::Geode* pGeode = new osg::Geode;
		pGeode->addDrawable(_BuildGeometry());

		return pGeode;
	}

	Q_ASSERT(!"no this type.");

	return nullptr;
}

osg::Vec3 CX3DCursor::_GetPosition()
{
	double dX, dY, dZ;
	CXCursor::Instance().GetPosition(dX, dY, dZ);

	osg::Vec3 position;
	m_pCoordMap->MapWorldToLocal(osg::Vec3d(dX, dY, dZ), position);

	CX3DWindow* p3DWindow = dynamic_cast<CX3DWindow*>(m_pWin);
	if (p3DWindow)
	{
		position.z() *= p3DWindow->GetZScale();
	}

	return position;
}

osg::AutoTransform * CX3DCursor::_BuildTransform()
{
	m_pAutoTrans = new osg::AutoTransform;
	m_pAutoTrans->setAutoScaleToScreen(true);
	m_pAutoTrans->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	m_pAutoTrans->addChild(_BuildGeode());

	return m_pAutoTrans;
}
