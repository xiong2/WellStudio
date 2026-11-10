#include "x2dsurvey.h"
#include "xobjectfactory.h"

BEGIN_REGISTER_OBJECT_TO_FACTORY(CX2DSurvey)
EX2DSurvey
END_REGISTER_OBJECT_TO_FACTORY(CX2DSurvey)

CX2DSurvey::CX2DSurvey(const QString& strName): CXObject(strName)
{
	SetIconName("2DSurvey.png");
	SetObjectType(EX2DSurvey);
}

QStringList CX2DSurvey::GetDescription()
{
	QStringList strList;

	return strList;
}

QList<CXObject*> CX2DSurvey::FetchAllSections()
{
	return GetChildren(EXSeismicDataLine);
}