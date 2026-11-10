#pragma once
#include "xdataplus_global.h"
#include "xasciifile.h"

class XDATAPLUS_EXPORT CXFracturePatchFile : public CXASCIIFile
{
public:
	CXFracturePatchFile(QString sFile);
	virtual bool Import();

private:
	void sortPoints(double *);
};