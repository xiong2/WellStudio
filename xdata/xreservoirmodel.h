#ifndef _CXReservoirModel_H__
#define _CXReservoirModel_H__

#include "xdata_global.h"
#include "xobject.h"

class CXGridModel;
class CXPropertyModel;

///@brief	The class used to represent a reservoir model.
///@author	Xiong Xiong
///@date	Nov, 2014
///@see		Reservoir.uml
class XDATA_EXPORT CXReservoirModel: public CXObject
{
public:
	CXReservoirModel()
	{
	}

	CXReservoirModel(CXGridModel *pGridModel, QString sName = "");

	CXGridModel* GetGridModel();

	virtual QStringList GetDescription();
	virtual QString GetTypeString() { return "Reservoir Grid"; }

	///@brief Get geometry object
	virtual CXObject* GetGeometryObject();
};


#endif