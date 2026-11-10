#include "xglobal.h"

#include <qtextcodec.h>
#include <assert.h>

#include "xproject.h"
#include "xrandomgenerator.h"
#include <qdatetime.h>
#include "xwellcurve.h"
#include "xtree.h"
#include "xutility.h"
#include "xgeneralfolder.h"
#include "xmathmacro.h" 
#include "xbaseconsole.h"
#include "xviewinfoobject.h"
#include "xwelltops.h"
#include "xwellzones.h"

XDATA_EXPORT bool g_bShowTestAction= false;
XDATA_EXPORT CXProject* g_pProject	= NULL;
XDATA_EXPORT CXConsole* g_pConsole	= NULL;
XDATA_EXPORT bool g_bDirtyProject		= false;

XDATA_EXPORT float g_f3DZFactor = -1.f;

static CXRandomGenerator g_RandomGenerator(true, QDateTime::currentDateTime().toTime_t());

void SetProject(CXProject *pProject)
{
	g_pProject = pProject;
}

QString GetTr(const char* str)
{
    return QString::fromUtf8(str);
}

CXProject* GetProject()
{
	return g_pProject;
}

QString GetProjectPath()
{
	return g_pProject->GetProjectDataPath();
}

void SetProjectDirty(bool bDirty)
{
	g_bDirtyProject = bDirty;
}

bool IsProjectDirty()
{
	return g_bDirtyProject;
}

bool UsingMetricUnit()
{
	if(g_pProject)
		return g_pProject->UsingMetricUnit();
	else
		return true;
}

bool UsingChinese()
{
	/*QString sLang(getenv("RLLANGUAGE"));
	return sLang != "ENG";*/
	return false;
}

void SetConsole(CXConsole *pConsole)
{
	g_pConsole = pConsole;
}

CXConsole* GetConsole()
{
	return g_pConsole;
}

QString GetIconPath()
{
	return ":/Icon/";
}

std::string GetOSGFontPath(const QString& fontName)
{
	return "fonts/" + fontName.toStdString() + ".ttf";
}

CXDBIO* GetDBIO()
{
	return GetProject()->GetDBIO();
}


QUuid GetUniqueGuid()
{
	static QMutex mutex;

	QMutexLocker locker(&mutex);

	return QUuid::createUuid();
}

QColor GetRandomColor(bool bDark)
{
	int base = bDark ? 128 : 255;

	int red = static_cast<int>(base*GetRandomGenerator()->GetValue());
	int green = static_cast<int>(base * GetRandomGenerator()->GetValue());
	int blue = static_cast<int>(base* GetRandomGenerator()->GetValue());

	return QColor(red, green, blue);
}

XDATA_EXPORT QColor GetCurveColor(int index)
{
	index %= 19;

	return QList<QColor>
	{
		QColor("pink"),
		QColor("olive"),
		QColor("magenta"),
		QColor("crimson"),
		QColor("gold"),
		QColor("teal"),
		QColor("saddlebrown"),
		QColor("rosybrown"),
		QColor("darkblue"),
		QColor("mediumslateblue"),
		QColor("darkturquoise"),
		QColor("darkslategray"),
		QColor("darkkhaki"),
		QColor("mediumvioletred"),
		QColor("green"),
		QColor("darkorchid"),
		QColor("tomato"),
		QColor("purple"),
		QColor("cyan"),
		QColor("dodgerblue")
	}.at(index);
}

XDATA_EXPORT QUuid g_InvalidObjectID = QUuid();

XDATA_EXPORT unsigned int g_InvalidTemplateID = 0;

XDATA_EXPORT double g_dInvalidData = M_FINVALID;

XDATA_EXPORT QString g_strProductName = "XStudio";

XDATA_EXPORT QMap<QUuid, CXObject*> g_mapIDToObject;

CXObject* GetObjectByID(const QUuid& uuid)
{
	return g_mapIDToObject.value(uuid, NULL);
}

void AddObjectEvent(CXObject* pParentObj, bool bUpdateImmediately )
{
	pParentObj->AddEvent(EAdded);
	QList<CXObject*> listChild = pParentObj->GetChildrenList();
	for (int i = 0; i < listChild.size(); ++i)
	{
		CXObject* pObj = listChild.at(i);
		if (!pObj || !pObj->GetNodeFlag())
			continue;
		
		AddObjectEvent(pObj,false);
	}
	if (bUpdateImmediately)
	{
		CXProcessEvent eventProcess;
	}
}

