#include "x3dscene.h"

#include <QDebug>

#include <osg/DisplaySettings>
#include <osg/GraphicsContext>
#include <osg/CullFace>
#include <osg/PolygonMode>
#include <osg/FrontFace>
#include <osg/LightModel>
#include <osg/Material>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgUtil/Optimizer>
#include <osgViewer/ViewerEventHandlers>

#include "xglobal.h"
#include "xobject.h"
#include "x3dbuilder.h"
#include "x3dpointsetbuilder.h"
#include "x3dbuilderfactory.h"
#include "x3dwindow.h"
#include "xosgwidget.h"
#include "x3dcompass.h"
#include "xcoordupdatecallback.h"
#include "xeventconsole.h"
#include "xobjectfactory.h"
#include "xcursor.h"
#include "x3dsurvey.h"
#include "x2dsurvey.h"
#include "xviewinfomanager.h"
#include "xseismicsection.h"
#include "x3dutility.h"

CX3dscene::CX3dscene(CX3DWindow* pOSGWindow) : m_pOSGWindow(pOSGWindow)
{
}

CX3dscene::~CX3dscene()
{
	
}

void CX3dscene::ReleaseResource()
{
	for (auto pBuilder : m_mapObjectToNodeBuilder)
	{
		if (!pBuilder || dynamic_cast<osg::Camera*>(pBuilder)) continue;

		if (pBuilder->IsScalable())
		{
			m_pGlobalTransform->removeChild(pBuilder->GetBuilderNode());
		}
		else
		{
			m_pRootNode->removeChild(pBuilder->GetBuilderNode());
		}

		delete pBuilder;
	}

	m_mapObjectToNodeBuilder.clear();
	m_listDisplayedObjNode.clear();
}

void CX3dscene::InitScene()
{
	m_pRootNode = new osg::Group;
	m_pRootNode->setName("3D RootNode");
	m_pRootNode->setDataVariance(osg::Object::DYNAMIC);

	m_pGlobalTransform = new osg::MatrixTransform;
	m_pGlobalTransform->setName("3D Scene Z-Scale Transform");
	m_pGlobalTransform->setMatrix(osg::Matrix::scale(osg::Vec3d(1.0, 1.0, 3.0)));
	m_pGlobalTransform->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
	m_pRootNode->addChild(m_pGlobalTransform.get());

	m_pCamera = m_pOSGWindow->GetOSGViewWidget()->getCamera();

	m_axes.SetWindowAndCoordMap(m_pOSGWindow, &m_coordMap);
	m_colorbar.SetWindow(m_pOSGWindow);
	m_compass.SetWindow(m_pOSGWindow);
	m_cursor.SetWindowAndCoordMap(m_pOSGWindow, &m_coordMap);
	m_lighting.SetWindowInfoAndRootStateSet(m_pOSGWindow->GetWindowInfo(), m_pRootNode->getOrCreateStateSet());

	connect(m_pOSGWindow, SIGNAL(UpdateWindowSize(int, int)), this, SLOT(slotUpdateWindowSize(int, int)));
}

void CX3dscene::UpdateView(const CXEventParameter& eventPara)
{
	CXObject* pObj = ::GetObjectByID(eventPara.m_objID);
	if (!pObj) return;

    QUuid uuidGeom = pObj->GetGeometryObject()->GetObjectID();

	if (eventPara.m_eEventType == EDeleted)
	{
        _RemoveObject(eventPara.m_objID);
	}
	else if (eventPara.m_eEventType == EInfoChanged && !eventPara.m_winID.isNull() && eventPara.m_winID != m_pOSGWindow->GetObjectID())
	{
		// Infomation changed message maybe only affect specified window when the `m_winID` isn't null.
		return;
	}
    else
    {
		if (_IsSeismicVolumeChanged(uuidGeom))
		{
			m_colorbar.UpdateObj(uuidGeom);
		}

		if (m_mapObjectToNodeBuilder.contains(uuidGeom))
        {
            m_mapObjectToNodeBuilder.value(uuidGeom)->UpdateNode(eventPara.m_eEventType);
			m_colorbar.UpdateObj(uuidGeom);
        }
		
		m_cursor.UpdatePosition();
        m_pOSGWindow->UpdateVCRControlData(eventPara.m_objID);
    }

	m_pOSGWindow->GetOSGViewWidget()->update();
}

