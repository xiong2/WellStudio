#ifndef _CX3DPoints_H__
#define _CX3DPoints_H__

#include "xdata_global.h"
#include "xobject.h"

///@brief	The class used to represent a 3D points set.
///@author	Xiong Xiong
///@date	Mar, 2014
///@see		
class XDATA_EXPORT CX3DPoints: public CXObject
{
public:
	CX3DPoints(QString strName = "");

	//	Populate the data.
	void ResetData(double* pData, unsigned int iNumber);

	virtual QString GetTypeString() { return "Points"; }

	virtual QStringList GetDescription();

protected:
	virtual void _SetSelfDimension();
};


#endif