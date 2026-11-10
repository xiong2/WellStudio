#ifndef _CXLICENSEMANAGER_H__
#define _CXLICENSEMANAGER_H__

#include "xconsole_global.h"

///@brief	It's a simple license manager of RockLog.
///@author	Xiong Xiong
///@date	Oct, 2013
///@see		
class XCONSOLE_EXPORT CXLicenseManager
{
public:
	static bool CheckLicense();

private:
	static QString getKeyFromHAddress(QString strHAdd);
};

#endif