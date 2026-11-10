#include "xbmsurveycallback.h"

#include <osg/Camera>
#include <osg/Point>
#include <osg/Group>

#include <QDebug>

#include "x3dutility.h"
#include "xbasemapwindow.h"
#include "xbasemapscene.h"
#include "xgraphicsapi.h"

CXBMSurveyCallback::CXBMSurveyCallback(osg::Camera* pHUDCamera, CXBaseMapWindow* pBMWindow)
	: osg::Callback(), m_pWin(pBMWindow), m_pHUDCamera(pHUDCamera)
{
	m_pHUDCamera->addChild(_BuildPointLinesGeode());

	m_pCamera = m_pWin->GetOSGViewWidget()->getCamera();
}

CXBMSurveyCallback::~CXBMSurveyCallback()
{

}

void CXBMSurveyCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	_Process(node, nv);

	traverse(node, nv);
}

void CXBMSurveyCallback::UpdateVertexWhileScroll()
{
	if (m_pVertex->empty())
		return;

	m_pVertex->clear();
	for (osg::Vec3 vecLocal : m_vLocal)
	{
		osg::Vec3 screenPos = NX3DUtility::MapToScene(m_pCamera, vecLocal);
		osg::Vec3 theHUDPos = NX3DUtility::MapToLocal(m_pHUDCamera, screenPos);
		m_pVertex->push_back(theHUDPos);
	}

	_Update();
}

void CXBMSurveyCallback::GetXYofTuringPoint(std::vector<double>& vecX, std::vector<double>& vecY)
{
	vecX.clear(); vecY.clear();
	for (osg::Vec3 vecLocal : m_vLocal)
	{
		osg::Vec3d vecWorld;
		m_pWin->GetCoordMap()->MapLocalToWorld(vecLocal, vecWorld);
		vecX.push_back(vecWorld.x());
		vecY.push_back(vecWorld.y());
	}
}

void CXBMSurveyCallback::GetData(double* &pData, int& nSize)
{
	nSize = m_vLocal.size() * 2;

	pData = new double[nSize];
	for (decltype(m_vLocal.size()) i = 0; i != m_vLocal.size(); ++i)
	{
		osg::Vec3d vecWorld;
		m_pWin->GetCoordMap()->MapLocalToWorld(m_vLocal.at(i), vecWorld);
		pData[i * 2] = vecWorld.x();
		pData[i * 2 + 1] = vecWorld.y();
	}
}

void CXBMSurveyCallback::_Process(osg::Node* node, osg::NodeVisitor* nv)
{
	if (!(m_pWin->IsRandomSectionCreating() || m_pWin->IsPolygonCreating()))
		return;

	osgGA::EventVisitor* ev = dynamic_cast<osgGA::EventVisitor*>(nv);
	if (!ev)
		return;

	const osgGA::EventQueue::Events &events = ev->getEvents();
	for (osg::ref_ptr<osgGA::Event> pEvent : events)
	{
		using EA = osgGA::GUIEventAdapter;

		auto ea = dynamic_cast<EA*>(pEvent.get());
		if (EA::FRAME == ea->getEventType())
			continue;

		if (EA::PUSH == ea->getEventType() && EA::LEFT_MOUSE_BUTTON == ea->getButton())
		{
			// left mouse click
			m_x = ea->getX();
			m_y = ea->getY();
		}
		else if (EA::RELEASE == ea->getEventType() && EA::LEFT_MOUSE_BUTTON == ea->getButton())
		{
			// click
			if (ea->getX() != m_x || ea->getY() != m_y)
				continue;

			osg::Vec2 curPos(ea->getX(), ea->getY());

			if (m_pWin->IsRandomSectionCreating() && !m_pWin->GetOSGScene()->IsInSurvey(curPos))
				continue;
			
			if (m_pWin->IsPolygonCreating() && NX3DUtility::IsPolygonSelfIntersection(m_pVertex, m_x, m_y))
				continue;

			_Append(curPos);
		}
		else if (EA::MOVE == ea->getEventType())
		{
			// move
			if (m_pVertex->empty())
				continue;

			osg::Vec2 movePos(ea->getX(), ea->getY());

			_Aim(movePos);
		}
		else if (EA::RELEASE == ea->getEventType() && EA::MIDDLE_MOUSE_BUTTON == ea->getButton())
		{
			// cancel
			if (m_pVertex->empty())
			{
				continue;
			}
			else if (2 >= m_pVertex->size())
			{
				_Clear();
			}
			else
			{
				_Pop();
			}
		}
		else if (EA::DOUBLECLICK == ea->getEventType() && EA::LEFT_MOUSE_BUTTON == ea->getButton())
		{
			// done.
			if (m_pVertex->size() < 2)
				continue;

			_Done();
			break;
		}
	}
}

