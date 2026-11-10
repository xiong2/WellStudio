#include "xtreeconsole.h"
#include "xwindow.h"
#include "xglobal.h"
#include "xviewinfoobject.h"
#include "xgeneralfolder.h"
#include "xseismicsection.h"
#include "xseismicsubvolume.h"
#include "xseismicdatavolume.h"
#include "xwell.h"
#include "xwellcurve.h"
#include "xtree.h"
#include "x3dsurface.h"
#include "xpropertymodel.h"
#include "xgridmodel.h"
#include "xwellcondition.h"
#include "xtreewidgetitem.h"
#include "xseismicrandomsection.h"
#include "xcurvecells.h"
#include "xscene.h"
#include "xlfmattribute.h"
#include "xlfmgeometry.h"
#include "x2dsectionwindow.h"
#include <cassert>
#include "xbasemapwindow.h"
#include "x3dwindow.h"
#include "x2dsectionwindow.h"
#include "xglobal.h"
#include "xtemplate.h"

void CXTreeConsole::SetObjectVisibility(CXWindow *pWindow, QUuid objectID, bool bVisible)
{
	CXObject* pObj = ::GetObjectByID(objectID);

	if (!pWindow || !pObj)
		return;

	switch (pWindow->GetWindowType())
	{
	case eLogViewWindow:
		_SetLVWindowObjVisibility(pWindow, pObj, bVisible);
		break;
	case e3DWindow:
		_Set3DWindowObjVisibility(pWindow, pObj, bVisible);
		break;
	case eSectionWindowBlank:
	case eSectionWindow:
		_Set2DWindowObjVisibility(pWindow, pObj, bVisible);
		break;
	case e3DBaseMap:
		_SetBMWindowObjVisibility(pWindow, pObj, bVisible);
		break;
	default:
		pWindow->SetObjectVisibility(objectID, bVisible);
	}
}

void CXTreeConsole::_SetLVWindowObjVisibility(CXWindow* pWin, CXObject* pObj, bool bChecked)
{
	switch (pObj->GetObjectType())
	{
	case EXWell:
		if (!bChecked)
			_SetObjListVisibility(pWin, pObj->GetChildren(EXWellCurve), false);
		else
		{
			CXWell *pWell = (CXWell *)pObj;
			_SetObjListVisibility(pWin, pWell->GetSpecialCurveList(CXTemplate::GetTemplate("MD")->GetID()), true);
		}
		break;
	case EXWellCurve:
		if (!bChecked)
		{
			if (pObj->GetTemplateID() == CXTemplate::GetTemplate("MD")->GetID())
			{
				CXObject *pParent = pObj->GetParent();
				_SetObjListVisibility(pWin, pParent->GetChildren(EXWellCurve), false);
				pWin->SetObjectVisibility(pParent->GetObjectID(), bChecked);
				CXTree::Instance().ChangeTreeItemStatus({ pParent->GetObjectID() }, false);
			}
		}
		else
		{
			CXObject *pParent = pObj->GetParent();
			pWin->SetObjectVisibility(pParent->GetObjectID(), true);
			CXTree::Instance().ChangeTreeItemStatus({ pParent->GetObjectID() }, true);

			CXWell *pWell = (CXWell *)pParent;
			_SetObjListVisibility(pWin, pWell->GetSpecialCurveList(CXTemplate::GetTemplate("MD")->GetID()), true);
		}
		break;
	default:
		return;
	}

	if (!pWin->SetObjectVisibility(pObj->GetObjectID(), bChecked))
	{
		CXTree::Instance().ChangeTreeItemStatus({ pObj->GetObjectID() }, !bChecked);
	}
}

