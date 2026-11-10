#include "xbasemapscene.h"

#include <osg/LightModel>
#include <osg/Callback>

#include "x3dbuilderfactory.h"
#include "xglobal.h"
#include "xobject.h"
#include "xbasemapwindow.h"
#include "xeventconsole.h"
#include "xviewinfo3dfaultsticks.h"
#include "xbasemapcoordinate.h"
#include "x3dsurvey.h"
#include "xseismicrandomsection.h"
#include "x2dpolygon.h"
#include "xtree.h"
#include "xbmpickhandle.h"
#include "xcursor.h"
#include "xobjectfactory.h"
#include "xviewinfoobject.h"
#include "xseismicsection.h"
#include "xbmsurveybuilder.h"
#include "xbmsurveycallback.h"
#include "xseismicdatavolume.h"
#include "x3dutility.h"
#include "xseismicutmtool.h"
#include "xgraphicsapi.h"

CXBasemapScene::CXBasemapScene(CXBaseMapWindow* pBaseMapWindow) 
	: m_pBaseMapWin(pBaseMapWindow)
{
}

CXBasemapScene::~CXBasemapScene()
{
    qDeleteAll(m_mapObjectToNodeBuilder);
    m_mapObjectToNodeBuilder.clear();
}

void CXBasemapScene::UpdateView(const CXEventParameter& eventPara)
{
    CXObject* pObj = ::GetObjectByID(eventPara.m_objID);
    if (!pObj) 
        return;

	if (!pObj->GetGeometryObject())
		return;

	QUuid uuidGeom = pObj->GetGeometryObject()->GetObjectID();
	
    if (eventPara.m_eEventType == EDeleted)
    {
        _RemoveObject(uuidGeom);
    }
	else if (eventPara.m_eEventType == EInfoChanged && !eventPara.m_winID.isNull() && eventPara.m_winID != m_pBaseMapWin->GetObjectID())
	{
		// Infomation changed message maybe only affect specified window when the `m_winID` isn't null.
		return;
	}
    else
    {
		if (_IsSeismicDataVolume(uuidGeom))
		{
			QUuid uuidPickedSection = _GetPickedSectionID(uuidGeom);
			if (!uuidPickedSection.isNull())
			{
				m_mapObjectToNodeBuilder.value(uuidPickedSection)->UpdateNode(eventPara.m_eEventType);
				m_colorbar.UpdateObj(uuidGeom);
			}
		}

        if (m_mapObjectToNodeBuilder.contains(uuidGeom))
        {
            m_mapObjectToNodeBuilder.value(uuidGeom)->UpdateNode(eventPara.m_eEventType);
			_UpdateBoundingBox();
			m_colorbar.UpdateObj(uuidGeom);
		}

		_UpdatePickedTimeSlice(eventPara);
		m_cursor.UpdatePosition();
		m_pBaseMapWin->UpdateSectionNumber(eventPara.m_objID);
    }

    m_pBaseMapWin->GetOSGViewWidget()->update();
}

void CXBasemapScene::InitScene()
{
    if (!m_pRootNode.valid())
        m_pRootNode = new osg::Group;

    m_pRootNode->setDataVariance(osg::Object::DYNAMIC);

    m_pCamera = m_pBaseMapWin->GetOSGViewWidget()->getCamera();
    osg::CullSettings::CullingMode mode = m_pCamera->getCullingMode();
    m_pCamera->setCullingMode(mode &(~osg::CullSettings::SMALL_FEATURE_CULLING));

	m_coord.SetWinInfoAndCoordMap(m_pBaseMapWin->GetWindowInfo(), &m_coordMap);
	m_cursor.SetWindowAndCoordMap(m_pBaseMapWin, &m_coordMap);
	m_scale.SetWindow(m_pBaseMapWin);
	m_compass.SetWindow(m_pBaseMapWin);
	m_colorbar.SetWindow(m_pBaseMapWin);
}

