#ifndef _CXWellTD_H__
#define _CXWellTD_H__

#include "xdata_global.h"
#include "xobject.h"
#include "xglobal.h"
#include <QVector3D>
#include <vector>
#include <QMutex>

///@brief	The class used to represent a well's T-D data.
///@author	Xiong
///@date	Jan, 2021
///@see		
class CXWell;
class XDATA_EXPORT CXWellTD: public CXObject
{
public:
	CXWellTD();
	~CXWellTD();
	
	///	Populate the data. Depth array (z) followed by TWT array.
	void ResetData(double* pData, unsigned int iNumber);

	double GetAValue(double dIVal, bool bFromZToT = true);
};

#endif