void CXTreeConsole::_Set3DWindowObjVisibility(CXWindow* pWin, CXObject* pObj, bool bChecked)
{
	switch (pObj->GetObjectType())
	{
	case EXWell:
		if (!bChecked)
		{
			_SetObjListVisibility(pWin, pObj->GetChildren(EXWellCurve), false);
		}
		break;
	case EXWellCurve:
		if (bChecked)
		{
			pWin->SetObjectVisibility(pObj->GetParent()->GetObjectID(), true);
			CXTree::Instance().ChangeTreeItemStatus({ pObj->GetParent()->GetObjectID() }, true);
		}
		break;
	case EXWellCurveAlias:
		_SetWellCurveAliasVisibility(pWin, pObj, bChecked);
		break;
	case EX2DSurvey:
		_Set2DSurveyVisibilityIn3DWindow(pWin, pObj, bChecked);
		break;
	case EXIntersectionGrid:
		_SetIntersectionGridVisibility(pWin, pObj, bChecked);
		return;
	case EXGridModel:
		if (bChecked)
		{
			QUuid propertyID = _FindPropertyModelID(pWin, pObj);
			_SetObjListVisibility(pWin, pObj->GetChildren(EXIntersectionGrid), false);
			pWin->SetObjectVisibility(pObj->GetObjectID(), true);
			if (!propertyID.isNull())
			{
				pWin->UpdateAttribute(pObj->GetObjectID(), propertyID);
			}
		}
		else
		{
			_UncheckAttributeTreeNodeWhenGeometryInvisible(pWin, pObj, bChecked);
			pWin->SetObjectVisibility(pObj->GetObjectID(), false);
		}
		return;
	case EXPropertyModel:
		_Set3DPropertyModelVisibility(pWin, pObj, bChecked);
		return;
	case EXWellCondition:
	case EXLowFrequencyModel:
	case EXLFMUpscalingGeometry:
	case EX3DHorizon:
		_UncheckAttributeTreeNodeWhenGeometryInvisible(pWin, pObj, bChecked);
		break;
	case EXCurveCells:
	case EXLFMAttribute:
	case EXLFMUpscalingAttribute:
	case EX3DHorizonAtt:
	{
		if (bChecked)
		{
			_SetGeometryObjectVisible(pWin, pObj->GetObjectID());
			_UncheckOtherAttributeTreeNode(pObj);
		}
		CXObject* pGeometry = pObj->GetGeometryObject();
		pWin->UpdateAttribute(pGeometry->GetObjectID(), bChecked ? pObj->GetObjectID() : pGeometry->GetObjectID());
		return; 
	}
	case EXSeismicDataLine:
		_Set2DSeismicDataLineVisibility(pWin, pObj, bChecked);
		break;
	default:
		if (pObj->IsFolder())
		{
			_SetObjListVisibility(pWin, pObj->GetChildrenList(), bChecked);
		}
	}

	pWin->SetObjectVisibility(pObj->GetObjectID(), bChecked);
}

void CXTreeConsole::_Set2DWindowObjVisibility(CXWindow* pWin, CXObject* pObj, bool bChecked)
{
	switch (pObj->GetObjectType())
	{
	case EXWell:
		if (!bChecked)
		{
			_SetObjListVisibility(pWin, pObj->GetChildren(EXWellCurve), false);
		}
		break;
	case EXWellCurveAlias:
		_SetWellCurveAliasVisibility(pWin, pObj, bChecked);
		break;
	case EXWellCurve:
		if (bChecked)
		{
			pWin->SetObjectVisibility(pObj->GetParent()->GetObjectID(), true);
			CXTree::Instance().ChangeTreeItemStatus({ pObj->GetParent()->GetObjectID() }, true);
		}
		break;
	case EXSeismicSection:
	case EXRandomSection:
		if (pObj->GetObjectType() == EXSeismicSection && ((CXSeismicSection *)pObj)->GetSectionType() == eTimeSlice)
			break;

		if (!bChecked)
		{
			dynamic_cast<CX2DSectionWindow*>(pWin)->ClearContent();
		}
		_SetSectionVisible(pWin, pObj, bChecked);
		break;
	default:
		if (pObj->IsFolder())
		{
			_SetObjListVisibility(pWin, pObj->GetChildrenList(), bChecked);
		}
	}

	pWin->SetObjectVisibility(pObj->GetObjectID(), bChecked);
}

void CXTreeConsole::_SetBMWindowObjVisibility(CXWindow* pWin, CXObject* pObj, bool bChecked)
{
	switch (pObj->GetObjectType())
	{
	case EXSeismicSection:
	case EXSeismicDataVolume:
		if (bChecked)
		{
			_SetObjListVisibility(pWin, { pObj->GetAncient(EX3DSurvey) }, bChecked);
		}
		break;
	case EX3DHorizon:
		_UncheckAttributeTreeNodeWhenGeometryInvisible(pWin, pObj, bChecked);
		break;
	case EX3DHorizonAtt:
	{
		if (bChecked)
		{
			_SetGeometryObjectVisible(pWin, pObj->GetObjectID());
			_UncheckOtherAttributeTreeNode(pObj);
		}
		CXObject* pGeometry = pObj->GetGeometryObject();
		pWin->UpdateAttribute(pGeometry->GetObjectID(), bChecked ? pObj->GetObjectID() : pGeometry->GetObjectID());
		return;
	}
	default:
		if (pObj->IsFolder())
		{
			_SetObjListVisibility(pWin, pObj->GetChildrenList(), bChecked);
			//dynamic_cast<CXBaseMapWindow*>(pWin)->slotViewAll();
		}
	}

	pWin->SetObjectVisibility(pObj->GetObjectID(), bChecked);
}

void CXTreeConsole::_SetObjListVisibility(CXWindow* pWin, const QList<CXObject*>& listObj, bool bChecked)
{
	QList<QUuid> listObjID;
	for (CXObject* pObj : listObj)
	{
		listObjID << pObj->GetObjectID();

		pWin->SetObjectVisibility(pObj->GetObjectID(), bChecked);
	}

	CXTree::Instance().ChangeTreeItemStatus(listObjID, bChecked);
}

