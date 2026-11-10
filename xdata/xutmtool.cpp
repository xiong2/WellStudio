#include "xutmtool.h"
#include "xmathmacro.h"


CXUTMTool::CXUTMTool()
{
	//	Both size and cooridnates initialize to invalid value.
	m_nI = 0;
	m_nJ = 0;

	m_fX0 = -999.;
	m_fY0 = -999.;

	m_fDIX = 0.;
	m_fDIY = 0.;
	m_fDJX = 0.;
	m_fDJY = 0.;
}

CXUTMTool::CXUTMTool(const CXUTMTool& other)
{
	m_nI = other.m_nI;
	m_nJ = other.m_nJ;

	m_fX0 = other.m_fX0;
	m_fY0 = other.m_fY0;

	m_fDIX = other.m_fDIX;
	m_fDIY = other.m_fDIY;
	m_fDJX = other.m_fDJX;
	m_fDJY = other.m_fDJY;
}

CXUTMTool::~CXUTMTool()
{
}

bool CXUTMTool::InitSize(int nI, int nJ)
{
	//	The minimum meanful size is 1*2.
	if(nI * nJ <= 1)
		return false;

	m_nI = nI;
	m_nJ = nJ;

	//	Coordinates intialized to invalid.
	m_fX0 = -999.;
	m_fY0 = -999.;

	m_fDIX = 0.;
	m_fDIY = 0.;
	m_fDJX = 0.;
	m_fDJY = 0.;

	return true;
}

/*	Intialize the coordinates, by 3 input points, user should initialize size before call this function.
*	This 3 points are not necessary the 3 corner, but should not belong to one beeline.
*	Unless the size of I or J is only 1, thus only the 2 points are used.
*/
bool CXUTMTool::InitCoordinates(int i0, int j0, double x0, double y0, 
	int i1, int j1, double x1, double y1, 
	int i2, int j2, double x2, double y2)
{
	//	Size not initialized.
	if(m_nI * m_nJ <= 1)
		return false;

	if(m_nI == 1)
	{
		//	While size of I direction is only 1, all I should be 0.
		if(i0 != 0 || i1 != 0 || i2 != 0)
			return false;

		//	Use two different points.
		if(j0 != j1)
		{
			//	Delta X, Y for J increament.
			m_fDJX = (x1 - x0)/(j1 - j0);
			m_fDJY = (y1 - y0)/(j1 - j0);

			//	Original point.
			m_fX0 = x1 - j1 * m_fDJX;
			m_fY0 = y1 - j1 * m_fDJY;
		}
		else if(j0 != j2)
		{
			//	Delta X, Y for J increament.
			m_fDJX = (x2 - x0)/(j2 - j0);
			m_fDJY = (y2 - y0)/(j2 - j0);

			//	Original point.
			m_fX0 = x2 - j2 * m_fDJX;
			m_fY0 = y2 - j2 * m_fDJY;
		}
		else
			return false;	//	3 points are the same.
	}
	else if(m_nJ == 1)
	{
		//	While size of J direction is only 1£¬ all I should be 0.
		if(j0 != 0 || j1 != 0 || j2 != 0)
			return false;

		//	Use two different points.
		if(i0 != i1)
		{
			//	Delta X, Y for J increament.
			m_fDIX = (x1 - x0)/(i1 - i0);
			m_fDIY = (y1 - y0)/(i1 - i0);

			//	Original point.
			m_fX0 = x1 - i1 * m_fDIX;
			m_fY0 = y1 - i1 * m_fDIY;
		}
		else if(i0 != i2)
		{
			//	Delta X, Y for J increament.
			m_fDIX = (x2 - x0)/(i2 - i0);
			m_fDIY = (y2 - y0)/(i2 - i0);

			//	Original point.
			m_fX0 = x2 - i2 * m_fDIX;
			m_fY0 = y2 - i2 * m_fDIY;
		}
		else
			return false;	//	3 points are the same.
	}
	else
	{
		int nx1 = i1 - i0;
		int nx2 = i2 - i0;
		int ny1 = j1 - j0;
		int ny2 = j2 - j0;

		if (nx1*ny2 == nx2*ny1)
		{
			//	This 3 points locate on a beeline.
			return false;
		}

		int iRatio = (i0 - i1)*(j0 - j2) - (i0 - i2)*(j0 - j1);
		if(iRatio == 0)
			iRatio = 1;

		//	Now calculate the delat X, Y for I, J increament.
		m_fDIX =  ((x0 - x1)*(j0 - j2) - (x0 - x2)*(j0 - j1))/iRatio;
		m_fDJX = -((x0 - x1)*(i0 - i2) - (x0 - x2)*(i0 - i1))/iRatio;
		m_fDIY =  ((y0 - y1)*(j0 - j2) - (y0 - y2)*(j0 - j1))/iRatio;
		m_fDJY = -((y0 - y1)*(i0 - i2) - (y0 - y2)*(i0 - i1))/iRatio;

		//	Original point.
		m_fX0 = x1 - i1*m_fDIX - j1*m_fDJX;
		m_fY0 = y1 - i1*m_fDIY - j1*m_fDJY;
	}

	//	Only one line, need not check the angle.
	if (m_nI == 1)
		return true;

	//Tell if inline and xline are orthogonal
	double fD1 = sqrt(m_fDIX*m_fDIX + m_fDIY*m_fDIY);
	double fD2 = sqrt(m_fDJX*m_fDJX + m_fDJY*m_fDJY);
	if ( qAbs(fD1) < M_FEPS || qAbs(fD2) < M_FEPS)
		return false;

	double fAngle = acos((m_fDIX*m_fDJX + m_fDIY*m_fDJY)/(fD1*fD2))*180.0/M_PI;
	if (qAbs(fAngle - 90.0) < 5)
		return true;
	else
		return false;
}

 bool CXUTMTool::SerializeData(CXArchive& ar)
 {
	 if (ar.IsSaving())
	 {
		 ar<<m_nI;
		 ar<<m_nJ;
		 ar<<m_fX0;
		 ar<<m_fY0;
		 ar<<m_fDIX;
		 ar<<m_fDIY;
		 ar<<m_fDJX; 
		 ar<<m_fDJY;
	 }
	 else
	 {
		 ar>>m_nI;
		 ar>>m_nJ;
		 ar>>m_fX0;
		 ar>>m_fY0;
		 ar>>m_fDIX;
		 ar>>m_fDIY;
		 ar>>m_fDJX; 
		 ar>>m_fDJY;
	 }

	 return true;
 }