void DelObjectEvent(CXObject* pParentObj, bool bUpdateImmediately )
{
	QList<CXObject*> listChild = pParentObj->GetChildrenList();
	for (int i = 0; i < listChild.size(); ++i)
	{
		CXObject* pObj = listChild.at(i);
		DelObjectEvent(pObj,false);
	}
	pParentObj->AddEvent(EDeleted);
	if (bUpdateImmediately)
	{
		CXProcessEvent eventProcess;
	}
}
CXRandomGenerator* GetRandomGenerator()
{
	return &g_RandomGenerator;
}


XDATA_EXPORT bool GetObjectMinMaxByPercentile(double& dMin, double& dMax, double dMinPercent, double dMaxPercent, CXObject * pObject)
{
	if (!pObject)
		return false;

	if (!pObject->HasHistogram())
		return false;

	return GetObjectMinMaxByPercentile(dMin, dMax, dMinPercent, dMaxPercent, pObject->GetHistogram());
}

XDATA_EXPORT bool GetObjectMinMaxByPercentile(double & dMin, double & dMax, double dMinPercent, double dMaxPercent, const CXHistogram & histogram)
{
	std::vector<double> vecData = histogram.m_vecHorizontal;
	std::vector<double> vecFrequency = histogram.m_vecVertical;
	
	if (vecData.empty() || vecFrequency.empty())
		return false;

	// prob distribution
	std::vector<double> vecSum(256);
	for (int i = 0; i < 256; ++i)
	{
		if (i == 0)
			vecSum[0] = vecFrequency[0] * 100;
		else
			vecSum[i] = vecFrequency[i] * 100 + vecSum[i - 1];
	}

	// bound
	dMinPercent = qBound(0., dMinPercent, vecSum[255]);
	dMaxPercent = qBound(0., dMaxPercent, vecSum[255]);

	// min and max
	int iMin = -1;
	int iMax = -1;

	for (int i = 0; i < 256; ++i)
	{
		if (iMin < 0 && dMinPercent <= vecSum[i])
		{
			iMin = i;
		}
		if (iMax < 0 && dMaxPercent <= vecSum[i])
		{
			iMax = i;
		}
		if (iMin >= 0 && iMax >= 0)
			break;
	}

	// min
	double dMaxSum = vecSum[iMin];
	double dMinSum = (iMin == 0 ? 0. : vecSum[iMin - 1]);
	double dMinData = vecData[iMin];
	double dMaxData = vecData[iMin] + vecData[1] - vecData[0];
	dMin = dMinData + (dMaxData - dMinData) / (dMaxSum - dMinSum)*(dMinPercent - dMinSum);

	// max
	dMaxSum = vecSum[iMax];
	dMinSum = (iMax == 0 ? 0. : vecSum[iMax - 1]);
	dMinData = vecData[iMax];
	dMaxData = vecData[iMax] + vecData[1] - vecData[0];
	dMax = dMinData + (dMaxData - dMinData) / (dMaxSum - dMinSum)*(dMaxPercent - dMinSum);

	return true;
}

XDATA_EXPORT bool GetPercentileByMinMax(double& dMinPercent, double& dMaxPercent, double dMin, double dMax, CXObject * pObject)
{	
	if (!pObject)
		return false;

	if (!pObject->HasHistogram())
		return false;

	std::vector<double> vecData, vecFrequency;
	pObject->GetHistogram(vecData, vecFrequency);
	if (vecData.empty() || vecFrequency.empty())
		return false;

	double dDataMin, dDataMax;
	pObject->GetDataRange(dDataMin, dDataMax);
	dMin = qBound(dDataMin, dMin, dDataMax);
	dMax = qBound(dDataMin, dMax, dDataMax);

	// same values
	if (dMin == dMax)
	{
		dMinPercent = 0;
		dMaxPercent = 0;
		return true;
	}

	// prob distribution
	std::vector<double> vecSum(256);
	for (int i = 0; i < 256; ++i)
	{
		if (i == 0)
			vecSum[0] = vecFrequency[0] * 100;
		else
			vecSum[i] = vecFrequency[i] * 100 + vecSum[i - 1];
	}

	int iMin = static_cast<int>((dMin - dDataMin) / (vecData[1] - vecData[0]));
	int iMax = static_cast<int>((dMax - dDataMin) / (vecData[1] - vecData[0]));

	// min
	double dMaxSum = vecSum[iMin];
	double dMinSum = (iMin == 0 ? 0. : vecSum[iMin - 1]);
	double dMinData = vecData[iMin];
	double dMaxData = vecData[iMin] + vecData[1] - vecData[0];
	dMinPercent = dMinSum + (dMaxSum - dMinSum) / (dMaxData - dMinData)*(dMin - dMinData);

	// max
	dMaxSum = vecSum[iMax];
	dMinSum = (iMax == 0 ? 0. : vecSum[iMax - 1]);
	dMinData = vecData[iMax];
	dMaxData = vecData[iMax] + vecData[1] - vecData[0];
	dMaxPercent = dMinSum + (dMaxSum - dMinSum) / (dMaxData - dMinData)*(dMax - dMinData);

	return true;
}

