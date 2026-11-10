#ifndef _CXGridCell_H__
#define _CXGridCell_H__

#include "xdata_global.h"

class CXGridModel;

///@brief	The class used to represent one cell in a reservoir grid model.
///@author	Xiong Xiong
///@date	Nov, 2014
///@see		Reservoir.uml
class XDATA_EXPORT CXGridCell
{
friend CXGridModel;

public:
	CXGridCell(unsigned short iI, unsigned short iJ, unsigned short iK, unsigned char iSegIndex = 0);
	~CXGridCell();

	double*	GetVertex()
	{
		return m_pVertex;
	}

	void GetIJK(unsigned short& iI, unsigned short& iJ, unsigned short& iK)
	{
		iI = m_iI;
		iJ = m_iJ;
		iK = m_iK;
	}

	unsigned char GetSegment() { return m_iSegmentIndex; }

	//! @fn	void CXGridCell::GetBoundingBox(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);
	//!
	//! @brief	Gets bounding box.
	//!
	//! @author	Pezy
	//! @date	2014/12/22
	//!
	//! @param [in,out]	dXMin	The x coordinate minimum.
	//! @param [in,out]	dXMax	The x coordinate maximum.
	//! @param [in,out]	dYMin	The y coordinate minimum.
	//! @param [in,out]	dYMax	The y coordinate maximum.
	//! @param [in,out]	dZMin	The z coordinate minimum.
	//! @param [in,out]	dZMax	The z coordinate maximum.

	void GetBoundingBox(double& dXMin, double& dXMax, double& dYMin, double& dYMax, double& dZMin, double& dZMax);

protected:
	/*	The sequence of the 8 vertex as (I,J,K): (0,0,0), (0,1,0), (1,1,0), (1,0,0)
		(0,0,1), (0,1,1), (1,1,1), (1,0,1)
		   3--------2           ^
		  /|       /|          /
		 / |      / |         I
		0--+-----1  |        /
		|  |     |  |       0---J---->
		|  7-----+--6       |
		| /      | /        K
		|/       |/         |
		4--------5          V
	*/
	double			m_pVertex[24];			//	X, Y, Z of 8 vertex, length is 8*3=24.
	unsigned char	m_iSegmentIndex;		//	Index of the segment this cell belongs to.
	unsigned short	m_iI;
	unsigned short	m_iJ;
	unsigned short	m_iK;
};

#endif