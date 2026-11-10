#ifndef XWELLCURVECELLS_H
#define XWELLCURVECELLS_H

#include "xdata_global.h"
#include "xobject.h"

class CXWellCurve;
class CXWellCells;

//!@brief	The class used to holds a list of reservoir cells a well curve pass through.
//!@author	Pezy
//!@date	Feb, 9th, 2015
//!@see		Reservoir.uml

class XDATA_EXPORT CXWellCurveCells : public CXObject
{
public:
	CXWellCurveCells() {}
	CXWellCurveCells(CXWellCells *, CXWellCurve *);
	~CXWellCurveCells() {}

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	QList<double> &GetValueList() 
	{ 
		return m_listValues;
	}

	const QUuid &GetWellCurveId()
	{
		return m_curveID;
	}

	const QUuid &GetWellID()
	{
		return m_wellID;
	}

	///	Calculate the each cell's value when a well curve pass through a grid model.
	static CXWellCurveCells* CreateWellCurveCells(CXWellCells *pWellCells, CXWellCurve *pWellCurve);

private:
	QUuid m_curveID;
	QUuid m_wellID;
	QList<double> m_listValues;
};

#endif // RLWELLCURVECELLS_H
