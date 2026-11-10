#ifndef _CXGridModel_H__
#define _CXGridModel_H__

#include "xdata_global.h"
#include "xobject.h"

class CXGridCell;

///@brief	The class used to represent a 3D grid model.
///@author	Xiong Xiong
///@date	Nov, 2014
///@see		Reservoir.uml
class XDATA_EXPORT CXGridModel: public CXObject
{
public:
	CXGridModel();
	CXGridModel(unsigned int nI, unsigned int nJ, unsigned int nK, unsigned int nSegment = 1);
	virtual ~CXGridModel();

	void GetIJKDimentionInfo(unsigned int& nI, unsigned int& nJ, unsigned int& nK)
	{
		nI = m_nI;
		nJ = m_nJ;
		nK = m_nK;
	}

	unsigned GetSegment() { return m_nSegment; }

	QList<CXGridCell *>& GetAllCells();

	unsigned int GetValidCellNumber();

	virtual QStringList GetDescription();
	virtual QString GetTypeString() { return "Geometry Grid"; }

	virtual bool SerializeData(CXArchive& ar);

	///	Directly set dimension info duing importing.
	void SetDimension(double dXMin, double dXMax, double dYMin, double dYMax, double dZMin, double dZMax);

protected:
	//	Dimension
	unsigned int	m_nI;
	unsigned int	m_nJ;
	unsigned int	m_nK;
	unsigned int	m_nValidCells;

	//	How many segments.
	unsigned char	m_nSegment;

	QList<CXGridCell *>	m_listCells;

	virtual void _WriteData();
	virtual void _ReadData();
	void _freeMemory();
};

#endif