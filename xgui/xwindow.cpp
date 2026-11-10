#include <qevent.h>
#include <qdebug.h>
#include "xwindow.h"
#include "xviewinfoobject.h"
#include "xviewinfocpcurve.h"
#include "xviewinfohiscurve.h"
#include "xviewinfolpcurve.h"
#include "xviewinfolpwell.h"
#include "xviewinfolpwelltops.h"
#include "xviewinfowellpath.h"
#include "xviewinfowellcurve.h"
#include "xglobal.h"
#include "xscene.h"
#include "xgraphicsview.h"
#include "xbaseconsole.h"
#include "xviewinfo3dwelltops.h"
#include "xviewinfo3dwelltopformation.h"
#include "xviewinfo3dfaultsticks.h"
#include "xviewinfo3dfracturepatches.h"
#include "xwindowinfosection.h"
#include "xviewinfo3dgridmodel.h"
#include "xeventconsole.h"
#include "xtemplate.h"
#include "xdbio.h"
#include "xviewinfosurface.h"
#include "xviewinfotimeslice.h"
#include "xviewinfowellcondition.h"
#include <cassert>
#include "xviewinfo3dhorizon.h"
#include "xviewinfo2dseismicline.h"
#include "xbaseconsole.h"
#include "xseismicsection.h"
#include "xviewinfolfmgeometry.h"
#include "xviewinfomanager.h"
#include "xwindowinfobasemap.h"
#include "xviewinfo3dsurvey.h"
#include "xviewinfoseismicdv.h"
#include "xviewinfoseismicsection.h"
#include "xviewinforandomsection.h"
#include "xviewinfo2dpolygon.h"
#include "xviewinfoprestackgather.h"
#include "xviewinfo3dpoints.h"

#include "gs3dhorizonviewinfo.h"
#include "gsstressmapviewinfo.h"
#include "gssectionviewinfo.h"
#include "gsrosediagramviewinfo.h"

CXWindow::CXWindow(QString sName, QWidget *parent, Qt::WindowFlags f):
m_sName(sName), QMainWindow(parent, f), IKEIO()
{
	setWindowTitle(m_sName);
	::SetProjectDirty();
}

CXWindow::~CXWindow()
{
	_FreeOwnResource();
}

void CXWindow::InitWindow()
{
	if (m_eWindowType == eGSBaseMap || m_eWindowType == eGSPDGWindow
		|| m_eWindowType == eGSSectionWindow || m_eWindowType == eGSFRGWindow)
		return;

	m_pView = new CXGraphicsView(GetScene(), m_eWindowType);
	m_pView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	setCentralWidget(m_pView);	
}

void CXWindow::ReleaseResource()
{
	_FreeOwnResource();
}

void CXWindow::_FreeOwnResource()
{
	// delete view info
	for (auto iter = m_mapObjViewInfo.begin(); iter != m_mapObjViewInfo.end(); ++iter)
	{
		CXViewInfoObject* pViewInfo = iter.value();
		if (pViewInfo) { delete pViewInfo; pViewInfo = nullptr; }
	}
	m_mapObjViewInfo.clear();
}

void CXWindow::SetWindowVisibility(bool bVisible)
{
}