void CXBasemapScene::UpdateHUDWithWindow()
{
	m_scale.UpdatePosition();
	m_compass.UpdatePosition();
	m_colorbar.UpdatePosition();
}

void CXBasemapScene::SetCursorVisible(bool bVisible)
{
	m_cursor.SetVisible(bVisible);
	m_pBaseMapWin->Update();
}

void CXBasemapScene::SetColorbarVisible(bool bVisible)
{
	m_colorbar.SetVisible(bVisible);
	m_pBaseMapWin->Update();
}

void CXBasemapScene::SetCompassVisible(bool bVisible)
{
	m_compass.SetVisible(bVisible);
	m_pBaseMapWin->Update();
}

void CXBasemapScene::SetScaleVisible(bool bVisible)
{
	m_scale.SetVisible(bVisible);
	m_pBaseMapWin->Update();
}

void CXBasemapScene::SetScaleMark(int scale)
{
	m_scale.UpdateScale(scale);
}

void CXBasemapScene::UpdateCoordinateInfo()
{
	m_coord.UpdateWindowInfo();
	m_pBaseMapWin->Update();
}

void CXBasemapScene::UpdateScaleInfo()
{
	m_scale.UpdateViewInfo();
	m_pBaseMapWin->Update();
}

void CXBasemapScene::UpdateCompassInfo()
{
	m_compass.UpdateViewInfo();
	m_pBaseMapWin->Update();
}

void CXBasemapScene::UpdateColorbarInfo()
{
	m_colorbar.UpdateViewInfo();
	m_pBaseMapWin->Update();
}

void CXBasemapScene::UpdateAttribtue(const QUuid & uuidGeom)
{
	CX3DBuilderAbstract* pBuilder = m_mapObjectToNodeBuilder.value(uuidGeom);
	if (!pBuilder)
		return;

	pBuilder->UpdateNode(EColormapChanged);
	m_colorbar.UpdateObj(uuidGeom);
}

void CXBasemapScene::SetColorbarObjVisible(const QUuid & objID, bool bVisible)
{
	CXViewInfoObject *pViewInfo = m_pBaseMapWin->GetObjectViewInfo(objID);
	pViewInfo->SetNeedColormap(bVisible);

	if (bVisible)
	{
		m_colorbar.PushObj(objID);
	}
	else
	{
		m_colorbar.RemoveObj(objID);
	}
}

bool CXBasemapScene::IsInSurvey(const osg::Vec3d& vecWorld, int& iInline, int& iXline)
{
	for (const QUuid& objID : m_mapObjectToNodeBuilder.keys())
	{
		auto pSurvey = dynamic_cast<CX3DSurvey*>(::GetObjectByID(objID));
		if (!pSurvey)
			continue;

		CXSeismicUTMTool& utm = pSurvey->GetUTM();

		int iFI = utm.GetFirstInline();
		int iLI = utm.GetLastInline();
		int iFX = utm.GetFirstCrossline();
		int iLX = utm.GetLastCrossline();

		osg::Vec2d vecFIFX, vecFILX, vecLILX, vecLIFX;
		utm.LineToXY(iFI, iFX, vecFIFX.x(), vecFIFX.y());
		utm.LineToXY(iFI, iLX, vecFILX.x(), vecFILX.y());
		utm.LineToXY(iLI, iLX, vecLILX.x(), vecLILX.y());
		utm.LineToXY(iLI, iFX, vecLIFX.x(), vecLIFX.y());

		double pBoundPoints[8] = { vecFIFX.x(), vecFIFX.y(), vecFILX.x(), vecFILX.y(), vecLILX.x(), vecLILX.y(), vecLIFX.x(), vecLIFX.y()};
		if (CXGraphicsAPI::IsPointInsidePolygon(4, vecWorld.x(), vecWorld.y(), pBoundPoints))
		{
			utm.XYToLine(vecWorld.x(), vecWorld.y(), iInline, iXline);
			return true;
		}
	}

	return false;
}

