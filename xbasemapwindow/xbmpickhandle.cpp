#include "xbmpickhandle.h"

#include <QUuid>
#include <QDebug>

#include <osgUtil/PolytopeIntersector>
#include <osg/ValueObject>

#include "xosgwidget.h"
#include "xbasemapwindow.h"
#include "x3dglobalcoordmap.h"
#include "xglobal.h"
#include "xbaseconsole.h"
#include "xbasemapscene.h"
#include "xseismicrandomsection.h"
#include "x2dpolygon.h"
#include "x3dutility.h"
#include "xbasemapscene.h"
#include "xbmpickcallback.h"
#include "xseismicsection.h"
#include "xeventconsole.h"
#include "xdlgproperty.h"
#include "xviewinfoobject.h"
#include "xviewinfoseismicdv.h"

CXBMPickhandle::CXBMPickhandle() : CXPickhandle()
{
}

CXBMPickhandle::~CXBMPickhandle()
{
}

bool CXBMPickhandle::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
	if (!view || view->getSceneData() == nullptr) 
		return false;
	
	CXOSGWidget* viewWidget = dynamic_cast<CXOSGWidget*>(view);
	m_pWin = dynamic_cast<CXBaseMapWindow *>(viewWidget->parent());
	m_pCamera = viewWidget->getCamera();

	if (!m_pWin->IsSelectMode())
		return false;

	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::PUSH:
		m_xNorm = ea.getXnormalized();
		m_yNorm = ea.getYnormalized();

		_PickObj(ea.getX(), ea.getY());
		break;
	case osgGA::GUIEventAdapter::DRAG:
		_DragObj(ea.getX(), ea.getY());
		_UpdateStatusBar(osg::Vec2(ea.getX(), ea.getY()), osg::Vec2(ea.getXnormalized(), ea.getYnormalized()));
		break;
	case osgGA::GUIEventAdapter::RELEASE:
		if (m_xNorm == ea.getXnormalized() && m_yNorm == ea.getYnormalized())
			break;

		_UpdateSeismicSection(osg::Vec2(ea.getX(), ea.getY()));
		_UpdateRandomSection(osg::Vec2(ea.getX(), ea.getY()));
		_UpdatePolygon(osg::Vec2(ea.getX(), ea.getY()));
		_UpdateStatusBar(osg::Vec2(ea.getX(), ea.getY()), osg::Vec2(ea.getXnormalized(), ea.getYnormalized()));
		break;
	case osgGA::GUIEventAdapter::MOVE:
		_UpdateStatusBar(osg::Vec2(ea.getX(), ea.getY()), osg::Vec2(ea.getXnormalized(), ea.getYnormalized()));
		break;
	case osgGA::GUIEventAdapter::DOUBLECLICK:
		m_pWin->GetOSGScene()->CreateRandomSection();
		m_pWin->GetOSGScene()->Create2DPolygon();

		if (_IsSeismicTimeslicePicked())
		{
			auto pViewInfoSection = m_pWin->GetObjectViewInfo(m_pPickedObj->GetObjectID());
			CXDlgProperty *pPropertyDialog = CXPropertyDialogFactory::Instance().CreatePropertyDialog(GetObjectByID(pViewInfoSection->GetAttributeObjID()));
			pPropertyDialog->ShowColormapPage();
			pPropertyDialog->show();
		}
		break;
	default:
		break;
	}

	return false;
}

bool CXBMPickhandle::_IsSectionLine(CXObject* pObj)
{
	if (m_pWin->IsPolygonMode() || m_pWin->IsRandomSectionMode())
		return false;

	CXSeismicSection* pSection = dynamic_cast<CXSeismicSection *>(pObj);
	if (pSection && pSection->GetSectionType() != eTimeSlice)
		return true;

	return false;
}

bool CXBMPickhandle::_IsRandomSection(CXObject* pObj)
{
	auto pRandomSection = dynamic_cast<CXSeismicRandomSection*>(pObj);
	if (pRandomSection)
		return true;

	return false;
}

bool CXBMPickhandle::_IsPolygon(CXObject* pObj)
{
	auto pPolygon = dynamic_cast<CX2DPolygon*>(pObj);
	if (pPolygon)
		return true;

	return false;
}

bool CXBMPickhandle::_IsInScene(const osg::Vec2& posXY)
{
	const osg::BoundingBox& box = m_pWin->GetOSGScene()->GetSceneBoundBox();
	osg::Vec3 localPos = NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(posXY, 0.f));

	if (box.xMin() < localPos.x() && localPos.x() < box.xMax() && box.yMin() < localPos.y() && localPos.y() < box.yMax())
		return true;

	return false;
}

bool CXBMPickhandle::_IsSeismicTimeslicePicked()
{
	if (!m_pPickedObj)
		return false;

	auto pSection = dynamic_cast<CXSeismicSection*>(m_pPickedObj);
	if (!pSection || pSection->GetSectionType() != eTimeSlice)
		return false;

	return true;
}

