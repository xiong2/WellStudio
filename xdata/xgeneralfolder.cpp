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
EXCLineFolder,
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
		return u8"井文件夹";
	else if (eType == EXWellCurveAliasFolder)
		return u8"测井曲线别名";
	else if (eType == EXFaultFolder)
		return u8"断层文件夹";
	else if (eType == EXFaultPolygonFolder)
		return u8"断层多边形文件夹";
	else if (eType == EXPointsFolder)
		return u8"散点文件夹";
	else if (eType == EXSurfaceFolder)
		return u8"Surface Folder";
	else if (eType == EXHorizonFolder)
		return u8"层位文件夹";
	else if (eType == EXGMFaultFolder)
		return u8"应力断层文件夹";
	else if (eType == EXWaveletFolder)
		return u8"子波文件夹";
	else if (eType == EXFracturePatchFolder)
		return u8"裂缝片文件夹";
	else if (eType == EXCLineFolder)
		return u8"组合测线文件夹";
	else if (eType == EXSeismicDVFolder)
		return u8"地震数据体";
	else if (eType == EXSeismicSectionFolder)
		return u8"地震剖面";
	else if (eType == EXGeobodyFolder)
		return u8"地质体";
	else if (eType == EXSeismicGatherFolder)
		return u8"地震道集";
	else
		return u8"文件夹";
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