void CX3dscene::_RemoveObject(QUuid objID)
{
	if (!m_mapObjectToNodeBuilder.contains(objID)) 
		return;

	CX3DBuilderAbstract* pBuilder = m_mapObjectToNodeBuilder.value(objID);
	if (!pBuilder) 
		return;

	if (pBuilder->IsScalable())
		m_pGlobalTransform->removeChild(pBuilder->GetBuilderNode().get());
	else
		m_pRootNode->removeChild(pBuilder->GetBuilderNode().get());

	m_mapObjectToNodeBuilder.remove(objID);
	m_listDisplayedObjNode.removeOne(objID);
	delete pBuilder;

	CXPickhandle* pPickhandle = m_pOSGWindow->GetOSGViewWidget()->GetPickhandle();
	if (pPickhandle)
		pPickhandle->ResetPickedObject(GetObjectByID(objID));

	m_axes.UpdateBoundingBox();
	m_colorbar.RemoveObj(objID);
	UpdateLightingPosition();
}

void CX3dscene::_CreateObjectNode(CX3DBuilderAbstract* pBuilder, QUuid objID)
{
	osg::ref_ptr<osg::Group> builderNode = pBuilder->Build(objID);
	if (!builderNode.valid()) 
		return;

	m_axes.ExpandBy(::GetObjectByID(objID));

	if (m_listDisplayedObjNode.empty())
	{
		m_pGlobalTransform->addChild(m_axes.GetCoordinateAxes());
		m_pRootNode->addChild(m_colorbar.GetColorbar());
		m_pRootNode->addChild(m_compass.GetCompassNode());
		m_pRootNode->addChild(m_cursor.GetCursor());
		m_pRootNode->addChild(m_lighting.GetLightingNode());
	}
	
	pBuilder->SetBuilderNode(builderNode);
	if (pBuilder->IsScalable())
		m_pGlobalTransform->addChild(builderNode.get());
	else
		m_pRootNode->addChild(builderNode.get());

	m_colorbar.PushObj(objID);
	m_mapObjectToNodeBuilder.insert(objID, pBuilder);
	m_listDisplayedObjNode.push_back(objID);
}

void CX3dscene::SetOjbectVisiability(QUuid objID, bool bVisible)
{
	if (bVisible && m_mapObjectToNodeBuilder.contains(objID)) return;

	if (!bVisible)
	{
		_RemoveObject(objID);
		return;
	}

	CX3DBuilderAbstract *pBuilder = CXBuilderFactory::Instance().CreateBuilder(::GetObjectByID(objID)->GetObjectType(), e3DWindow);
	if (!pBuilder) return;

	pBuilder->SetWindowAndCoordMap(m_pOSGWindow, &m_coordMap);

	if (!m_coordMap.IsInitialized())
		m_coordMap.Init(objID);

	_CreateObjectNode(pBuilder, objID);
	UpdateLightingPosition();

	if (!dynamic_cast<osg::Group*>(m_pOSGWindow->GetOSGViewWidget()->getSceneData()))
	{
		m_pOSGWindow->GetOSGViewWidget()->setSceneData(m_pRootNode);
	}

	if (m_bFirst)
	{
		m_bFirst = false;
		m_pOSGWindow->slotViewAll();
	}
}

bool CX3dscene::_IsSeismicVolumeChanged(const QUuid & uuidVolume)
{
	auto pPickhandle = m_pOSGWindow->GetOSGViewWidget()->GetPickhandle();
	if (!pPickhandle)
		return false;

	auto pPickedSection = dynamic_cast<CXSeismicSection*>(pPickhandle->GetCurPickedObj());
	if (!pPickedSection)
		return false;

	auto pViewInfoSection = m_pOSGWindow->GetObjectViewInfo(pPickedSection->GetObjectID());
	if (pViewInfoSection->GetAttributeObjID() != uuidVolume)
		return false;

	m_mapObjectToNodeBuilder.value(pPickedSection->GetObjectID())->UpdateNode(EColormapChanged);

	return true;
}

osg::Switch* CX3dscene::_GetDisplayObjectSwitch(QUuid objID)
{
	CX3DBuilderAbstract* pBuilder = m_mapObjectToNodeBuilder.value(objID);
	if (!pBuilder) return nullptr;

	return pBuilder->GetBuilderNode()->asSwitch();
}

void CX3dscene::ShowCompass(bool bShow)
{
	m_compass.SetVisible(bShow);
}

