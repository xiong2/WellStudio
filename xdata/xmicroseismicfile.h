#ifndef XMICROSEISMICFILE_H__
#define XMICROSEISMICFILE_H__

#include "xdata_global.h"
#include "xasciifile.h"

///@brief	Used to represent an ASCII micro seismic file being imported.
///@author	Xiong Xiong
///@date	Aug, 2014
///@see		
class XDATA_EXPORT CXMicroSeismicFile: public CXASCIIFile
{
public:
	CXMicroSeismicFile(QString sFile): CXASCIIFile(eMicroSeismicASCII, sFile)
	{
	}

	///@brief	Let derived classes to check the selected columns.
	virtual bool CheckSelectedColumns(QStringList&);

	virtual bool Import();
};

#endif