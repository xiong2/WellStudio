#ifndef _CX2DPOLYGON_H__
#define _CX2DPOLYGON_H__

#include "xdata_global.h"
#include "xobject.h"

///@brief	The class used to represent a 2D polygon
///@author	Xiong Xiong
///@date	Apr, 2014
///@see		
class XDATA_EXPORT CX2DPolygon: public CXObject
{
public:
	CX2DPolygon();
	CX2DPolygon(QString strName, EXObjectType eType);
		
	//	Populate the data.
	void ResetData(double* pData, unsigned int iNumber);
	void ResetData(unsigned int index,double xValue,double yValue);
	virtual QStringList GetDescription();
	virtual QString GetTypeString();

protected:
	virtual void _SetSelfDimension();
};

#endif