//	Get the specified object's viewinfo on this window.
CXViewInfoObject* CXWindow::GetObjectViewInfo(const QUuid& objID)
{
	// Already exist, get it.
	CXViewInfoObject* pViewInfo = m_mapObjViewInfo.value(objID, NULL);
	if (pViewInfo)
		return pViewInfo;

	CXObject* pObj = ::GetObjectByID(objID);
	if (pObj) // Geometry exist, attribute use geometry viewinfo.
	{
		pViewInfo = m_mapObjViewInfo.value(pObj->GetGeometryObject()->GetObjectID(), nullptr);
		if (pViewInfo)
			return pViewInfo;
	}

	// Else, get a new one.
	EXObjectType eObjType = pObj ? pObj->GetGeometryObject()->GetObjectType() : EXBegin;
	switch (m_eWindowType)
	{
	case eHistogramWindow:
		pViewInfo = new CXViewInfoHisCurve;
		break;
	case eCrossplotWindow:
		pViewInfo = new CXViewInfoCPCurve;
		break;
	case eLogViewWindow:
		if (eObjType == EXWell)
		{
			pViewInfo = new CXViewInfoLPWell(pObj);
		}
		else if (eObjType == EXWellTops)
		{
			pViewInfo = new CXViewInfoLPWellTops;
		}
		else if (eObjType == EXWellCurve)
		{
			pViewInfo = new CXViewInfoLPCurve(pObj);
		}
		break;
	case e3DWindow:
		if (eObjType == EXWell)
		{
			pViewInfo = new CXViewInfoWellPath;
		}
		else if (eObjType == EXWellCurve)
		{
			pViewInfo = new CXViewInfoWellCurve;
		}
		else if (eObjType == EXWellTops)
		{
			pViewInfo = new CXViewInfo3DWellTops;
		}
		else if (eObjType == EXWellTopFormation)
		{
			pViewInfo = new CXViewInfo3DWellTopFormation;
		}
		else if (eObjType == EXFaultSticks || eObjType == EXGMFault)
		{
			pViewInfo = new CXViewInfo3DFaultSticks;
		}
		else if (eObjType == EXFracturePatch)
		{
			pViewInfo = new CXViewInfo3DFracturePatches;
		}
		else if (eObjType == EX3DSurface || eObjType == EX3DHorizon
			|| eObjType == EXGS3DHorizonTWT || eObjType == EXGS3DHorizonDepth
			|| eObjType == EXGS3DHorizonIso || eObjType == EXGS3DHorizonAtt)
		{
			pViewInfo = new CXViewInfoSurface;
		}
		else if (eObjType == EXGridModel || eObjType == EXIntersectionGrid)
		{
			pViewInfo = new CXViewInfo3DGridModel;
		}
		else if (eObjType == EXWellCondition)
		{
			pViewInfo = new CXViewInfoWellCondition;
		}
		else if (eObjType == EXLowFrequencyModel)
		{
			pViewInfo = new CXViewInfoLFMGeometry;
		}
		else if (eObjType == EXSeismicDataVolume)
		{
			pViewInfo = new CXViewInfoSeismicDV;
		}
		else if (eObjType == EXSeismicSection)
		{
			if (eTimeSlice == dynamic_cast<CXSeismicSection*>(pObj)->GetSectionType())
			{
				pViewInfo = new CXViewInfoTimeSlice;
			}
			else
			{
				pViewInfo = new CXViewInfoSeismicSection;
			}
		}
		else if (eObjType == EX2DSeismicLine)
		{
			pViewInfo = new CXViewInfo2DSeismicLine;
		}
		else if (eObjType == EX3DPoints)
		{
			pViewInfo = new CXViewInfo3DPoints;
		}
		else
		{
			pViewInfo = new CXViewInfoObject;
		}
		break;
	case e3DBaseMap:
		if (eObjType == EXFaultSticks)
		{
			pViewInfo = new CXViewInfo3DFaultSticks;
		}
		else if (eObjType == EXWell)
		{
			pViewInfo = new CXViewInfoWellPath;
		}
		else if (eObjType == EX3DSurface || eObjType == EX3DHorizon
			|| eObjType == EXGS3DHorizonTWT || eObjType == EXGS3DHorizonDepth
			|| eObjType == EXGS3DHorizonIso || eObjType == EXGS3DHorizonAtt)
		{
			pViewInfo = new CXViewInfoSurface;
		}
		else if (eObjType == EX2DSeismicLine)
		{
			pViewInfo = new CXViewInfo2DSeismicLine;
		}
		else if (eObjType == EX3DSurvey)
		{
			pViewInfo = new CXViewInfo3DSurvey;
		}
		else if (eObjType == EXSeismicDataVolume)
		{
			pViewInfo = new CXViewInfoSeismicDV;
			// Calculate Fold map.
			auto pViewInfoDV = dynamic_cast<CXViewInfoSeismicDV*>(pViewInfo);
			pViewInfoDV->CalcFoldHistogram(pObj);
		}
		else if (eObjType == EXSeismicSection)
		{
			if (eTimeSlice == dynamic_cast<CXSeismicSection*>(pObj)->GetSectionType())
			{
				pViewInfo = new CXViewInfoTimeSlice;
			}
			else
			{
				pViewInfo = new CXViewInfoSeismicSection;
			}
		}
		else if (eObjType == EXRandomSection)
		{
			pViewInfo = new CXViewInfoRandomSection;
		}
		else if (eObjType == EX2DPolygon || eObjType == EXFaultPolygon)
		{
			pViewInfo = new CXViewInfo2DPolygon;
		}
		else if (eObjType == EXPrestackGather)
		{
			pViewInfo = new CXViewInfoPreStackGather;
		}
		else if (eObjType == EX3DPoints)
		{
			pViewInfo = new CXViewInfo3DPoints;
		}
		else
		{
			pViewInfo = new CXViewInfoObject;
		}
		break;
	case eSectionWindowBlank:
	case eSectionWindow:
		if (this->GetObjectID() == objID)
		{
			pViewInfo = new CXWindowInfoSection;
		}
		else if (eObjType == EXWell)
		{
			pViewInfo = new CXViewInfoWellPath;
		}
		else if (eObjType == EXWellCurve)
		{
			pViewInfo = new CXViewInfoWellCurve;
		}
		else if (eObjType == EXWellTopFormation)
		{
			pViewInfo = new CXViewInfo3DWellTopFormation;
		}
		else if (eObjType == EXFaultSticks)
		{
			pViewInfo = new CXViewInfo3DFaultSticks;
		}
		else if (eObjType == EX3DSurface)
		{
			pViewInfo = new CXViewInfoSurface;
		}
		else if (eObjType == EX3DHorizon)
		{
			pViewInfo = new CXViewInfo3DHorizon;
		}
		else if (eObjType == EXLowFrequencyModel)
		{
			pViewInfo = new CXViewInfoLFMGeometry;
		}
		else if (eObjType == EXSeismicSection && eTimeSlice == dynamic_cast<CXSeismicSection*>(pObj)->GetSectionType())
		{
			pViewInfo = new CXViewInfoTimeSlice;
		}
		else
		{
			pViewInfo = new CXViewInfoObject;
			
			if (EXSeismicSection == eObjType || EXRandomSection == eObjType)
			{
				pViewInfo->SetNeedColormap(false);
			}
		}
		break;
	case eGSSectionWindow:
	case eGSBaseMap:
	case eGSPDGWindow:
	case eGSFRGWindow:
		if (eObjType == EXGS3DHorizonTWT || eObjType == EXGS3DHorizonDepth 
			|| eObjType == EXGS3DHorizonIso || eObjType == EXGS3DHorizonAtt)
			pViewInfo = new GS3DHorizonViewInfo;
		else if (eObjType == EXGSStressMap)
			pViewInfo = new GSStressMapViewInfo;
		else if (eObjType == EXGSSection)
			pViewInfo = new GSSectionViewInfo;
		else if (eObjType == EXGSRoseDiagram)
			pViewInfo = new GSRoseDiagramViewInfo;
		else
			pViewInfo = new CXViewInfoObject;
		break;
	default:
		throw std::invalid_argument("received invalid window type");
	}

	pViewInfo->SetViewObjectID(objID);
	m_mapObjViewInfo.insert(objID, pViewInfo);

	return pViewInfo;
}

