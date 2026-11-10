#include <QtCore/qglobal.h>
#include "xeclipseobject.h"

CXEclipseObject::CXEclipseObject(unsigned int nI, unsigned int nJ, unsigned int nK)
{
	m_nI			= nI;
	m_nJ			= nJ;
	m_nK			= nK;
	m_nTotalCells	= m_nI * m_nJ * m_nK;

	m_pPillars		= NULL;
	m_pZCoord		= NULL;
	if(m_nTotalCells > 0)
	{
		m_pPillars	= new SPillar[(nI + 1) * (nJ + 1)];
		m_pZCoord	= new float[m_nTotalCells * 8];
		m_arrayBit.resize(m_nTotalCells);
	}
}

CXEclipseObject::~CXEclipseObject()
{
	if(m_pPillars)
	{
		delete []m_pPillars;
		delete []m_pZCoord;
	}
}