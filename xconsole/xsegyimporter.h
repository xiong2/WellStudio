#ifndef _CXSEGYImporter_H__
#define _CXSEGYImporter_H__

#include "xconsole_global.h"
#include <QList>

class CXSEGYLoadParameters;

///@brief	Used to offer a SEGY file importer API.
///@author	Xiong Xiong
///@date	Apr, 2014
///@see		
class XCONSOLE_EXPORT CXSEGYImporter
{
public:
	static bool ImportSEGY(CXSEGYLoadParameters *);

	static void Import2DSEGY(QList<CXSEGYLoadParameters*> listPara, const QString& strSurveyName);
};

#endif