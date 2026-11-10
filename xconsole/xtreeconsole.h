#ifndef _CXTreeCONSOLE_H__
#define _CXTreeCONSOLE_H__

#include "xconsole_global.h"
#include <quuid.h>

class CXWindow;
class CXObject;
class CXViewInfoObject;

///@brief	It's the console of main data tree.
///@author	Xiong Xiong
///@date	Apr, 2014
///@see		
class XCONSOLE_EXPORT CXTreeConsole
{
public:
	static void SetObjectVisibility(CXWindow *, QUuid objectID, bool bVisible);

private:
	static void _SetLVWindowObjVisibility(CXWindow* pWin, CXObject* pObj, bool bChecked);
	static void _Set3DWindowObjVisibility(CXWindow* pWin, CXObject* pObj, bool bChecked);
	static void _Set2DWindowObjVisibility(CXWindow* pWin, CXObject* pObj, bool bChecked);
	static void _SetBMWindowObjVisibility(CXWindow* pWin, CXObject* pObj, bool bChecked);

	static void _SetObjListVisibility(CXWindow* pWin, const QList<CXObject*>& listObj, bool bChecked);
	static void _SetWellCurveAliasVisibility(CXWindow* pWin, CXObject* pWellCurveAlias, bool bChecked);
	static void _Set2DSeismicDataLineVisibility(CXWindow* pWin, CXObject* pSeismicDataLine, bool bChecked);
	static void _Set2DSurveyVisibilityIn3DWindow(CXWindow* pWin, CXObject* p2DSurvey, bool bChecked);
	static void _Set3DPropertyModelVisibility(CXWindow* pWin, CXObject* pProperty, bool bChecked);
	static void _SetGeometryObjectVisible(CXWindow* pWin, const QUuid& attributeID);
	static void _SetIntersectionGridVisibility(CXWindow* pWin, CXObject* pIntersection, bool bChecked);
	static void _SetSectionVisible(CXWindow* pWin, CXObject* pSection, bool bChecked);

	static void _UncheckOtherAttributeTreeNode(CXObject* pAttribute);
	static void _UncheckAttributeTreeNodeWhenGeometryInvisible(CXWindow* pWin, CXObject* pGeometry, bool bChecked);

	static QUuid _FindPropertyModelID(CXWindow* pWin, CXObject* pGeometry);
	static bool _IsAnyGeometryVisible(CXWindow* pWin, const QList<CXObject*>& listGeometry, CXObject* pExclude = nullptr);
};

#endif