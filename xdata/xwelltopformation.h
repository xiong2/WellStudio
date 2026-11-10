#ifndef XWELLTOPFORMATION_H
#define XWELLTOPFORMATION_H

#include "xdata_global.h"
#include "xobject.h"

class CX3DPoints;

///@brief	The class provides data structure for well top formation
///@author	Yong Shu
///@date	Jun. 11th, 2014
///@see	

class XDATA_EXPORT CXWellTopFormation : public CXObject
{
public:
	CXWellTopFormation(const QString& strName = QString());
	~CXWellTopFormation();

	virtual QString GetTypeString() { return "Well Tops Formation"; }

	///@brief Get points from the formation
	CX3DPoints* GetAllPoints();

	///@brief Get the formation depth on a specified well
	double GetDepthOnWell(QString sWellName);

protected:
	virtual void _SetSelfDimension();

};

#endif // RLWELLTOPFORMATION_H
