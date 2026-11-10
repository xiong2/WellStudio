#ifndef XGMPOINT_H
#define XGMPOINT_H

#include "xgeomodel_global.h"
#include <cmath>
#include "xfunctiontemplate.h"
#include "xmathmacro.h"

class XGEOMODEL_EXPORT CXGMPoint
{
public:
	CXGMPoint(double x=0., double y=0., double z=0.):m_dX(x), m_dY(y), m_dZ(z) {}
	~CXGMPoint(){}

	double Distance(const CXGMPoint& other)
	{
		return sqrt(SQR(m_dX-other.m_dX)+SQR(m_dY-other.m_dY)+SQR(m_dZ-other.m_dZ));
	}

	double Distance2(const CXGMPoint& other)
	{
		return (SQR(m_dX-other.m_dX)+SQR(m_dY-other.m_dY)+SQR(m_dZ-other.m_dZ));
	}

	bool IsEqual(const CXGMPoint& other)
	{
		return (qAbs(m_dX - other.m_dX) < M_FEPS &&
				qAbs(m_dY - other.m_dY) < M_FEPS &&
				qAbs(m_dZ - other.m_dZ) < M_FEPS);			    
	}

	double m_dX, m_dY, m_dZ;

private:
	
};

#endif // RFGMPOINT_H