XDATA_EXPORT CXObject* GetRootObjectFolder(EXObjectType eObjType, bool bCreate)
{
	if (!::GetProject())
	{
		return NULL;
	}
	CXGeneralFolder *pRootObjFolder = NULL;
	QList<CXObject *> listObjects = ::GetProject()->GetChildren(eObjType, true);

	if (!bCreate && listObjects.size() == 0)
	{
		return NULL;
	}

	if(listObjects.size() == 0)
	{
		if(eObjType == EXWellCurveAliasFolder)
		{
			//	For log alias folder, find the well folder first.
			CXObject *pWellFolder = ::GetRootObjectFolder(EXWellFolder);
			return pWellFolder->GetChild("Log Alias", EXWellCurveAliasFolder);
		}
		else if (eObjType == EXWellTops)
		{
			CXWellTops* pWellTops = new CXWellTops();
			::GetProject()->AddChild(pWellTops);
			::AddObjectEvent(pWellTops);
			return pWellTops;
		}
		else if (eObjType == EXWellZones)
		{
			CXWellZones* pWellTops = new CXWellZones();
			::GetProject()->AddChild(pWellTops);
			::AddObjectEvent(pWellTops);
			return pWellTops;
		}

		QString strObjName, strIconName;
		switch(eObjType)
		{
		case EXWellFolder:
			{
				strObjName = "Wells";
				strIconName = "Wells.png";
			}
			break;
		case EXPointsFolder:
			{
				strObjName = "Points";
				strIconName = "PointsFolder.png";
			}
			break;
		case EXFaultFolder:
		{
			strObjName = "Faults";
			strIconName = "FaultFolder.png";
		}
		break;
		case EXFaultPolygonFolder:
		{
			strObjName = "Fault Polygons";
			strIconName = "FaultPolygonFolder.png";
		}
		break;

		case EXSurfaceFolder:
		{
			strObjName = "3-D Surfaces";
			strIconName = "SurfaceFolder.png";
		}
		break;
		case EXHorizonFolder:
		{
			strObjName = "3-D Horizon";
			strIconName = "HorizonFolder.png";
		}
		break;
		case EXPolygonFolder:
			{
				strObjName= "Polygons";
				strIconName="PolygonFolder";
			}
			break;
		case EXWaveletFolder:
		{
			strObjName = "Wavelets";
			strIconName = "WaveletFolder.png";
		}
		break;
		case EXFracturePatchFolder:
		{
			strObjName = "FracturePatches";
			strIconName = "FracturePatchFolder.png";
		}
		break;
		case EXGeobodyFolder:
		{
			strObjName = "Geobodies";
			strIconName = "GeobodyFolder.png";
		}
		break;
		case EXLFMFolder:
		{
			strObjName = "Structure Models";
			strIconName = "Folder.png";
		}
		break;
		case EXSeismicGatherFolder:
		{
			strObjName = "Seismic Gathers";
			strIconName = "GatherFolder.png";
		}
		break;
		default:
			break;

		}

		pRootObjFolder = new CXGeneralFolder(strObjName, eObjType, strIconName);
		::GetProject()->AddChild(pRootObjFolder);	
		
		if(eObjType == EXWellFolder)
		{
			//	Find well folder first.
			CXGeneralFolder *pAliasFolder = new CXGeneralFolder("Log Alias" , EXWellCurveAliasFolder, "WellCurveAlias.png");
			pRootObjFolder->AddChild(pAliasFolder);
		}

		::AddObjectEvent(pRootObjFolder);
	}
	else
	{
		pRootObjFolder = (CXGeneralFolder *)(listObjects[0]);
	}

	return pRootObjFolder;
}


XDATA_EXPORT CXObject* GetRootObjectFolderOnly(EXObjectType eObjType)
{
	if (!::GetProject())
	{
		return NULL;
	}
	CXGeneralFolder *pRootObjFolder = NULL;
	QList<CXObject *> listObjects = ::GetProject()->GetChildren(eObjType, true);
	if (listObjects.size() == 0)
	{
		return NULL;
	}
	else
	{
		pRootObjFolder = (CXGeneralFolder *)(listObjects[0]);
	}

	return pRootObjFolder;
}
XDATA_EXPORT QString vtos(double dValue, int nDecimal,int *pReallyDecimal)
{
	if( nDecimal < 0 ) 
	{
		nDecimal = 0;
	}

	QString str;
	str.setNum( dValue , 'a' , nDecimal );

	if( nDecimal>0 && !str.isEmpty() )
	{
		int iPos(0);
		for( iPos = str.length()-1 ; iPos>=0 ; --iPos )
		{
			if( str[iPos] != '0' )
			{
				break;
			}

			--nDecimal;
		}
		if( str[iPos] =='.' ) --iPos;

		str.truncate( iPos +1 );
	}

	if( pReallyDecimal )
	{
		*pReallyDecimal = qMax(0,nDecimal );
	}

	return str;
}