//	Get a list of displayed objects.
QList<QUuid> CXWindow::GetDisplayedObjects()
{
	QList<QUuid> listDisplayedObjectID;
	QSet<QUuid> setObjectIDCache;

	for (auto iter = m_mapObjViewInfo.begin(); iter != m_mapObjViewInfo.end(); ++iter)
	{
		Q_ASSERT(iter.value());
		if (!iter.value()->GetVisible())
			continue;

		listDisplayedObjectID << iter.key(); // geometry.
		setObjectIDCache << iter.key();

		const QUuid& attributeID = iter.value()->GetAttributeObjID();
		if (attributeID.isNull() || !::GetObjectByID(attributeID))
			continue;

		if (!setObjectIDCache.contains(attributeID))
		{
			listDisplayedObjectID << attributeID; // attribute
			setObjectIDCache << attributeID;
		}
	}

	return listDisplayedObjectID;
}

bool CXWindow::SetObjectVisibility(QUuid objID, bool bVisible)
{
	//	Find out the object viewinfo, create one if not exist.
	CXViewInfoObject *pViewInfo = GetObjectViewInfo(objID);
	if (!pViewInfo)
		return false;

	//	Status not changed.
	if(bVisible == pViewInfo->GetVisible())
		return false;

	pViewInfo->SetVisible(bVisible);

	CXScene *pScene = GetScene();
	bool bResult;

	if(bVisible)
	{
		bResult = pScene->CreateItem(objID, pViewInfo);
	}
	else
	{
		bResult = pScene->DeleteItem(objID);
	}

	if(bResult)
	{
		itemChanged(bVisible, objID);
		RefreshScene();
	}

	return bResult;
}

void CXWindow::RefreshScene()
{
	CXScene *pScene = GetScene();
	pScene->update();
}

