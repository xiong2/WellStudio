#ifndef _CXPointsFile_H__
#define _CXPointsFile_H__

#include "xdata_global.h"
#include "xasciifile.h"

///@brief	Used to represent an ASCII points file being imported.
///@author	Xiong Xiong
///@date	Apr, 2014
///@see		
class XDATA_EXPORT CXPointsFile: public CXASCIIFile
{
public:
	CXPointsFile(QString sFile): CXASCIIFile(e3DPointsASCII, sFile)
	{
	}

	virtual bool Import();
};


#endif