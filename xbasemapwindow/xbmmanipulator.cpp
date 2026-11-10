#include "xbmmanipulator.h"
#include "xosgwidget.h"
#include "xbasemapwindow.h"
#include "x3dglobalcoordmap.h"
#include <qdebug.h>
#include "xutility.h"
#include "x3dutility.h"
#include "xbasemapscene.h"
#include "xbmsurveycallback.h"

CXBMManipulator::CXBMManipulator()
{
}

CXBMManipulator::~CXBMManipulator()
{
}

bool CXBMManipulator::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{
	auto pView = dynamic_cast<CXOSGWidget*>(&us);
	m_pWin = dynamic_cast<CXBaseMapWindow*>(pView->parent());

	m_pCamera = pView->getCamera();

	switch (ea.getEventType())
	{
		case osgGA::GUIEventAdapter::SCROLL:
		{
			m_pCamera->getProjectionMatrixAsOrtho(m_l, m_r, m_b, m_t, m_n, m_f);
			double rate = ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP ? 1 + _wheelZoomFactor : 1 - _wheelZoomFactor;
			m_pCamera->setProjectionMatrixAsOrtho2D(m_l * rate, m_r * rate, m_b * rate, m_t * rate);
			m_pWin->SetCurrentScale(QString("%1:%2").arg(1).arg(qRound(GetCurrentScale()) * 100));
			m_pWin->GetOSGScene()->SetScaleMark(qRound(GetCurrentScale()));
			_UpdateHUDCamera();
			break;
		}
		case osgGA::GUIEventAdapter::PUSH:
		{
			m_originX = ea.getX();
			m_originY = ea.getY();
			m_pCamera->getProjectionMatrixAsOrtho(m_l, m_r, m_b, m_t, m_n, m_f);
			m_center = getCenter();
			break;
		}
		case osgGA::GUIEventAdapter::DRAG:
		{
			if (m_pWin->IsSelectMode())
				break;

			if (ea.getButtonMask() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON
				&& m_originX != ea.getX() && m_originY != ea.getY())
			{
				osg::Vec3 currCoord = NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(ea.getX(), ea.getY(), 0));
				osg::Vec3 prevCoord = NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(m_originX, m_originY, 0));
				osg::Vec3 distLocal = currCoord - prevCoord;
				
				setCenter(m_center - osg::Vec3d(distLocal.x(), distLocal.y(), 0));
				pView->setCursor(Qt::ClosedHandCursor);
			}
			else if (ea.getButtonMask() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{
				using osg::Matrix;
				const Matrix& windowMatrix = m_pCamera->getViewport()->computeWindowMatrix();
					
				Matrix invW = Matrix::inverse(windowMatrix);
				osg::Vec3 disInWorld = invW.preMult(osg::Vec3(ea.getX(), ea.getY(), 0)) - invW.preMult(osg::Vec3(m_originX, m_originY, 0));
				double rate = (ea.getY() - m_originY < 0) ? (1 - disInWorld.length()) : (1 + disInWorld.length());
				if (rate <= 0)
					break;

				m_pCamera->setProjectionMatrixAsOrtho2D(m_l * rate, m_r * rate, m_b * rate, m_t * rate);

				m_pWin->SetCurrentScale(QString("%1:%2").arg(1).arg(qRound(GetCurrentScale()) * 100));
				m_pWin->GetOSGScene()->SetScaleMark(qRound(GetCurrentScale()));
			}
			break;
		}
		case osgGA::GUIEventAdapter::RELEASE:
		{
			if (m_pWin->IsSelectMode())
				break;

			pView->setCursor(Qt::PointingHandCursor);
			const osg::Vec3d& currentCenter = getCenter();
			m_offsetX += currentCenter.x() - m_center.x();
			m_offsetY += currentCenter.y() - m_center.y();

			break;
		}
		default:
			break;
	}

	return false;
}

float CXBMManipulator::GetCurrentScale()
{
	float disDPIX, disDPIY;
	NXUtility::GetMMPerDPI(disDPIX, disDPIY);

	float fDPIPerCM = 1. / disDPIX * 10.;

	osg::Vec3 distLocal1CM = NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(fDPIPerCM, 0, 0));
	osg::Vec3 distLocal2CM = NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(fDPIPerCM * 2, 0, 0));

	osg::Vec3d vecWorld1, vecWorld2;
	m_pWin->GetCoordMap()->MapLocalToWorld(distLocal1CM, vecWorld1);
	m_pWin->GetCoordMap()->MapLocalToWorld(distLocal2CM, vecWorld2);

	return (vecWorld2 - vecWorld1).length();
}

void CXBMManipulator::GetOffsetCenter(double& offsetX, double& offsetY)
{
	offsetX = m_offsetX;
	offsetY = m_offsetY;
}

void CXBMManipulator::_UpdateHUDCamera()
{
	osg::Camera* pHUDCamera = m_pWin->GetOSGScene()->GetHudCamera();
	if (!pHUDCamera)
		return;
	
	auto pSurveyCallback = dynamic_cast<CXBMSurveyCallback*>(pHUDCamera->getEventCallback());
	if (!pSurveyCallback)
		return;

	pSurveyCallback->UpdateVertexWhileScroll();
}