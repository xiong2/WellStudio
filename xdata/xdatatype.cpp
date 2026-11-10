#include "xdatatype.h"

QStringList CXDataType::GetAllDataTypeNames()
{
	QStringList sListDataTypes;
	sListDataTypes<<"Integer"<<"Double"<<"Unsigned char"<<"Bool"<<"String";
	return sListDataTypes;
}

QString CXDataType::GetDataTypeName(EXDataType eType)
{
	QString sDataType = "";
	if(eType == eInt)
		sDataType = "Integer";
	else if(eType == eDouble)
		sDataType = "Double";
	else if(eType == eString)
		sDataType = "String";
	else if(eType == eUnsignedChar)
		sDataType = "Unsigned char";
	else if(eType == eBool)
		sDataType = "Bool";

	return sDataType;
}

EXDataType CXDataType::GetDataType(QString sDataType)
{
	if(sDataType.contains("int", Qt::CaseInsensitive))
		return eInt;
	else if(sDataType.contains("double", Qt::CaseInsensitive)
		|| sDataType.contains("real", Qt::CaseInsensitive)
		|| sDataType.contains("float", Qt::CaseInsensitive))
		return eDouble;
	else if(sDataType.contains("string", Qt::CaseInsensitive))
		return eString;
	else if(sDataType.contains("unsigned char", Qt::CaseInsensitive))
		return eUnsignedChar;
	else if(sDataType.contains("bool", Qt::CaseInsensitive))
		return eBool;
	else
		return eNone;
}