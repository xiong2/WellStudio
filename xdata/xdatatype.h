#ifndef _CXDATATYPE_H__
#define _CXDATATYPE_H__

#include <QStringList>
#include "xdata_global.h"

enum EXDataType
{
	eNone			= 0,
	eInt			= 1,
	eDouble			= 2,
	eUnsignedChar	= 3,
	eBool			= 4,
	eString			= 5,
};

///@brief	Used to represent data types used in RockLog.
///@author	Xiong Xiong
///@date	Sep, 2013

class XDATA_EXPORT CXDataType
{
public:
	static QStringList GetAllDataTypeNames();
	static QString GetDataTypeName(EXDataType eType);
	static EXDataType GetDataType(QString strDataType);
};

#endif