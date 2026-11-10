#ifndef XGENERALFOLDER_H
#define XGENERALFOLDER_H

#include "xobject.h"
#include "xdata_global.h"

class XDATA_EXPORT CXGeneralFolder : public CXObject
{
public:
	///@brief Constructor for serialization
	CXGeneralFolder(const QString& strName="");

	///@brief Constructor for create new folder
	CXGeneralFolder(const QString& strName, EXObjectType eObjType, const QString& strIconName);
		
	~CXGeneralFolder();

	virtual QStringList GetDescription();
	virtual QString GetTypeString();

	virtual bool IsFolder() {return true;}
};


#endif // RLGENERALFOLDER_H
