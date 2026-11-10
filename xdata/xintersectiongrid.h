#ifndef XINTERSECTIONGRID_H
#define XINTERSECTIONGRID_H

#include "xdata_global.h"
#include "xgridmodel.h"

//! @class	CXIntersectionGrid in the file "rlintersectiongrid.h"
//! @brief	completed grid + intersected grid
//! 
//! @author	Pezy
//! @date	2015-3-25
//! @see	CXPropertyModel in the file "rlpropertymodel.h"

class CXIntersectedGridCell;

class XDATA_EXPORT CXIntersectionGrid : public CXGridModel
{
public:
	CXIntersectionGrid();
	CXIntersectionGrid(unsigned uI, unsigned uJ, unsigned uK, unsigned uSegment = 1u);
	
	virtual ~CXIntersectionGrid();
	virtual QStringList GetDescription() override;
	
	QList<CXIntersectedGridCell*>& GetIntersectedCells();

protected:
	virtual void _WriteData() override;
	virtual void _ReadData() override;

	QList<CXIntersectedGridCell*> m_listIntersectedCells;

private:
    void _FreeMemory();
	void _ClearIntersectedList();
	void _ClearCompleteList();
};

#endif // RLINTERSECTIONGRID_H