osg::Geode* CXBMSurveyCallback::_BuildPointLinesGeode()
{
	osg::Geode* pGeode = new osg::Geode;

	osg::StateSet* pStateSet = pGeode->getOrCreateStateSet();
	pStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	pGeode->addDrawable(_BuildPointLinesGeometry());
	
	return pGeode;
}

osg::Geometry* CXBMSurveyCallback::_BuildPointLinesGeometry()
{
	m_pGeom = new osg::Geometry;

	m_pVertex = new osg::Vec3Array;
	m_pGeom->setVertexArray(m_pVertex);
	
	osg::Vec3Array* pColors = new osg::Vec3Array(1);
	(*pColors)[0].set(1.0, 1.0, 0.0);
	m_pGeom->setColorArray(pColors, osg::Array::BIND_OVERALL);

	m_pGeom->getOrCreateStateSet()->setAttributeAndModes(new osg::Point(10.f), osg::StateAttribute::ON);

	return m_pGeom.get();
}

GLenum CXBMSurveyCallback::_GetShapeType()
{
	if (m_pWin->IsPolygonCreating())
		return GL_LINE_LOOP;
	else if (m_pWin->IsRandomSectionCreating())
		return GL_LINE_STRIP;
	else
		return GL_POINTS;
}

void CXBMSurveyCallback::_SetReady(bool bReady)
{
	if (m_pWin->IsPolygonCreating())
		m_pWin->SetPolygonlineReady(true);
	else if (m_pWin->IsRandomSectionCreating())
		m_pWin->SetRandomSectionReady(true);
}

void CXBMSurveyCallback::_Append(const osg::Vec2& newPos)
{
	osg::Vec3 HUDPos = NX3DUtility::MapToLocal(m_pHUDCamera, osg::Vec3(newPos, 0.f));
	HUDPos.z() = 0.f;
	m_pVertex->push_back(HUDPos);

	osg::Vec3 localPos = NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(newPos, 0.f));
	localPos.z() = 0.f;
	m_vLocal.push_back(localPos);
	
	_Update();
}

void CXBMSurveyCallback::_Aim(const osg::Vec2& movePos)
{
	osg::Vec3 HUDPos = NX3DUtility::MapToLocal(m_pHUDCamera, osg::Vec3(movePos, 0.f));
	HUDPos.z() = 0.f;

	osg::Vec3 localPos = NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(movePos, 0.f));
	localPos.z() = 0.f;

	if (1 == m_pVertex->size())
	{
		m_pVertex->push_back(HUDPos);
		m_vLocal.push_back(localPos);
	}
	else
	{
		m_pVertex->back().set(HUDPos);
		m_vLocal.back().set(localPos);
	}

	_Update();
}

void CXBMSurveyCallback::_Pop()
{
	m_pVertex->erase(std::prev(m_pVertex->end(), 2));
	m_vLocal.erase(std::prev(m_vLocal.end(), 2));
	_Update();
}

void CXBMSurveyCallback::_Clear()
{
	m_pGeom->dirtyDisplayList();
	m_pVertex->clear();
	m_vLocal.clear();
	m_pGeom->setVertexArray(m_pVertex);
	m_pGeom->removePrimitiveSet(0, m_pGeom->getNumPrimitiveSets());
}

void CXBMSurveyCallback::_Done()
{
	m_pVertex->pop_back();
	m_vLocal.pop_back();
	_Update();
	_SetReady(true);
}

void CXBMSurveyCallback::_Update()
{
	m_pGeom->dirtyDisplayList();
	m_pGeom->setVertexArray(m_pVertex);
	m_pGeom->removePrimitiveSet(0, m_pGeom->getNumPrimitiveSets());
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, m_pVertex->size()));
	m_pGeom->addPrimitiveSet(new osg::DrawArrays(_GetShapeType(), 0, m_pVertex->size()));
}