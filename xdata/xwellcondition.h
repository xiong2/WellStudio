#ifndef _CXWellCONDITION_H__
#define _CXWellCONDITION_H__

#include "xdata_global.h"
#include "xobject.h"

class CXWell;

///@brief	The class used to represent a well condition data of a reservoir model.
///@author	Xiong Xiong
///@date	Dec, 2014
///@see		Reservoir.uml
class XDATA_EXPORT CXWellCondition: public CXObject
{
public:
	CXWellCondition();
	CXWellCondition(QList<CXWell *>);
	~CXWellCondition();

	/// Retun the list of wells have already been calculated.
	QList<CXWell *> GetCalculatedWells();

	///	Calculate cells along one well, if the well calculated before, re-calculate it!
	void CalculateOneWell(CXWell *);

};

#endif