//	Create and new UTM based on current one and input parameters.
CXUTMTool* CXUTMTool::GenerateNewUTM(int i0, int j0, int nI, int nJ, int nIInterval, int nJInterval)
{
	//	Size can not be too small.
	if(nI * nJ <= 1)
		return NULL;

	//	Creat the new one and set the original point.
	CXUTMTool *pUTM = new CXUTMTool;
	pUTM->InitSize(nI, nJ);
	pUTM->m_fX0 = m_fX0 + i0 * m_fDIX + j0 * m_fDJX;
	pUTM->m_fY0 = m_fY0 + i0 * m_fDIY + j0 * m_fDJY;

	//	Set the new DX, DY of I diretion.
	if(nIInterval > 0)
	{
		pUTM->m_fDIX = m_fDIX * nIInterval;
		pUTM->m_fDIY = m_fDIY * nIInterval;
	}
	else if(nIInterval < 0)
	{
		pUTM->m_fDIX = m_fDIX / qAbs(nIInterval);
		pUTM->m_fDIY = m_fDIY / qAbs(nIInterval);
	}
	else
	{
		pUTM->m_fDIX = m_fDIX;
		pUTM->m_fDIY = m_fDIY;
	}

	//	Set the new DX, DY of J direction.
	if(nJInterval > 0)
	{
		pUTM->m_fDJX = m_fDJX * nJInterval;
		pUTM->m_fDJY = m_fDJY * nJInterval;
	}
	else if(nJInterval < 0)
	{
		pUTM->m_fDJX = m_fDJX / qAbs(nJInterval);
		pUTM->m_fDJY = m_fDJY / qAbs(nJInterval);
	}
	else
	{
		pUTM->m_fDJX = m_fDJX;
		pUTM->m_fDJY = m_fDJY;
	}

	return pUTM;
}

