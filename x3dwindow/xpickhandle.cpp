#include "xpickhandle.h"
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/PolytopeIntersector>
#include <osg/ComputeBoundsVisitor>
#include <osg/ValueObject>
#include "quuid.h"
#include "xosgwidget.h"
#include "x3dwindow.h"
#include "xseismicsection.h"
#include "x3dglobalcoordmap.h"
#include "xbaseconsole.h"
#include "xglobal.h"
#include "xpickcallback.h"
#include "xdlgproperty.h"
#include "xviewinfoobject.h"

CXPickhandle::CXPickhandle() :m_xNorm(0.0f), m_yNorm(0.0f)
{
	setName("PickHandle");
	m_pPickedNode = NULL;
	m_pPickedObj = NULL;
	m_PrimitiveIndex = -1;
}

CXPickhandle::~CXPickhandle()
{
	if (m_pPickedNode)
	{
		osg::Switch* pSwitch = m_pPickedNode->asSwitch();
		if (pSwitch)
			pSwitch->setValue(1, false);
		//pOsgWindow->SetVCRControlData(NULL,false);
	}
	m_pPickedNode = NULL;
	m_pPickedObj = NULL;
	m_PrimitiveIndex = -1;
}

void CXPickhandle::ResetPickedObject(CXObject* pObject)
{
	if (pObject == m_pPickedObj)
	{
		m_pPickedObj = NULL;
		m_pPickedNode = NULL;
	}
}

void CXPickhandle::_ResetPickedNodeStatus()
{
	if (!m_pPickedObj)
		return;

	auto pCallback = dynamic_cast<CXPickCallback*>(m_pPickedNode->getEventCallback());
	Q_ASSERT(pCallback);

	pCallback->SetActive(false);
	_ShowVolumeToolbar(false);

	m_pPickedNode = nullptr;
	m_pPickedObj = nullptr;
}

void CXPickhandle::_ShowVolumeToolbar(bool bVisible)
{
	auto pSection = dynamic_cast<CXSeismicSection*>(m_pPickedObj);
	if (pSection)
	{
		m_pWin->SetVolumeToolbarVisible(pSection, bVisible);
		m_pWin->SetVCRControlData(pSection, bVisible);
	}
}

bool CXPickhandle::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	CXOSGWidget *pOSGWidget = dynamic_cast<CXOSGWidget*>(&aa);
	if (!pOSGWidget)
		return false;

	m_pWin = dynamic_cast<CX3DWindow *>(pOSGWidget->parent());

	switch (ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::PUSH) :
	{
		m_xNorm = ea.getXnormalized();
		m_yNorm = ea.getYnormalized();
		break;
	}
	case(osgGA::GUIEventAdapter::RELEASE) :
	{
		if (m_xNorm == ea.getXnormalized() && m_yNorm == ea.getYnormalized())
		{
			pick(pOSGWidget, ea);
		}
		break;
	}
	case(osgGA::GUIEventAdapter::DOUBLECLICK) :
	{
		if (!m_pPickedObj)
			return false;

		auto pSection = dynamic_cast<CXSeismicSection*>(m_pPickedObj);
		if (pSection->GetSectionType() == eInlineProfile)
			return false;

		auto pViewInfoSection = m_pWin->GetObjectViewInfo(pSection->GetObjectID());

		CXDlgProperty *pPropertyDialog = CXPropertyDialogFactory::Instance().CreatePropertyDialog(GetObjectByID(pViewInfoSection->GetAttributeObjID()));
		pPropertyDialog->ShowColormapPage();
		pPropertyDialog->show();
		break;
	}
	case (osgGA::GUIEventAdapter::MOVE) :
	{
		float curX = ea.getXnormalized();
		float curY = ea.getYnormalized();
		osg::Node *node = new osg::Node();
		osg::Group* parent = new osg::Group;
		m_pWin->ShowMessage("");
		double w(.01), h(.01);
		osgUtil::PolytopeIntersector* picker =
			new osgUtil::PolytopeIntersector(
			osgUtil::Intersector::PROJECTION, curX - w, curY - h, curX + w, curY + h);
		osgUtil::IntersectionVisitor iv(picker);
		pOSGWidget->getCamera()->accept(iv);
		osgUtil::PolytopeIntersector::Intersection FirstIntersection;
		if (picker->containsIntersections())
		{

			FirstIntersection = picker->getFirstIntersection();
			osgUtil::PolytopeIntersector::Intersections::iterator it = picker->getIntersections().begin();
			while (FirstIntersection.distance < 100)
			{
				if ((++it) == picker->getIntersections().end())
					return false;
				FirstIntersection = *it;
			}

			osg::NodePath& nodePath = FirstIntersection.nodePath;
			unsigned int idx = nodePath.size();
			node = (nodePath.size() >= 1) ? nodePath[nodePath.size() - 1] : 0;
			parent = (nodePath.size() >= 2) ? dynamic_cast<osg::Group*> (nodePath[nodePath.size() - 2]) : 0;

			if (node == NULL || parent == NULL)
			{
				return false;
			}
			std::string objName, objID;
			node->getUserValue("objID", objID);
			QString SUUid(objID.c_str());
			QUuid objUuid(SUUid);
			CXObject* pObj = ::GetObjectByID(objUuid);
			if (pObj)
			{
				osg::Vec3d worldCord, realWorld;
				worldCord = FirstIntersection.localIntersectionPoint;
				m_pWin->GetCoordMap()->MapLocalToWorld(worldCord, realWorld);

				QString statInfoX = QString::number(realWorld[0], 'g', 10);
				QString statInfoY = QString::number(realWorld[1], 'g', 10);
				QString statInfoZ = QString::number(realWorld[2], 'g', 10);
				QString curCoord = ": X = " + statInfoX + " ; " + "Y = " + statInfoY + " ; " + "Z = " + statInfoZ + " ";
				m_pWin->ShowMessage(curCoord + pObj->GetObjectName());
			}

		}
		break;
	}
	default:
		break;
	}
	return false;
}

void CXPickhandle::pick(osgViewer::View *view, const osgGA::GUIEventAdapter &ea)
{
	_ResetPickedNodeStatus();

	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (!view->computeIntersections(ea, intersections))
		return;

	const osg::NodePath& nodePath = (*intersections.cbegin()).nodePath;
	if (nodePath.empty())
		return;

	m_pPickedNode = dynamic_cast<osg::Geode*>(nodePath.back());
	if (!m_pPickedNode)
		return;

	auto pCallback = dynamic_cast<CXPickCallback*>(m_pPickedNode->getEventCallback());
	if (!pCallback)
		return;

	std::string strID;
	m_pPickedNode->getUserValue("objID", strID);
	if (strID.empty())
		return;

	m_pPickedObj = ::GetObjectByID(QUuid(QString::fromStdString(strID)));
	auto pSection = dynamic_cast<CXSeismicSection*>(m_pPickedObj);
	if (pSection->GetSectionType() == eInlineProfile)
	{
		_ShowVolumeToolbar(false);
	}
	else
	{
		_ShowVolumeToolbar(true);
	}
	
	pCallback->SetActive(true);
}