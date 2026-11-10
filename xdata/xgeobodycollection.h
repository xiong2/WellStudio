#ifndef CXGEOBODYCOLLECTION_H__
#define CXGEOBODYCOLLECTION_H__

#include <qbitarray.h>
#include "xdata_global.h"
#include "xobject.h"
#include "xseismicutmtool.h"

/**
*@brief		It represent a geobody collection, that collects all geobodies detected one time.
*@author	Xiong Xiong
*@date		Nov, 2015
*@see		See UML diagram "geobody.uml" to find the relationship with other classes.
*/
class XDATA_EXPORT CXGeobodyCollection : public CXObject
{
public:
	CXGeobodyCollection(QString sName = "");
	~CXGeobodyCollection();
	
	virtual QString GetTypeString() { return "Geobody Collection"; }
	virtual bool IsFolder() { return true; }
};

#endif