bool CXWindow::Serialize(bool bSave)
{
	// base object
	if (!IKEIO::Serialize(bSave))
		return false;	

	QString strTable = "window";

	// save
	if (bSave)
	{
		QStringList strFieldList;
		strFieldList<<"ID";	
		strFieldList<<"WindowName";

		QList<QVariant> vtList;

		vtList.append(GetObjectID().toString());
		vtList.append(m_sName);


		return ::GetDBIO()->UpdateInsert(strTable, strFieldList, vtList, GetObjectID().toString());
	}
	else
	{
		QStringList strFieldList;
		strFieldList<<"WindowName";

		QSqlQuery query = ::GetDBIO()->Select(strTable, strFieldList, this->GetObjectID().toString());

		if( query.first() )
		{
			m_sName = query.value(0).toString();
			setWindowTitle(m_sName);
		}

		return true;
	}
}

bool CXWindow::SerializeData(CXArchive& ar)
{
	if (!IKEIO::SerializeData(ar))
		return false;

	if (ar.IsSaving())
	{
		QList<QUuid> listDisplayedObjID = GetDisplayedObjects();

		ar << listDisplayedObjID.size();

		for (const auto& objID : listDisplayedObjID)
		{
			ar << objID;

			CXViewInfoObject* pViewInfo = GetObjectViewInfo(objID);
			pViewInfo->SetModifiedFlag();
			ar << pViewInfo->GetObjectID();
			pViewInfo->Serialize(true);
		}

		// window information
		CXBaseParameter* pWindowInfo = GetWindowInfo();
		if (pWindowInfo)
		{			
			ar << pWindowInfo->GetObjectID();
			pWindowInfo->Serialize(true);
		}
	}
	else
	{
		m_mapObjViewInfo.clear();

		int nSize;
		ar>>nSize;

		for (int i = 0; i < nSize; ++i)
		{
			QUuid objID, viewInfoID;
			ar>> objID;
			ar>> viewInfoID;

			CXViewInfoObject* pObjViewInfo = GetObjectViewInfo(objID);
			assert(pObjViewInfo);

			pObjViewInfo->SetObjectID(viewInfoID);
			pObjViewInfo->Serialize(false);
			pObjViewInfo->CheckColormapNameValid();
		}

		CXBaseParameter* pWindowInfo = GetWindowInfo();
		if (pWindowInfo)
		{
			QUuid winInfoID;
			ar >> winInfoID;
			pWindowInfo->SetObjectID(winInfoID);
			pWindowInfo->Serialize(false);
		}
	}

	return true;
}

QUuid CXWindow::GetObjIDFromViewInfo(CXViewInfoObject* pViewInfo)
{
	return m_mapObjViewInfo.key(pViewInfo, QUuid());
}

void CXWindow::UpdateView(const CXEventParameter& eventPara)
{
	if (eventPara.m_eEventType == EDeleted)
	{
		CXViewInfoObject* pViewInfo = m_mapObjViewInfo.value(eventPara.m_objID);
		if (!pViewInfo)
			delete pViewInfo;
		m_mapObjViewInfo.remove(eventPara.m_objID);
	}	
}

CXBaseParameter* CXWindow::GetWindowInfo()
{
	return nullptr;
}

void CXWindow::SaveScene()
{

}

void CXWindow::RestoreScene()
{

}

bool CXWindow::event(QEvent *e)
{
	if (e->type() == QEvent::Close)
	{
		CXBaseConsole *pConsole = (CXBaseConsole *)::GetConsole();
		pConsole->SetActiveWindow(NULL);
		pConsole->RemoveOneWindow(GetObjectID());
	}
	else if (e->type() == QEvent::WindowActivate /*&& m_pView != NULL*/)
	{
		CXBaseConsole *pConsole = (CXBaseConsole *)::GetConsole();
		pConsole->SetActiveWindow(this);
	}
	return QMainWindow::event(e);
}

void CXWindow::InitOpenGL()
{
}

void CXWindow::UpdateAttribute(const QUuid & uuidGeom, const QUuid & uuidAttr)
{
	auto pViewInfo = GetObjectViewInfo(uuidGeom);
	pViewInfo->SetAttributeObjID(uuidAttr);

	CXObject* pAttribute = ::GetObjectByID(uuidAttr);
	double dMin, dMax;
	pAttribute->GetDataRange(dMin, dMax);
	pViewInfo->SetDisplayDataMin(dMin);
	pViewInfo->SetDisplayDataMax(dMax);
}
