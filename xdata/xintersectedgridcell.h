#ifndef XINTERSECTEDGRIDCELL_H
#define XINTERSECTEDGRIDCELL_H

#include "xdata_global.h"

#include <vector>
using std::vector;

//! @class	CXIntersectedGridCell in the file "rlintersectedgridcell.h"
//! @brief	Intersected cells may have many of faces, and each face may have uncertain vertex numbers.
//! 
//! @author	Pezy
//! @date	2015-3-25
//! @see	CXGridCell in the file "rlgridcell.h"

class XDATA_EXPORT CXIntersectedGridCell
{
public:
	CXIntersectedGridCell(unsigned short usI, unsigned short usJ, unsigned short usK, unsigned char ucSegIndex = 0);
	~CXIntersectedGridCell() {}

	double*						GetVertex()			{ return m_pVertex; }
	int&						GetVertexNum()		{ return m_nNum; }
	vector<vector<unsigned> >&	GetFace()			{ return m_vecFaceIndices; }
	vector<unsigned>&			GetBorderIndices()	{ return m_vecBorderIndices; }
	void						GetIJK(unsigned short &i, unsigned short &j, unsigned short &k) { i = m_usI; j = m_usJ; k = m_usK; }
	void						GetBoundingBox(double &dXMin, double &dXMax, double &dYMin, double &dYMax, double &dZMin, double &dZMax) const;
	unsigned char				GetSegmentIndex()	{ return m_ucSegmentIndex; }

protected:
	double						m_pVertex[30];

	int							m_nNum;

	vector<vector<unsigned> >	m_vecFaceIndices;
	vector<unsigned>			m_vecBorderIndices;

	unsigned char				m_ucSegmentIndex;		//	Index of the segment this cell belongs to.
	unsigned short				m_usI;
	unsigned short				m_usJ;
	unsigned short				m_usK;
};

#endif // RLINTERSECTEDGRIDCELL_H
