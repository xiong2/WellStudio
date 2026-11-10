#include "xgeneralfolder.h"
#include "xobjectfactory.h"
#include "xglobal.h"
#include <QObject>

BEGIN_REGISTER_OBJECT_TO_FACTORY(CXGeneralFolder)
EXWellFolder,
EXWellCurveAliasFolder,
EXFaultFolder,
EXFaultPolygonFolder,
EXPointsFolder,
EXSurfaceFolder,
EXHorizonFolder,
EXGMFaultFolder,
EXWaveletFolder,
EXSeismicDVFolder,
EXSeismicGatherFolder,
EXSeismicDataLineFolder,
EXSeismicSectionFolder,
EXGeobodyFolder,
EXLFMFolder,
EXLFMUpscalingResultFolder,
EXLFMAttributeFolder,
EXPolygonFolder,
EX3TermAVOInversionFolder,
EXNMRFolder,
EXFractureAnalysisAVO,
EXHorizonAttributeFolder,
EXFractureInversionFolder,
EXAnisotropyForwardingFolder,
EXGSFolder,
EXGSFolderHorizon,
EXGSFolderSection,
EXGSFolderPDG,
EXFracturePatchFolder,
EXGSFolderStage
END_REGISTER_OBJECT_TO_FACTORY(CXGeneralFolder)

CXGeneralFolder::CXGeneralFolder(const QString& strName)
	:CXObject(strName)
{	
}

CXGeneralFolder::CXGeneralFolder(const QString& strName, EXObjectType eObjType, const QString& strIconName)
	: CXObject(strName)
{
	SetObjectType(eObjType);
	SetIconName(strIconName);
}


CXGeneralFolder::~CXGeneralFolder()
{
}
QString CXGeneralFolder::GetTypeString() 
{ 
	EXObjectType eType = GetObjectType();
	
	if (eType == EXWellFolder)
		return "Well Folder";
	else if (eType == EXWellCurveAliasFolder)
		return "Well Curve Aliases";
	else if (eType == EXFaultFolder)
		return "Fault Folder";
	else if (eType == EXFaultPolygonFolder)
		return "Fault Polygon Folder";
	else if (eType == EXPointsFolder)
		return "Points Folder";
	else if (eType == EXSurfaceFolder)
		return "Surface Folder";
	else if (eType == EXHorizonFolder)
		return "Horizon Folder";
	else if (eType == EXGMFaultFolder)
		return "Folder";
	else if (eType == EXWaveletFolder)
		return "Wavelet Folder";
	else if (eType == EXFracturePatchFolder)
		return "Fracture patches Folder";
	else if (eType == EXSeismicDVFolder)
		return "Seismic Data Volumes";
	else if (eType == EXSeismicSectionFolder)
		return "Seismic Sections";
	else if (eType == EXGeobodyFolder)
		return "Geobodies";
	else if (eType == EXSeismicGatherFolder)
		return "Seismic Gathers";
	else
		return "Folder";
}

QStringList CXGeneralFolder::GetDescription()
{
	QStringList strListDesc;

	if(GetObjectType() == EXWellFolder)
	{
		QList<CXObject *> listChild = GetChildren(EXWell);
		strListDesc << QObject::tr("Contains wells") << QString::number(listChild.size());
	}
	else
	{
		QList<CXObject *> listChild = this->GetChildrenList();
		strListDesc << QObject::tr("Contains objects") << QString::number(listChild.size());
	}

	return strListDesc;
}