void CXTreeConsole::_SetWellCurveAliasVisibility(CXWindow* pWin, CXObject* pWellCurveAlias, bool bChecked)
{
	QList<QUuid> listCurveID;

	for (CXObject* pWell : pWellCurveAlias->GetAncient(EXWellFolder)->GetChildren(EXWell))
	{
		CXViewInfoObject* pWellViewInfo = pWin->GetObjectViewInfo(pWell->GetObjectID());
		if (!pWellViewInfo->GetVisible())
			continue;

		for (CXObject* pObj : pWell->GetChildren(EXWellCurve))
		{
			CXWellCurve* pCurve = dynamic_cast<CXWellCurve*>(pObj);
			if (pCurve && pCurve->GetAliasID() == pWellCurveAlias->GetObjectID())
			{
				pWin->SetObjectVisibility(pCurve->GetObjectID(), bChecked);
				listCurveID << pCurve->GetObjectID();
			}
		}
	}

	CXTree::Instance().ChangeTreeItemStatus(listCurveID, bChecked);
}

void CXTreeConsole::_Set2DSeismicDataLineVisibility(CXWindow * pWin, CXObject * pSeismicDataLine, bool bChecked)
{
	CXObject* p2DLine = pSeismicDataLine->GetGeometryObject();
	Q_ASSERT(p2DLine == pSeismicDataLine->GetParent());

	pWin->SetObjectVisibility(pSeismicDataLine->GetObjectID(), bChecked);

	if (bChecked)
	{
		_UncheckOtherAttributeTreeNode(pSeismicDataLine);
		pWin->UpdateAttribute(p2DLine->GetObjectID(), pSeismicDataLine->GetObjectID());
	}

	CXTree::Instance().ChangeTreeItemStatus({ pSeismicDataLine->GetObjectID() }, bChecked);
}

void CXTreeConsole::_Set2DSurveyVisibilityIn3DWindow(CXWindow* pWin, CXObject* p2DSurvey, bool bChecked)
{
	for (CXObject* p2DLine : p2DSurvey->GetChildrenList())
	{
		Q_ASSERT(EX2DSeismicLine == p2DLine->GetObjectType());
		if (p2DLine->GetChildrenList().isEmpty()) continue;
		_Set2DSeismicDataLineVisibility(pWin, p2DLine->GetChildrenList().front(), bChecked);
	}

	pWin->SetObjectVisibility(p2DSurvey->GetObjectID(), bChecked);
}

void CXTreeConsole::_Set3DPropertyModelVisibility(CXWindow* pWin, CXObject* pProperty, bool bChecked)
{
	CXObject* pGeometry = pProperty->GetGeometryObject();
	CXViewInfoObject* pGeometryViewInfo = pWin->GetObjectViewInfo(pGeometry->GetObjectID());

	if (bChecked)
	{
		bool bHasGeometry = false;

		if (pGeometryViewInfo->GetVisible()) // geometry checked.
		{
			pWin->UpdateAttribute(pGeometry->GetObjectID(), pProperty->GetObjectID());
			bHasGeometry = true;
		}
		else // check intersections.
		{
			for (CXObject* pIntersection : pGeometry->GetChildren(EXIntersectionGrid))
			{
				CXViewInfoObject* pIntersectionViewInfo = pWin->GetObjectViewInfo(pIntersection->GetObjectID());
				if (pIntersectionViewInfo->GetVisible())
				{
					pWin->UpdateAttribute(pIntersection->GetObjectID(), pProperty->GetObjectID());
					bHasGeometry = true;
				}
			}
		}

		if (!bHasGeometry)
		{
			_SetGeometryObjectVisible(pWin, pProperty->GetObjectID());
			pWin->UpdateAttribute(pGeometry->GetObjectID(), pProperty->GetObjectID());
		}

		_UncheckOtherAttributeTreeNode(pProperty);
	}
	else
	{
		if (pGeometryViewInfo->GetVisible() && pGeometry->GetObjectID() != pGeometryViewInfo->GetAttributeObjID())
		{
			pWin->UpdateAttribute(pGeometry->GetObjectID(), pGeometry->GetObjectID());
		}

		for (CXObject* pIntersection : pGeometry->GetChildren(EXIntersectionGrid))
		{
			CXViewInfoObject* pIntersectionViewInfo = pWin->GetObjectViewInfo(pIntersection->GetObjectID());
			if (pIntersectionViewInfo->GetVisible() && pIntersection->GetObjectID() != pIntersectionViewInfo->GetAttributeObjID())
			{
				pWin->UpdateAttribute(pIntersection->GetObjectID(), pIntersection->GetObjectID());
			}
		}
	}
}

