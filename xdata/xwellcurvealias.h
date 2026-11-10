#ifndef _CXWellCURVEALIAS_H__
#define _CXWellCURVEALIAD_H__

#include <qlist.h>
#include "xdata_global.h"
#include "xobject.h"

///@brief	The class to represent a well curve alias.
///@author	Xiong Xiong
///@date	May, 2014
///@see		

class XDATA_EXPORT CXWellCurveAlias: public CXObject
{
public:
	CXWellCurveAlias(QString sName = "");

	virtual QString GetTypeString() { return "Well Curve Alias"; }

	///@brief	Get the list of associated logs.
	void GetAssociatedCurves(QList<CXObject *>& listCurves);

	///@brief	Get the alias by name (create if not exist.)
	static CXObject* GetAlias(QString sAliasName);

	///@brief Overwrite basic function, to return template icon.
	virtual QString GetIconName() const;

protected:
	virtual void _SetSelfDimension();
};

#endif