void CXBMPickhandle::_UpdateStatusBar(const osg::Vec2& posXY, const osg::Vec2& normalizedXY)
{
	_ResetStatus();

	if (!_IsInScene(posXY))
		return;

	osg::Vec3d worldPos = _ScreenPosToWorld(posXY);
	QString strMsg;

	// for object
	{
		QString strObjName;
		if (_IsObject(normalizedXY, strObjName))
		{
			strMsg += "[" + strObjName + "] ";
		}
	}

	// for seismic survey
	{
		int iInline, iXline;
		if (m_pWin->GetOSGScene()->IsInSurvey(worldPos, iInline, iXline))
		{
			strMsg += "Inline: " + QString::number(iInline) + " ";
			strMsg += "Crossline: " + QString::number(iXline) + " ";
		}
	}
	
	strMsg += QString("X: %1 Y: %2").arg(worldPos.x(), 0, 'f', 2).arg(worldPos.y(), 0, 'f', 2);
	m_pWin->ShowMessage(strMsg);
}

bool CXBMPickhandle::_IsObject(const osg::Vec2& normalizedXY, QString& strObjName)
{
	float mx = normalizedXY.x();
	float my = normalizedXY.y();
	float w = 0.01;
	float h = 0.01;

	auto pIntersector = new osgUtil::PolytopeIntersector(osgUtil::Intersector::PROJECTION, mx - w, my - h, mx + w, my + h);
	osgUtil::IntersectionVisitor iv(pIntersector);
	iv.setTraversalMask(4);
	m_pCamera->accept(iv);

	if (!pIntersector->containsIntersections())
		return false;

	osgUtil::PolytopeIntersector::Intersection intersection = pIntersector->getFirstIntersection();
	const osg::NodePath& nodePath = intersection.nodePath;

	if (nodePath.empty())
		return false;

	osg::Node* pHoverNode = nodePath.back();

	CXObject* pHoverObj = [](osg::Node* pNode){
		std::string strObjID;
		pNode->getUserValue("objID", strObjID);
		return ::GetObjectByID(QUuid(QString::fromStdString(strObjID)));
	}(pHoverNode);

	if (!pHoverObj)
		return false;

	m_pWin->GetOSGViewWidget()->setToolTip(pHoverObj->GetObjectName());

	if (_IsSectionLine(pHoverObj))
	{
		m_pWin->GetOSGViewWidget()->setCursor(Qt::OpenHandCursor);
	}

	strObjName = pHoverObj->GetObjectName();
	return true;
}

void CXBMPickhandle::_ResetStatus()
{
	m_pWin->GetOSGViewWidget()->setToolTip("");
	m_pWin->GetOSGViewWidget()->setCursor(Qt::ArrowCursor);
}

void CXBMPickhandle::_PickObj(float fX, float fY)
{
	if (m_pWin->IsRandomSectionCreating() || m_pWin->IsPolygonCreating())
		return;

	CXOSGWidget* pOSGWidget = m_pWin->GetOSGViewWidget();
	if (!pOSGWidget->getSceneData())
		return;

	double w = 0.01, h = 0.01;
	using namespace osgUtil;
	auto picker = new PolytopeIntersector(Intersector::PROJECTION, m_xNorm - w, m_yNorm - h, m_xNorm + w, m_yNorm + h);
	IntersectionVisitor iv(picker);
	pOSGWidget->getCamera()->accept(iv);

	if (!picker->containsIntersections())
	{
		if (!m_pWin->IsRandomSectionMode() && !m_pWin->IsPolygonMode())
		{
			ResetPickedNodeStatus();
		}
		else if (m_pPickedNode)
		{
			auto pCallback = dynamic_cast<CXBMPickCallback*>(m_pPickedNode->getEventCallback());
			Q_ASSERT(pCallback);

			pCallback->SetActive(false);
		}

		return;
	}

	const PolytopeIntersector::Intersections& intersections = picker->getIntersections();

	for (auto iter = intersections.begin(); iter != intersections.end(); ++iter)
	{
		if (iter->nodePath.empty())
			continue;

		auto pGeode = dynamic_cast<osg::Geode*>(iter->nodePath.back());
		if (!pGeode)
			continue;

		std::string strID;
		pGeode->getUserValue("objID", strID);

		auto pCallback = dynamic_cast<CXBMPickCallback*>(pGeode->getEventCallback());

		if (strID.empty() || !pCallback || !pCallback->SetActive(true))
			continue;

		if (pGeode != m_pPickedNode)
		{
			ResetPickedNodeStatus();

			m_pPickedNode = pGeode;
			m_pPickedObj = ::GetObjectByID(QUuid(QString::fromStdString(strID)));
		}
		
		if (_IsRandomSection(m_pPickedObj) || _IsPolygon(m_pPickedObj))
		{
			m_iPivotIndex = pCallback->GetPivotIndexFromPos(NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(fX, fY, 0.f)), NX3DUtility::DistPerMM(m_pCamera));
		}

		break;
	}
}

