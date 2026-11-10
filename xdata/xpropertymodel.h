#ifndef _CXPropertyModel_H__
#define _CXPropertyModel_H__

#include "xdata_global.h"
#include "xobject.h"
#include <QString>

class CXGridModel;

///@brief	The class used to represent a 3D property model.
///@author	Xiong Xiong
///@date	Nov, 2014
///@see		Reservoir.uml
class XDATA_EXPORT CXPropertyModel: public CXObject
{
public:
	CXPropertyModel();
	CXPropertyModel(QString strName);
	~CXPropertyModel();

	///	Reset data, so far only used by importing procedure.
	void ResetData(unsigned int iNum, double *pData);

	///	Get the associated geometry model.
	CXGridModel* GetGridModel();

	///@brief Set the get dimension info	
	virtual bool GetDimension(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);

	virtual QStringList GetDescription();

	///@brief Get geometry object
	virtual CXObject* GetGeometryObject();

protected:
	virtual float* _GetHistogramData(int& nDataNum, bool& bDeleted);

};

#endif