void CX3dscene::ShowColormap(bool bShow)
{
	m_colorbar.SetVisible(bShow);
}

void CX3dscene::ShowCoordinate(bool bShow)
{
	m_axes.SetVisible(bShow);
}

void CX3dscene::ShowCoordinateGrid(bool bShow)
{
	m_axes.SetGridVisible(bShow);
}

void CX3dscene::slotUpdateZScale(double dZScale)
{
	for(auto pBuilder : m_mapObjectToNodeBuilder)
	{
		pBuilder->UpdateNode(EDataChanged);
	}

	m_pGlobalTransform->setMatrix(osg::Matrix::scale(1., 1., dZScale));
}

QList<QUuid> CX3dscene::GetAllDisplayObject()
{
	return m_mapObjectToNodeBuilder.keys();
}

void CX3dscene::slotUpdateWindowSize(int width, int height)
{
	m_colorbar.UpdatePosition();
	m_compass.UpdateViewport();
}

void CX3dscene::slotUpdateCompass()
{
	m_compass.UpdateViewInfo();
}

void CX3dscene::slotChangeBGColor(const QColor& color)
{
	QColor invCol(255 - color.red(), 255 - color.green(), 255 - color.blue());
	m_pOSGWindow->GetWindowInfo()->SetCoordColor(invCol);
	m_axes.UpdateWindowInfo();
}

void CX3dscene::slotSetProjectionMode(bool bOrtho)
{
	m_bOrtho = bOrtho;
	if (m_bOrtho)
	{
		m_pCamera->setProjectionMatrixAsOrtho(-7000.0f, 7000.0f, -3000.0f, 3000.0f, 1.0f, 10000.0f);
	}
	else
	{
		m_pCamera->setProjectionMatrixAsPerspective(30.0f, 1.5476f, 1.0f, 10000.0f);
	}
}

void CX3dscene::SetColorbarObjVisible(const QUuid & objID, bool bVisible)
{
	CXViewInfoObject *pViewInfo = m_pOSGWindow->GetObjectViewInfo(objID);
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

void CX3dscene::UpdateLightingPosition()
{
	osg::BoundingBox box = m_axes.GetBoundingBox();

	float fZScale = static_cast<float>(m_pOSGWindow->GetZScale());
	box.zMin() *= fZScale;
	box.zMax() *= fZScale;

	m_lighting.UpdatePosition(NX3DUtility::ExpandBox(box));

	for (auto iter = m_mapObjectToNodeBuilder.cbegin(); iter != m_mapObjectToNodeBuilder.cend(); ++iter)
	{
		CXObject* pObj = ::GetObjectByID(iter.key());
		if (pObj && QList<EXObjectType>{EX3DSurface, EX3DSurfaceAtt, EX3DHorizon, EX3DHorizonAtt, EXGS3DHorizonAtt, EXGS3DHorizonTWT, EXGS3DHorizonDepth, EXGS3DHorizonIso}.contains(pObj->GetObjectType()))
		{
			iter.value()->UpdateNode(ELightToggle);
		}
	}
}

void CX3dscene::UpdateAttribtue(const QUuid & uuidGeom)
{
	CX3DBuilderAbstract* pBuilder = m_mapObjectToNodeBuilder.value(uuidGeom);
	if (!pBuilder)
		return;

	pBuilder->UpdateNode(EColormapChanged);
	m_colorbar.UpdateObj(uuidGeom);
}

void CX3dscene::UpdateLightingViewInfo(int id)
{
	m_lighting.UpdateViewInfo(id);

	for (auto iter = m_mapObjectToNodeBuilder.cbegin(); iter != m_mapObjectToNodeBuilder.cend(); ++iter)
	{
		CXObject* pObj = ::GetObjectByID(iter.key());
		if (pObj && QList<EXObjectType>{EX3DSurface, EX3DSurfaceAtt, EX3DHorizon, EX3DHorizonAtt, EX3DHorizonAtt, EXGS3DHorizonAtt, EXGS3DHorizonTWT, EXGS3DHorizonDepth, EXGS3DHorizonIso}.contains(pObj->GetObjectType()))
		{
			iter.value()->UpdateNode(ELightToggle);
		}
	}
}

void CX3dscene::SetLightingSphereVisible(bool bVisible)
{
	m_lighting.SetSphereVisible(bVisible);
}
