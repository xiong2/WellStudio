#ifndef XGLOBAL_H
#define XGLOBAL_H

#pragma execution_character_set("utf-8")

#include <qmap.h>
#include "xio.h"
#include "xdata_global.h"
#include <qcolor.h>
#include "xmathmacro.h"
#include <QDebug>

class QUuid;
class QTextCodec;

class CXProject;
class CXBaseConsole;
class CXConsole;
class CXRandomGenerator;
class CXWellCurve;
class CXDBIO;
class CXObject;
class CXWindow;
class QUndoGroup;
class CXViewInfoObject;
class CXHistogram;

///@brief	The current opening project.
extern XDATA_EXPORT CXProject* g_pProject;

///@brief	The current opening project.
extern XDATA_EXPORT bool g_bShowTestAction;

///@brief	The global console pointer.
extern XDATA_EXPORT CXConsole* g_pConsole;

///@brief The global unique invalid data
extern XDATA_EXPORT double g_dInvalidData;

///@brief Whether current project data is dirty.
extern XDATA_EXPORT bool g_bDirtyProject;

///@brief The global unique invalid data
extern XDATA_EXPORT QString g_strProductName;

///@brief The global 3-D window Z factor
extern XDATA_EXPORT float g_f3DZFactor;

///@brief	Whether using metric unit system.
XDATA_EXPORT bool UsingMetricUnit();

///@brief	Whether using Chinese characters.
XDATA_EXPORT bool UsingChinese();

///@brief Get the DB IO of the project
XDATA_EXPORT CXDBIO* GetDBIO();

///@brief Set current project dirty.
XDATA_EXPORT void SetProjectDirty(bool bDirty = true);

///@brief Get the appropriate text
XDATA_EXPORT QString GetTr(const char* str);

///@brief Ask whether project is dirty.
XDATA_EXPORT bool IsProjectDirty();

///@brief	API to get and set project;
XDATA_EXPORT CXProject* GetProject();
XDATA_EXPORT void SetProject(CXProject *);

XDATA_EXPORT QString GetProjectPath();

///@brief	API to get and set console;
XDATA_EXPORT CXConsole* GetConsole();
XDATA_EXPORT void SetConsole(CXConsole *);

///@brief Get the icon path.
XDATA_EXPORT QString GetIconPath();

XDATA_EXPORT std::string GetOSGFontPath(const QString& fontName);

///@biref Get the unique guid
 XDATA_EXPORT QUuid GetUniqueGuid();

 ///@brief Get the random object color
 XDATA_EXPORT QColor GetRandomColor(bool bDark = false);

 ///@brief Get the kelly colors
 XDATA_EXPORT QColor GetCurveColor(int index);

 ///@brief Invalid object ID
 extern XDATA_EXPORT QUuid g_InvalidObjectID; 

 ///@brief Invalid template ID
 extern XDATA_EXPORT unsigned int g_InvalidTemplateID;

 ///@brief a Map from object ID to the object
 extern XDATA_EXPORT QMap<QUuid, CXObject*> g_mapIDToObject;

 ///@brief Get the object from the object ID
 XDATA_EXPORT CXObject* GetObjectByID(const QUuid& uuid);

 ///@brief Add the object event
 XDATA_EXPORT void AddObjectEvent(CXObject* pParentObj, bool bUpdateImmediately=true);
 ///@brief Del the object event
 XDATA_EXPORT void DelObjectEvent(CXObject* pParentObj, bool bUpdateImmediately = true);

 ///@brief	Get the well folder instance (create one if not exist.)
 XDATA_EXPORT CXObject* GetRootObjectFolder(EXObjectType eObjType, bool bCreate = true);

 ///@brief	Get the well folder instance (not create one .)
 XDATA_EXPORT CXObject* GetRootObjectFolderOnly(EXObjectType eObjType);

 ///@brief Get a global generator of the random value
 XDATA_EXPORT CXRandomGenerator* GetRandomGenerator();

 ///@brief Get min and max values by the percentiles
 XDATA_EXPORT bool GetObjectMinMaxByPercentile(double& dMin, double& dMax, double dMinPercent, double dMaxPercent, CXObject * pObject);
 XDATA_EXPORT bool GetObjectMinMaxByPercentile(double& dMin, double& dMax, double dMinPercent, double dMaxPercent, const CXHistogram& histogram);

 ///@brief Get percentile by min and max values
 XDATA_EXPORT bool GetPercentileByMinMax(double& dMinPercent, double& dMaxPercent, double dMin, double dMax, CXObject * pObject);

 ///@brief Get current attribute object from the geometry object
 XDATA_EXPORT bool IsSeismic(CXObject* pGeoObj);
 XDATA_EXPORT CXObject* GetAttributeFromGeometry(CXObject* pGeoObj, CXWindow* pWindow);

 ///@brief Get the current selected object
 XDATA_EXPORT CXObject* GetCurrentObject();

 ///@brief Get epsilon of invalid data for data comparison
 template<typename T>
 T GetEPSofInvalidData(T InvalidData)
 {
	 T EPS = (qAbs(InvalidData) < M_FEPS) ? M_FEPS : qAbs(InvalidData)*M_FEPS;
	 return EPS;
 }

 XDATA_EXPORT QString vtos(double dValue,int nDecimal = -1,int *pReallyDecimal = NULL);
 XDATA_EXPORT QString vtos(float  fValue,int nDecimal = -1,int *pReallyDecimal = NULL );

 XDATA_EXPORT int GetSeisUnitDecimalNumber(double dInterval);

 XDATA_EXPORT bool IsDivideExactly(double dEnum, double dDenomi);

 XDATA_EXPORT bool isPointOnLine(double x, double y, double x1, double y1, double x2, double y2, double tolerance = 0.0001);

 XDATA_EXPORT bool isPointInPolygon(double x, double y, double* polygonX,double* polygonY,int nPoint,double tolerance = 1e-3);

#endif // RLGLOBAL_H