//	Is the input UTM compatible with current one?
bool CXUTMTool::IsCompatible(CXUTMTool *pUTM)
{
	if (!pUTM)
		return false;	

	int nI = pUTM->GetNI();
	int nJ = pUTM->GetNJ();

	if (m_nI*m_nJ <=1 || nI*nJ <=1)
		return false;

	double dComingIDirection = pUTM->GetIDirection();
	double dComingJDirection = pUTM->GetJDirection();
	double dIDirection = this->GetIDirection();
	double dJDirection = this->GetJDirection();

	if (nI == 1)
	{
		if (m_nJ > 1)		
			return qAbs(dComingJDirection - dJDirection) < qMax(0.618, qMax(dComingJDirection, dJDirection)*0.01);
	}
	else if (nJ == 1)
	{
		if (m_nI > 1)
			return qAbs(dComingIDirection - dIDirection) < qMax(0.618, qMax(dComingIDirection, dIDirection)*0.01);
	}
	else
	{
		if (m_nI == 1)
			return qAbs(dComingJDirection - dJDirection) < qMax(0.618, qMax(dComingJDirection, dJDirection)*0.01);
		else if (m_nJ == 1)
			return qAbs(dComingIDirection - dIDirection) < qMax(0.618, qMax(dComingIDirection, dIDirection)*0.01);
		else
		{
			bool bJ = qAbs(dComingJDirection - dJDirection) < qMax(0.618, qMax(dComingJDirection, dJDirection)*0.01);
			bool bI = qAbs(dComingIDirection - dIDirection) < qMax(0.618, qMax(dComingIDirection, dIDirection)*0.01);
			return bI && bJ; 
		}
	}

	return false;
}

/// Tell if two UTM's are equal
bool CXUTMTool::Equals(CXUTMTool *pOther)
{
	if (pOther == NULL)
		return false;

	int nI = pOther->GetNI();
	int nJ = pOther->GetNJ();

	if (m_nI != nI || m_nJ != nJ)
		return false;

	if (!IsCompatible(pOther))
		return false;

	const double fErrorPercentage = 0.15;
	double fErrorEPS = qMax(GetIInterval(), GetJInterval())*fErrorPercentage;

	double x0, y0, x1, y1, x0_, y0_, x1_, y1_;
	this->IJToXY(0, 0, x0, y0);
	this->IJToXY(nI-1, nJ-1, x1, y1);
	pOther->IJToXY(0, 0, x0_, y0_);
	pOther->IJToXY(nI-1, nJ-1, x1_, y1_);

	if (qAbs(x0 - x0_) > fErrorEPS || qAbs(x1 - x1_) > fErrorEPS || qAbs(y0 - y0_) > fErrorEPS || qAbs(y1 - y1_) > fErrorEPS )
		return false;
	else
		return true;
}

//	Copy everything from the source UTM.
void CXUTMTool::Copy(CXUTMTool *pSourceUTM)
{
	m_nI = pSourceUTM->m_nI;
	m_nJ = pSourceUTM->m_nJ;
	m_fX0 = pSourceUTM->m_fX0;
	m_fY0 = pSourceUTM->m_fY0;
	m_fDIX = pSourceUTM->m_fDIX;
	m_fDIY = pSourceUTM->m_fDIY;
	m_fDJX = pSourceUTM->m_fDJX;
	m_fDJY = pSourceUTM->m_fDJY;
}

//	Input I, J and get the corresponding X, Y.  Return true means inside the grid.
bool CXUTMTool::IJToXY(int i, int j, double& x, double& y) const
{
	return IJToXY2(static_cast<double>(i), static_cast<double>(j),x,y);
}

bool CXUTMTool::IJToXY2(double i, double j, double& x, double& y) const
{
	x = m_fX0 + i * m_fDIX + j * m_fDJX;
	y = m_fY0 + i * m_fDIY + j * m_fDJY;

	//	Inside the grid?
	if(i < 0 || i >= m_nI || j < 0 || j >= m_nJ)
		return false;
	else
		return true;

}

//	Input X, Y and get the corresponding I, J.  Return true means inside the grid.
bool CXUTMTool::XYToIJ(double x, double y, int& i, int& j)
{	
	float iValue, jValue;

	XYToIJ(x,y,iValue,jValue);

	i=int(iValue+0.5);
	j=int(jValue+0.5);

	if(i < 0 || i >= m_nI || j < 0 || j >= m_nJ)
		return false;
	else
		return true;
}

bool CXUTMTool::XYToIJ(double x, double y, float& i, float& j)
{
	i = static_cast<float>((m_fDJY * (x - m_fX0) - m_fDJX * (y - m_fY0))/(m_fDIX * m_fDJY - m_fDJX * m_fDIY));
	j = static_cast<float>((m_fDIY * (x - m_fX0) - m_fDIX * (y - m_fY0))/(m_fDJX * m_fDIY - m_fDIX * m_fDJY) );

	//	Inside the grid?
	if(i < 0 || i > m_nI-1 || j < 0 || j > m_nJ-1)
		return false;
	else
		return true;

}

//	Get the interval in I direction.
double CXUTMTool::GetIInterval() const
{
	return sqrt(m_fDIY * m_fDIY + m_fDIX * m_fDIX);
}

//	Get the interval in J direction.
double CXUTMTool::GetJInterval() const
{
	return sqrt(m_fDJY * m_fDJY + m_fDJX * m_fDJX);
}

