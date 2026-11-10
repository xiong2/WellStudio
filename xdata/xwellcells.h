#ifndef _CXWellCELLS_H__
#define _CXWellCELLS_H__

#include "xdata_global.h"
#include "xobject.h"

class CXWell;
class CXGridModel;

///@brief	The class used to holds a list of reservoir cells a well pass through.
///@author	Xiong Xiong
///@date	Dec, 2014
///@see		Reservoir.uml
class XDATA_EXPORT CXWellCells: public CXObject
{
public:
	CXWellCells();
	CXWellCells(CXWell *);
	~CXWellCells();

	///@brief Serialization using the binary data array
	virtual bool SerializeData(CXArchive& ar);

	QList<unsigned int>& GetCellList()
	{
		return m_listCellIDX;
	}

	QList<double>& GetMDList()
	{
		return m_listCellMD;
	}

	QUuid GetWellID()
	{
		return m_wellID;
	}

	///	Calculate the cells a well pass through a grid model.
	static CXWellCells* CreateWellCells(CXGridModel *pModel, CXWell *pWell);

protected:
	virtual void _SetSelfDimension();

protected:
	QUuid					m_wellID;
	QList<unsigned int>		m_listCellIDX;		//	It's the list of cells the well pass through.
	QList<double>			m_listCellMD;		//	It's the list of the MD the well pass in and out each cell.
};

#endif