bool CXBasemapScene::IsInSurvey(const osg::Vec2& vecScreen)
{
	osg::Vec3 vecLocal = NX3DUtility::MapToLocal(m_pCamera, osg::Vec3(vecScreen, 0.f));
	osg::Vec3d vecWorld;
	m_coordMap.MapLocalToWorld(vecLocal, vecWorld);
	int iInline, iXline;
	if (IsInSurvey(vecWorld, iInline, iXline))
		return true;

	return false;
}

void CXBasemapScene::CreateHudCamera()
{
    if (!m_pHudCamera.valid())
    {
        m_pHudCamera = new osg::Camera;
        m_pHudCamera->setDataVariance(osg::Object::DYNAMIC);
		m_pHudCamera->setName("HUD(polygon_randomsection)");
        m_pRootNode->addChild(m_pHudCamera.get());
    }
    else
    {
        m_pHudCamera->removeChild(0, m_pHudCamera->getNumChildren());
        m_pHudCamera->setNodeMask(0xffffffff);
    }
    // set the projection matrix

    float width = m_pCamera->getViewport()->width();
    float height = m_pCamera->getViewport()->height();

    m_pHudCamera->setProjectionMatrix(osg::Matrix::ortho2D(0, width, 0, height));
    m_pHudCamera->setViewport(0, 0, width, height);

    // set the view matrix
    m_pHudCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    m_pHudCamera->setViewMatrix(osg::Matrix::identity());

    // only clear the depth buffer
    m_pHudCamera->setClearMask(GL_DEPTH_BUFFER_BIT);

    // draw subgraph after main camera view.
    m_pHudCamera->setRenderOrder(osg::Camera::POST_RENDER);

    // we don't want the camera to grab event focus from the viewers main camera(s).
    m_pHudCamera->setAllowEventFocus(false);
	m_pHudCamera->setEventCallback(new CXBMSurveyCallback(m_pHudCamera, m_pBaseMapWin));
}

void CXBasemapScene::CreateRandomSection()
{
	if (!m_pBaseMapWin->IsRandomSectionReady())
		return;

	auto pSurveyCallback = dynamic_cast<CXBMSurveyCallback*>(m_pHudCamera->getEventCallback());
	if (!pSurveyCallback)
		return;

	const QList<QUuid>& listObjID = m_mapObjectToNodeBuilder.keys();
	auto iterSurvey = std::find_if(listObjID.cbegin(), listObjID.cend(), [](const QUuid& id){
		return ::GetObjectByID(id)->GetObjectType() == EX3DSurvey;
	});

	Q_ASSERT(iterSurvey != listObjID.cend());
	auto pSurvey = dynamic_cast<CX3DSurvey*>(GetObjectByID(*iterSurvey));
	CXObject* pSectionFolder = pSurvey->GetFolder(EXSeismicSectionFolder);

	// new randomsection object
	auto pNewRandomSection = new CXSeismicRandomSection;
	pNewRandomSection->SetObjectName(pSectionFolder->GetUnallocatedName("Random Section"));

	std::vector<double> vecX, vecY;
	pSurveyCallback->GetXYofTuringPoint(vecX, vecY);
	pNewRandomSection->SetPolyline(vecX, vecY);

	pSectionFolder->AddChild(pNewRandomSection);
	::AddObjectEvent(pNewRandomSection);
	
	// stop HUD Callback, and remove HUD geometry.
	m_pBaseMapWin->SetRandomSectionReady(false);
	m_pHudCamera->removeChildren(0, m_pHudCamera->getNumChildren());

	// check new random section and display it.
	CXTree::Instance().ChangeTreeItemStatus(QList<QUuid>{pNewRandomSection->GetObjectID()}, true);
	m_pBaseMapWin->SetObjectVisibility(pNewRandomSection->GetObjectID(), true);
}