XDATA_EXPORT QString vtos( float  fValue,int nDecimal,int *pReallyDecimal )
{	
	return vtos( (double)(fValue),nDecimal,pReallyDecimal );
}

XDATA_EXPORT int GetSeisUnitDecimalNumber(double dInterval)
{	
	dInterval = qAbs(dInterval);
	if(dInterval < M_FEPS)
		return 0;

	int nNum = 0;

	while(dInterval < 1.)
	{
		++nNum;
		dInterval *= 10.;
	}

	return nNum;
}
XDATA_EXPORT bool IsDivideExactly(double dEnum, double dDenomi)
{
	if(qAbs(dDenomi) < M_FEPS)
	{
		return false ;
	}

	double dValue = dEnum / dDenomi ;
	int nValue = (int) (dValue + 0.0001) ;
	if(qAbs(dValue - nValue) < 0.001)
	{
		return true ;
	}

	return false ;
}
XDATA_EXPORT bool isPointOnLine(double x, double y, double x1, double y1, double x2, double y2, double tolerance )
{
	double dt = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)) -
		sqrt((x1 - x )*(x1 - x ) + (y1 - y )*(y1 - y )) -
		sqrt((x2 - x )*(x2 - x ) + (y2 - y )*(y2 - y ));
	if (fabs(dt) < tolerance)
		return true;
	else
		return false;
}
XDATA_EXPORT bool isPointInPolygon(double x, double y, double* polygonX,double* polygonY,int nPoint,double tolerance)
{
	double xinters, x1, y1, x2, y2;
	int counter = 0, corner  = 0;
	if(nPoint <= 0) return false;
	x1 = polygonX[0];
	y1 = polygonY[0];		
	for (int i = 1; i <= nPoint; i++)
	{
		x2 = polygonX[i % nPoint];
		y2 = polygonY[i % nPoint];
		if (isPointOnLine(x, y, x1, y1, x2, y2, tolerance)) return true;
		if (fabs(y - y1) < tolerance && fabs(y - y2) < tolerance)
		{
			if (x < qMin(x1, x2))			
				counter++;			
			else if (x >= qMin(x1, x2) && x <= qMax(x1, x2))			
				return true;			
		}
		else if (fabs(y - y1) < tolerance && fabs(y - y2) > tolerance)
		{
			if (x <= x1)
			{
				counter++;
				corner++;
			}
		}
		else if (fabs( y - y1) > tolerance && fabs(y - y2) < tolerance)
		{
			if (x <= x2)
			{
				counter++;
				corner++;
			}
		}
		else if (y > qMin(y1, y2))
		{
			if (y <= qMax(y1, y2))
			{
				if (x <= qMax(x1, x2))
				{
					if (y1 != y2)
					{
						xinters = (y-y1)*(x2-x1)/(y2-y1)+x1;
						if (x1 == x2 || x <= xinters)
							counter++;
					}
				}
			}
		}
		x1 = x2;
		y1 = y2;
	}
	counter = counter - corner/2;
	if (counter % 2 == 0) return false;	
	return true;
}

bool IsSeismic(CXObject* pGeoObj)
{
	if (!pGeoObj) return false;

    std::vector<EXObjectType> vecSeismic{EXSeismicSection, EXRandomSection, EXSeismicSubVolume, EX2DSeismicLine, EXSeismicDataVolume, EXSeismicDataLine};

    return std::find(vecSeismic.cbegin(), vecSeismic.cend(), pGeoObj->GetObjectType()) != vecSeismic.cend();
}

CXObject* GetAttributeFromGeometry(CXObject* pGeoObj, CXWindow* pWindow)
{
	if (!pGeoObj)
	{
		return pGeoObj;
	}

	auto pConsole = reinterpret_cast<CXBaseConsole*>(g_pConsole);
	CXViewInfoObject* pGeoViewInfo = pConsole->GetViewInfoOfWindow(pGeoObj->GetObjectID(), pWindow);
	if (!pGeoViewInfo) return nullptr;

	QUuid uidAttribute = pGeoViewInfo->GetAttributeObjID();

	if (uidAttribute.isNull())
	{
		return pGeoObj;
	}
	else
	{
		return ::GetObjectByID(uidAttribute);
	}
}

CXObject* GetCurrentObject()
{
	return CXTree::Instance().GetCurrentSelectedObject(); 
}
