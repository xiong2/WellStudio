#ifndef _CX2DSurvey_H__
#define _CX2DSurvey_H__

#include "xdata_global.h"
#include "xobject.h"
#include "xdef.h"

///@brief	The class provides data structure for 2-D survey
///@author	Xiong Xiong
///@date	Sep, 2015
class XDATA_EXPORT CX2DSurvey : public CXObject
{
public:
	CX2DSurvey() {}
	CX2DSurvey(const QString& strName);

	virtual QString GetTypeString() { return "2D Seismic Survey"; }
	virtual bool IsFolder() { return true; }
	virtual QStringList GetDescription();

	QList<CXObject*> FetchAllSections();
};

#endif