void CXBasemapScene::Create2DPolygon()
{
	if (!m_pBaseMapWin->IsPolygonReady())
		return;

	auto pSurveyCallback = dynamic_cast<CXBMSurveyCallback*>(m_pHudCamera->getEventCallback());
	if (!pSurveyCallback)
		return;

	// new polygon object
	CXObject *pPolygonFolder = ::GetRootObjectFolder(EXPolygonFolder);
	auto p2DPolygon = new CX2DPolygon(pPolygonFolder->GetUnallocatedName("2D Polygon"), EX2DPolygon);
	
	double *pData = nullptr;
	int nSize;
	pSurveyCallback->GetData(pData, nSize);
	p2DPolygon->ResetData(pData, nSize);

	pPolygonFolder->AddChild(p2DPolygon);
	::AddObjectEvent(p2DPolygon);

	// stop HUD Callback, and remove HUD geometry.
	m_pBaseMapWin->SetPolygonlineReady(false);
	m_pHudCamera->removeChildren(0, m_pHudCamera->getNumChildren());

	// check new random section and display it.
	CXTree::Instance().ChangeTreeItemStatus(QList<QUuid>{p2DPolygon->GetObjectID()}, true);
	m_pBaseMapWin->SetObjectVisibility(p2DPolygon->GetObjectID(), true);
}

bool CXBasemapScene::SetOjbectVisiability(QUuid objID, bool bVisible)
{
    if (bVisible && m_mapObjectToNodeBuilder.contains(objID))
        return false;

    if (!bVisible)
        return _RemoveObject(objID);

    CXObject *pObject = ::GetObjectByID(objID);
    if (!pObject)
        return false;

    CX3DBuilderAbstract *pBuilder = CXBuilderFactory::Instance().CreateBuilder(pObject->GetObjectType(), e3DBaseMap);
    if (!pBuilder)
        return false;

    pBuilder->SetWindowAndCoordMap(m_pBaseMapWin, &m_coordMap);

    if (!m_coordMap.IsInitialized())
        m_coordMap.Init(objID);

    _CreateObjectNode(pBuilder, objID);

    if (dynamic_cast<osg::Group*>(m_pBaseMapWin->GetOSGViewWidget()->getSceneData()) == NULL)
    {
		m_pBaseMapWin->GetOSGViewWidget()->setSceneData(m_pRootNode);
    }

    _UpdateTrackingToolsStatus(); 

	if (m_bFirst)
	{
		m_bFirst = false;
		m_pBaseMapWin->slotViewAll();
		m_pBaseMapWin->EnablePolygonMode(true);
	}

	m_pBaseMapWin->Update();

    return true;

}

bool CXBasemapScene::_RemoveObject(QUuid objID)
{
    if (!m_mapObjectToNodeBuilder.contains(objID))
        return false;

    CX3DBuilderAbstract* pBuilder = m_mapObjectToNodeBuilder.value(objID);
    if (!pBuilder)
        return false;

    osg::ref_ptr<osg::Group> pNode = pBuilder->GetBuilderNode();
    m_pRootNode->removeChild(pNode.get());
    delete pBuilder;

    m_mapObjectToNodeBuilder.remove(objID);

	CXPickhandle* pickHandle = m_pBaseMapWin->GetOSGViewWidget()->GetPickhandle();
	if (pickHandle)
	{
		pickHandle->ResetPickedObject(::GetObjectByID(objID));
	}

    if (m_mapObjectToNodeBuilder.empty())
    {
		m_pRootNode->removeChildren(0, m_pRootNode->getNumChildren());
		m_coord.Clear();
		m_colorbar.Clear();
		m_cursor.SetVisible(false);
		m_bFirst = true;
        _UpdateTrackingToolsStatus();
		m_pBaseMapWin->EnablePolygonMode(false);
		m_pBaseMapWin->Update();

        return false;
    }
	else
	{
		_UpdateBoundingBox();

		m_colorbar.RemoveObj(objID);
		_UpdateTrackingToolsStatus();
		m_pBaseMapWin->Update();

		return true;
	} 
}