void CXTreeConsole::_SetGeometryObjectVisible(CXWindow* pWin, const QUuid& attributeID)
{
	CXObject* pGeometry = ::GetObjectByID(attributeID)->GetGeometryObject();
	pWin->SetObjectVisibility(pGeometry->GetObjectID(), true);
	CXTree::Instance().ChangeTreeItemStatus({ pGeometry->GetObjectID() }, true);
}

void CXTreeConsole::_SetIntersectionGridVisibility(CXWindow* pWin, CXObject* pIntersection, bool bChecked)
{
	CXObject* pGeometry = pIntersection->GetParent();
	QUuid propertyID = _FindPropertyModelID(pWin, pGeometry);

	if (bChecked)
	{
		pWin->SetObjectVisibility(pGeometry->GetObjectID(), false);
		CXTree::Instance().ChangeTreeItemStatus({ pGeometry->GetObjectID() }, false);

		pWin->SetObjectVisibility(pIntersection->GetObjectID(), true);
		if (!propertyID.isNull())
		{
			pWin->UpdateAttribute(pIntersection->GetObjectID(), propertyID);
		}
	}
	else
	{
		if (!_IsAnyGeometryVisible(pWin, pGeometry->GetChildren(EXIntersectionGrid), pIntersection) && !propertyID.isNull())
		{
			CXTree::Instance().ChangeTreeItemStatus({ propertyID }, false);
		}
		pWin->SetObjectVisibility(pIntersection->GetObjectID(), false);
	}
}

void CXTreeConsole::_SetSectionVisible(CXWindow* pWin, CXObject* pSection, bool bChecked)
{
	if (!bChecked)
		return;

	QList<QUuid> listOtherSectionID;

	for (CXObject* pOther : pSection->GetParent()->GetChildren(EXSeismicSection) + pSection->GetParent()->GetChildren(EXRandomSection))
	{
		if (pOther->GetObjectType() != eTimeSlice && pOther != pSection)
		{
			pWin->SetObjectVisibility(pOther->GetObjectID(), false);
			listOtherSectionID << pOther->GetObjectID();
		}
	}

	CXTree::Instance().ChangeTreeItemStatus(listOtherSectionID, false);
}

void CXTreeConsole::_UncheckOtherAttributeTreeNode(CXObject * pAttribute)
{
	QList<QUuid> listAttribute;
	for (CXObject* pAtt : pAttribute->GetParent()->GetChildren(pAttribute->GetObjectType()))
	{
		if (pAtt == pAttribute)
			continue;

		listAttribute << pAtt->GetObjectID();
	}
	CXTree::Instance().ChangeTreeItemStatus(listAttribute, false);
}

void CXTreeConsole::_UncheckAttributeTreeNodeWhenGeometryInvisible(CXWindow* pWin, CXObject* pGeometry, bool bChecked)
{
	if (bChecked)
		return;

	CXViewInfoObject* pViewInfo = pWin->GetObjectViewInfo(pGeometry->GetObjectID());
	if (pViewInfo->GetAttributeObjID() != pGeometry->GetObjectID()) // has attribute.
	{
		CXTree::Instance().ChangeTreeItemStatus({ pViewInfo->GetAttributeObjID() }, false);
	}
}

QUuid CXTreeConsole::_FindPropertyModelID(CXWindow* pWin, CXObject * pGeometry)
{
	CXViewInfoObject* pGeometryViewInfo = pWin->GetObjectViewInfo(pGeometry->GetObjectID());
	if (pGeometryViewInfo->GetVisible())
	{
		if (pGeometryViewInfo->GetAttributeObjID() != pGeometry->GetObjectID())
		{
			return pGeometryViewInfo->GetAttributeObjID();
		}
	}
	else
	{
		for (CXObject* pIntersection : pGeometry->GetChildren(EXIntersectionGrid))
		{
			CXViewInfoObject* pIntersectionViewInfo = pWin->GetObjectViewInfo(pIntersection->GetObjectID());
			if (pIntersectionViewInfo->GetVisible() && pIntersection->GetObjectID() != pIntersectionViewInfo->GetAttributeObjID())
			{
				return pIntersectionViewInfo->GetAttributeObjID();
			}
		}
	}

	return QUuid();
}

bool CXTreeConsole::_IsAnyGeometryVisible(CXWindow* pWin, const QList<CXObject*>& listGeometry, CXObject* pExclude)
{
	for (CXObject* pGeometry : listGeometry)
	{
		if (pGeometry == pExclude)
			continue;

		CXViewInfoObject* pGeometryViewInfo = pWin->GetObjectViewInfo(pGeometry->GetObjectID());
		if (!pGeometryViewInfo->GetVisible())
			continue;

		return true;
	}

	return false;
}