//	Get the bounding box's corners coordinates.
void CXUTMTool::GetDimensionRange(double &fXMin, double &fXMax, double &fYMin, double &fYMax)
{
	//	Calculate the other 3 corners cooridnates.
	double x1, y1, x2, y2, x3, y3;
	x1 = m_fX0 + (m_nJ - 1) * m_fDJX;
	y1 = m_fY0 + (m_nJ - 1) * m_fDJY;
	x2 = m_fX0 + (m_nJ - 1) * m_fDJX + (m_nI - 1) * m_fDIX;
	y2 = m_fY0 + (m_nJ - 1) * m_fDJY + (m_nI - 1) * m_fDIY;
	x3 = m_fX0 + (m_nI - 1) * m_fDIX;
	y3 = m_fY0 + (m_nI - 1) * m_fDIY;

	fXMin = m_fX0;
	if(fXMin > x1)
		fXMin = x1;
	if(fXMin > x2)
		fXMin = x2;
	if(fXMin > x3)
		fXMin = x3;

	fYMin = m_fY0;
	if(fYMin > y1)
		fYMin = y1;
	if(fYMin > y2)
		fYMin = y2;
	if(fYMin > y3)
		fYMin = y3;

	fXMax = m_fX0;
	if(fXMax < x1)
		fXMax = x1;
	if(fXMax < x2)
		fXMax = x2;
	if(fXMax < x3)
		fXMax = x3;

	fYMax = m_fY0;
	if(fYMax < y1)
		fYMax = y1;
	if(fYMax < y2)
		fYMax = y2;
	if(fYMax < y3)
		fYMax = y3;
}

//	Get the I direction, counter-clockwise with horizontal line, from origin to right.
double CXUTMTool::GetIDirection()
{
	double x0, y0, x1, y1;
	this->IJToXY(0, 0, x0, y0);
	this->IJToXY(1, 0, x1, y1);

	double dAngle = atan2(y1-y0, x1-x0)*M_DEG;
	if (dAngle < 0)
		dAngle += 360.0;

	return dAngle;
}

//	Get the J direction, counter-clockwise with horizontal line, from origin to right.
double CXUTMTool::GetJDirection()
{
	double x0, y0, x1, y1;
	this->IJToXY(0, 0, x0, y0);
	this->IJToXY(0, 1, x1, y1);

	double dAngle = atan2(y1-y0, x1-x0)*M_DEG;
	if (dAngle < 0)
		dAngle += 360.0;

	return dAngle;
}

void CXUTMTool::ChangeUnit(double factor)
{
	m_fX0 *= factor;
	m_fY0 *= factor;

	m_fDIX *= factor;
	m_fDIY *= factor;
	m_fDJX *= factor;
	m_fDJY *= factor;
}

//	To resize current UTMTool, but still compatible with original one.
bool CXUTMTool::_resize(int i0, int j0, int ni, int nj, double iInc, double jInc)
{
	//	Change the original point first.
	m_fX0 += (i0 * m_fDIX + j0 * m_fDJX);
	m_fY0 += (i0 * m_fDIY + j0 * m_fDJY);

	//	Set the new size.
	m_nI = ni;
	m_nJ = nj;

	//	Adjust the step them.
	m_fDIX *= iInc;
	m_fDIY *= iInc;
	m_fDJX *= jInc;
	m_fDJY *= jInc;

	return true;
}

bool CXUTMTool::IsIntersecting(CXUTMTool *pOther) const
{
	double x0_, y0_, x1_, y1_;
	double x0, y0, x1, y1;

	if (!IJToXY(0, 0, x0_, y0_) || !IJToXY(m_nI-1, m_nJ-1, x1_, y1_) )
		return false;

	if (!pOther->IJToXY(0, 0, x0, y0) || !pOther->IJToXY(pOther->m_nI-1, pOther->m_nJ-1, x1, y1))
		return false;

	if (x0_ > x1_)
		qSwap(x0_, x1_);
	if (y0_ > y1_)
		qSwap(y0_, y1_);
	if (x0 > x1)
		qSwap(x0, x1);
	if (y0 > y1)
		qSwap(y0, y1);

	if (x0_ > x1 || x0 > x1_)
		return false;

	if (y0_ > y1 || y0 > y1_)
		return false;

	return true;
}

void CXUTMTool::RemoveXStrip()
{
	if (m_fX0 > 10000000)
	{
		int iBase = (int)m_fX0 / 1000000;
		iBase *= 1000000;
		m_fX0 -= iBase;
	}
}