void CXBasemapScene::_CreateObjectNode(CX3DBuilderAbstract* pBuilder, QUuid objID)
{
	osg::ref_ptr<osg::Group> builderNode = pBuilder->Build(objID);
	if (!builderNode.valid())
		return;

	pBuilder->SetBuilderNode(builderNode);
	
	m_coord.ExpandBy(pBuilder->GetBoundBox());

	if (m_pRootNode->getNumChildren() == 0)
	{
		m_pRootNode->addChild(m_coord.GetCoordinateAxis());
		m_pRootNode->addChild(m_scale.GetScaleNode());
		m_pRootNode->addChild(m_compass.GetCompassNode());
		m_pRootNode->addChild(m_colorbar.GetColorbar());
		m_pRootNode->addChild(m_cursor.GetCursor());
	}

	m_pRootNode->addChild(builderNode.get());
	m_colorbar.PushObj(objID);

	m_mapObjectToNodeBuilder.insert(objID, pBuilder);
}

void CXBasemapScene::_UpdatePickedTimeSlice(const CXEventParameter& eventPara)
{
	auto pPickhandle = dynamic_cast<CXBMPickhandle*>(m_pBaseMapWin->GetOSGViewWidget()->GetPickhandle());
	if (!pPickhandle)
		return;

	auto pPickedSection = dynamic_cast<CXSeismicSection*>(pPickhandle->GetCurPickedObj());
	if (!pPickedSection || eTimeSlice != pPickedSection->GetSectionType())
		return;

	CXViewInfoObject* pSectionViewInfo = m_pBaseMapWin->GetObjectViewInfo(pPickedSection->GetObjectID());
	if (!pSectionViewInfo || eventPara.m_objID != pSectionViewInfo->GetAttributeObjID())
		return;

	CX3DBuilderAbstract* pBuilder = m_mapObjectToNodeBuilder.value(pPickedSection->GetObjectID());
	Q_ASSERT(pBuilder);

	pBuilder->UpdateNode(eventPara.m_eEventType);
}

void CXBasemapScene::_UpdateTrackingToolsStatus()
{
	for (const QUuid& objID : m_mapObjectToNodeBuilder.keys())
	{
		CXObject *pObj = ::GetObjectByID(objID);
		Q_ASSERT(pObj);

		EXObjectType curType = pObj->GetObjectType();
		if (curType == EX3DSurvey || curType == EXSeismicDataVolume)
		{
			m_pBaseMapWin->EnableRandomSectionMode(true);
			return;
		}
	}

	m_pBaseMapWin->EnableRandomSectionMode(false);
}

void CXBasemapScene::_UpdateBoundingBox()
{
	osg::BoundingBox allBox;

	const QList<CX3DBuilderAbstract*>& listBuilder = m_mapObjectToNodeBuilder.values();
	std::for_each(listBuilder.cbegin(), listBuilder.cend(), [&allBox](CX3DBuilderAbstract* pBuilder) {
		allBox.expandBy(pBuilder->GetBoundBox());
	});

	m_coord.ResetBy(allBox);
}

bool CXBasemapScene::_IsSeismicDataVolume(const QUuid & uuidGeom)
{
	auto pDV = dynamic_cast<CXSeismicDataVolume*>(::GetObjectByID(uuidGeom));
	return pDV != nullptr;
}

QUuid CXBasemapScene::_GetPickedSectionID(const QUuid & uuidDV)
{
	auto pPickhandle = dynamic_cast<CXBMPickhandle*>(m_pBaseMapWin->GetOSGViewWidget()->GetPickhandle());
	if (!pPickhandle)
		return QUuid();

	auto pPickedSection = dynamic_cast<CXSeismicSection*>(pPickhandle->GetCurPickedObj());
	if (!pPickedSection || eTimeSlice != pPickedSection->GetSectionType())
		return QUuid();

	auto pViewInfoSection = m_pBaseMapWin->GetObjectViewInfo(pPickedSection->GetObjectID());
	if (pViewInfoSection->GetAttributeObjID() != uuidDV) // uuidGeom is DataVolume.
		return QUuid();

	return pPickedSection->GetObjectID();
}