void CXBMPickhandle::_DragObj(float fX, float fY)
{
	if (!m_pPickedObj || !m_pPickedNode)
		return;

	auto pCallback = dynamic_cast<CXBMPickCallback*>(m_pPickedNode->getEventCallback());
	if (!pCallback)
		return;

	if (_IsSectionLine(m_pPickedObj))
	{
		int iInline, iXline;
		if (!m_pWin->GetOSGScene()->IsInSurvey(_ScreenPosToWorld(osg::Vec2(fX, fY)), iInline, iXline))
			return;

		pCallback->SetSeismicSectionTrace(iInline, iXline);
	}
	else if ((_IsRandomSection(m_pPickedObj) && m_pWin->GetOSGScene()->IsInSurvey(osg::Vec2(fX, fY))) || _IsPolygon(m_pPickedObj))
	{
		pCallback->DragPivot(m_iPivotIndex, NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(osg::Vec2(fX, fY), 0.f)));
	}
}

void CXBMPickhandle::_OptDone(float fX, float fY)
{

}

void CXBMPickhandle::_UpdateSeismicSection(const osg::Vec2 & posXY)
{
	if (!m_pPickedObj || !_IsSectionLine(m_pPickedObj))
		return;

	auto pSeismicSection = dynamic_cast<CXSeismicSection*>(m_pPickedObj);

	int iInline = 0, iXline = 0;
	if (!m_pWin->GetOSGScene()->IsInSurvey(_ScreenPosToWorld(posXY), iInline, iXline))
	{
		auto pCallback = dynamic_cast<CXBMPickCallback*>(m_pPickedNode->getEventCallback());
		if (pCallback)
		{
			pSeismicSection->SetSectionNumber(pCallback->GetSeismicSectionTrace());
		}
	}
	else if (eInlineSection == pSeismicSection->GetSectionType())
	{
		pSeismicSection->SetSectionNumber(iInline);
	}
	else if (eCrosslineSection == pSeismicSection->GetSectionType())
	{
		pSeismicSection->SetSectionNumber(iXline);
	}

	CXProcessEvent processEvent(m_pWin);
	pSeismicSection->AddEvent(EDataChanged);
}

void CXBMPickhandle::_UpdateRandomSection(const osg::Vec2 & posXY)
{
	if (!m_pPickedObj || !_IsRandomSection(m_pPickedObj))
		return;

	auto pRandomSection = dynamic_cast<CXSeismicRandomSection*>(m_pPickedObj);

	auto pCallback = dynamic_cast<CXBMPickCallback*>(m_pPickedNode->getEventCallback());
	if (!pCallback)
		return;

	pCallback->SetActive(true);
	pCallback->FixedPivot();
	pCallback->SetLastPivotIndex(m_iPivotIndex);
	
	if (!m_pWin->GetOSGScene()->IsInSurvey(posXY))
		return;

	osg::Vec3d worldPos = _ScreenPosToWorld(posXY);
	pRandomSection->SetXYByIndex(m_iPivotIndex, worldPos.x(), worldPos.y());

	CXProcessEvent processEvent(m_pWin);
	pRandomSection->AddEvent(EDataChanged);
}

void CXBMPickhandle::_UpdatePolygon(const osg::Vec2 & posXY)
{
	if (!m_pPickedObj || !_IsPolygon(m_pPickedObj))
		return;

	auto pPolygon = dynamic_cast<CX2DPolygon*>(m_pPickedObj);

	auto pCallback = dynamic_cast<CXBMPickCallback*>(m_pPickedNode->getEventCallback());
	if (!pCallback)
		return;

	pCallback->FixedPivot();
	pCallback->SetLastPivotIndex(m_iPivotIndex);

	if (pCallback->IsPolygonSelfIntersection(m_iPivotIndex, NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(posXY, 0.f))))
		return;

	osg::Vec3d worldPos = _ScreenPosToWorld(posXY);
	pPolygon->ResetData(m_iPivotIndex, worldPos.x(), worldPos.y());

	CXProcessEvent processEvent(m_pWin);
	pPolygon->AddEvent(EDataChanged);
}

void CXBMPickhandle::ResetPickedNodeStatus()
{
	if (!m_pPickedObj)
		return;

	auto pCallback = dynamic_cast<CXBMPickCallback*>(m_pPickedNode->getEventCallback());
	Q_ASSERT(pCallback);

	pCallback->SetActive(false);

	m_pPickedObj = nullptr;
	m_pPickedNode = nullptr;
}

osg::Vec3d CXBMPickhandle::_ScreenPosToWorld(const osg::Vec2& posXY)
{
	osg::Vec3d worldPos;
	m_pWin->GetCoordMap()->MapLocalToWorld(NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(posXY, 0.f)), worldPos);

	return worldPos;
}