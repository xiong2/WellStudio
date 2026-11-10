#ifndef _CXECLIPSEOBJECT_H__
#define _CXECLIPSEOBJECT_H__

#include <qbitarray.h>

struct SPillar
{
	float m_pPoints[6];		//	X, Y, Z of the pillar top and delta X, delta Y, delta Z.
};

///@brief	The class used to represent a tmp object while importing eclipse model file.
///@author	Xiong Xiong
///@date	Nov, 2014
///@see		
class CXEclipseObject
{
public:
	CXEclipseObject(unsigned int nI, unsigned int nJ, unsigned int nK);
	~CXEclipseObject();

	unsigned int	m_nI;
	unsigned int	m_nJ;
	unsigned int	m_nK;
	unsigned int	m_nTotalCells;

	SPillar*		m_pPillars;
	float*			m_pZCoord;
	QBitArray		m_arrayBit;
};

#endif