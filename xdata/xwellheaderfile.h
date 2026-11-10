#ifndef XWELLHEADERFILE_H__
#define XWELLHEADERFILE_H__

#include "xdata_global.h"
#include "xasciifile.h"

///@brief	Used to represent an ASCII well header file being imported.
///@author	Xiong Xiong
///@date	Mar, 2014
///@see		
class XDATA_EXPORT CXWellHeaderFile: public CXASCIIFile
{
public:
	CXWellHeaderFile(QString sFile): CXASCIIFile(eWellHeaderASCII, sFile)
	{
	}

	virtual bool Import();

	///@brief	Let derived classes to check the selected columns.
	virtual bool CheckSelectedColumns(QStringList&);
};

#endif